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
  namespace hash
  {
    //! Calculate FNV-1A hash from given null-terminated string.
    u32 fnv1a(const char8* str);

    //! Calculate FNV-1A hash at compile time from the given null-terminated string
    constexpr auto fnv1a_const(const char8* const str, const unsigned value = 0x811c9dc5ull) -> unsigned
    {
      // Implementation from https://notes.underscorediscovery.com/constexpr-fnv1a/
      return (str[0] == '\0') ? value : fnv1a_const(&str[1], 
      static_cast<u32>
      (
        (value ^ u64(str[0])) * 0x1000193ull)
      );
    }

}} // Stardrive::hash

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
