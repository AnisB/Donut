/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/


#ifndef DONUT_MESH
#define DONUT_MESH

#include "graphics/drawable.h"
#include "graphics/geometry.h"
#include "graphics/material.h"
#include "resource/texture.h"

 namespace Donut
 {
	class TMesh : public TDrawable
	{
	public:
	 	// Creating a mesh
		TMesh(TMaterial& _material, TGeometry* _model);
		// Dstructor
	 	virtual ~TMesh();
	 	// Attach a texture to a mesh => should be moved somewhere where it makes sense
	 	virtual void AddTexture(TTexture* _texture, const std::string& _nameInMaterial);
	 	// Drawing a mesh
	 	virtual void Draw(const Matrix4& _modelMatrix, const Matrix4& _viewProjectionMatrix);
		virtual void UpdateCameraData(const Matrix4& _projection, const Matrix4& _view);
 	protected:
 		void Bind();
 		void Unbind();
	protected:
	 	// Model to draw
	 	TMaterial FMaterial;
	 	TGeometry* FGeometry;
	 };
}
 #endif // DONUT_MESH