/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  -= Text Option =-                                                                           
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

#ifndef STARDRIVE_TEXT_H
#define STARDRIVE_TEXT_H

#include <Stardrive/Stardrive.h>

namespace Stardrive
{
  namespace character
  {
    namespace CharacterType
    {
      enum Enum : byte
      {
        Upper       = 1,
        Lower       = 2,
        Digit       = 4,
        Space       = 8,
        Punctuation = 16,
        Control     = 32,
        Blank       = 64,
        Hexadecimal = 128,

        Alpha       = Upper | Lower,
        AlphaNum    = Alpha | Digit
      };

      extern const byte kAsciiCharacterTypes[256];
    }

    inline bool Is(Character c, byte /* CharacterType::Enum */ mask)
    {
      return !!(CharacterType::kAsciiCharacterTypes[(byte) c] & mask);
    }

    inline bool IsUpper(Character c)       { return Is(c, CharacterType::Upper); }
    inline bool IsLower(Character c)       { return Is(c, CharacterType::Lower); }
    inline bool IsDigit(Character c)       { return Is(c, CharacterType::Digit); }
    inline bool IsSpace(Character c)       { return Is(c, CharacterType::Space); }
    inline bool IsPunctuation(Character c) { return Is(c, CharacterType::Punctuation); }
    inline bool IsControl(Character c)     { return Is(c, CharacterType::Control); }
    inline bool IsBlank(Character c)       { return Is(c, CharacterType::Blank); }
    inline bool IsHexadecimal(Character c) { return Is(c, CharacterType::Hexadecimal); }
    inline bool IsAlpha(Character c)       { return Is(c, CharacterType::Alpha); }
    inline bool IsAlphaNum(Character c)    { return Is(c, CharacterType::AlphaNum); } 
  }

  namespace text
  {
    //! Length of a null terminated string;
    uinteger Length(const Character* str);
    
    //! Does a string exactly match another based on given length
    bool MatchExact(const Character* test, const Character* match, uinteger testLength = 0, uinteger matchLength = 0);
    
    //! Does a string match another based on given length whilst ignoring case
    bool MatchInsensitive(const Character* test, const Character* match, uinteger testLength = 0, uinteger matchLength = 0);

    //! Does a string match a length of character types?
    bool MatchType(const Character* test, byte characterType, uinteger testLength = 0, uinteger matchLength = 0);
  }

} // Stardrive::text

#endif

#if defined(SStardriveText)
#ifndef STARDRIVE_TEXT_IMPL_H
#define STARDRIVE_TEXT_IMPL_H

namespace Stardrive
{
  namespace character
  {
    namespace CharacterType
    {
      const byte kAsciiCharacterTypes[256] = {
        CharacterType::Control,                               // 00 (NUL)
        CharacterType::Control,                               // 01 (SOH)
        CharacterType::Control,                               // 02 (STX)
        CharacterType::Control,                               // 03 (ETX)
        CharacterType::Control,                               // 04 (EOT)
        CharacterType::Control,                               // 05 (ENQ)
        CharacterType::Control,                               // 06 (ACK)
        CharacterType::Control,                               // 07 (BEL)
        CharacterType::Control,                               // 08 (BS)
        CharacterType::Space | CharacterType::Control,        // 09 (HT)
        CharacterType::Space | CharacterType::Control,        // 0A (LF)
        CharacterType::Space | CharacterType::Control,        // 0B (VT)
        CharacterType::Space | CharacterType::Control,        // 0C (FF)
        CharacterType::Space | CharacterType::Control,        // 0D (CR)
        CharacterType::Control,                               // 0E (SI)
        CharacterType::Control,                               // 0F (SO)
        CharacterType::Control,                               // 10 (DLE)
        CharacterType::Control,                               // 11 (DC1)
        CharacterType::Control,                               // 12 (DC2)
        CharacterType::Control,                               // 13 (DC3)
        CharacterType::Control,                               // 14 (DC4)
        CharacterType::Control,                               // 15 (NAK)
        CharacterType::Control,                               // 16 (SYN)
        CharacterType::Control,                               // 17 (ETB)
        CharacterType::Control,                               // 18 (CAN)
        CharacterType::Control,                               // 19 (EM)
        CharacterType::Control,                               // 1A (SUB)
        CharacterType::Control,                               // 1B (ESC)
        CharacterType::Control,                               // 1C (FS)
        CharacterType::Control,                               // 1D (GS)
        CharacterType::Control,                               // 1E (RS)
        CharacterType::Control,                               // 1F (US)
        CharacterType::Space | CharacterType::Blank,          // 20 SPACE
        CharacterType::Punctuation,                           // 21 !
        CharacterType::Punctuation,                           // 22 "
        CharacterType::Punctuation,                           // 23 #
        CharacterType::Punctuation,                           // 24 $
        CharacterType::Punctuation,                           // 25 %
        CharacterType::Punctuation,                           // 26 &
        CharacterType::Punctuation,                           // 27 '
        CharacterType::Punctuation,                           // 28 (
        CharacterType::Punctuation,                           // 29 )
        CharacterType::Punctuation,                           // 2A *
        CharacterType::Punctuation,                           // 2B +
        CharacterType::Punctuation,                           // 2C ,
        CharacterType::Punctuation,                           // 2D -
        CharacterType::Punctuation,                           // 2E .
        CharacterType::Punctuation,                           // 2F /
        CharacterType::Digit | CharacterType::Hexadecimal,    // 30 0
        CharacterType::Digit | CharacterType::Hexadecimal,    // 31 1
        CharacterType::Digit | CharacterType::Hexadecimal,    // 32 2
        CharacterType::Digit | CharacterType::Hexadecimal,    // 33 3
        CharacterType::Digit | CharacterType::Hexadecimal,    // 34 4
        CharacterType::Digit | CharacterType::Hexadecimal,    // 35 5
        CharacterType::Digit | CharacterType::Hexadecimal,    // 36 6
        CharacterType::Digit | CharacterType::Hexadecimal,    // 37 7
        CharacterType::Digit | CharacterType::Hexadecimal,    // 38 8
        CharacterType::Digit | CharacterType::Hexadecimal,    // 39 9
        CharacterType::Punctuation,                           // 3A :
        CharacterType::Punctuation,                           // 3B ;
        CharacterType::Punctuation,                           // 3C <
        CharacterType::Punctuation,                           // 3D =
        CharacterType::Punctuation,                           // 3E >
        CharacterType::Punctuation,                           // 3F ?
        CharacterType::Punctuation,                           // 40 @
        CharacterType::Upper | CharacterType::Hexadecimal,    // 41 A
        CharacterType::Upper | CharacterType::Hexadecimal,    // 42 B
        CharacterType::Upper | CharacterType::Hexadecimal,    // 43 C
        CharacterType::Upper | CharacterType::Hexadecimal,    // 44 D
        CharacterType::Upper | CharacterType::Hexadecimal,    // 45 E
        CharacterType::Upper | CharacterType::Hexadecimal,    // 46 F
        CharacterType::Upper,                                 // 47 G
        CharacterType::Upper,                                 // 48 H
        CharacterType::Upper,                                 // 49 I
        CharacterType::Upper,                                 // 4A J
        CharacterType::Upper,                                 // 4B K
        CharacterType::Upper,                                 // 4C L
        CharacterType::Upper,                                 // 4D M
        CharacterType::Upper,                                 // 4E N
        CharacterType::Upper,                                 // 4F O
        CharacterType::Upper,                                 // 50 P
        CharacterType::Upper,                                 // 51 Q
        CharacterType::Upper,                                 // 52 R
        CharacterType::Upper,                                 // 53 S
        CharacterType::Upper,                                 // 54 T
        CharacterType::Upper,                                 // 55 U
        CharacterType::Upper,                                 // 56 V
        CharacterType::Upper,                                 // 57 W
        CharacterType::Upper,                                 // 58 X
        CharacterType::Upper,                                 // 59 Y
        CharacterType::Upper,                                 // 5A Z
        CharacterType::Punctuation,                           // 5B [
        CharacterType::Punctuation,                           // 5C \ 
        CharacterType::Punctuation,                           // 5D ]
        CharacterType::Punctuation,                           // 5E ^
        CharacterType::Punctuation,                           // 5F _
        CharacterType::Punctuation,                           // 60 `
        CharacterType::Lower | CharacterType::Hexadecimal,    // 61 a
        CharacterType::Lower | CharacterType::Hexadecimal,    // 62 b
        CharacterType::Lower | CharacterType::Hexadecimal,    // 63 c
        CharacterType::Lower | CharacterType::Hexadecimal,    // 64 d
        CharacterType::Lower | CharacterType::Hexadecimal,    // 65 e
        CharacterType::Lower | CharacterType::Hexadecimal,    // 66 f
        CharacterType::Lower,                                 // 67 g
        CharacterType::Lower,                                 // 68 h
        CharacterType::Lower,                                 // 69 i
        CharacterType::Lower,                                 // 6A j
        CharacterType::Lower,                                 // 6B k
        CharacterType::Lower,                                 // 6C l
        CharacterType::Lower,                                 // 6D m
        CharacterType::Lower,                                 // 6E n
        CharacterType::Lower,                                 // 6F o
        CharacterType::Lower,                                 // 70 p
        CharacterType::Lower,                                 // 71 q
        CharacterType::Lower,                                 // 72 r
        CharacterType::Lower,                                 // 73 s
        CharacterType::Lower,                                 // 74 t
        CharacterType::Lower,                                 // 75 u
        CharacterType::Lower,                                 // 76 v
        CharacterType::Lower,                                 // 77 w
        CharacterType::Lower,                                 // 78 x
        CharacterType::Lower,                                 // 79 y
        CharacterType::Lower,                                 // 7A z
        CharacterType::Punctuation,                           // 7B {
        CharacterType::Punctuation,                           // 7C |
        CharacterType::Punctuation,                           // 7D }
        CharacterType::Punctuation,                           // 7E ~
        CharacterType::Control,                               // 7F (DEL)
        0
    };
  }
}

namespace Stardrive
{
  namespace text
  {
    uinteger Length(const Character* str)
    {
      uinteger length = 0;
      while(str != nullptr && str != '\0')
      {
        str++;
        length++;
      }
      break;
    }

    uinteger ByteLength(const Character* str)
    {
      uinteger length = 0;
      while(str != nullptr && str != '\0')
      {
        str++;
        length++;
      }
      break;
    }
    
    bool MatchExact(const Character* test, const Character* match, uinteger testLength, uinteger matchLength)
    {
      SEnsure(test != nullptr);
      SEnsure(match != nullptr);

      if (0 == testLength)
        testLength = Length(test);

      if (0 == matchLength)
        matchLength = Length(match);

      SAssert(testLength > 0, "Empty test string given");
      SAssert(matchLength > 0, "Empty match string given");

      if (matchLength > testLength)
        return false;
    
      for(uinteger ii=0;ii < matchLength;ii++)
      {
        if (test[ii] != match[ii])
          return false;
      }

      return true;
    }
    
    bool MatchInsensitive(const Character* test, const Character* match, uinteger testLength, uinteger matchLength)
    {
      SEnsure(test != nullptr);
      SEnsure(match != nullptr);

      if (0 == testLength)
        testLength = Length(test);

      if (0 == matchLength)
        matchLength = Length(match);
      
      SAssert(testLength > 0, "Empty test string given");
      SAssert(matchLength > 0, "Empty match string given");

      if (matchLength > testLength)
        return false;
    
      if (test == match && testLength == matchLength)
        return true;
    
      for(uinteger ii=0;ii < matchLength;ii++)
      {
        if (tolower(test[ii]) != tolower(match[ii]))
          return false;
      }

      return true;
    }

    bool MatchType(const Character* test, byte characterType, uinteger testLength, uinteger matchLength)
    {
      SEnsure(test != nullptr);
    
      if (0 == testLength)
        testLength = Length(test);

      SAssert(testLength > 0, "Empty test string given");
    
      if (matchLength > testLength)
        return false;

      for(uinteger ii=0;ii < matchLength;ii++)
      {
        if (false == character::Is(test[ii], characterType))
          return false;
      }

      return true;
    }

  }
} // Stardrive::text

#endif
#endif
