Array
=====

Array is a growable array of any type that is based upon configurable Store. It is similar to the `std::vector`.

Setting up
----------

Array is in `Optional/StardriveContainers.h` just `#include` it normally.

```cpp
#include <Stardrive/Optionals/StardriveContainers.h>

typedef Array<u32> Integers;
```

Apart from `Array<T>` which is based upon `HeapStore`, there are some specialisations `FixedArray<T, MaxCapacity>` and `DynamicArray<T, MinCapacity>`.

Basic Usage
-----------

All `Array` functions belong in the `Stardrive::array` namespace with the first parameter always refering to the `Array` to work on. Like with all Stardrive classes, functions for the `Array` can be extended by defining them in the `Stardrive::array` namespace.

To setup the array just specifiy the type you want to store, and optionally set the Store to change the variant.

```cpp
Array<u32> m;
Array<
```


```cpp
int main()
{
  Array<u32> m;

  array::PushBack(m, 1);
  array::PushBack(m, 1);
  array::PushBack(m, 2);
  array::PushBack(m, 5);
  
  u32 sum = 0;
  for(u32 ii=0;ii < array::Length(m);ii++)
  {
    sum += m[ii];
  }
  
  array::Clear(m);
}
```

