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
#include "cpage.h"
#include "negdefs.h"
#include "rselstr.h"

/*----------------------------------------------------------------------------*/

//���������

extern int inf_neg_h;
extern int inf_neg_w;
extern double inf_neg_black;
extern double sup_neg_black_del;
extern double weak_neg_black_del;
extern double neg_cut_black;
extern double neg_cut_white;
extern double neg_cut_str;
extern int min_let_h;
extern int min_let_w;
//extern int max_let_h;
//extern int max_let_w;
extern int inf_betw_str_h;
extern int sup_square;
/*----------------------------------------------------------------------------*/

//���������

extern int	DPIX;
extern int	DPIY;
extern int Height;
extern int Width;
extern Word8 ImageName[CPAGE_MAXNAME];
extern NegImage* pNegImage;
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
BOOL IsNegSize(Int16,Int16);
BOOL IsNegBlack(Handle,NegList*);
BOOL GetMasP(Handle,Rect16,Word8**);
BOOL GetMasP(Rect16*,Word8**);
void NormNeg(Handle,NegList*,NegList**,int&);
void CutNeg(Handle,NegList**,int&,int);
void CutNegStr(Handle,NegList**,int&,int);
BOOL IfDrob(Handle,Rect16*,int,CCOM_comp *);
void InitRc(Rect16*,CCOM_comp *);
BOOL SearchNegBySize(CCOM_handle,Handle,NegList**,int&);
void SearchNegByBlack(Handle,NegList**,int&);
void NegMoveMas(Rect16*,int&,int);
void PMoveMas(double*,int,int);
void NegMoveMasR(Rect16*,int&,int);
void NegMoveMas(Rotating*,int,int);
BOOL IfNegIn(NegList*,int,int,int,int,int);
void DeleteRotateMas(Word8**,Int16**,Int16**,Word8**,int**);
void NegInvert(Word8*,Rect16);
void DelIn(Handle,NegList**,int&);
int absolut(int);
double NegBlack(Word8*,Rect16);
void PostRotate(NegList* now,int skew);


/*----------------------------------------------------------------------------*/
