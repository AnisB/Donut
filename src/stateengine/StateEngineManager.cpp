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

#include "StateEngineManager.h"
#include <stateengine/Common.h>

namespace donut
{

  TStateEngineManager::TStateEngineManager()
  {

  }
  TStateEngineManager::~TStateEngineManager()
  {

  }

  void TStateEngineManager::RegisterInstance(const TStateEngineId& parId, TStateEngine* parInstance)
  {
  	FInstances[parId] = parInstance;
#if _DEBUG
  	STATE_ENGINE_DEBUG("Instance registered with id "<<parId.FId);
#endif  
  }

  void TStateEngineManager::DestroySpecificInstance(int parStateId)
  {
    ASSERT(FInstances[TStateEngineId(parStateId)] != NULL);
    delete FInstances[TStateEngineId(parStateId)];
    FInstances.erase(parStateId);
    STATE_ENGINE_DEBUG("The instance with ID "<<parStateId<<" was destroyed");
  }

  void TStateEngineManager::DestroyAllInstances()
  {
  	for(auto& instance : FInstances)
  	{
  		if(instance.second != nullptr)
  		{
  			delete instance.second;
  		}
  	}
  	FInstances.clear();
    STATE_ENGINE_DEBUG("All State Engine Instances where destroyed");
  }

  TStateEngine * TStateEngineManager::CreateInstance(int parStateId)
  {
    TStateEngine * stateEngine = new TStateEngine(parStateId);
    TStateEngineId stateId(parStateId);
    ASSERT(FInstances[stateId] == NULL);
    FInstances[stateId] = stateEngine;
    STATE_ENGINE_DEBUG("Instance registered with id "<<parStateId);
    return stateEngine;
  }
  TStateEngine * TStateEngineManager::GetInstance(const TStateEngineId& parId)
  {
  	TStateEngineMap::iterator it = FInstances.find(parId);
  	if (it != FInstances.end())
  		return it->second;
  	else
  		return NULL;
  }
}