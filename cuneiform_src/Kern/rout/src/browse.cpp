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


// Browse.cpp

//********************************************************************
//********************************************************************

#include <string.h>
#include "stdafx.h"
#include "rout_own.h"

// ����� ������� ������
// ���� �������=NULL, ����� ����� ��� ����� �����������,
// ��� ���� �������������� ���������� �������� gHitxxx
// FALSE �������� ���������� ����� � ������� FALSE.
#define BROWSE_FUNCTION(a,b) \
		{if (BrowseFunction && \
			!BrowseFunction(a,b)\
		)\
			return FALSE;}

//********************************************************************
BOOL BrowsePage(
	FNROUT_BrowseFunction BrowseFunction, // �������� ��� ������
	BOOL wantSkipTableCells,	// ���������� ������ ������
	BOOL wantSkipParagraphs		// ���������� ������
	)
{
/* ����� ��������.

   ��� ������� ������� ���������� ������� "BrowseFunction"
   ���� ������� "BrowseFunction" ���������� FALSE, ��
   ����� �������� ������������ � BrowsePage ����� ���������� FALSE.

   �� ����� �������� ������ ����� ������:
		wantSkipTableCells �
		wantSkipParagraphs
*/
	long sections=0, columns=0, frames=0;
	long indexSection=0, indexColumn=0, indexFrame=0;

	// ������� ������� �� ���� �������
	gSectionHandle = NULL;
	gColumnHandle = NULL;
	gFrameHandle = NULL;
	gTableHandle = NULL;
	gCellHandle = NULL;
	gParagraphHandle = NULL;
	gLineHandle = NULL;

	// �������� ��������� ��������
	gHitSections = 0;
	gHitColumns = 0;
	gHitFrames = 0;
	gHitTables = 0;
	gHitCells = 0;
	gHitParagraphs = 0;
	gHitLines = 0;

	gHitChars = 0;
	gHitPictures = 0;

	// ��������� �� ��������
	if ( !gPageHandle )
		{
		PAGE_NOT_LOADED;
		return FALSE;
		}

	// ������ ��������
	BROWSE_FUNCTION(gPageHandle,BROWSE_PAGE_START);

	// �������
	sections = CED_GetCountSection(gPageHandle);
	for (indexSection = 0; indexSection < sections; indexSection++)
		{
		gSectionHandle = CED_GetSection(gPageHandle,indexSection);

		// ������ �������
		ASSERT(gSectionHandle);
		gHitSections++;
		BROWSE_FUNCTION(gSectionHandle,BROWSE_SECTION_START);

		// �������
		columns = CED_GetCountColumn(gSectionHandle);
		for (indexColumn = 0; indexColumn < columns; indexColumn++)
			{
			gColumnHandle = CED_GetColumn(gSectionHandle,indexColumn);

			// ������ �������
			ASSERT(gColumnHandle);
			gHitColumns++;
			BROWSE_FUNCTION(gColumnHandle,BROWSE_COLUMN_START);

			// ����� �������, ������ � ������� ������ �������
			if (!BrowseParagraphs(gColumnHandle,
							BrowseFunction,
							wantSkipTableCells,
							wantSkipParagraphs
				))
				return FALSE;

			// ����� �������
			BROWSE_FUNCTION(gColumnHandle,BROWSE_COLUMN_END);
			gColumnHandle = NULL;
			}

		// ������ �� �������� ��������, ������ ��� �����������
		// ������� � �������������� � ������� BrowseParagraphs()
		// -- 18.10.99 E.P.
/*
		// ������
		frames = CED_GetCountFrame(gSectionHandle);
		for (indexFrame = 0; indexFrame < frames; indexFrame++)
			{
			gFrameHandle = CED_GetFrame(gSectionHandle,indexFrame);

			// ������ ������
			ASSERT(gFrameHandle);
			gHitFrames++;
			BROWSE_FUNCTION(gFrameHandle,BROWSE_FRAME_START);

			// ����� �������, ������ � �������
			if (!BrowseParagraphs(gFrameHandle,
							BrowseFunction,
							wantSkipTableCells,
							wantSkipParagraphs
				))
				return FALSE;

			// ����� ������
			BROWSE_FUNCTION(gFrameHandle,BROWSE_FRAME_END);
			gFrameHandle = NULL;
			}
*/
		// ����� �������
		BROWSE_FUNCTION(gSectionHandle,BROWSE_SECTION_END);
		gSectionHandle = NULL;
		}

	// ����� ��������
	BROWSE_FUNCTION(gPageHandle,BROWSE_PAGE_END);

	return TRUE;

}
//********************************************************************
BOOL BrowseParagraphs(Handle hParentObject,
	FNROUT_BrowseFunction BrowseFunction, // �������� ��� ������
	BOOL wantSkipTableCells,	// ���������� ������ ������
	BOOL wantSkipParagraphs		// ���������� ������
	)
{
/*
   ����� �������, ������ � ������� � ��������
   ������� hParentObject (�������, ������, ������)

   ��� ������� ������, ��������, ������� ����������
   ������� "BrowseFunction", � ���� ��� ���������� FALSE, ��
   ����� ������������, ��� ���� BrowseParagraphs �����
   ���������� FALSE.

   �� ����� ������ ����� ������:
		wantSkipTableCells �
		wantSkipParagraphs
*/
	long objects=0, lines=0, chars=0;
	long indexObject=0, indexLine=0, indexChar=0;
	Handle hObject = NULL;

	gParagraphHandle = NULL;
	gLineHandle = NULL;

	ASSERT (hParentObject);

	// ���� �� ���� ��������
	for (hObject = CED_GetFirstObject(hParentObject);
		 hObject;
		 hObject = CED_GetNextObject(hObject)
		 )
		{
		// ���������� ��� �������
		if (CED_IsFrame(hObject))
			{
			// �����
			gFrameHandle = hObject;

			// ������ ������
			gHitFrames++;
			BROWSE_FUNCTION(gFrameHandle,BROWSE_FRAME_START);

			// ����� ������� � ������ ������ ������
			if (!BrowseParagraphs(gFrameHandle,
							BrowseFunction,
							wantSkipTableCells,
							wantSkipParagraphs
				))
				return FALSE;

			// ����� ������
			BROWSE_FUNCTION(gFrameHandle,BROWSE_FRAME_END);
			gFrameHandle = NULL;

			}

		else if (CED_IsTable(hObject))
			{
			// �������
			if(gTableHandle)
				{
				DEBUG_PRINT("Skipping table inside table");
				continue;
				}

			gTableHandle = hObject;

			// ���������� ����� � �������� �������
			EDSIZE dim = CED_GetSize(gTableHandle);
			gTableRows = dim.cy;
			gTableCols = dim.cx;

			// ���������� ���������� �����
			gTableCells = CED_GetCountLogicalCell(gTableHandle);

			// ������ ���������� ������� �����
			gLogicalCells = (long*)CED_GetTableOfCells(gTableHandle);

			// ������ �������
			gHitTables++;
			BROWSE_FUNCTION(gTableHandle,BROWSE_TABLE_START);

			// ����� ����� �������
			if (!wantSkipTableCells &&
				!BrowseCells(BrowseFunction)
				)
				return FALSE;

			// ����� �������
			BROWSE_FUNCTION(gTableHandle,BROWSE_TABLE_END);
			gTableHandle = NULL;
			gTableRows = 0;
			gTableCols = 0;
			gTableCells = 0;
			gLogicalCells = NULL;
			}

		else if (CED_IsParagraph(hObject))
			{
			// ���������� ������?
			if (wantSkipParagraphs)
				continue;

			// �����
			gParagraphHandle = hObject;

			// ������ ������
			gHitParagraphs++;
			BROWSE_FUNCTION(gParagraphHandle, BROWSE_PARAGRAPH_START);

			// ����� ����� � ������
			lines = CED_GetCountLine(gParagraphHandle);
			for (indexLine = 0; indexLine < lines; indexLine++)
				{
				gLineHandle = CED_GetLine(gParagraphHandle,indexLine);

				// ������ ������
				ASSERT(gLineHandle);
				gHitLines++;
			    gEdLineHardBreak = CED_GetLineHardBreak(gLineHandle);
				BROWSE_FUNCTION(gLineHandle,BROWSE_LINE_START);

				// ����� �������� � ������
				chars = CED_GetCountChar(gLineHandle);
				for (indexChar = 0; indexChar < chars; indexChar++)
					{
					Handle charHandle = CED_GetChar(gLineHandle,
													indexChar);
					ASSERT(charHandle);

					if (CED_IsPicture(charHandle))
						{
						// ��������
						// �������� �������� ��������
						if (!PictureFromChar(charHandle))
							return FALSE;

						gHitPictures++;
						BROWSE_FUNCTION(charHandle, BROWSE_PICTURE);

						gPictureNumber = 0;
						gPictureData = 0;
						gPictureLength = 0;
						}
					else
						{
						// ������� ������
						gHitChars++;

						// ������� �� ������
						gEdCharHidden =
								CED_GetCharFontAttribs(charHandle) &
								ED_HIDDEN;

						BROWSE_FUNCTION(charHandle,BROWSE_CHAR);
						}
					}

				// ����� ������
				BROWSE_FUNCTION(gLineHandle,BROWSE_LINE_END);
				gLineHandle = NULL;
				}

			// ����� ������
			BROWSE_FUNCTION(gParagraphHandle, BROWSE_PARAGRAPH_END);
			gParagraphHandle = NULL;
			}
		else
			{
			DEBUG_PRINT("Skipping fictive paragraph in ED");
			}
		}

	return TRUE;

}
//********************************************************************
BOOL BrowseCells(FNROUT_BrowseFunction BrowseFunction)
{
/* ����� ����� ������� gTableHandle

   ��� ������ ������ ���������� ������� "BrowseFunction"
   � ����� ����, ��� ������ ������� � ������
   ���������� ������� BrowseParagraphs().

   ���� ���� �� ���� ������� ���������� FALSE, ��
   ����� ������������ � BrowseCells ����� ���������� FALSE.
*/

	// ���������� ������ �����
	Byte sprav[10000];
	ASSERT(gTableCells < sizeof(sprav));
	memset(&sprav,0,sizeof(sprav));

	// ���� �� ������� �������
	for (gIndexTableRow = 0;
		gIndexTableRow < gTableRows;
		gIndexTableRow++
		)
		{
		// ������ ������ �������
		gRowHandle = CED_GetTableRow(gTableHandle,gIndexTableRow);
		BROWSE_FUNCTION((Handle)gIndexTableRow, BROWSE_ROW_START);

		// ���� �� �������� �������
		for (gIndexTableCol = 0;
			gIndexTableCol < gTableCols;
			gIndexTableCol++
			)
			{
			// ���������� ����� ������
			gIndexTableCell = gLogicalCells[
								gIndexTableRow * gTableCols +
								gIndexTableCol];

			// ��������� �� ����������
			if( gIndexTableCell < 0 ||
				sprav[gIndexTableCell]
			  )
				{
				// � ���� ���������� ������ ��� ����
				gCellHandle = NULL;
				continue;
				}

			sprav[gIndexTableCell] = 1;

			// ������ ������
			gCellHandle = CED_GetLogicalCell(
							gTableHandle,
							gIndexTableCell);
			ASSERT(gCellHandle);

			gHitCells++;
			BROWSE_FUNCTION(gCellHandle, BROWSE_CELL_START);

			// ����� ������� � ������
			if ( !BrowseParagraphs(gCellHandle,
							BrowseFunction,
							FALSE,	// wantSkipTableCells
							FALSE	// wantSkipParagraphs
				))
				return FALSE;

			// ����� ������
			BROWSE_FUNCTION(gCellHandle, BROWSE_CELL_END);
			gCellHandle = NULL;
			}

		// ����� ������ �������
		BROWSE_FUNCTION((Handle)gIndexTableRow, BROWSE_ROW_END);
		gRowHandle = 0;
		}

	gIndexTableCell = 0;
	gIndexTableRow = 0;
	gIndexTableCol = 0;

	return TRUE;

}
//********************************************************************
BOOL BrowseTable(FNROUT_BrowseFunction BrowseFunction)
{
// ����� �������.

	// ������ �������
	BROWSE_FUNCTION(gTableHandle,BROWSE_TABLE_START);

	// ����� ����� �������
	if ( !BrowseCells(BrowseFunction) )
		return FALSE;

	// ����� �������
	BROWSE_FUNCTION(gTableHandle,BROWSE_TABLE_END);

	return TRUE;
}
//********************************************************************
