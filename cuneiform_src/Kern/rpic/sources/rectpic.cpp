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

/*# include <windows.h>*/
# include <stdio.h>

#include "dpuma.h"
#include "pumadef.h"
#include "mainpic.h"
#include "cpage.h"
#include "ccom.h"
#include "rstr.h"
#include "rpic.h"

/************************ External Handles from DPUMA *************************/
extern Handle hShowCheckLetters;
/******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
Bool32 CheckAreaForComps(Int32 hCCOM,Int32 hCCOM_big, Rect32 rect, Int32 Height, Word32 *Result1, Word32 *Result2)
{
	CCOM_comp * comp;
	Word32 i;
	comp =  NULL;

	Rect16 rect1;
	Word32 key = 111;
	Word32 color = 23000;

	Handle MainWindowD=NULL;
    MainWindowD=LDPUMA_GetWindowHandle ("����������� ����� ���������");
    if(!MainWindowD)
       MainWindowD=LDPUMA_GetWindowHandle ("Main");


	*Result1 = 0;
	*Result2 = 0;

	if(!LDPUMA_Skip(hShowCheckLetters))
	{
		rect1.top = (Word16)rect.top;
		rect1.left = (Word16)rect.left;
		rect1.bottom = (Word16)rect.bottom;
		rect1.right = (Word16)rect.right;
		LDPUMA_DrawRect(MainWindowD, &rect1, 0, 23635, 4, key);
	}

//stepa_am
comp = CCOM_GetFirst(hCCOM_big,NULL);
	while (comp)
	{
		if(comp->h < Height/6) goto lNextComp_big;
		if(comp->h > Height*1.5) goto lNextComp_big;
		if(comp->upper < rect.top) goto lNextComp_big;
		if(comp->left < rect.left) goto lNextComp_big;
		if(comp->upper + comp->h > rect.bottom) goto lNextComp_big;
		if(comp->left + comp->w > rect.right) goto lNextComp_big;
		if((comp->h < Height/3 )&&(comp->upper < rect.top))goto lNextComp_big;
		for(i=0; i<nPics; i++)
		{
			if ( (comp->upper >= pPics[i].upper)&&
				 (comp->left >= pPics[i].left)&&
				 (comp->upper + comp->h < pPics[i].upper + pPics[i].h)&&
				 (comp->left + comp->w <= pPics[i].left + pPics[i].w))
			{
				goto lNextComp_big;
			}
		}

		if((comp->h > Height*0.5)&&(comp->h < Height*1.5))
		{
			(*Result1)++;
			if(!LDPUMA_Skip(hShowCheckLetters))
			{
				rect1.left = comp->left;
				rect1.top = comp->upper;
				rect1.right = comp->left + comp->w;
				rect1.bottom = comp->upper + comp->h;
				LDPUMA_DrawRect(MainWindowD, &rect1, 0, color, 8, key);
			}
			goto lNextComp_big;
		}

		if((comp->h > Height/3*0.5)&&(comp->h < Height/3*1.5))
		{
			(*Result2)++;
			if(!LDPUMA_Skip(hShowCheckLetters))
			{
				rect1.left = comp->left;
				rect1.top = comp->upper;
				rect1.right = comp->left + comp->w;
				rect1.bottom = comp->upper + comp->h;
				LDPUMA_DrawRect(MainWindowD, &rect1, 0, color, 2, key);
			}
			goto lNextComp_big;
		}

lNextComp_big:
		comp = CCOM_GetNext(comp,NULL);
	}
//end stepa_am

	comp = CCOM_GetFirst(hCCOM,NULL);
	while (comp)
	{
		if(comp->h < Height/6) goto lNextComp;
		if(comp->h > Height*1.5) goto lNextComp;
		if(comp->upper < rect.top) goto lNextComp;
		if(comp->left < rect.left) goto lNextComp;
		if(comp->upper + comp->h > rect.bottom) goto lNextComp;
		if(comp->left + comp->w > rect.right) goto lNextComp;
		if((comp->h < Height/3 )&&(comp->upper < rect.top))goto lNextComp;
		for(i=0; i<nPics; i++)
		{
			if ( (comp->upper >= pPics[i].upper)&&
				 (comp->left >= pPics[i].left)&&
				 (comp->upper + comp->h < pPics[i].upper + pPics[i].h)&&
				 (comp->left + comp->w <= pPics[i].left + pPics[i].w))
			{
				goto lNextComp;
			}
		}

		if((comp->h > Height*0.5)&&(comp->h < Height*1.5))
		{
			(*Result1)++;
			if(!LDPUMA_Skip(hShowCheckLetters))
			{
				rect1.left = comp->left;
				rect1.top = comp->upper;
				rect1.right = comp->left + comp->w;
				rect1.bottom = comp->upper + comp->h;
				LDPUMA_DrawRect(MainWindowD, &rect1, 0, color, 8, key);
			}
			goto lNextComp;
		}

		if((comp->h > Height/3*0.5)&&(comp->h < Height/3*1.5))
		{
			(*Result2)++;
			if(!LDPUMA_Skip(hShowCheckLetters))
			{
				rect1.left = comp->left;
				rect1.top = comp->upper;
				rect1.right = comp->left + comp->w;
				rect1.bottom = comp->upper + comp->h;
				LDPUMA_DrawRect(MainWindowD, &rect1, 0, color, 2, key);
			}
			goto lNextComp;
		}

lNextComp:
		comp = CCOM_GetNext(comp,NULL);
	}

	if(!LDPUMA_Skip(hShowCheckLetters))
	{
		LDPUMA_Console("RPIC_������ �� ���������  \n");
		LDPUMA_WaitUserInput(hShowCheckLetters, MainWindowD);
		LDPUMA_DeleteRects(MainWindowD, key);
	}

	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
Bool32 SearchRectanglePictures(Int32 hCCOM,Int32 hCCOM_big,Handle hCPAGE)
{
	Word32 i,j;
	CCOM_comp pic;
	CCOM_comp * comp;
	Word16 pLocalHystogram[MaxHeightOfLetter];
	Word32 nLocalComps;
	Word32 MaxLocal, nMaxLocal;
	Word32 Result1, Result2, Result3, Result4, tmp1, tmp2;
	Rect32 rect;
	Int32 LengthTotal,LengthByIntervals;
	Word32 BlockType;
	RecRaster rec;
	RecVersions vs;
	Int16 Language;
	RPIC_Comp_Rect CompRect;


	BlockType = CPAGE_GetInternalType("pic's to letters boxes");

	for(i=0; i<nPics; i++)
	{
		pic = pPics[i];
		my_upper  = pic.upper;
		my_left   = pic.left;
		my_bottom = pic.upper + pic.h;
		my_right  = pic.left + pic.w;


		//Additional parameter - local distribution of heights
		//in case of local fragment with different (from main) height
		nLocalComps = 0;
		for(j=0;j<MaxHeightOfLetter;j++)
		{
			pLocalHystogram[j] = 0;
		}

//stepa_am
		comp = CCOM_GetFirst(hCCOM_big, &MyFiltrateIn);
		while(comp)
		{
			if( (comp->h < MaxHeightOfLetter) && (comp->h > MinHeightOfLetter) )
			{
				pLocalHystogram[comp->h]++;
				nLocalComps++;
			}
			comp = CCOM_GetNext(comp, &MyFiltrateIn);
		}
//end stepa_am

		comp = CCOM_GetFirst(hCCOM, &MyFiltrateIn);
		while(comp)
		{
			if( (comp->h < MaxHeightOfLetter) && (comp->h > MinHeightOfLetter) )
			{
				pLocalHystogram[comp->h]++;
				nLocalComps++;
			}
			comp = CCOM_GetNext(comp, &MyFiltrateIn);
		}

		if (nLocalComps!=0)
		{
			MaxLocal = pLocalHystogram[0];
			for(j=0;j<MaxHeightOfLetter;j++)
			{
				if(pLocalHystogram [j] > MaxLocal)
				{
					MaxLocal = pLocalHystogram [j];
					nMaxLocal = j;
				}
			}

			Result1 = 0;
			Result2 = 0;
			sprintf(tmp_str, " %i Result1 (must be 0)\n", Result1);
			LDPUMA_FPuts(logFile_comp,tmp_str);
			sprintf(tmp_str, " %i Result2 (must be 0)\n", Result2);
			LDPUMA_FPuts(logFile_comp,tmp_str);
			sprintf(tmp_str, " %i (nComps)\n", nComps);
			LDPUMA_FPuts(logFile_comp,tmp_str);

//stepa_am
			comp = CCOM_GetFirst(hCCOM_big, &MyFiltrateIn);
			while(comp)
			{
				//sprintf(tmp_str, " %i  (comp)\n", comp);
				//LDPUMA_FPuts(hFile,tmp_str);
				if( (comp->h < MaxHeightOfLetter-1) && (comp->h > MinHeightOfLetter) )
				{

					sprintf(tmp_str, " %i  (comp->h)\n", comp->h);
					LDPUMA_FPuts(logFile_comp,tmp_str);
					sprintf(tmp_str, " %i  (pHystogram[comp->h])\n", pHystogram[comp->h]);
					LDPUMA_FPuts(logFile_comp,tmp_str);


					//Result1 += OVERALL*pHystogram[comp->h];
					Result1 += pHystogram[comp->h]/20+pHystogram[comp->h-1]/20+pHystogram[comp->h+1]/20;
					if(comp->h - nMaxLocal < DIFFERENCE1)
					{
						//Result2 += LOCAL*pLocalHystogram[comp->h];
						Result2 += pLocalHystogram[comp->h]+pLocalHystogram[comp->h-1]+pLocalHystogram[comp->h+1];
					}
				}
				comp = CCOM_GetNext(comp, &MyFiltrateIn);
			}
//end stepa_am

			comp = CCOM_GetFirst(hCCOM, &MyFiltrateIn);
			while(comp)
			{
				//sprintf(tmp_str, " %i  (comp)\n", comp);
				//LDPUMA_FPuts(hFile,tmp_str);
				if( (comp->h < MaxHeightOfLetter-1) && (comp->h > MinHeightOfLetter) )
				{

					sprintf(tmp_str, " %i  (comp->h)\n", comp->h);
					LDPUMA_FPuts(logFile_comp,tmp_str);
					sprintf(tmp_str, " %i  (pHystogram[comp->h])\n", pHystogram[comp->h]);
					LDPUMA_FPuts(logFile_comp,tmp_str);


					//Result1 += OVERALL*pHystogram[comp->h];
					Result1 += pHystogram[comp->h]/20+pHystogram[comp->h-1]/20+pHystogram[comp->h+1]/20;
					if(comp->h - nMaxLocal < DIFFERENCE1)
					{
						//Result2 += LOCAL*pLocalHystogram[comp->h];
						Result2 += pLocalHystogram[comp->h]+pLocalHystogram[comp->h-1]+pLocalHystogram[comp->h+1];
					}
				}
				comp = CCOM_GetNext(comp, &MyFiltrateIn);
			}

			//Result1 = Result1/nComps;
			Result1 = Result1/10;
			//Result2 = Result2/nLocalComps;
			Result2 = Result2/20;

			sprintf(tmp_str , " Picture %i (i)\n", i);
			LDPUMA_FPuts(logFile_comp,tmp_str);
			sprintf(tmp_str, " %i (Result1)\n", Result1);
			LDPUMA_FPuts(logFile_comp,tmp_str);
			sprintf(tmp_str, " %i (Result2)\n", Result2);
			LDPUMA_FPuts(logFile_comp,tmp_str);

			if(Result1 + Result2 > CONDITION1)
			{
				DeleteFromPics(i);
				//i--;
				continue;
			}
		}

		/**************************************************************************/
		/*                      Analys by comp's count of begins&ends             */
		/**************************************************************************/

		CCOM_USER_BLOCK uBlock;
		uBlock.code = CCOM_UB_BEGENDS;
		if( CCOM_GetUserBlock(&pPics[i], &uBlock) )
		{
			if(*(Word8*)uBlock.data > 100)
			{
				continue;
			}
		}

		/**************************************************************************/
		/*                      Analys by comp's intervals                        */
		/**************************************************************************/

		//CCOM_USER_BLOCK uBlock;
		uBlock.code = CCOM_UB_DENSITY;
		if( CCOM_GetUserBlock(&pPics[i], &uBlock) )
		{
			LengthByIntervals = *(Int32*)uBlock.data;
			LengthTotal = pPics[i].h * pPics[i].w;

			if(LengthByIntervals==0)
			{
				return FALSE;
			}

			if(LengthTotal/LengthByIntervals > CONDITION2)
			{
				DeleteFromPics(i);
				//i--;
			}
		}

	}

	/***********************************************************************************/
	/*
	{
	Rect16 rect1;
	for (i=0; i<nPics; i++)
	{
	rect1.left = pPics[i].left;
	rect1.top = pPics[i].upper;
	rect1.right = pPics[i].left + pPics[i].w;
	rect1.bottom = pPics[i].upper + pPics[i].h;
	LDPUMA_DrawRect(NULL, &rect1, 0, 200, 2, 111);
	}
	LDPUMA_Console("RPIC_Before \n");
	LDPUMA_WaitUserInput(NULL, NULL);
	LDPUMA_DeleteRects(NULL, 111);
	}
	/***********************************************************************************/
	/************** final union all crossed and included pictures ******************/
	CCOM_comp common;
	for (i=0; i<nPics; i++)
	{
		if(pPics[i].large & CCOM_LR_KILLED)
		{
			continue;
		}
		for (j=0; j<nPics; j++)
		{
			if(pPics[j].large & CCOM_LR_KILLED)
			{
				continue;
			}
			if ( (pPics[i].upper  < pPics[j].upper)&&
				(pPics[i].left   < pPics[j].left)&&
				(pPics[i].left   + pPics[i].w > pPics[j].left + pPics[j].w)&&
				(pPics[i].upper  + pPics[i].h > pPics[j].upper + pPics[j].h) )
			{
				if((pPics[i].type!=CCOM_CH_LETTER)||(pPics[j].type!=CCOM_CH_LETTER))
				{
					pPics[i].type = CCOM_CH_MERGE;
				}
				DeleteFromPics (j);
				//j--;
			}
		}
	}

	/***********************************************************************************/
	/*
	{
	Rect16 rect1;
	for (i=0; i<nPics; i++)
	{
	rect1.left = pPics[i].left;
	rect1.top = pPics[i].upper;
	rect1.right = pPics[i].left + pPics[i].w;
	rect1.bottom = pPics[i].upper + pPics[i].h;
	LDPUMA_DrawRect(NULL, &rect1, 0, 200, 2, 111);
	}
	LDPUMA_Console("RPIC_middle \n");
	LDPUMA_WaitUserInput(NULL, NULL);
	LDPUMA_DeleteRects(NULL, 111);
	}
	/***********************************************************************************/


	for (i=0; i<nPics; i++)
	{
		if(pPics[i].large & CCOM_LR_KILLED)
		{
			continue;
		}
		for (j=0; j<nPics; j++)
		{
			if(pPics[j].large & CCOM_LR_KILLED)
			{
				continue;
			}
			if (i==j) continue;
			if ( (pPics[i].upper  < pPics[j].upper + pPics[j].h)&&
				(pPics[i].left   < pPics[j].left  + pPics[j].w)&&
				(pPics[i].left  + pPics[i].w  > pPics[j].left)&&
				(pPics[i].upper + pPics[i].h  > pPics[j].upper) )
			{
				common = pPics[i];
				if (pPics[i].upper >= pPics[j].upper)
					common.upper = pPics[j].upper;
				if (pPics[i].left >= pPics[j].left)
					common.left = pPics[j].left;
				if (pPics[i].upper + pPics[i].h < pPics[j].upper + pPics[j].h)
					common.h = pPics[j].upper + pPics[j].h - pPics[i].upper;
				if (pPics[i].left  + pPics[i].w < pPics[j].left + pPics[j].w)
					common.w = pPics[j].left + pPics[j].w - pPics[i].left;
				common.h += pPics[i].upper - common.upper;
				common.w += pPics[i].left  - common.left;
				pPics[i] = common;
				/*
				if((pPics[i].type!=CCOM_CH_LETTER)||(pPics[j].type!=CCOM_CH_LETTER))
				{
				pPics[i].type = CCOM_CH_MERGE;
				}
				*/
				pPics[i].type = CCOM_CH_NOTLTR;
				DeleteFromPics (j);
				//j=0;
				//i=0;
			}
		}
	}
	/***********************************************************************************/
	/*
	{
	Rect16 rect1;
	for (i=0; i<nPics; i++)
	{
	rect1.left = pPics[i].left;
	rect1.top = pPics[i].upper;
	rect1.right = pPics[i].left + pPics[i].w;
	rect1.bottom = pPics[i].upper + pPics[i].h;
	LDPUMA_DrawRect(NULL, &rect1, 0, 200, 2, 111);
	}
	LDPUMA_Console("RPIC_after \n");
	LDPUMA_WaitUserInput(NULL, NULL);
	LDPUMA_DeleteRects(NULL, 111);
	}
	/***********************************************************************************/


	for(i=0; i<nPics; i++)
	{
		if(pPics[i].large & CCOM_LR_KILLED)
		{
			continue;
		}
		pic = pPics[i];
		my_upper  = pic.upper;
		my_left   = pic.left;
		my_bottom = pic.upper + pic.h;
		my_right  = pic.left + pic.w;
		/*
		Deleting from Pics, in case of Titles and "Bukvica", zero version,
		planing CHECK (by Oleg) for Letters in case of Bukvica, else check for
		comps with compatible heights in local area (horizontal).
		*/
		if(pPics[i].scale <= 3)
		{
			rect.top = pPics[i].upper;
			rect.left = pPics[i].left + pPics[i].w;
			rect.bottom = pPics[i].upper + pPics[i].h;
			rect.right = pPics[i].left + pPics[i].w + pPics[i].h;
			CheckAreaForComps(hCCOM,hCCOM_big, rect, nAverageHeight, &Result1, &Result2);

			if( (Result1 > 10)&&(pPics[i].type != CCOM_CH_NOTLTR))
			{
				if( CCOM_GetRaster(&pPics[i], &rec) &&
					CCOM_GetLanguage(hCCOM, &Language) &&
					RSTR_RecogOneLetter (&rec, (Word8)(Language), &vs) )
				{

					if( (vs.lnAltCnt > 0)&&
						(vs.Alt[0].Prob > 240)&&
						(vs.Alt[0].Code != 'i')&&
						(vs.Alt[0].Code != '1')&&
						(vs.Alt[0].Code != 'I')&&
						(vs.Alt[0].Code != 'l'))
					{
						pPics[i].type = CCOM_CH_LETTER;
						CompRect.upper = pPics[i].upper;
						CompRect.left = pPics[i].left;
						CompRect.h = pPics[i].h;
						CompRect.w = pPics[i].w;
						CPAGE_CreateBlock(hCPAGE, BlockType, 0, 0, &CompRect, sizeof(CompRect));

						DeleteFromPics(i);
						//i--;
						continue;
					}
				}
			}


			rect.top = pPics[i].upper - (Int32)(0.3*(double)(pPics[i].h));
			rect.left = pPics[i].left - 12*pPics[i].h;
			rect.bottom = pPics[i].upper + (Int32)(1.3*(double)(pPics[i].h));
			//rect.right = pPics[i].left + pPics[i].w;
			rect.right = pPics[i].left;
			CheckAreaForComps(hCCOM,hCCOM_big, rect, pPics[i].h, &Result1, &Result2);
			if(Result2 > 7)
			{
				rect.top = pPics[i].upper - (Int32)(0.3*(double)(pPics[i].h));
				rect.left = pPics[i].left - (Int32)(1.5*(double)(pPics[i].h));
				rect.bottom = pPics[i].upper + (Int32)(1.3*(double)(pPics[i].h));
				rect.right = pPics[i].left;
				CheckAreaForComps(hCCOM,hCCOM_big, rect, pPics[i].h, &tmp1, &tmp2);
				if(tmp2 == 0) Result2 = 0;
			}
			if((Result1 > 3)||(Result2 > 7))
			{
				pPics[i].type = CCOM_CH_LETTER;
				CompRect.upper = pPics[i].upper;
				CompRect.left = pPics[i].left;
				CompRect.h = pPics[i].h;
				CompRect.w = pPics[i].w;
				CPAGE_CreateBlock(hCPAGE, BlockType, 0, 0, &CompRect, sizeof(CompRect));

				DeleteFromPics(i);
				//i--;
				continue;
			}

			rect.top = pPics[i].upper - (Int32)(0.3*(double)(pPics[i].h));
			rect.left = pPics[i].left + pPics[i].w;
			rect.bottom = pPics[i].upper + (Int32)(1.3*(double)(pPics[i].h));
			rect.right = pPics[i].left + pPics[i].w + 12*pPics[i].h;
			CheckAreaForComps(hCCOM,hCCOM_big, rect, pPics[i].h, &Result3, &Result4);
			if(Result4 > 0)
			{
				rect.top = pPics[i].upper - (Int32)(0.3*(double)(pPics[i].h));
				rect.left = pPics[i].left + pPics[i].w;
				rect.bottom = pPics[i].upper + (Int32)(1.3*(double)(pPics[i].h));
				rect.right = pPics[i].left + pPics[i].w + (Int32)(1.5*(double)(pPics[i].h));
				CheckAreaForComps(hCCOM,hCCOM_big ,rect, pPics[i].h, &tmp1, &tmp2);
				if(tmp2 == 0) Result4 = 0;
			}
			if( (Result3 > 3) ||
				(Result4 > 7) ||
				(Result1 + Result3 > 3)||
				(Result2 + Result4 > 7))
			{
				pPics[i].type = CCOM_CH_LETTER;
				CompRect.upper = pPics[i].upper;
				CompRect.left = pPics[i].left;
				CompRect.h = pPics[i].h;
				CompRect.w = pPics[i].w;
				CPAGE_CreateBlock(hCPAGE, BlockType, 0, 0, &CompRect, sizeof(CompRect));

				DeleteFromPics(i);
				//i--;
				continue;
			}
		}
        }

        return TRUE;
}
