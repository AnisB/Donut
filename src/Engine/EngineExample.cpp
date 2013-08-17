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

// ----------------------------------------
//  Includes
// ----------------------------------------

#include "EngineExample.h"

// ----------------------------------------
//  Implementation
// ----------------------------------------

 namespace Donut
 {
 	TEngineExample::TEngineExample() : Engine()
 	{
 		FSquare = new TSquare(float2(-1,-1), 0.2);
 		FSquare->SetColor(TColorFilter(1.0f,0.0f,0.0f,1.0f));
 	}
 	
 	TEngineExample::~TEngineExample()
 	{	
 	}

 	void TEngineExample::PrepareNextFrame()
 	{
 		Flush();
 		DrawObject(FSquare);
 	}

 	void TEngineExample::Update(float dt)
 	{
 		FSquare->SetPosition(FSquare->GetPosition().x +dt *1.f,FSquare->GetPosition().y + dt*1.f);
 	}

	void TEngineExample::Init()
	{
		LaunchRendering();
	}

	void TEngineExample::Loop(float parNbSec)
	{
		size_t counter = 0; 
		while(counter < (parNbSec*60)) // 3 seconds
		{
			Update(0.016f);
			PrepareNextFrame();
			usleep(16000); // A corriger
			counter++;
		}
	}

 }
