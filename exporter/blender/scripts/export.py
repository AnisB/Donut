import bpy
import array
import numpy

def ExportMesh(targetMesh):
	print("Exporting mesh: " + targetMesh.name)
	# Fetching the actual geometry
	rawMesh = targetMesh.data

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

	print(eggArray)


def ExportCamera(targetCamera):
	print("Exporting camera: " + targetCamera.name)

def ExportLamp(targetLamp):
	print("Exporting lamp: " + targetLamp.name)


def ExportTargetScene (sceneRef):
    print("Exporting the scene: " + sceneRef.name)
    for obj in sceneRef.objects:
        if (obj.type == "MESH"):
        	ExportMesh(obj)
        elif (obj.type == "CAMERA"):
        	ExportCamera(obj)
        elif (obj.type == "LAMP"):
        	ExportLamp(obj)
        else:
        	print("Object " + object.name + " "+ object.type +" will not be exported")

    
# Fetch the current scene
for scene in bpy.data.scenes:
	ExportTargetScene(scene)