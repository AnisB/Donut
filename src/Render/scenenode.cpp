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
 #include "scenenode.h"

 #include <Base/Common.h>


namespace Donut
{
	TSceneNode::TSceneNode()
	{

	}

	TSceneNode::~TSceneNode()
	{
		
	}

	void TSceneNode::Draw(const Matrix4& parModelMatrix, Camera* parCamera)
	{	
		foreach(drawable,FDrawables)
		{
			TDrawableObject& drw = (**drawable);
			drw.Bind();
			drw.UpdateInfoShader(parModelMatrix*FModel,parCamera);
			drw.Draw();
			drw.Unbind();
		}

		foreach(son,FSons)
		{
			(*son)->Draw(parModelMatrix*FModel,parCamera);
		}
	}

	void TSceneNode::AddDrawable(TDrawableObject* parDrawable)
	{
		FDrawables.push_back(parDrawable);
	}

}