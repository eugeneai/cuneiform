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

////////////////////////////////////////////////////////////
// EXTRACTION OF THE COMPONENTS                           //
////////////////////////////////////////////////////////////
// A.Talalay   (for Tiger32.DLL & MAC version)            //
// V.Troyanker (Cuneiform 96, FormReader     )            //
// O.Slavin    (for Cuneifrom2000            )            //
////////////////////////////////////////////////////////////
// Creation     : 08 Jul 1998                             //
////////////////////////////////////////////////////////////
// Modification : 21 Jul 1998                             //
////////////////////////////////////////////////////////////
#ifndef __EXC_H
   #define __EXC_H

#ifdef __cplusplus
   extern "C" {
#endif

   #ifndef __GLOBUS_H
   #include "globus.h"
   #endif

   #ifndef __IMGACCS_H
   #include "imgaccs.h"
   #endif

   #ifndef __EXCDEFS_H
   #include "excdefs.h"
   #endif

   #ifndef __RECDEFS_H
   #include "recdefs.h"
   #endif

   #ifndef __CCOMDEFS_H
   #include "ccomdefs.h"
   #endif

#ifdef __EXC__
  #define EXC_FUNC  FUN_EXPO
#else
  #define EXC_FUNC  FUN_IMPO
#endif

// Return codes for Extracomp

#define ExRc_OK                 0       // Compatible with Err16.h
#define ExRc_InternalError      -1      // Compatible with Err16.h
#define ExRc_MemAllocFail       -3      // Compatible with Err16.h
#define ExRc_DumpOpenFail       -6      // Compatible with Err16.h
#define ExRc_DumpWriteFail      -8      // Compatible with Err16.h
#define ExRc_ErrorInCallback    -4000
#define ExRc_IncorrectParam     -20     // Compatible with Err16.h
#define ExRc_NotEnoughMemory    4

typedef Bool  (* Tiger_ProcComp)    (void * pool,Word32 size);
/*
#ifndef Handle
typedef void * Handle ;
#endif
*/
#ifdef PPS_MAC
 #pragma export on
#endif
enum    REXCParametrs
    {
//-    REXC_FNEVNPROPERT,
    REXC_FNEXTRACOMP,
    REXC_FNEXTRA,
    REXC_FNEXTRADIB,
    REXC_FNGETCONTAINER,
    REXC_FNGETLENEREP,
    REXC_FNVERSION,
//-    REXC_FNREX_ISLANGUAGE,
	REXC_Word8_Matrix,
	REXC_Word8_Fax1x2,
    REXC_Word16_ActualResolution,
//-    REXC_FNGETORIENT,
    REXC_ProgressStart,
    REXC_ProgressStep,
    REXC_ProgressFinish,
    REXC_FNMN2CCOM,
//-    REXC_OcrPath,
    REXC_FNGETINVERTION,
//-    REXC_FNEVNALPHABET,
    REXC_FNEXTRACOMP3CB,
//-    REXC_FNEXTGETRECRASTERORIENT,
//-    REXC_FNSETALLALPHAGRA
    };


   EXC_FUNC(Bool32) ExtrcompInit( void);
    // Start initialization. TRUE if OK
    // Can new call after closing the library without ExtrcompDone
   EXC_FUNC(void)   ExtrcompDone(void);
    // Closing of the library.
   EXC_FUNC(Word32) REXC_GetReturnCode(void);
   EXC_FUNC(char*)  REXC_GetReturnString(Word32 dwError);
   EXC_FUNC(Bool32) REXC_Init(Word16 wHeightCode, Handle hStorage);
   EXC_FUNC(void)   REXC_Done(void);
   EXC_FUNC(Bool32) REXC_GetExportData(Word32 dwType, void * pData);
   EXC_FUNC(Bool32) REXC_SetImportData(Word32 dwType, void * pData);

// 1    REXC_FNEVNPROPERT   ���������� ����� ��� �����
// setup condition for recognition all comps without Event-algoriphm
//       and alphabet (256 ANSI indicators for any letter)
/*-Andrey: moved to RRecCom (recognition) and RNorm (autorotate)
//--------------------------------------------------------------
typedef Bool32   (*FNREXC_SetEVNProperties)(ExcControl ExCW,char *spath, Word8 lang);
EXC_FUNC(Bool32)  REXC_SetEVNProperties(ExcControl ExCW,char *spath, Word8 lang);
-*/
// 2    REXC_FNEXTRACOMP    ����� ���������� � ������� ���������
typedef Bool32 (*FNREXC_Excomp)(ExcControl Control,
    TImageOpen  tio,        TImageClose tic,
    TImageRead  tir,        Tiger_ProcComp tipc);
EXC_FUNC(Int32)  Extracomp(ExcControl Control,
    TImageOpen  tio,        TImageClose tic,
    TImageRead  tir,        Tiger_ProcComp tipc);
// 3    REXC_FNEXTRA        ����� ���������� � ������
typedef Bool32 (*FNREXC_Exc)(ExcControl Control,
    Word8 *lpRaster, Int32 BWid, Bool32 ReverseOrder,
    Int32 Wid, Int32 Hei,
    Int32 HRes, Int32 VRes,
    Int32 TemplCol, Int32 TemplRow, Int32 TemplWid, Int32 TemplHei);
EXC_FUNC(Bool32)  REXCExtra(ExcControl Control,
    Word8 *lpRaster, Int32 BWid, Bool32 ReverseOrder,
    Int32 Wid, Int32 Hei,
    Int32 HRes, Int32 VRes,
    Int32 TemplCol, Int32 TemplRow, Int32 TemplWid, Int32 TemplHei, Bool32 FotoMetr);
// 4    REXC_FNEXTRADIB     ����� ���������� � ����
typedef Bool32 (*FNREXC_ExcDIB)(ExcControl ExCW,
    Word8 *lpDIB,
    Int32 TemplCol, Int32 TemplRow, Int32 TemplWid, Int32 TemplHei);
EXC_FUNC(Bool32)  REXCExtraDIB(ExcControl ExCW,
    Word8 *lpDIB,
    Int32 TemplCol, Int32 TemplRow, Int32 TemplWid, Int32 TemplHei);
// 5    REXC_FNGETCONTAINER   �������� ��� ���������� � ������������
typedef  Int32 (*FNREXC_GetContainer)(void);
EXC_FUNC(Int32)  REXCGetContainer(void);
// 6    REXC_FNGETLENEREP     �������� ������������ �������������
typedef  Bool32  (*FNREXC_MakeLP)( RecRaster   *rRaster , Word8 *lp, Int16 *lp_size, Int16 *numcomp);
EXC_FUNC(Bool32)     REXCMakeLP  ( RecRaster   *rRaster , Word8 *lp, Int16 *lp_size, Int16 *numcomp);
// 7    REXC_FNVERSION ���� ������ ����������
//
//
/*-Andrey: moved to RRecCom (recognition) and RNorm (autorotate)
//--------------------------------------------------------------
// 8    REXC_FNREX_ISLANGUAGE ���������� �� ����
typedef Bool32 (*FNREXC_IsLanguage)(Word8 language);
EXC_FUNC(Bool32)  REXC_IsLanguage(Word8 language);
// 9    REXC_FNGETORIENT    ���������� ��������
typedef Bool32 (*FNREXC_GetOrient)(Word8 *ori);
EXC_FUNC(Bool32) REXC_GetOrient(Word8 *ori);
-*/
// 10   REXC_FNMN2CCOM      �� MN � CCOM_comp
typedef CCOM_comp*   (*FNREXC_MN2CCOM)(Handle hCCOM,Handle hmn);
EXC_FUNC(CCOM_comp*)   REXC_MN2CCOM(Handle hCCOM,Handle hmn);
// 11   REXC_FNGETINVERTION ��������� �� ����� (����� �� ������)
typedef Bool32 (*FNREXC_GetInvertion)(Word8 *inv);
EXC_FUNC(Bool32) REXC_GetInvertion(Word8 *inv);
typedef Bool32 (*FNREXC_ProgressStart )(void);
typedef Bool32 (*FNREXC_ProgressStep  )(Word32 step);
typedef Bool32 (*FNREXC_ProgressFinish)(void);
/*-Andrey: moved to RRecCom (recognition) and RNorm (autorotate)
//--------------------------------------------------------------
// 12   REXC_FNEVNALPHABET   ��������� �������� ��� �����
typedef Bool32 (*FNREXC_SetEVNAlphabet)(char *spath, Word8 lang);
EXC_FUNC(Bool32) REXC_SetEVNAlphabet(char *spath, Word8 lang);
-*/
// 13   REXC_FNEXTRACOMP3CB 3 ��������
typedef Bool32  (*FNREXCExtracomp3CB)(ExcControl ExCW,TImageOpen tio,
                                TImageClose tic, TImageRead tir);
EXC_FUNC(Bool32)  REXCExtracomp3CB(ExcControl ExCW,TImageOpen tio,
                                TImageClose tic, TImageRead tir);
/*-Andrey: moved to RRecCom (recognition) and RNorm (autorotate)
//--------------------------------------------------------------
// 14   REXC_FNEXTGETRECRASTERORIENT ���������� �������� ������
typedef Bool32 (*FNexc_get_rec_raster_orient)(RecRaster   *rs,Int32 *res);
EXC_FUNC(Bool32) exc_get_rec_raster_orient(RecRaster   *rs,Int32 *res);
// 15   REXC_FNSETALLALPHAGRA   ������� ��������� ����
typedef Bool32 (*FNexc_set_all_alphabet_gra)(void);
EXC_FUNC(Bool32) exc_set_all_alphabet_gra(void);
-*/
#ifdef PPS_MAC
 #pragma export off
#endif

// error codes (moved 30.07.01 from "exc\src\resource.h")
#define REXC_ERR_MIN                2048
#define REXC_ERR_NO                 2048
#define REXC_ERR_NOTOPERATE         2049
#define REXC_ERR_NOMEMORY           2050
#define REXC_ERR_NOTIMPLEMENT       2051
#define REXC_ERR_INTERNAL           2052
#define REXC_ERR_DUMPOPEN           2053
#define REXC_ERR_DUMPWRITE          2054
#define REXC_ERR_CALLBACK           2055
#define REXC_ERR_PARAM              2056
#define REXC_ERR_NOCOMP             2057
#define REXC_ERR_NOINITEV           2058
#define REXC_ERR_DIFVERSIONS        2059
#define REXC_ERR_NOIMPORT           2060
#define REXC_ERR_NOEXPORT           2061
#define REXC_ERR_NOLANGUAGE         2062
#define REXC_ERR_NOSETALPHABET      2063
#define REXC_ERR_NOGRA              2064
#define REXC_ERR_USE                2065
#define REXC_ERR_NOTENOUGHTMEMORY   2066
#define REXC_ERR_GETORIENT          2067
#define REXC_ERR_IMAGEINFO          2068
#define REXC_ERR_MAX                2068


#ifdef __cplusplus
            }
#endif

#endif // __EXC_H
