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

#ifndef DONUT_MULTI_THREAD_USUAL_OBJECTS
#define DONUT_MULTI_THREAD_USUAL_OBJECTS

#include "ThreadSharedObject.h"
#include "Defines.h"

#include "Base/DebugPrinters.h"



namespace Donut 
{

	#define DECLARE_USUAL_THREAD_SAFE_OBJECT(CLASSNAME, TYPE, DEFAULTVALUE) \
	class CLASSNAME : public TThreadSharedObject\
	{\
	\
	public:\
		CLASSNAME(TYPE parInitVal): FValue(parInitVal)\
		{\
			TThreadSharedObject();\
		}\
		TYPE GetValue()\
		{\
			TYPE value = DEFAULTVALUE;\
			CRITICAL_SECTION_BEGIN();\
			value = FValue;\
			CRITICAL_SECTION_END();\
			return value;\
		}\
		void SetValue(TYPE Val)\
		{\
			CRITICAL_SECTION_BEGIN();\
			FValue = Val;\
			CRITICAL_SECTION_END();\
		}\
	protected:\
		TYPE FValue;\
	};



	DECLARE_USUAL_THREAD_SAFE_OBJECT(TThreadSafeBolean, bool, false)
	DECLARE_USUAL_THREAD_SAFE_OBJECT(TThreadSafeInteger, int, 0)
	DECLARE_USUAL_THREAD_SAFE_OBJECT(TThreadSafeString, std::string, "INVALID")


}
#endif // DONUT_MULTI_THREAD_USUAL_OBJECTS
