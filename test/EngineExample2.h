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


#ifndef DONUT_ENGINE_EXAMPLE
#define DONUT_ENGINE_EXAMPLE

#include <Engine/Engine.h>
#include <Objects/Square.h>
#include <Objects/Triangle.h>
#include <Objects/Quad.h>



 namespace Donut{
 	class TEngineExample : public Engine
 	{
 	public:
 		TEngineExample();
 		virtual ~TEngineExample();

 		virtual void Update(float dt);

 		virtual void Init();
 		
 		virtual void Loop();

 	protected:
 		TSquare * FSquare;
 		TTriangle * FTriangle;
 		TQuad * FQuad;
 		bool FIsRendering;

 	};
 }
 #endif // DONUT_ENGINE_EXAMPLE