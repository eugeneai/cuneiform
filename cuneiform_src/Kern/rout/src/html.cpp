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


// HTML.cpp

//********************************************************************
//
// HTML.cpp - ������ HTML
//
// This file creation date: 27.05.99
// By Eugene Pliskin pliskin@cs.isa.ac.ru
//********************************************************************

#include <string.h>
#include "stdafx.h"
#include "rout_own.h"
#include "compat_defs.h"

static BOOL Static_MakeHTML(Handle hObject, long reason);

static BOOL FontStyle(ULONG newStyle);
static BOOL BeginParagraph(Handle hObject);
static BOOL CellStart();
static BOOL CalcCellSpan();
static BOOL OptimizeTags();
static BOOL Picture();
static BOOL CreatePageFilesFolder();

static ULONG sFontStyle = 0;		// ����� ������
static long rowspan = 0, colspan = 0;
static BOOL hocrmode = FALSE; // If true, print hOCR tags to output.

//********************************************************************
BOOL MakeHTML()
{
/* ������ HTML.

   ���������� �������.
   ����� ����� �����������, ���� gPreserveLineBreaks = TRUE.
*/
	sFontStyle = 0;			// ����� ������
	hocrmode = FALSE;

	return BrowsePage(Static_MakeHTML,
				FALSE,		// wantSkipTableCells
				FALSE);		// wantSkipParagraphs

}
//********************************************************************
BOOL MakeHOCR() {
    sFontStyle = 0;
    hocrmode = TRUE;
    return BrowsePage(Static_MakeHTML, FALSE, FALSE);
}
//********************************************************************
BOOL Static_MakeHTML(
			Handle hObject,
			long reason	// ��. enum BROWSE_REASON
			)
{
    char buf[256] = "";
    edRect r;
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

			// ����� ������
			FontStyle(CED_GetCharFontAttribs(hObject));

			r = CED_GetCharLayout(hObject);
			// �������� ������
                        if(r.left != -1 && hocrmode) {
                            sprintf(buf, "<span title=\"bbox %d %d %d %d\">", r.left,
                            r.top, r.right, r.bottom);
                            PUT_STRING(buf);
                        }

                        ONE_CHAR(hObject);
                        if(r.left != -1 && hocrmode)
                            PUT_STRING("</span>");

			break;

		case BROWSE_LINE_END:
			// ����� ������ ������
			if ( gPreserveLineBreaks || gEdLineHardBreak )
				PUT_STRING("<br>");
			break;

		case BROWSE_PARAGRAPH_START:
			// ������ ������
			FontStyle(0);
			BeginParagraph(hObject);
			break;

		case BROWSE_PARAGRAPH_END:
			// ����� ������
			FontStyle(0);
			PUT_STRING("</p>");
			break;

		case BROWSE_PAGE_START:
			// ������ ��������
			FontStyle(0);
			PUT_STRING("<html><body>");
			break;

		case BROWSE_PAGE_END:
			// ����� ��������
			PUT_STRING("</body></html>");
			break;

		case BROWSE_TABLE_START:
			// ������ �������
			FontStyle(0);
			PUT_STRING("<table border>");
			break;

		case BROWSE_TABLE_END:
			// ����� �������
			FontStyle(0);
			PUT_STRING("</table>");
			break;

		case BROWSE_ROW_START:
			// ������ ������ �������
			PUT_STRING("<tr>");
			break;

		case BROWSE_CELL_START:
			// ������ ������ �������
			CellStart();
			break;

		case BROWSE_PICTURE:
			// ��������
			Picture();
			break;

		}

	// �������� �� ������� � ��������
	WORDS_CONTROL(reason);

	// ���������� ���������� �����
	OptimizeTags();

	return TRUE;	// ���������� ��������
}
//********************************************************************
static BOOL FontStyle(ULONG newStyle)
{

if ((newStyle & FONT_BOLD) &&
				(!(sFontStyle & FONT_BOLD) ||
				  (sFontStyle & FONT_LIGHT)))
	{PUT_STRING("<b>");}

else if ((sFontStyle & FONT_BOLD) &&
				(!(newStyle & FONT_BOLD) ||
				  (newStyle & FONT_LIGHT)))
	{PUT_STRING("</b>");}

if ((newStyle & FONT_ITALIC) &&
				(!(sFontStyle & FONT_ITALIC) ))
	{PUT_STRING("<i>");}

else if ((sFontStyle & FONT_ITALIC) &&
				(!(newStyle & FONT_ITALIC) ))
	{PUT_STRING("</i>");}

if ((newStyle & FONT_UNDERLINE) &&
	!(sFontStyle & FONT_UNDERLINE))
	{PUT_STRING("<u>");}

else if ((sFontStyle & FONT_UNDERLINE) &&
		 !(newStyle & FONT_UNDERLINE))
	{PUT_STRING("</u>");}

// ��������� �����
sFontStyle = newStyle;
return TRUE;
}
//********************************************************************
static BOOL BeginParagraph(Handle hObject)
{
	const char *p = NULL;
	char buf[80] = "";
        edBox b = CED_GetLayout(hObject);
        ULONG alignment = CED_GetAlignment(hObject);

        switch (alignment & ALIGN_MASK)	{
	case ALIGN_CENTER:
		p = "center";
		break;

	case (ALIGN_LEFT | ALIGN_RIGHT):
		p = "justify";
		break;

	case ALIGN_LEFT:
	default:
		// "left" by default
	    ;
    }

    PUT_STRING("<p");
    if (p) {
        sprintf(buf, " align=%s", p);
        PUT_STRING(buf);
    }

    if (b.x != -1 && hocrmode) {
        sprintf(buf, " title=\"bbox %d %d %d %d\"", b.x, b.y, b.x + b.w, b.y
                + b.h);
        PUT_STRING(buf);
    }
    PUT_STRING(">");

    return TRUE;
}
//********************************************************************
static BOOL CellStart()
{
// ������ �������
	char buf[80] = "";

	// ��������� ������ ������
	CalcCellSpan();

	if ( rowspan == 1 && colspan == 1 )
		strcpy(buf,"<td>");

	else if ( rowspan > 1 && colspan == 1 )
		sprintf(buf,"<td rowspan=%d>",rowspan);

	else if ( rowspan == 1 && colspan > 1 )
		sprintf(buf,"<td colspan=%d>",colspan);

	else // ( rowspan > 1 && colspan > 1 )
		sprintf(buf,"<td rowspan=%d colspan=%d>",rowspan,colspan);

	PUT_STRING(buf);
	return TRUE;
}
//********************************************************************
static BOOL CalcCellSpan()
{
// ��������� ������ ������
	long row,col;

	rowspan = 0;
	colspan = 0;

	// �������� ���� �� ������� ������
	row = gIndexTableRow;
	col = gIndexTableCol;

	while ( row < gTableRows &&
			gIndexTableCell == gLogicalCells[row*gTableCols+col]
		  )
		{
		rowspan++;
		row++;
		}

	// �������� ������ �� ������� ������
	row = gIndexTableRow;
	col = gIndexTableCol;

	while ( col < gTableCols &&
			gIndexTableCell == gLogicalCells[row*gTableCols+col]
		  )
		{
		colspan++;
		col++;
		}

	ASSERT(rowspan>0 && colspan>0);
	return TRUE;
}
//********************************************************************
static BOOL OptimizeTags()
{
	// ���������� ���������� �����
	long l1 = 0, l2 = 0;
	char *p;

#define SUBST(a,b) {\
		l1 = strlen(a);\
		l2 = strlen(b);\
		p = (char*)gMemCur - l1;\
		if (!memcmp(a,p,l1))\
			{\
			strcpy(p,b);\
			gMemCur -= l1 - l2;\
			}\
		}

	SUBST("<td><p>","<td>");
	SUBST("</p><td>","<td>");
	SUBST("</p></table>","</table>");
	SUBST("<p></p>","");
	SUBST("<br></p>","</p>");

	return TRUE;
}
//********************************************************************
static BOOL Picture()
{
/* ��������.

	gPictureNumber - img number 1
	gPictureData   - DIB address, wiith header
	gPictureLength - DIB length, with header

	1. ������� �������� ��� �������� "<page>_files"
	2. �������� �������� � BMP-���� <�����>.bmp.
	3. �������� ��� "img" �� ������� �� ���� ��������.
*/
	char buf[256] = "";
	char absPicFileName[256] = "";
	char relPicFileName[256] = "";
	char dir[_MAX_PATH], name[_MAX_PATH], ext[_MAX_EXT];

	// create folder for images gPageFilesFolder.
	if ( !CreatePageFilesFolder() )
		return FALSE;

	// create file name
	split_path(gPageName, dir, name, ext);

	// write picture to bmp file
	if(dir[0])
	    sprintf(absPicFileName,"%s/%s/%d.bmp", dir,
	            gPageFilesFolder, gPictureNumber);
	else
	    sprintf(absPicFileName,"%s/%d.bmp",
	            gPageFilesFolder, gPictureNumber);

	sprintf (relPicFileName,"%s/%d.bmp",
		gPageFilesFolder, gPictureNumber);

	if ( !WritePictureToBMP_File(
					gPictureData,
					gPictureLength,
					absPicFileName)
		)
		return FALSE;

	// write img html tag.
	sprintf (buf,"<img src=%s "
"width=%d height=%d "
"alt=\"%s\">",
		relPicFileName,
		gPictureGoal.cx * 72L / 1440L,
		gPictureGoal.cy * 72L / 1440L,
		relPicFileName
		);

	PUT_STRING(buf);
	return TRUE;
}
//********************************************************************

/**
 * Create a subdirectory to hold image files for html document.
 */
static BOOL CreatePageFilesFolder() {
    // ������� �������� ��� �������� gPageFilesFolder.
    char dir[_MAX_PATH], name[_MAX_PATH], ext[_MAX_EXT], path[_MAX_PATH];

    // ������ �� ��� ��������?
    if (!gPageName[0])
        return FALSE;

    // ���������� ��� ��������
    split_path(gPageName, dir, name, ext);
    memset(gPageFilesFolder, 0, sizeof(gPageFilesFolder));
    sprintf(gPageFilesFolder, "%s_files", name);

    // ������� ��������
    if(dir[0])
        sprintf(path, "%s/%s", dir, gPageFilesFolder);
    else
        sprintf(path, "%s", gPageFilesFolder);
    if (CreateDirectory(&path[0], 0) == FALSE) {
        DWORD err = GetLastError();
        if (err != ERROR_ALREADY_EXISTS) {
            DEBUG_PRINT("CreatePageFilesFolder error = %d",err);
            return FALSE;
        }
    }

    return TRUE;
}
//********************************************************************
