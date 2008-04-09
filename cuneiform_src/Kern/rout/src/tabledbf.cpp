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


// TableDBF.cpp

//********************************************************************
//********************************************************************

#include "stdafx.h"
#include "rout_own.h"
#include "dbf.h"
#include <time.h>

static BOOL TableDBF_Finish(long reason);
static BOOL MakeDbfHeader();
static Byte DbfLanguage();

static DBF_HEADER *dbf_header;	// ����� ���������
static DBF_FIELD *dbf_fields;	// ����� ��������� ����
static long rec_num;	// ����� ������� ������ DBF-�����
static Byte *rec_ptr;	// ����� ������� ������

//********************************************************************
BOOL MakeTableDBF()
{
/* 
	������ TableDBF.

	�������������� ���� �������.
	����� ����� �����������, ���� gPreserveLineBreaks = TRUE.

    ������� ����������� ���������� ������������� ������� �� ������ 
	�������� ������ ��� ������ ������� TableText_Prepare().

	��� ��������� ������ DBF ������������ ����� �������� ������.

*/

	// �������� ������� ���������
	if ( !TableText_Prepare() )
		return FALSE;

	// ��������� ����� ������
	Byte *saveMemEnd = gMemEnd;

	// ����� ���������� ��������� ������,
	// ������������� ������ �� �����
	gMemEnd = (Byte*)gBegLineText - gBumperSize;

	// ������� ��������� � ������
	gMemCur = gMemStart;

	// ��������� ������ DBF
	BOOL good = BrowseTableText(TableDBF_Finish);

	// ������������ ����� ������
	gMemEnd = saveMemEnd;

	// ������� ���������� �������������
	TableText_Delete();

	return good;
}
//********************************************************************
static BOOL TableDBF_Finish(
			long reason // ��. enum BROWSE_TABLE_TEXT_REASON
			)
{
/* 
	������������ DBF-����� �� ������ � �������� ������ �����������
	������������� ������� � ������� ������� BrowseTableText().

	�� �����:

		gCurLineText - ���������� ������ ������,
		gCellText - ���������� ������,
		gIndexTableCell - ����� ������,
		gIndexTableRow - ����� ������ �������, 
		gIndexTableCol - ����� ������� �������

*/

	switch(reason)
		{
		case BROWSE_TABLE_TEXT_TABLE_START:
			// ������ �������

			// ������� ��������� DBF-�����
			// ������� ����������� �����
			if (!MakeDbfHeader())
				return FALSE;

			// ����� ������ ������
			rec_num = 0;
			rec_ptr = gMemCur;
			break;

		case BROWSE_TABLE_TEXT_TABLE_END:
			// ����� �������

			// ���������� ��������� DBF-�����
			// ���������� ������ � DBF-�����
			dbf_header->records = rec_num;

			// ���� "����� �����" 
			*gMemCur++ = DBF_TERM_FILE;	// ����� DBF-�����
			break;

		case BROWSE_TABLE_TEXT_RECORD_START:
			// ������ ������

			// ���������� ��� ������
			PUT_SPACES(dbf_header->record_size);
			break;
			
		case BROWSE_TABLE_TEXT_RECORD_END:
			// ����� ������
			rec_ptr += dbf_header->record_size;
			rec_num++;
			gMemCur = rec_ptr;
			break;

		case BROWSE_TABLE_TEXT_STRING:
			// �������� ����

			{
			// ���������� ����
			DBF_FIELD *f = &dbf_fields[gIndexTableCol];

			// ����� ���� ��������
			gMemCur = rec_ptr + f->offset;

			// �� ����� ������ ����, ��� �������� �����
			long w = min(f->length,gCurLineText->ltext);

			// ����������� �����
			memcpy(gMemCur,gCurLineText->text,w);
			}
			break;
		}

	return TRUE;
}
//********************************************************************
static BOOL MakeDbfHeader()
{
// ������� ��������� DBF-����� ������� ����������� �����
	CHECK_MEMORY(sizeof(DBF_HEADER) +
				gTableCols * sizeof(DBF_FIELD) + 10);

	dbf_header = (DBF_HEADER*) gMemCur;
	gMemCur += sizeof(DBF_HEADER);

	// ����������� ���� � �����
	struct tm *today = 0;
	time_t aclock={0};
	time( &aclock );               // Get time in seconds
	today = localtime( &aclock );  // Convert time to struct

	// ���������� ���������
	dbf_header->tag = 3;	// ������ �����
	dbf_header->year  = today->tm_year;// ��� ����� 1900 (�� 255)
	dbf_header->month = today->tm_mon+1;
	dbf_header->day   = today->tm_mday;
	dbf_header->header_size = sizeof(DBF_HEADER) + 
							gTableCols * sizeof(DBF_FIELD)
							+ 1;
	dbf_header->record_size = 1;	// ������ � ������ ������

	// ����
	dbf_header->language = DbfLanguage();

	// ������� ����������� �����
	dbf_fields = (DBF_FIELD*) gMemCur;

	for(gIndexTableCol = 0;
		gIndexTableCol < gTableCols;
		gIndexTableCol++, 	
		gMemCur += sizeof(DBF_FIELD)
		)
		{
		// ���������� ����
		DBF_FIELD *f = &dbf_fields[gIndexTableCol];

		// ��� ���� "col_n"
		sprintf(f->name,"col_%d",gIndexTableCol+1);

		// ��� ���� ������ ���������
		f->type = 'C';

		// ������ �������
		long w = gTableColWidths[gIndexTableCol];
		if (w > 254)
			POSSIBLE_LOSS_OF_DATA;

		// ������ ����
		f->length = min(w,254);

		// �������� ���� �� ������ ������
		f->offset = dbf_header->record_size;
		dbf_header->record_size += f->length;

		}

	// ������� ����� ���������
	*gMemCur++ = DBF_TERM_BYTE;
	return TRUE;
}
//********************************************************************
static Byte DbfLanguage()
{
// ��� ����� � ��������� DBF-�����

	long cp = GetCodePage();
	switch(cp)
		{
		case 437:	return 0x01;	// DOS USA
		case 850:	return 0x02;	// DOS Multilingual
		case 1251:	return 0x03;	// Windows ANSI
		case 1250:	return 0xC8;	// Windows EE
		case 852:	return 0x64;	// DOS USA
		case 866:	return 0x66;	// Russian DOS
		case 865:	return 0x65;	// Nordic DOS
		}

	return 0;
}
//********************************************************************
