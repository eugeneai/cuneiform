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

#ifndef __NEW_C_H__
#define __NEW_C_H__

//#include <windows.h>

//# include "iolib.h"
# include "resource.h"
# include "dpuma.h"
# include "pumadef.h"
# include "layout.h"
# include "extract.h"
# include "kernel.h"
//# include "status.h"
# include "ccom.h"
# include "cpage.h"
# include "newfunc.h"
# include "exc.h"
# include "excdefs.h"
# include "cstr.h"
# include "cstrdefs.h"
# include "polyblock.h"
# include "ctp.h"
# include "pic_n_table.h"
# include "rpic.h"
# include "rstr.h"

////////////////////////////////////////////////////////////////////////////////
#define LOGFILENAME_COMP "rom_comp.log"
#define RESFILENAME_COMP "rom_comp.res"
#define LOGFILENAME_PICT "rom_pict.log"
#define RESFILENAME_PICT "rom_pict.res"
#define LOGFILENAME_BLOCKS "rom_BLOCKS.log"
#define RESFILENAME_BLOCKS "rom_BLOCKS.res"

# define ROOTS_QUANTUM			1024
# define COMPS_QUANTUM			128
# define PICS_QUANTUM		16
# define BIG_LETTERS_QUANTUM	16
# define DUST_LENGHT			4
# define HOR_BOUND_SIZE		20
# define VER_BOUND_SIZE		10
# define MinHeightOfLetter 10
# define MaxHeightOfLetter 100
# define DIFFERENCE1  4  //3
# define CONDITION1      700
# define ROM_TYPE_TABLE 111;
//# define BOUND 15
# define BOUND 1
# define INC_COEFF		 1.4
# define DEC_COEFF		 0.9
# define BOUND_SIZE		 30
////////////////////////////////////////////////////////////////////////////////

#ifdef __LOAD_ROOTS_C__
	#define EXTERN
	#define VAL1(a)		= a
	#define VAL2(a,b)	= { a,b }
	#define VAL4(a,b,c,d)	= { a,b,c,d }
#else
	#define EXTERN		extern
	#define VAL1(a)
	#define VAL2(a,b)
	#define VAL4(a,b,c,d)
#endif

////////////////////////////////////////////////////////////////////////////////
EXTERN Handle resFile_comp;
EXTERN Handle logFile_comp;
EXTERN Handle resFile_pict;
EXTERN Handle logFile_pict;
EXTERN Handle resFile_blocks;
EXTERN Handle logFile_blocks;

EXTERN BYTE *CellsPage VAL1(NULL); //Rom 08-02-99
EXTERN RPIC_Comp_Rect * pBigLetters VAL1(NULL);
EXTERN int nBigLetters  VAL1(0);
EXTERN Word32 nPics;
EXTERN CCOM_comp * pPics VAL1(NULL);
EXTERN Word16 pBlockHystogram[MaxHeightOfLetter];
EXTERN int my_upper, my_left, my_bottom, my_right;
EXTERN char tmp_str[200];
EXTERN Word32 nComps;
EXTERN Word32 page_count VAL1(0);
EXTERN char* file_name;
EXTERN Int32 exthCCOM;
////////////////////////////////////////////////////////////////////////////////


#endif
