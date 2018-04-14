// Bento includes
#include <bento_base/security.h>

#include "stateengine/StateEngineManager.h"

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
  }

  void TStateEngineManager::DestroySpecificInstance(int parStateId)
  {
    assert(FInstances[TStateEngineId(parStateId)] != NULL);
    delete FInstances[TStateEngineId(parStateId)];
    FInstances.erase(parStateId);
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
  }

  TStateEngine * TStateEngineManager::CreateInstance(int parStateId)
  {
    TStateEngine * stateEngine = new TStateEngine(parStateId);
    TStateEngineId stateId(parStateId);
    assert(FInstances[stateId] == NULL);
    FInstances[stateId] = stateEngine;
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