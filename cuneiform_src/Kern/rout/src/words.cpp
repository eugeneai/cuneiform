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


// Words.cpp

//********************************************************************
//********************************************************************

#include <string.h>
#include "stdafx.h"
#include "rout_own.h"

//********************************************************************
BOOL IsLetter(Byte c)
{
	Byte type = gAlphabetTable[c];

	return (type & CASE_UPPER) ||
		   (type & CASE_LOWER);
}
//********************************************************************
BOOL IsEOL(Byte c)
{
	return c == 0x0d ||
		   c == 0x0a;
}
//********************************************************************
BOOL WordsControl(
		long reason	// ��. enum BROWSE_REASON
		)
{
// �������� �� ������� � ��������
// ���������� ����� ������ ������� ��� ����� ������
// ��� ����� ���� ���������

	switch(reason)
		{
		case BROWSE_PARAGRAPH_START:
			// ������ ������
			gLastEOL = NULL;
			gBegWord = NULL;
			gDefis = NULL;
			gCharBack = NULL;
			break;

		case BROWSE_PARAGRAPH_END:
			// ����� ������
			// ���������� ����� ����� ���� ����
			if ( gBegWord && !WordEnd() )
				return FALSE;

			gLastEOL = NULL;
			gBegWord = NULL;
			gDefis = NULL;
			gCharBack = NULL;
			break;

		case BROWSE_LINE_END:
			// ����� ������
			// ������������ ����� �� ������ ����� ������
			// ��� ������� � ������ ��������� ������
			if ( gCharBack && IsEOL(*gCharBack) )
				gLastEOL = gCharBack;
			else
				gLastEOL = gMemCur;
			break;

		case BROWSE_LINE_START:
			// ������ ������
			{
			Byte c = *(gMemCur-1);	// ���������� ������
			if (gLastEOL &&			// ���������� ������
				c &&				// �� ��������� �����
				!IsEOL(c) &&		// ��� ����� ������ ������
				!(gFormat==ROUT_FMT_HTML && // ��� ����� ������ HTML
				  !memcmp("<br>",(char*)gMemCur-4,4)
				 ) &&
				c != ' '			// �� ����� �� ������
				)
				{
				// �������� ������ ����� ����� �������
				*gMemCur++ = ' ';
				}
			}
			break;

		case BROWSE_CHAR:
			// ������

			// �����
			if (IS_LETTER(gCharCode))
				{
				// ������ �����
				if(!gBegWord)
					gBegWord = gCharBack;
				}
			// �� �����. � ����� ����.
			else if (gBegWord)
				{
				// �����
				if (gCharCode == '-')
					{
					Byte c = *(gMemCur-2);	// ���������� ������
					if ( c == '-' )
						{
						// ��� ������ ������ ��� ����
						if ( gDefis == gMemCur-2 )
							gDefis = 0;
						}
					else
						{
						// ������� ����� � "������" ������ ����� ���� ������
						if ( gEdCharHidden &&
							!(gPreserveLineBreaks || gEdLineHardBreak)
						   )
 							gDefis = gCharBack;
						}
					}

				// ����� �����
				else
					{
					// ���������� ����� �����
					if ( !WordEnd() )
						return FALSE;
					}
				}

			break;

		}

	return TRUE;
}
//********************************************************************
BOOL WordEnd()
{
// ���������� ����� �����
// �������: gBegWord > 0,
//			gDefis >= 0,
//			gLastEOL >= 0

	BOOL hasWordBreak = (gBegWord < gDefis &&
					     gDefis + 1 == gLastEOL &&
						*gLastEOL == ' '
						 );

	// ��������� ��������
	if (hasWordBreak)
		{
		// ������� ����� � ������ ����� ��������
		long lth = 2;
		memcpy(gDefis, gDefis + lth,
			   gMemCur - gDefis - lth);
		gMemCur -= lth;
		*gMemCur = 0;
		}

	gBegWord = NULL;
	gDefis = NULL;
	return TRUE;
}
//********************************************************************
