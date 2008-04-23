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

/**********  ���������  ****************************************************************************/
/*  �����,                                                                                         */
/*  �����������                                                                                    */
/*  ������     :                                                                                   */
/*  ��������   :  08.09.00                                                                         */
/*  ����       :  'AboutLines.AboutLin.CPP'                                                        */
/*  ���������� :                                                                                   */
/*  ���������� :                                                                                   */
/*-------------------------------------------------------------------------------------------------*/
#include <stdio.h>
/*#include <windows.h>*/
/*  interface our-other  */
#include "lnsdefs.h"
#include "dpuma.h"
#include "rsdefines.h"
#include "rsmemory.h"
#include "rsfunc.h"
#include "resource.h"
#include "cline.h"
/*  interface our-my     */
/*  interface my        */
#include "un_err.h"
#include "aboutlines.buffer.h"
/*  interface my-my      */
#include "un_buff.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////
// 
static char *Buffer = NULL;/*[SizeMyBuff]*/;
static char *WorkMem = NULL;/*[SizeWorkMem]*/;
/////////////////////////////////////////////////////////////////////////////////////////////////////
// 
Bool32 AboutLines (PRSPreProcessImage Image, Bool32 *BadScan, Int32 *ScanQual)
{
	int SizeMain, SizeWork;
//	char Str[256];
//	Bool ret;
//	LineInfo *pLns;
//	LinesTotalInfo *pLti;
	UN_BUFF MainBuff = {0};
//	void *vLti;
	void *vMain;
	char *cWork;
	Bool32 bRc = TRUE;
	
	//////////////////////////////////////////////////////////////////////////////////
	Buffer  = (char *)RSTUFFDAlloc(RSTUFF_AboutLines_SizeMyBuff,"����� � AboutLines");
	WorkMem = (char *)RSTUFFDAlloc(RSTUFF_AboutLines_SizeWorkMem,"������� ����� � AboutLines");

	if (Buffer == NULL || WorkMem == NULL )
	{
		SetReturnCode((Word16)IDS_RSTUFF_ERR_NO_MEMORY);
		bRc =  FALSE;
	}
	
	if ( bRc )
		do
		{
			//////////////////////////////////////////////////////////////////////////////////////
			/*  1. ��������.  */
			if ((Image->pgneed_clean_line==NULL)&&(BadScan!=NULL))
				break;
				//return TRUE;
			
			/*  2. �������������.  */
			vMain = Buffer;
			SizeMain = RSTUFF_AboutLines_SizeMyBuff;
			MainBuff.vBuff    = vMain;
			MainBuff.SizeBuff = SizeMain;
			MainBuff.vCurr    = MainBuff.vBuff;
			MainBuff.SizeCurr = MainBuff.SizeBuff;
			cWork = WorkMem;
			SizeWork = RSTUFF_AboutLines_SizeWorkMem;
			
//		   extern Handle hUseCLine;
/*		   if(LDPUMA_Skip(hUseCLine))
		   {
			//  3. ��������� ��������� ������ - �����.  
			ret = LoadData_rv (Image->hCPAGE, UN_LD_LinesVP, (void *)(&MainBuff), Str, 0);
			if ((ret!=RV_TRUE)&&(ret!=RV_EMPTY))
			{
				if (1)
					LDPUMA_ConsoleN (Str);

				bRc = FALSE;
				break;
				//return FALSE;
			}
			if (ret==RV_EMPTY)
			{
				if (Image->pgneed_clean_line != NULL)
				{
					*Image->pgneed_clean_line = FALSE;
					if (1)
						LDPUMA_ConsoleN ("RSource: �� ���� ������� �����!");
				}
				if (BadScan!=NULL)
				{
					if (1)
						LDPUMA_ConsoleN ("RSource: �������� ������������ : �� ����, �����.");
					*BadScan = TRUE;
					*ScanQual = 100;
				}
				break;
				//return TRUE;
			}
			if (Image->pgneed_clean_line!=NULL)
			{
				*Image->pgneed_clean_line = FALSE;
				ret = GetComplexData_rv (UN_LD_LinesVP, UN_DA_Unknown
					, (void *)(&MainBuff), &vLti);
				if ((ret!=RV_TRUE)&&(ret!=RV_EMPTY))
				{
					bRc = FALSE;
					break;
					//return FALSE;
				}
				pLti = (LinesTotalInfo *)vLti;
				n = pLti->Hor.Cnt;
				pLns = pLti->Hor.Lns;
				for (i=0; i<n; i++)
				{
					if (pLns[i].Flags & LI_IsTrue)
						*Image->pgneed_clean_line = TRUE;
				}
				n = pLti->Ver.Cnt;
				pLns = pLti->Ver.Lns;
				for (i=0; i<n; i++)
				{
					if (pLns[i].Flags & LI_IsTrue)
						*Image->pgneed_clean_line = TRUE;
				}
				if (1)
				{
					if (*Image->pgneed_clean_line)
						LDPUMA_ConsoleN ("RSource: ����� ����� �����.");
					else
						LDPUMA_ConsoleN ("RSource: �� ���� ������� �����!");
				}
			}
		   }
		   else
		   {*/
			if (Image->pgneed_clean_line!=NULL)
			{
				*Image->pgneed_clean_line = FALSE;
				CLINE_handle hCLINE=*((CLINE_handle*)(Image->phCLINE));
				BOOL fl_break=FALSE;
				for(CLINE_handle hline=CLINE_GetFirstLine(hCLINE);hline;hline=CLINE_GetNextLine(hline))
				{
					CPDLine cpdata=CLINE_GetLineData(hline);
					if(!cpdata)
						continue;
					if(cpdata->Flags&LI_IsTrue)
					{
						*Image->pgneed_clean_line=TRUE;
						fl_break=TRUE;
					}
					if(fl_break)
						break;
				}
				if (1)
				{
					if (*Image->pgneed_clean_line)
						LDPUMA_ConsoleN ("RSource: ����� ����� �����.");
					else
						LDPUMA_ConsoleN ("RSource: �� ���� ������� �����!");
				}
			}
//		   }

			if (BadScan!=NULL)
			{
				if (1)
					LDPUMA_ConsoleN ("RSource: �������� ������������ : �� ���� ���� ����������.");
				*BadScan = TRUE;
				*ScanQual = 100;
			}
		} while ( false );

	RSTUFFFree(Buffer);
	RSTUFFFree(WorkMem);

	return bRc;
}
/*----------------------------------------------------------------------------*/
