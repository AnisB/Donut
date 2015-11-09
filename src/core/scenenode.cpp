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

 #include "Base/Common.h"
 #include "Base/Macro.h"


namespace Donut
{
	TSceneNode::TSceneNode()
	{

	}

	TSceneNode::~TSceneNode()
	{
		
	}

	void TSceneNode::Draw(std::map<std::string, TUniformHandler>& _values, const TBufferOutput& _previousData)
	{	
		Matrix4& parentModel = _values["model"].GetValue<Matrix4>();
		Matrix4 save = parentModel;
		parentModel = parentModel * FModel;
		foreach_macro(drawable,FDrawables)
		{
			(*drawable)->Draw(_values, _previousData);
		}
		parentModel = save;
		TNode::Draw(_values, _previousData);
	}

	void TSceneNode::AddDrawable(TDrawable* parDrawable)
	{
		FDrawables.push_back(parDrawable);
	}
}