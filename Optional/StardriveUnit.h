/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  -= Unit Option =-                                                                           
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

#ifndef STARDRIVE_UNIT_H
#define STARDRIVE_UNIT_H

#include <Stardrive/Stardrive.h>
#include <Stardrive/Optional/StardriveContainers.h>


namespace Stardrive
{
  struct Unit
  {
    u32 i;
    inline u32 Index();
    inline u32 Generation();
  };
  
  template<typename T = void>
  struct UnitMap;
  
  template<typename T>
  struct UnitData;

  namespace unit
  {
    Unit Make(u32 index, u32 generation);

    template<typename T>
    inline Unit Obtain(UnitMap<T>& map, const T& value);

    inline Unit Obtain(UnitMap<void>& map);

    template<typename T>
    inline bool Release(UnitMap<T>& map, Unit unit);

    inline bool Release(UnitMap<void>& map, Unit unit);

    template<typename T>
    inline Optional<T> Fetch(UnitMap<T>& map, Unit unit);

    inline void Fetch(UnitMap<void>& map, Unit unit);

    template<typename T>
    inline bool IsAlive(UnitMap<T>& map, Unit unit);
  }
}


namespace Stardrive
{

  inline u32 Unit::Index()      { return i & 0x003fffff;         }
  inline u32 Unit::Generation() { return (i >> 22) & 0x3fc00000; }

  template<typename T>
  struct UnitData
  {
    T  value;
    u8 generation;
  };

  template<>
  struct UnitData<void>
  {
    u8 generation;
  };

  template<typename T = void>
  struct UnitMap
  {
    Array<UnitData<T>>  data;
    Array<u32>          free;
    UnitMap();
    UnitMap(const UnitMap& other);
    UnitMap(UnitMap&& other);
    ~UnitMap();

    UnitMap<T>& operator=(const UnitMap& other);
    UnitMap<T>& operator=(UnitMap&& other);
  };

  namespace unit
  {
    inline Unit Make(u32 index, u32 generation)
    {
      Unit u;
      u.i = index | ((generation & 0xFF) << 22);
      return u;
    }
    
    template<typename T>
    inline Unit Obtain(UnitMap<T>& map, const T& value)
    {
      u32 index;
      if (array::Any(map.free))
      {
        index = array::Pop(map.free);
      }
      else
      {
        index = array::Size(map.data);
        array::Expand(map.data);
      }

      map.data[index].value = value;
      return Make(index, map.data[index].generation);
    }

    inline Unit Obtain(UnitMap<void>& map)
    {
      u32 index;
      if (array::Any(map.free))
      {
        index = array::Pop(map.free);
      }
      else
      {
        index = array::Size(map.data);
        array::Expand(map.data);
      }

      return Make(index, map.data[index].generation);
    }

    template<typename T>
    inline bool Release(UnitMap<T>& map, Unit unit)
    {

      if (IsAlive(map, unit))
      {
        u32 index = unit.Index();
        memory::DestructItems(&map.data[index].value, 1);
        ++map.data[index].generation;
        array::Push(map.free, index);
        return true;
      }

      return false;
    }

    inline bool Release(UnitMap<void>& map, Unit unit)
    {
      if (IsAlive(map, unit))
      {
        u32 index = unit.Index();
        ++map.data[index].generation;
        array::Push(map.free, index);
        return true;
      }

      return false;
    }

    template<typename T>
    inline Optional<T> Fetch(UnitMap<T>& map, Unit unit)
    {
      if (IsAlive(map, unit))
      {
        return Optional<T>::True(map.data[unit.Index()].value);
      }

      return Optional<T>::False();
    }

    inline void Fetch(UnitMap<void>& map, Unit unit) {}

    template<typename T>
    inline bool IsAlive(UnitMap<T>& map, Unit unit)
    {
      const u32 index = unit.Index();
      return index < array::Size(map.data) && map.data[index].generation == unit.Generation();
    }

  }

}

#endif
