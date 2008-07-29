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

// CRInvertor.cpp: implementation of the CRInvertor class.
//
//////////////////////////////////////////////////////////////////////

#include "crinvertor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRInvertor::CRInvertor()
{

}

CRInvertor::~CRInvertor()
{

}

Bool32 CRInvertor::Invert(PCTDIB Image)
{
	Word32   LineLen;
	Word32   Lines;
	Word32   x;
	Word32   y;
	PWord32  pData;

	if ( !Image )
	{
		return FALSE;
	}

	LineLen = Image->GetLineWidthInBytes();

	Lines   = Image->GetLinesNumber();

	for (y = 0; y < Lines; y++ )
	{
		pData = (PWord32)Image->GetPtrToLine(y);

		for ( x = 0; x < LineLen; x += 4 )
		{
			*pData++ =  ~(*pData);
		}
	}

	return ((LineLen != 0) && (Lines != 0));
}

Bool32 CRInvertor::Inverse(PCTDIB Image)
{
	Word32   Colors;
	Word32   Color;
	CTDIBRGBQUAD  ctQuad;

	if ( !Image )
	{
		return FALSE;
	}

	Colors = Image->GetActualColorNumber();

	if ( Colors == 0 )
		return Invert( Image );

	for ( Color = 0; Color < Colors; Color++ )
	{
		if ( !Image->GetRGBQuad(Color, &ctQuad) )
			continue;

		ctQuad.rgbBlue  = ~(ctQuad.rgbBlue);
		ctQuad.rgbGreen = ~(ctQuad.rgbGreen);
		ctQuad.rgbRed   = ~(ctQuad.rgbRed);

		Image->SetRGBQuad(Color, ctQuad);
	}

	return (Colors != 0);
}
