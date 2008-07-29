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

/**********  ���������  *******************************************************/
/*  �����,                                                                    */
/*  �����������                                                               */
/*  � ���������                                                               */
/*  ������     :  ������� ��������                                            */
/*  ��������   :  08.06.00                                                    */
/*  ����       :  'dll.cpp'                                                   */
/*  ���������� :  ��������� ����������                                        */
/*  ���������� :                                                              */
/*----------------------------------------------------------------------------*/
#ifndef _RS_FUNC_H_
#define _RS_FUNC_H_
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
# if defined (_DEBUG)
 # pragma message( __FILE__" : RStuff functions declaration")
# endif // (_DEBUG)
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#include "rsdefines.h"
#include "ctiimage.h"
#include "ccomdefs.h"
#include "lnsdefs.h"
#include "linedefs.h"
//#include "RStuff.H"
//////////////////////////
//������ ����������
void SetReturnCode_rstuff(Word16);
void SetReturnCode_rstuff(Word32);
void DebugInit (void );
void DebugDPumaDrawRect(Handle, Point16 *, Word32, Int32, Word32);
void DebugDPumaShowComponents(PRSPreProcessImage, Handle, Word32, Int32, Word32);

Bool32    Binarise( void );
Bool32    Normalise( PRSPreProcessImage );
Bool32    VerifyN( PRSPreProcessImage );
Bool32    DeleteLines(Handle hCPage,void* phCLINE,char* ImageDelLines);
Bool32    DeleteDotLines(void* phCLINE, char* ImageDelLines);

Bool32    KillLinesN( PRSPreProcessImage );
Bool32    Layout( PRSPreProcessImage );
/////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� �����
Bool32    PreProcessImage      ( PRSPreProcessImage );
Bool32    CreateContainerBigComp( PRSPreProcessImage );
Bool32    SearchNewLines       ( PRSPreProcessImage Image );
Bool32    SearchLines          ( PRSPreProcessImage );
Bool32    CalcIncline          ( PRSPreProcessImage );
Bool32    VerifyLines          ( PRSPreProcessImage );
Bool32    OrtoMove             ( PRSPreProcessImage );
Bool32    KillLines            ( PRSPreProcessImage );
Bool32    SearchTables         ( PRSPreProcessImage );
/////////////////////////////////////////////////////////////////////////////////////////////////////
// �������� � �����
Bool32    LineKiller           ( PRSPreProcessImage );
Bool32    SearchAndKill        ( PRSPreProcessImage, LinesTotalInfo* );
Bool32    ComponentFilter      ( PRSPreProcessImage, LineInfo* );
Bool32    IsRectIntersect      ( Rect16*, Rect16* );
Bool32    TuneFilter           ( LineInfo*, Rect16*, Word32, Word32);
Bool32    ChekComponentAndLine ( LineInfo*, Rect16*, Word32);
Bool32    CheckSquare          ( LineInfo*, Rect16*, Word32, Word32);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
Bool32    ExtractComponents    ( Bool32, Handle *, PWord8, PRSPreProcessImage );
Bool32    RemoveLines          ( PRSPreProcessImage, PWord8 *);
Bool32    MyGetZher            ( void **, Int32 *, Int32, Handle );
Bool32    remove_overlayed     ( CCOM_comp *,CCOM_handle );
Bool32    comp_over            ( CCOM_comp *,CCOM_comp * );
//Bool32    AboutLines           ( PRSPreProcessImage, Bool32 *, Int32 * );
Bool32    AboutLines           ( PRSPreProcessImage, Bool32 *, Int32 * );
void GiveMainBuff (void **vvBuff, int *Size);
void GiveWorkBuff (char **ccBuff, int *Size);
void SetMainBuff(void *vBuff, int Size);
void SetWorkBuff(void *vBuff, int Size);
void ReSetMem(void);
/////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� �������� ������������ �����
//Bool32    ShortVerticalLinesProcess    ( PRSPreProcessImage, Word32 );
//Bool32    ReadSVLFromPageContainer     ( PRSPreProcessImage, void * );
/////////////////////////////////////////////////////////////////////////////////////////////////////
// �������
Bool32    SetCBProgressPoints(void *);
//
#define DEC_CB_TYPE(a)  PF##a
#define DEC_CB_FUN(a,b,c) typedef a (*DEC_CB_TYPE(b))c; a b c;
DEC_CB_FUN(void,    ProgressStart,      (void));
DEC_CB_FUN(Bool32,  ProgressStep,       (Word32,  Word32));
DEC_CB_FUN(Bool32,  ProgressStepLines,  (Word32,  Word32));
DEC_CB_FUN(Bool32,  ProgressStepTables, (Word32,  Word32));
DEC_CB_FUN(void,    ProgressFinish,     (void));
DEC_CB_FUN(Bool32,  InitPRGTIME,        (void));
DEC_CB_FUN(PRGTIME, StorePRGTIME,       (Word32, Word32));
DEC_CB_FUN(void,    RestorePRGTIME,     (PRGTIME));
DEC_CB_FUN(Bool32,  DonePRGTIME,        (void));
DEC_CB_FUN(Bool32,  DPumaSkipComponent, (void));
DEC_CB_FUN(Bool32,  DPumaSkipTurn,      (void));
DEC_CB_FUN(Bool32,  rexcProgressStep,   (Word32));
DEC_CB_FUN(void,    SetUpdate,          (Word32, Word32));
DEC_CB_FUN(char *,  GetModulePath,      (void));
#undef DEC_CB_FUN
#endif //_RS_FUNC_H_
////////////////////////////////////////////////////////////////////////////////
//end of file
