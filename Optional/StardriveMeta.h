/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  -= Meta Option =-                                                                           
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

#ifndef STARDRIVE_META_H
#define STARDRIVE_META_H

#include <Stardrive/Stardrive.h>

//! Define before including or change here; the maximum variadic arguments you expect to use.
//! Options are 8, 16, 24 or 32
//! Note: Larger values may increase compile time.
#ifndef SMetaMaximumArguments
#define SMetaMaximumArguments 16
#endif


//! Converts a given argument to a string literal
//! > const char* k = SToString("Hello");
#define SToString(_1) S_Meta_ToString(_1)
#if 0
  // Example
  const char* k = S_Meta_ToString(Hello);
  // Resolves to:
  const char* k = "Hello";
#endif

//! Get the type of member variable of a class
//! > SFieldType(Vector3f, x) x = v.x;
#define SFieldType(CLASS, NAME) decltype(CLASS::NAME)
#if 0
  struct Vector3f
  {
    f32 x, y, z;
  };
  void Main()
  {
    Vector3f v = { 1.0f, 2.0f, 3.0f };
    SFieldType(Vector3f, x) x = v.x;
  }
#endif


//! Count the number of arguments in a variadic macro
//! > int count = SMetaNumArgs(float, int char);
#define SMetaNumArgs S_MetaNumArgs
#if 0
  // Example:
  void GetCount()
  {
    int count = SMetaNumArgs(float, int, char);   // 3
    int count2 = SMetaNumArgs(1, 2, 4, 8);        // 4
  }
#endif

//! For each arguments in variadic macro pass that argument to a given macro
//! > #define MAKE_FUNCTION(NAME) NAME Make_##NAME();
//! > SMetaForeach(MAKE_FUNCTION, float, int, char)
#define SMetaForeach(FN, ...)     S_MetaForeachImpl(FN, __VA_ARGS__)
#if 0
  // Example:
  #define MAKE_FUNCTION(NAME) NAME Make_##NAME();
  SMetaForeach(MAKE_FUNCTION, float, int, char)
  // Resolves to:
  float Make_float();
  int   Make_int();
  char  Make_char();
#endif

//! For each arguments in variadic macro pass that argument to a given macro and the index-of of that argument
//! > #define MAKE_ENUM(I, NAME) NAME = I,
//! > enum Quarks { SMetaForeachIndexed(MAKE_ENUM, Up, Down, Charm, Strange, Top, Bottom) };
#define SMetaForeachIndexed(FN, ...)    S_MetaForeachIndexed(FN, __VA_ARGS__)
#if 0
  // Example:
  #define MAKE_ENUM(NUM, NAME) NAME = NUM,
  enum Quarks
  {
    SMetaForeachIndexed(MAKE_ENUM, Up, Down, Charm, Strange, Top, Bottom)
  };
  // Resolves to:
  enum Quarks
  {
    Up = 0, Down = 1, Charm = 2, Strange = 3, Top = 4, Bottom = 5, 
  };
#endif

//! For each arguments in variadic macro pass that argument to a given macro, the index-of of that argument and a constant
//! > #define MAKE_BAZ(BAZ, NUM, TYPE) template<> struct BAZ<TYPE> { enum { Value = NUM }; };
//! > SMetaForeachIndexedArg1(Foo, MAKE_BAZ, float, int, double)
#define SMetaForeachIndexedArg1(_1, FN, ...) S_MetaForeachIndexedArg1(A1, FN, __VA_ARGS__)
#if 0
  // Example:
  template<typename T> struct Foo {};
  #define MAKE_BAZ(BAZ, NUM, TYPE) template<> struct BAZ<TYPE> { enum { Value = NUM }; };
  SMetaForeachIndexedArg1(Foo, MAKE_BAZ, float, int, double)
  // Resolves to:
  template<> struct Foo<float> { enum { Value = 0 }; };
  template<> struct Foo<int> { enum { Value = 1 }; };
  template<> struct Foo<double> { enum { Value = 2 }; }; 
#endif

//! For each arguments in variadic macro pass that argument to a given macro, the index-of of that argument and two constants
//! > #define MAKE_WALDO(BAZ, WALDO, NUM, TYPE) template<> struct BAZ<TYPE> { enum { WALDO = NUM }; };
//! > SMetaForeachIndexedArg2(Foo, Bar, MAKE_WALDO, float, int, double)
#define SMetaForeachIndexedArg2(_1, _2, FN, ...) S_MetaForeachIndexedArg2(_1, _2, FN, __VA_ARGS__)
#if 0
  // Example:
  template<typename T> struct Foo {};
  #define MAKE_WALDO(BAZ, WALDO, NUM, TYPE) template<> struct BAZ<TYPE> { enum { WALDO = NUM }; };
  SMetaForeachIndexedArg2(Foo, Bar, MAKE_WALDO, float, int, double)
  // Resolves to:
  template<> struct Foo<float> { enum { Bar = 0 }; };
  template<> struct Foo<int> { enum { Bar = 1 }; };
  template<> struct Foo<double> { enum { Bar = 2 }; }; 
#endif



SMacroDoc(Text="Expand macro argument")
#define SMetaExpand(_1) _1


SMacroDoc(Text="Concatenate two arguments")
#define SMetaConcat(_1, _2) S_MetaConcat_1(_1, _2)



SRegionDoc(Implementation)

  #define S_MetaConcat_1(_1, _2) _1 ## _2
  #define S_Meta_ToString(_1) #_1

  #if SMetaMaximumArguments == 8
  #include <Stardrive/Optional/StardriveMeta_8.inl>
  #elif SMetaMaximumArguments == 16
  #include <Stardrive/Optional/StardriveMeta_16.inl>
  #elif SMetaMaximumArguments == 24
  #include <Stardrive/Optional/StardriveMeta_24.inl>
  #elif SMetaMaximumArguments == 32
  #include <Stardrive/Optional/StardriveMeta_32.inl>
  #else
  #error "SMetaMaximumArguments not 8, 16, 24 or 32"
  #endif

#endif
