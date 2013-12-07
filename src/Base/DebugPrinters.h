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



#ifndef DONUT_DEBUG_PRINTER
#define DONUT_DEBUG_PRINTER

#include <iostream>
#include <cstdio>

 namespace Donut
 {

 	// Color list
	#define DEFAULT "\033[0m"
	#define RED "\033[0;31m"
	#define GREEN "\033[0;32m"
	#define ORANGE "\033[0;33m"
	#define BLUE "\033[0;34m"
	#define MAGENTA "\033[0;35m"
	#define CYAN "\033[0;36m"

	// Print terms
	#define PRINT std::cout
	#define END_PRINT DEFAULT<<std::endl


#ifdef DEBUG
#define DEFAULT_DEBUG(Enonce)\
 	{\
 		PRINT<<BLUE<<"[DEFAULT]"<<Enonce<<END_PRINT;\
 	}
#else
#define DEFAULT_DEBUG_NOARGS(Enonce) {}
#endif


// STATE_ENGINE 	
#ifdef DEBUG
#define STATE_ENGINE_DEBUG(Enonce)\
 	{\
 		PRINT<<ORANGE<<"[STATE ENGINE]"<<Enonce<<END_PRINT;\
 	}
#else
#define STATE_ENGINE_DEBUG(Enonce) {}
#endif

// RENDER
#ifdef DEBUG
#define RENDER_DEBUG(Enonce)\
 	{\
 		PRINT<<CYAN<<"[RENDER]"<<Enonce<<END_PRINT;\
 	}
 	#define RENDER_ERR(Enonce)\
 	{\
 		std::cout<<RED<<"[RENDER]"<<Enonce<<END_PRINT<<std::endl;\
 	} 	
#else
#define RENDER_DEBUG(Enonce) {}
 	#define RENDER_ERR(Enonce) {}
#endif

// INPUT
#ifdef DEBUG
#define INPUT_DEBUG(Enonce)\
 	{\
 		PRINT<<GREEN<<"[INPUT]"<<Enonce<<END_PRINT;\
 	}
 	#define INPUT_ERR(Enonce)\
 	{\
 		std::cout<<GREEN<<"[INPUT]"<<Enonce<<END_PRINT<<std::endl;\
 	} 	
#else
#define INPUT_DEBUG(Enonce) {}
 	#define INPUT_ERR(Enonce) {}
#endif

}
#endif