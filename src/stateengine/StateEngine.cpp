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

#include "StateEngine.h"

#include "Defines.h"
#include <stateengine/Common.h>
#include "StateEngineManager.h"

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
 			ASSERT_NO_RELEASE(state.second);
 			delete state.second;
 		}

 		for(auto& transition : FTransitions)
 		{
 			ASSERT_NO_RELEASE(transition.second);
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