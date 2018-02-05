/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  -= Containers Option =-                                                                           
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

#ifndef STARDRIVE_CONTAINERS_H
#define STARDRIVE_CONTAINERS_H

#include <Stardrive/Stardrive.h>

namespace Stardrive {

//! Array
//! https://github.com/betajaen/Stardrive/blob/master/Documentation/Containers/array.md
//! 
//! Standard growable array based on a customisable Store (HeapStore as default).
//!
//! Cheat Sheet:
//! 
//! Array<int> ary;
//! 
//! ary[index]      -- Get reference to the Item at index.
//! array::Push     -- Push item to the end of the array.
//! array::Pop      -- Pop item from the end of array.
//! array::Size     -- Get the number of items in the array.
//! array::Capacity -- Get the maximum number of items in the array before the Store grows.
//! array::GetData  -- Get a pointer to the first element in the array.
//! 
//! Specalisations:
//! 
//! FixedArray      -- Array based on a Fixed Store aka; int array[4];
//! DynamicArray    -- Array based on a Dynamic Store aka;  int* array;
//! 
template<typename T, typename TStore = HeapStore<T>>
struct Array;

//! Array specialisation using a HeapStore -- A bit like; int* array = malloc(sizeof(int) * size);
template<typename T>
using HeapArray = Array<T, HeapStore<T>>;

//! Array specialisation using a FixedStore -- A bit like; int array[8];
template<typename T, u32 MaxCapacity>
using FixedArray = Array<T, FixedStore<T, MaxCapacity>>;

//! Array specialisation using a Dynamic Store.
template<typename T, u32 MinCapacity>
using DynamicArray = Array<T, DynamicStore<T, MinCapacity>>;

namespace array
{
  //! Get a pointer to the first element in the array
  template<typename T, typename TStore>
  T* GetData(Array<T, TStore>& a);

  //! Get a const pointer to the first element in the array
  template<typename T, typename TStore>
  const T* GetData(const Array<T, TStore>& a);

  //! Is the array empty?
  template<typename T, typename TStore>
  bool Empty(const Array<T, TStore>& a);

  //! Does the array have anything?;
  template<typename T, typename TStore>
  bool Any(const Array<T, TStore>& a);

  //! Has the array has exactly one element
  template<typename T, typename TStore>
  bool One(const Array<T, TStore>& a);

  //! Has the array has many (more than one) elements?
  template<typename T, typename TStore>
  bool Many(const Array<T, TStore>& a);

  //! Get the Size (number of items) of the array
  template<typename T, typename TStore>
  uinteger Size(const Array<T, TStore>& a);

  //! Get the Capacity (reserved capacity of items) of the array
  template<typename T, typename TStore>
  uinteger Capacity(const Array<T, TStore>& a);

  //! Get a pointer to the first item in the array
  template<typename T, typename TStore>
  T* Begin(Array<T, TStore>& a);

  //! Get a const pointer to the first item in the array
  template<typename T, typename TStore>
  const T* Begin(const Array<T, TStore>& a);

  //! Get a pointer to the last item in the array
  template<typename T, typename TStore>
  T* End(Array<T, TStore>& a);

  //! Get a const pointer to the last item in the array
  template<typename T, typename TStore>
  const T* End(const Array<T, TStore>& a);

  //! Reset the size of the 0 to zero.
  //! Note: Does not call item destructors!
  template<typename T, typename TStore>
  void Clear(Array<T, TStore>& a);

  //! Change the size of the array
  //! Note: Does not call item destructors!
  template<typename T, typename TStore>
  void Resize(Array<T, TStore>& a, uinteger newSize);

  //! Reserve a given capacity for the array
  //! Note: Pointers may be invalid after a resize
  template<typename T, typename TStore>
  void Reserve(Array<T, TStore>& a, uinteger newMaxSize);

  //! Set the capacity of the array.
  //! Note: Does not call item destructors!
  //! Note: Pointers may be invalid after a resize
  template<typename T, typename TStore>
  void SetCapacity(Array<T, TStore>& a, uinteger newMaxSize);

  //! Push a future item to the end of the array.
  template<typename T, typename TStore>
  T* LatePush(Array<T, TStore>& a);

  //! Insert item at the index of the array and shift items to the right upwards
  template<typename T, typename TStore>
  void Insert(Array<T, TStore>& a, uinteger index, const T& value);

  //! Push item to the end of the array.
  template<typename T, typename TStore>
  void Push(Array<T, TStore>& a, const T& value);

  //! Pop item from the end of the array and return it.
  template<typename T, typename TStore>
  T Pop(Array<T, TStore>& a);

  //! Remove item from the array and shift items down to the right downwards
  template<typename T, typename TStore>
  void Remove(Array<T, TStore>& a, uinteger index);

  //! Remove item from the array and replace it with the last
  //! Note: Does not call item destructors!
  template<typename T, typename TStore>
  void RemoveSwap(Array<T, TStore>& a, uinteger index);

  //! Shift items at index to the right by one
  //! Item at index may be duplicated.
  template<typename T, typename TStore>
  void ShiftRight(Array<T, TStore>& a, uinteger index);
  
  //! Shift items at index to the right by one
  //! Item at index may be duplicated.
  template<typename T, typename TStore>
  void ShiftLeft(Array<T, TStore>& a, uinteger index);

  //! Copy one array into another array.
  template<typename T, typename TStore>
  void Copy(Array<T, TStore>& dst, const Array<T, TStore>& src);

  //! Move one array into another array.
  template<typename T, typename TStore>
  void Move(Array<T, TStore>& dst, Array<T, TStore>& src);
}

//! Array implementation
template<typename T, typename TStore>
struct Array : protected TStore
{
  friend T*       array::GetData(Array<T, TStore>& a);
  friend const T* array::GetData(const Array<T, TStore>& a);
  friend uinteger array::Capacity<T, TStore>(const Array<T, TStore>& a);
  friend void     array::SetCapacity(Array<T, TStore>& a, uinteger newMaxSize);

  uinteger size;

  Array();
  Array(const Array& other);
  Array(Array&& other);
  ~Array();

  Array<T, TStore>& operator=(const Array& other);
  Array<T, TStore>& operator=(Array&& other);

  T& operator[](uinteger idx);
  const T& operator[](uinteger idx) const;
};
} // Stardrive


//! List
//! https://github.com/betajaen/Stardrive/blob/master/Documentation/Containers/list.md
//!
//! Double Linked list implementation using inheritance or duck-typed classes.
//! 
//! Cheat Sheet:
//! 
//! list::Add     -- Add an item to the end of the list
//! list::Remove  -- Remove an item from anywhere in the list
//! list::Clear   -- Clear list
//! list::Count   -- Count number of items in the list
//! 
//! Inheritance Usage:
//!   struct Thing  : ListItem<T> {};
//!   struct Things : List<Thing> {};
//! Duck-Typed Usage:
//!   struct Thing  { Thing *next, *prev;  };
//!   struct Things { Thing *first, *last; };
//!

namespace Stardrive {

//! Linked-List Container interface to be inherited or mimicked
template<typename TItemLike>
struct List
{
  TItemLike *first, *last;
};

//! Linked-List Item interface to be inherited or mimicked
template<typename TItemLike>
struct ListItem
{
  ListItem<TItemLike>* next, *prev;
};

namespace list {

  //! Add item to list
  template<typename TListLike, typename TItemLike>
  void Add(TListLike& list, TItemLike* item);

  //! Add item to list
  template<typename TListLike, typename TItemLike>
  void Add(TListLike* list, TItemLike* item);

  //! Remove item from a list
  template<typename TListLike, typename TItemLike>
  void Remove(TListLike* list, TItemLike* item);

  //! Remove item from a list
  template<typename TListLike, typename TItemLike>
  void Remove(TListLike& list, TItemLike* item);

  //! Clear all items from a list
  template<typename TListLike>
  void Clear(TListLike* list);

  //! Clear all items from a list
  template<typename TListLike>
  void Clear(TListLike& list);

  //! Count items in a list
  template<typename TListLike>
  uinteger Count(TListLike* list);

  //! Count items in a list
  template<typename TListLike>
  uinteger Count(const TListLike& list);

}} // Stardrive::list


//! Ring Buffer
//! https://github.com/betajaen/Stardrive/blob/master/Documentation/Containers/ring-buffer.md
//!
//! FIFO-style array based upon a Store
//! 
//! Cheat Sheet:
//! 
//! list::Add     -- Add an item to the end of the list
//! list::Remove  -- Remove an item from anywhere in the list
//! list::Clear   -- Clear list
//! list::Count   -- Count number of items in the list
//! 
//! Specalisations:
//! 
//! FixedRingBuffer      -- Ring Buffer based on a Fixed Store aka; int array[4];
//! DynamicRingBuffer    -- Ring Buffer based on a Dynamic Store aka;  int* array;
//! 
namespace Stardrive {

template<typename T, typename TStore>
struct RingBuffer;

//! Array specialisation using a FixedStore a bit like; int array[4];
//! HeapRingBuffer<int>
template<typename T>
using HeapRingBuffer = RingBuffer<T, HeapStore<T>>;

//! Array specialisation using a FixedStore a bit like; int array[4];
//! FixedArray<int, 8>
template<typename T, u32 Capacity>
using FixedRingBuffer = RingBuffer<T, FixedStore<T, Capacity>>;

//! Array specialisation using a Dynamic Store.
//! DynamicArray<int, 8>
template<typename T, u32 Capacity>
using DynamicRingBuffer = RingBuffer<T, DynamicStore<T, Capacity>>;

namespace ringbuffer {

  //! Set the size of the ring buffer
  //! Note: This is Store dependent.
  template<typename T, typename TStore>
  void SetSize(RingBuffer<T, TStore>& buffer, u32 size);
  
  //! Get the size of the ring buffer
  template<typename T, typename TStore>
  u32 Size(const RingBuffer<T, TStore>& buffer);

  //! Get the amount of data to read.
  template<typename T, typename TStore>
  u32 Distance(const RingBuffer<T, TStore>& buffer);

  //! Try and Write to the ring buffer
  template<typename T, typename TStore>
  bool Write(RingBuffer<T, TStore>& buffer, const T& value);

  //! Try and read from the ring buffer
  template<typename T, typename TStore>
  Optional<T> Read(RingBuffer<T, TStore>& buffer);

  //! Pretend to read over the ring buffer the given amount.
  //! Note: Return value is number of items skipped.
  template<typename T, typename TStore>
  u32 TrySkip(RingBuffer<byte, TStore>& buffer, u32 length);

  //! Copy one RingBuffer over another similar RingBuffer
  template<typename T, typename TStore>
  void Copy(RingBuffer<T, TStore>& dst, const RingBuffer<T, TStore>& src);

  //! Move one RingBuffer to another similar RingBuffer
  template<typename T, typename TStore>
  void Move(RingBuffer<T, TStore>& dst, RingBuffer<T, TStore>& src);

  //! Get a pointer to the beginning of data representing the ring buffer
  template<typename T, typename TStore>
  const T* GetData(const RingBuffer<T, TStore>& buffer);
  
  //! Get a const pointer to the beginning of data representing the ring buffer
  template<typename T, typename TStore>
  T* GetData(RingBuffer<T, TStore>& buffer);

} // Stardrive::ringbuffer

template<typename T, typename TStore>
struct RingBuffer : protected TStore
{
  friend void         ringbuffer::SetSize<T, TStore>(RingBuffer<T, TStore>& buffer, u32 size);
  friend const T*     ringbuffer::GetData<T, TStore>(const RingBuffer<T, TStore>& buffer);
  friend T*           ringbuffer::GetData<T, TStore>(RingBuffer<T, TStore>& buffer);
  friend unsigned int ringbuffer::Size<T, TStore>(const RingBuffer<T, TStore>& buffer);

  u32     read, write;

  RingBuffer();
  RingBuffer(const RingBuffer& other);
  RingBuffer(RingBuffer&& other);
  ~RingBuffer();
  
  RingBuffer<T, TStore>& operator=(const RingBuffer& other);
  RingBuffer<T, TStore>& operator=(RingBuffer&& other);
};

} // Stardrive

#endif














#ifndef STARDRIVE_CONTAINERS_IMPL_H
#define STARDRIVE_CONTAINERS_IMPL_H

SRegionDoc(Text="Array implementation")
namespace Stardrive { namespace array {

    template<typename T, typename TStore>
    T* GetData(Array<T, TStore>& a)
    {
      return a.GetData();
    }

    template<typename T, typename TStore>
    const T* GetData(const Array<T, TStore>& a)
    {
      return a.GetData();
    }

    template<typename T, typename TStore>
    bool Empty(const Array<T, TStore>& a)
    {
      return 0 == Size(a);
    }

    template<typename T, typename TStore>
    bool Any(const Array<T, TStore>& a)
    {
      return 0 != Size(a);
    }

    template<typename T, typename TStore>
    bool One(const Array<T, TStore>& a)
    {
      return 1 == Size(a);
    }

    template<typename T, typename TStore>
    bool Many(const Array<T, TStore>& a)
    {
      return 1 < Size(a);
    }

    template<typename T, typename TStore>
    uinteger Size(const Array<T, TStore>& a)
    {
      return a.size;
    }
    
    template<typename T, typename TStore>
    uinteger Capacity(const Array<T, TStore>& a)
    {
      return a.GetSize();
    }

    template<typename T, typename TStore>
    T* Begin(Array<T, TStore>& a)
    {
      return &a.data.GetData()[0];
    }
    
    template<typename T, typename TStore>
    const T* Begin(const Array<T, TStore>& a)
    {
      return &a.data.GetData()[0];
    }

    template<typename T, typename TStore>
    T* End(Array<T, TStore>& a)
    {
      return &a.data.GetData()[a.size - 1];
    }

    template<typename T, typename TStore>
    const T* End(const Array<T, TStore>& a)
    {
      return &a.data.GetData()[a.size - 1];
    }

    template<typename T, typename TStore>
    void Clear(Array<T, TStore>& a)
    {
      memory::DestructItems(GetData(a), a.size);
      a.size = 0;
    }

    template<typename T, typename TStore>
    void Resize(Array<T, TStore>& a, uinteger newSize)
    {
      if (newSize > Capacity(a))
      {
        Grow(a, newSize);
      }
      a.size = newSize;
    }

    template<typename T, typename TStore>
    void Reserve(Array<T, TStore>& a, uinteger newMaxSize)
    {
      if (newMaxSize > Capacity(a))
      {
        SetCapacity(a, Capacity(a));
      }
    }

    template<typename T, typename TStore>
    void Grow(Array<T, TStore>& a, uinteger minMaxSize = 0)
    {
      uinteger newMaxSize = (Capacity(a) * 2) + 8;
      if (newMaxSize < minMaxSize)
      {
        newMaxSize = minMaxSize;
      }
      SetCapacity<T, TStore>(a, newMaxSize);
    }

    template<typename T, typename TStore>
    void SetCapacity(Array<T, TStore>& a, uinteger newCapacity)
    {
      if (newCapacity == Capacity(a))
        return;

      if (newCapacity < a.size)
        Resize<T, TStore>(a, newCapacity);

      if (newCapacity > 0)
      {
        a.Resize(newCapacity);
      }
    }

    template<typename T, typename TStore>
    T* LatePush(Array<T, TStore>& a)
    {
      if (a.size >= Capacity(a))
      {
        Grow<T, TStore>(a);
      }

      T* p = &GetData(a)[a.size];
      ++a.size;
      return p;
    }

    template <typename T, typename TStore>
    void Insert(Array<T, TStore>& a, uinteger index, const T& value)
    {
      if (index >= array::Size(a))
      {
        Push(a, value);
        return;
      }
    
      ShiftRight(a, index);
      GetData(a)[index] = value;
    }

    template<typename T, typename TStore>
    void Push(Array<T, TStore>& a, const T& value)
    {
      if (a.size >= Capacity(a))
      {
        Grow<T, TStore>(a);
      }

      GetData(a)[a.size] = value;
      ++a.size;
    }

    template<typename T, typename TStore>
    void Expand(Array<T, TStore>& a, u32 amount = 1)
    {
      if (a.size + amount >= Capacity(a))
      {
        Grow<T, TStore>(a, a.size + amount);
      }

      a.size += amount;
    }

    template<typename T, typename TStore>
    T Pop(Array<T, TStore>& a)
    {
      SEnsure(a.size > 0);

      memory::DestructItems(GetData(a) + a.size);
      return GetData(a)[a.size--];
    }

    template <typename T, typename TStore>
    void Remove(Array<T, TStore>& a, uinteger index)
    {
      ShiftLeft(a, index);
    }

    template <typename T, typename TStore>
    void RemoveSwap(Array<T, TStore>& a, uinteger index)
    {
      SEnsure(index < a.size);

      memory::DestructItems(GetData(a) + index, 1);
      a[index] = a[a.size - 1];
      --a.size;
    }

    template <typename T, typename TStore>
    void ShiftRight(Array<T, TStore>& a, uinteger index)
    {
      SEnsure(index < a.size);

      if (a.size >= Capacity(a))
      {
        Grow<T, TStore>(a);
      }

      for(u32 ii=index;ii < a.size;ii++)
        a[ii + 1] = a[ii];

      ++a.size;
    }

    template <typename T, typename TStore>
    void ShiftLeft(Array<T, TStore>& a, uinteger index)
    {
      SEnsure(index < a.size);
      
      memory::DestructItems(GetData(a) + index, 1);
      for(u32 ii=index;ii < a.size;ii++)
        a[ii] = a[ii + 1];

      --a.size;
    }

    template<typename T, typename TStore>
    void Copy(Array<T, TStore>& dst, const Array<T, TStore>& src)
    {
      array::SetCapacity(dst, src.size);
      memory::Copy(GetData(dst), GetData(src), src.size * sizeof(T));
    }

    template<typename T, typename TStore>
    void Move(Array<T, TStore>& dst, Array<T, TStore>& src)
    {
      array::Clear(dst);

      dst.elements = src.elements;
      dst.size = src.size;

      src.items = nullptr;
      src.size = 0;
    }

} // Stardrive::array

template <typename T, typename TStore>
Array<T, TStore>::Array()
  : TStore(), size(0)
{
}

template<typename T, typename TStore>
Array<T, TStore>::Array(const Array<T, TStore>& buffer)
  : TStore(), size(0)
{
  array::Copy(*this, buffer);
}

template<typename T, typename TStore>
Array<T, TStore>::Array(Array<T, TStore>&& buffer)
  : TStore(), size(0)
{
  array::Move(*this, buffer);
}

template<typename T, typename TStore>
Array<T, TStore>::~Array()
{
  memory::DestructItems<T>(array::GetData(*this), size);
}

template<typename T, typename TStore>
Array<T, TStore>& Array<T, TStore>::operator=(const Array<T, TStore>& buffer)
{
  array::Copy(*this, buffer);
  return *this;
}

template <typename T, typename TStore>
Array<T, TStore>& Array<T, TStore>::operator=(Array<T, TStore>&& buffer)
{
  array::Move(*this, buffer);
  return *this;
}

template <typename T, typename TStore>
T& Array<T, TStore>::operator[](uinteger idx)
{
  SEnsure(idx < size);
  return array::GetData(*this)[idx];
}

template <typename T, typename TStore>
const T& Array<T, TStore>::operator[](uinteger idx) const
{
  SEnsure(idx < size);
  return array::GetData(*this)[idx];
}

} // Stardrive





SRegionDoc(Text="List implementation")
namespace Stardrive { namespace list {
  template<typename TListLike, typename TItemLike>
  void Add(TListLike* list, TItemLike* item)
  {
    if (list->first == nullptr)
    {
      list->first = list->last = item; 
    }
    else
    {
      list->last->next = item; 
      item->prev = list->last; 
      list->last = item; 
    }
  }

  template<typename TListLike, typename TItemLike>
  void Add(TListLike& list, TItemLike* item)
  {
    Add(&list, item);
  }

  template<typename TListLike, typename TItemLike>
  void Remove(TListLike* list, TItemLike* item)
  {
    if (list->first == item && list->last == item)
    {
      list->first = nullptr; 
      list->last = nullptr; 
    }
    else if (list->first == item) 
    {
      list->first = item->next; 
      list->first->prev = nullptr; 
    }
    else if (list->last == item) 
    {
      list->last = item->prev; 
      list->last->next = nullptr; 
    }
    else
    {
      auto after = item->next; 
      auto before = item->prev; 
      after->prev = before; 
      before->next = after; 
    }
    item->next = nullptr; 
    item->prev = nullptr; 
  }

  template<typename TListLike, typename TItemLike>
  void Remove(TListLike& list, TItemLike* item)
  {
    Remove(*list);
  }
    
  template<typename TListLike>
  void Clear(TListLike* list)
  {
    auto item = list->first;
    while (item != nullptr)
    {
      auto next = item->next;
      remove_func(item);
      item = next;
    }
    list->first = nullptr;
    list->last = nullptr;
  }

  template<typename TListLike>
  void Clear(TListLike& list)
  {
    Clear(&list);
  }
    
  template<typename TListLike>
  uinteger Count(const TListLike* list)
  {
    uinteger count = 0;
    auto item = list->first;
    while (item != nullptr)
    {
        count++;
        item = item->next;
    }
    return count;
  }

  template<typename TListLike>
  uinteger Count(const TListLike& list)
  {
    return Count(&list);
  }

}} // Stardrive::list


SRegionDoc(Text="Ring Buffer Implementation")
namespace Stardrive { namespace ringbuffer {
  
  template<typename T, typename TStore>
  void Copy(RingBuffer<T, TStore>& dst, const RingBuffer<T, TStore>& src)
  {
    dst.data.Resize(src.data.GetCount());
    memory::Copy(&dst.data[0], &src.data[0], src.data.GetCount());
    dst.read  = src.read;
    dst.write = src.write;
  }

  template<typename T, typename TStore>
  void Move(RingBuffer<T, TStore>& dst, RingBuffer<T, TStore>& src)
  {
    dst.data.Resize(src.data.GetCount());
    memory::Copy(&dst.data[0], &src.data[0], src.data.GetCount());
    dst.read  = src.read;
    dst.write = src.write;

    src.data.Resize(0);
    src.read  = 0;
    src.write = 0;
  }

  template<typename T, typename TStore>
  void SetSize(RingBuffer<T, TStore>& buffer, u32 size)
  {
    buffer.Resize(size);
    memory::Zero(GetData(buffer), size * sizeof(T));
    buffer.read = 0;
    buffer.write = 0;
  }
  
  template<typename T, typename TStore>
  u32 Size(const RingBuffer<T, TStore>& buffer)
  {
    return buffer.GetSize();
  }
  
  template<typename T, typename TStore>
  u32 Distance(const RingBuffer<T, TStore>& buffer)
  {
    if (buffer.read < buffer.write)
      return (buffer.write - buffer.read);
    else if (buffer.read > buffer.write)
      return (Size(buffer) - buffer.read) + buffer.write;
    else
      return 0;
  }

  template<typename T, typename TStore>
  bool Write(RingBuffer<T, TStore>& buffer, const T& value)
  {
    u32 next = (buffer.write + 1) % Size(buffer);
      
    if (next == buffer.read)
      return false;
      
    GetData(buffer)[next] = value;
    buffer.write = next;
    return true;
  }
    
  template<typename T, typename TStore>
  Optional<T> Read(RingBuffer<T, TStore>& buffer)
  {
    if (Distance(buffer) == 0)
      return Optional<T>();

    Optional<T> m(buffer.data[buffer.read]);
    buffer.read = (buffer.read + 1) % Size(buffer);
    return m;
  }

  template <typename T, typename TStore>
  u32 TrySkip(RingBuffer<byte, TStore>& buffer, u32 length)
  {
    u32 clamped = Stardrive::Min(Distance(buffer), length);
    buffer.read = buffer.read % Size(buffer);
    return clamped;
  }
  
  template<typename T, typename TStore>
  const T* GetData(const RingBuffer<T, TStore>& buffer)
  {
    return buffer.GetData();
  }
  
  template<typename T, typename TStore>
  T* GetData(RingBuffer<T, TStore>& buffer)
  {
    return buffer.GetData();
  }

} // Stardrive::ringbuffer

template <typename T, typename TStore>
RingBuffer<T, TStore>::RingBuffer()
  : TStore(), read(0), write(0)
{
}

template <typename T, typename TStore>
RingBuffer<T, TStore>::RingBuffer(const RingBuffer& other)
  : TStore(), read(0), write(0)
{
  ringbuffer::Copy(*this, other);
}

template <typename T, typename TStore>
RingBuffer<T, TStore>::RingBuffer(RingBuffer&& other)
  : TStore(), read(0), write(0)
{
  ringbuffer::Move(*this, other);
}

template <typename T, typename TStore>
RingBuffer<T, TStore>::~RingBuffer()
{
  ringbuffer::SetSize(*this, 0);
  read = 0;
  write = 0;
}

template <typename T, typename TStore>
RingBuffer<T, TStore>& RingBuffer<T, TStore>::operator=(const RingBuffer& other)
{
  Copy(this, other);
  return *this;
}

template <typename T, typename TStore>
RingBuffer<T, TStore>& RingBuffer<T, TStore>::operator=(RingBuffer&& other)
{
  Move(this, other);
  return *this;
}
  
} // Stardrive::ringbuffer

#endif
