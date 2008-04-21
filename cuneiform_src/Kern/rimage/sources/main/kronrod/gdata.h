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

/*----------------------------------------------------------------------*/
/*	DATA.H	10.08.1993	M.Kronrod	in SCAN-LEM		*/
/*----------------------------------------------------------------------*/
#define	noCARMAN
/*----------------------------------------------------------------------*/
// 03.08.1993	Begin from LEMAN's DATA.H 02.08.1993 (??????)
//		DELETE Itek (see also ZONE.C);
//		see also Flag_FAX_100x200;
//	move here  Card_Up, Card_Left, Card_H, Card_W,
//		   Card_DEXTRA_Multi, 	Card_DEXTRA_Ncards_max,
//		   Card_DEXTRA_Address;
// 10.08.1993	take LEMAN's DATA.H (05.08.1993) and add CARMAN;
//		NOTA BENE: here (HEAD);  "CARMAN";  Itek;
/*----------------------------------------------------------------------*/
#ifndef __DATA_H__

#ifdef __DATA_C__
#define EXTERN
#define INIT(v)         = v
#else
#define EXTERN extern
#define INIT(v)
#endif

#include "compat_defs.h"

#define FAR

EXTERN HWND             hAppWnd;
#define BUFSZ   0x4000

EXTERN BYTE FAR         * BufZone; // [BUFSZ];
EXTERN BYTE FAR         * aBufPass;
EXTERN HANDLE           hBufPass;

EXTERN  BYTE FAR     szTempTiffName [144];
EXTERN  char         szScanFullName[144];
EXTERN  char         szScanDriverName[16];
EXTERN  char         Main_Dir_Name [128];       // H:\CUNEI  (see zB SCANTAB.C)
EXTERN  char         *MainDir;
EXTERN  BYTE         szValidNames[144];

//EXTERN int     cancel_done;
//EXTERN int     x_centrum, y_centrum, brt_ans, brt_arg;
//EXTERN long    act_w, act_h, act_x, act_y, act_br, act_inverse;
//EXTERN RAT     act_xr, act_yr;
//EXTERN INT32   scan_width, scan_height;
//EXTERN void  * _heapbase;
//EXTERN HANDLE  hInst;
//EXTERN char    Flag_FAX_100x200;       // (GREY-WIN.C);  sets here
//EXTERN BYTE    Flag_GREY INIT(0x55) ;        // (GREY-WIN.C)
/*......................................................................*/
							// 03.08.1993 MK:
//EXTERN int     cun_wparm;
//EXTERN char     far *cun_lparm;
EXTERN WORD    Itek;   /////////////////// OTLADKA ONLY
//EXTERN int     brt_ans;
//EXTERN char    auto_flag INIT(0);

#define __DATA_H__
#endif
