Memory
======

New and Delete
--------------

Stardrive has `new` and `delete` operators as `SNew` and `SDelete` macros.

```cpp
struct Point
{
  f32 x, y;

  Point(f32 X, f32 Y) : x(X), y(Y) {}
};

int main()
{
  Point* point = SNew(Point)(1.234f, 4.567f);
  // ...
  SDelete(point);
}
```

Allocators
----------

Stardrive uses an Allocator system to allocate, reallocate and deallocate memory. Generally they go;

```cpp
struct Allocator
{
  virtual void* Reallocate(void* memory, uinteger size, uinteger alignment) = 0;
};
```

The reallocate is a three-in-one function. If you give it a pointer and a size, it'll reallocate it, give it a pointer with no size, it'll free it, and give it no pointer with a size, it'll create it.

There is a default Heap Allocator which allocates memory on the Heap, through standard `malloc`, `realloc` and `free`.

```cpp
int main()
{
  byte* mem = memory::Allocate(16);
  // ...
  mem = memory::Deallocate(mem);
}
```

Alternatively you can allocate/deallocate directly with the Heap Allocator; via `memory::Heap()` or if you prefer `SHeap` macro.

```cpp
int main()
{
  byte* mem = SHeap->Reallocate(nullptr, 16, alignof(byte));
  // ...
  mem = SHeap->Reallocate(mem, 0, alignof(byte));
}
```

There are even use allocator specific macros for `SNew` and `SDelete`.

```cpp
int main()
{
  MyAllocator* allocator = GetMyAllocator();
  Point* point = SNewA(Point, allocator)(1.234f, 4.567f);
  // ...
  SDeleteA(point, allocator);
}
```

Functions
---------

The `Stardrive::memory` namespace has your typical memory management functions; `Zero`, `Set` and `Copy`.

```cpp
int main()
{
  byte* mem = memory::Allocate(16);
  memory::Zero(mem, 16);
  
  byte* mem2 = memory::Allocate(16);
  
  memory::Copy(mem2, mem, 16);

  memory::Set(mem2, 0xBB, 8);

  memory::Deallocate(mem);
  memory::Deallocate(mem2);
}
```
