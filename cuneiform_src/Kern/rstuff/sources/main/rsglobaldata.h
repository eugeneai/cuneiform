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
/*  ����       :  'RSTGlobalData.h'                                           */
/*  ���������� :  �������� � ���������� ���������� ����������                 */
/*  ���������� :                                                              */
/*----------------------------------------------------------------------------*/
#ifndef _RSGLOBALDATA_H_
#define _RSGLOBALDATA_H_

////////////////////////////////////////////////////////////////////////////////
# if defined (_DEBUG)
 # ifdef __RSTUFF_CPP__
  # pragma message( __FILE__" : RStuff global variables definition")
 # else
  # pragma message( __FILE__" : RStuff global variables declardtion")
 # endif
# endif // (_DEBUG)
////////////////////////////////////////////////////////////////////////////////
#include "globus.h"
#include "rsdefines.h"
#include "lnsdefs.h"

// predefined
#ifdef __RSTUFF_CPP__
	#define EXTERN
	#define VAL(a)		    = a
    #define VALM(a)		    = {a}
	#define VAL2(a,b)	    = { a,b }
	#define VAL4(a,b,c,d)	= { a,b,c,d }
#else
	#define EXTERN		extern
	#define VAL(a)
	#define VALM(a)
	#define VAL2(a,b)
	#define VAL4(a,b,c,d)
#endif

////////////////////////////////////////////////

EXTERN RSCBProgressPoints   ProgressPoints      VALM(NULL);
EXTERN LinesTotalInfo       *gLTInfo            VAL(NULL);

EXTERN RSLinesBuffer        gLinesData          VALM(NULL);

EXTERN Word32               gKillComponents     VAL(1);
EXTERN Word32               gKillZone           VAL(1);
EXTERN Word32               gKillRate           VAL(127);
EXTERN Int32                gComponentRange     VAL(0);
EXTERN Int32                bShowLineDebug      VAL(FALSE);
EXTERN Int32                bShowStepLineDebug  VAL(FALSE);
EXTERN Int32                bShowLineDebugData  VAL(FALSE);

EXTERN Handle               hLineKillerWindow                   VAL(NULL);
EXTERN Handle               hDebugRoot                          VAL(NULL);
EXTERN Handle               hDebugKillLines                     VAL(NULL);
EXTERN Handle               hDebugKillLinesStep                 VAL(NULL);
EXTERN Handle               hDebugKillLinesData                 VAL(NULL);
EXTERN Handle               hDebugKillLinesShowComponentsBefore VAL(NULL);
EXTERN Handle               hDebugKillLinesShowComponentsAfter  VAL(NULL);
EXTERN	Word8				db_spec_prj			VAL(0);
#endif //_RSGLOBALDATA_H_
////////////////////////////////////////////////////////////////////////////////////
//end of file
