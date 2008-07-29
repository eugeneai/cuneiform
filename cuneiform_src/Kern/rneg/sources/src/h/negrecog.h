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

#include <stdio.h>
/*#include <windows.h>*/


#include "ccom.h"
#include "ctiimage.h"
#include "exc.h"
#include "recdefs.h"
#include "negdefs.h"
#include "rstr.h"
#include "dpuma.h"
#include "cpage.h"
#include "cstr.h"
#include "rselstr.h"


/*----------------------------------------------------------------------------*/

//���������


extern int min_let_h;
extern int min_let_w;
//extern int max_let_h;
//extern int max_let_w;
extern int NegRecTYPEE;
extern double inf_prob;
/*----------------------------------------------------------------------------*/

//���������

extern int	DPIX;
extern int	DPIY;
extern int Height;
extern int Width;
extern double inf_prob;
extern Word8 ImageName[CPAGE_MAXNAME];
extern Handle NegRecD;
extern Handle NegResD;
extern Handle NegRecDC;
extern Handle MainWindowD;
extern Handle RecOneLetter;
extern Handle PrintResConsole;
extern Handle hShowNegComps;

/*----------------------------------------------------------------------------*/




//My function's diclarations

BOOL InitNegMas(Rect16**,int);
BOOL InitNegMas(RecVersions**,int);
BOOL InitNegMas(UniVersions**,int);
BOOL InitNegMas(CCOM_comp***,int);
void DelNegMas(Rect16**);
void DelNegMas(RecVersions*);
void DelNegMas(UniVersions*);
void DelNegMas(CCOM_comp**);
BOOL AddLenNegMas(Rect16**,int&,int);
BOOL AddLenNegMas(CCOM_comp***,int&,int);
BOOL GetMasP(Handle,Rect16,Word8**);
BOOL GetMasP(Rect16*,Word8**);
BOOL NegGetRaster(Handle,Rect16,RecRaster*,BOOL);
void InitRc(Rect16*,int,CCOM_comp *);
void PrintFrameComp(Handle,Rect16*,int);
Int32 GetNegCCOM(Handle,Rect16*,int);
void NegRecog(Handle,NegList**,int&,int);
void NegInvert(RecRaster*,Rect16);
void SortLetter(Rect16*,int,BOOL);
void ToHoriz(Rect16*,int);
void NegPrintConsol(Word8*,int);
void NegPrintConsol(double);
void NegPrintConsol(int,int,int,int);
void NegMoveResult(Word8*,int&,int);
void NegMoveMas(Rect16*,int&,int);
void PMoveMas(double*,int,int);
void NegMoveMas(Rotating*,int,int);
void NegMoveMasR(Rect16*,int&,int);
void NegPutLetter(Word8*,int&,RecAlt,BOOL);
int GetMediumW(Rect16*,int);
int GetMediumH(Rect16*,int);
BOOL IfExistA(RecVersions);
BOOL IfGl(Word8);
BOOL IfExistDef(RecVersions);
BOOL IfExistI(RecVersions);
BOOL IfBadResult(Word8*,int);
BOOL IfNegIn(NegList*,int,int,int,int,int);
void NegDrawRect(Handle,Word32,Word32,Rect16);
void NegAr2(Word8*,int,int);
double NegStrControl(Rect16*,int,BOOL,Rect16*);
double NegRecControl(int);
int CountLetter(Rect16*,int,BOOL);
int NegGetCountOfStr(Rect16*,int);
void NegPrintInFile(FILE*,NegList*,int);
int NegCountNumbers(int);
void NegSetAlf(char*);
void DeleteRotateMas(Word8**,Int16**,Int16**,Word8**,int**);
void NegMoveMas(Int32* hCCOM,int n,int num);
BOOL UnifCont(CCOM_handle to,CCOM_handle from);
void TurnRaster(RecRaster*);
void TurnOverNeg(RecRaster, Word8*);


/*----------------------------------------------------------------------------*/
