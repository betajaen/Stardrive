/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  -= File Option =-                                                                           
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

#ifndef STARDRIVE_HASH_H
#define STARDRIVE_HASH_H

#include <Stardrive/Stardrive.h>

namespace Stardrive
{

  typedef Hidden<'FILE'> File;

  namespace file
  {
    namespace FileAccess
    {
      enum Enum
      {
        Read      = 0,
        ReadWrite = 1,
        Create    = 2
      };
    }

    namespace FileRelativePosition
    {
      enum Enum
      {
        Begin,
        Current,
        End
      };
    }
    
    //! Maybe open a file
    Optional<File> Open(const char* path, FileAccess::Enum access);

    //! Maybe close an opened file.
    bool Close(File& file);

    //! Is a file open?
    bool IsOpen(const File& file);

    //! Maybe set file size either increasing the file size, or trucating existing data.
    bool SetSize(File& file, u64 size);

    //! Maybe get the file size
    Optional<u64> GetSize(const File& file);

    //! Maybe get the current write/read position in the file
    Optional<u64> GetPosition(const File& file);

    //! Maybe set the current write/read position in the file
    bool SetPosition(File& file, u64 position);

    //! Maybe set the current relative write/read position in the file
    bool SetRelativePosition(File& file, u64 position, FileRelativePosition::Enum relativePosition);

    //! Maybe read an amount of bytes from the file, increase read/write position by read amount and return number of bytes read
    Optional<u64> ReadBytes(File& file, byte* data, u64 length);

    //! Maybe write an amount of bytes to the file, increase read/write position by write amount and return number of bytes wrote
    Optional<u64> WriteBytes(File& file, const byte* data, u64 length);

  }
} // Stardrive::file

#endif

#if SIsWindows
#include <Windows.h>
#endif

namespace Stardrive
{
namespace file
{
  
  struct FileData
  {
#if SIsWindows
    HANDLE handle;
#endif
    mutable u64 position;
  };
  
    Optional<File> Open(const char* path, FileAccess::Enum access)
    {
#if SIsWindows
      DWORD  a;
      
      if (FileAccess::Read == access)
        a = GENERIC_READ;
      else
        a = GENERIC_READ  | GENERIC_WRITE;

      DWORD c;

      if (FileAccess::Create == access)
        c = CREATE_ALWAYS;
      else
        c = OPEN_EXISTING;
      
      HANDLE handle = CreateFile(path, a, FILE_SHARE_READ, nullptr, c, FILE_ATTRIBUTE_NORMAL, nullptr);

      if (INVALID_HANDLE_VALUE == handle)
        return Optional<File>::False();

      FileData* data = new FileData();
      data->handle   = handle;
      data->position = 0;

      File file;
      file.opaque.Acquire(data);

      return Optional<File>::True(file);
#else
      return Optional<File>::False();
#endif
    }

    bool Close(File& file)
    {
      if (IsOpen(file))
      {
#if SIsWindows
        FileData* data = file.opaque.Cast<FileData*>();
        CloseHandle(data->handle);
        delete data;
        file.opaque.SetDefault();
        return true;
#endif
      }
      return false;
    }

    bool IsOpen(const File& file)
    {
      return file.opaque.IsSet();
    }

    bool SetSize(File& file, u64 size)
    {
      if (false == IsOpen(file))
        return false;

#if SIsWindows
      FileData* data = file.opaque.Cast<FileData*>();

      LARGE_INTEGER endPosition;
      endPosition.QuadPart = size;
      
      SetFilePointerEx(data->handle, endPosition, nullptr, FILE_BEGIN);
      SetEndOfFile(data->handle);
      return true;
#else
      return Optional<u64>::False();
#endif
    }
    
    Optional<u64> GetSize(const File& file)
    {
      if (false == IsOpen(file))
        return Optional<u64>::False();
#if SIsWindows
      FileData* data = file.opaque.Cast<FileData*>();

      LARGE_INTEGER size;
      GetFileSizeEx(data->handle, &size);
      return Optional<u64>::True((u64) size.QuadPart);
#else
      return Optional<u64>::False();
#endif
    }

    Optional<u64> GetPosition(const File& file)
    {
      if (false == IsOpen(file))
        return Optional<u64>::False();
#if SIsWindows
      FileData* data = file.opaque.Cast<FileData*>();

      return Optional<u64>((u64) data->position);
#else
      return Optional<u64>::False();
#endif
    }

    bool SetPosition(const File& file, u64 position)
    {
      if (IsOpen(file))
      {
#if SIsWindows
        FileData* data = file.opaque.Cast<FileData*>();
        data->position = position;
        return true;
#endif
      }
      return false;
    }

    bool SetPosition(const File& file, i64 position, FileRelativePosition::Enum relativeTo)
    {
      if (IsOpen(file))
      {
#if SIsWindows
        FileData* data = file.opaque.Cast<FileData*>();
        
        if (FileRelativePosition::Begin == relativeTo)
          data->position = position;
        else if (FileRelativePosition::Current == relativeTo)
          data->position += position;
        else if (FileRelativePosition::End == relativeTo)
          data->position = GetSize(file).value - position;
        else
          return false;

        return true;
#endif
      }
      return false;
    }

    Optional<u32> ReadBytes(const File& file, byte* data, u32 length)
    {
      if (IsOpen(file))
      {
#if SIsWindows
        SAssert(length <= numeric<u32>::Max, "Capacity to big for Windows");
        
        FileData* fdData = file.opaque.Cast<FileData*>();

        LARGE_INTEGER readPosition;
        DWORD readSize;
        readPosition.QuadPart = fdData->position;
        
        SetFilePointerEx(fdData->handle, readPosition, nullptr, FILE_BEGIN);
        
        if (::ReadFile(fdData->handle, data, length, &readSize, nullptr))
        {
          fdData->position += readSize;
          return Optional<u32>::True((u32) readSize);
        }
#endif
      }
      return Optional<u32>::False();
    }

    Optional<u64> WriteBytes(File& file, const byte* data, u64 length)
    {
      if (IsOpen(file))
      {
#if SIsWindows
        SAssert(length <= numeric<u32>::Max, "Length to big for Windows");
        
        FileData* fdData = file.opaque.Cast<FileData*>();

        LARGE_INTEGER writePosition;
        DWORD         writeSize;

        writePosition.QuadPart = fdData->position;
        SetFilePointerEx(fdData->handle, writePosition, nullptr, FILE_BEGIN);

        if (::WriteFile(fdData->handle, data, length, &writeSize, nullptr))
        {
          fdData->position += length;
          return Optional<u64>::True((u64) writeSize);
        }
#endif
      }
      return Optional<u64>::False();
    }

}} // Stardrive::file
