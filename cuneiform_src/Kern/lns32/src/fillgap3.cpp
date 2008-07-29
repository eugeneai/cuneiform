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

#include "lnslang.h"

#ifndef PPS_MAC
#pragma hdrstop
#endif

#include "fillgap3.h"
#include "fillgap_.h"
#include "lns.h"

static Word8* buff=NULL;
static Word8* buff_=NULL;
static int nByteWidth=0;

static Bool16 No_Fillgap = FALSE;

extern LnsSetupStr lnsSetup;

 // fill gaps with 3 pels
Bool     FillGap3_Init(int wImageByteWidth)
{
	No_Fillgap = lnsSetup.nOptions & LSS_NOFILLGAP3_FILTER;

   if (!No_Fillgap) // no flag - look to ini
   {
      int nSmoothWidth = LnsGetProfileInt( "nSmoothWidth", 4 ); // by default 3 pixel gaps are filled
      No_Fillgap = (nSmoothWidth == 0);
   }

	if ( !No_Fillgap )				//*******Rom
	{
		nByteWidth= wImageByteWidth;

		buff_ = (Word8*)malloc(nByteWidth+4);
		if (buff_==NULL)
			return FALSE;
		memset(buff_, 0xff, nByteWidth + 4);

		buff = buff_+4;
		return TRUE;
	}
	else
	{
		return TRUE;
	}
}

Word8*   FillGap3_SubstLine( Word8* line )
{
	if ( !No_Fillgap )				//*******Rom
	{
		if (buff==NULL)
			return line;

		Word8* res = buff-1;

		int xx = 0;
		int bytes =nByteWidth;
		while (bytes--)
		{
			xx = ((xx & 0x0f) << 8) | *line++;
			xx = FillGap3_Tbl[xx];
			*res++ &= (Word8)( (xx | 0xf000) >> 8);        // black assumed 1
			*res =    (Word8)xx;
		}

		return buff;
	}
	else
	{
		return line;
	}
}

void     FillGap3_Done()
{
	if ( !No_Fillgap )				//*******Rom
	{
		if (buff_)
		{
			free(buff_);
			buff_ = NULL;
			buff = NULL;
		}
	}
	else
	{
	}
}


