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

//DEFAULT
#ifdef DEBUG
#define DEFAULT_DEBUG(Enonce,...)\
 	{\
 		std::string msg = "[DEFAULT]";\
 		msg += Enonce;\
 		msg += "\n";\
		fprintf(stderr, msg.c_str(),##__VA_ARGS__);\
 	}
#else
#define DEFAULT_DEBUG(Enonce,...) {}
#endif


#ifdef DEBUG
#define DEFAULT_DEBUG_NOARGS(Enonce)\
 	{\
 		std::string msg = "[DEFAULT]";\
 		msg += Enonce;\
 		msg += "\n";\
		fprintf(stderr,"%s", msg.c_str());\
 	}
#else
#define DEFAULT_DEBUG_NOARGS(Enonce,...) {}
#endif




// STATE_ENGINE 	
#ifdef DEBUG
#define STATE_ENGINE_DEBUG(Enonce,...)\
 	{\
 		std::string msg = "[STATE ENGINE]";\
 		msg += Enonce;\
 		msg += "\n";\
		fprintf(stderr, msg.c_str(),##__VA_ARGS__);\
 	}
#else
#define STATE_ENGINE_DEBUG(Enonce,...) {}
#endif


#ifdef DEBUG
#define STATE_ENGINE_DEBUG_NOARGS(Enonce)\
 	{\
 		std::string msg = "[STATE ENGINE]";\
 		msg += Enonce;\
 		msg += "\n";\
		fprintf(stderr,"%s", msg.c_str());\
 	}
#else
#define STATE_ENGINE_DEBUG_NOARGS(Enonce,...) {}
#endif



// RENDER
#ifdef DEBUG
#define RENDER_DEBUG(Enonce,...)\
 	{\
 		std::string msg = "[RENDER]";\
 		msg += Enonce;\
 		msg += "\n";\
		fprintf(stderr, msg.c_str(),##__VA_ARGS__);\
 	}
#else
#define RENDER_DEBUG(Enonce,...) {}
#endif


#ifdef DEBUG
#define RENDER_DEBUG_NOARGS(Enonce)\
 	{\
 		std::string msg = "[RENDER]";\
 		msg += Enonce;\
 		msg += "\n";\
		fprintf(stderr,"%s", msg.c_str());\
 	}
#else
#define RENDER_DEBUG_NOARGS(Enonce,...) {}
#endif
}
#endif