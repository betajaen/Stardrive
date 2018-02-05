/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  -= Vector Option =-                                                                           
                                                                                                    
  (c) Robin Southern 2017 https://github.com/betajaen/stardrive https://opensource.org/licenses/MIT 
                                                                                                    
*/

#ifndef STARDRIVE_VECTOR_H
#define STARDRIVE_VECTOR_H

#include <Stardrive/Stardrive.h>
#include <Stardrive/Optional/StardriveMath.h>

namespace Stardrive
{

  struct Vector
  {
    union
    {
      f32 m[4];
      struct { f32 x, y, z, w;         };
      struct { f32 right, up, forward; };
    };
    
    inline f32* Ptr()             { return &m[0]; }
    inline const f32* Ptr() const { return &m[0]; }
  };

  struct Quaternion
  {
    union
    {
      f32 m[4];
      struct { f32 x, y, z, w; };
    };

    inline f32* Ptr()             { return &m[0]; }
    inline const f32* Ptr() const { return &m[0]; }
  };

  struct Matrix
  {
    union
    {
      f32 m[16];
      f32 M[4][4];
      struct { Vector rot[3]; Vector pos; };
    };

    inline f32* Ptr()             { return &m[0]; }
    inline const f32* Ptr() const { return &m[0]; }
  };

}


namespace Stardrive
{
  namespace vector
  {
    inline void Forward(Vector& v)
    {
      v.forward = 1;
      v.right   = 0;
      v.up      = 0;
    }
    inline void Right(Vector& v)
    {
      v.right   = 1;
      v.forward = 0;
      v.up      = 0;
    }
    inline void Up(Vector& v)
    {
      v.up      = 1;
      v.forward = 0;
      v.right   = 0;
    }
    inline void Set(Vector& v, f32 x = 0, f32 y = 0, f32 z = 0, f32 w = 1)
    {
      v.x = x;
      v.y = y;
      v.z = z;
      v.w = w;
    }
    inline Vector Value(f32 x = 0, f32 y = 0, f32 z = 0, f32 w = 1)
    {
      Vector v;
      v.x = x;
      v.y = y;
      v.z = z;
      v.w = w;
      return v;
    }
    inline Vector Expand(f32 x)
    {
      return Value(x,x,x);
    }
    inline Vector Negate(const Vector& v)
    {
      return Value(-v.x, -v.y, -v.z, v.w);
    }
    inline Vector Add(const Vector& _1, const Vector& _2)
    {
      return Value(_1.x + _2.x, _1.y + _2.y, _1.z + _2.z);
    }
    inline Vector Sub(const Vector& _1, const Vector& _2)
    {
      return Value(_1.x - _2.x, _1.y - _2.y, _1.z - _2.z);
    }
    inline Vector Mul(const Vector& _1, const Vector& _2)
    {
      return Value(_1.x * _2.x, _1.y * _2.y, _1.z * _2.z);
    }
    inline Vector Mul(const Vector& v, f32 s)
    {
      return Value(v.x * s, v.y * s, v.z * s);
    }
    inline Vector Div(const Vector& _1, const Vector& _2)
    {
      return Value(_1.x / _2.x, _1.y / _2.y, _1.z / _2.z);
    }
    inline Vector Div(const Vector& v, f32 s)
    {
      return Value(v.x / s, v.y / s, v.z / s);
    }
    inline f32 Dot(const Vector& _1, const Vector& _2)
    {
      return (_1.x * _2.x) + (_1.y * _2.y) + (_1.z * _2.z);
    }
    inline Vector Cross(const Vector& _1, const Vector& _2)
    {
      return Value(
        _1.y * _2.z - _1.z * _2.y,
        _1.z * _2.x - _1.x * _2.z,
        _1.x * _2.y - _1.y * _2.x
      );
    }
    inline f32 Length2(const Vector& v)
    {
      return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
    }
    inline f32 Length(const Vector& v)
    {
      return math::SquareRoot(Length2(v));
    }
    inline Vector Normalise(const Vector& v)
    {
      return Mul(v, 1.0f / Length(v));
    }
    inline bool NotZero(const Vector& v)
    {
      return Length2(v) > 0.0f;
    }
    inline bool IsZero(const Vector& v)
    {
      return !NotZero(v);
    }
    inline Vector Direction(f32 x, f32 y, f32 z)
    {
      return Normalise(Value(x, y, z));
    }
  }
  
  namespace quaternion
  {
    inline void Set(Quaternion& q, f32 x, f32 y, f32 z, f32 w)
    {
      q.x = x;
      q.y = y;
      q.z = z;
      q.w = w;
    }
    inline Quaternion Value(f32 x = 0, f32 y = 0, f32 z = 0, f32 w = 1)
    {
      Quaternion q;
      q.x = x;
      q.y = y;
      q.z = z;
      q.w = w;
      return q;
    }
    inline Quaternion Value(f32 angle, Vector axis)
    {
      const f32 halfAngle = angle * 0.5f;
      const f32 c = math::Cos(halfAngle);
      const f32 s = math::Sin(halfAngle);

      return Value(axis.x * s, axis.y * s, axis.z * s, c);
    }
    inline Quaternion Identity()
    {
      return Value(0,0,0,1);
    }
    inline void AngleAxisX(Quaternion& q, f32 angle)
    {
      const f32 halfAngle = angle * 0.5f;
      const f32 c = math::Cos(halfAngle);
      const f32 s = math::Sin(halfAngle);

      return Set(q, s, 0, 0, c);
    }
    inline void AngleAxisY(Quaternion& q, f32 angle)
    {
      const f32 halfAngle = angle * 0.5f;
      const f32 c = math::Cos(halfAngle);
      const f32 s = math::Sin(halfAngle);

      return Set(q, 0, s, 0, c);
    }
    inline void AngleAxisZ(Quaternion& q, f32 angle)
    {
      const f32 halfAngle = angle * 0.5f;
      const f32 c = math::Cos(halfAngle);
      const f32 s = math::Sin(halfAngle);

      return Set(q, 0, 0, s, c);
    }
    inline Quaternion Mul(const Quaternion& a, const Quaternion& b)
    {
      return Value(
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
      );
    }
    inline Quaternion Invert(const Quaternion& v)
    {
      return Value(-v.x, -v.y, -v.z, v.w);
    }
    inline Vector Rotate(const Quaternion& q, const Vector& v)
    {
      Quaternion tmp0 = Invert(q);
      Quaternion qv;
      Set(qv, v.x, v.y, v.z, 0.0f);

      Quaternion tmp1;
      tmp1 = Mul(tmp0, qv);
      
      return vector::Value(
        tmp1.w * q.x + tmp1.x * q.w + tmp1.y * q.z - tmp1.z * q.y,
        tmp1.w * q.y - tmp1.x * q.z + tmp1.y * q.w + tmp1.z * q.x,
        tmp1.w * q.z + tmp1.x * q.y - tmp1.y * q.x + tmp1.z * q.w
      );
    }
  }
  
  namespace math
  {
    inline Vector Lerp(const Vector& _1, const Vector& _2, f32 alpha)
    {
      return vector::Value(
        Lerp(_1.x, _2.x, alpha),
        Lerp(_1.y, _2.y, alpha),
        Lerp(_1.z, _2.z, alpha)
      );
    }
    inline Vector Min(const Vector& _1, const Vector& _2)
    {
      return vector::Value(
        Stardrive::Min(_1.x, _2.x),
        Stardrive::Min(_1.y, _2.y),
        Stardrive::Min(_1.z, _2.z)
      );
    }
    inline Vector Min(const Vector& _1, const Vector& _2, const Vector& _3)
    {
      return Min(_1, Min(_2, _3));
    }
    inline Vector Max(const Vector& _1, const Vector& _2)
    {
      return vector::Value(
        Stardrive::Max(_1.x, _2.x),
        Stardrive::Max(_1.y, _2.y),
        Stardrive::Max(_1.z, _2.z)
      );
    }
    inline Vector Max(const Vector& _1, const Vector& _2, const Vector& _3)
    {
      return Max(_1, Max(_2, _3));
    }
  }

  namespace matrix
  {
    inline void Set(Matrix& m, 
      f32 _00, f32 _01, f32 _02, f32 _03,
      f32 _10, f32 _11, f32 _12, f32 _13,
      f32 _20, f32 _21, f32 _22, f32 _23,
      f32 _30, f32 _31, f32 _32, f32 _33
    )
    {
      m.M[0][0] = _00; m.M[0][1] = _01; m.M[0][2] = _02; m.M[0][3] = _03;
      m.M[1][0] = _10; m.M[1][1] = _11; m.M[1][2] = _12; m.M[1][3] = _13;
      m.M[2][0] = _20; m.M[2][1] = _21; m.M[2][2] = _22; m.M[2][3] = _23;
      m.M[3][0] = _30; m.M[3][1] = _31; m.M[3][2] = _32; m.M[3][3] = _33;
    }
    inline void Identity(Matrix& m)
    {
      Set(m, 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    }
    inline void Zero(Matrix& m)
    {
      Set(m, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);
    }
    inline Matrix Inverse(const Matrix& m)
    {
      f32 det = 0.0f;
      det += m.M[0][0] * (m.M[1][1]*(m.M[2][2]*m.M[3][3] - m.M[2][3]*m.M[3][2]) - m.M[1][2]*(m.M[2][1]*m.M[3][3] - m.M[2][3]*m.M[3][1]) + m.M[1][3]*(m.M[2][1]*m.M[3][2] - m.M[2][2]*m.M[3][1]) );
      det -= m.M[0][1] * (m.M[1][0]*(m.M[2][2]*m.M[3][3] - m.M[2][3]*m.M[3][2]) - m.M[1][2]*(m.M[2][0]*m.M[3][3] - m.M[2][3]*m.M[3][0]) + m.M[1][3]*(m.M[2][0]*m.M[3][2] - m.M[2][2]*m.M[3][0]) );
      det += m.M[0][2] * (m.M[1][0]*(m.M[2][1]*m.M[3][3] - m.M[2][3]*m.M[3][1]) - m.M[1][1]*(m.M[2][0]*m.M[3][3] - m.M[2][3]*m.M[3][0]) + m.M[1][3]*(m.M[2][0]*m.M[3][1] - m.M[2][1]*m.M[3][0]) );
      det -= m.M[0][3] * (m.M[1][0]*(m.M[2][1]*m.M[3][2] - m.M[2][2]*m.M[3][1]) - m.M[1][1]*(m.M[2][0]*m.M[3][2] - m.M[2][2]*m.M[3][0]) + m.M[1][2]*(m.M[2][0]*m.M[3][1] - m.M[2][1]*m.M[3][0]) );

      f32 invDet = 1.0f / det;

      Matrix v;
      v.m[ 0] = +(m.M[1][1]*(m.M[2][2]*m.M[3][3] - m.M[3][2]*m.M[2][3]) - m.M[1][2]*(m.M[2][1]*m.M[3][3] - m.M[3][1]*m.M[2][3]) + m.M[1][3]*(m.M[2][1]*m.M[3][2] - m.M[3][1]*m.M[2][2])) * invDet;
      v.m[ 1] = -(m.M[0][1]*(m.M[2][2]*m.M[3][3] - m.M[3][2]*m.M[2][3]) - m.M[0][2]*(m.M[2][1]*m.M[3][3] - m.M[3][1]*m.M[2][3]) + m.M[0][3]*(m.M[2][1]*m.M[3][2] - m.M[3][1]*m.M[2][2])) * invDet;
      v.m[ 2] = +(m.M[0][1]*(m.M[1][2]*m.M[3][3] - m.M[3][2]*m.M[1][3]) - m.M[0][2]*(m.M[1][1]*m.M[3][3] - m.M[3][1]*m.M[1][3]) + m.M[0][3]*(m.M[1][1]*m.M[3][2] - m.M[3][1]*m.M[1][2])) * invDet;
      v.m[ 3] = -(m.M[0][1]*(m.M[1][2]*m.M[2][3] - m.M[2][2]*m.M[1][3]) - m.M[0][2]*(m.M[1][1]*m.M[2][3] - m.M[2][1]*m.M[1][3]) + m.M[0][3]*(m.M[1][1]*m.M[2][2] - m.M[2][1]*m.M[1][2])) * invDet;
      v.m[ 4] = -(m.M[1][0]*(m.M[2][2]*m.M[3][3] - m.M[3][2]*m.M[2][3]) - m.M[1][2]*(m.M[2][0]*m.M[3][3] - m.M[3][0]*m.M[2][3]) + m.M[1][3]*(m.M[2][0]*m.M[3][2] - m.M[3][0]*m.M[2][2])) * invDet;
      v.m[ 5] = +(m.M[0][0]*(m.M[2][2]*m.M[3][3] - m.M[3][2]*m.M[2][3]) - m.M[0][2]*(m.M[2][0]*m.M[3][3] - m.M[3][0]*m.M[2][3]) + m.M[0][3]*(m.M[2][0]*m.M[3][2] - m.M[3][0]*m.M[2][2])) * invDet;
      v.m[ 6] = -(m.M[0][0]*(m.M[1][2]*m.M[3][3] - m.M[3][2]*m.M[1][3]) - m.M[0][2]*(m.M[1][0]*m.M[3][3] - m.M[3][0]*m.M[1][3]) + m.M[0][3]*(m.M[1][0]*m.M[3][2] - m.M[3][0]*m.M[1][2])) * invDet;
      v.m[ 7] = +(m.M[0][0]*(m.M[1][2]*m.M[2][3] - m.M[2][2]*m.M[1][3]) - m.M[0][2]*(m.M[1][0]*m.M[2][3] - m.M[2][0]*m.M[1][3]) + m.M[0][3]*(m.M[1][0]*m.M[2][2] - m.M[2][0]*m.M[1][2])) * invDet;
      v.m[ 8] = +(m.M[1][0]*(m.M[2][1]*m.M[3][3] - m.M[3][1]*m.M[2][3]) - m.M[1][1]*(m.M[2][0]*m.M[3][3] - m.M[3][0]*m.M[2][3]) + m.M[1][3]*(m.M[2][0]*m.M[3][1] - m.M[3][0]*m.M[2][1])) * invDet;
      v.m[ 9] = -(m.M[0][0]*(m.M[2][1]*m.M[3][3] - m.M[3][1]*m.M[2][3]) - m.M[0][1]*(m.M[2][0]*m.M[3][3] - m.M[3][0]*m.M[2][3]) + m.M[0][3]*(m.M[2][0]*m.M[3][1] - m.M[3][0]*m.M[2][1])) * invDet;
      v.m[10] = +(m.M[0][0]*(m.M[1][1]*m.M[3][3] - m.M[3][1]*m.M[1][3]) - m.M[0][1]*(m.M[1][0]*m.M[3][3] - m.M[3][0]*m.M[1][3]) + m.M[0][3]*(m.M[1][0]*m.M[3][1] - m.M[3][0]*m.M[1][1])) * invDet;
      v.m[11] = -(m.M[0][0]*(m.M[1][1]*m.M[2][3] - m.M[2][1]*m.M[1][3]) - m.M[0][1]*(m.M[1][0]*m.M[2][3] - m.M[2][0]*m.M[1][3]) + m.M[0][3]*(m.M[1][0]*m.M[2][1] - m.M[2][0]*m.M[1][1])) * invDet;
      v.m[12] = -(m.M[1][0]*(m.M[2][1]*m.M[3][2] - m.M[3][1]*m.M[2][2]) - m.M[1][1]*(m.M[2][0]*m.M[3][2] - m.M[3][0]*m.M[2][2]) + m.M[1][2]*(m.M[2][0]*m.M[3][1] - m.M[3][0]*m.M[2][1])) * invDet;
      v.m[13] = +(m.M[0][0]*(m.M[2][1]*m.M[3][2] - m.M[3][1]*m.M[2][2]) - m.M[0][1]*(m.M[2][0]*m.M[3][2] - m.M[3][0]*m.M[2][2]) + m.M[0][2]*(m.M[2][0]*m.M[3][1] - m.M[3][0]*m.M[2][1])) * invDet;
      v.m[14] = -(m.M[0][0]*(m.M[1][1]*m.M[3][2] - m.M[3][1]*m.M[1][2]) - m.M[0][1]*(m.M[1][0]*m.M[3][2] - m.M[3][0]*m.M[1][2]) + m.M[0][2]*(m.M[1][0]*m.M[3][1] - m.M[3][0]*m.M[1][1])) * invDet;
      v.m[15] = +(m.M[0][0]*(m.M[1][1]*m.M[2][2] - m.M[2][1]*m.M[1][2]) - m.M[0][1]*(m.M[1][0]*m.M[2][2] - m.M[2][0]*m.M[1][2]) + m.M[0][2]*(m.M[1][0]*m.M[2][1] - m.M[2][0]*m.M[1][1])) * invDet;
      return v;
    }
    inline Matrix Mul(const Matrix& a, const Matrix& b)
    {
      Matrix m;
      m.m[ 0] = b.M[0][0] * a.M[0][0] + b.M[0][1] * a.M[1][0] + b.M[0][2] * a.M[2][0] + b.M[0][3] * a.M[3][0];
      m.m[ 1] = b.M[0][0] * a.M[0][1] + b.M[0][1] * a.M[1][1] + b.M[0][2] * a.M[2][1] + b.M[0][3] * a.M[3][1];
      m.m[ 2] = b.M[0][0] * a.M[0][2] + b.M[0][1] * a.M[1][2] + b.M[0][2] * a.M[2][2] + b.M[0][3] * a.M[3][2];
      m.m[ 3] = b.M[0][0] * a.M[0][3] + b.M[0][1] * a.M[1][3] + b.M[0][2] * a.M[2][3] + b.M[0][3] * a.M[3][3];
      m.m[ 4] = b.M[1][0] * a.M[0][0] + b.M[1][1] * a.M[1][0] + b.M[1][2] * a.M[2][0] + b.M[1][3] * a.M[3][0];
      m.m[ 5] = b.M[1][0] * a.M[0][1] + b.M[1][1] * a.M[1][1] + b.M[1][2] * a.M[2][1] + b.M[1][3] * a.M[3][1];
      m.m[ 6] = b.M[1][0] * a.M[0][2] + b.M[1][1] * a.M[1][2] + b.M[1][2] * a.M[2][2] + b.M[1][3] * a.M[3][2];
      m.m[ 7] = b.M[1][0] * a.M[0][3] + b.M[1][1] * a.M[1][3] + b.M[1][2] * a.M[2][3] + b.M[1][3] * a.M[3][3];
      m.m[ 8] = b.M[2][0] * a.M[0][0] + b.M[2][1] * a.M[1][0] + b.M[2][2] * a.M[2][0] + b.M[2][3] * a.M[3][0];
      m.m[ 9] = b.M[2][0] * a.M[0][1] + b.M[2][1] * a.M[1][1] + b.M[2][2] * a.M[2][1] + b.M[2][3] * a.M[3][1];
      m.m[10] = b.M[2][0] * a.M[0][2] + b.M[2][1] * a.M[1][2] + b.M[2][2] * a.M[2][2] + b.M[2][3] * a.M[3][2];
      m.m[11] = b.M[2][0] * a.M[0][3] + b.M[2][1] * a.M[1][3] + b.M[2][2] * a.M[2][3] + b.M[2][3] * a.M[3][3];
      m.m[12] = b.M[3][0] * a.M[0][0] + b.M[3][1] * a.M[1][0] + b.M[3][2] * a.M[2][0] + b.M[3][3] * a.M[3][0];
      m.m[13] = b.M[3][0] * a.M[0][1] + b.M[3][1] * a.M[1][1] + b.M[3][2] * a.M[2][1] + b.M[3][3] * a.M[3][1];
      m.m[14] = b.M[3][0] * a.M[0][2] + b.M[3][1] * a.M[1][2] + b.M[3][2] * a.M[2][2] + b.M[3][3] * a.M[3][2];
      m.m[15] = b.M[3][0] * a.M[0][3] + b.M[3][1] * a.M[1][3] + b.M[3][2] * a.M[2][3] + b.M[3][3] * a.M[3][3];
      return m;
    }
    inline Vector Mul(const Matrix& m, const Vector& v)
    {
      return vector::Value(
        v.x * m.rot[0].x + v.y * m.rot[1].x + v.z * m.rot[2].x + m.pos.x,
        v.x * m.rot[0].y + v.y * m.rot[1].y + v.z * m.rot[2].y + m.pos.y,
        v.x * m.rot[0].z + v.y * m.rot[1].z + v.z * m.rot[2].z + m.pos.z
      );
    }
    inline void Perspective(Matrix& m, const Radian& fovY, f32 aspect, f32 nearClip, f32 farClip, bool leftHanded = true, bool homogeneousDepth = true)
    {
      const f32 height = 1.0f / math::Tan(fovY.Radians() * 0.5f);
      const f32 width  = height * 1.0f/ aspect;
  
      const f32 diff = farClip - nearClip;
      const f32 aa = homogeneousDepth ? (     farClip + nearClip) / diff : farClip / diff;
      const f32 bb = homogeneousDepth ? (2.0f*farClip * nearClip) / diff : nearClip * aa;

      m.m[ 0] = width;
      m.m[ 1] = 0;
      m.m[ 2] = 0;
      m.m[ 3] = 0;
      m.m[ 4] = 0;
      m.m[ 5] = height;
      m.m[ 6] = 0;
      m.m[ 7] = 0;
      m.m[ 8] = (leftHanded) ? -0.0f :  0.0f;
      m.m[ 9] = (leftHanded) ? -0.0f :  0.0f;
      m.m[10] = (leftHanded) ?  aa   : -aa;
      m.m[11] = (leftHanded) ?  1.0f : -1.0f;
      m.m[12] = 0;
      m.m[13] = 0;
      m.m[14] = -bb;
      m.m[15] = 0;
    }
    inline void LookAt(Matrix& m, Vector eye, Vector target, Vector up, bool leftHanded = true)
    {
      Vector x, y, z;

      if (leftHanded)
      {
        z = vector::Normalise(vector::Sub(target, eye));
      }
      else
      {
        z = vector::Normalise(vector::Sub(eye, target));
      }

      x = vector::Normalise(vector::Cross(up, z));
      y = vector::Cross(z, x);

      m.M[0][0] = x.x;
      m.M[0][1] = y.x;
      m.M[0][2] = z.x;
      m.M[0][3] = 0.0f;
      
      m.M[1][0] = x.y;
      m.M[1][1] = y.y;
      m.M[1][2] = z.y;
      m.M[1][3] = 0.0f;
      
      m.M[2][0] = x.z;
      m.M[2][1] = y.z;
      m.M[2][2] = z.z;
      m.M[2][3] = 0.0f;
      
      m.M[3][0] = -vector::Dot(x, eye);
      m.M[3][1] = -vector::Dot(y, eye);
      m.M[3][2] = -vector::Dot(z, eye);
      m.M[3][3] = 1.0f;
    }
  }
  
  namespace traits
  {
    template<> struct MinMax<Vector>
    {
      static constexpr Vector  Max = { MinMax<f32>::Max, MinMax<f32>::Max, MinMax<f32>::Max, 1.0f },
                               Min = { MinMax<f32>::Min, MinMax<f32>::Min, MinMax<f32>::Min, 1.0f };
    };

    template<> struct IsSigned<Vector>
    {
      static constexpr bool Signed = true;
    };
  }

  namespace ops
  {
    template<> struct SignedArithmetic<Vector>
    {
      static Vector Neg(const Vector& value)
      { 
        return vector::Negate(value);
      }
    };

    template<>
    struct Arithmetic<Vector>
    {
      static Vector Value(const Vector& _1)                 { return _1; }
      template<typename T>
      static Vector Value(const T& _1)                      { return vector::Expand(_1);  }
      static Vector Add(const Vector& _1, const Vector& _2) { return vector::Add(_1, _2); }
      static Vector Sub(const Vector& _1, const Vector& _2) { return vector::Sub(_1, _2); }
      static Vector Mul(const Vector& _1, const Vector& _2) { return vector::Mul(_1, _2); }
      static Vector Div(const Vector& _1, const Vector& _2) { return vector::Div(_1, _2); }
    };
    
    template<>
    struct Equality<Vector>
    {
      static bool IsZero(const Vector& _1, const Vector& _2)
      {
        const f32 sqLen1 = vector::Length2(_1);
        return Equality<f32>::IsZero(sqLen1);
      }
      static bool Equals(const Vector& _1, const Vector& _2)
      {
        const f32 sqLen1 = vector::Length2(_1), sqLen2 = vector::Length2(_2);
        return Equality<f32>::Equals(sqLen1, sqLen2);
      }
      static bool NotEquals(const Vector& _1, const Vector& _2)
      {
        const f32 sqLen1 = vector::Length2(_1), sqLen2 = vector::Length2(_2);
        return Equality<f32>::NotEquals(sqLen1, sqLen2);
      }
      static bool LessThan(const Vector& _1, const Vector& _2)
      {
        const f32 sqLen1 = vector::Length2(_1), sqLen2 = vector::Length2(_2);
        return Equality<f32>::LessThan(sqLen1, sqLen2);
      }
      static bool LessThanEquals(const Vector& _1, const Vector& _2)
      {
        const f32 sqLen1 = vector::Length2(_1), sqLen2 = vector::Length2(_2);
        return Equality<f32>::LessThanEquals(sqLen1, sqLen2);
      }
      static bool MoreThan(const Vector& _1, const Vector& _2)
      {
        const f32 sqLen1 = vector::Length2(_1), sqLen2 = vector::Length2(_2);
        return Equality<f32>::MoreThan(sqLen1, sqLen2);
      }
      static bool MoreThanEquals(const Vector& _1, const Vector& _2)
      {
        const f32 sqLen1 = vector::Length2(_1), sqLen2 = vector::Length2(_2);
        return Equality<f32>::MoreThanEquals(sqLen1, sqLen2);
      }
    };
  }

}

#endif
