import bpy
import array
import numpy
import os
import xml.etree.ElementTree as element_tree
import struct
import bpy_extras
from bpy_extras.io_utils import ExportHelper
import bmesh
import shutil
import xml.dom.minidom as minidom
import mathutils

_texture_mapping = dict()

# Function that makes xml trees pretty for printing
def make_pretty_xml(elem):
    rough_string = element_tree.tostring(elem, encoding="us-ascii")
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="\t")

# Make sure a given object is trangulated
def triangulate_object(obj):
    me = obj.data
    # Get a BMesh representation
    bm = bmesh.new()
    bm.from_mesh(me)

    bmesh.ops.triangulate(bm, faces=bm.faces[:], quad_method=0, ngon_method=0)

    # Finish up, write the bmesh back to the mesh
    bm.to_mesh(me)
    bm.free()

def to_y_up(matrix):
    mm = bpy_extras.io_utils.axis_conversion(from_forward='Y', from_up='Z', to_forward='-Z', to_up='Y')
    om = matrix.to_3x3()
    t = mm * om
    output_mat = mathutils.Matrix()
    output_mat[0][0] = t[0][0]
    output_mat[0][1] = t[0][1]
    output_mat[0][2] = t[0][2]
    output_mat[0][3] = matrix[0][3]

    output_mat[1][0] = t[1][0]
    output_mat[1][1] = t[1][1]
    output_mat[1][2] = t[1][2]
    output_mat[1][3] = matrix[2][3]

    output_mat[2][0] = t[2][0]
    output_mat[2][1] = t[2][1]
    output_mat[2][2] = t[2][2]
    output_mat[2][3] = -matrix[1][3]

    output_mat[3][0] = 0
    output_mat[3][1] = 0
    output_mat[3][2] = 0
    output_mat[3][3] = 1

    return output_mat

def mat_to_string(matrix):
    y_up_mat = to_y_up(matrix)

    out_str = str(y_up_mat[0][0])    
    out_str += " "
    out_str += str(y_up_mat[0][1])    
    out_str += " "
    out_str += str(y_up_mat[0][2])
    out_str += " "
    out_str += str(y_up_mat[0][3])
    out_str += " "
    out_str += str(y_up_mat[1][0])    
    out_str += " "
    out_str += str(y_up_mat[1][1])    
    out_str += " "
    out_str += str(y_up_mat[1][2])
    out_str += " "
    out_str += str(y_up_mat[1][3])
    out_str += " "
    out_str += str(y_up_mat[2][0])    
    out_str += " "
    out_str += str(y_up_mat[2][1])    
    out_str += " "
    out_str += str(y_up_mat[2][2])
    out_str += " "
    out_str += str(y_up_mat[2][3])
    out_str += " "
    out_str += str(y_up_mat[3][0])    
    out_str += " "
    out_str += str(y_up_mat[3][1])    
    out_str += " "
    out_str += str(y_up_mat[3][2])
    out_str += " "
    out_str += str(y_up_mat[3][3])
    return out_str

def vector_to_string(vector3):
    out_str = str(vector3[0])    
    out_str += " "
    out_str += str(vector3[1])    
    out_str += " "
    out_str += str(vector3[2])    
    out_str += " 1"
    return out_str

def export_geometry(mesh_data, output_file_name, matrix, dupli_offset):

    # Lets open our target file
    fout = open(output_file_name, 'w')

    # Our Header
    fout.write("# Donut wavefront exporter\n")
    fout.write("\n")

    # Write all the positions
    for v in mesh_data.vertices:
        transformed_pos =  matrix * v.co + dupli_offset
        fout.write("v %.4f %.4f %.4f\n" % transformed_pos[:])
    fout.write("\n")
    
    # The internal blender format supports multiple UV channels
    # The first one is used for the Diffuse, NormalMap, ARM and the second one
    # (if available) is used for lightmaps
    if (len(mesh_data.uv_layers) > 0) :
        for tex_coord in mesh_data.uv_layers[0].data:
            fout.write("vt %.4f %.4f\n" % tex_coord.uv[:])
    else:
        for loop in mesh_data.polygons:
            fout.write("vt %.4f %.4f\n" % (0, 0))
            fout.write("vt %.4f %.4f\n" % (0, 0))
            fout.write("vt %.4f %.4f\n" % (0, 0))
    fout.write("\n")         
    
    # Finally write all the faces and their indexes
    face_idx = 0
    for p in mesh_data.polygons:
        fout.write("f ")
        vert_idx = 0
        for i in p.vertices:
            fout.write("%d/%d " % (i + 1, 3 * face_idx + vert_idx + 1))
            vert_idx = vert_idx + 1
        face_idx = face_idx + 1
        fout.write("\n")

def export_sugar(sugar_name, geometry_relative_path, material_name, project_dir):
    print("Exporting sugar: " + sugar_name)

    # Building the sugar xml file
    sugar_node = element_tree.Element("sugar", name=sugar_name)
    renderables_node = element_tree.SubElement(sugar_node, "renderables")
    renderable_node = element_tree.SubElement(renderables_node, "renderable", id="0")
    geometry_node = element_tree.SubElement(renderable_node, "geometry", location=geometry_relative_path)
    material_node = element_tree.SubElement(renderable_node, "material", name=material_name)

    sugar_dir = project_dir + "/sugars/" + sugar_name + ".sugar"
    fout = open(sugar_dir, 'w')
    fout.write(make_pretty_xml(sugar_node))

def export_material(material_name, material, output_topping_path):
    print("Exporting topping: " + material_name)

    # Lets define if this material uses any texture
    uses_texture = False

    mat_texture_list = []

    if material and material.use_nodes:
        for n in material.node_tree.nodes:
            if n.type == 'TEX_IMAGE':
                uses_texture = True
                mat_texture_list.append(_texture_mapping[n.image.filepath]);

    # Building the topping xml file
    topping_node = element_tree.Element("topping", name=material_name)
    # Create the shaders
    shader_node = element_tree.SubElement(topping_node, "shader")
    if uses_texture:
        vertex_node = element_tree.SubElement(shader_node, "vertex", location="common/shaders/base/vertex.glsl")
        geometry_node = element_tree.SubElement(shader_node, "geometry", location="common/shaders/base/geometry.glsl")
        fragment_node = element_tree.SubElement(shader_node, "fragment", location="common/shaders/base/fragment.glsl")
        textures_node = element_tree.SubElement(topping_node, "textures")
        color_node = element_tree.SubElement(textures_node, "texture2D", name="textureCmp", location=mat_texture_list[0])
    else:
        vertex_node = element_tree.SubElement(shader_node, "vertex", location="common/shaders/uniform_color/vertex.glsl")
        fragment_node = element_tree.SubElement(shader_node, "fragment", location="common/shaders/uniform_color/fragment.glsl")
        extern_data_node = element_tree.SubElement(topping_node, "extern_data")
        color_str = "1 1 1 1"
        if material != None:
            color_str = vector_to_string(material.diffuse_color)
        color_node = element_tree.SubElement(extern_data_node, "data", type="vec4", name="uniform_color", value=color_str)

    fout = open(output_topping_path, 'w')
    fout.write(make_pretty_xml(topping_node))

def export_element(target_object, root_node, target_path, project_name, project_dir):

    if(target_object.library):
        print("Object in library")

    # Export name
    asset_name = target_object.name.lower()
    print("Exporting sugar: " + asset_name)

    # Create the scene node that holds it
    new_scene_node = element_tree.SubElement(root_node, "node", TM=mat_to_string(target_object.matrix_world))
    sugar_instance = element_tree.SubElement(new_scene_node, "model", sugar=asset_name)

    # Make sure the geometry is triangulated first
    triangulate_object(target_object)

    # Fetching the actual geometry
    mesh_name = target_object.data.name.lower()
    
    # Fetch the materials of this mesh
    current_material = target_object.active_material
    material_name = asset_name + "_material"
    material_output_path = project_dir + "/toppings/" + material_name + ".topping"
    export_material(material_name, current_material, material_output_path)

    # Output the geometry
    geometry_output_path = project_dir + "/geometries/" + mesh_name + ".obj"
    export_geometry(target_object.data, geometry_output_path, mathutils.Matrix.Identity(4), mathutils.Vector((0,0,0)))

    # Export the sugar that matches this element
    export_sugar(asset_name, project_name + "/geometries/" + mesh_name + ".obj", material_name, project_dir)

def export_scene (target_scene, target_path, project_name, project_dir):
    # Create the level file
    flour_file = os.path.join(project_dir, "default.flour")
    print ("The exported flour will be at " + flour_file)

    # Create all the required nodes of the flour
    flour_node = element_tree.Element("flour", name="blender_flour")
    root_node = element_tree.SubElement(flour_node, "node")
    pipeline_node = element_tree.SubElement(flour_node, "pipeline", name="complete")
    illumination_node = element_tree.SubElement(flour_node, "illumination")

    for obj in target_scene.objects:
        # If it has a mesh create a sugar for it
        if (obj.type == "MESH"):
            export_element(obj, root_node, target_path, project_name, project_dir)

        # If it has a dupli group
        if(obj.dupli_group):
            group_name = obj.dupli_group.name.lower() + "_group"
            new_scene_node = element_tree.SubElement(root_node, "node", TM=mat_to_string(obj.matrix_world))
            sugar_instance = element_tree.SubElement(new_scene_node, "model", sugar=group_name)

    # Build the tree and export it
    fout = open(flour_file, 'w')
    fout.write(make_pretty_xml(flour_node))

def export_groups(target_path, project_name):
    # Go through the groups
    for group in bpy.data.groups:

        # Evaluate the group asset-name
        group_name = group.name.lower() + "_group"

        # Building the sugar xml
        sugar_node = element_tree.Element("sugar", name=group_name)
        renderables_node = element_tree.SubElement(sugar_node, "renderables")

        # Index of the renderable
        geo_idx = 0

        # Loop through the elements of this object
        for obj in group.objects:
            # If the object is a mesh, process it as a mesh
            if (obj.type == "MESH"):

                # triangulate the object first
                triangulate_object(obj)

                # Generate the name for the matching assets
                geometry_name = obj.name.lower()
                material_name = obj.name.lower() + "_material"
                geometry_relative_path = project_name + "/geometries/" + geometry_name + "_group.obj"
                geometry_absolute_path = target_path + geometry_relative_path
                material_absolute_path = target_path + project_name + "/toppings/" + material_name + "_group.topping"

                # Create a renderable node for it 
                renderable_node = element_tree.SubElement(renderables_node, "renderable", id=str(geo_idx))
                geometry_node = element_tree.SubElement(renderable_node, "geometry", location=geometry_relative_path)
                material_node = element_tree.SubElement(renderable_node, "material", name=material_name)

                # Write the geometry file
                export_geometry(obj.data, geometry_absolute_path, obj.matrix_world, group.dupli_offset)
                geo_idx += 1

                # Write the material file
                export_material(material_name, obj.active_material, material_absolute_path)

        # Generate the output filename of the sugar file
        sugar_path = target_path + project_name + "/sugars/" + group_name + ".sugar"
        fout = open(sugar_path, 'w')
        fout.write(make_pretty_xml(sugar_node))

def export_textures(target_path, project_name):
    # Go through the images
    for image_var in bpy.data.images:
        # Get the absolute path of the image
        image_absolute_path = image_var.filepath_from_user()
        # If the file exists
        if os.path.isfile(image_absolute_path):
            # Get the basename of the file
            base_name = os.path.basename(image_absolute_path)
            output_image_path = target_path + project_name + "/textures/" + base_name
            shutil.copyfile(os.path.realpath(bpy.path.abspath(image_absolute_path)), output_image_path)

            # Add it to the mapping
            _texture_mapping[image_var.filepath] = project_name + "/textures/" + base_name

def create_project_structure(project_dir):
    print("Project will be exported to " + project_dir)
 
    # Destroy the hosting folder if it exists
    if os.path.exists(project_dir):
        shutil.rmtree(project_dir)
    
    # Make sure 
    while os.path.exists(project_dir):
        pass

    os.makedirs(project_dir)
    os.makedirs(project_dir + "/geometries")
    os.makedirs(project_dir + "/sugars")
    os.makedirs(project_dir + "/toppings")
    os.makedirs(project_dir + "/textures")

def export_donut_project(target_path, project_name):
    # Build the projet directory
    project_dir = target_path + "/" + project_name

    # First of all we need to create the donut project (file hierarchy)
    create_project_structure(project_dir)

    # Copy all the texture files used by this project
    export_textures(target_path, project_name)

    # Lets go through all the groups and flatten each one of them as a sugar
    export_groups(target_path, project_name)

    # Export all the scene items
    export_scene(bpy.context.scene, target_path, project_name, project_dir)

# Gather the required data
target_path = "C:/TEMP/"
project_name = "blender_scene"

# Export the scene into a donut project
export_donut_project(target_path, project_name)