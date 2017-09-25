/*
                                                                                                    
   ad88888ba                                           88              88                           
  d8"     "8b  ,d                                      88              ""                           
  Y8,          88                                      88                                           
  `Y8aaaaa,  MM88MMM  ,adPPYYba,  8b,dPPYba,   ,adPPYb,88  8b,dPPYba,  88  8b       d8   ,adPPYba,  
    `"""""8b,  88     ""     `Y8  88P'   "Y8  a8"    `Y88  88P'   "Y8  88  `8b     d8'  a8P_____88  
          `8b  88     ,adPPPPP88  88          8b       88  88          88   `8b   d8'   8PP"""""""  
  Y8a     a8P  88,    88,    ,88  88          "8a,   ,d88  88          88    `8b,d8'    "8b,   ,aa  
   "Y88888P"   "Y888  `"8bbdP"Y8  88           `"8bbdP"Y8  88          88      "8"       `"Ybbd8"'  
                                                                                                    
  Copyright (c) Robin Southern 2017                                                                 
                                                                                                    
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
                                                                                  
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
                                                                                  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef STARDRIVE_META_8_INC
#define STARDRIVE_META_8_INC

#define STypenameT1 typename T1
#define STypenameT2 typename T1, typename T2
#define STypenameT3 typename T1, typename T2, typename T3
#define STypenameT4 typename T1, typename T2, typename T3, typename T4
#define STypenameT5 typename T1, typename T2, typename T3, typename T4, typename T5
#define STypenameT6 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6
#define STypenameT7 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7
#define STypenameT8 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8

#define ST1 T1
#define ST2 T1, T2
#define ST3 T1, T2, T3
#define ST4 T1, T2, T3, T4
#define ST5 T1, T2, T3, T4, T5
#define ST6 T1, T2, T3, T4, T5, T6
#define ST7 T1, T2, T3, T4, T5, T6, T7
#define ST8 T1, T2, T3, T4, T5, T6, T7, T8

#define S_MetaExpand(x) x
#define S_MetaArgCountN(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define S_MetaNumArgs(...) S_MetaExpand(S_MetaArgCountN(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0))

#define S_MetaForeachRun0(FN)
#define S_MetaForeachRun1(FN, _1) FN(_1) 
#define S_MetaForeachRun2(FN, _1, _2) FN(_1) FN(_2) 
#define S_MetaForeachRun3(FN, _1, _2, _3) FN(_1) FN(_2) FN(_3) 
#define S_MetaForeachRun4(FN, _1, _2, _3, _4) FN(_1) FN(_2) FN(_3) FN(_4) 
#define S_MetaForeachRun5(FN, _1, _2, _3, _4, _5) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) 
#define S_MetaForeachRun6(FN, _1, _2, _3, _4, _5, _6) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) 
#define S_MetaForeachRun7(FN, _1, _2, _3, _4, _5, _6, _7) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) FN(_7) 
#define S_MetaForeachRun8(FN, _1, _2, _3, _4, _5, _6, _7, _8) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) FN(_7) FN(_8) 
#define S_MetaForeachRun_(M, ...)  S_MetaExpand(M(__VA_ARGS__))
#define S_MetaForeachImpl(FN, ...) S_MetaExpand(S_MetaForeachRun_(SMetaConcat(S_MetaForeachRun, S_MetaNumArgs(__VA_ARGS__)), FN, __VA_ARGS__))


#define S_MetaForeachNumRun0(FN)
#define S_MetaForeachNumRun1(FN, _1) FN(0, _1) 
#define S_MetaForeachNumRun2(FN, _1, _2) FN(0, _1) FN(1, _2) 
#define S_MetaForeachNumRun3(FN, _1, _2, _3) FN(0, _1) FN(1, _2) FN(2, _3) 
#define S_MetaForeachNumRun4(FN, _1, _2, _3, _4) FN(0, _1) FN(1, _2) FN(2, _3) FN(3, _4) 
#define S_MetaForeachNumRun5(FN, _1, _2, _3, _4, _5) FN(0, _1) FN(1, _2) FN(2, _3) FN(3, _4) FN(4, _5) 
#define S_MetaForeachNumRun6(FN, _1, _2, _3, _4, _5, _6) FN(0, _1) FN(1, _2) FN(2, _3) FN(3, _4) FN(4, _5) FN(5, _6) 
#define S_MetaForeachNumRun7(FN, _1, _2, _3, _4, _5, _6, _7) FN(0, _1) FN(1, _2) FN(2, _3) FN(3, _4) FN(4, _5) FN(5, _6) FN(6, _7) 
#define S_MetaForeachNumRun8(FN, _1, _2, _3, _4, _5, _6, _7, _8) FN(0, _1) FN(1, _2) FN(2, _3) FN(3, _4) FN(4, _5) FN(5, _6) FN(6, _7) FN(7, _8) 
#define S_MetaForeachNumRun_(M, ...)  S_MetaExpand(M(__VA_ARGS__))
#define S_MetaForeachIndexed(FN, ...) S_MetaExpand(S_MetaForeachNumRun_(SMetaConcat(S_MetaForeachNumRun, S_MetaNumArgs(__VA_ARGS__)), FN, __VA_ARGS__))


#define S_MetaForeachNumA1Run0(A1, FN)
#define S_MetaForeachNumA1Run1(A1, FN, _1) FN(A1, 0, _1) 
#define S_MetaForeachNumA1Run2(A1, FN, _1, _2) FN(A1, 0, _1) FN(A1, 1, _2) 
#define S_MetaForeachNumA1Run3(A1, FN, _1, _2, _3) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) 
#define S_MetaForeachNumA1Run4(A1, FN, _1, _2, _3, _4) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) FN(A1, 3, _4) 
#define S_MetaForeachNumA1Run5(A1, FN, _1, _2, _3, _4, _5) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) FN(A1, 3, _4) FN(A1, 4, _5) 
#define S_MetaForeachNumA1Run6(A1, FN, _1, _2, _3, _4, _5, _6) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) FN(A1, 3, _4) FN(A1, 4, _5) FN(A1, 5, _6) 
#define S_MetaForeachNumA1Run7(A1, FN, _1, _2, _3, _4, _5, _6, _7) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) FN(A1, 3, _4) FN(A1, 4, _5) FN(A1, 5, _6) FN(A1, 6, _7) 
#define S_MetaForeachNumA1Run8(A1, FN, _1, _2, _3, _4, _5, _6, _7, _8) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) FN(A1, 3, _4) FN(A1, 4, _5) FN(A1, 5, _6) FN(A1, 6, _7) FN(A1, 7, _8) 
#define S_MetaForeachNumA1Run_(M, ...)  S_MetaExpand(M(__VA_ARGS__))
#define S_MetaForeachIndexedArg1(A1, FN, ...) S_MetaExpand(S_MetaForeachNumA1Run_(SMetaConcat(S_MetaForeachNumA1Run, S_MetaNumArgs(__VA_ARGS__)), A1, FN, __VA_ARGS__))


#define S_MetaForeachNumA2Run0(A1, A2, FN)
#define S_MetaForeachNumA2Run1(A1, A2, FN, _1) FN(A1, A2, 0, _1) 
#define S_MetaForeachNumA2Run2(A1, A2, FN, _1, _2) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) 
#define S_MetaForeachNumA2Run3(A1, A2, FN, _1, _2, _3) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) 
#define S_MetaForeachNumA2Run4(A1, A2, FN, _1, _2, _3, _4) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) FN(A1, A2, 3, _4) 
#define S_MetaForeachNumA2Run5(A1, A2, FN, _1, _2, _3, _4, _5) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) FN(A1, A2, 3, _4) FN(A1, A2, 4, _5) 
#define S_MetaForeachNumA2Run6(A1, A2, FN, _1, _2, _3, _4, _5, _6) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) FN(A1, A2, 3, _4) FN(A1, A2, 4, _5) FN(A1, A2, 5, _6) 
#define S_MetaForeachNumA2Run7(A1, A2, FN, _1, _2, _3, _4, _5, _6, _7) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) FN(A1, A2, 3, _4) FN(A1, A2, 4, _5) FN(A1, A2, 5, _6) FN(A1, A2, 6, _7) 
#define S_MetaForeachNumA2Run8(A1, A2, FN, _1, _2, _3, _4, _5, _6, _7, _8) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) FN(A1, A2, 3, _4) FN(A1, A2, 4, _5) FN(A1, A2, 5, _6) FN(A1, A2, 6, _7) FN(A1, A2, 7, _8) 
#define S_MetaForeachNumA2Run_(M, ...)  S_MetaExpand(M(__VA_ARGS__))
#define S_MetaForeachIndexedArg2(A1, A2, FN, ...) S_MetaExpand(S_MetaForeachNumA2Run_(SMetaConcat(S_MetaForeachNumA2Run, S_MetaNumArgs(__VA_ARGS__)), A1, A2, FN, __VA_ARGS__))


#define S_MetaForeachCommaRun0(FN)
#define S_MetaForeachCommaRun1(FN, _1) FN(_1)
#define S_MetaForeachCommaRun2(FN, _1, _2) FN(_1), FN(_2)
#define S_MetaForeachCommaRun3(FN, _1, _2, _3) FN(_1), FN(_2), FN(_3)
#define S_MetaForeachCommaRun4(FN, _1, _2, _3, _4) FN(_1), FN(_2), FN(_3), FN(_4)
#define S_MetaForeachCommaRun5(FN, _1, _2, _3, _4, _5) FN(_1), FN(_2), FN(_3), FN(_4), FN(_5)
#define S_MetaForeachCommaRun6(FN, _1, _2, _3, _4, _5, _6) FN(_1), FN(_2), FN(_3), FN(_4), FN(_5), FN(_6)
#define S_MetaForeachCommaRun7(FN, _1, _2, _3, _4, _5, _6, _7) FN(_1), FN(_2), FN(_3), FN(_4), FN(_5), FN(_6), FN(_7)
#define S_MetaForeachCommaRun8(FN, _1, _2, _3, _4, _5, _6, _7, _8) FN(_1), FN(_2), FN(_3), FN(_4), FN(_5), FN(_6), FN(_7), FN(_8)
#define S_MetaForeachCommaRun_(M, ...)  S_MetaExpand(M(__VA_ARGS__))
#define S_MetaForeachCommaImpl(FN, ...) S_MetaExpand(S_MetaForeachCommaRun_(SMetaConcat(S_MetaForeachCommaRun, S_MetaNumArgs(__VA_ARGS__)), FN, __VA_ARGS__))


namespace Stardrive
{
  namespace meta
  {
    template<uinteger I, typename ...> struct TypeAt {};
    template<STypenameT1> struct TypeAt<0, ST1>  { typedef T1 Type; };
    template<STypenameT2> struct TypeAt<0, ST2>  { typedef T1 Type; };
    template<STypenameT3> struct TypeAt<0, ST3>  { typedef T1 Type; };
    template<STypenameT4> struct TypeAt<0, ST4>  { typedef T1 Type; };
    template<STypenameT5> struct TypeAt<0, ST5>  { typedef T1 Type; };
    template<STypenameT6> struct TypeAt<0, ST6>  { typedef T1 Type; };
    template<STypenameT7> struct TypeAt<0, ST7>  { typedef T1 Type; };
    template<STypenameT8> struct TypeAt<0, ST8>  { typedef T1 Type; };

    template<STypenameT2> struct TypeAt<1, ST2>  { typedef T2 Type; };
    template<STypenameT3> struct TypeAt<1, ST3>  { typedef T2 Type; };
    template<STypenameT4> struct TypeAt<1, ST4>  { typedef T2 Type; };
    template<STypenameT5> struct TypeAt<1, ST5>  { typedef T2 Type; };
    template<STypenameT6> struct TypeAt<1, ST6>  { typedef T2 Type; };
    template<STypenameT7> struct TypeAt<1, ST7>  { typedef T2 Type; };
    template<STypenameT8> struct TypeAt<1, ST8>  { typedef T2 Type; };

    template<STypenameT3> struct TypeAt<2, ST3>  { typedef T3 Type; };
    template<STypenameT4> struct TypeAt<2, ST4>  { typedef T3 Type; };
    template<STypenameT5> struct TypeAt<2, ST5>  { typedef T3 Type; };
    template<STypenameT6> struct TypeAt<2, ST6>  { typedef T3 Type; };
    template<STypenameT7> struct TypeAt<2, ST7>  { typedef T3 Type; };
    template<STypenameT8> struct TypeAt<2, ST8>  { typedef T3 Type; };

    template<STypenameT4> struct TypeAt<3, ST4>  { typedef T4 Type; };
    template<STypenameT5> struct TypeAt<3, ST5>  { typedef T4 Type; };
    template<STypenameT6> struct TypeAt<3, ST6>  { typedef T4 Type; };
    template<STypenameT7> struct TypeAt<3, ST7>  { typedef T4 Type; };
    template<STypenameT8> struct TypeAt<3, ST8>  { typedef T4 Type; };

    template<STypenameT5> struct TypeAt<4, ST5>  { typedef T5 Type; };
    template<STypenameT6> struct TypeAt<4, ST6>  { typedef T5 Type; };
    template<STypenameT7> struct TypeAt<4, ST7>  { typedef T5 Type; };
    template<STypenameT8> struct TypeAt<4, ST8>  { typedef T5 Type; };

    template<STypenameT6> struct TypeAt<5, ST6>  { typedef T6 Type; };
    template<STypenameT7> struct TypeAt<5, ST7>  { typedef T6 Type; };
    template<STypenameT8> struct TypeAt<5, ST8>  { typedef T6 Type; };

    template<STypenameT7> struct TypeAt<6, ST7>  { typedef T7 Type; };
    template<STypenameT8> struct TypeAt<6, ST8>  { typedef T7 Type; };

    template<STypenameT8> struct TypeAt<7, ST8>  { typedef T8 Type; };
  }
}

#endif
