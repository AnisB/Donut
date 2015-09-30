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

#ifndef DONUT_BASE_MACRO
#define DONUT_BASE_MACRO

namespace Donut
{
#ifdef __posix__
	#define foreach_macro(IT, X) for ( typeof( X.begin() ) IT = X.begin(); IT != X.end(); ++IT )
	#define tryget(IT, LIST, ELEM) typeof( LIST.begin()) IT = LIST.find(ELEM);
#elif WIN32
	#define foreach_macro(IT, X) for ( auto IT = X.begin(); IT != X.end(); ++IT )
	#define tryget(IT, LIST, ELEM) auto IT = LIST.find(ELEM);
#endif

	#define PACK_DATA(VAL,MAXVAL) (VAL/MAXVAL+0.5)
	#define UNPACK_DATA(VAL,MAXVAL) ((VAL-0.5)*MAXVAL)
}

#endif // DONUT_BASE_MACRO