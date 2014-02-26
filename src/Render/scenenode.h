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

#ifndef DONUT_SCENE_NODE
#define DONUT_SCENE_NODE


#include "Node.h"

#include <Render/DrawableObject.h>

#include <list>

namespace Donut
{
	class TSceneNode : public TNode
	{
	public:
		// Consrtuctor
		TSceneNode();
		//Destructor
		~TSceneNode();
		// Adds a child to the tree
		virtual void Draw(const Matrix4& parModelMatrix, Camera* parCamera);

		virtual void AddDrawable(TDrawableObject* parDrawable);

	protected:
		std::list<TDrawableObject*> FDrawables;
	};
}
#endif //DONUT_SCENE_NODE