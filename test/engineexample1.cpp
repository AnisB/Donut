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
#include <Render/Defines.h>

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
        delete FNode1;
        delete FNode2;
        FRenderer->UnRegisterToDraw(FCubeR);
        delete FCubeR;   
        FRenderer->UnRegisterToDraw(FTeapot);
        delete FTeapot; 
        delete inManager;  
    }

    void TEngineExample::InitScene()
    {
        FRenderer->SetFragmentShader("shaders/canvas/outVertex.glsl");
        FRenderer->SetFragmentShader("shaders/canvas/outFragment.glsl");

        Donut::TRenderPass* pass= FRenderer->GetPasses()[0];
        Donut::TNode* root= pass->GetRoot();
        Donut::Camera* camera = pass->GetCamera();
        inManager = new Donut::TDefaultInputManager();
        Donut::SetInputManager(inManager);
        inManager->FCamera = camera;
        camera->DefinePerspective(45.0,1280.0/720.0,1.0,500.0);
        FCubeR = new Donut::TCubeR(TVec3(0,0,-5),0.5);
        FTeapot = new Donut::TMesh(TVec3(0,0,0),"Teapot");

        FNode1 = new Donut::TSceneNode();
        FNode2 = new Donut::TSceneNode();
        FNode2->Translate(TVec3(-5,0,-40));
        FCubeR->GenerateShader();
        FCubeR->Init();

        FTeapot->GenerateShader();
        FTeapot->Init();
        FNode1->AddDrawable(FCubeR);
        FNode2->AddDrawable(FTeapot);
        root->AddChild(FNode1);
        root->AddChild(FNode2);
        FRenderer->RegisterToDraw(FCubeR);
        FRenderer->RegisterToDraw(FTeapot);
    }
    void TEngineExample::Update(float dt)
    {
        TEngine::Update(dt);
        inManager->Update();  
        FNode2->Yaw(dt*2);  
    }

    void TEngineExample::Init()
    {
        Donut::TContextDetail newContext;
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