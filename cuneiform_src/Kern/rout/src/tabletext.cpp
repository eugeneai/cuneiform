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


// TableText.cpp

//********************************************************************
//********************************************************************

#include <string.h>
#include "stdafx.h"
#include "rout_own.h"

static BOOL Static_TableText_Prepare(Handle hObject, long reason);
static BOOL LineEnd();
static BOOL TableText_Columns();
static BOOL TableText_CellWidths();
static long BottomRow();
static long RightmostCol();
static BOOL SearchTable(long fromCol);
static BOOL CellRight();
static BOOL FirstCell();
static BOOL NextLevel();
static BOOL TableText_Finish(long reason);
static BOOL EmptyColumns(long fromCol,long toCol);
static BOOL AfterColumn(long col);

//********************************************************************
BOOL MakeTableText()
{
/* 
	������ TableText.

	�������������� ���� �������.
	����� ����� �����������, ���� gPreserveLineBreaks = TRUE.

    ������� ����������� ���������� ������������� ������� �� ������ 
	�������� ������ ��� ������ ������� TableText_Prepare().

	����� ������������� �������������� ���������� ������� ������
	��� ������ ������� TableText_Columns().

	��� ��������� ������ ���������� ������ ������������ 
	����� �������� ������.

*/

	// �������� ������� ���������
	if ( !TableText_Prepare() )
		return FALSE;

	// ���������� ���������� ������� �������
	// � ������ ���������� � ������������
	if ( !TableText_Columns() )
		return FALSE;

	// ���������� ������ ����� � ������ ���������� �������
	if ( !TableText_CellWidths() )
		return FALSE;

	// ��������� ����� ������
	Byte *saveMemEnd = gMemEnd;

	// ����� ���������� ��������� ������,
	// ������������� ������ �� �����
	gMemEnd = (Byte*)gBegLineText - gBumperSize;

	// ������� ��������� � ������
	gMemCur = gMemStart;

	// ��������� ������ ���������� ������
	BOOL good = BrowseTableText(TableText_Finish);

	// ������������ ����� ������
	gMemEnd = saveMemEnd;

	// ������� ���������� ������������� 
	TableText_Delete();

	return good;
}
//********************************************************************
BOOL TableText_Prepare()
{
/* 
	�������� ������� ���������.
	����������� ��� ���� ��������� ��������.

	�������������� ���� �������.
	����� ����� �����������, ���� gPreserveLineBreaks = TRUE.

	������� ����������� �� ������ �������� ������.
	������ ����������� ������ ������������ ����� ������
	gBegLineText, �� � ������ ������ ��������� ������
	��� ����������� ��������.

	� �������� ������������ ���������� ������������� �������
	�������������� ��������� �������������� ����� � �������
	�������.

	��� ����� ������� �����������:
		gTableRowTops - ������ ������� ��������� ����� �������
		gTableRowBottoms - ������ ������ ��������� ����� �������

	��� ������� ���������� ����������� ��������� ����� �� ����� 
	�������.

		��������� 1: ��������������, ��� "������" ����� � �������
		� ������� ���, �� ����:

			1) ������ ������ ������� �������� ������� ������� 
			   ��� ��������� ���������� ������ � ������ ������� ���
			   ��������� (���� ����� ��������) ���������� ������.

			2) ������ ������� ������� �������� ����� �������� 
			   ��� ��������� ���������� ������ � ������ �������� ���
			   ��������� (���� ����� ��������) ���������� ������.

		��������� 2: � �������� ������ ������� ������ ���������� 
		������ ����� ������������ ������, ��� ������� ����������.
		��� ����������� ���, ���:

			1)����� ����������� � ������� ������������
			  ���������� ����� ������� �

			2)���� ������ ����� ������������ ������ ���� 
			  �� ��������� ����� �������.

		��������� 3: �������
			gTableColLefts - ������ ����� ��������� ������� ������� 
		  � gTableColRights - ������ ������ ��������� ������� �������

		 - ������ ������������, �� �� �����������. 
		 ��� ������� ���, ���:

			1) ��� ������� ������� ������� ������ ������� ������ 
			   ���������� (�� �� ������� �������, � �� ��������);

			2) ���������� ������� ����� ������ ��� ������� TableText;

			3) ��� ������� ��������� ������� ������� �����������
			   ������� TableText_Columns().

	��� ������� ������� �����������:
		gTableColWidths - ������ "����� �������" �������.

	������ ������� ������� ����������� ��� �������� ������ �����, 
	������������ � ������ ������� �������.

*/

#define USE_MEMORY(a)\
			{lth = (a);\
			CHECK_MEMORY(lth);\
			memset(gMemCur,0,lth);\
			gMemCur+=lth;}

	long lth = 0, row = 0, col = 0, cell = 0;

	// �������� ��������� ������, ����������� �� 8
	gMemCur = (Byte*)((((ULONG)gMemStart + (ULONG)gMemEnd) >>4) <<3);

	// ������ ������������ ����� ������
	gBegLineText = (LINE_TEXT*)gMemCur;
	USE_MEMORY(gMaxTextLinesInOneTable*sizeof(gBegLineText[0]));
	gEndLineText = (LINE_TEXT*)gMemCur;
	gCurLineText = gBegLineText;

	// ������ ������� ��������� ����� �������
	gTableRowTops = (long*)gMemCur;
	USE_MEMORY(gTableRows * sizeof(gTableRowTops[0]));

	// ������ ������ ��������� ����� �������
	gTableRowBottoms = (long*)gMemCur;
	USE_MEMORY(gTableRows * sizeof(gTableRowBottoms[0]));

	// ������ "�����" ������� �������
	gTableColWidths = (long*)gMemCur;
	USE_MEMORY(gTableCols * sizeof(gTableColWidths[0]));

	// ������ ����� ��������� ������� �������
	gTableColLefts = (long*)gMemCur;
	USE_MEMORY(gTableCols * sizeof(gTableColLefts[0]));

	// ������ ������ ��������� ������� �������
	gTableColRights = (long*)gMemCur;
	USE_MEMORY(gTableCols * sizeof(gTableColRights[0]));

	// ������ ������������ �����
	gTableText = (CELL_TEXT*)gMemCur;
	USE_MEMORY(gTableCells * sizeof(gTableText[0]));

	// ������� ������� �� ���� �������
	gCellHandle = NULL;
	gParagraphHandle = NULL;
	gLineHandle = NULL;

	// �������� ��������� ��������
	gHitCells = 0;
	gHitParagraphs = 0;
	gHitLines = 0;

	gHitChars = 0;
	gHitPictures = 0;

	// ���������� ������
	gCellText = NULL;

	// ������ �������
	gTableTextHeight = 0;

	// ������ �������
	gTableTextWidth = 0;

	// �������� ����� �������
	if ( !BrowseTable(Static_TableText_Prepare) )
		return FALSE;

	return TRUE;

}
//********************************************************************
BOOL TableText_Delete()
{
// ������� ���������� �������������

// ������� ��������� �������, ��������� 
// � ������� TableText_Prepare().
	gBegLineText = NULL;
	gEndLineText = NULL;
	gCurLineText = NULL;

	gTableRowTops = NULL;
	gTableRowBottoms = NULL;
	gTableColWidths = NULL;
	gTableColLefts = NULL;
	gTableColRights = NULL;
	gTableText = NULL;
	
	gCellText = NULL;

	return TRUE;
}
//********************************************************************
BOOL Static_TableText_Prepare(
			Handle hObject, 
			long reason	// ��. enum BROWSE_REASON
			)
{
// � ����� ���������� WordControl

	long *pl = 0, lth = 0;

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

		case BROWSE_PARAGRAPH_START:
			// ������ ������

			if (!gPreserveLineBreaks
				&& gCellText->lines	// 21.03.2000
			   )
				{
				// ������� ����� ������ � ���������� ������
				gCurLineText->text = gMemCur;

				// ���������� ����� � ������
				gCellText->lines++;
				}
					
			break;

		case BROWSE_LINE_START:
			// ������ ������ ������

			if ( (gPreserveLineBreaks || gEdLineHardBreak ||
				 !gCellText->lines			// 21.03.2000
				 ) 
				 && !gCurLineText->text		// 21.03.2000
			   )
				{
				// ������� ����� ������ � ���������� ������
				gCurLineText->text = gMemCur;

				// ���������� ����� � ������
				gCellText->lines++;
				}

			break;

		case BROWSE_PARAGRAPH_END:
			// ����� ������
			if (gCurLineText->text)	// 21.02.2000
				LineEnd();
			break;

		case BROWSE_LINE_END:
			// ����� ������ ������
			if (gPreserveLineBreaks || gEdLineHardBreak)
				LineEnd();
			break;

		case BROWSE_CELL_START:
			// ������ ������ �������

			// ���������� ������
			gCellText = &gTableText[gIndexTableCell];

			// ������� ����� ���������� ����������� ������ 
			gCellText->line = gCurLineText;

			// ������� ������ � ������� �������
			gCellText->row = gIndexTableRow;
			gCellText->col = gIndexTableCol;
			break;

		case BROWSE_CELL_END:
			// ����� ������ �������

			// ������ ������� �������
			pl = &gTableColWidths[gIndexTableCol];
			*pl = MAX(*pl,gCellText->width);

			// ���������� ���� ������ ������� ��� ������ �������, 
			// � ������� ������������� ������� ������
			pl = &gTableRowBottoms[BottomRow()];
			*pl = MAX(*pl,
					gTableRowTops[gIndexTableRow] + 
						gCellText->lines);

			gCellText = NULL;
			break;

		case BROWSE_ROW_START:
			// ������ ������ �������

			if ( gIndexTableRow > 0 )
				{
				// ���������� ����� ������ �������
				// �� ���������� ������ �������
				gTableRowTops[gIndexTableRow] = 
					gTableRowBottoms[gIndexTableRow - 1] +
						gTableTextIntervalBetweenCellsYY;
				}
			break;

		case BROWSE_TABLE_END:
			// ����� �������

			// ������ ������� �� ��������� ������
			gTableTextHeight = gTableRowBottoms[gTableRows - 1];

			break;
		}

	// �������� �� ������� � ��������
	WORDS_CONTROL(reason);

	return TRUE;	// ���������� ��������
}
//********************************************************************
static BOOL LineEnd()
{
// ����� ������ ������

	ASSERT(gCurLineText->text);

	// ����� ������ ������
	long lth = gMemCur - gCurLineText->text;

	gCurLineText->ltext = lth;

	// ������ ������
	long *pl = &gCellText->width;
	*pl = MAX(*pl,lth);

	// �������� ���� �� ����� ������ ������
	*gMemCur++ = 0;

	// ��������� ������� � ������� ������������ �����
	gCurLineText++;

	if (gCurLineText >= gEndLineText)
		{
		NO_MEMORY;
		return FALSE;
		}

	return TRUE;
}
//********************************************************************
static BOOL TableText_Columns()
{
/* 
	���������� ���������� ������� �������:
		gTableColLefts - ������ ����� ��������� ������� ������� 
		gTableColRights - ������ ������ ��������� ������� �������

	��� ������� ������� ����������� ����� ������������ �����
	������� �� �������� � �� ������� �������.

	����������� ����� ������ ���� ������� �������������� 
	� ������� ������� TableText_Prepare().
*/

	// ���������� ������ �����
	Byte sprav[10000];
	ASSERT(gTableCells < sizeof(sprav));
	memset(&sprav,0,sizeof(sprav));

	// ���� �� �������� �������
	for (gIndexTableCol = 0; 
		gIndexTableCol < gTableCols; 
		gIndexTableCol++
		)
		{
		// ������ ������� �������
		if ( gIndexTableCol > 0 )
			{
			// �������� ����� ���������
			gTableColLefts[gIndexTableCol] = 
				gTableColRights[gIndexTableCol-1] + 
					gTableTextIntervalBetweenCellsXX;

			// ����������� ����� ���������
			if (gTableTextSeparators[1])
				gTableColLefts[gIndexTableCol]++;
			}
		else
			{
			// �������� ������ ������� �� ������ ������
			gTableColLefts[0] = gTableTextLeftIndent;

			// ����������� ����� ������ ��������
			if (gTableTextSeparators[0])
				gTableColLefts[0]++;
			}

		// ���� �� ������� �������
		for (gIndexTableRow = 0; 
			gIndexTableRow < gTableRows; 
			gIndexTableRow++
			)
			{
			// ���������� ����� ������
			gIndexTableCell = gLogicalCells[
								gIndexTableRow * gTableCols + 
								gIndexTableCol];

			// ��������� �� ����������
			if(sprav[gIndexTableCell])
				continue;	// � ���� ���������� ������ ��� ����
			
			sprav[gIndexTableCell] = 1;

			// ���������� ������
			gCellText = &gTableText[gIndexTableCell];

			// ���������� ������ ������� ������� ������� 
			// ��� ����� ������ ������� �������, 
			// � ������� ������������� ������� ������
			long *pl = &gTableColRights[RightmostCol()];
			*pl = MAX(*pl,
					gTableColLefts[gIndexTableCol] + 
						gCellText->width);

			} // ����� ������ �������
		} // ����� ������� �������

	// ������ ������� �� ��������� �������
	gTableTextWidth = gTableColRights[gTableCols - 1];

	gCellText = NULL;
	gIndexTableCell = 0;
	gIndexTableRow = 0;
	gIndexTableCol = 0;

	return TRUE;
}
//********************************************************************
static BOOL TableText_CellWidths()
{
// ���������� ������ ����� � ������ ���������� �������

	// ���� �� ������� �������
	for (gIndexTableCell = 0; 
		gIndexTableCell < gTableCells; 
		gIndexTableCell++
		)
		{
		gCellText = &gTableText[gIndexTableCell];
		gIndexTableRow = gCellText->row;
		gIndexTableCol = gCellText->col;

		// ������ ���������� �������
		long col2 = RightmostCol();

		// ������ ������ � ������ ���������� �������
		long w = gTableColRights[col2] - 
				 gTableColLefts[gIndexTableCol];


		ASSERT(gCellText->width <=w);
		gCellText->width = w;
		}


	return TRUE;
}
//********************************************************************
BOOL BrowseTableText(
			FNROUT_BrowseTableTextFunction 
				BrowseTableTextFunction
			)
{
/* 
	����� ����������� ������������� �������, 
	��������������� �������� TableText_Prepare.

	��� ������ ������ ������ ���������� �������� �������
	BrowseTableTextFunction(), ��� ����

		gCurLineText - ���������� ������ ������,
		gCellText - ���������� ������,
		gIndexTableCell - ����� ������,
		gIndexTableRow - ����� ������ �������, 
		gIndexTableCol - ����� ������� �������,
		gYpos - ������� Y-���������� (��������� ���������� 
			    ����� ������ �� ����� �������)
		gXpos - ����� ���������� ������ ������� (���������
			    �������� �� ������ ���� �������)

	������� ������ - �� ������� ������ ������ ����. �� ������
	������ �������� ���� ������� ����� �������.

*/
#define BROWSE_TABLE_TEXT_FUNCTION(a)\
	{if (!BrowseTableTextFunction(a)) return FALSE;}

	BOOL empty_line = FALSE;

	gCurLineText = NULL;
	gCellText = NULL;
	gIndexTableCell = 0;
	gIndexTableRow = 0;
	gIndexTableCol = 0;
	gYpos = 0;
	gXpos = 0;

	// ������ �������
	BROWSE_TABLE_TEXT_FUNCTION(BROWSE_TABLE_TEXT_TABLE_START);

	// ������ ������, � ������� ���� �����
	if ( FirstCell() ) 
		{
	// ���� �� ������� ������ ������ ����.
		do
			{
			// ������ ������
			BROWSE_TABLE_TEXT_FUNCTION(BROWSE_TABLE_TEXT_RECORD_START);

			// �������� ������ ����� �������
			if (!empty_line) do
				{
				// ������� � ������ ������ ������ ������� ������
				long line = gYpos - gTableRowTops[gIndexTableRow];

				if ( line >= 0 && line < gCellText->lines)
					{
					// ���������� ������ ������
					gCurLineText = &gCellText->line[line];

					// ��������� ������ ������
					BROWSE_TABLE_TEXT_FUNCTION(BROWSE_TABLE_TEXT_STRING);
					}
				else
					{
//					ASSERT ( line >= 0 && line < gCellText->lines);
					}

				gCurLineText = NULL;

				// ������� � ����� ����� ������ ������ ��
				// ������� ������ �� ��� �� ������ ������
				} while ( CellRight() );

			// ����� ������
			BROWSE_TABLE_TEXT_FUNCTION(BROWSE_TABLE_TEXT_RECORD_END);

			// ������� � ����� ����� ������ 
			// �� ��������� ������ ������
			empty_line = !NextLevel();

			} while ( gYpos < gTableTextHeight );

		}

	// ����� �������
	BROWSE_TABLE_TEXT_FUNCTION(BROWSE_TABLE_TEXT_TABLE_END);

	return TRUE;
}
//********************************************************************
static long BottomRow()
{
// ���������� ����� ����� ������ ������ �������,
// ������� �������� ������� ������

	long row = gIndexTableRow,
		 col = gIndexTableCol;

	while( row < gTableRows &&
			gIndexTableCell == gLogicalCells[
							gTableCols * row + col]
		 )
		row++;

	return row-1;	
}
//********************************************************************
static long RightmostCol()
{
// ���������� ����� ����� ������ ������� �������,
// ������� �������� ������� ������

	long row = gIndexTableRow,
		 col = gIndexTableCol;

	while( col < gTableCols &&
			gIndexTableCell == gLogicalCells[
							gTableCols * row + col]
		 )
		col++;

	return col-1;	
}
//********************************************************************
static BOOL SearchTable(
			long fromCol	// ����� ������� ������� ������
			)
{
/* 
	����� ����� ����� ������ ������� �� �������� �������,
	���������� ����� �� ������� ������ ������ gYpos.

	����������� ��� ������ ����������� ������������� �������
	��� ������ ������� BrowseTableText().

	�� ����� � �� ������:
		gYpos - ������� ������� ������ (�� ��������),
		gXpos - ���������������,
		gIndexTableCell - ����� ������,
		gIndexTableRow - ����� ������ �������, 
		gIndexTableCol - ����� ������� �������,
		gCellText - ���������� ������.

   		���������: ����� �������� ����� ���� ���������� ���������, 
		� ��������� ������ ����� �� ��������� ������.

  	��������� ������������ ����������� ����� ��������� 
	������� ������� � ������� ��������� ����� �������.

	���������� FALSE, ���� ������ �� �������, ��� ����
	������� ������ �� ��������.

*/

	long bestCol = LONG_MAX, bestCell = -1;

	// ����������� ��� ������ ������� �� ����� �������
	// �� ������, ������������ ���� ��������� ������
	for (long row = 0; row < gTableRows; row++ )
		{
		// ����� �� ������ � ���� ������
		if (gYpos > gTableRowBottoms[row])
			 continue;

		// ����� �� ������ ������ ����
		if (gYpos < gTableRowTops[row])
			 break;

		// ������ ������ �� ��������� �������
		// �� ������� ���������
		for (long col = fromCol; col < gTableCols; col++)
			{
			// ������-��������
			long cell = gLogicalCells[gTableCols * row + col];

			// �������� ������� ������ � ������
			if (gYpos >= gTableRowTops[row] &&
				gYpos < gTableRowTops[row] + gTableText[cell].lines
				)
				{
				// �������� � ������ ����������
				if ( bestCol > col )
					{
					bestCol = col;
					bestCell = cell;
					}

				break;	// ������� � ��������� ������ �������
				}
			}
		}

	// �� ������ ��������� ���
	if ( bestCell == -1)
		return FALSE;

	// ������ �����
	gIndexTableCell = bestCell;
	gCellText = &gTableText[bestCell];
	gIndexTableRow = gCellText->row;
	gIndexTableCol =  gCellText->col;
	gXpos = gTableColLefts[gIndexTableCol];
	return TRUE;
	
}
//********************************************************************
static BOOL CellRight()
{
/* 
	������� � ������ ������ �� ������� ������
	�� ��� �� ������ ������.

	����������� ��� ������ ����������� ������������� �������
	��� ������ ������� BrowseTableText().

	���������� FALSE, ���� ������ �� �������, ��� ����
	������� ������ �� ��������.

*/

	// ������� ������ �� �������� ������
	long fromCol = RightmostCol() + 1;
	if ( fromCol >= gTableCols )
		return FALSE;

	// ������ ������ �� ��� �� ������ ������
	return SearchTable(fromCol);
	
}
//********************************************************************
static BOOL FirstCell()
{
/*
	����� ������ ������ �������, � ������� ���� �����
	�� ������� ������.

	����������� ��� ������ ����������� ������������� �������
	��� ������ ������� BrowseTableText().

	���������� FALSE, ���� ������ �� �������.

*/

	// ������ �� ������ ���� ������� �� ����� ������ ������
	return SearchTable(0);

}
//********************************************************************
static BOOL NextLevel()
{
/*
	������� � ����� ����� ������ �� ��������� ������ ������.

	����������� ��� ������ ����������� ������������� �������
	��� ������ ������� BrowseTableText().

	���������� FALSE, ���� ������ �� �������, ��� ����
	������� ������ �� ��������.

*/

	// ��������� ������� ������
	gYpos++;
	if ( gYpos >= gTableTextHeight )
		return FALSE;

	// ������ �� ������ ���� ������� �� ����� ������ ������
	return SearchTable(0);

}
//********************************************************************
static BOOL TableText_Finish(
			long reason // ��. enum BROWSE_TABLE_TEXT_REASON
			)
{
/* 
	������������ ����� ������ � �������� ������ �����������
	������������� ������� � ������� ������� BrowseTableText().

	�� �����:

		gCurLineText - ���������� ������ ������,
		gCellText - ���������� ������,
		gIndexTableCell - ����� ������,
		gIndexTableRow - ����� ������ �������, 
		gIndexTableCol - ����� ������� �������,
		gYpos - ������� Y-���������� (��������� ���������� 
			    ����� ������ �� ����� �������)
		gXpos - ����� ���������� ������ ������� (���������
			    �������� �� ������ ���� �������)


*/

	// ����� ������ ������ � ������� ������� (static)
	static long line, col;

	switch(reason)
		{
		case BROWSE_TABLE_TEXT_TABLE_START:
			// ������ �������
			line = 0;
			break;

		case BROWSE_TABLE_TEXT_TABLE_END:
			// ����� �������
			break;

		case BROWSE_TABLE_TEXT_RECORD_START:
			// ������ ������ ������
			col = -1;

			// �������� ������ ������ �� ��������� ������
			while ( line < gYpos )
				{
				NEW_LINE;
				line++;
				}

			// �������� ������� � �����������
			// ����� ������ ��������
			PUT_SPACES(gTableTextLeftIndent);

			if (gTableTextSeparators[0])
				*gMemCur++ = gTableTextSeparators[0];

			break;
			

		case BROWSE_TABLE_TEXT_RECORD_END:
			// ����� ������ ������

			// �������� ������ �������
			if (!EmptyColumns(col+1,gTableCols-1))
				return FALSE;

			NEW_LINE;
			line++;
			break;

		case BROWSE_TABLE_TEXT_STRING:
			// ������ ������

			// �������� ������ �������
			if (!EmptyColumns(col+1,gIndexTableCol-1))
				return FALSE;

			// ������ ���������� �������
			col = RightmostCol();

			// �������� ������ ������
			PUT_STRING(gCurLineText->text);

			// �������� �������� �� ������ ������,
			// � ������ ���� ���������� ������� ������� 
			// � ���������� ����� ����
			if ( gTableTextOptions & ROUT_TABLE_TEXT_ALIGN_COLUMNS )
				PUT_SPACES( gCellText->width -
							gCurLineText->ltext +
							gTableTextIntervalBetweenCellsXX
							);

			// ����������� ����� �������
			if(!AfterColumn(col))
				return FALSE;

			break;
		}

	return TRUE;
}
//********************************************************************
static BOOL EmptyColumns(
		long fromCol,	// ������ ������ �������
		long toCol		// ��������� ������ �������
		)
{
// �������� ������ �������
for(long col = fromCol; col <= toCol; col++)
	{
	// ���������� ������ ������� ���������
	// � �������� ����� �������
	if ( gTableTextOptions & ROUT_TABLE_TEXT_ALIGN_COLUMNS )
		PUT_SPACES(gTableColRights[col] - gTableColLefts[col] +
				   gTableTextIntervalBetweenCellsXX);

	// ����������� ����� �������
	if(!AfterColumn(col))
		return FALSE;

	}

	return TRUE;
}
//********************************************************************
static BOOL AfterColumn(long col)
{
// ����������� ����� �������
	char sep = 0;

	if(col < gTableCols-1)
		// ����������� ����� ���������
		sep = gTableTextSeparators[1];
	else
		// ����������� ����� ��������� �������
		sep = gTableTextSeparators[2];

	if (sep)
		*gMemCur++ = sep;

	return TRUE;
}
//********************************************************************
