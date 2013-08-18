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

#include "Defines.h"


// ----------------------------------------
//  Implementation
// ----------------------------------------

 namespace Donut
 {
 	TEngineExample::TEngineExample() : Engine()
 	{
 		DEFAULT_DEBUG_NOARGS("Creating engine");
 		FSquare = new TSquare(float2(-1,-1), 0.2);
 		FSquare->GetRepresentation()->SetColor(TColorFilter(1.0f,0.0f,0.0f,1.0f));
 		REGISTER_DRAWABLE_PTR(FSquare);
 	}
 	
 	TEngineExample::~TEngineExample()
 	{	
 		UNREGISTER_DRAWABLE_PTR(FSquare);
 		delete FSquare;
 	}

 	void TEngineExample::Update(float dt)
 	{
 		FSquare->SetPosition(FSquare->GetPosition().x +dt *1.f,FSquare->GetPosition().y + dt*1.f);
 		if(FSquare->GetPosition().x > 1.0f || FSquare->GetPosition().y > 1.0f)
 		{
 			FIsRendering = false;
 		}
 	}

	void TEngineExample::Init()
	{
		LaunchRendering();
		FIsRendering = true;
	}

	void TEngineExample::Loop()
	{
		while(FIsRendering) // 3 seconds
		{
			Update(0.016f);
			usleep(16000); // A corriger
		}
	}
 }
