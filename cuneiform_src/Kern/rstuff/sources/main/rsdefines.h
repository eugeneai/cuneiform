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
/*  ����       :  'RSTimer.cpp'                                               */
/*  ���������� :  ��������� ����������                                        */
/*  ���������� :                                                              */
/*----------------------------------------------------------------------------*/
#ifndef _RSDEFINES_H_
#define _RSDEFINES_H_
////////////////////////////////////////////////////////////////////////////////
# if defined (_DEBUG)
 # pragma message( __FILE__" : RStuff types definition")
# endif // (_DEBUG)
//////////////////////////////////////////////////////////////////////////////////
//#define _NO_CFIO
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "globus.h"
#include "mpumatime.h"
#include "rstuff.h"
/////////////////////////////////////////////////////////////////////////////////////////////
//
typedef void    (*RSPROGRESSSTART)       (void);
typedef Bool32  (*RSPROGRESSSTEP)        (Word32, Word32);
typedef void    (*RSPROGRESSFINISH)      (void);
typedef Bool32  (*RSINITPRGTIME)         (void);
typedef PRGTIME (*RSSTOREPRGTIME)        (Word32, Word32);
typedef void    (*RSRESTOREPRGTIME)      (PRGTIME);
typedef Bool32  (*RSDONEPRGTIME)         (void);
typedef Bool32  (*RSDPUMASKIPCOMPONENT)  (void);
typedef Bool32  (*RSDPUMASKIPTURN)       (void);
typedef void    (*RSSETRETURNCODE32)     (Word32);
typedef char *  (*RSGETMODULEPATH)       (void);
typedef void    (*RSSETUPDATE)           (Word32, Word32);
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define   RStuffMaxNumLines             2000
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define   RS_SVL_FIRST_STEP              0x1
#define   RS_SVL_SECOND_STEP             0x2
/////////////////////////////////////////////////////////////////////////////////////////////////////
// ��� ������� ���������
#define     RSTUFF_AboutLines_SizeMyBuff    492000
#define     RSTUFF_AboutLines_SizeWorkMem   180000//165000
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
typedef struct tagRSLinesBuffer
{
	void * HLinesBufferA;
	void * VLinefBufferA;
	void * HLinesBufferB;
	void * VLinefBufferB;
} RSLinesBuffer, *PRSLinesBuffer;
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
#endif //_RSDEFINES_H_
