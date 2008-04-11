/*
Copyright (c) 1993-2008, Cognitive Technologies
All rights reserved.

����������� ��������� ��������������� � ������������� ��� � ���� ��������� ����,
��� � � �������� �����, � ����������� ��� ���, ��� ���������� ��������� �������:

      * ��� ��������� ��������������� ��������� ���� ������ ���������� ���������
        ���� ����������� �� ��������� �����, ���� ������ ������� � ����������� 
        ����� �� ��������. 
      * ��� ��������� ��������������� ��������� ���� � ������������ �/��� � 
        ������ ����������, ������������ ��� ���������������, ������ �����������
        ��������� ���� ���������� �� ��������� �����, ���� ������ ������� �
        ����������� ����� �� ��������.  
      * �� �������� Cognitive Technologies, �� ����� �� ����������� �� ����� 
        ���� ������������ � �������� �������� ��������� �/��� ����������� 
        ���������, ���������� �� ���� ��, ��� ���������������� �����������
        ����������. 

��� ��������� ������������� ����������� ��������� ���� �/��� ������� ������ "���
��� ����" ��� ������-���� ���� ��������, ���������� ���� ��� ���������������, 
������� �������� ������������ �������� � ����������� ��� ���������� ����, �� ��
������������� ���. �� �������� ��������� ���� � �� ���� ������ ����, ������� 
����� �������� �/��� �������� �������������� ���������, �� � ���� ������ �� 
��Ѩ� ���������������, ������� ����� �����, ���������, ����������� ��� 
������������� ������, ��������� � �������������� ��� ���������� ���������� 
������������� ������������� ��������� (������� ������ ������, ��� ������, 
������� ���������, ��� ������ �/��� ������ �������, ���������� ��-�� �������� 
������� ��� �/��� ������ ��������� �������� ��������� � ������� �����������, 
�� �� ������������� ����� ��������), �� �� ������������� ���, ���� ���� ����� 
�������� ��� ������ ���� ���� �������� � ����������� ����� ������� � ������.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * Neither the name of the Cognitive Technologies nor the names of its
      contributors may be used to endorse or promote products derived from this
      software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE 
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "sfont.h"

#ifndef PPS_MAC
#pragma message(__FILE__)
#endif
#ifndef __FON_H
   #define __FON_H

   #ifndef __GLOBUS_H
   #include "globus.h"
   #endif

   #include "fondefs.h"
#ifndef __RECDEFS_H
   #include "recdefs.h"
#endif
   #include "memfunc.h"

   #ifdef __FON__
      #define FON_FUNC  FUN_EXPO
   #else
      #define FON_FUNC  FUN_IMPO
   #endif

   #ifdef __cplusplus
   extern "C" {
   #endif
#ifdef PPS_MAC
        #pragma export on
#endif

	// return < 0 - error
    // FonSpecInfo *fonSpecInfo ����� ���� NULL
	FON_FUNC(Int32) FONRecogChar(RecRaster *recRast,RecVersions *collection,FonSpecInfo *fonSpecInfo);
	FON_FUNC(Int32) FONRecogCharTiger(RecRaster *recRast,RecVersions *collection,FonSpecInfo *fonSpecInfo);
	// okr - �� ���������� ����� �� ���������� �� �������� okr
	// proc - ���������� ����� �������� > (wei*proc)/100
	FON_FUNC(Int32) FONRecogOkr(RecRaster *recRast,RecVersions *collection,FonSpecInfo *specInfo,Int32 okr,Int32 proc);

	// ������ ���������� ����� ��������
	// ������ - ������
	FON_FUNC(Int32) FONRecogInner(RecRaster *recRast,RecVersions *collection,FonSpecInfo *specInfo);

	// �������� ����� �������� ��� ������� �� ���� 
	FON_FUNC(Int32) FONGetNumCluster(Int32 nInCTB);

	// ��������� ����� � ������ let
	// �������  -2 - ������� ������� ������
	//    -1 - ��� �������� � ����� ������
	//    >= 0 , <= 4- ������� ��������� � ������� 
	//     ���������� � ��������� ��������       
	//    � testInfo - ����������
	//      �������� �������� Italic,Bold,Serif 
	FON_FUNC(Int32) FONTestChar(RecRaster *recRast,Word8 let,FonTestInfo *testInfo,Int16 nInCTB);
	FON_FUNC(Int32) FONTestCharTiger(RecRaster *recRast,Word8 let,FonTestInfo *testInfo);
    // ������ �� ��������  numWelet
	// movx,movy - ��������
	FON_FUNC(Int32) FONCompareRasterCluster(RecRaster *recRast,int numWelet,
										int movx,int movy);
    FON_FUNC(Int32) FONCompareOkrRasterCluster(RecRaster *recRast,int numWelet,
										int movx,int movy,int okr,int procent,
										int *dist1,int *dist2);
	FON_FUNC(Int32) FONSetAlphabet(char *coll);
	// ������� �������� ��� �������
	FON_FUNC(Int32) FONSetAlphaColumn(Int32 column,Bool32 onlyDigits);

	FON_FUNC(Int32) FONFontInfo(FontInfo *fontinfo);
	FON_FUNC(Int32) FONSizesInfo(SizesInfo *sizeinfo,int num);

	// 3.12.98 
	// return < 0 - error (no base loaded)
	//          0 - undefined
	//        > 0 - count   
	FON_FUNC(Int32) FONGetFontCount(void);  
////////////////// 29 sep 98
	//
	// if input clustinfo->let == 0 - �������� ���������� � �������� num
	// ����� - �������� ���������� � �������� � ������ clustinfo->let 
	// � ������� >= num
	FON_FUNC(Int32) FONGetClustInfo( ClustInfo *clustinfo,
                                    int num   // in range [1..FONGetClustCount(void)]
                                   );
	FON_FUNC(Int32) FONGetClustCount(void);   // returns count (N) => numbers [1..N] can be used as indexes

   FON_FUNC(Int32) FONGetNearestClusters( RecRaster* pattern,  // symbol
                                          ClustAlt result[],   // result table of K nearest klusters
                                          int nClustAltLen,    // length of table
                                          int nDistLevel       // don't report about clusters with distance more than nDistLevel 
                                        );   
////////////////////////////////////
	//
	//  ������� �� �������� �����-����� �����
	//   [in/out] name   - ����� ������� � ������ *name (���� name !=NULL && *name >0)
	//                 - ���������� ��� ���������� �������� (���� name!=NULL)
	//   [in] number - & � ���������� ������� >= number  
	//   [in] porog -  & ������������ ����� (0-100 ) (0 - default)
	//   [out]recRaster - �������� � recRaster
	//
	//   Return  
	//      >=0 - ����� ��������, ������� ������.
	//      < 0 - error :
	//       -10 - �� ��������� ����
	//       -20 - �������� �����  (<0 ��� > ����� ���������)
	//       -21 - �������� ���    (<0 or > 255)
	//       -22 - ������� �� ������ (��� ������ � ������ ������) 
	//
	FON_FUNC(Int32) FONGetClusterAsBW(Int32 *name,Int32 number,Int32 porog,RecRaster *recRast);

	 // return < 0  - error	 (-1 - no memory)
	 //		   == 0 no file or invalid file
	 //		   > 0 O.K
	 //
	FON_FUNC(Int32)  FONInit(char *); 

    FON_FUNC(void)   FONDone(void);

	// ��������� �������� (num>=1) ������ �����
	FON_FUNC(Int32) FONSetClusterInvalid(Int32 num);
    
    FON_FUNC(Int16) FONGetErr(void);
      // Err16.h defined codes or one of the next
      //

	    // �������������. 

	// �������� ��������� ����� ��� ������� �������������
	// ���������� �����
	// <0 - ������ (��� ������)
	//  0 - ����� �� ���� �� �����-�� ������� (������...)
	FON_FUNC(Int32) FONStoreRaster(RecRaster *r,Word8 let, Word8 IsPrint,
		Word8 Prob, Word8 Valid, Int16 line_number, Word8 kegl,Rect16 *rect,Word8 column);

    //
	// return < 0 - error
    // return >= 0 - ������� ��������� ���������
    //
    //  ���������:
    //  CTBname - ��� ������� ���� ��� ��� ����� ������� (.r ��� tiger)
    //  cluname - �������� ���. ���� cluname==NULL - �������� �� CTBname � ����������� clu
    //                       (���� ����� .clu)   
    //  accept - ��������� �� �������, ���������� ��� ������� ������� ��� ��������� 
    //         ��� � �������� (������ ��� tiger) - ����� NULL
    //  extern_buf - ������� �����, ������� ����� ������������ - ����� NULL
	//  size       - ������ ������
    //  param - ��������� ������������� (0 default)
	//    if( (param&FONCLU_MultiFontRow) != 0 ) - � ����� ������ ����� �������
    //    else                      - � ����� ������ ���� �����
    //    if( (param&FONCLU_SaveAsClu) != 0 ) - ��������� ��� ���� .clu
    //    else                      - ��������� ��� grey CTB     
	//    if( (param&FONCLU_NotFonts) != 0 ) - ��������� ��� ��������
    //    else                     - ������� ����
    //    if( (param&FONCLU_SaveWeak) != 0 ) - �� ���������� solid � twin (tiger )
	//                               �� ����������� ������ �������� (CTB)
    //    else                     - ����������
    //    if( (param&FONCLU_AddClu) != 0 ) - ���������� �������� � ���������� � cluname (tiger only)
    //    else                     - ��������� ������  
    //    if( (param&FONCLU_InputR) != 0 ) - ������� ���� - ���� �������
    //    else                     - ������� ���� - CTB-����
    //    param&FONCLU_Threshold - ����� ������������� 
    //     ���� ����� <=0  - ��������������� ����� 3 ( ���������� >=3 - ������ ��������)
	//  ShowProgress - ��������� �� �������, (void Show(long percent)), 
    //    ������� �� ���� ���������� ������� ��������� ������. ����� NULL.

    //    default param=0
    //    accept,extern_buf, ShowProgress  may be NULL
    //  standard usage (FormReader) FONFontClusters(CTBname,cluname,NULL,NULL,0,0,NULL);
	//  standard usage (Puma) FONFontClusters(CTBname,cluname,NULL,NULL,0,0x2000,NULL);

    FON_FUNC(Int32) FONFontClusters(char *CTBname,char *cluname,void *accept,Word8 *extern_buf,Int32 size,
					 			    Word32 param,void *ShowProgress,Word8 language);
	FON_FUNC(Int32) FONCutOffClusters(welet *ww,Int16 numWelet);
    FON_FUNC(Bool32) FONCheckItself(Word8 let,Int32 num,Int16 col,Int16 row);
////////////////////
	// ������� ��� ����������
	FON_FUNC(Int32) FONRecogCharBound(RecRaster *recRast,RecVersions *collection,
								  Int32 *recBounds);
	FON_FUNC(Int32) FONRecogKley(RecRaster *recRast,RecVersions *collection);
	// snap for RecogKley  (unglue)
	FON_FUNC(Int32) FONShowSnap(void);
	FON_FUNC(Int32) FONInitSnap(Handle hhh);
	FON_FUNC(Int32) FONEndSnap(void);

//////////////////
//
//  ������� ��������� - ������������ ���������
//  
// �������� - ���� �� ������� ����� ��������� � �������
// name1 & name2
//  return < 0 - error
//   else 0 - 255  (255 - the same )
//
    FON_FUNC(Int32) FONCompareClustNames(Int32 name1,Int32 name2); 
//
// ����� ��������, ������� �� ������� � �������� �������
// ������ - c 1 
// �������� � collect. Info - nomer ��������
//
    FON_FUNC(Int32) FONGetSameClust(Int32 num,RecVersions *collect);

    
///////////////////////
// error code
#define ER_FON_NO_ERROR  0
#define ER_FON_NO_RECOG  1
#define ER_FON_OPEN      2
#define ER_FON_READ      3
#define ER_FON_MEMORY    4

#ifdef PPS_MAC
        #pragma export off
#endif

   #ifdef __cplusplus
            }
   #endif

#endif

