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
#include <Base/Common.h>
namespace Donut
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
#ifdef DEBUG
  	STATE_ENGINE_DEBUG("Instance registered with id %u",parId.FId);
#endif  
  }

  void TStateEngineManager::DestroySpecificInstance(int parStateId)
  {
    AssertRelease(FInstances[TStateEngineId(parStateId)] != NULL);
    delete FInstances[TStateEngineId(parStateId)];
    FInstances.erase(parStateId);
    STATE_ENGINE_DEBUG("The instance with ID %u was destroyed", parStateId);
  }

  void TStateEngineManager::DestroyAllInstances()
  {
  	foreach(instance, FInstances)
  	{
  		if(instance->second !=NULL)
  		{
  			TStateEngine * tmp = instance->second;
  			delete tmp;
  		}
  	}
  	FInstances.clear();
    STATE_ENGINE_DEBUG_NOARGS("All State Engine Instances where destroyed");

  }

  TStateEngine * TStateEngineManager::CreateInstance(int parStateId)
  {
    Donut::TStateEngine * stateEngine = new Donut::TStateEngine(parStateId);
    TStateEngineId stateId(parStateId);
    AssertRelease(FInstances[stateId] == NULL);
    FInstances[stateId] = stateEngine;
    STATE_ENGINE_DEBUG("Instance registered with id %u",parStateId);
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