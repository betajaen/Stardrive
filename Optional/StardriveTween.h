/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  -= Tween Option =-                                                                           
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

#ifndef STARDRIVE_TWEEN_H
#define STARDRIVE_TWEEN_H

#include <Stardrive/Stardrive.h>
#include <Stardrive/Optional/StardriveMath.h>


//! Tweening functions
//! Based upon easing functions by Robert Penner http://www.robertpenner.com/
//! 
//! Tweening functions will operate on any type that implements the 'numeric' class.
//! These are by default:
//!   u8,u16,u32,u64
//!   i8,i16,i32,i64
//!   f32,f64
//!   Vector (from Stardrive/Optional/StardriveVector.h)
//! 
namespace Stardrive
{
  namespace tween
  {
    template<typename T>
    inline T Linear(const T& _1, const T& _2, f32 a)
    {
      typedef numeric<T> N;
      return N::AddMul(_1, N::Value(a), N::Sub(_2, _1));
    }

    template<typename T>
    inline T EaseInQuad(T _1, T _2, f32 a)
    {
      typedef numeric<T> N;
      
      T b  = N::Sub(_2, _1);
      T aa = N::Value(a);

      return N::Add(N::Mul(b, aa, aa), _1);
    }

    template<typename T>
    inline T EaseOutQuad(T _1, T _2, f32 a)
    {
      typedef numeric<T> N;
      
      T b   = N::Negate(N::Sub(_2, _1));
      T aa  = N::Value(a);
      T aa2 = N::Sub(aa, N::Value(2));
      
      return N::Add(N::Mul(b, aa, aa2), _1);
    }

    template<typename T>
    inline T EaseInOutQuad(T _1, T _2, f32 a)
    {
      typedef numeric<T> N;

      a *= 0.5f;

      T b = N::Sub(_2, _1);
      if (a < 1.0f)
      {
        return N::Add(
          N::Mul(
            N::Div(_1, 2),
            N::Value(a),
            N::Value(a)
          ),
          _1
        );
      }
      a -= 1.0f;
    }

  }
}

#endif
