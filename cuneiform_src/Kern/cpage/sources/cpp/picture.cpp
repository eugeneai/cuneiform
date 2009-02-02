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

#include "globus.h"
#include "cpage.h"
#include "backup.h"
#include "polyblock.h"
#include "resource.h"

// ���������� �������������� �� TYPE_PICTURE � CPAGE_PICTURE
Word32 TYPE_PICTURE_to_CPAGE_PICTURE(POLY_ * lpDataIn,Word32 SizeIn,CPAGE_PICTURE* LpDataOut,Word32 SizeOut)
{
	Word32 rc = 0;
	if(LpDataOut == NULL)
		return sizeof(CPAGE_PICTURE);

	if(sizeof(POLY_) != SizeIn ||
		sizeof(CPAGE_PICTURE) != SizeOut ||
		lpDataIn == NULL)
	{
		SetReturnCode_cpage(IDS_ERR_DISCREP);
		return 0;
	}

	POLY_  desc = *lpDataIn;
	CPAGE_PICTURE pict = {0};

	pict.Number = desc.com.count;
	for(Word32 i=0;i<pict.Number;i++)
	{
		pict.Corner[i] = desc.com.Vertex[i];
	}

	*LpDataOut = pict;

	rc = sizeof(CPAGE_PICTURE);
	return rc;
}
//##########################################################
Word32 CPAGE_PICTURE_to_TYPE_PICTURE( CPAGE_PICTURE * lpDataIn,Word32 SizeIn,POLY_ * LpDataOut,Word32 SizeOut)
{
	Word32 rc = 0;

	if(LpDataOut == NULL)
			return sizeof(POLY_);

	if(sizeof(POLY_) != SizeOut ||
		sizeof(CPAGE_PICTURE) != SizeIn ||
		lpDataIn == NULL)
	{
		SetReturnCode_cpage(IDS_ERR_DISCREP);
		return 0;
	}

	POLY_  desc = {0} ;
	CPAGE_PICTURE pict = *lpDataIn;

	desc.com.count = pict.Number;
	for(Word32 i=0;i<pict.Number;i++)
	{
		desc.com.Vertex[i] = pict.Corner[i];
	}
	desc.com.type		= TYPE_PICTURE;
	desc.com.number	= 0;

	*LpDataOut = desc;
	rc = sizeof(POLY_);
	return rc;
}

