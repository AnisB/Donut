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

#ifndef DONUT_TOPPING_LOADER
#define DONUT_TOPPING_LOADER

// Library includes
#include "recipe/toppingdescriptor.h"

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
            
            // if it is registers it into memory
            void Init();

            // This function searches for a given toppping file and determines either or 
            // not it has been found and returns it if it has.
			TOPPING_GUID FetchMaterial(const STRING_TYPE& _toppingName);

			// Method required by rendering threads
			TMaterial* RequestRuntimeMaterial(TOPPING_GUID _toppingGUID) { return &m_toppings[_toppingGUID].data; }
        protected:
            // Parses the sugar sub_directory
            void LoadToppings();

            // Load the topping into memory if it is not
            void LoadIntoMemory(TToppingDescriptor& _targetTopping);

			// Insert a topping into the local data structures
			TOPPING_GUID InsertTopping(TToppingDescriptor& _targetTopping);

        protected:
			// The root folder that contains all the toppings
            STRING_TYPE m_toppingsFolder;

			// The loaded into memory toppings
			std::map<STRING_TYPE, TOPPING_GUID> m_toppingsIdentifiers;
			std::vector<TToppingDescriptor> m_toppings;
    };
}
#endif // DONUT_TOPPING_LOADER
 