/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  -= File Option =-                                                                           
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

#ifndef STARDRIVE_STRING_H
#define STARDRIVE_STRING_H

#include <Stardrive/Stardrive.h>

namespace Stardrive
{
  typedef DynamicStore<Character, 16> StringData;
  
  struct String
  {
    mutable StringData text;

    String();
    String(const String& s);
    String(String&& s);
    String(const Character* str, uinteger strLength = 0);
    ~String();
    
    String& operator=(const String& s);
    String& operator=(String&& s);

    Character32& operator[](uinteger idx);
    const Character32& operator[](uinteger idx) const;
  };

  namespace string
  {
    SFunctionDoc(Text="String equals in exact text content to another string")
    bool Equals(const String& lhs, const String& rhs);
    
    SFunctionDoc(Text="Is the string empty in length")
    bool IsEmpty(const String& str);
    
    SFunctionDoc(Text="Is the string empty in length or consists of whitespace characters?")
    bool IsEmptyOrWhitespace(const String& str);

    SFunctionDoc(Text="Length of String")
    uinteger Length(const String& str);
    
    SFunctionDoc(Text="Create a new string to the equivalent of sprintf")
    String   Format(const Character* format, ...);
    
    SFunctionDoc(Text="Set the text of the given string to the equivalent of sprintf")
    String&  Format(String& str, const Character* format, ...);
    
    SFunctionDoc(Text="Append to the text of the given string to the equivalent of sprintf")
    String&  AppendFormat(String& str, const Character* format, ...);
    
    SFunctionDoc(Text="Set the text of the given string to the given text. Text length is given as how many characters to append, or 0 to use all.")
    String&  Text(String& str, const Character* text, uinteger textLength = 0);
    
    SFunctionDoc(Text="Append to the text of the given string the given text. Text length is given as how many characters to append, or 0 to use all.")
    String&  AppendText(String& str, const Character* text, uinteger textLength = 0);

    SFunctionDoc(Text="Get a null-terminated c-style string");
    const Character* CString(const String& str);
    
    SFunctionDoc(Text="Get a Pascal string where the first two bytes are the length (system endian) and the following bytes are the characters");
    const byte*  PascalString(const String& str);
  }

} // Stardrive::file

#endif
