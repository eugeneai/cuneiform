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

// CTIMaskLine.cpp: implementation of the CTIMaskLine class.
//
//////////////////////////////////////////////////////////////////////

#include "ctimaskline.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTIMaskLine::CTIMaskLine()
            : mwLenght(0),
			  mwSegments(0),
			  mpNext(NULL),
			  mwLine(-1){}

CTIMaskLine::CTIMaskLine(Word32 Lenght)
            : mwLenght(Lenght),
			  mwSegments(0),
			  mpNext(NULL),
			  mwLine(-1){}

CTIMaskLine::CTIMaskLine(Word32 Lenght, PCTIMaskLineSegment pSegm)
            : mwLenght(Lenght),
			  //mcFirst(pSegm),
			  mwSegments(0),
			  mpNext(NULL),
			  mwLine(-1)
{
	AddSegment( pSegm );
}

CTIMaskLine::CTIMaskLine(Word32 Lenght, Word32 nLine, PCTIMaskLineSegment pSegm)
            : mwLenght(Lenght),
			  //mcFirst(pSegm),
			  mwSegments(0),
			  mpNext(NULL),
			  mwLine(nLine)
{
	AddSegment ( pSegm );
}

CTIMaskLine::CTIMaskLine(Word32 Lenght, Word32 nLine, PCTIMaskLineSegment pSegm, PCTIMaskLine pcNextLine)
            : mwLenght(Lenght),
			  //mcFirst(pSegm),
			  mwSegments(0),
			  mpNext(pcNextLine),
			  mwLine(nLine)
{
	AddSegment ( pSegm );
}

CTIMaskLine::~CTIMaskLine()
{
	PCTIMaskLineSegment pS = mcFirst.GetNext();
	PCTIMaskLineSegment pD;

	while (pS )
	{
		pD = pS;
		pS = pS->GetNext();
		delete pD;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////
Bool32 CTIMaskLine::AddSegment(PCTIMaskLineSegment pSegm)
{
	PCTIMaskLineSegment pS = &mcFirst;
	PCTIMaskLineSegment pL;
	Bool32 bRet = FALSE;
	Bool32 Added = FALSE;
	Bool32 Check = FALSE;

	if ( IsSegmentOnLine(pSegm) )
	{
		pL = pS;

		while (pS && !Added )
		{
			switch( pS->IsIntersectWith(pSegm) )
			{
			case CTIMLSEGMINTERSECTFULLLEFT:
				pS = NULL;
				break;
			case CTIMLSEGMINTERSECTFULLRIGHT:
				pL = pS;
				pS = pS->GetNext();
				break;
			case CTIMLSEGMINTERSECTIN:
			case CTIMLSEGMINTERSECTEQUAL:
				bRet = Added = TRUE;
				break;
			case CTIMLSEGMINTERSECTOVER:
				Check = TRUE;
			case CTIMLSEGMINTERSECTLEFT:
			case CTIMLSEGMINTERSECTRIGHT:
				bRet = pS->AddWith(pSegm);
				Added = TRUE;
				break;
			default:
				FALSE;
			}
		}

		if ( !Added )
		{
			pS = pL->GetNext();
			pL->SetNext( new CTIMaskLineSegment(pSegm->GetStart(), pSegm->GetEnd()));
			(pL->GetNext())->SetNext(pS);
			mwSegments++;
			bRet = TRUE;
		}

		if (Check)
			CheckSegments();
	}
	else
		SetReturnCode_cimage(IDS_CIMAGE_INVALID_MASK_LAGER_IMAGE);

	return bRet;
}

Bool32 CTIMaskLine::RemoveSegment(PCTIMaskLineSegment pSegm)
{
	PCTIMaskLineSegment pPS = &mcFirst;
	PCTIMaskLineSegment pS = pPS->GetNext();
	Bool32 Remed = FALSE;

	if ( mwSegments )
	{
		if ( IsSegmentOnLine(pSegm) )
		{
			while ( pS && !Remed )
			{
				switch ( pS->IsIntersectWith(pSegm) )
				{
				// pSegm ����� pS
				case CTIMLSEGMINTERSECTEQUAL:
					pPS->SetNext(pS->GetNext());
					delete pS;
					Remed = TRUE;
					mwSegments--;
					pS = pPS->GetNext();
					break;
				// pSegm ���������� pS
				case CTIMLSEGMINTERSECTOVER:
					pPS->SetNext(pS->GetNext());
					delete pS;
					mwSegments--;
					pS = pPS->GetNext();
					break;
				// pSegm ���������� ������ ����� pS
				case CTIMLSEGMINTERSECTRIGHT:
					pS->CutLeftTo(pSegm);
					pPS = pPS->GetNext();
					pS = pPS->GetNext();
					break;
				// pSegm ���������� ����� ����� pS
				case CTIMLSEGMINTERSECTLEFT:
					pS->CutRightTo(pSegm);
					pPS = pPS->GetNext();
					pS = pPS->GetNext();
					break;
				// pSegm ����� ������ pS
				case CTIMLSEGMINTERSECTIN:
					pS->SetNext(new CTIMaskLineSegment(pS));
					pS->CutLeftTo(pSegm);
					pS = (pPS = pS)->GetNext();
					pS->CutRightTo(pSegm);
					mwSegments++;
					pPS = pPS->GetNext();
					pS = pPS->GetNext();
					break;
				case CTIMLSEGMINTERSECTFULLLEFT:
					pS = NULL;
					break;
				case CTIMLSEGMINTERSECTFULLRIGHT:
					pPS = pS;
					pS = pS->GetNext();
					break;
				}
			}
		}
		else
			SetReturnCode_cimage(IDS_CIMAGE_INVALID_MASK_LAGER_IMAGE);
	}
	else
		SetReturnCode_cimage(IDS_CIMAGE_NO_MASK_ON_THIS_LINE);

	return TRUE;
}

Bool32 CTIMaskLine::GetLeftIntersection(PCTIMaskLineSegment pcSegm)
{
	PCTIMaskLineSegment pL = mcFirst.GetNext();
	Word32  wItype;
	Bool32  bInt = FALSE;

	while ( pL )
	{
		//wItype = pL->IsIntersectWith( pcSegm );
		wItype = pcSegm->IsIntersectWith( pL );

		if ( !(wItype == CTIMLSEGMINTERSECTFULLRIGHT ||
			   wItype == CTIMLSEGMINTERSECTFULLLEFT    ) )
		{
			pcSegm->IntersectWith(pL);
			bInt = TRUE;
			break;
		}

		pL = pL->GetNext();
	}

	return bInt;
}

Bool32 CTIMaskLine::CheckSegments()
{
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////
// end of file
