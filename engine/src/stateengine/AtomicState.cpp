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

#include "stateengine/AtomicState.h"
#include "stateengine/Defines.h"
//--------------------------------------------------------------------
// TAtomicState
//--------------------------------------------------------------------
//--------------------------------------------------------------------


namespace donut
{
	typedef void (*TUpdaterFunction)(const TStateEngineId&, double);
	typedef void (*TStateCallBack)(const TStateEngineId&, TStateData *);
	//--------------------------------------------------------------------
 	TAtomicState::TAtomicState(TStateEngineId parStateEngineId, TStateId parId, TStateData (* parTStateData), void (* parEnterCallBack), void (* parLeaveCallBack), void (* parUpdater))
 	: FStateEngineId (parStateEngineId)
 	{
 		FEnterCallBack = parEnterCallBack;
 		
 		FLeaveCallBack = parLeaveCallBack;

 		FStateData = parTStateData;

 		FUpdater = parUpdater;

 		FId = parId;
 	}

 	TAtomicState::~TAtomicState()
 	{
 		// assert_msg_NO_RELEASE(FStateData!=NULL, "The state data has been already deleted. you do not need to.")
 		delete FStateData;
 	}

	void TAtomicState::AddTransition(TTransitionId parId, TTransition * parTransition)
 	{
 		FOutTransitions[parId] = parTransition;
 	}

 	#if _DEBUG
 	void TAtomicState::AddInTransition(const TTransition * parTransition)
 	{
 		// FInTransitions.push_back(parTransition)
 	}
	#endif


	void TAtomicState::Update(double parDt)
	{
		void (*updater)( const TStateEngineId&, double) = *((TUpdaterFunction*) (&FUpdater));
		updater(FStateEngineId , parDt);
	}

	void TAtomicState::Enter()
	{
		void (*enter)(const TStateEngineId&, TStateData *) = *((TStateCallBack*) (&FEnterCallBack));
		enter(FStateEngineId, FStateData);

	}

	void TAtomicState::Leave()
	{
		void (*leave)(const TStateEngineId&, TStateData *) = *((TStateCallBack*) (&FLeaveCallBack));
		leave(FStateEngineId, FStateData);
	}

	void TAtomicState::TransitionCallBack()
	{

	}


} // End namestate StateEngine