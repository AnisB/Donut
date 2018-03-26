#pragma once

// Bento includes
#include <bento_base/security.h>

// Engine includes
#include "stateengine/StateEngine.h"
#include "stateengine/Defines.h"
#include <stateengine/Common.h>
#include "stateengine/StateEngineManager.h"

//--------------------------------------------------------------------
// TStateEngine
//--------------------------------------------------------------------
//--------------------------------------------------------------------
namespace donut
{
 	TStateEngine::TStateEngine(int parStateId) : FId (parStateId)
 	{
 	}
 	
 	TStateEngine::~TStateEngine()
 	{
 		for(auto& state : FStates)
 		{
 			assert(state.second);
 			delete state.second;
 		}

 		for(auto& transition : FTransitions)
 		{
 			assert(transition.second);
 			delete transition.second;
 		}
 	}
	
 	void TStateEngine::CreateState(const TStateId& stateID, TStateData * parTStateData, void (* parEnterStateCallBack), void (*parLeaveStateCallBack), void (*parUpdater))
 	{
 		TAtomicState * newState = new TAtomicState(FId, stateID, parTStateData, parEnterStateCallBack, parLeaveStateCallBack , parUpdater);
 		FStates[stateID] = newState;
 	}
 	
 	void TStateEngine::CreateTransition(const TTransitionId& stateID, void (*parEvaluateFunction), void (* parTransitionCallBack), TStateId parEnterState, TStateId parLeaveState)
 	{
 		TTransition * newStransition = new TTransition(FId,stateID, parEvaluateFunction, parTransitionCallBack, parEnterState, parLeaveState );
		FTransitions[stateID] = newStransition;
 	}

 	void TStateEngine::Update(double parDt)
 	{
 		TAtomicState * currentState = FStates[FCurrentState];
 		bool hasChangedState = false;
 		const std::map<TTransitionId, TTransition *> & associatedTransitions = currentState->GetTransitions();

 		for(auto& transition : associatedTransitions)
 		{
 			currentState->TransitionCallBack();
 			if(transition.second->EvaluateTransition())
 			{
 				currentState->Leave();
 				FCurrentState = transition.second->GetNextStateId();
 				TAtomicState * nextState = FStates[FCurrentState];
 				nextState->Enter();
 				hasChangedState= true;
 				break;
 			}
 		}
 		if (hasChangedState)
 			currentState = FStates[FCurrentState];
 		currentState->Update(parDt);
 	}


 	void TStateEngine::ReverseUpdate(double parDt)
 	{
		TAtomicState * currentState = FStates[FCurrentState];
 		currentState->Update(parDt);

 		const std::map<TTransitionId, TTransition *> & associatedTransitions = currentState->GetTransitions();
 		for(auto& transition : associatedTransitions)
 		{
 			currentState->TransitionCallBack();
 			if(transition.second->EvaluateTransition())
 			{
 				currentState->Leave();
 				FCurrentState = transition.second->GetNextStateId();
 				TAtomicState * nextState = FStates[FCurrentState];
 				nextState->Enter();
 				break;
 			}
 		}
 	}


} // End namestate StateEngine