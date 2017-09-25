Plain Old Data
==============

Stardrive provides a cross-compiler set of typedefs for integers, floating point numbers, booleans and characters so they are the same consistent size between platforms.

Integers
--------

There are two main types in Stardrive; `integer` and `uinteger`.

They represent the largest possible ranges of numbers for the compiled architecture. Typically on 32-bit architecture they are 4 bytes in size, and 8 bytes on 64-bit. Internally they are typedefs of `size_t` and `intptr_t`. 

`uinteger` is used throughout Stardrive to represent sizes, counts of items or sizes of memory allocations. `integer` is less used in Stardrive as it's main use is for pointer arithmetic.

```c++
struct Container
{
  uinteger count;
  
  uinteger GetCount()
  {
    return count;
  }
};
```

Numbers
--------

All Stardrive numbers start with `u` or `i` to indicate unsigned or signed, then have a number to indicate the number of bits of that type.

| Type    | Size | Signed | Aliases                       |
|---------|------|--------|-------------------------------|
| `u8`    | 1    | N      | `byte`, `SUnsignedChar`       |
| `u16`   | 2    | N      | `word`, `SUnsignedShort`      |
| `u32`   | 4    | N      | `dword`, `SUnsignedInt`       |
| `u64`   | 8    | N      | `qword`, `SUnsignedLongLong`  |
| `i8`    | 1    | Y      | `sbyte`, `SSignedChar`        |
| `i16`   | 2    | Y      | `sword`, `SShort`             |
| `i32`   | 4    | Y      | `sdword`, `SInt`              |
| `i64`   | 8    | Y      | `sqword`, `SLongLong`         |

```c++
int main()
{
  u32 a = 1234567;
  u8  b = 0xCA;
  i16 c = -70;
}
```

To check the maximum range of values for each number you can use the `numeric<TNumber>` struct, you can use these with the `Min`, `Max` and `Clamp` functions if you wish.

```c++
i32 ClampRange(i32 v)
{
  return Clamp(v, numeric<u16>::Min, numeric<u16>::Max);
}
```

You can twiddle and fiddle bits of all numbers through the `Stardrive::bits` namespace;

```c++
int main()
{
  u8 b = 0;
  bits::Set(b, 3);
  bool v = bits::Get(b, 3);
  bits::Clear(b, 3);
  
  u8 value = bits::At(5);
}
```

Floating Points
---------------

Floating points are more simplier, they both start with f and are either 32 or 64 to represent a float or a double.

```c++
int main()
{
  f32 pi = 3.14f;
  f64 e  = 2.71828182845904523536028747135266249775724709369995;
}
```

Character
---------

Character is represented as `char8` which is your standard go to non-Unicode character `char`.

```c++
struct Person
{
  const char8* name;
  void SetName(const char8* newName)
  {
    name = newName;
  }
};
```

Booleans
--------

Boolean doesn't have a Stardrive representation it's just `bool`, but there is another type `b32` which is a bit-field boolean.

Bit-field booleans are useful for craming lots of booleans into one struct, since a `bool` is at least 1 byte inside, lots of booleans to represent flags can eat up unnecessary memory.

```c++
struct SocketFlags
{
  b32 isTcp       : 1;
  b32 isBlocking  : 1;
  b32 isServer    : 1;
  b32 hasError    : 1;
  b32 hasIncoming : 1;
  b32 hasOutGoing : 1;
  
  void SetTcp(bool value)
  {
    isTcp = value;
  }
  
  bool IsTcp() const
  {
    return !!isTcp; // << Little trick to avoid a compiler warning of casting int to bool.
  }
};
```

In the case of `SocketFlags` the total size will be 4-bytes. Internally a `b32` is just an `int`.
