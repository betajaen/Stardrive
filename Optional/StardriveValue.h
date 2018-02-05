/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  -= Hash Option =-                                                                           
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

#ifndef STARDRIVE_HASH_H
#define STARDRIVE_HASH_H

#include <Stardrive/Stardrive.h>

namespace Stardrive
{
  namespace ValueType
  {
    enum Enum : u8
    {
      Boolean,
      Number,
      String,
      Null
    };
  }

  template<uinteger MaxStringSize = 15>
  struct Value<>
  {
    union
    {
      bool  booleanValue;
      f64   numberValue;
      char  string[MaxStringSize + 1];
    };
    ValueType::Enum type;
  };

  namespace value
  {
    template<typename T, uinteger MaxStringSize>
    struct CastTo {};

    template<uinteger MaxStringSize> struct CastTo<bool>
    {
      static bool Cast(const Value<MaxStringSize>& val)
      {
        switch(val.type)
        {
          case ValueType::Null:
            return false;
          case ValueType::Boolean:
            return val.booleanValue;
          case ValueType::Number:
            return val.numberValue != 0.0;
          case ValueType::String:
            return ...;
        }
      }
    };
  }
}

template<typename T, Stardrive::uinteger MaxStringSize>
T value_cast(const ::Stardrive::Value<MaxStringSize>& value)
{
  return Stardrive::value::CastTo<T, MaxStringSize>::Cast(value);
};

#endif

#ifdef SStardriveHash

namespace Stardrive
{
namespace hash
{
  u32 fnv1a(const char8* str)
  {
    // Implementation from https://notes.underscorediscovery.com/constexpr-fnv1a/
    u32 hash  = 0x811c9dc5;
    u32 prime = 0x1000193;
      
    if (nullptr == str)
      return hash;
    
    while(*str != '\0')
    {
        u8 value = *str;
        hash = hash ^ value;
        hash *= prime;
        str++;
    }
    
    return hash;
  }
}} // Stardrive::hash

#endif
