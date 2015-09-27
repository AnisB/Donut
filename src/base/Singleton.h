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

#ifndef DONUT_BASE_SINGLETON
#define DONUT_BASE_SINGLETON

#include <iostream>
 namespace Donut
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
      if (FInstance == NULL)
      {
        FInstance = new T;
      }

      return (static_cast<T*> (FInstance));
    }
    static T &Instance ()
    {
      if (NULL == FInstance)
      {
        FInstance = new T;
      }

      return *(static_cast<T*> (FInstance));
    }

    static void Destroy ()
    {
      if (NULL != FInstance)
      {
        delete FInstance;
        FInstance = NULL;
      }
    }

  private:
  // Unique instance
    static T *FInstance;
  };

template <typename T>
  T *Singleton<T>::FInstance = NULL;
}

#endif // DONUT_BASE_SINGLETON