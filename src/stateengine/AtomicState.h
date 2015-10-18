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

#ifndef STATE_ENGINE_ATOMIC_STATE
#define STATE_ENGINE_ATOMIC_STATE

#include "StateData.h"
#include "Defines.h"
#include <list>
#include <map>

 namespace Donut
 {

 	class TTransition;
 	class TAtomicState
 	{
 	public:

 		TAtomicState(TStateEngineId parStateEngineId, TStateId parId, TStateData (* parTStateData), void (* parEnterCallBack), void (* parLeaveCallBack), void (* parUpdater));

 		virtual ~TAtomicState();

 	public:
 		const TStateData * GetTStateData() const { return FStateData; }
 		void* GetEnterCallBack() { return FEnterCallBack; }
 		void* GetLeaveCallBack() { return FLeaveCallBack; }

 		const std::map<TTransitionId, TTransition* > & GetTransitions() { return FOutTransitions; }


 	public:
 		void AddTransition(TTransitionId parId, TTransition * parTransition);

 		void Enter();
 		void Leave();
 		void TransitionCallBack();

 		void Update(double dt);


 	#if _DEBUG
 		void AddInTransition(const TTransition * parTransition);
	#endif

 	private:
 		void (*FEnterCallBack);
 		void (*FLeaveCallBack);
 		TStateData* FStateData;

 		void (*FUpdater);

 		std::map<TTransitionId, TTransition*> FOutTransitions;
 		TStateEngineId FStateEngineId;

 		TStateId FId;

 	#if _DEBUG
 		std::list<TTransition*> FInTransitions;
 	#endif

 	};
 }
#endif