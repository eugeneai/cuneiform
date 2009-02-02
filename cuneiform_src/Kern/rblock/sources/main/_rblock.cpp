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

/*#include <windows.h>*/
#include <setjmp.h>
#include <assert.h>

#include "resource.h"
#include "rblock.h"
#include "mymem.h"
#include "newfunc.h"
#include "dpuma.h"
#include "ccom.h"
#include "cline.h"
#include "cpage.h"

//# include "new_c.h"
#include "compat_defs.h"
////////////// KERNEL //////////////////

extern "C"
{
	void PageLayout (void);
	void progress_finish(void);
	void EnableDebug( void );

	jmp_buf fatal_error_exit;	// For error handling
	INT nStrings;
	CLINE_handle HCLINE=0;
	INT nIncline;
}

Handle MainWindowD;





//###########################################
RBLOCK_FUNC(Bool32) RBLOCK_ExtractTextBlocks(Handle hCCOM,Handle hCPAGE,CLINE_handle hCLINE)
{
  SetReturnCode_rblock(IDS_ERR_NO);
  Open_Res_Log();

  MainWindowD=NULL;
  MainWindowD=LDPUMA_GetWindowHandle ("����������� ����� ���������");
  if(!MainWindowD)
    MainWindowD=LDPUMA_GetWindowHandle ("Main");
  HCLINE=hCLINE;

  PAGEINFO info={0};
  if(GetPageInfo(hCPAGE,&info))
	  nIncline=info.Incline2048;
  else
	  nIncline=0;

  if (setjmp (fatal_error_exit))
	{
		  progress_finish();
		  return FALSE;
	}

  EnableDebug();
  PageLayoutBlocks(hCCOM);
  OutputFragments(hCPAGE);
  Close_Res_Log();

  return TRUE;
}

////////////////////////////////////////////////
RBLOCK_FUNC(Bool32) RBLOCK_ExtractTextStrings(Handle hCCOM,Handle hCPAGE)
{
  SetReturnCode_rblock(IDS_ERR_NO);
  Open_Res_Log();

  if (setjmp (fatal_error_exit))
	{
		  progress_finish();
		  return FALSE;
	}

  nStrings = 0;
  EnableDebug();
  PageLayoutStrings(hCCOM,hCPAGE);
  Close_Res_Log();

  return TRUE;
}
////////////////////////////////////////////////
RBLOCK_FUNC(Bool32) RBLOCK_GetAnglePage(Handle hCCOM,Int32 * lpNominator,Int32 * lpDenominator)
{
 Bool32 rc = TRUE;
 SetReturnCode_rblock(IDS_ERR_NO);
 Open_Res_Log();

  if (setjmp (fatal_error_exit))
	{
		  progress_finish();
		  return FALSE;
	}
  EnableDebug();
  _ASSERT(lpNominator);
  _ASSERT(lpDenominator);
  _ASSERT(hCCOM);
  CalculatePageIncline(hCCOM, lpNominator,lpDenominator);
  Close_Res_Log();

  return rc;
}
