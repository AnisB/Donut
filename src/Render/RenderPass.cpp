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

#include "RenderPass.h"

#include "Base/Common.h"
 namespace Donut
 {

 	//CLASS IMPLEMENTATION
	TRenderPass::TRenderPass()
	{

	}
	TRenderPass::~TRenderPass()
	{
		FDrawables.clear();
	}

	void TRenderPass::Draw()
	{
		foreach(drawable,FDrawables)
		{
			(*drawable)->Draw();
		}
	}

	void TRenderPass::AddDrawable(TDrawableObject* parDrawable)
	{
		FDrawables.push_back(parDrawable);
	}

	void TRenderPass::Clear()
	{
		FDrawables.clear();
	}
	// END CLASS IMPLEMENTATION


 }
