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

#define __CPAGE__

#include "globus.h"
#include "cpage.h"
#include "backup.h"
#include "polyblock.h"
#include "resource.h"

static Handle varTYPE_CPAGE_TABLE = 0;
static Handle varTYPE_CPAGE_PICTURE = 0;

void DefConvertInit()
{
	varTYPE_CPAGE_TABLE = TYPE_CPAGE_TABLE;
	varTYPE_CPAGE_PICTURE = TYPE_CPAGE_PICTURE;
}
#undef TYPE_CPAGE_TABLE
#undef TYPE_CPAGE_PICTURE

Word32 DefConvertBlock(Word32 dwContext,
				  Handle TypeIn,void * lpDataIn,Word32 SizeIn,
				  Handle TypeOut,void * LpDataOut, Word32 SizeOut)
{
	Word32 rc = 0;
	SetReturnCode_cpage(IDS_ERR_NO);

	if(TypeIn==TYPE_DESK)
	{
		if(TypeOut==varTYPE_CPAGE_TABLE)
			rc = TYPE_DESK_to_CPAGE_TABLE((TABLE_DESC *)lpDataIn,SizeIn,(CPAGE_TABLE *)LpDataOut,SizeOut);
	}
	else if(TypeIn==varTYPE_CPAGE_TABLE)
	{
		if(TypeOut==TYPE_DESK)
			rc = CPAGE_TABLE_to_TYPE_DESK((CPAGE_TABLE *)lpDataIn,SizeIn,(TABLE_DESC *)LpDataOut,SizeOut);
	}
	else if(TypeIn==TYPE_IMAGE)
	{
		if(TypeOut==varTYPE_CPAGE_PICTURE)
			rc = TYPE_PICTURE_to_CPAGE_PICTURE((POLY_ *)lpDataIn,SizeIn,(CPAGE_PICTURE *)LpDataOut,SizeOut);
	}
	else if(TypeIn==varTYPE_CPAGE_PICTURE)
	{
		if(TypeOut==TYPE_IMAGE)
			rc = CPAGE_PICTURE_to_TYPE_PICTURE((CPAGE_PICTURE *)lpDataIn,SizeIn,(POLY_ *)LpDataOut,SizeOut);
	}
	return rc;
}

Word32 DefConvertPage(Word32 dwContext,
				  Handle TypeIn,void * lpDataIn,Word32 SizeIn,
				  Handle TypeOut,void * LpDataOut, Word32 SizeOut)
{
	Word32 rc = 0;
	SetReturnCode_cpage(IDS_ERR_NO);

	return rc;
}
