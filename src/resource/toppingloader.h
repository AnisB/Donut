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
#include "base/common.h"
#include "recipe/toppingdescriptor.h"

// External includes
#include <vector>
#include <map>

namespace Donut
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
            const TToppingDescriptor& FetchTopping(const std::string& _toppingName);
        protected:
            // Parses the sugar sub_directory
            void LoadToppings();

        protected:
            std::string m_toppingsFolder;
            std::map<std::string, TToppingDescriptor> m_toppings;
    };
}
#endif // DONUT_TOPPING_LOADER
 