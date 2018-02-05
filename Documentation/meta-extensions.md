
Meta Extensions
===============

The meta extensions are a collection of macros and templates to allow C++ meta programming. 

The main parts are in the `Stardrive.h` file, but expanded in the `Optional/Stardrive_meta.h` header.

Traits
------

There are utilities to determine at compile type if a particular type has a type-trait;

```
  typedef meta::IsPod<i32>()   is_true;
  typedef meta::IsClass<f32>() is_false;
```

Type Modifiers
-----------

Type modifiers can change the type to change parts of it;

```
  meta::RemovePointer<int*> x = 4;
  meta::RemoveReference<int&> y = 5;
  meta::RemoveEverything<int&*> z = 6;
```

Logic
------

The meta namespace has your standard `And`, `Or`, `Not` operators, and `If` and `IfNot`;

```
   template<typename T>
   struct IsNotPodOrClass : meta:Not<
    meta::Or<
      meta::IsPod<T>,
      meta::IsClass<T>
      >
   >
   {
   };
```

Constants as types
-------

Numerical and Boolean Constants contains are expressed as types, these are;

```
Stardrive::meta::True
Stardrive::meta::False
Stardrive::meta::Zeroth
Stardrive::meta::First
Stardrive::meta::Second
Stardrive::meta::Third
```

Simple uses of these could be as a cookie type within functions, that have identical argument types but perform differently. A good example, is the recursive meta function pattern;

``` 
	struct MyClass
    {
    	i32  x;
        i64  y;
        bool z;
        i8   w;
    };
    
    template<typename T, uinteger Index> struct TypesInfo {};
    template<typename T> struct TypeCount {};
    
    template<> struct TypesInfo<MyClass, 0> { typedef i32  T; };
    template<> struct TypesInfo<MyClass, 1> { typedef i64  T; };
    template<> struct TypesInfo<MyClass, 2> { typedef bool T; };
    template<> struct TypesInfo<MyClass, 3> { typedef i8   T; };
    
    template<> struct TypeCount<MyClass> { static const uinteger Count = 4; };
    
    ...
    
	template<typename T, uinteger FIndex>
    void SizeOf(uinteger& size, meta::False) {}

    template<typename T, uinteger FIndex>
    void SizeOf(uinteger& size, meta::True = meta::True())
    {
      size += sizeof(typename TypesInfo<T, FIndex>::T);
      SizeOf<T, FIndex + 1>(meta::If<FIndex < TypeCount<T>>(), size, count);
    }
    
    ...
    
    void main()
    {
    	uinteger size = 0;
        SizeOf<MyClass, 0>(&size);
    }
    
    
```

Macro Expansion
===============

Finally we have the macro side of meta programming, which is in the `Optional/StardriveMeta.h` header.

You may wish to define the `SMetaMaximumArguments` to either `8,16,24,32` to reduce or expand the maximum amount of arguments you are willing to use with them.

Counting
-----------

First of all, let's count some arguments.

```
void GetCount()
{
	int count = SMetaCountVaArgs(float, int, char);   // 3
    int count2 = SMetaCountVaArgs(1, 2, 4, 8);        // 4
}
 ```

Arguments to Code
-------

Instead let's expand that into something more useful. How about a list of types?

```
#define MAKE_FUNCTION(NAME) NAME Make_##NAME();
SMetaForeach(MAKE_FUNCTION, float, int, char)
```
Becomes:
```
float Make_float();
int   Make_int();
char  Make_char();
```

Let's do something more useful, how about an enum?
```
#define MAKE_ENUM(NUM, NAME) NAME = NUM,
enum Quarks
{
  SMetaForeachNum(MAKE_ENUM, Up, Down, Charm, Strange, Top, Bottom)
};
```
```
enum Quarks
  {
    Up = 0, 
    Down = 1,
    Charm = 2, 
    Strange = 3, 
    Top = 4, 
    Bottom = 5, 
  };
```

There are some variants on this as well, `SMetaForeachNumA1` and `SMetaForeachNumA2` will allow you to pass in 1 or 2 argument and use them as arguments in your macro expansion macro.

