import bpy
import array
import numpy
import os
import xml.etree.cElementTree as element_tree
import struct
from bpy_extras.io_utils import ExportHelper


# Plugin information
bl_info = {
    "name": "Donut exporter",
    "author": "Anis Benyoub",
    "version": (1, 0, 0),
    "blender": (2, 78, 0),
    "location": "File > Import-Export",
    "description": "Exports the current scene for the donut engine",
    "warning": "",
    "category": "Export"}

# Class that handles the resource locations for a donut project
class DonutProject:
    def __init__(self):
        self.project_name = None
        self.project_dir = None
        self.flours_dir = None
        self.sugars_dir = None
        self.eggs_dir = None
        self.toppings_dir = None

    def create_folders(self, blender_path):
        path_to_directory = os.path.dirname(blender_path)
        self.project_name = os.path.splitext(os.path.basename(blender_path))[0]
        self.project_dir = os.path.join(path_to_directory, self.project_name)
        print("Project will be exported to " +  self.project_dir)

        # Create the hosting folder
        if not os.path.exists(self.project_dir):
            os.makedirs(self.project_dir)

        # Generate all the project paths
        self.flours_dir = os.path.join(self.project_dir, "flours")
        self.sugars_dir = os.path.join(self.project_dir, "sugars")
        self.eggs_dir = os.path.join(self.project_dir, "eggs")
        self.toppings_dir = os.path.join(self.project_dir, "toppings")

        # Create all the required directories
        if not os.path.exists(self.flours_dir):
            os.makedirs(self.flours_dir)
        if not os.path.exists(self.sugars_dir):
            os.makedirs(self.sugars_dir)
        if not os.path.exists(self.eggs_dir):
            os.makedirs(self.eggs_dir)
        if not os.path.exists(self.toppings_dir):
            os.makedirs(self.toppings_dir)

# Class that defines the geometry of a donut egg
class Egg:
    def __init__(self):
        self.name = None
        self.num_vertices = 0
        self.vertex_array = []
        self.num_faces = 0
        self.index_array = []

    def build(self, mesh_data):
        # Fetch the uv_layers
        uv_layer = None
        has_uv = False
        if (len(mesh_data.uv_layers) > 0) :
            has_uv = True
            uv_layer = mesh_data.uv_layers[0].data

        # Fetching the number of vertice
        num_vertices = len(mesh_data.vertices)

        # Declaring the indermediate arrays
        coord_array = []
        normal_array = []
        uv_array = []

        # Lets iterate over the polygons of the mesh
        for poly in mesh_data.polygons:
            if (poly.loop_total == 3):
                # Fetch the indexes of the vertices
                i0 = mesh_data.loops[poly.loop_start].vertex_index
                i1 = mesh_data.loops[poly.loop_start + 1].vertex_index
                i2 = mesh_data.loops[poly.loop_start + 2].vertex_index

                # Fetch the coordinates
                v0 =  mesh_data.vertices[i0].co
                v1 =  mesh_data.vertices[i1].co
                v2 =  mesh_data.vertices[i2].co
                coord_array.extend([v0.x, v0.y, v0.z, v1.x, v1.y, v1.z, v2.x, v2.y, v2.z])

                # Fetch the normals
                n0 =  mesh_data.vertices[i0].normal
                n1 =  mesh_data.vertices[i1].normal
                n2 =  mesh_data.vertices[i2].normal
                normal_array.extend([n0.x, n0.y, n0.z, n1.x, n1.y, n1.z, n2.x, n2.y, n2.z])

                if has_uv:
                    # Fetch the uvs
                    tx0 = uv_layer[poly.loop_start].uv
                    tx1 = uv_layer[poly.loop_start + 1].uv
                    tx2 = uv_layer[poly.loop_start + 2].uv
                    uv_array.extend([tx0.x, tx0.y, tx1.x, tx1.y, tx2.x, tx2.y])
                else:
                    uv_array.extend([0.0, 0.0, 0.0, 0.0, 0.0, 0.0])

                # Append the face data
                self.index_array.extend([ self.num_vertices,  self.num_vertices + 1,  self.num_vertices + 2])

                # Increment the data-structure size
                self.num_vertices += 3
                self.num_faces += 1

            elif (poly.loop_total == 4):
                 # Fetch the indexes of the vertices
                i0 = mesh_data.loops[poly.loop_start].vertex_index
                i1 = mesh_data.loops[poly.loop_start + 1].vertex_index
                i2 = mesh_data.loops[poly.loop_start + 2].vertex_index
                i3 = mesh_data.loops[poly.loop_start + 3].vertex_index

                # Fetch the coordinates
                v0 =  mesh_data.vertices[i0].co
                v1 =  mesh_data.vertices[i1].co
                v2 =  mesh_data.vertices[i2].co
                v3 =  mesh_data.vertices[i3].co
                coord_array.extend([v0.x, v0.y, v0.z, v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z])

                # Fetch the normals
                n0 =  mesh_data.vertices[i0].normal
                n1 =  mesh_data.vertices[i1].normal
                n2 =  mesh_data.vertices[i2].normal
                n3 =  mesh_data.vertices[i3].normal
                normal_array.extend([n0.x, n0.y, n0.z, n1.x, n1.y, n1.z, n2.x, n2.y, n2.z, n3.x, n3.y, n3.z])

                # Fetch the uvs
                if has_uv:
                    tx0 = uv_layer[poly.loop_start].uv
                    tx1 = uv_layer[poly.loop_start + 1].uv
                    tx2 = uv_layer[poly.loop_start + 2].uv
                    tx3 = uv_layer[poly.loop_start + 3].uv
                    uv_array.extend([tx0.x, tx0.y, tx1.x, tx1.y, tx2.x, tx2.y, tx3.x, tx3.y])
                else:
                    uv_array.extend([0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0])

                # Append the new faces
                self.index_array.extend([ self.num_vertices,  self.num_vertices + 1,  self.num_vertices + 2])
                self.index_array.extend([ self.num_vertices ,  self.num_vertices + 2,  self.num_vertices + 3])

                # Increment the data-structure size
                self.num_vertices += 4
                self.num_faces += 2

        self.vertex_array.extend(coord_array)
        self.vertex_array.extend(normal_array)
        self.vertex_array.extend(uv_array)

    def export(self, file_name):
        fout = open(file_name, 'wb')
        fout.write(struct.pack('I', self.num_vertices ))
        fout.write(struct.pack('%sf' % len(self.vertex_array), *self.vertex_array))
        fout.write(struct.pack('I', self.num_faces))
        fout.write(struct.pack('%sI' % len(self.index_array), *self.index_array))
        fout.close()


def export_element(target_mesh, root_node, donut_project):
    print("Exporting mesh: " + target_mesh.name)

    # Create the scene node that holds it
    new_scene_node = element_tree.SubElement(root_node, "scene_node", TM="1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1")

    sugar_instance = element_tree.SubElement(new_scene_node, "scene_node", sugar=target_mesh.name)

    # Fetching the actual geometry
    input_mesh = target_mesh.data

    # Fetch the materials of this mesh
    materials = input_mesh.materials[:]
    material_names = [m.name if m else None for m in materials]
    print(material_names)

    # Export fhte geometry of this 
    new_egg = Egg()
    new_egg.build(input_mesh)
    new_egg.export(donut_project.eggs_dir + "/" + target_mesh.name + ".egg" )

def ExportCamera(target_camera):
    print("Exporting camera: " + target_camera.name)

def ExportLamp(target_lamp, illumination_node):
    print("Exporting lamp: " + target_lamp.name)
    print(target_lamp.color)
    new_lamp = element_tree.SubElement(illumination_node, "light")


def export_scene (scene_reference, donut_project):

    # Create the level file
    level_file = os.path.join(donut_project.flours_dir, (scene_reference.name + ".flour"))
    print ("The exported flour will be at " + level_file)

    # Create all the required nodes of the flour
    flour_node = element_tree.Element("flour")
    root_node = element_tree.SubElement(flour_node, "root")
    pipeline_node = element_tree.SubElement(flour_node, "pipeline", name="complete")
    illumination_node = element_tree.SubElement(flour_node, "illumination")

    for obj in scene_reference.objects:
        if (obj.type == "MESH"):
            export_element(obj, root_node, donut_project)
        elif (obj.type == "CAMERA"):
            ExportCamera(obj)
        elif (obj.type == "LAMP"):
            ExportLamp(obj, illumination_node)
        else:
            print("Object " + object.name + " "+ object.type +" will not be exported")

    # Build the tree and export it
    complete_tree = element_tree.ElementTree(flour_node)
    complete_tree.write(level_file)

def create_project(scene_reference, file_path):
    print("Creating donut project")
    donut_project = DonutProject()
    donut_project.create_folders(file_path)

    # Lets export the scene
    export_scene(scene_reference, donut_project)

class ExportDonut(bpy.types.Operator, ExportHelper):
    """Save a Wavefront OBJ File"""

    bl_idname = "export_scene.dpnut"
    bl_label = 'Export donut'
    bl_options = {'PRESET'}
    filename_ext = ".flour"

    def execute(self, context):
        create_project(context.scene, self.filepath)
        return {'FINISHED'}


def menu_func_export(self, context):
    self.layout.operator(ExportDonut.bl_idname, text="Donut")


def register():
    bpy.utils.register_module(__name__)

    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_module(__name__)

    bpy.types.INFO_MT_file_export.remove(menu_func_export)

if __name__ == "__main__":
    register()
