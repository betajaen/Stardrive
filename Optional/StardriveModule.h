/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  -= Module Option =-                                                                           
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

#ifndef STARDRIVE_MODULE_H
#define STARDRIVE_MODULE_H

#include <Stardrive/Stardrive.h>

//! Module
//! https://github.com/betajaen/Stardrive/blob/master/Documentation/module.md
//! 
//! Loading and unloading shared libraries at runtime. Could be used for live-code reloading.
//!
//! Cheat Sheet:
//! 
//! Module module;
//! 
//! module::Open    -- Open the library
//! module::Close   -- Close the library
//! module::Call    -- Call a function in the library
//! SModuleFunction -- Macro declare a callable function in the shared library
//! 
//! #define SStardriveModule before including StardriveModule.h in executable.
//! 
#if SIsWindows
  #define SModuleFunction(RETURN, NAME, ...) \
    extern "C" __declspec(dllexport) RETURN NAME(__VA_ARGS__)
#else
  #define SModuleFunction(RETURN, NAME, ...) \
    RETURN NAME(__VA_ARGS__)
#endif

namespace Stardrive
{
  typedef Opaque<'hMOD'> Module;
  
  namespace module
  {
    //! Maybe open a library
    inline Optional<Module> Open(const char* name);

    //! Close a module
    inline bool Close(Module& library);
    
    //! Call a module function that has been defined by the 'SModuleFunction' macro
    //! Note: This is used for calling entry points for setting up/tearing down the module.
    template<typename T, typename TReturn = void>
    inline Optional<TReturn> Call(const Module& library, const char* entryPoint, T argument);
  }
}

#endif

#ifdef SStardriveModule

#if SIsWindows
  #include <Windows.h>
#endif

namespace Stardrive
{
  namespace module
  {
    namespace impl
    {
      #if SIsWindows == 1
      Optional<Module> LoadModule(const char* name)
      {
        HMODULE hInstance = LoadLibrary(name);
        if (hInstance == nullptr)
          return Optional<Module>::False();

        Module module;
        module.Acquire(hInstance);
        return Optional<Module>::True(module);
      }
      bool UnloadModule(Module& module)
      {
        HMODULE hInstance = module.Cast<HMODULE>();

        if (hInstance == NULL)
          return false;

        module.opaque = 0;
        return !!FreeLibrary(hInstance);
      }
      template<typename TReturn, typename TArg>
      struct CallModuleFunction
      {
        static Optional<TReturn> Call(const Module& module, const char* name, TArg arg)
        {
          typedef TReturn (__cdecl *EntryFunction)(TArg);
          
          HMODULE hInstance = module.Cast<HMODULE>();
          if (hInstance == nullptr)
            return Optional<TReturn>::False();

          EntryFunction moduleEntry = (EntryFunction) GetProcAddress(hInstance, name);

          if (moduleEntry == nullptr)
            return Optional<TReturn>::False();

          return Optional<TReturn>::True(moduleEntry(arg));
        }
      };
      template<typename TArg>
      struct CallModuleFunction<void, TArg>
      {
        static Optional<void> Call(const Module& module, const char* name, TArg arg)
        {
          typedef void (__cdecl *EntryFunction)(TArg);
          
          HMODULE hInstance = module.Cast<HMODULE>();
          if (hInstance == nullptr)
            return Optional<void>::False();

          EntryFunction moduleEntry = (EntryFunction) GetProcAddress(hInstance, name);

          if (moduleEntry == nullptr)
            return Optional<void>::False();
          
          moduleEntry(arg);
          return Optional<void>::True();
        }
      };
      #endif
    }

    inline Optional<Module> Open(const char* name)
    {
      return impl::LoadModule(name);
    }

    inline bool Close(Module& library)
    {
      return impl::UnloadModule(library);
    }

    template<typename T, typename TReturn>
    inline Optional<TReturn> Call(Module& library, const char* entryPoint, T arg)
    {
      return impl::CallModuleFunction<TReturn, T>::Call(library, entryPoint, arg);
    }

  }
}

#endif
