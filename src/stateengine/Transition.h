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

#ifndef STATE_ENGINE_TRANSITION
#define STATE_ENGINE_TRANSITION

 #include "Defines.h"


 namespace Donut
 {
 	class TAtomicState;
 	class TTransition
 	{
 	public:

 		TTransition(const TStateEngineId& parStateEngineId, TTransitionId parId, void (*parEvaluateFunction),  void (*parTransitionCallBack), TStateId parNextState, TStateId parPreviousState);

 		virtual ~TTransition();

 	public:

 		bool EvaluateTransition();
 		const TStateId& GetNextStateId() {return FNextState; }

 	private:
 		void (*FTransitionCondition);
 		TStateId FNextState;
 		TTransitionId FId;

 		TStateEngineId FStateEngineId;


 		#ifdef DEBUG
 		TStateId FOriginState;
 		#endif 


 	};
 }
#endif //STATE_ENGINE_TRANSITION