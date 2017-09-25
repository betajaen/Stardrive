Module
======

The module optional addon provides a platform independent way of loading shared libraries into the executable at runtime. 

One purpose for this to allow module hotswapping for live code reloading.

Minimal example setting up
--------------------------

In; `MyProject/SharedLib/main.cpp`

```cpp
#include <Stardrive/Optional/StardriveModule.h>

SModuleFunction(int, AddOne, int x)
{
  return x + 1;
}
```

In; `MyProject/MainExecutable/main.cpp`

```cpp
#define SStardriveModule
#include <Stardrive/Optional/StardriveModule.h>

using namespace Stardrive;

void main()
{
  Optional<Module> mod = module::Open("SharedLib");

  if (mod.IsSet())
  {
    int value = module::Call<int, int>(mod, "AddOne", 3); // -> 4
    
    module::Close(mod);
  }
}

```


Live-Code reloading example
===========================

A good usage of the module optional is to introduce live code reloading; such as in a computer game, the Game Engine running as an executable will run the game code represented as a shared library. The game can be unloaded and reloaded when the code for the game is recompiled.

One way of doing this, is using an interface class of function pointers to pass to the shared library when it is started. The interface can work bi-directionally by passing in engine functions, game event functions and shared global variables.

This could be presented in the Engine executable as:

```
#define SStardriveModule
#include <Stardrive/Optional/StardriveModule.h>

typedef void (*UpdateFunction)(f32 deltaTime);

struct EngineInterface
{
  bool exit;
  void (*PutSprite)(i32 x, i32 y, const char* spriteName);
  bool (*KeyDown)(char key);
  void (*OnUpdate)(UpdateFunction);
};

f32 kDeltaTime = 1.0f / 60.0f;
void PutSprite(i32 x, i32 y, const char* spriteName);
bool KeyDown(char key);

void LoadGame()
{
  EngineInterface engine;
  engine.exit      = false;
  engine.PutSprite = PutSprite;
  engine.KeyDown   = KeyDown;
  engine.OnUpdate  = nullptr;
  
  Optional<Module> game = module::Load("Game");
  if (game.IsSet())
  {
    
    module::Call<EngineInterface*>(game, "Setup", &engine);
    
    while(engine.exit == false)
    {
      if (engine.OnUpdate)
      {
        engine.OnUpdate(kDeltaTime);
      }
      WaitFrame();
    }

    module
  }
}
```

And implemented in the Game shared library as so:

```
#include <Stardrive/Optional/StardriveModule.h>
#include <Engine.h>

EngineInterface* engine;

i32 x = 0, y = 0;

void Update()
{
  if (engine->KeyDown('Q'))
    engine->quit = true;
  engine->PutSprite(x, y, 'flower');
}

SModuleFunction(void, Setup, EngineInterface* e)
{
  engine = e;
  engine->OnUpdate = Update;
}
```
