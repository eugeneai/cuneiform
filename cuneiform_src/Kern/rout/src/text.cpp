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


// Text.cpp

//********************************************************************
//********************************************************************

#include <string.h>
#include "stdafx.h"
#include "rout_own.h"
#include "ligas.h"	// ������ � HHH 01.09.2000 E.P.

static BOOL Static_MakeText(Handle hObject, long reason);
static BOOL TableStub();
static BOOL IncludeTable();

//********************************************************************
BOOL MakeText()
{
/* ��������� �������.

   ������� �������� � ����:
	 "<< ������� 1: ����� 1, �������� 2, ����� 2 >>"

   ����� ����� �����������, ���� gPreserveLineBreaks = TRUE.
*/

	return BrowsePage(Static_MakeText,
				TRUE,		// wantSkipTableCells
				FALSE);		// wantSkipParagraphs

}
//********************************************************************
BOOL Static_MakeText(
			Handle hObject,
			long reason	// ��. enum BROWSE_REASON
			)
{
// � ����� ���������� WordControl

	switch(reason)
		{
		case BROWSE_CHAR:
			// ������
			// ���������� ����
			{
			long lang = CED_GetCharFontLang(hObject);
			if (lang != gLanguage)
				SetLanguage(lang);
			}

			// �������� ������
			ONE_CHAR(hObject);
			break;

		case BROWSE_LINE_END:
			// ����� ������
			if ( 0 ||
				gFormat==ROUT_FMT_SmartText ||
				( gPreserveLineBreaks || gEdLineHardBreak)
				)
				NEW_LINE;
			break;

		case BROWSE_PARAGRAPH_END:
			// ����� ������
			NEW_LINE;
			break;

		case BROWSE_TABLE_START:
			// ������ �������

			// �������� ������� � ����� ��������
			if (gTableTextOptions & ROUT_TABLE_TEXT_INCLUDED)
				{if (!IncludeTable()) return FALSE;}
			else
				// ���������� ����� ������� � ������ ��������
				{if (!TableStub()) return FALSE;}

			break;

		case BROWSE_TABLE_END:
			// ����� �������
			NEW_LINE;
			break;

		}

	// �������� �� ������� � ��������
	WORDS_CONTROL(reason);

	return TRUE;	// ���������� ��������
}
//********************************************************************
BOOL NewLine()
{
// �������� ����� ������

	CHECK_MEMORY(10);

	// ��� ������ Words.cpp
	gCharBack = gMemCur;

	Byte *p = (Byte*)gEOL;
	while(*p)
		*gMemCur++ = *p++;

	return TRUE;
}
//********************************************************************
BOOL OneChar(Handle charHandle)
{
// �������� � ����� ���� ������

	CHECK_MEMORY(10);

	struct letterEx *alt = CED_GetAlternatives(charHandle);
	ASSERT(alt);

	// �������� ������
	Byte c1 = alt->alternative;

	// ���������������� ������
	Byte c2 = gActiveCodeTable[c1];

	// ��������� ��� ������ Words.cpp
	gCharHandle = charHandle;
	gAlt = alt;
	gCharCode = c1;
	gCharBack = gMemCur;

	// �������, ����������� ��� ������������ SmartText,
	// ����� ������ 253; �� ������� ����������
	// ��� ���� ��������� ��������
	if (c1 == ' ' && alt->probability == 253 &&
		gFormat != ROUT_FMT_SmartText
	    )
		return TRUE;

	// ����������� ������ �������������
	switch(c1)
		{
		// ����������� �������� - ���������,
		// �� �������� ��� ����. 26.05.99
#ifdef __MAC__
		case (BYTE)206: case (BYTE)207:
		case (BYTE)174: case (BYTE)190:
			if( gLanguage==LANG_FRENCH )
				c2=�1;
			break;
#endif
		// �������������� ������
		case bad_char:
			c2 = gBadChar;
			break;

/*
	21.01.2000 ������������� ������� - �������������
		������������� � ��� ������. �.�.


		case '_':
			// ������������� ��������� � �����
			// � ����������� ����� SmartText � HTML
			c2 = '-';
			if (gFormat != ROUT_FMT_SmartText &&
				gFormat != ROUT_FMT_HTML
				)
				*gMemCur++ = '-';
			break;
*/

		case 0x97:
			// ������� ���� ��������� � �����
			// � ����������� ����� SmartText � HTML
			// 29.02.2000
			if (gFormat == ROUT_FMT_HTML)
				{
				// � HTML ���� ������� ����
				c2 = c1;
				}
			else
				{
				c2 = '-';
				if (gFormat != ROUT_FMT_SmartText)
					*gMemCur++ = '-';
				}
			break;

		// ������� ������ � HTML ���������� �� �������
		case '<':
		case '>':
			if (gFormat == ROUT_FMT_HTML) {
				*gMemCur++ = '&';
				*gMemCur++ = (c1 == '<' ? 'l' : 'g');
				*gMemCur++ = 't';
				*gMemCur++ = ';';
				return TRUE;
			}
			break;

		case '&':
                        if(gFormat == ROUT_FMT_HTML) {
                            *gMemCur++ = '&';
                            *gMemCur++ = 'a';
                            *gMemCur++ = 'm';
                            *gMemCur++ = 'p';
                            *gMemCur++ = ';';
                            return TRUE;
                        }
                        break;

		// ������� oe / OE
		case oe_deaf_sound:
			if( FALSE == (
					gLanguage==LANG_RUSSIAN ||
					langKaz ||   // 18.08.98 E.P.
					gLanguage==LANG_FRENCH &&
					gActiveCode==ROUT_CODE_ANSI
					) ||
					gFormat == ROUT_FMT_HTML
				)
				{
				*gMemCur++ = 'o';
				c2='e';
				}
			break;

		case OE_cap_deaf_sound:
			if( FALSE == (
					gLanguage==LANG_RUSSIAN ||
					langKaz ||   // 18.08.98 E.P.
					gLanguage==LANG_FRENCH &&
					gActiveCode==ROUT_CODE_ANSI
					) ||
					gFormat == ROUT_FMT_HTML
				)
				{
				*gMemCur++ = 'O';
				c2='E';
				}
			break;

#ifndef __MAC__
		//	0xA9 � -> (C),
		//	0xAE � -> (R)
		case  0xA9:  case  0xAE:
			if( gActiveCode==ROUT_CODE_ASCII ||
				gActiveCode==ROUT_CODE_ISO
			  )
				*gMemCur++ = '(';

			*gMemCur++ = c2;

			if( gActiveCode==ROUT_CODE_ASCII ||
				gActiveCode==ROUT_CODE_ISO
			  )
				*gMemCur++ = ')';

			return TRUE;
			break;

#endif
		// 0x99 � -> (TM) ����� ANSI
		case  0x99:
			if( gActiveCode!=ROUT_CODE_ANSI)
				{
				*gMemCur++ = '(';
				*gMemCur++ = c2;	// 'T'
				*gMemCur++ = 'M';
				*gMemCur++ = ')';
				return TRUE;
				}

			break;

		}	// switch(c1)

	*gMemCur++ = c2;
	return TRUE;
}
//********************************************************************
BOOL PutString(char *s)
{
// ������ ������ � �����.
// ���������� �������� ������ �����, ��� �����
// ������������� ������������ NEW_LINE

	ULONG lth = strlen(s);

	if ( !lth )
		return TRUE;

	CHECK_MEMORY(lth+10);	// � �������

	strcpy((char*)gMemCur,s);
	gMemCur += lth;
	return TRUE;
}
//********************************************************************
BOOL PutSpaces(long lth)
{
// ������ �������� � �����.

	if ( lth <= 0 )
		return TRUE;

	CHECK_MEMORY(lth+10);	// � �������

	memset (gMemCur,' ', lth);
	gMemCur += lth;
	return TRUE;
}
//********************************************************************
static BOOL TableStub()
{
// ����������� ������� � ������ ��������

// ����� "�������", "�����:", "��������:", "�����:"
char word1[40]="", word2[40]="", word3[40]="", word4[40]="";

	LoadString((HINSTANCE)ghInst_rout,
		IDS_MODULE_TEXT_Table,word1,sizeof(word1));
	LoadString((HINSTANCE)ghInst_rout,
		IDS_MODULE_TEXT_Rows,word2,sizeof(word2));
	LoadString((HINSTANCE)ghInst_rout,
		IDS_MODULE_TEXT_Cols,word3,sizeof(word3));
	LoadString((HINSTANCE)ghInst_rout,
		IDS_MODULE_TEXT_Cells,word4,sizeof(word4));

	char buf[1000] = "";
	sprintf(buf,
			"<< %s %d: %s %d, %s %d, %s %d >>",
			word1, gHitTables,
			word2, gTableRows,
			word3, gTableCols,
			word4, gTableCells);

	PUT_STRING(buf);
	NEW_LINE;
	return TRUE;
}
//********************************************************************
static BOOL IncludeTable()
{
/*
	�������� ������� � ����� ��������

*/

	// ��������� ������ ������
	Byte *saveMemStart = gMemStart;

	// ������ ���������� ��������� ������
	gMemStart = gMemCur;

	// �������� ��������� ������
	memset(gMemStart,0,gMemEnd - gMemStart);

	// ������� ��������� �����
	BOOL good = MakeTableText();

	// ������������ ������ ������
	gMemStart = saveMemStart;

	return good;
}
//********************************************************************
