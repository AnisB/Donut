# Donut

## Description
A sandbox 3D rendering engine. I use it to build and test rendering and architecture ideas. It has been alive for a while now (couple years) and I try to contribute to it when I have some free time. 

I have no ambitions to sell or ship games with it, it is simply my toy.

## Features
Here is the (non-exhaustive) list of features that I developped or am planning to add to it:

- 	Use bento (library that provides a set of development basis: allocators, collections, serialization, scalar and SIMD math library)
-	Define assets and versioning (~~DONE~~)
-	Asset compilation, serialization and access to an asset database (~~DONE~~)
- 	Write a backend around opengl (~~DONE~~)
-	Scriptable rendering pipeline (~~DONE~~)
- 	Support various texture formats (PNG, BMP, JPG, TGA) (~~DONE~~)
- 	Support the wavefront formats	(WAVEFRONT)  (~~DONE~~)
- 	Implement various postfxs (DOF: ~~DONE~~, SSR: ~~DONE~~, SSAO: ~~DONE~~)
- 	Frustrum Culling (~~DONE~~)
- 	Implement a Render Request feature so that the update and render thread are independent (~~DONE~~)
-	Various Skybox Formats (~~DONE~~/to be finished)
-	Blender scene exporter (~~DONE~~/to be finished)
-	UV unwrapinng (*TBD*)
-	PBR rendering pipeline (*TBD*)
- 	Lightmap baking (*TBD*)
- 	Write a backend around vulakn (*TBD*)
- 	AO baking (*TBD*)
-	Reflection probe baking (*TBD*)
-	Instance batching (*TBD*)
-	Supporting Android and opengles (*TBD*)
-	Integrating NYX for occlusion culling (an other project that handles cross-platform occlusion culling)(*TBD*)
-	Atlasing (*TBD*)
-	Support the FBX format (*TBD*)
-	Implement a spacial antialiasing post effect (*TBD*)

## Compilation:

Compile the engine and the various programs for windows and vc14 and vc15:

```
ruby make.rb
```

## Naming
Given that the engine is named donut, all the base components are ingredients of a donut:
-	**Egg**: The compiled version of the geometries
-	**Flour**: Levels
-	**Topping**: The compiled version of a material resource
-	**Sugar**: A set of renderables with their geometries and their matching materials.

For the moment I removed Linux and MacOSX support, but I plan to add them back.

## Usage
Two programs are available:

- Asset Compiler: A program that takes a source directory and will output an asset_database that holds the all serialized assets and allows us to instanciate the assets and the levels in game later when needed.
- Flour Loader: A program that will either run an asset compilation and then load a given level or load the level from a pre-compiled asset_database.

## Content
Given that I do not have Max License, I only support scenes from Blender. The export script is in *exporter/blender*

I removed all the images and samples that were in the documentation, they were outdated.

I'll soon post some pictures to illustrate what it does.