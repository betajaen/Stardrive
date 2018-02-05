
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
  
  struct Radian;
  struct Degree;
  
  Radian Radians(f32 radians);
  Degree Degrees(f32 degrees);

  struct Radian
  {
  protected:
    f32 rads;
  public:
  
    friend Radian Radians(f32 radians);

    inline Radian() : rads(0) {}
    inline operator Degree() const;

    inline f32     Radians() const
    {
      return rads;
    }

    inline f32 Degrees() const;
  };
  
  struct Degree
  {
  protected:
    f32 degs;
  public:
    friend Degree Degrees(f32 degrees);

    inline Degree() : degs(0) {}
    inline operator Radian() const;

    inline f32 Degrees() const
    {
      return degs;
    }

    inline f32 Radians() const;
  };

  namespace math
  {
    constexpr f32 Pi = 3.1415926535897932384626433832795f;
    
    //! Radians to Degrees
    inline f32 RadToDeg(f32 value)
    {
      return ((value) * 180.0f / Pi);
    }

    //! Degrees to Radians
    inline f32 DegToRad(f32 value)
    {
      return ((value) * Pi / 180.0f);
    }
  }

  inline f32 Radian::Degrees() const
  {
    return math::RadToDeg(rads);
  }

  inline f32 Degree::Radians() const
  {
    return math::DegToRad(degs);
  }
  
  inline Radian Radians(f32 radians)
  {
    Radian rad;
    rad.rads = radians;
    return rad;
  }
  
  inline Degree Degrees(f32 degrees)
  {
    Degree deg;
    deg.degs = degrees;
    return deg;
  }

  inline Radian::operator Degree() const
  {
    return Degree(*this);
  }

  inline Degree::operator Radian() const
  {
    return Radian(*this);
  }

  namespace math
  {
    //! Cosine
    f32 Cos(f32 radians);

    //! Cosine
    inline f32 Cos(const Radian& value)
    {
      return Cos(value.Radians());
    }

    //! Cosine
    inline f32 Cos(const Degree& value)
    {
      return Cos(value.Radians());
    }

    //! Sine
    f32 Sin(f32 radians);

    //! Sine
    inline f32 Sin(const Radian& value)
    {
      return Sin(value.Radians());
    }

    //! Sine
    inline f32 Sin(const Degree& value)
    {
      return Sin(value.Radians());
    }

    //! Cosine/Sine
    void CosSin(f32 radians, f32& c, f32& s);

    //! Cosine/Sine
    inline void CosSin(const Radian& value, f32& c, f32& s)
    {
      return CosSin(value.Radians(), c, s);
    }
    
    //! Cosine/Sine
    inline void CosSin(const Degree& value, f32& c, f32& s)
    {
      return CosSin(value.Radians(), c, s);
    }

    //! Tangent
    f32 Tan(f32 radians);

    //! Tangent
    inline f32 Tan(const Radian& value)
    {
      return Tan(value.Radians());
    }

    //! Tangent
    inline f32 Tan(const Degree& value)
    {
      return Tan(value.Radians());
    }

    //! Squared
    inline f32 Squared(f32 value)
    {
      return value * value;
    }

    //! Square Root
    f32 SquareRoot(f32 value);

    //! Absolute
    f32 Absolute(f32 value);

    //! Ceil
    f32 Ceil(f32 value);

    //! Floor
    f32 Floor(f32 value);

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

#if defined(SStardriveMath)
#ifndef STARDRIVE_MATH_IMPL_H
#define STARDRIVE_MATH_IMPL_H

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
    
    f32 Wrap(f32 value, f32 upper)
    {
      return fmodf(upper + fmodf(value, upper), upper);
    }

    f32 Wrap(f32 value, f32 lower, f32 upper)
    {
      return lower + Wrap(value - lower, upper - lower);
    }
    
    f32 Modulus(f32 _1, f32 _2)
    {
      return fmodf(_1, _2);
    }

    f32 Lerp(f32 _1, f32 _2, f32 alpha)
    {
      return (_1 + alpha * (_2 - _1));
    }

  }
}

#endif
#endif

