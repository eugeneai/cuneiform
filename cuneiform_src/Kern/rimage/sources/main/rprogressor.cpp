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

// RProgressor.cpp: implementation of the CRProgressor class.
//
//////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "rprogressor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRProgressor::CRProgressor()
{
	mfStart  = NULL;
	mfStep   = NULL;
	mfFinish = NULL;
	mbProgressStarted = FALSE;
	mwLastPercent = 0;
}

CRProgressor::CRProgressor( void (*pStart)(void), void (*pFinish)(void), Bool32 (*pStep)(Word32))
{
	mfStart  = pStart;
	mfStep   = pStep;
	mfFinish = pFinish;
	mbProgressStarted = FALSE;
	mwLastPercent = 0;
}

CRProgressor::~CRProgressor()
{
	Finish();
}

Bool32 CRProgressor::Start()
{
	if ( !mbProgressStarted && mfStart )
	{
		mfStart();
		return TRUE;
	}

	return FALSE;
}

Bool32 CRProgressor::Finish()
{
	if ( mbProgressStarted && mfFinish )
	{
		mfFinish();
		mbProgressStarted = FALSE;
		mwLastPercent = 0;
		return TRUE;
	}

	return FALSE;
}

Bool32 CRProgressor::SetStep(Word32 wPercent)
{
	if ( mbProgressStarted && mfStep )
	{
		if ( wPercent > mwLastPercent )
		{
			mwLastPercent = wPercent;

			if ( mfStep(wPercent) )
			{
				Finish();
				return TRUE;
			}
		}
	}

	return FALSE;

}

Bool32 CRProgressor::SetExternals(CRPStart pStart, CRPFinish pFinish, CRPStep pStep)
{
	Bool32 ret = FALSE;

	if ( pStart )
	{
		mfStart = pStart;
		ret = TRUE;
	}
	if ( pFinish )
	{
		mfFinish = pFinish;
		ret = TRUE;
	}

	if ( pStep )
	{
		mfStep = pStep;
		ret = TRUE;
	}

	return ret;
}


