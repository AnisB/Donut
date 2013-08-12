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



#ifndef DONUT_MULTI_THREAD
#define DONUT_MULTI_THREAD

#define CRITICAL_SECTION_BEGIN() this->Lock();
#define CRITICAL_SECTION_END() this->UnLock();


#define CRITICAL_SECTION_OBJ_BEGIN(OBJ) OBJ.Lock();
#define CRITICAL_SECTION_OBJ_END(OBJ) OBJ.UnLock();

#define CRITICAL_SECTION_PTR_BEGIN(OBJ) ptr->Lock();
#define CRITICAL_SECTION_PTR_END(OBJ) ptr->UnLock();

#endif
