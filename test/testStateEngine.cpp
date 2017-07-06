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

#include <iostream>
#include <StateEngine/StateEngine.h>
#include <StateEngine/StateEngineManager.h>


int main()
{
	donut::TStateEngineManager  & semRef = donut::TStateEngineManager::Instance();

	donut::TStateEngine * engine = semRef.CreateInstance(1);
	donut::TStateEngine * engine2 = semRef.CreateInstance(2);

	donut::TStateEngineManager::Instance().DestroySpecificInstance(1);
	
	donut::TStateEngineManager::Instance().DestroyAllInstances();
}