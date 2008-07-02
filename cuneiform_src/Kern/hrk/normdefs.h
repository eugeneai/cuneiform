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

/**********  ���������  **********/
/*  �����      :  ��������� ��������                                          */
/*  ��������   :  08.06.00                                                    */
/*  ����       :  'NormDefs.H'                                                */
/*  ���������� :  ��������� � ���� �������������� ��������.                   */
/*  ���������� :  ������������ �����������.                                   */
/*----------------------------------------------------------------------------*/
#ifndef __NORMDEFS_H
#define __NORMDEFS_H
#include "cttypes.h"

typedef enum
{
	NR_DT_Unknown = 0,
	NR_DT_Rect,
	NR_DT_LineSimple,
	NR_DT_LineDefis,
	NR_DT_LinePointed,
	NR_DT_Frame,
	NR_DT_EvenHori,
	NR_DT_EvenVert,
	NR_DT_PoolInteHori,
	NR_DT_PoolInteVert,
	NR_DT_CompHori,
	NR_DT_CompVert
} NORM_DATATYPES;

typedef struct tagNR_Rect
{
	Int32  Lef;
	Int32  Top;
	Int32  Rig;
	Int32  Bot;
	Int32  Skew10; // == 10*1024*Tg(fi)
} NR_Rect;

typedef struct tagNR_SimpLine
{
	Int32  Beg_X;
	Int32  Beg_Y;
	Int32  End_X;
	Int32  End_Y;
	Int32  Wid10; // == 10*width
} NR_SimpLine;

typedef struct tagNR_DefiLine
{
	NR_Rect Rc_0;
	Int32  Step1000; // == 1000*step
	Int32  nRc;
} NR_DefiLine;

typedef struct tagNR_PoinLine
{
	Int32  Lef_0;
	Int32  Top_0;
	Int32  Size;
	Int32  Step1000; // == 1000*step
	Int32  nRc;
} NR_PoinLine;

typedef struct tagNR_Frame
{
	NR_Rect Rc;
	Int32  StepInto;
} NR_Frame;

typedef struct tagNR_Shift
{
	Int32  Pos;
	Int32  Lent;
} NR_Shift;

typedef struct tagNR_Event
{
	Bool   Hori;      //�����. ��� ������.
	Bool   Increase;  //���������� ��� ��������� �������
	Int32  Lev_0;     //������� ������� ���������
	int    nInter;
	NR_Shift *pInter; //������� � ������������� ����������
} NR_Event;

typedef struct tagNR_Inter
{
	Int32  Lev;
	Int32  Pos;
	Int32  Lent;
} NR_Inter;

typedef struct tagNR_Bag
{
	Bool   Hori;      //�����. ��� ������.
	int    nInter;
	NR_Inter *pInter;
} NR_Bag;

#endif
