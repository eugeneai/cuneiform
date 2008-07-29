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
/*  ��������   :  03.07.00                                                    */
/*  ����       :  'LineDefs.H'                                                */
/*  ���������� :  ��������� � ���� ��� �����.                                 */
/*  ���������� :  ���������� ������ � �������.                                */
/*----------------------------------------------------------------------------*/
#ifndef __LINEDEFS_H
#define __LINEDEFS_H
#include "cttypes.h"
#include "normdefs.h"


typedef enum
{
	LD_Unknown = 0,
	LD_Horiz,
	LD_Verti,
	LD_Kosa1,
	LD_Kosa2
	/***  ������������    :  90' - 22.5' < Skew <  90' + 22.5'  ***/
	/***  ��������������  :   0' - 22.5' < Skew <   0' + 22.5'  ***/
	/***  �����-1�������� :  45' - 22.5' < Skew <  45' + 22.5'  ***/
	/***  �����-2�������� : 135' - 22.5' < Skew < 135' + 22.5'  ***/
} LINE_DIR;

typedef struct tagLINE_COM
{
	NR_SimpLine     Line;     // ���������� �������� �����
	Int32           Status;   // ������� ����� � ���������
	Word32          Flags;    // common use info
	NORM_DATATYPES  Type;     //*Unknown, *Simple, *Defis, *Pointed
	LINE_DIR        Dir;
	char            Qual;     // quality (or estimation) at percents
	char            Dens;     // density at percents
	Int32           nFrag;    // if==-1 - fragmentation was not made
	NR_Event       *pFrag;    // NULL for nFrag<1
	void           *Specline; //(NR_DefiLine), (NR_PoinLine)
	/* �� NULL ������ ��� *Defis � *Pointed �����, � ���� ���������� �������� */
} LINE_COM;

//Line flags (from LNS):
      #define LI_NOISE      0x00000001   // is a noise line
      #define LI_ATTACHED   0x00000002   // Line  confidently
                                         // attached to form element
      #define LI_SMARTSWEEP 0x00000004   // must smartly dissolve it from image
      #define LI_CRUDESWEEP 0x00000008   //
      #define LI_SWEEP (LI_SMARTSWEEP | LI_CRUDESWEEP)
      #define LI_DOT        0x00000010   //
      #define LI_COVERED    0x00000020   // always with LI_NOISE
	/*****  ������������ ������������� �����.  *****/
		// ���� ������ ���� �� ���������, ���� �� ������. ���� �� ������, ��
		// ���� ����� �����������, ���� �� �������������.
	#define LI_IsTrue       0x00000040
			// ��������� ���������� �����
	#define LI_IsFalse      0x00000080
			// �� �����
	#define LI_NOTWHOLE     0x00000100
			// ������� �������. �������� ����� ������ - �� Anew �� Bnew.
	#define LI_COMPLEX      0x00000200
			// ��������� ����� : ��������� �������� �����, ������ ��� � ����
			// ��� ��������� ��������� ���������. ���������� � �������� � ��
			// ������ �������� ������ � ����������� ������������ � ����������
			// ����������� ���������.
	#define LI_Pointed      0x00001000
	#define LI_Doubt        0x00002000
	#define LI_Used         0x00004000  // ������������ ��� �������������
 #define LI_FRMT_Used    0x00008000  // Formatter used
	/*****  ������������ ����������� ������.  *****/
	#define LI_IsAtTable    0x00000400
	#define LI_IsNotAtTable 0x00000800
//end Line flags
#endif
