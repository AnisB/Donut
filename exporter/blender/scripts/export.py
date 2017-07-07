import bpy
from bpy_extras.io_utils import ExportHelper
import array
import numpy
import os
import xml.etree.cElementTree as element_tree

bl_info = {
    "name": "Donut exporter",
    "author": "Anis Benyoub",
    "version": (1, 0, 0),
    "blender": (2, 78, 0),
    "location": "File > Import-Export",
    "description": "Exports the current scene for the donut engine",
    "warning": "",
    "category": "Import-Export"}

# Class that handles the resources for a donut project
class DonutProject:
    def __init__(self):
        self.project_name = None
        self.project_dir = None
        self.flours_dir = None
        self.sugars_dir = None
        self.eggs_dir = None
        self.toppings_dir = None

    def create_folders(self, initial_path):
        path_to_directory = os.path.dirname(initial_path)
        self.project_name = os.path.splitext(os.path.basename(initial_path))[0]
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

def ExportMesh(target_mesh, root_node):
    print("Exporting mesh: " + target_mesh.name)

    # Create the scene node that holds it
    new_scene_node = element_tree.SubElement(root_node, "scene_node", TM="1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1")

    sugar_instance = element_tree.SubElement(new_scene_node, "scene_node", sugar=target_mesh.name)

    # Fetching the actual geometry
    rawMesh = target_mesh.data

    # Fetching the number of vertice
    nbVertices = len(rawMesh.vertices)

    # Delcaring the output egg array
    eggArray = []

    # Appending the number of vertices
    eggArray.append(nbVertices)

    # Appending the vertices
    for v in rawMesh.vertices:
        eggArray.append(numpy.float32(v.co.x))
        eggArray.append(numpy.float32(v.co.y))
        eggArray.append(numpy.float32(v.co.z))


    # Appending the normals
    for v in rawMesh.vertices:
        eggArray.append(numpy.float32(v.normal.x))
        eggArray.append(numpy.float32(v.normal.y))
        eggArray.append(numpy.float32(v.normal.z))


    # Appending the uvs
    for v in rawMesh.vertices:
        eggArray.append(numpy.float32(0.0))
        eggArray.append(numpy.float32(0.0))

    #print(eggArray)

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
            ExportMesh(obj, root_node)
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
