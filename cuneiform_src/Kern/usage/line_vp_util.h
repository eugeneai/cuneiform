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
/*  ��������   :  13.03.01                                                    */
/*  ����       :  'Line_VP_Util.H'                                            */
/*  ���������� :  ��������� ������ ������ � ������� ������� LNS.              */
/*  ���������� :  ������������ �����/������ (� ��������������� ������� � ���).*/
/*----------------------------------------------------------------------------*/
#include "cline.h"
/* !!! */Bool LoadLinesVP_rv (Handle hC, int Type, void *vB, char *pStr, Word16 *pCode);
Bool LoadLinesVP_rv (CLINE_handle hC, int Type, void *vB, char *pStr, Word16 *pCode);
/* !!! ������ ��� ������ MyReSetLines */void GetKeysPumaVP (void *vLti, Word32 *pKeyHor, Word32 *pKeyVer);
Bool GetSomeKeys_rv (void *vB, Word32 *pKeyHor, Word32 *pKeyVer
					 , int *pCntHor, int *pCntVer, char *pStr);
Bool LoadLinesTotalInfo_rv (Handle hC, void *vB, char *pStr);
Bool LoadLinesSpecInfo (Handle hC, void *vB, Word32 Key, int Cnt);
Bool LoadLinesInfo_rv (CLINE_handle hC, void *vB, char *pStr,Bool Hori);
/* !!! */Bool MyReSetLines (void *vLti, int MaxNumLin, Handle hCPage, Word32 HoriType
				   , Word32 VertType, char *pStr);
Bool MyReSetLines(void* vLines,int Count,CLINE_handle hCLINE,char *pStr);
Bool ReferForLinesVP (void *vLti, void *vB);
/* !!! */Bool PrepareLinesVP_rv (void *vB, void **vvData);
Bool ReferForAndCountLinesVP (void *vB, void **vvData,int* pcount,Bool Hori);
Bool IsWarnAtLine (void *vLns, Bool Hori);
Bool IsWarnAtLine (void *vLine,Bool Hori,Bool zero);
/* !!! */void MarkTableLines (void *vLti, int *pForw, int MyMaxL);
void MarkTableLines (void *vHorLines,int hor_count,void *vVerLines,int ver_count, int *pForw, int MyMaxL);
Bool LineBringToTable (int i, int *pForw, int MyMaxL);
/*---------------------------------------------------------------------------*/
