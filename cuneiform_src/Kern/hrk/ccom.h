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
// CONTAINER OF THE COMPONENTS                            //
////////////////////////////////////////////////////////////
// O.Slavin                                               // 
////////////////////////////////////////////////////////////
// Creation     : 08 Jul 1998                             //
////////////////////////////////////////////////////////////
// Modification : 21 Jul 1998                             //
////////////////////////////////////////////////////////////
#ifndef __CCOM_H
   #define __CCOM_H

   #ifndef __GLOBUS_H
   #include "globus.h"
   #endif
   #include "ccomdefs.h"

#ifndef __RECDEFS_H
   #include "recdefs.h"
#endif
   #include "memfunc.h"

   #ifdef __CCOM__
      #define CCOM_FUNC  FUN_EXPO
   #else
      #define CCOM_FUNC  FUN_IMPO
   #endif

   #ifdef __cplusplus
   extern "C" {
   #endif

#ifdef PPS_MAC
   #pragma export on
#endif
/////////////////////////////////
// AK 22.02.99
//#ifndef Handle
//typedef void * Handle ;
//#endif
//#include "cttypext.h"
//////////////////////////////AK"

   CCOM_FUNC(Bool32)  CCOM_Init( Word16 wHeightCode, Handle hStorage );
   CCOM_FUNC(void)    CCOM_Done(void);
   CCOM_FUNC(Word32)  CCOM_GetReturnCode(void);
   CCOM_FUNC(char*)   CCOM_GetReturnString(Word32 dwError);
   CCOM_FUNC(Bool32)  CCOM_SetImportData(Word32 dwType, void * pData);
   CCOM_FUNC(Bool32)  CCOM_GetExportData(Word32 dwType, void * pData);

    enum CCOMFunctionsExt
        {
        CCOM_FNNEW,
        CCOM_FNSTORE,
		CCOM_FNCOPY,
        CCOM_FNDELETE,
        CCOM_FNGETFIRST,
        CCOM_FNGETNEXT,
        CCOM_FNGETLINE,
        CCOM_FNGETRASTER,
        CCOM_FNGETCOLLECTION,
        CCOM_FNGETUSERBLOCK,
        CCOM_FNCREATECONT,
        CCOM_FNDELETECONT,
        CCOM_FNADDLPTORS,
        CCOM_FNMAKELP,
        CCOM_FNSETUSERBLOCK,
        CCOM_FNNEWUSERCODE,
        CCOM_FNVERSION,
        CCOM_FNBACKUP,
        CCOM_FNRESTORE,
        CCOM_FNDELALL      ,
        CCOM_FNLARGENEW ,
        CCOM_FNLARGENEWLN,
        CCOM_FNLARGENEWINTERVAL,
        CCOM_FNLARGECLOSE,
        CCOM_FNSETKILLEDACCESS,
        CCOM_FNKILL,
        CCOM_FNGETEXTRASTER,
        CCOM_FNCLEARCONTAINER,
        CCOM_FNGETSCALERASTER,
        CCOM_COMPRESSCONTAINER,
        CCOM_SETLANGUAGE,
        CCOM_GETLANGUAGE,
        CCOM_GECONTAINERVOLUME,
        CCOM_YDECR,
        CCOM_YINCR,
		    CCOM_FNREANIMATE,
        CCOM_FNADDCOMPTORS
        };
    enum CCOMFunctionsImp
        {
        CCOM_FNIMP_ALLOC,
        CCOM_FNIMP_REALLOC,
        CCOM_FNIMP_FREE,
        CCOM_FNIMP_OPEN,
        CCOM_FNIMP_CLOSE,
        CCOM_FNIMP_READ,
        CCOM_FNIMP_WRITE,
        CCOM_FNIMP_MAKELP
        };
// 1    CCOM_FNNEW          ������� ����� ����������       
typedef CCOM_comp  * (*FNCCOM_New)(CCOM_handle cont, Int32 upper, Int32 left, Int32 w, Int32 h);
CCOM_FUNC(CCOM_comp*) CCOM_New(CCOM_handle cont,Int32 upper, Int32 left, Int32 w, Int32 h);
// 2    CCOM_FNSTORE        �������� � ���������� �����
typedef Bool32         (*FNCCOM_Store)(CCOM_comp * comp,Int16 numcomp,
                Int32 size_nlines, Word8 *lines,  Int16 nl,
                Word8 free_beg, Word8 free_e,
                RecVersions *vers,
                CCOM_USER_BLOCK  *ub);
CCOM_FUNC(Bool32)          CCOM_Store(CCOM_comp * comp,Int16 numcomp,
                Int32 size_nlines, Word8 *lines,  Int16 nl,
                Word8 free_beg, Word8 free_e,
                RecVersions *vers,
                CCOM_USER_BLOCK  *ub);
// 3    CCOM_FNSTORE        �������� � ���������� �����
typedef Bool32         (*FNCCOM_Copy)(CCOM_comp * to,CCOM_comp *from);
CCOM_FUNC(Bool32)          CCOM_Copy(CCOM_comp * to,CCOM_comp *from);
// 4    CCOM_FNDELETE       ������� ����������   
typedef Bool32       (*FNCCOM_Delete)(CCOM_handle cont, CCOM_comp * comp);
CCOM_FUNC(Bool32)     CCOM_Delete(CCOM_handle cont, CCOM_comp * comp);
// 5    CCOM_FNGETFIRST     ���� ������ ���������� �� ����������   
typedef CCOM_comp  * (*FNCCOM_GetFirst)(CCOM_handle ccom, Bool32 (*filtrate)(Int32 upper, Int32 left, Int32 w, Int32 h) );
CCOM_FUNC(CCOM_comp*) CCOM_GetFirst(CCOM_handle ccom,Bool32 (*filtrate)(Int32 upper, Int32 left, Int32 w, Int32 h) );
// 6    CCOM_FNGETNEXT      ���� ��������� ����������    
typedef CCOM_comp  * (*FNCCOM_GetNext)(CCOM_comp * comp,Bool32 (*filtrate)(Int32 upper, Int32 left, Int32 w, Int32 h) );
CCOM_FUNC(CCOM_comp*) CCOM_GetNext(CCOM_comp * comp, Bool32 (*filtrate)(Int32 upper, Int32 left, Int32 w, Int32 h));
// 7    CCOM_FNGETLINE      �������� ������������ �������������   
typedef Bool32       (*FNCCOM_GetLine)(CCOM_comp * comp,CCOM_linerep  *lrep );
CCOM_FUNC(Int16)     CCOM_GetLine(CCOM_comp * comp,CCOM_linerep  *lrep);
// 8    CCOM_FNGETRASTER    �������� ������� ����� ����������  
typedef Bool32       (*FNCCOM_GetRaster)(CCOM_comp * comp,RecRaster *rec );
CCOM_FUNC(Bool32)     CCOM_GetRaster(CCOM_comp * comp, RecRaster *rec);
// 9    CCOM_FNGETCOLLECTION  �������� ��������� ������������� 
typedef Bool32       (*FNCCOM_GetCollection)(CCOM_comp * comp,RecVersions   *vers);
CCOM_FUNC(Bool32)     CCOM_GetCollection(CCOM_comp * comp, RecVersions   *vers);
// 10    CCOM_FNGETUSERBLOCK �������� ���������������� ����
typedef Bool32       (*FNCCOM_GetUserBlock)(CCOM_comp * comp,CCOM_USER_BLOCK *ub);
CCOM_FUNC(Bool32)     CCOM_GetUserBlock(CCOM_comp * comp,CCOM_USER_BLOCK *ub);
// 11   CCOM_FNCREATECONT   ������� ����� ���������
typedef CCOM_handle (*FNCCOM_CreateContainer)(void);
CCOM_FUNC(CCOM_handle) CCOM_CreateContainer(void);
// 12   CCOM_FNDELETECONT   ���������� ���������
typedef Bool32      (*FNCCOM_DeleteContainer)(CCOM_handle con);
CCOM_FUNC(Bool32)      CCOM_DeleteContainer  (CCOM_handle con);
// 13   CCOM_FNADDLPTORS    �������� �� � ������
typedef Bool32      (*FNCCOM_AddLPToRaster)(CCOM_comp * comp, RecRaster *rec);
CCOM_FUNC(Bool32)      CCOM_AddLPToRaster  (CCOM_comp * comp, RecRaster *rec);
// 14   CCOM_FNMAKELP       �������� ������������ �������������
typedef Bool32      (*FNCCOM_MakeLP)( RecRaster   *rRaster , Word8 *lp, Int16 *lp_size, Int16 *numcomp);
CCOM_FUNC(Bool32)      CCOM_MakeLP  ( RecRaster   *rRaster , Word8 *lp, Int16 *lp_size, Int16 *numcomp);
// 15   CCOM_FNSETUSERBLOCK �������� ���������������� ����
typedef Bool32       (*FNCCOM_SetUserBlock)(CCOM_comp * comp,CCOM_USER_BLOCK *ub);
CCOM_FUNC(Bool32)     CCOM_SetUserBlock(CCOM_comp * comp, CCOM_USER_BLOCK *ub);
// 16   CCOM_FNNEWUSERCODE  ���� ��� ���������� ����������������� ����
typedef Int32     (*FNCCOM_NewUserCode)(void);
CCOM_FUNC(Int32)      CCOM_NewUserCode (void);
// 17   CCOM_FNVERSION      ���� ����� ������
// 18   CCOM_FNBACKUP       ��������� ��������� �� ����         
typedef Bool32  (*FNCCOM_Backup)(CCOM_handle hcont);
CCOM_FUNC(Bool32)   CCOM_Backup (CCOM_handle hcont);
// 19   CCOM_FNRESTORE      ������������ ��������� � �����
typedef CCOM_handle  (*FNCCOM_Restore)(void);
CCOM_FUNC(CCOM_handle)   CCOM_Restore (void);
// 20   CCOM_FNDELALL       ������� ��� ����������
typedef void    (*FNCCOM_DeleteAll)(void);
CCOM_FUNC(void)    CCOM_DeleteAll(void);
// 21   CCOM_FNLARGENEW     ������� ����� ���������� � �������� �����������
typedef CCOM_comp   *(*FNCCOM_LargeNew)(CCOM_handle cont,Int32 upper, Int32 left, Int32 w, Int32 h, Int32 size);
CCOM_FUNC(CCOM_comp)   *CCOM_LargeNew(CCOM_handle cont,Int32 upper, Int32 left, Int32 w, Int32 h, Int32 size);
// 22   CCOM_FNLARGENEWLN   ������� ����� ����� � �������� �����������
typedef Bool32 (*FNCCOM_LargeNewLn)(CCOM_comp   *cmp,CCOM_lnhead **lnh);
CCOM_FUNC(Bool32) CCOM_LargeNewLn(CCOM_comp   *cmp,CCOM_lnhead **lnh);
// 23   CCOM_FNLARGENEWINTERVAL �������� ����� ������� ��������
typedef Bool32 (*FNCCOM_LargeNewInterval)(CCOM_comp   *cmp,Int16 e,Int16 l);
CCOM_FUNC(Bool32) CCOM_LargeNewInterval(CCOM_comp   *cmp,Int16 e,Int16 l);
// 24   CCOM_FNLARGECLOSE   ��������� ��������� ���������� � �������� �����������
typedef void (*FNCCOM_LargeClose)(CCOM_comp   *cmp);
CCOM_FUNC(void) CCOM_LargeClose(CCOM_comp   *cmp);
// 25   CCOM_FNSETKILLEDACCESS    ����� ������� � ������
typedef Bool32  (*FNCCOM_SetKilledAccess)(Bool32 ShowEnable);
CCOM_FUNC(Bool32)   CCOM_SetKilledAccess(Bool32 ShowEnable);
// 26   CCOM_FNKILL               ������� ��� �����������
typedef Bool32  (*FNCCOM_Kill)(CCOM_comp *c);
CCOM_FUNC(Bool32)  CCOM_Kill(CCOM_comp *c);
// 27   CCOM_FNGETEXTRASTER    �������� ������� ����� ����������  
typedef Bool32       (*FNCCOM_GetExtRaster)(CCOM_comp * comp,RecRaster *rec );
CCOM_FUNC(Bool32)     CCOM_GetExtRaster(CCOM_comp * comp, RecRaster *rec);
// 28   CCOM_FNCLEARCONTAINER    ������� ��� ����������  � ����������
typedef Bool32       (*FNCCOM_ClearContatiner)(CCOM_handle con );
CCOM_FUNC(Bool32)     CCOM_ClearContatiner(CCOM_handle con);
// 29   CCOM_FNGETSCALERASTER    �� � ����� �� �������
typedef Bool32 (*FNCCOM_GetScaleRaster)(CCOM_comp * comp, RecRaster *rec,Int32 scale);
CCOM_FUNC(Bool32) CCOM_GetScaleRaster(CCOM_comp * comp, RecRaster *rec,Int32 scale);
// 30   CCOM_COMPRESSCONTAINER  ������� ������
typedef Bool32     (*FNCCOM_CompressContatiner)(CCOM_handle hcont);
CCOM_FUNC(Bool32)     CCOM_CompressContatiner(CCOM_handle hcont);
// 31   CCOM_SETLANGUAGE        ���������� ���� ����������
typedef Bool32     (*FNCCOM_SetLanguage)(CCOM_handle hcont,Int16 language);
CCOM_FUNC(Bool32)     CCOM_SetLanguage(CCOM_handle hcont,Int16 language);
// 32   CCOM_GETLANGUAGE        �������� ���� ����������
typedef Bool32     (*FNCCOM_GetLanguage)(CCOM_handle hcont,Int16 *language);
CCOM_FUNC(Bool32)     CCOM_GetLanguage(CCOM_handle hcont,Int16 *language);
// 33   CCOM_GECONTAINERVOLUME  ����� ��������� � ����������
typedef Int32      (*FNCCOM_GetContainerVolume)(CCOM_handle hcont);
CCOM_FUNC(Int32)      CCOM_GetContainerVolume(CCOM_handle hcont);
// 34   CCOM_YDECR:             ��������� �������� ���� ��������� ���������� �� 1
typedef Bool32      (*FNCCOM_YDecr) (CCOM_handle hcont);
CCOM_FUNC(Bool32)     CCOM_YDecr (CCOM_handle hcont);
// 35   CCOM_YINCR:             ��������� �������� ���� ��������� ���������� �� 1
typedef Bool32      (*FNCCOM_YIncr) (CCOM_handle hcont);
CCOM_FUNC(Bool32)     CCOM_YIncr (CCOM_handle hcont);
// 36   CCOM_FNREANIMATE               ������� � ����� ������� ��������
typedef Bool32  (*FNCCOM_Reanimate)(CCOM_comp *c);
CCOM_FUNC(Bool32)  CCOM_Reanimate(CCOM_comp *c);
// 37   CCOM_FNADDCOMPTORS
// �������� �� � ������ -- ������������ �������
typedef Bool32      (*FNCCOM_AddCompToRaster)(CCOM_comp * comp, Int16 relleft, Int16 relupper, RecRaster *rec);
CCOM_FUNC(Bool32)      CCOM_AddCompToRaster(CCOM_comp * comp, Int16 relleft, Int16 relupper, RecRaster *rec);
#ifdef PPS_MAC
   #pragma export off
#endif
// error code



   #ifdef __cplusplus
            }
   #endif

#endif
