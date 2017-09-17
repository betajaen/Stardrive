Basic Usage
===========

To start just include Stardrive normally:

```c++
#include <Stardrive/Stardrive.h>
```

Stardrive should also be implemented in a single `.cpp` source file, at the top - only do this once.

```c++
#define SStardrive
#include <Stardrive/Stardrive.h>
```

Then you can use Stardrive normally

```c++
int main()
{
  int x = Stardrive::hash::fnv1a("Hello World!");
}
```
