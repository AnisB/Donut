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

#ifndef DONUT_SUGAR_LOADER
#define DONUT_SUGAR_LOADER

#include "base/singleton.h"
#include "graphics/uniformhandler.h"
#include "recipe/sugar_descriptor.h"

#include <list>
#include <map>

namespace donut
{
    class TSugarLoader : public Singleton<TSugarLoader>
    {
        public:
            //Base
            TSugarLoader();
            ~TSugarLoader();
            
            // Parse the project and search for sugar files
            void Init();

            // This function searches for a given sugar file and determines either or 
            // not it has been found and returns it if it has.
            const TSugarDescriptor& FetchSugar(const STRING_TYPE& parModel);
        protected:
            // Parses the sugar sub_directory
            void LoadSugars();
        protected:
            std::map<STRING_TYPE, TSugarDescriptor> FSugars;
    };
}
#endif // DONUT_SUGAR_LOADER
 