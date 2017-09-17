Macros and Constants
====================

Platform
--------

| Macro                 | Options          |                                                                  |
|-----------------------|------------------|------------------------------------------------------------------|
| `SArchitecture`       | 32, 64           | Compiler Architecture; i.e. 32-bit or 64-bit                     |
| `SIsDebug`            | 0, 1             | Compiler Built in Debug Mode                                     |
| `SIsRelease`          | 0, 1             | Compiler Built in Release (not Debug) Mode                       |
| `SIsWindows`          | 0, 1             | Is Compiling for Microsoft Windows?                              |
| `SIsApple`            | 0, 1             | Is Compiling for Apple iOS or Apple macOS?                       |
| `SIsLinux`            | 0, 1             | Is Compiling for Linux or UNIX-like Operating System             |
| `SIsVisualStudio`     | 0, 1, 2015, 2017 | Is the Compiler Microsoft Visual Studio? And if so what version? |
| `SIsClang`            | 0, 1             | Is the Compiler Clang?                                           |
| `SIsGcc`              | 0, 1             | Is the Compiler GCC?                                             |

```cpp
int main()
{
#if SIsWindows
  printf("I am on Windows");
#else
  printf("I am not on Windows");
#endif
}
```

Macro Shortcuts
---------------

| Macro                 |                                           |
|-----------------------|-------------------------------------------|
| `SToStr(x)`           | Turn given argument into a string literal |
| `SNoClass(CLASS)`     | Prevent Class being copied                |
| `SNoMove(CLASS)`      | Prevent Class being moved                 |

```cpp
struct Mutex
{
  SNoClass(Mutex);
  SNoMove(Mutex);
  
  Mutex();
  ~Mutex();

#if SIsWindows
  CRITICAL_SECTION cs;
#endif
};
```
