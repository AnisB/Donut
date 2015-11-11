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
// Includes
// ----------------------------------------
#include "EngineExample1.h"

#include <Input/InputHelper.h>

#include <resource/sugarloader.h>

#include <Render/Renderer.h>

// ----------------------------------------
// Implementation
// ----------------------------------------

namespace Donut
{
    TEngineExample::TEngineExample() 
    : TEngine()
    {
        Donut::TSugarLoader::Instance().Init("data");
    }
     
    TEngineExample::~TEngineExample()
    {
       // delete FNode1;
        delete inManager;  
    }

    void TEngineExample::InitScene()
    {

    }
    void TEngineExample::Update(float dt)
    {
        TEngine::Update(dt);
        inManager->Update();  
        //FNode2->Yaw(dt*2);  
    }

    void TEngineExample::Init()
    {
        Donut::TGraphicsSettings newContext;
        newContext.windowName = "Engine example 1";
        newContext.width = 1280;
        newContext.lenght = 720;
        newContext.major = 4;
        newContext.minor = 1;
        LaunchRendering(newContext);
        FIsRendering = true;
    }

    void TEngineExample::Loop()
    {
        while(FIsRendering && FRenderer->IsRendering())
        {
          Update(0.016f);
          GENERIC_SLEEP(16); // A corriger
        }
    }
 }