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
#ifndef DONUT_STATE_ENGINE_MANAGER
#define DONUT_STATE_ENGINE_MANAGER


#include <base/singleton.h>
#include "StateEngine.h"
#include "Defines.h"
#include <map>

 namespace Donut 
 {
 	class TStateEngine;
 	class TStateEngineManager : public Singleton<TStateEngineManager>
 	{
 	public:
 		TStateEngineManager();
 		virtual ~TStateEngineManager();

 		TStateEngine * CreateInstance(int parStateId);
 		
 		void RegisterInstance(const TStateEngineId& parId, TStateEngine* parInstance);
 		TStateEngine * GetInstance(const TStateEngineId& parId);

 		void DestroySpecificInstance(int parStateId);
 		void DestroyAllInstances();


 	protected:
 		typedef std::map<TStateEngineId, TStateEngine*> TStateEngineMap;
 		TStateEngineMap FInstances;

 	};
 }
#endif