#pragma once

// Library includes
#include "recipe/topping_descriptor.h"
#include "base/Singleton.h"

// External includes
#include <vector>
#include <map>

namespace donut
{
    // Class that manages the rendering pipelines
    class TToppingLoader : public Singleton<TToppingLoader>
    {
        public:
            //Base
            TToppingLoader();
            ~TToppingLoader();
            
            void Init();
			const TToppingDescriptor& request_topping(const char* topping_name) { return m_toppings[topping_name]; }

        protected:
            // Parses the sugar sub_directory
            void LoadToppings();

        protected:
			// The root folder that contains all the toppings
			std::string m_toppingsFolder;

			// The loaded into memory toppings
			std::map<std::string, TToppingDescriptor> m_toppings;
    };
}