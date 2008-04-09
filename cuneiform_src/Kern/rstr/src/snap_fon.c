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

// ������ � ����������� DFON (���� ��� ����)

#include "tuner.h"

#ifdef _USE_DFON_

#include <windows.h>
#include "nt_types.h"
#include "rstr.h"

BOOL snap_show_text(BYTE *txt);

static HINSTANCE hDFon = NULL;

static int DFon_SendRasterStat(RecRaster* rr, Handle pPaintWnd, Word8 let)
{
	snap_show_text("version without DFON.DLL");
	return 0;
}

static void DFon_TerminatedStat(Word32 wParam)
{ }
//////////
int  (*DFon_SendRaster)(RecRaster* rr, Handle pPaintWnd, Word8 let)=DFon_SendRasterStat;
void (*DFon_Terminated)(Word32 wParam)=DFon_TerminatedStat;

////////////
void DFon_NewPage(char *name)
{
	void (*DFon_NewPg)(char*);

	if( !hDFon )
       hDFon = LoadLibrary("DFON.DLL");

	if( hDFon )
	{
	 DFon_SendRaster = (void *)GetProcAddress(hDFon,"DFon_SendRaster");
	 DFon_Terminated = (void *)GetProcAddress(hDFon,"DFon_Terminated");

	 if( !DFon_SendRaster )
	      DFon_SendRaster = DFon_SendRasterStat;
	 if ( !DFon_Terminated )
          DFon_Terminated = DFon_TerminatedStat;

	 DFon_NewPg = (void *)GetProcAddress(hDFon,"DFon_NewPage");
	 if( DFon_NewPg )
         DFon_NewPg(name);
	}
	else
	{
		DFon_SendRaster = DFon_SendRasterStat;
        DFon_Terminated = DFon_TerminatedStat;
	}
}
///////////
void DFON_Done(void)
{
	void (*DFON_DoneDll)(void);

	if( hDFon )
	{
		DFON_DoneDll = (void *)GetProcAddress(hDFon,"DFON_Done");
		if( DFON_DoneDll )
		    DFON_DoneDll();

		FreeLibrary(hDFon);
	}

	hDFon = NULL;
}
///////////
#endif