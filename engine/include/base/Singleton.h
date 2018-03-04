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

#pragma once

#include "bento_memory/common.h"

namespace donut
{
  template <typename T>
  class Singleton
  {
  protected:
    Singleton () { }
    ~Singleton () { }

  public:
    // Interface publique
    static T *Instance_Ptr ()
    {
      if (FInstance == nullptr)
      {
        FInstance = make_new<T>(common_allocator());
      }

      return (static_cast<T*> (FInstance));
    }

    static T &Instance ()
    {
      if (FInstance == nullptr)
      {
        FInstance = new T;
      }
      return *(static_cast<T*> (FInstance));
    }

    static void Destroy ()
    {
      if (FInstance != nullptr)
      {
        make_delete<T>(FInstance);
        FInstance = nullptr;
      }
    }

  private:
    // Unique instance
    static T* FInstance;
  };

  template <typename T>
  T* Singleton<T>::FInstance = nullptr;
}