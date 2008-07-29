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
#include <stddef.h>

#include "cstr.h"
#include "compat_defs.h"

static HINSTANCE hSJTL = 0;

typedef int (*FSJTL_1)(char*);
typedef int (*FSJTL_2)(char*,CSTR_line,int);
typedef int (*FSJTL_3)(char*, char*);
typedef void (*FSJTL_4)(void);

static FSJTL_1 fSJTL_save = NULL;
static FSJTL_2 fSJTL_save_old = NULL;
static FSJTL_3 fSJTL_open = NULL;
static FSJTL_1 fSJTL_mkfrm = NULL;
static FSJTL_4 fSJTL_close = NULL;

void My_SJTL_Init()
{
	if( !hSJTL )
       hSJTL = LoadLibrary("SJTL.DLL");

	if( hSJTL )
	{
		fSJTL_save = (void*)GetProcAddress(hSJTL,"SJTL_save");
		fSJTL_save_old = (void*)GetProcAddress(hSJTL,"SJTL_save_old");
		fSJTL_open = (void*)GetProcAddress(hSJTL,"SJTL_open");
		fSJTL_mkfrm = (void*)GetProcAddress(hSJTL,"SJTL_mkfrm");
		fSJTL_close = (void*)GetProcAddress(hSJTL,"SJTL_close");
	}
}

int My_SJTL_save(char* filename)
{
	if(fSJTL_save!=NULL)
		return fSJTL_save(filename);
	else
		return 0;
}

int My_SJTL_save_old(char *filename, CSTR_line lino,int nfield)
{
	if(fSJTL_save_old!=NULL)
		return fSJTL_save_old(filename,lino,nfield);
	else
		return 0;
}

int My_SJTL_open(char *frmname, char *jtlname)
{
	if(fSJTL_open!=NULL)
		return fSJTL_open(frmname,jtlname);
	else
		return 0;
}

int My_SJTL_mkfrm(char *frmname)
{
	if(fSJTL_mkfrm!=NULL)
		return fSJTL_mkfrm(frmname);
	else
		return 0;
}

void My_SJTL_close(void)
{
	if(fSJTL_close!=NULL)
		fSJTL_close();
}

void My_SJTL_Done()
{
	if(hSJTL)
		FreeLibrary(hSJTL);
}
