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



#ifndef STATE_ENGINE_DEFINES
#define STATE_ENGINE_DEFINES

#include "base/stringhelper.h"

#include <assert.h>

#include <iostream>

 namespace donut
 {
 	typedef int TStateId; 
 	typedef int TTransitionId;

 	struct TStateEngineId
 	{
 		TStateEngineId(int parId)
 		{
 			FId = parId;
 		}
 		bool operator == (int parId)
 		{
 			return (FId == parId);
 		}
 		bool operator < (int parId) const
 		{
 			return (FId < parId);
 		}
 		bool operator < (const TStateEngineId& parId) const
 		{
 			return (FId < parId.FId);
 		}
 		void operator = (int parId)
 		{
 			FId = parId;
 		}

 		int FId;
	#if _DEBUG
 		STRING_TYPE FDebugStateEngineName;
	#endif
 	};
 }
#endif
