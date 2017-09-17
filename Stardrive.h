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
//! SIsDebug            -- Is this the Debug Build? [0  or 1]
//! SIsRelease          -- Is this the Release Build? [0  or 1]
//! SIsWindows          -- Is this Microsoft Windows? [0  or 1]
//! SIsApple            -- Is this macOS or iOS? [0  or 1]
//! SIsLinux            -- Is this Linux? [0  or 1]
//! SIsVisualStudio     -- Is this Visual Studio Compiler and what version? [2017, 2015, 1, 0]
//! SIsClang            -- Is this the Clang Compiler? [0  or 1]
//! SIsGcc              -- Is this the GCC Compiler? [0  or 1]
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


//! Plain Old Data
//! https://github.com/betajaen/Stardrive/blob/master/Documentation/plain-old-data.md
//! 
//! Cheat Sheet:
//! 
//! Integers -- uinteger (size_t), integer (intptr_t)
//! Numbers  -- unsigned: u8, u16, u32, u64  signed: i8, i16, i32, i64
//! Floats   -- f32, f64
//! Boolean  -- bool, b32
//! Char     -- char8
namespace Stardrive {

  typedef size_t    uinteger; SCompilerAssert(sizeof(uinteger) == (SArchitecture / 8), "Uninteger is expected to match register size");
  typedef intptr_t  integer;  SCompilerAssert(sizeof(integer ) == (SArchitecture / 8), "Integer is expected to match register size");
  
  typedef uint8_t   byte;     SCompilerAssert(sizeof(byte  )   == 1, "Unexpected byte size. Should be 1 bytes.");
  typedef uint16_t  word;     SCompilerAssert(sizeof(word  )   == 2, "Unexpected word size. Should be 2 bytes.");
  typedef uint32_t  dword;    SCompilerAssert(sizeof(dword )   == 4, "Unexpected dword size. Should be 4 bytes.");
  typedef uint64_t  qword;    SCompilerAssert(sizeof(qword )   == 8, "Unexpected qword size. Should be 8 bytes.");
  typedef int8_t    sbyte;    SCompilerAssert(sizeof(sbyte )   == 1, "Unexpected sbyte size. Should be 1 bytes.");
  typedef int16_t   sword;    SCompilerAssert(sizeof(sword )   == 2, "Unexpected sword size. Should be 2 bytes.");
  typedef int32_t   sdword;   SCompilerAssert(sizeof(sdword)   == 4, "Unexpected sdword size. Should be 4 bytes.");
  typedef int64_t   sqword;   SCompilerAssert(sizeof(sqword)   == 8, "Unexpected sqword size. Should be 8 bytes.");

  typedef uint8_t   u8;       SCompilerAssert(sizeof(u8  )     == 1, "Unexpected u8 size. Should be 1 bytes.");
  typedef uint16_t  u16;      SCompilerAssert(sizeof(u16 )     == 2, "Unexpected u16 size. Should be 2 bytes.");
  typedef uint32_t  u32;      SCompilerAssert(sizeof(u32 )     == 4, "Unexpected u32 size. Should be 4 bytes.");
  typedef uint64_t  u64;      SCompilerAssert(sizeof(u64 )     == 8, "Unexpected u64 size. Should be 8 bytes.");
  typedef int8_t    i8;       SCompilerAssert(sizeof(i8  )     == 1, "Unexpected i8 size. Should be 1 bytes.");
  typedef int16_t   i16;      SCompilerAssert(sizeof(i16 )     == 2, "Unexpected i16 size. Should be 2 bytes.");
  typedef int32_t   i32;      SCompilerAssert(sizeof(i32 )     == 4, "Unexpected i32 size. Should be 4 bytes.");
  typedef int64_t   i64;      SCompilerAssert(sizeof(i64 )     == 8, "Unexpected i64 size. Should be 8 bytes.");

  typedef int32_t   b32;      SCompilerAssert(sizeof(b32)      == 4, "Unexpected b32 size. Should be 4 bytes.");
  typedef char      char8;    SCompilerAssert(sizeof(char8)    == 1, "Unexpected char8 size. Should be 1 byte.");

  typedef float     f32;      SCompilerAssert(sizeof(f32)      == 4, "Unexpected f32 size. Should be 4 bytes.");
  typedef double    f64;      SCompilerAssert(sizeof(f64)      == 8, "Unexpected f64 size. Should be 4 bytes.");

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

  template<typename T> struct numeric {};
  template<> struct numeric<u8>  { static const u8  Max = UINT8_MAX,  Min = 0;         };
  template<> struct numeric<u16> { static const u16 Max = UINT16_MAX, Min = 0;         };
  template<> struct numeric<u32> { static const u32 Max = UINT32_MAX, Min = 0;         };
  template<> struct numeric<u64> { static const u64 Max = UINT64_MAX, Min = 0;         };
  template<> struct numeric<i8>  { static const i8  Max = INT8_MAX,   Min = INT8_MIN;  };
  template<> struct numeric<i16> { static const i16 Max = INT16_MAX,  Min = INT16_MIN; };
  template<> struct numeric<i32> { static const i32 Max = INT32_MAX,  Min = INT32_MIN; };
  template<> struct numeric<i64> { static const i64 Max = INT64_MAX,  Min = INT64_MIN; };

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

namespace Stardrive {
  
  SFunctionDoc(Text="Minimum of the a and b")
  template<typename T>
  T Min(const T& a, const T& b)
  {
    return a < b ? a : b;
  };

  SFunctionDoc(Text="Minimum of a, b and c")
  template<typename T>
  T Min(const T& a, const T& b, const T&c)
  {
    return Min(Min(a, b), c);
  };
  
  SFunctionDoc(Text="Maximum of the a and b")
  template<typename T>
  T Max(const T& a, const T& b)
  {
    return a > b ? a : b;
  };

  SFunctionDoc(Text="Maximum of a, b and c")
  template<typename T>
  T Max(const T& a, const T& b, const T& c)
  {
    return Max(Max(a, b), c);
  };
  
  SFunctionDoc(Text="Clamp value between minimum and maximum")
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

  template<typename T> struct AllocatedStore<T, memory::HeapAllocator>
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



//! Language Extensions
//! 

namespace Stardrive { namespace meta {
  
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
  
  namespace Pod
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

  namespace impl {
    template<typename T, uinteger C>
    struct Strong
    {
      T value;
      
      Strong()
        : value {} {}
      
      explicit Strong(const T value_)
        : value(value)
      {
      }
      
      Strong(const Strong& value)
      : value(value.value)
      {
      }

      Strong& operator=(const Strong& other) 
      {
        value = other.value;
        return *this;
      }

      Strong& operator=(const T& newValue)
      {
        value = newValue;
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
  }

  template<typename T>
  using Strong = impl::Strong<T, 0>;

}} // Stardrive::meta

namespace Stardrive {

  template<typename T>
  struct Optional
  {
    T   value;
    b32 isSet : 1;

    Optional();
    Optional(const T& value_);
    Optional(T&& value_);
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
  };

  template <typename T>
  Optional<T>::Optional() : value {}, isSet(false) {}
  
  template <typename T>
  Optional<T>::Optional(T&& value_) : value(value_), isSet(true) {}
  
  template <typename T>
  Optional<T>::Optional(const T& value_) : value(value_), isSet(true) {}

  template <typename T1, typename T2>
  Either<T1, T2>::Either(meta::First, const T1& first_): first(first_), isFirst(true) {}

  template <typename T1, typename T2>
  Either<T1, T2>::Either(meta::Second, const T2& second_): second(second_), isFirst(true) {}

  template<typename T>
  Optional<T> MakeOptional() { return Optional<T>(); }
  
  template<typename T>
  Optional<T> MakeOptional(const T& value)   { return Optional<T>(value); }
  
  template<typename T>
  Optional<T> MakeOptional(T&& value)   { return Optional<T>(value); }
  
  template<typename T1, typename T2>
  Either<T1, T2> MakeEither(const T1& value) { return Either<T1, T2>(meta::First(), value); }

  template<typename T1, typename T2>
  Either<T1, T2> MakeEither(const T2& value) { return Either<T1, T2>(meta::Second(), value); }

} // Stardrive

namespace Stardrive { namespace hash
{
  SFunctionDoc(Text="Calculate FNV-1A Hash from the given text")
  u32 fnv1a(const char8* str);

  #if defined(SStardrive)

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
  #endif

  SFunctionDoc(Text="constexpr version of fnv1a")
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



//! Endian
//! 
//! Cheat Sheet:
//! 
//! For u/i 8,16,32,64 types
//!
//! Swap      -- Swap endianness of a value
//! Convert   -- Convert a value from one endian to another type.

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

//! Bytes
//! 
//! Cheat Sheet:
//! 

namespace Stardrive { namespace bytes {
  
  template<typename T>
  inline byte* Get(const T& value) { return (byte*) &value; }
  
  template<typename T>
  inline uinteger Length()         { return sizeof(T); }
  
}} // Stardrive::bytes


//! Tribool
//!

namespace Stardrive {

  struct tribool
  {
    i8 v;
    
    tribool()       : v(-1) {}
    tribool(bool m) : v(m ? 1 : 0)  {}
    
    tribool& operator=(bool m)
    {
      v = m;
      return *this;
    }

    tribool& operator=(tribool m)
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

  };

  inline tribool operator!(tribool m)
  {
    if (m.v == 0)
      return tribool(true);
    else if (m.v == 1)
      return tribool(false);
    else
      return tribool();
  }

  inline bool IsUnknown(tribool m)
  {
    return m.v == -1;
  }

  const tribool unknown;
  
} // namespace Stardrive

#endif
