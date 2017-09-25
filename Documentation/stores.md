Stores
======

Stores are templated classes that hold one or many values (of the same Type) through an Allocator. They could be thought as an Array but with some extra bits thrown in. Some can grow in size some cannot. They also garbage collect.

### FixedStore

`FixedStore` just reserves memory as part of it self - just like a fixed array. Nothing special.

```cpp
int main()
{
  FixedStore<i32, 4> fs;
  fs[0] = 5;
  fs[1] = 6;
  fs[2] = 7;
  fs[3] = 8;

  DoSomething(m.GetData())
}
```

### AllocatedStore (and HeapStore)

```AllocatorStore``` and it's variant ```HeapStore``` are stores use memory that was allocated through an Allocator, because of this they are growable and thus have no fixed size, and like with all stores it will automatically clean up if it goes out of scope or deleted.

```cpp
struct Point
{
  f32 x, y;
};

int main()
{
  HeapStore<Point> hs;
  hs.Resize(100);
  for(uinteger ii=0;ii < 100;ii++)
    hs[ii] = {ii * -1.0f, ii * 3.0f};
  hs.Resize(150);
  for(uinteger ii=100;ii < 150;ii++)
    hs[ii] = {ii * 1.0f, ii * 9.0f};
}
```

### DynamicStore

A `DynamicStore` is a hybrid between a `FixedStore` and a `HeapStore`. It is a self growing Store, that first starts as a `FixedStore` but once it reaches maximum capacity it switches over to a `HeapStore` - all automatically.

```cpp
struct Vector4
{
  f32 x, y, z, w;
};

int main()
{
  DynamicStore<Vector4, 16> ds;
  ds.Resize(8);
  for(uinteger ii=0;ii < 8;ii++)
    ds[ii] = {ii * 0.01f, ii * 0.25f, ii * 4.0f, ii * 1.0f };
  ds.Resize(32);
  for(uinteger ii=8;ii < 32;ii++)
    ds[ii] = {ii * 0.1f, ii * 0.33f, ii * -3.2f, ii * 0.5f };
}
```
