/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

//! Basic Usage
//! https://github.com/betajaen/Stardrive/blob/master/Documentation/basic-usage.md
//! 
//! Cheat Sheet:
//! 
//! #include <Stardrive/Stardrive.h>    -- Header Files
//! 
//! #define SStardrive                  -- To a cpp file, only once!
//! #include <Stardrive/Stardrive.h>    

#ifndef STARDRIVE_H
#define STARDRIVE_H

#include <stdint.h>
#include <float.h>
#include <assert.h>
#include <new>

#if defined(SStardrive)
# include <malloc.h>
# include <string.h>
# include <stdio.h>
#endif

//! Basic Macros
//! https://github.com/betajaen/Stardrive/blob/master/Documentation/macros-and-constants.md
//! 
//! Cheat Sheet:
//! 
//! SArchitecture       -- Compiler Architecture [32 or 64]
//! SIsDebug            -- Is this the Debug Build? [0 or 1]
//! SIsRelease          -- Is this the Release Build? [0 or 1]
//! SIsWindows          -- Is this Microsoft Windows? [0 or 1]
//! SIsApple            -- Is this macOS or iOS? [0 or 1]
//! SIsLinux            -- Is this Linux? [0 or 1]
//! SIsVisualStudio     -- Is this Visual Studio Compiler and what version? [2017, 2015, 1, 0]
//! SIsClang            -- Is this the Clang Compiler? [0 or 1]
//! SIsGcc              -- Is this the GCC Compiler? [0 or 1]
//! SToStr              -- Turn given argument to string literal
//! SAssert             -- Assert based upon condition and give reason
//! SEnsure             -- Ensure given argument is valid and assert otherwise
//! SAssertAlways       -- Always assert at this point
//! SCompilerAssert     -- When compiling assert based upon condition and give reason
//! SCompilerAssertSize -- Assert size of type when it's not the expected size
//! SNoCopy             -- Class cannot be copied
//! SNoMove             -- Class cannot be moved

#if defined(_WIN32)
  #if defined(_WIN64)
    #define SArchitecture   64
  #else
    #define SArchitecture   32
  #endif
  #if defined(_DEBUG)
    #define SIsDebug 1
    #define SIsRelease 0
  #else
    #define SIsDebug 0
    #define SIsRelease 1
  #endif
  #define SIsWindows 1
#else
  #error "Unknown platform!"
  #define SIsWindows 0
  #define SIsApple   0
  #define SIsLinux   0
#endif

#if defined(__clang__)
  #define SIsClang 1
  #define SIsGcc 0
  #define SIsVisualStudio 0
#elif defined(__GNUC__) || defined(__GNUG__)
  #define SIsClang 0
  #define SIsGcc 1
  #define SIsVisualStudio 0
#elif defined(_MSC_VER)
  #if (_MSC_VER >= 1910)
    #define SIsVisualStudio 2017
  #elif (_MSC_VER >= 1900)
    #define SIsVisualStudio 2015
  #else
    #define SIsVisualStudio 1
  #endif
#else
  #error "Unknown Compiler"
#endif

#define SNoCopy(CLASS)                    CLASS(const CLASS&) = delete;  CLASS& operator=(const CLASS&) = delete;   
#define SNoMove(CLASS)                    CLASS(const CLASS&&) = delete; CLASS& operator=(const CLASS&&) = delete; 

//! Assertions
#define SAssert(COND, REASON)             assert((COND) && REASON)
#define SEnsure(COND)                     assert(COND)
#define SAssertAlways(REASON)             assert(false && REASON)
#define SCompilerAssert(COND, REASON)     static_assert(COND, REASON)
#define SCompilerAssertSize(TYPE, SIZE)   static_assert(sizeof(TYPE) == (SIZE), "Unexpected size for " SToStr(TYPE) " expected " SToStr(SIZE) " bytes!")


//! Unit Testing
//! 
#if defined(STests)
  #define STestRuntime_DeclareSuite(NAME)                const char* STestSuite_##NAME();
  #define STestRuntime_Suite(NAME, ...)                  const char* STestSuite_##NAME() { const char* r = nullptr; __VA_ARGS__;  return nullptr; }
  #define STestRuntime_RunTest(NAME)                     do { r = STest_##NAME(); if (r != nullptr) { return r; } } while(0)
  #define STestRuntime(NAME, ...)                        static const char* STest_##NAME() { __VA_ARGS__; return nullptr; }
  #define STestRuntime_Equals(A, B)                      do { if ((A) != (B)) return SToStr(A) "==" SToStr(B); } while(0)
  #define STestRuntime_Equals_Reasoning(A, B, REASON)    do { if ((A) != (B)) return REASON; } while(0)
  #define STestRuntime_NotEquals(A, B)                   do { if ((A) == (B)) return SToStr(A) "!=" SToStr(B); } while(0)
  #define STestRuntime_NotEquals_Reasoning(A, B, REASON) do { if ((A) == (B)) return REASON; } while(0)
  #define STestCompiler(NAME, ...)                       namespace __VA_ARGS__
  #define STestCompiler_Equals(A, B, REASON)             static_assert((A) == (B), REASON)
#else
  #define STestRuntime_DeclareSuite(NAME)                
  #define STestRuntime_Suite(NAME, ...)                  
  #define STestRuntime_RunTest(NAME)                     
  #define STestRuntime(NAME, ...)                        
  #define STestRuntime_Equals(A, B)                      
  #define STestRuntime_Equals_Reasoning(A, B, REASON)    
  #define STestRuntime_NotEquals(A, B)                   
  #define STestRuntime_NotEquals_Reasoning(A, B, REASON) 
  #define STestCompiler(NAME, ...)                       
  #define STestCompiler_Equals(A, B, REASON)             
#endif



//! Documentation Macros
//! 
#define SMacroDoc(...)
#define STypeDoc(...)
#define SFunctionDoc(...)
#define SFieldDoc(...)
#define SConstructorDoc(...)
#define SDestructorDoc(...)
#define SRegionDoc(...)


//! Plain Old Data and Number-likes
//! https://github.com/betajaen/Stardrive/blob/master/Documentation/plain-old-data.md
//! 
//! Cheat Sheet:
//! 
//! Integers                    -- uinteger (size_t), integer (intptr_t)
//! Numbers                     -- unsigned: u8, u16, u32, u64  signed: i8, i16, i32, i64
//! Floats                      -- f32, f64
//! Boolean                     -- bool, b32
//! Char                        -- char8
//!
//! Traits and Ops:             -- Type Traits/Operations, can be overriden (see Vector)
//! 
//! traits::MinMax<T>::Min      -- Minimum value
//! traits::MinMax<T>::Max      -- Maximum value
//! traits::IsSigned<T>::Value  -- Is the type signed
//! ops::Arithmetic<T>          -- Arithmetic functions (Add, Sub, Mul, Div)
//! ops::Equality<T>            -- Equality functions (Equals, NotEquals, ...)
//! numeric<T>                  -- All traits + ops in one class, acting as a 'templated namespace'

namespace Stardrive {

  typedef size_t    uinteger;   SCompilerAssert(sizeof(uinteger) == (SArchitecture / 8), "Uninteger is expected to match register size");
  typedef intptr_t  integer;    SCompilerAssert(sizeof(integer ) == (SArchitecture / 8), "Integer is expected to match register size");
  
  typedef uint8_t   byte;       SCompilerAssert(sizeof(byte  )   == 1, "Unexpected byte size. Should be 1 bytes.");
  typedef uint16_t  word;       SCompilerAssert(sizeof(word  )   == 2, "Unexpected word size. Should be 2 bytes.");
  typedef uint32_t  dword;      SCompilerAssert(sizeof(dword )   == 4, "Unexpected dword size. Should be 4 bytes.");
  typedef uint64_t  qword;      SCompilerAssert(sizeof(qword )   == 8, "Unexpected qword size. Should be 8 bytes.");
  typedef int8_t    sbyte;      SCompilerAssert(sizeof(sbyte )   == 1, "Unexpected sbyte size. Should be 1 bytes.");
  typedef int16_t   sword;      SCompilerAssert(sizeof(sword )   == 2, "Unexpected sword size. Should be 2 bytes.");
  typedef int32_t   sdword;     SCompilerAssert(sizeof(sdword)   == 4, "Unexpected sdword size. Should be 4 bytes.");
  typedef int64_t   sqword;     SCompilerAssert(sizeof(sqword)   == 8, "Unexpected sqword size. Should be 8 bytes.");

  typedef uint8_t   u8;         SCompilerAssert(sizeof(u8  )     == 1, "Unexpected u8 size. Should be 1 bytes.");
  typedef uint16_t  u16;        SCompilerAssert(sizeof(u16 )     == 2, "Unexpected u16 size. Should be 2 bytes.");
  typedef uint32_t  u32;        SCompilerAssert(sizeof(u32 )     == 4, "Unexpected u32 size. Should be 4 bytes.");
  typedef uint64_t  u64;        SCompilerAssert(sizeof(u64 )     == 8, "Unexpected u64 size. Should be 8 bytes.");
  typedef int8_t    i8;         SCompilerAssert(sizeof(i8  )     == 1, "Unexpected i8 size. Should be 1 bytes.");
  typedef int16_t   i16;        SCompilerAssert(sizeof(i16 )     == 2, "Unexpected i16 size. Should be 2 bytes.");
  typedef int32_t   i32;        SCompilerAssert(sizeof(i32 )     == 4, "Unexpected i32 size. Should be 4 bytes.");
  typedef int64_t   i64;        SCompilerAssert(sizeof(i64 )     == 8, "Unexpected i64 size. Should be 8 bytes.");

  typedef int32_t   b32;        SCompilerAssert(sizeof(b32)      == 4, "Unexpected b32 size. Should be 4 bytes.");
  typedef byte      Character;  SCompilerAssert(sizeof(Character)== 1, "Unexpected Character size. Should be 1 byte.");
  typedef u32       Character32;SCompilerAssert(sizeof(Character32)== 4, "Unexpected Character32 size. Should be 4 bytes.");

  typedef float     f32;        SCompilerAssert(sizeof(f32)      == 4, "Unexpected f32 size. Should be 4 bytes.");
  typedef double    f64;        SCompilerAssert(sizeof(f64)      == 8, "Unexpected f64 size. Should be 4 bytes.");

  #define SChar               char
  #define SSignedChar         signed char
  #define SShort              short
  #define SInt                int
  #define SLongLong           long long
  #define SUnsignedChar       unsigned char
  #define SUnsignedShort      unsigned short
  #define SUnsignedInt        unsigned int
  #define SUnsignedLongLong   unsigned long long
  #define SFloat              float
  #define SDouble             double

  namespace traits {
      
    template<typename T> 
    struct MinMax {};
      
    template<> struct MinMax<bool> { static constexpr bool Max = true,       Min = false;     };
    template<> struct MinMax<u8>   { static constexpr u8   Max = UINT8_MAX,  Min = 0;         };
    template<> struct MinMax<u16>  { static constexpr u16  Max = UINT16_MAX, Min = 0;         };
    template<> struct MinMax<u32>  { static constexpr u32  Max = UINT32_MAX, Min = 0;         };
    template<> struct MinMax<u64>  { static constexpr u64  Max = UINT64_MAX, Min = 0;         };
    template<> struct MinMax<i8>   { static constexpr i8   Max = INT8_MAX,   Min = INT8_MIN;  };
    template<> struct MinMax<i16>  { static constexpr i16  Max = INT16_MAX,  Min = INT16_MIN; };
    template<> struct MinMax<i32>  { static constexpr i32  Max = INT32_MAX,  Min = INT32_MIN; };
    template<> struct MinMax<i64>  { static constexpr i64  Max = INT64_MAX,  Min = INT64_MIN; };
    template<> struct MinMax<f32>  { static constexpr f32  Max = FLT_MAX,    Min = FLT_MIN;   };
    template<> struct MinMax<f64>  { static constexpr f64  Max = DBL_MAX,    Min = DBL_MIN;   };

    template<typename T>
    struct IsSigned
    {
      static constexpr bool Signed = false;
    };
      
    template<> struct IsSigned<i8>  { static constexpr bool Signed = true; };
    template<> struct IsSigned<i16> { static constexpr bool Signed = true; };
    template<> struct IsSigned<i32> { static constexpr bool Signed = true; };
    template<> struct IsSigned<i64> { static constexpr bool Signed = true; };
    template<> struct IsSigned<f32> { static constexpr bool Signed = true; };
    template<> struct IsSigned<f64> { static constexpr bool Signed = true; };
  }

  namespace ops
  {
    template<typename T>
    struct SignedArithmetic {};

    template<> struct SignedArithmetic<i8>  { static i8  Neg(i8  value) { return -value; } };
    template<> struct SignedArithmetic<i16> { static i16 Neg(i16 value) { return -value; } };
    template<> struct SignedArithmetic<i32> { static i32 Neg(i32 value) { return -value; } };
    template<> struct SignedArithmetic<i64> { static i64 Neg(i64 value) { return -value; } };
    template<> struct SignedArithmetic<f32> { static f32 Neg(f32 value) { return -value; } };
    template<> struct SignedArithmetic<f64> { static f64 Neg(f64 value) { return -value; } };

    template<typename T>
    struct Arithmetic
    {
      static T Value(T _1)           { return _1;      }
      static T Add(T _1, T _2)       { return _1 + _2; }
      static T Sub(T _1, T _2)       { return _1 - _2; }
      static T Mul(T _1, T _2)       { return _1 * _2; }
      static T Div(T _1, T _2)       { return _1 / _2; }

      static T AddMul(T _1, T _2, T _3) { return Add(_1, Mul(_2, _3)); }
      static T Mul(T _1, T _2, T _3)    { return Mul(_1, Mul(_2, _3)); }
    };

    template<typename T>
    struct Equality
    {
      static bool IsZero(const T& _1)                         { return _1 == 0;  }
      static bool Equals(const T& _1, const T& _2)            { return _1 == _2; }
      static bool NotEquals(const T& _1, const T& _2)         { return _1 != _2; }
      static bool LessThan(const T& _1, const T& _2)          { return _1 <  _2; }
      static bool LessThanEquals(const T& _1, const T& _2)    { return _1 <= _2; }
      static bool MoreThan(const T& _1, const T& _2)          { return _1 >  _2; }
      static bool MoreThanEquals(const T& _1, const T& _2)    { return _1 >= _2; }
      static T    IIfEquals(const T& _1, const T& _2)         { return Equals(_1, _2)         ? _1 : _2; }
      static T    IIfNotEquals(const T& _1, const T& _2)      { return NotEquals(_1, _2)      ? _1 : _2; }
      static T    IIfLessThan(const T& _1, const T& _2)       { return LessThan(_1, _2)       ? _1 : _2; }
      static T    IIfLessThanEquals(const T& _1, const T& _2) { return LessThanEquals(_1, _2) ? _1 : _2; }
      static T    IIfMoreThan(const T& _1, const T& _2)       { return MoreThan(_1, _2)       ? _1 : _2; }
      static T    IIfMoreThanEquals(const T& _1, const T& _2) { return MoreThanEquals(_1, _2) ? _1 : _2; }
    };

    template<>
    struct Equality<f32>
    {
      static bool IsZero(const f32& _1);
      static bool Equals(const f32& _1, const f32& _2);
      static bool NotEquals(const f32& _1, const f32& _2);
      static bool LessThan(const f32& _1, const f32& _2);
      static bool LessThanEquals(const f32& _1, const f32& _2);
      static bool MoreThan(const f32& _1, const f32& _2);
      static bool MoreThanEquals(const f32& _1, const f32& _2);
      static f32  IIfEquals(const f32& _1, const f32& _2)         { return Equals(_1, _2)         ? _1 : _2; }
      static f32  IIfNotEquals(const f32& _1, const f32& _2)      { return NotEquals(_1, _2)      ? _1 : _2; }
      static f32  IIfLessThan(const f32& _1, const f32& _2)       { return LessThan(_1, _2)       ? _1 : _2; }
      static f32  IIfLessThanEquals(const f32& _1, const f32& _2) { return LessThanEquals(_1, _2) ? _1 : _2; }
      static f32  IIfMoreThan(const f32& _1, const f32& _2)       { return MoreThan(_1, _2)       ? _1 : _2; }
      static f32  IIfMoreThanEquals(const f32& _1, const f32& _2) { return MoreThanEquals(_1, _2) ? _1 : _2; }
    };
    
    template<>
    struct Equality<f64>
    {
      static bool IsZero(const f64& _1);
      static bool Equals(const f64& _1, const f64& _2);
      static bool NotEquals(const f64& _1, const f64& _2);
      static bool LessThan(const f64& _1, const f64& _2);
      static bool LessThanEquals(const f64& _1, const f64& _2);
      static bool MoreThan(const f64& _1, const f64& _2);
      static bool MoreThanEquals(const f64& _1, const f64& _2);
      static f64  IIfEquals(const f64& _1, const f64& _2)         { return Equals(_1, _2)         ? _1 : _2; }
      static f64  IIfNotEquals(const f64& _1, const f64& _2)      { return NotEquals(_1, _2)      ? _1 : _2; }
      static f64  IIfLessThan(const f64& _1, const f64& _2)       { return LessThan(_1, _2)       ? _1 : _2; }
      static f64  IIfLessThanEquals(const f64& _1, const f64& _2) { return LessThanEquals(_1, _2) ? _1 : _2; }
      static f64  IIfMoreThan(const f64& _1, const f64& _2)       { return MoreThan(_1, _2)       ? _1 : _2; }
      static f64  IIfMoreThanEquals(const f64& _1, const f64& _2) { return MoreThanEquals(_1, _2) ? _1 : _2; }
    };
  }
  
  template<typename T>
  struct numeric : 
    traits::MinMax<T>, 
    traits::IsSigned<T>,
    ops::SignedArithmetic<T>,
    ops::Arithmetic<T>,
    ops::Equality<T>
  {
    typedef T Type;
  };
  
  namespace pod
  {
    enum Type
    {
      None,
      U8,
      U16,
      U32,
      U64,
      I8,
      I16,
      I32,
      I64,
      Float,
      Double,
      Boolean,
      Char
    };
  }

namespace bit {

  SFunctionDoc(Text="Get the nth bit of the given value")
  template<typename TNumeric>
  bool Get(TNumeric v, TNumeric bit)    { return (TNumeric) 0 != (v & ((TNumeric) 1 << bit)); }

  SFunctionDoc(Text="Set the bit of the given value from the given value")
  template<typename TNumeric>
  void Set(TNumeric& v, TNumeric bit)   { v |= ((TNumeric) 1 << bit); }

  SFunctionDoc(Text="Clear the bit of the given value from the given value")
  template<typename TNumeric>
  void Clear(TNumeric& v, TNumeric bit) { v &= ~((TNumeric) 1 << bit); }

  SFunctionDoc(Text="Get the value at the given bit")
  template<typename TNumeric>
  constexpr TNumeric At(TNumeric bit)   { return ((TNumeric) 1 << bit); }

  STestCompiler(Bits, {
    STestCompiler_Equals(bit::At<u64>(0),  0x01, "0x01 at bit 0");
    STestCompiler_Equals(bit::At<u64>(7),  0x80, "0x80 at bit 7");
    STestCompiler_Equals(bit::At<u64>(63), 0x8000000000000000, "0x8000000000000000 at bit 63");
  })

}} // Stardrive::bit


//! Limiting Values
//! 
//! Cheat Sheet:
//! 
//! Min   -- Minimum of A, B or A, B, C
//! Max   -- Maximum of A, B or A, B, C
//! Clamp -- Minimum < Value < Maximum 
//! 
//! Note: These functions work with any type that implements numeric<T>
//!
namespace Stardrive {
  
  //! Minimum of two values
  template<typename T>
  T Min(const T& _1, const T& _2)
  {
    return numeric<T>::IIfLessThan(_1, _2);
  };

  //! Minimum of three values
  template<typename T>
  T Min(const T& _1, const T& _2, const T& _3)
  {
    return numeric<T>::IIfLessThan(_1, numeric<T>::IIfLessThan(_2, _3));
  };
  
  //! Maximum of two values
  template<typename T>
  T Max(const T& _1, const T& _2)
  {
    return numeric<T>::IIfMoreThan(_1, _2);
  };

  //! Maximum of three values
  template<typename T>
  T Max(const T& _1, const T& _2, const T& _3)
  {
    return numeric<T>::IIfMoreThan(_1, numeric<T>::IIfMoreThan(_2, _3));
  };
  
  //! Restrict a value within range of minimum and maximum
  template<typename T>
  T Clamp(const T& value, const T& minimum, const T& maximum)
  {
    return Max(Min(value, minimum), maximum);
  };
  
}



//! Memory and Allocators
//! https://github.com/betajaen/Stardrive/blob/master/Documentation/memory-and-allocators.md
//! 
//! Cheat Sheet:
//!
//! SNew, SDelete                             --  New and Delete
//! SNewA, SDeleteA                           --  New and Delete with Allocator
//! memory::Allocate, Deallocate, Reallocate  --  Allocate, Deallocate or Reallocate memory or arrays
//! memory::Zero, Set, Copy                   --  Zero, Set or Copy Memory
//! FixedStore                                --  Fixed Sized Array-like container
//! AllocatorStore, HeapStore                 --  Dynamic Array-like Array container
//! DynamicStore                              --  Fixed Size then Dynamic Array-like container
//! SHeap                                     --  Get Heap Allocator
//! 
//! struct Allocator {
//!   virtual void* Reallocate(void* memory, uinteger size, uinteger alignment) = 0;
//! };

#define SNew(TYPE)                          new( SHeap->Reallocate(nullptr, sizeof(TYPE), alignof(TYPE)) ) TYPE
#define SDelete(OBJECT)                     do { ::Stardrive::memory::DestructAndDeallocate(SHeap, (OBJECT)); } while(0)
#define SNewA(TYPE, ALLOCATOR)              new( ALLOCATOR->Reallocate(nullptr, sizeof(TYPE), alignof(TYPE))) TYPE
#define SDeleteA(OBJECT)                    do { ::Stardrive::memory::DestructAndDeallocate((ALLOCATOR), (OBJECT)); } while(0)

namespace Stardrive { 

  STypeDoc(Text="User driven memory allocator")
  struct Allocator
  {
    virtual ~Allocator() {}
    virtual void* Reallocate(void* memory, uinteger size, uinteger alignment) = 0;
  };

  namespace memory {
  SFunctionDoc(Text="Align an existing pointer forward to the nearest given alignment")
  void* AlignForward(void* pointer, uinteger alignment);
  
#if defined(SStardrive)
  void* AlignForward(void* pointer, uinteger alignment)
  {
    uinteger address = uinteger(pointer);
    const uinteger addressModulus = address % alignment;
    if (addressModulus)
      address += (alignment - addressModulus);
    return (void*)(address);
  }
#endif

  SFunctionDoc(Text="Fill given memory with zeros with the given size in bytes")
  void Zero(void* memory, uinteger size);

#if defined(SStardrive)
  void Zero(void* memory, uinteger size)
  {
    memset(memory, 0, size);
  }
#endif

  SFunctionDoc(Text="Copy memory from the source address to the destination address of the given size in bytes")
  void Copy(void* dst, const void* src, uinteger size);

#if defined(SStardrive)
  void Copy(void* dst, const void* src, uinteger size)
  {
    memcpy(dst, src, size);
  }
#endif

  SFunctionDoc(Text="Set memory from the given address to the repeating given value")
  void Set(void* memory, byte value, uinteger size);

#if defined(SStardrive)
  void Set(void* memory, byte value, uinteger size)
  {
    memset(memory, value, size);
  }
#endif

  SFunctionDoc(Text="Destruct object and deallocate object memory")
  template<typename T> void DestructAndDeallocate(Allocator* allocator, T*& object)
  {
    if (allocator && object)
    {
      object->~T();
      object = (T*) allocator->Reallocate(object, 0, alignof(T));
    }
  }

  struct HeapAllocator;

#if defined(SStardrive)
  struct HeapAllocator : Allocator
  {
    
    ~HeapAllocator() {}

    void* Reallocate(void* memory, uinteger size, uinteger alignment)
    {
      /// @TODO alignment

      void* mem = nullptr;

      if (nullptr == memory && 0 != size)
      {
        mem = malloc(size);
      }
      else if (nullptr != memory && 0 != size)
      {
        mem = realloc(memory, size);
      }
      else if (nullptr != memory && 0 == size)
      {
        free(memory);
      }

      return mem;
    }
  };

  static byte           sHeapAllocatorData[sizeof(HeapAllocator)];
  static HeapAllocator* sHeapAllocator = nullptr;
#endif

  SFunctionDoc(Text="Get the Heap Allocator")
  Allocator* Heap();

#if defined(SStardrive)
  Allocator* Heap()
  {
    static HeapAllocator heapAllocator;
    return &heapAllocator;
  }
#endif

  #define SHeap (::Stardrive::memory::Heap())
  
  SFunctionDoc(Text="Allocate some memory using the given allocator. Default is SHeap")
  inline void* Allocate(uinteger size, uinteger alignment = alignof(uinteger), Allocator* allocator = SHeap)
  {
    return allocator->Reallocate(nullptr, size, alignment);
  }
  
  SFunctionDoc(Text="Deallocate some memory using the given allocator. Default is SHeap")
  inline void* Deallocate(void* mem, uinteger alignment = alignof(uinteger), Allocator* allocator = SHeap)
  {
    return allocator->Reallocate(mem, 0, alignment);
  }
  
  SFunctionDoc(Text="Deallocate some memory using the given allocator. Default is SHeap")
  inline void* Reallocate(void* mem, uinteger size, uinteger alignment = alignof(uinteger), Allocator* allocator = SHeap)
  {
    return allocator->Reallocate(mem, 0, alignment);
  }

  template<typename T>
  void DestructItems(T* items, uinteger count = 1)
  {
    while(count)
    {
      items->~T();
      ++items;
      --count;
    }
  }

}} // Stardrive::memory

namespace Stardrive {

  template<typename T, typename TAllocator>
  struct AllocatedStore
  {
  private:
    T*   _elements;
    u32  _count;
    T*   _allocator;
  public:
    AllocatedStore(TAllocator* allocator, u32 count = 0) 
      : _elements(nullptr), _count(count), _allocator(allocator)
    {
      _count = count;
      Resize(count);
    }

    ~AllocatedStore()
    {
      Release();
    }
    
    uinteger  GetSize() const 
    { 
      return _count;
    }

    T*   GetData()
    {
      return _elements;
    }
    
    const T* GetData() const
    {
      return _elements;
    }

    T& operator[](u32 index)
    {
      SEnsure(index < _count);
      return _elements[index];
    }
    
    const T& operator[](u32 index) const
    {
      SEnsure(index < _count);
      return _elements[index];
    }
    
    void Release()
    {
      Resize(0);
    }
    
    bool Resize(uinteger newCount)
    {
      SAssert(newCount < numeric<u32>::Max, "To large to allocate");
      _elements  = (T*) _allocator->Reallocate(_elements, sizeof(T) * _count, alignof(T));
      _count     = (u32) newCount;
      return true;
    }
    
  };

  template<typename T>
  struct AllocatedStore<T, memory::HeapAllocator>
  {
  private:
    T*   _elements;
    u32  _count;
  public:
    AllocatedStore(u32 count = 0) 
      : _elements(nullptr), _count(count)
    {
      Resize(count);
    }

    ~AllocatedStore()
    {
      Release();
    }

    T*   GetData()
    {
      return _elements;
    }
    
    const T* GetData() const
    {
      return _elements;
    }

    uinteger  GetSize() const 
    { 
      return _count;
    }

    T& operator[](u32 index)
    {
      SEnsure(index < _count);
      return _elements[index];
    }
    
    const T& operator[](u32 index) const
    {
      SEnsure(index < _count);
      return _elements[index];
    }

    void Release()
    {
      Resize(0);
    }

    bool Resize(uinteger newCount)
    {
      SAssert(newCount < numeric<u32>::Max, "To large to allocate");
      _elements  = (T*) (::Stardrive::memory::Heap())->Reallocate(_elements, sizeof(T) * newCount, alignof(T));
      _count     = (u32) newCount;
      return true;
    }
    
  };
  
  template<typename T> using HeapStore = AllocatedStore<T, memory::HeapAllocator>;

  template<typename T, u32 TCapacity>
  struct FixedStore
  {
  private:
    T   _elements[TCapacity];

  public:

    FixedStore()
    {
      memory::Zero(&_elements[0], sizeof(_elements));
    }
    
    ~FixedStore()
    {
      memory::Zero(&_elements, sizeof(_elements));
    }

    T* GetData()
    {
      return _elements;
    }
    
    const T* GetData() const
    {
      return _elements;
    }

    uinteger GetSize() const
    {
      return TCapacity;
    }

    T& operator[](u32 index)
    {
      SEnsure(index < TCapacity);
      return _elements[index];
    }
    
    const T& operator[](u32 index) const
    {
      SEnsure(index < TCapacity);
      return _elements[index];
    }
    
    bool Resize(uinteger newCount /* ignored */)
    {
      return false;
    }

  };

  template<typename T, u32 TMinCapacity>
  struct DynamicStore
  {
  private:
    bool _heapAllocated;
    u32 _count;
    union TData
    {
      struct { T  elements[TMinCapacity]; } i;
      struct { T* elements; } h;
    };
    TData data;
  public:
    DynamicStore()
      : _heapAllocated(false), _count(0)
    {
      memory::Zero(&data, sizeof(data));
    }

    ~DynamicStore()
    {
      if (_heapAllocated)
      {
        SHeap->Reallocate(data.h.elements, 0, sizeof(T));
      }
      memory::Zero(&data, sizeof(data));
    }
    
    T* GetData()
    {
      if (_count <= TMinCapacity)
        return &data.i.elements[0];
      return &data.h.elements[0];
    }
    
    uinteger GetSize() const
    {
      return _count;
    }

    bool IsHeapAllocated() const
    {
      return _heapAllocated;
    }

    T& operator[](u32 index)
    {
      SEnsure(index < _count);
      return GetData()[index];
    }
    
    const T& operator[](u32 index) const
    {
      SEnsure(index < _count);
      return GetData()[index];
    }

    bool Resize(uinteger newCount)
    {
      SAssert(newCount < numeric<u32>::Max, "To large to allocate");

      if (IsHeapAllocated())
      {
        if (newCount < TMinCapacity)
        {
          T* heapData = data.h.elements;
          memory::Copy(&data.i.elements, heapData, newCount * sizeof(T));
          SHeap->Reallocate(heapData, 0, alignof(T));
          _count = newCount;
        }
        else
        {
          data.h.elements = (T*) SHeap->Reallocate(data.h.elements, sizeof(T) * newCount, alignof(T));
          _count = newCount;
        }
      }
      else
      {
        if (newCount > TMinCapacity)
        {
          T* newHeapData = (T*) SHeap->Reallocate(nullptr, sizeof(T) * newCount, alignof(T));
          memory::Copy(newHeapData, &data.i.elements, _count * sizeof(T));
          memory::Zero(&data.i.elements, sizeof(data.i.elements));
          data.h.elements = newHeapData;
          _count = newCount;
        }
        else
        {
          _count = newCount;
        }
      }
      return false;
    }

  };

  template<uinteger MinSize> using ScratchData = DynamicStore<byte, MinSize>;
  
} // Stardrive



//! Meta Language Extensions
//! https://github.com/betajaen/Stardrive/blob/master/Documentation/meta-extensions.md
//! 
//! Cheat Sheet:
//!
//! Constants expressed as types:
//!
//! Constant<T, T TValue, uinteger Cookie>  -- Integer/Boolean value as a constant type
//! Numeric                                 -- Integer; see Zeroth, First, Second, Third, Fourth
//! TrueFalse                               -- Boolean; see True, False
//! 
//! Comparisons expressed as types:
//! 
//! meta::True                              -- True type
//! meta::False                             -- False type
//! meta::If                                -- Templated If condition      -- meta::If<4 == 3>    -> False as TrueFalse type
//! meta::IfNot                             -- Templated If not condition  -- meta::IfNot<4 ===3> -> True  as TrueFalse type
//! meta::And                               -- Bitwise And on a template True/False argument  -> meta::
//! meta::Or                                -- Bitwise Or on a template True/False argument
//! meta::Not                               -- Bitwise Not on a template True/False argument
//! 
//! Type Modifiers:
//!
//! meta::RemoveConst                       -- Remove const from type      -- meta::RemoveConst<const char*>::Type -> char*
//! meta::RemoveVolatile                    -- Remove volatile from type
//! meta::RemovePointer                     -- Remove pointer (and pointer pointer) from type
//! meta::RemoveReference                   -- Remove reference
//! meta::RemoveAll                         -- Just the type nothing else
//! meta::Carry                             -- Make no modifications to type
//! 
//! Type Is:
//! 
//! meta::IsSame<T1, T2>                    -- Are two types the same?                -- int* == int* -> True
//! meta::IsApproximately<T1, T2>           -- Are two types approximately the same?  --  int* == int   -> True
//! meta::IsPointer<T>                      -- Is a type a pointer?
//! meta::IsReference<T>                    -- Is a type a reference?
//! meta::IsClass<T>                        -- Is a type a class?
//! meta::IsUnion<T>                        -- Is a type a union?
//! meta::IsPod<T>                          -- Is a type Plain-Old-Data               -- char, i32, f32, etc.
//! meta::IsNotPod<T>                       -- Is a type not Plain Old-Data
//! meta::IsPodStruct<T>                    -- Is a type a POD-like struct            -- Vector, Quaternion, etc.
//! meta::IsEnum<T>                         -- Is a type an enum?

namespace Stardrive
{
  
  template<typename T, typename TEvalulator = bool>
  T IIf(TEvalulator condition, const T& _true, const T& _false)
  {
    return ((condition)()) ? _true : _false;
  }

  namespace meta
  {

  template<typename T, T TValue, uinteger TCookie = 0>
  struct Constant
  {
    static constexpr T Value = TValue;
    operator T() const     { return Value; }
    T operator ()() const  { return Value; }
  };
  
  template<integer N>
  using Numeric = Constant<integer, N, 'NUM'>;

  typedef Numeric<0> Zeroth;
  typedef Numeric<1> First;
  typedef Numeric<2> Second;
  typedef Numeric<3> Third;
  typedef Numeric<4> Fourth;

  template<bool B>
  using TrueFalse = Constant<bool, B, 'BOOL'>;

  typedef TrueFalse<true>   True;
  typedef TrueFalse<false>  False;
  
  template<bool Condition>
  using If = TrueFalse<Condition>;
  
  template<bool Condition>
  using IfNot = TrueFalse<!(Condition)>;

  template<typename T>
  struct Not {};
  template<> struct Not<True>  : meta::False {};
  template<> struct Not<False> : meta::True {};

  template<typename T1, typename T2>
  struct And {};
  template<> struct And<False, False> : meta::False {};
  template<> struct And<False, True>  : meta::False {};
  template<> struct And<True, False>  : meta::False {};
  template<> struct And<True, True>   : meta::True  {};
  
  template<typename T1, typename T2>
  struct Or {};
  template<> struct Or<False, False>  : meta::False {};
  template<> struct Or<False, True>   : meta::True  {};
  template<> struct Or<True, False>   : meta::True  {};
  template<> struct Or<True, True>    : meta::True  {};

  template<typename T> struct RemoveConst                { typedef T Type; };
  template<typename T> struct RemoveConst<const T>       { typedef T Type; };
  template<typename T> struct RemoveVolatile             { typedef T Type; };
  template<typename T> struct RemoveVolatile<volatile T> { typedef T Type; };
  template<typename T> struct RemovePointer              { typedef T Type; };
  template<typename T> struct RemovePointer<T*>          { typedef T Type; };
  template<typename T> struct RemovePointer<T**>         { typedef T Type; };
  template<typename T> struct RemoveReference            { typedef T Type; };
  template<typename T> struct RemoveReference<T&>        { typedef T Type; };
  template<typename T> struct RemoveReference<T&&>       { typedef T Type; };
  template<typename T> struct Carry                      { typedef T Type; };
  
  namespace impl
  {
    template<typename T> struct RemoveAll
    {
      typedef typename meta::RemovePointer<
              typename meta::RemoveReference<
              typename meta::RemoveVolatile<
              typename meta::RemoveConst<T>
              ::Type>::Type>::Type>::Type
              Type;
    };
  }

  template<typename T>
  using Clean = typename impl::RemoveAll<T>::Type;

  namespace impl
  {
    template<typename T1, typename T2> struct IsSame          : meta::False {};
    template<typename T>               struct IsSame<T, T>    : meta::True  {};
    
    template<typename T>               struct IsPointer       : meta::False {};
    template<typename T>               struct IsPointer<T*>   : meta::True  {};
    
    template<typename T>               struct IsReference     : meta::False {};
    template<typename T>               struct IsReference<T&> : meta::True  {};

    template<typename T>               struct IsEnum          : meta::If<__is_enum(T)>  {};
    template<typename T>               struct IsPod           : meta::If<__is_pod(T)>   {};
    template<typename T>               struct IsClass         : meta::If<__is_class(T)> {};
    template<typename T>               struct IsUnion         : meta::If<__is_union(T)> {};
    template<typename T>               struct IsPodStruct     : meta::If<__is_pod(T) && __is_class(T) && __is_trivial(T)> {};
  }

  template<typename T1, typename T2>
  using IsSame          = impl::IsSame<T1, T2>;
    
  template<typename T1, typename T2>
  using IsApproximately = impl::IsSame<typename impl::RemoveAll<T1>::Type, typename impl::RemoveAll<T2>::Type>;

  template<typename T>
  using IsPointer       = impl::IsPointer<typename impl::RemoveAll<T>::Type>;

  template<typename T>
  using IsReference     = impl::IsReference<typename impl::RemoveAll<T>::Type>;

  template<typename T>
  using IsPod           = impl::IsPod<typename impl::RemoveAll<T>::Type>;

  template<typename T>
  using IsNotPod        = meta::Not<impl::IsPod<typename impl::RemoveAll<T>::Type>>;
    
  template<typename T>
  using IsPodStruct     = impl::IsPodStruct<T>;

  template<typename T>
  using IsEnum          = impl::IsEnum<T>;
    
  template<typename T>
  using IsClass         = impl::IsClass<T>;

  template<typename T>
  using IsUnion         = impl::IsUnion<T>;

}} // Stardrive::meta

namespace Stardrive
{
  namespace mixin
  {
    struct NonCopyable
    {
      NonCopyable() = default;
      NonCopyable(const NonCopyable& other) = delete;
      NonCopyable& operator=(const NonCopyable& other) = delete;
    };

    struct NonMovabable
    {
      NonMovabable() = default;
      NonMovabable(const NonMovabable&& other) = delete;
      NonMovabable& operator=(const NonMovabable&& other) = delete;
    };
  }
}

//! Type Hardening
//! https://github.com/betajaen/Stardrive/blob/master/Documentation/type-hardening.md
//! 
//! Cheat Sheet:
//!
//!  Strong<T, Cookie> -- Strong typedef                            -- typedef Strong<f32, 'LENG'> Length; Length len = Length(4.0f);
//!  Optional<T>       -- Optional value                            -- Optional<int>::True(4),  Optional<int>::False()
//!  Optional<void>    -- Optional with no type of value            -- Optional<void>::True(), Optional<void>::False()
//!  Either<T1, T2>    -- Either one value or an other but not both -- Either<f32, const char*>::First(3.14f), Either<f32, const char*>::Second("Pi") 
//!  Tribool           -- True, False or Unknown type
//!  Opaque<Cookie>    -- Representation of a pointer or handle as an uinteger to hide implementation.
//!  Dummy<T>          -- Store of a variable inside itself with delayed New/Delete functions.

namespace Stardrive
{

  template<typename T, uinteger Cookie>
  struct Strong
  {
    T value;
      
    Strong()
      : value {} {}
    
    explicit Strong(const T value_)
      : value(value) {}
    
    Strong(const Strong& value)
      : value(value.value) {}

    Strong& operator=(const Strong& other) 
    {
      value = other.value;
      return *this;
    }

    Strong& operator=(const T& newValue)
    {
      value = newValue;
      return *this;
    }

    operator const T&() const 
    {
      return value;
    }

    operator T&()
    {
      return value;
    }

    bool operator==(const Strong& other) const
    {
      return value == other.value;
    }

    bool operator<(const Strong& other) const
    {
      return value < other.value;
    }
  };

  template<typename T>
  struct Optional
  {
    T   value;
    b32 isSet : 1;

    Optional();
    Optional(const T& value_);
    Optional(T&& value_);

    inline bool IsSet() const { return !!isSet; }

    static Optional<T> False();
    static Optional<T> True(const T& value_);
  };

  template<>
  struct Optional<void>
  {
    b32 isSet : 1;

    Optional();
    
    inline bool IsSet() const { return !!isSet; }

    static Optional<void> False();
    static Optional<void> True();
  };

  template<typename T1, typename T2>
  struct Either
  {
    union
    {
      T1 first;
      T2 second;
    };
    b32 isFirst : 1;

    operator T1&()
    {
      return first;
    }

    operator T2&()
    {
      return second;
    }

    Either(meta::First,  const T1& first_);
    Either(meta::Second, const T2& second_);

    static Either<T1, T2> First(const T1& first_);
    static Either<T1, T2> Second(const T2& second_);
  };

  template <typename T>
  inline Optional<T>::Optional() : value {}, isSet(false) {}
  
  template <typename T>
  inline Optional<T>::Optional(T&& value_) : value(value_), isSet(true) {}
  
  template <typename T>
  inline Optional<T> Optional<T>::False() { return Optional<T>(); }

  template <typename T>
  inline Optional<T> Optional<T>::True(const T& value_) { return Optional<T>(value_); }

  template <typename T>
  inline Optional<T>::Optional(const T& value_) : value(value_), isSet(true) {}

  inline Optional<void>::Optional() : isSet(false) {}

  inline Optional<void> Optional<void>::False() { return Optional<void>(); }

  inline Optional<void> Optional<void>::True()  { Optional<void> m; m.isSet = true; return m; }

  template <typename T1, typename T2>
  Either<T1, T2>::Either(meta::First, const T1& first_): first(first_), isFirst(true) {}

  template <typename T1, typename T2>
  Either<T1, T2>::Either(meta::Second, const T2& second_): second(second_), isFirst(true) {}

  template <typename T1, typename T2>
  Either<T1, T2> Either<T1, T2>::First(const T1& first_) { return Either<T1, T2>(meta::First(), first_); }

  template <typename T1, typename T2>
  Either<T1, T2> Either<T1, T2>::Second(const T2& second_) { return Either<T1, T2>(meta::Second(), second_); }

  struct Tribool
  {
    i8 v;
    
    Tribool()       : v(-1) {}
    Tribool(bool m) : v(m ? 1 : 0)  {}
    
    Tribool& operator=(bool m)
    {
      v = m;
      return *this;
    }

    Tribool& operator=(Tribool m)
    {
      v = m.v;
      return *this;
    }

    bool operator==(bool m) const
    {
      if (m && v == 1 || !m && v == 0)
        return m;
      return false;
    }

    bool operator!=(bool m) const
    {
      return !operator==(m);
    }
    
    static Tribool True()    { return Tribool(true); }
    static Tribool False()   { return Tribool(false); }
    static Tribool Unknown() { return Tribool(); }

  };

  inline Tribool operator!(Tribool m)
  {
    if (m.v == 0)
      return Tribool(true);
    else if (m.v == 1)
      return Tribool(false);
    else
      return Tribool();
  }
  
  inline bool IsUnknown(Tribool m)
  {
    return m.v == -1;
  }
  
  template<uinteger Cookie, uinteger Default = 0>
  struct Opaque
  {
    u64 opaque;

    inline Opaque()
     : opaque(Default)
    {
    }

    inline void SetDefault()
    {
      opaque = Default;
    }

    inline bool IsSet() const
    {
      return opaque != Default;
    }

    template<typename T>
    inline void Acquire(const T& value)
    {
      opaque = (u64) value;
    }

    template<typename T>
    inline T Cast() const
    {
      return (T) opaque;
    }
  };
  
  template<uinteger Cookie, uinteger Default = 0>
  struct Hidden : mixin::NonCopyable
  {
    Opaque<Cookie, Default> opaque;

    Hidden() = default;
    Hidden(const Hidden&& op);

    Hidden& operator=(const Hidden&& other);

  };

  template <uinteger Cookie, uinteger Default>
  Hidden<Cookie, Default>::Hidden(const Hidden&& op)
  {
    opaque = op.opaque;
    op.opaque.SetDefault();
  }

  template <uinteger Cookie, uinteger Default>
  Hidden<Cookie, Default>& Hidden<Cookie, Default>::operator=(const Hidden&& other)
  {
    opaque = other.opaque;
    other.opaque.SetDefault();
    return *this;
  }

  template<typename T>
  struct Dummy
  {
    u8 data[sizeof(T)];
    
    void New()
    {
      memory::Zero(&data[0], sizeof(T));
      new((void*) &data[0]) T();
    }

    template<typename... TArgs>
    void New(const TArgs&... constructorArguments)
    {
      memory::Zero(&data[0], sizeof(T));
      new((void*) &data[0]) T(constructorArguments...);
    }

    void Delete()
    {
      T* t = operator*();
      t->~T();
      memory::Zero(&data[0], sizeof(T));
    }

    T* operator*()
    {
      return (T*) &data[0];
    }

    const T* operator*() const
    {
      return (T*) &data[0];
    }

    T* operator->()
    {
      return (T*) &data[0];
    }

    const T* operator->() const
    {
      return (T*) &data[0];
    }

  };

} // Stardrive

#endif
