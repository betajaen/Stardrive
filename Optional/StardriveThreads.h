/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  -= Threads Option =-                                                                           
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

#ifndef STARDRIVE_THREADS_H
#define STARDRIVE_THREADS_H

#include <Stardrive/Stardrive.h>

namespace Stardrive
{
  
  namespace sync
  {
    struct Semaphore : mixin::NonCopyable
    {
      Opaque<'SEMP'> o;

      Semaphore() = default;
      Semaphore(Semaphore&& s);
      ~Semaphore();
      
      Semaphore& operator=(const Semaphore&& other);
    };

    struct Mutex : mixin::NonCopyable
    {
      Opaque<'MUTX'> o;
      
      Mutex() = default;
      Mutex(Mutex&& m);
      ~Mutex();
      
      Mutex& operator=(const Mutex&& other);
    };
  }

  typedef bool (*ThreadFn)(void* threadFn);

  //! 
  struct Thread : mixin::NonCopyable
  {
    Opaque<'THRD'>  o;

    Thread() = default;
    Thread(Thread&& m);
    ~Thread();
      
    Thread& operator=(const Thread&& other);
  };

  namespace thread
  {
    bool Start(Thread& thread, ThreadFn function, void* functionArguments);

    bool Stop(Thread& thread);

    bool IsRunning(const Thread& thread);
  }

  namespace sync
  {
    void Lock(Mutex& mutex);

    void Unlock(Mutex& mutex);

    void Wait(Semaphore& semaphore);

    void Post(Semaphore& semaphore, u32 count = 1);
  }
  
} // Stardrive

#endif


//#ifdef SStardriveThreads

#if SIsWindows
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace Stardrive
{
  namespace sync
  {
    namespace impl
    {
      struct MutexData
      {
#if SIsWindows
        CRITICAL_SECTION cs;
#else
        i32 padding;
#endif
      };
      struct SemaphoreData
      {
#if SIsWindows
        HANDLE s;
#else
        i32 padding;
#endif
      };
    }
  }

  namespace thread
  {
    namespace impl
    {
      struct ThreadData
      {
#if SIsWindows
        HANDLE          handle;
        ThreadFn        function;
        void*           functionArguments;
        bool            isRunning;
        sync::Semaphore semaphore;
#else
        i32 padding;
#endif
      };


#if SIsWindows
      static DWORD WINAPI ThreadProcess(void* threadObject)
      {
        ThreadData* data = (ThreadData*) threadObject;
        sync::Post(data->semaphore);
        return data->function(data->functionArguments);
      }
#endif
    }
    
    bool Start(Thread& thread, ThreadFn function, void* functionArguments)
    {
      if (thread.o.IsSet())
        return false;
      
      impl::ThreadData* data = new impl::ThreadData();
      
#if SIsWindows
      SEnsure(INVALID_HANDLE_VALUE == thread.handle);
#endif

      SEnsure(IsRunning(thread));
      SEnsure(function != nullptr);

      thread.function           = function;
      thread.functionArguments  = functionArguments;
#if SIsWindows
      thread.handle = CreateThread(nullptr, 0, impl::ThreadProcess, &thread, 0, nullptr);
      if (nullptr == thread.handle)
        return false;
      thread.isRunning = true;
      sync::Wait(thread.semaphore);
      return true;
#else
      return false;
#endif
    }

    bool Stop(Thread& thread)
    {
      SEnsure(IsRunning(thread));

#if SIsWindows
      SEnsure(INVALID_HANDLE_VALUE != thread.handle);
      WaitForSingleObject(thread.handle, INFINITE);
      CloseHandle(thread.handle);
      thread.handle = INVALID_HANDLE_VALUE;
      thread.isRunning = false;
#endif

      return IsRunning(thread);
    }

    bool IsRunning(const Thread& thread)
    {
      return !!thread.isRunning;
    }
    
  }
  
  inline Thread::Thread(Thread&& m)
  {
    o = m.o;
    m.o.opaque = 0;
  }

  inline Thread::~Thread()
  {
    if (o.IsSet())
    {
      thread::impl::Dispose(o);
    }
  }
}

//#endif
