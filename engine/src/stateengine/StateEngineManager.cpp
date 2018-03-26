// Bento includes
#include <bento_base/security.h>

#include "stateengine/StateEngineManager.h"
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
    assert(FInstances[TStateEngineId(parStateId)] != NULL);
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
    assert(FInstances[stateId] == NULL);
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