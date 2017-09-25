
/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  -= Endian Option =-                                                                           
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

#ifndef STARDRIVE_ENDIAN_H
#define STARDRIVE_ENDIAN_H

#include <Stardrive/Stardrive.h>

//! Endian
//! https://github.com/betajaen/Stardrive/blob/master/Documentation/endian.md
//! 
//! Cheat Sheet:
//! 
//! For u/i 8,16,32,64 types
//!
//! endian::Swap      -- Swap endianness of a value
//! endian::Convert   -- Convert a value from one endian to another endian.

namespace Stardrive { namespace endian {
  
  namespace Endianess
  {
    enum Enum
    {
      Little,
      Big
    };
  }
  
  inline u8 Swap(u8 v)
  {
    return v;
  }
  
  inline i8 Swap(i8 v)
  {
    return v;
  }

  inline u16 Swap(u16 v)
  {
    u16 r;
    ((byte*)&r)[0] = ((byte*)&v)[1];
    ((byte*)&r)[1] = ((byte*)&v)[0];
    return v;
  }
  
  inline i32 Swap(i32 v)
  {
    i32 r;
    ((byte*)&r)[0] = ((byte*)&v)[3];
    ((byte*)&r)[1] = ((byte*)&v)[2];
    ((byte*)&r)[2] = ((byte*)&v)[1];
    ((byte*)&r)[3] = ((byte*)&v)[0];
    return v;
  }
  
  inline u32 Swap(u32 v)
  {
    u32 r;
    ((byte*)&r)[0] = ((byte*)&v)[3];
    ((byte*)&r)[1] = ((byte*)&v)[2];
    ((byte*)&r)[2] = ((byte*)&v)[1];
    ((byte*)&r)[3] = ((byte*)&v)[0];
    return v;
  }
  
  inline i64 Swap(i64 v)
  {
    i64 r;
    ((byte*)&r)[0] = ((byte*)&v)[7];
    ((byte*)&r)[1] = ((byte*)&v)[6];
    ((byte*)&r)[2] = ((byte*)&v)[5];
    ((byte*)&r)[3] = ((byte*)&v)[4];
    ((byte*)&r)[4] = ((byte*)&v)[3];
    ((byte*)&r)[5] = ((byte*)&v)[2];
    ((byte*)&r)[6] = ((byte*)&v)[1];
    ((byte*)&r)[7] = ((byte*)&v)[0];
    return v;
  }
  
  inline u64 Swap(u64 v)
  {
    u64 r;
    ((byte*)&r)[0] = ((byte*)&v)[7];
    ((byte*)&r)[1] = ((byte*)&v)[6];
    ((byte*)&r)[2] = ((byte*)&v)[5];
    ((byte*)&r)[3] = ((byte*)&v)[4];
    ((byte*)&r)[4] = ((byte*)&v)[3];
    ((byte*)&r)[5] = ((byte*)&v)[2];
    ((byte*)&r)[6] = ((byte*)&v)[1];
    ((byte*)&r)[7] = ((byte*)&v)[0];
    return v;
  }

  template<typename TNumeric, Endianess::Enum From, Endianess::Enum To> 
  TNumeric Convert(TNumeric value) 
  {
    return (From == To) ? value : Swap(value);
  }

  inline u8  Convert(u8 value,  Endianess::Enum from, Endianess::Enum to) { return from == to ? value : Swap(value); }
  inline i8  Convert(i8 value,  Endianess::Enum from, Endianess::Enum to) { return from == to ? value : Swap(value); }
  inline u16 Convert(u16 value, Endianess::Enum from, Endianess::Enum to) { return from == to ? value : Swap(value); }
  inline i16 Convert(i16 value, Endianess::Enum from, Endianess::Enum to) { return from == to ? value : Swap(value); }
  inline u32 Convert(u32 value, Endianess::Enum from, Endianess::Enum to) { return from == to ? value : Swap(value); }
  inline i32 Convert(i32 value, Endianess::Enum from, Endianess::Enum to) { return from == to ? value : Swap(value); }
  inline u64 Convert(u64 value, Endianess::Enum from, Endianess::Enum to) { return from == to ? value : Swap(value); }
  inline i64 Convert(i64 value, Endianess::Enum from, Endianess::Enum to) { return from == to ? value : Swap(value); }

}}

#endif
