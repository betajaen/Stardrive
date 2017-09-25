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

#ifndef STARDRIVE_META_16_INC
#define STARDRIVE_META_16_INC

#define STypenameT1 typename T1
#define STypenameT2 typename T1, typename T2
#define STypenameT3 typename T1, typename T2, typename T3
#define STypenameT4 typename T1, typename T2, typename T3, typename T4
#define STypenameT5 typename T1, typename T2, typename T3, typename T4, typename T5
#define STypenameT6 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6
#define STypenameT7 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7
#define STypenameT8 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8
#define STypenameT9 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
#define STypenameT10 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10
#define STypenameT11 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11
#define STypenameT12 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12
#define STypenameT13 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13
#define STypenameT14 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14
#define STypenameT15 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15
#define STypenameT16 typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16

#define ST1 T1
#define ST2 T1, T2
#define ST3 T1, T2, T3
#define ST4 T1, T2, T3, T4
#define ST5 T1, T2, T3, T4, T5
#define ST6 T1, T2, T3, T4, T5, T6
#define ST7 T1, T2, T3, T4, T5, T6, T7
#define ST8 T1, T2, T3, T4, T5, T6, T7, T8
#define ST9 T1, T2, T3, T4, T5, T6, T7, T8, T9
#define ST10 T1, T2, T3, T4, T5, T6, T7, T8, T9, T10
#define ST11 T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11
#define ST12 T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12
#define ST13 T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13
#define ST14 T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14
#define ST15 T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15
#define ST16 T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15, T16

#define S_MetaExpand(x) x
#define S_MetaArgCountN(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...) N
#define S_MetaNumArgs(...) S_MetaExpand(S_MetaArgCountN(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))

#define S_MetaForeachRun0(FN)
#define S_MetaForeachRun1(FN, _1) FN(_1) 
#define S_MetaForeachRun2(FN, _1, _2) FN(_1) FN(_2) 
#define S_MetaForeachRun3(FN, _1, _2, _3) FN(_1) FN(_2) FN(_3) 
#define S_MetaForeachRun4(FN, _1, _2, _3, _4) FN(_1) FN(_2) FN(_3) FN(_4) 
#define S_MetaForeachRun5(FN, _1, _2, _3, _4, _5) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) 
#define S_MetaForeachRun6(FN, _1, _2, _3, _4, _5, _6) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) 
#define S_MetaForeachRun7(FN, _1, _2, _3, _4, _5, _6, _7) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) FN(_7) 
#define S_MetaForeachRun8(FN, _1, _2, _3, _4, _5, _6, _7, _8) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) FN(_7) FN(_8) 
#define S_MetaForeachRun9(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) FN(_7) FN(_8) FN(_9) 
#define S_MetaForeachRun10(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) FN(_7) FN(_8) FN(_9) FN(_10) 
#define S_MetaForeachRun11(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) FN(_7) FN(_8) FN(_9) FN(_10) FN(_11) 
#define S_MetaForeachRun12(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) FN(_7) FN(_8) FN(_9) FN(_10) FN(_11) FN(_12) 
#define S_MetaForeachRun13(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) FN(_7) FN(_8) FN(_9) FN(_10) FN(_11) FN(_12) FN(_13) 
#define S_MetaForeachRun14(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) FN(_7) FN(_8) FN(_9) FN(_10) FN(_11) FN(_12) FN(_13) FN(_14) 
#define S_MetaForeachRun15(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) FN(_7) FN(_8) FN(_9) FN(_10) FN(_11) FN(_12) FN(_13) FN(_14) FN(_15) 
#define S_MetaForeachRun16(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) FN(_1) FN(_2) FN(_3) FN(_4) FN(_5) FN(_6) FN(_7) FN(_8) FN(_9) FN(_10) FN(_11) FN(_12) FN(_13) FN(_14) FN(_15) FN(_16) 
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
#define S_MetaForeachNumRun9(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9) FN(0, _1) FN(1, _2) FN(2, _3) FN(3, _4) FN(4, _5) FN(5, _6) FN(6, _7) FN(7, _8) FN(8, _9) 
#define S_MetaForeachNumRun10(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) FN(0, _1) FN(1, _2) FN(2, _3) FN(3, _4) FN(4, _5) FN(5, _6) FN(6, _7) FN(7, _8) FN(8, _9) FN(9, _10) 
#define S_MetaForeachNumRun11(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) FN(0, _1) FN(1, _2) FN(2, _3) FN(3, _4) FN(4, _5) FN(5, _6) FN(6, _7) FN(7, _8) FN(8, _9) FN(9, _10) FN(10, _11) 
#define S_MetaForeachNumRun12(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) FN(0, _1) FN(1, _2) FN(2, _3) FN(3, _4) FN(4, _5) FN(5, _6) FN(6, _7) FN(7, _8) FN(8, _9) FN(9, _10) FN(10, _11) FN(11, _12) 
#define S_MetaForeachNumRun13(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) FN(0, _1) FN(1, _2) FN(2, _3) FN(3, _4) FN(4, _5) FN(5, _6) FN(6, _7) FN(7, _8) FN(8, _9) FN(9, _10) FN(10, _11) FN(11, _12) FN(12, _13) 
#define S_MetaForeachNumRun14(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) FN(0, _1) FN(1, _2) FN(2, _3) FN(3, _4) FN(4, _5) FN(5, _6) FN(6, _7) FN(7, _8) FN(8, _9) FN(9, _10) FN(10, _11) FN(11, _12) FN(12, _13) FN(13, _14) 
#define S_MetaForeachNumRun15(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) FN(0, _1) FN(1, _2) FN(2, _3) FN(3, _4) FN(4, _5) FN(5, _6) FN(6, _7) FN(7, _8) FN(8, _9) FN(9, _10) FN(10, _11) FN(11, _12) FN(12, _13) FN(13, _14) FN(14, _15) 
#define S_MetaForeachNumRun16(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) FN(0, _1) FN(1, _2) FN(2, _3) FN(3, _4) FN(4, _5) FN(5, _6) FN(6, _7) FN(7, _8) FN(8, _9) FN(9, _10) FN(10, _11) FN(11, _12) FN(12, _13) FN(13, _14) FN(14, _15) FN(15, _16) 
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
#define S_MetaForeachNumA1Run9(A1, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) FN(A1, 3, _4) FN(A1, 4, _5) FN(A1, 5, _6) FN(A1, 6, _7) FN(A1, 7, _8) FN(A1, 8, _9) 
#define S_MetaForeachNumA1Run10(A1, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) FN(A1, 3, _4) FN(A1, 4, _5) FN(A1, 5, _6) FN(A1, 6, _7) FN(A1, 7, _8) FN(A1, 8, _9) FN(A1, 9, _10) 
#define S_MetaForeachNumA1Run11(A1, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) FN(A1, 3, _4) FN(A1, 4, _5) FN(A1, 5, _6) FN(A1, 6, _7) FN(A1, 7, _8) FN(A1, 8, _9) FN(A1, 9, _10) FN(A1, 10, _11) 
#define S_MetaForeachNumA1Run12(A1, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) FN(A1, 3, _4) FN(A1, 4, _5) FN(A1, 5, _6) FN(A1, 6, _7) FN(A1, 7, _8) FN(A1, 8, _9) FN(A1, 9, _10) FN(A1, 10, _11) FN(A1, 11, _12) 
#define S_MetaForeachNumA1Run13(A1, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) FN(A1, 3, _4) FN(A1, 4, _5) FN(A1, 5, _6) FN(A1, 6, _7) FN(A1, 7, _8) FN(A1, 8, _9) FN(A1, 9, _10) FN(A1, 10, _11) FN(A1, 11, _12) FN(A1, 12, _13) 
#define S_MetaForeachNumA1Run14(A1, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) FN(A1, 3, _4) FN(A1, 4, _5) FN(A1, 5, _6) FN(A1, 6, _7) FN(A1, 7, _8) FN(A1, 8, _9) FN(A1, 9, _10) FN(A1, 10, _11) FN(A1, 11, _12) FN(A1, 12, _13) FN(A1, 13, _14) 
#define S_MetaForeachNumA1Run15(A1, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) FN(A1, 3, _4) FN(A1, 4, _5) FN(A1, 5, _6) FN(A1, 6, _7) FN(A1, 7, _8) FN(A1, 8, _9) FN(A1, 9, _10) FN(A1, 10, _11) FN(A1, 11, _12) FN(A1, 12, _13) FN(A1, 13, _14) FN(A1, 14, _15) 
#define S_MetaForeachNumA1Run16(A1, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) FN(A1, 0, _1) FN(A1, 1, _2) FN(A1, 2, _3) FN(A1, 3, _4) FN(A1, 4, _5) FN(A1, 5, _6) FN(A1, 6, _7) FN(A1, 7, _8) FN(A1, 8, _9) FN(A1, 9, _10) FN(A1, 10, _11) FN(A1, 11, _12) FN(A1, 12, _13) FN(A1, 13, _14) FN(A1, 14, _15) FN(A1, 15, _16) 
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
#define S_MetaForeachNumA2Run9(A1, A2, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) FN(A1, A2, 3, _4) FN(A1, A2, 4, _5) FN(A1, A2, 5, _6) FN(A1, A2, 6, _7) FN(A1, A2, 7, _8) FN(A1, A2, 8, _9) 
#define S_MetaForeachNumA2Run10(A1, A2, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) FN(A1, A2, 3, _4) FN(A1, A2, 4, _5) FN(A1, A2, 5, _6) FN(A1, A2, 6, _7) FN(A1, A2, 7, _8) FN(A1, A2, 8, _9) FN(A1, A2, 9, _10) 
#define S_MetaForeachNumA2Run11(A1, A2, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) FN(A1, A2, 3, _4) FN(A1, A2, 4, _5) FN(A1, A2, 5, _6) FN(A1, A2, 6, _7) FN(A1, A2, 7, _8) FN(A1, A2, 8, _9) FN(A1, A2, 9, _10) FN(A1, A2, 10, _11) 
#define S_MetaForeachNumA2Run12(A1, A2, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) FN(A1, A2, 3, _4) FN(A1, A2, 4, _5) FN(A1, A2, 5, _6) FN(A1, A2, 6, _7) FN(A1, A2, 7, _8) FN(A1, A2, 8, _9) FN(A1, A2, 9, _10) FN(A1, A2, 10, _11) FN(A1, A2, 11, _12) 
#define S_MetaForeachNumA2Run13(A1, A2, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) FN(A1, A2, 3, _4) FN(A1, A2, 4, _5) FN(A1, A2, 5, _6) FN(A1, A2, 6, _7) FN(A1, A2, 7, _8) FN(A1, A2, 8, _9) FN(A1, A2, 9, _10) FN(A1, A2, 10, _11) FN(A1, A2, 11, _12) FN(A1, A2, 12, _13) 
#define S_MetaForeachNumA2Run14(A1, A2, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) FN(A1, A2, 3, _4) FN(A1, A2, 4, _5) FN(A1, A2, 5, _6) FN(A1, A2, 6, _7) FN(A1, A2, 7, _8) FN(A1, A2, 8, _9) FN(A1, A2, 9, _10) FN(A1, A2, 10, _11) FN(A1, A2, 11, _12) FN(A1, A2, 12, _13) FN(A1, A2, 13, _14) 
#define S_MetaForeachNumA2Run15(A1, A2, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) FN(A1, A2, 3, _4) FN(A1, A2, 4, _5) FN(A1, A2, 5, _6) FN(A1, A2, 6, _7) FN(A1, A2, 7, _8) FN(A1, A2, 8, _9) FN(A1, A2, 9, _10) FN(A1, A2, 10, _11) FN(A1, A2, 11, _12) FN(A1, A2, 12, _13) FN(A1, A2, 13, _14) FN(A1, A2, 14, _15) 
#define S_MetaForeachNumA2Run16(A1, A2, FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) FN(A1, A2, 0, _1) FN(A1, A2, 1, _2) FN(A1, A2, 2, _3) FN(A1, A2, 3, _4) FN(A1, A2, 4, _5) FN(A1, A2, 5, _6) FN(A1, A2, 6, _7) FN(A1, A2, 7, _8) FN(A1, A2, 8, _9) FN(A1, A2, 9, _10) FN(A1, A2, 10, _11) FN(A1, A2, 11, _12) FN(A1, A2, 12, _13) FN(A1, A2, 13, _14) FN(A1, A2, 14, _15) FN(A1, A2, 15, _16) 
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
#define S_MetaForeachCommaRun9(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9) FN(_1), FN(_2), FN(_3), FN(_4), FN(_5), FN(_6), FN(_7), FN(_8), FN(_9)
#define S_MetaForeachCommaRun10(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) FN(_1), FN(_2), FN(_3), FN(_4), FN(_5), FN(_6), FN(_7), FN(_8), FN(_9), FN(_10)
#define S_MetaForeachCommaRun11(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) FN(_1), FN(_2), FN(_3), FN(_4), FN(_5), FN(_6), FN(_7), FN(_8), FN(_9), FN(_10), FN(_11)
#define S_MetaForeachCommaRun12(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) FN(_1), FN(_2), FN(_3), FN(_4), FN(_5), FN(_6), FN(_7), FN(_8), FN(_9), FN(_10), FN(_11), FN(_12)
#define S_MetaForeachCommaRun13(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) FN(_1), FN(_2), FN(_3), FN(_4), FN(_5), FN(_6), FN(_7), FN(_8), FN(_9), FN(_10), FN(_11), FN(_12), FN(_13)
#define S_MetaForeachCommaRun14(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) FN(_1), FN(_2), FN(_3), FN(_4), FN(_5), FN(_6), FN(_7), FN(_8), FN(_9), FN(_10), FN(_11), FN(_12), FN(_13), FN(_14)
#define S_MetaForeachCommaRun15(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) FN(_1), FN(_2), FN(_3), FN(_4), FN(_5), FN(_6), FN(_7), FN(_8), FN(_9), FN(_10), FN(_11), FN(_12), FN(_13), FN(_14), FN(_15)
#define S_MetaForeachCommaRun16(FN, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) FN(_1), FN(_2), FN(_3), FN(_4), FN(_5), FN(_6), FN(_7), FN(_8), FN(_9), FN(_10), FN(_11), FN(_12), FN(_13), FN(_14), FN(_15), FN(_16)
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
    template<STypenameT9> struct TypeAt<0, ST9>  { typedef T1 Type; };
    template<STypenameT10> struct TypeAt<0, ST10>  { typedef T1 Type; };
    template<STypenameT11> struct TypeAt<0, ST11>  { typedef T1 Type; };
    template<STypenameT12> struct TypeAt<0, ST12>  { typedef T1 Type; };
    template<STypenameT13> struct TypeAt<0, ST13>  { typedef T1 Type; };
    template<STypenameT14> struct TypeAt<0, ST14>  { typedef T1 Type; };
    template<STypenameT15> struct TypeAt<0, ST15>  { typedef T1 Type; };
    template<STypenameT16> struct TypeAt<0, ST16>  { typedef T1 Type; };

    template<STypenameT2> struct TypeAt<1, ST2>  { typedef T2 Type; };
    template<STypenameT3> struct TypeAt<1, ST3>  { typedef T2 Type; };
    template<STypenameT4> struct TypeAt<1, ST4>  { typedef T2 Type; };
    template<STypenameT5> struct TypeAt<1, ST5>  { typedef T2 Type; };
    template<STypenameT6> struct TypeAt<1, ST6>  { typedef T2 Type; };
    template<STypenameT7> struct TypeAt<1, ST7>  { typedef T2 Type; };
    template<STypenameT8> struct TypeAt<1, ST8>  { typedef T2 Type; };
    template<STypenameT9> struct TypeAt<1, ST9>  { typedef T2 Type; };
    template<STypenameT10> struct TypeAt<1, ST10>  { typedef T2 Type; };
    template<STypenameT11> struct TypeAt<1, ST11>  { typedef T2 Type; };
    template<STypenameT12> struct TypeAt<1, ST12>  { typedef T2 Type; };
    template<STypenameT13> struct TypeAt<1, ST13>  { typedef T2 Type; };
    template<STypenameT14> struct TypeAt<1, ST14>  { typedef T2 Type; };
    template<STypenameT15> struct TypeAt<1, ST15>  { typedef T2 Type; };
    template<STypenameT16> struct TypeAt<1, ST16>  { typedef T2 Type; };

    template<STypenameT3> struct TypeAt<2, ST3>  { typedef T3 Type; };
    template<STypenameT4> struct TypeAt<2, ST4>  { typedef T3 Type; };
    template<STypenameT5> struct TypeAt<2, ST5>  { typedef T3 Type; };
    template<STypenameT6> struct TypeAt<2, ST6>  { typedef T3 Type; };
    template<STypenameT7> struct TypeAt<2, ST7>  { typedef T3 Type; };
    template<STypenameT8> struct TypeAt<2, ST8>  { typedef T3 Type; };
    template<STypenameT9> struct TypeAt<2, ST9>  { typedef T3 Type; };
    template<STypenameT10> struct TypeAt<2, ST10>  { typedef T3 Type; };
    template<STypenameT11> struct TypeAt<2, ST11>  { typedef T3 Type; };
    template<STypenameT12> struct TypeAt<2, ST12>  { typedef T3 Type; };
    template<STypenameT13> struct TypeAt<2, ST13>  { typedef T3 Type; };
    template<STypenameT14> struct TypeAt<2, ST14>  { typedef T3 Type; };
    template<STypenameT15> struct TypeAt<2, ST15>  { typedef T3 Type; };
    template<STypenameT16> struct TypeAt<2, ST16>  { typedef T3 Type; };

    template<STypenameT4> struct TypeAt<3, ST4>  { typedef T4 Type; };
    template<STypenameT5> struct TypeAt<3, ST5>  { typedef T4 Type; };
    template<STypenameT6> struct TypeAt<3, ST6>  { typedef T4 Type; };
    template<STypenameT7> struct TypeAt<3, ST7>  { typedef T4 Type; };
    template<STypenameT8> struct TypeAt<3, ST8>  { typedef T4 Type; };
    template<STypenameT9> struct TypeAt<3, ST9>  { typedef T4 Type; };
    template<STypenameT10> struct TypeAt<3, ST10>  { typedef T4 Type; };
    template<STypenameT11> struct TypeAt<3, ST11>  { typedef T4 Type; };
    template<STypenameT12> struct TypeAt<3, ST12>  { typedef T4 Type; };
    template<STypenameT13> struct TypeAt<3, ST13>  { typedef T4 Type; };
    template<STypenameT14> struct TypeAt<3, ST14>  { typedef T4 Type; };
    template<STypenameT15> struct TypeAt<3, ST15>  { typedef T4 Type; };
    template<STypenameT16> struct TypeAt<3, ST16>  { typedef T4 Type; };

    template<STypenameT5> struct TypeAt<4, ST5>  { typedef T5 Type; };
    template<STypenameT6> struct TypeAt<4, ST6>  { typedef T5 Type; };
    template<STypenameT7> struct TypeAt<4, ST7>  { typedef T5 Type; };
    template<STypenameT8> struct TypeAt<4, ST8>  { typedef T5 Type; };
    template<STypenameT9> struct TypeAt<4, ST9>  { typedef T5 Type; };
    template<STypenameT10> struct TypeAt<4, ST10>  { typedef T5 Type; };
    template<STypenameT11> struct TypeAt<4, ST11>  { typedef T5 Type; };
    template<STypenameT12> struct TypeAt<4, ST12>  { typedef T5 Type; };
    template<STypenameT13> struct TypeAt<4, ST13>  { typedef T5 Type; };
    template<STypenameT14> struct TypeAt<4, ST14>  { typedef T5 Type; };
    template<STypenameT15> struct TypeAt<4, ST15>  { typedef T5 Type; };
    template<STypenameT16> struct TypeAt<4, ST16>  { typedef T5 Type; };

    template<STypenameT6> struct TypeAt<5, ST6>  { typedef T6 Type; };
    template<STypenameT7> struct TypeAt<5, ST7>  { typedef T6 Type; };
    template<STypenameT8> struct TypeAt<5, ST8>  { typedef T6 Type; };
    template<STypenameT9> struct TypeAt<5, ST9>  { typedef T6 Type; };
    template<STypenameT10> struct TypeAt<5, ST10>  { typedef T6 Type; };
    template<STypenameT11> struct TypeAt<5, ST11>  { typedef T6 Type; };
    template<STypenameT12> struct TypeAt<5, ST12>  { typedef T6 Type; };
    template<STypenameT13> struct TypeAt<5, ST13>  { typedef T6 Type; };
    template<STypenameT14> struct TypeAt<5, ST14>  { typedef T6 Type; };
    template<STypenameT15> struct TypeAt<5, ST15>  { typedef T6 Type; };
    template<STypenameT16> struct TypeAt<5, ST16>  { typedef T6 Type; };

    template<STypenameT7> struct TypeAt<6, ST7>  { typedef T7 Type; };
    template<STypenameT8> struct TypeAt<6, ST8>  { typedef T7 Type; };
    template<STypenameT9> struct TypeAt<6, ST9>  { typedef T7 Type; };
    template<STypenameT10> struct TypeAt<6, ST10>  { typedef T7 Type; };
    template<STypenameT11> struct TypeAt<6, ST11>  { typedef T7 Type; };
    template<STypenameT12> struct TypeAt<6, ST12>  { typedef T7 Type; };
    template<STypenameT13> struct TypeAt<6, ST13>  { typedef T7 Type; };
    template<STypenameT14> struct TypeAt<6, ST14>  { typedef T7 Type; };
    template<STypenameT15> struct TypeAt<6, ST15>  { typedef T7 Type; };
    template<STypenameT16> struct TypeAt<6, ST16>  { typedef T7 Type; };

    template<STypenameT8> struct TypeAt<7, ST8>  { typedef T8 Type; };
    template<STypenameT9> struct TypeAt<7, ST9>  { typedef T8 Type; };
    template<STypenameT10> struct TypeAt<7, ST10>  { typedef T8 Type; };
    template<STypenameT11> struct TypeAt<7, ST11>  { typedef T8 Type; };
    template<STypenameT12> struct TypeAt<7, ST12>  { typedef T8 Type; };
    template<STypenameT13> struct TypeAt<7, ST13>  { typedef T8 Type; };
    template<STypenameT14> struct TypeAt<7, ST14>  { typedef T8 Type; };
    template<STypenameT15> struct TypeAt<7, ST15>  { typedef T8 Type; };
    template<STypenameT16> struct TypeAt<7, ST16>  { typedef T8 Type; };

    template<STypenameT9> struct TypeAt<8, ST9>  { typedef T9 Type; };
    template<STypenameT10> struct TypeAt<8, ST10>  { typedef T9 Type; };
    template<STypenameT11> struct TypeAt<8, ST11>  { typedef T9 Type; };
    template<STypenameT12> struct TypeAt<8, ST12>  { typedef T9 Type; };
    template<STypenameT13> struct TypeAt<8, ST13>  { typedef T9 Type; };
    template<STypenameT14> struct TypeAt<8, ST14>  { typedef T9 Type; };
    template<STypenameT15> struct TypeAt<8, ST15>  { typedef T9 Type; };
    template<STypenameT16> struct TypeAt<8, ST16>  { typedef T9 Type; };

    template<STypenameT10> struct TypeAt<9, ST10>  { typedef T10 Type; };
    template<STypenameT11> struct TypeAt<9, ST11>  { typedef T10 Type; };
    template<STypenameT12> struct TypeAt<9, ST12>  { typedef T10 Type; };
    template<STypenameT13> struct TypeAt<9, ST13>  { typedef T10 Type; };
    template<STypenameT14> struct TypeAt<9, ST14>  { typedef T10 Type; };
    template<STypenameT15> struct TypeAt<9, ST15>  { typedef T10 Type; };
    template<STypenameT16> struct TypeAt<9, ST16>  { typedef T10 Type; };

    template<STypenameT11> struct TypeAt<10, ST11>  { typedef T11 Type; };
    template<STypenameT12> struct TypeAt<10, ST12>  { typedef T11 Type; };
    template<STypenameT13> struct TypeAt<10, ST13>  { typedef T11 Type; };
    template<STypenameT14> struct TypeAt<10, ST14>  { typedef T11 Type; };
    template<STypenameT15> struct TypeAt<10, ST15>  { typedef T11 Type; };
    template<STypenameT16> struct TypeAt<10, ST16>  { typedef T11 Type; };

    template<STypenameT12> struct TypeAt<11, ST12>  { typedef T12 Type; };
    template<STypenameT13> struct TypeAt<11, ST13>  { typedef T12 Type; };
    template<STypenameT14> struct TypeAt<11, ST14>  { typedef T12 Type; };
    template<STypenameT15> struct TypeAt<11, ST15>  { typedef T12 Type; };
    template<STypenameT16> struct TypeAt<11, ST16>  { typedef T12 Type; };

    template<STypenameT13> struct TypeAt<12, ST13>  { typedef T13 Type; };
    template<STypenameT14> struct TypeAt<12, ST14>  { typedef T13 Type; };
    template<STypenameT15> struct TypeAt<12, ST15>  { typedef T13 Type; };
    template<STypenameT16> struct TypeAt<12, ST16>  { typedef T13 Type; };

    template<STypenameT14> struct TypeAt<13, ST14>  { typedef T14 Type; };
    template<STypenameT15> struct TypeAt<13, ST15>  { typedef T14 Type; };
    template<STypenameT16> struct TypeAt<13, ST16>  { typedef T14 Type; };

    template<STypenameT15> struct TypeAt<14, ST15>  { typedef T15 Type; };
    template<STypenameT16> struct TypeAt<14, ST16>  { typedef T15 Type; };

    template<STypenameT16> struct TypeAt<15, ST16>  { typedef T16 Type; };
  }
}

#endif
