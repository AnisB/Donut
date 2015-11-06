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

#ifndef SUGAR_GRAPHICS_DONUT
#define SUGAR_GRAPHICS_DONUT

// Library includes
#include "graphics/shader.h"
#include "graphics/material.h"

namespace Donut
{
    struct TSugar
    {
        std::string     name;
        std::string     geometry;
        TMaterial       material;
        
        TSugar( )
        {
        }

        TSugar( const TSugar& _sugar)
        {
            name = _sugar.name;
            geometry = _sugar.geometry;
            material = _sugar.material;
        }
    };
}

#endif // SUGAR_GRAPHICS_DONUT
 