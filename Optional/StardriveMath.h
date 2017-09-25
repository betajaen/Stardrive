
/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  -= Math Option =-                                                                           
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

#ifndef STARDRIVE_MATH_H
#define STARDRIVE_MATH_H

#include <Stardrive/Stardrive.h>

namespace Stardrive
{
  namespace math
  {
    constexpr f32 Pi = 3.1415926535897932384626433832795f;

    //! Radians to Degrees
    inline f32 RadToDeg(f32 value)
    {
      return ((value) * 180.0f / Pi);
    }

    inline f32 DegToRad(f32 value)
    {
      return ((value) * Pi / 180.0f);
    }

    //! Cosine
    f32 Cos(f32 value);

    //! Sine
    f32 Sin(f32 value);

    //! Cosine/Sine
    void CosSin(f32 value, f32& c, f32& s);

    //! Tan
    f32 Tan(f32 value);

    //! Squared
    f32 Squared(f32 value);

    //! Square Root
    f32 SquareRoot(f32 value);

    //! Absolute
    f32 Absolute(f32 value);

    //! Ceil
    f32 Ceil(f32 value);

    //! Floor
    f32 Floor(f32 value);

    //! Min
    f32 Min(f32 _1, f32 _2);

    //! Min
    f32 Min(f32 _1, f32 _2, f32 _3);

    //! Max
    f32 Max(f32 _1, f32 _2);

    //! Max
    f32 Max(f32 _1, f32 _2, f32 _3);

    //! Clamp
    f32 Clamp(f32 value, f32 lower, f32 upper);

    //! Wrap
    f32 Wrap(f32 value, f32 upper);

    //! Wrap
    f32 Wrap(f32 value, f32 lower, f32 upper);
    
    //! Modulus
    f32 Modulus(f32 _1, f32 _2);

    //! Lerp
    f32 Lerp(f32 _1, f32 _2, f32 alpha);

  }
}

#endif

#ifdef SStardriveMath

#include <math.h>

namespace Stardrive
{
  namespace math
  {
    f32 Cos(f32 value)
    {
      return ::cosf(value);
    }

    f32 Sin(f32 value)
    {
      return ::sinf(value);
    }

    void CosSin(f32 value, f32& c, f32& s)
    {
      c = Cos(value);
      s = Sin(value);
    }

    f32 Tan(f32 value)
    {
      return ::tanf(value);
    }
    
    f32 Squared(f32 value)
    {
      return value * value;
    }

    f32 SquareRoot(f32 value)
    {
      return ::sqrtf(value);
    }

    f32 Absolute(f32 value)
    {
      return ::fabsf(value);
    }

    f32 Ceil(f32 value)
    {
      return ::ceilf(value);
    }

    f32 Floor(f32 value)
    {
      return ::floorf(value);
    }

    f32 Min(f32 _1, f32 _2)
    {
      return fminf(_1, _2);
    }

    f32 Min(f32 _1, f32 _2, f32 _3)
    {
      return Min(_1, Min(_2, _3));
    }
    
    f32 Min(f32 _1, f32 _2, f32 _3, f32 _4)
    {
      return Min(_1, Min(_2, Min(_3, _4)));
    }

    f32 Max(f32 _1, f32 _2)
    {
      return fmaxf(_1, _2);
    }

    f32 Max(f32 _1, f32 _2, f32 _3)
    {
      return Max(_1, Max(_2, _3));
    }
    
    f32 Max(f32 _1, f32 _2, f32 _3, f32 _4)
    {
      return Max(_1, Max(_2, Max(_3, _4)));
    }

    f32 Clamp(f32 value, f32 lower, f32 upper)
    {
      return Min(lower, Max(value, upper));
    }
    
    f32 Modulus(f32 _1, f32 _2)
    {
      return fmodf(_1, _2);
    }

    f32 Wrap(f32 value, f32 upper)
    {
      return fmodf(upper + fmodf(value, upper), upper);
    }

    f32 Wrap(f32 value, f32 lower, f32 upper)
    {
      return lower + Wrap(value - lower, upper - lower);
    }
    
    f32 Lerp(f32 _1, f32 _2, f32 alpha)
    {
      return (_1 + alpha * (_2 - _1));
    }

  }
}

#endif
