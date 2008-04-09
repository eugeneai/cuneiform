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

//Filename: ced_struct.h
//Created 7.12.98 by Bozhenov Artem, (C)CT inc.

#pragma message(__FILE__"(1)")  // BC doesn't understand it somewhy...

#ifndef _CED_STRUCT_
#define _CED_STRUCT_


#include <windows.h>
//#include "edfile.h"
#include "ced.h"

#define		FICTIVE			0xf000
#define		COLUMN_BEGIN	(1|FICTIVE)
#define		LAST_IN_COLUMN	(2|FICTIVE)
#define		FRAME_BEGIN		(3|FICTIVE)
#define		FRAME_END		(4|FICTIVE)
#define		TAB_BEGIN		(5|FICTIVE)
#define		TAB_CELL_BEGIN	(6|FICTIVE)
#define		TAB_END			(7|FICTIVE)
#define		TAB_ROW_BEGIN	(8|FICTIVE)
class CEDPage;
class CEDSection;
class CEDParagraph;
class CEDLine;
class CEDChar;

//��� ��������� ed...Descr ������ ����� ������ ����� 
//CEDParagraph* next, ����� ����� ���� �� ��� ������

typedef struct edColDescr
{
	CEDParagraph* next;
}EDCOLDESCR;

typedef struct edFrameDescr
{
	CEDParagraph* last;
	EDBOX	rec;
	BYTE position;	
	int borderSpace;
	int dxfrtextx;
	int dxfrtexty;
	int flag;
} EDFRAMEDESCR;

typedef struct edTabDescr
{
	CEDParagraph* next,*last,*cur;
	int numOfRows;
	int *table,*linesX,*linesY;
	edSize size;
}
EDTABDESCR;
typedef struct edCellDescr
{
	CEDParagraph* next;
	int cellX;
	int merging;
	int vertTextAlign;
	int leftBrdrType, leftBrdrWidth;
	int rightBrdrType, rightBrdrWidth;
	int topBrdrType, topBrdrWidth;
	int bottomBrdrType, bottomBrdrWidth;
	EDBOX layout;
	int shading;
	int color;
	int flag;
}EDCELLDESCR;
typedef struct edRowDescr
{
	CEDParagraph* next,*last,*cur;//������ ������, ����. ����� � ����� RowBeg ���� TabEnd,cur - ��������� ��������� ������
	int numOfCells;
	int left; 
	int rowHeight;
	int leftBrdrType,leftBrdrWidth;
	int rightBrdrType, rightBrdrWidth;
	int topBrdrType, topBrdrWidth; 
	int bottomBrdrType, bottomBrdrWidth;
	int gaph;
	int position; 
	Bool32 header;
}EDROWDESCR;

typedef struct fontEntry
{
	BYTE fontNumber;
    BYTE fontPitchAndFamily;
    BYTE fontCharset;
    char* fontName;
}FONTENTRY;
typedef struct pictEntry
{
	WORD pictNumber;
	EDSIZE pictSize;
	EDSIZE pictGoal;
	BYTE pictAlign;
	BYTE type;
	DWORD len;
	void* data;
}PICTENTRY;
#define DEC_FUN(a,b,c) typedef a (*FN##b)c

DEC_FUN(Bool32,CED_FormattedWrite,(char * fileName, CEDPage *page));
DEC_FUN(CEDPage*,CED_FormattedLoad,(char * file,Bool32 readFromFile, Word32 bufLen));
DEC_FUN(void,CED_DeleteTree,(CEDPage * pg));


#undef DEC_FUN

class CED_FUNC(CEDPage)
{
public:
	
	//������ � �����������
	EDSIZE	sizeOfImage;		//������� �������� �������� � ��������
	EDSIZE	dpi;				//���������� ������� ��� ���� ��������
	int		turn;				//������� ���� �������� �������� ������������ ���������*2048
	char*	imageName;			//��� ����� �����������. ���� ���� �� ������, ������ � ����� 
								//�������� � ed ������
	
	int		pageNumber;			//����� ��������(=0 �� � �������� ������)
	EDSIZE	pageSizeInTwips;	//������ �������� � ������(1����=1440������) ��� ���������� ���������
	EDRECT	pageBordersInTwips;	//���� �������� � ������
	char	unrecogChar;
	char	recogLang;
	Bool32  resizeToFit;

	int		fontsUsed;			//���������� �������������� ������� � �������
	int		fontsCreated;			//���������� ��������� ������� � �������
	fontEntry*	fontTable;			//��������� �� ������� �������
	int		picsUsed;			//���������� �������������� �������� � �������
	int		picsCreated;			//���������� ��������� �������� � �������
	pictEntry*	picsTable;			//��������� �� ������� ��������

	char *	extData;			//������, ���. ����� �������� � ���� ����� ���������;
	int		extDataLen;			//�� �����

	CEDPage();
	~CEDPage();
	
	Bool32	FormattedWriteRtf(const char * fileName, BOOL merge);
	
	CEDSection * GetSection(int _num);
	CEDParagraph * GetParagraph(int _num);
	CEDLine * GetLine(int _num);
	CEDChar * GetChar(int _num);
	
	Bool32	GoToNextSection();
	Bool32	GoToNextParagraph(Bool32 NonFictiveOnly);
	Bool32	GoToNextLine();
	Bool32	GoToNextChar();
	
	int	GetNumberOfSections();
	int	GetNumberOfParagraphs();
	int	GetNumberOfLines();
	int	GetNumberOfChars();
	
	Bool32 CreateFont(BYTE fontNumber, BYTE fontPitchAndFamily, BYTE fontCharset,
				char* fontName);
	Bool32 GetFont(int number, BYTE* fontNumber, BYTE* fontPitchAndFamily, BYTE* fontCharset,
				char** fontName);
	
	int GetFontByNum(BYTE fontNumber);

	Bool32 CreatePicture(int pictNumber, EDSIZE pictSize, EDSIZE pictGoal, int pictAlign, int type, void * data, int len);

	CEDSection * InsertSection();	//��������� ����� ������ ����� �������. ������� ���������� ����� ������
								//���������� ��������� �� ����� ��������� ������
//	CEDSection * DeleteSection(Bool32 _deleteSubItems);	//������� ������� ������. ������� ���������� ���������� ������.
								//��� � ������������ 
				//_deleteSubItems - ������� �� ��� �������� ��������, ���� ���������� ��
				//� ����������� �������
	CEDSection * SetCurSection(CEDSection* _sect);//������������� ����� �������� ������� ������
	CEDSection * SetCurSection(int _number);//������������� ����� �������� ������� ������
	
	CEDSection * GetCurSection();	//���������� ������� ������
	int		GetNumOfCurSection();	//���������� ������� ������
	
	CEDSection * NextSection();	//���������� ������, ��������� �� �������,0 - ���� ������ ���������
	CEDSection * PrevSection();	//���������� ������, ���������� �������,0 - ���� ������ ������

	int NumberOfSections,NumberOfParagraphs,NumberOfLines,NumberOfChars;

	CEDSection * sections;		//������� ������ �� ������
//	CEDParagraph * paragraphs;	//������� ������ ��������
//	CEDLine * lines;
//	CEDChar * chars;
	
	CEDSection * curSect;		//������� ������
	};

class CED_FUNC(CEDSection)
{
public:
	int		numberOfColumns;	//���������� ������� � ������(n ����)
//	int		numberOfFrames;		//���������� �������-1 � ������(n-1 ����)
	//SIZE *	pColSize;			//��������� �� n-1 ����� �������� SIZE.cx-������ �������,
								//SIZE.cy - ���������� �� ��������� ������� � ������
								//������_���������_������� = ������_�������� - ������_����� -
								//- ������_����.������� - ������_���������_�����_���������
	EDRECT	borders;			//������� �� ���� ������
	int colInterval;
	char sectionBreak;
	int width;
	int height;
	char orientation;
	int headerY;
	int footerY;
	int numSnakeCols;
	BOOL lineBetCol;
	EDCOL *colInfo;
	char *	extData;			//������, ���. ����� �������� � ���� ����� ���������;
	int		extDataLen;			//�� �����

	CEDParagraph * CreateColumn();
	CEDParagraph * CreateFrame(CEDParagraph* hObject, edBox rect, char position=-1, DWORD borderSpace=-1, DWORD dxfrtextx=-1, DWORD dxfrtexty=-1);
	CEDParagraph * CreateParagraph(CEDParagraph * hObject,int align, EDRECT indent, int UserNum,int FlagBorder,EDSIZE interval, edBox layout, int  color, int  shading, 
						   int spaceBetweenLines, char spcBtwLnsMult, 
						   char  keep);

	CEDParagraph * CreateTable(CEDParagraph * hObject);
//	CEDParagraph * ReCreateTable(CEDParagraph * hTable,EDSIZE sz, int * cx,int * cy, int * table, 
//				   Bool32 * bHorShow,Bool32 * bVerShow);
	CEDParagraph * CreateTableRow(CEDParagraph * hTable, 
		int left, int rowHeight, 
		int leftBrdrType, int leftBrdrWidth, 
		int rightBrdrType, int rightBrdrWidth, 
		int topBrdrType, int topBrdrWidth, 
		int bottomBrdrType, int bottomBrdrWidth, 
		int gaph, int position, Bool32 header);

	CEDParagraph * CreateCell(CEDParagraph* hRow, int cellX, int merging, int vertTextAlign, int leftBrdrType, int leftBrdrWidth, int rightBrdrType, int rightBrdrWidth, int topBrdrType, int topBrdrWidth, int bottomBrdrType, int bottomBrdrWidth, EDBOX layout, int shading, int color);

	CEDParagraph * GetColumn( int _num);
//	CEDParagraph * GetFrame( int _num);
	
	CEDSection();
	~CEDSection();
	
	CEDParagraph * InsertParagraph(Bool32 AfterCurrent=TRUE);	//��������� ����� ����� ����� ��������. ������� ���������� ����� �����
								//���������� ��������� �� ����� ��������� �����
//	CEDParagraph * DeleteParagraph(Bool32 _deleteSubItems);	//������� ������� �����. ������� ���������� ���������� �����.
								//�� � ������������ 
				//_deleteSubItems - ������� �� ��� �������� ��������, ���� ���������� ��
				//� ����������� �������
	CEDParagraph *	SetCurParagraph(CEDParagraph* _para);//������������� ����� �������� �������� ������
	CEDParagraph * SetCurParagraph(int _number);//������������� ����� �������� ������� ������

	CEDParagraph * GetCurParagraph();	//���������� ������� ����� 
	int		GetNumOfCurParagraph();	//���������� ������� �����
	
	CEDParagraph * NextParagraph(Bool32 _goThroughSect);	//���������� �����, ��������� �� �������,0 - ���� ����� ���������
	CEDParagraph * PrevParagraph(Bool32 _goThroughSect);	//���������� �����, ���������� ��������,0 - ���� ����� ������
		//���� _goThroughSect = TRUE, �� ������� ��������� ��������� ����� � �����, �����- � ������

	CEDParagraph * paragraphs;	//������� ������ �������
	CEDParagraph * columnsBeg,*columnsEnd,*columnsCur/*,*framesBeg,*framesEnd,*framesCur*/;

	CEDParagraph * curPara;//������� �����
	CEDSection * prev,*next;		//��������� �� �������� ��-�� � ������
	int internalNumber;			//���������� ����� ������ �� ������ �����

friend CEDPage;
};

class CED_FUNC(CEDParagraph)
{
public:
	int		type;					//��� ������
	int		alignment;				//������������ �������
	EDRECT	indent;					//�������: left=�����, right=������,top=�����.������(� ������)
	int		userNumber;				//�����, ������ ������������� �� ����� ������������
	int		border;					//����� ������ �������
	EDSIZE	interval;				//cx-������� ������, cy- ������

	edBox		layout;					//������������ ������ �� ��������
	int		color;
	int		shading;
	int		spaceBetweenLines;
	char	spcBtwLnsMult;
	char	keep;

	int leftBrdrType;
	int rightBrdrType;
	int topBrdrType;
	int bottomBrdrType;
	int leftBrdrWidth;
	int rightBrdrWidth;
	int topBrdrWidth;
	int bottomBrdrWidth;
	int brdrBtw;

	void *	descriptor;			//��������� �� ����������� ��������� ����������� ��������
	
	char *	extData;			//������, ���. ����� �������� � ���� ����� ���������;
	int		extDataLen;			//�� �����

	CEDParagraph();
	~CEDParagraph();
	
	CEDLine*	GetLine(int _num);	
	int	GetCountLine();	
	
	CEDParagraph* GetFirstObject();
	CEDParagraph*	GetNextObject();
	CEDParagraph* GetCell(int cell);
	CEDParagraph* GetRow(int row);
	CEDParagraph* GetLogicalCell(int number);
	int GetCountLogicalCell();
	void CreateTableOfCells();		
	CEDLine * InsertLine();	//��������� ����� ������ ����� �������. ������� ���������� ����� ������
								//���������� ��������� �� ����� ��������� ������
	//CEDLine * DeleteLine(Bool32 _deleteSubItems);	//������� ������� ������. ������� ���������� ���������� ������.
								//��� � ������������ 
				//_deleteSubItems - ������� �� ��� �������� ��������, ���� ���������� ��
				//� ����������� �������

	void	SetCurLine(CEDLine* _line);//������������� ����� �������� ������� ������
	CEDLine * SetCurLine(int _number);//������������� ����� �������� ������� ������
	
	CEDLine * GetCurLine();	//���������� ������� ������
	int		GetNumOfCurLine();	//���������� ������� ������
	
	CEDLine * NextLine(Bool32 _goThroughPara);	//���������� ������, ��������� �� �������,0 - ���� ������ ���������
	CEDLine * PrevLine(Bool32 _goThroughPara);	//���������� ������, ���������� �������,0 - ���� ������ ������
		//���� _goThroughSect = TRUE, �� ������� ��������� ��������� ������ � �����, �����- � ������

	CEDLine * lines;	//������� ������ �����
	int		numOfLines;
	CEDLine * curLine;		//������� ������
	CEDParagraph * prev,*next;		//��������� �� �������� ��-�� � ������
	int internalNumber;			//���������� ����� ������ �� ������ �����
	int parentNumber;			//���������� ����� �������� � �����
friend CEDSection;
friend CEDPage;
};

class CED_FUNC(CEDLine)
{
public:
	char *	extData;			//������, ���. ����� �������� � ���� ����� ���������;
	int		extDataLen;			//�� �����
	Bool32	hardBreak;		
	int defChrFontHeight;

	CEDLine();
	~CEDLine();
	
	CEDChar*	GetChar(int _num);	
	int	GetCountChar();	

	CEDChar * InsertChar();	//��������� ����� ������ ����� ��������. ������� ���������� ����� ������
								//���������� ��������� �� ����� ��������� ������
//	CEDChar * DeleteChar(Bool32 _deleteSubItems);	//������� ������� ������. ������� ���������� ���������� ������.
								//�� � ������������ 
					//_deleteSubItems - ������� �� ��� �������� ��������, ���� ���������� ��
				//� ����������� �������

	void	SetCurChar(CEDChar* _char);//������������� ����� �������� ������� �������
	CEDChar * SetCurChar(int _number);//������������� ����� �������� ������� �������
	
	CEDChar * GetCurChar();	//���������� ������� ������
	int		GetNumOfCurChar();	//���������� ������� ������
	
	CEDChar * NextChar(Bool32 _goThroughLines);	//���������� ������, ��������� �� �������,0 - ���� ������ ���������
	CEDChar * PrevChar(Bool32 _goThroughLines);	//���������� ������, ���������� ��������,0 - ���� ������ ������
		//���� _goThroughSect = TRUE, �� ������� ��������� ��������� ������ � �����, �����- � ������

	CEDChar * chars;	//������� ������ ��������
	int		numOfChars;

	CEDChar * curChar;			//������� ������
	CEDLine * prev,*next;		//��������� �� �������� ��-�� � ������
	int internalNumber;			//���������� ����� ������ �� ������ �����
	int parentNumber;			//���������� ����� �������� � �����
friend CEDParagraph;
friend CEDPage;
};

class CED_FUNC(CEDChar)
{
public:
	edRect		layout;			//���������� ������� �� �������� �����������(� ��������)
	int		fontHeight,fontAttribs;	//��������� ������
	int fontNum;
	int fontLang;
	int foregroundColor;
	int backgroundColor;
	letterEx * alternatives;	//������ �����������
	int		numOfAltern;
	char *	extData;			//������, ���. ����� �������� � ���� ����� ���������;
	int		extDataLen;			//�� �����

	CEDChar();
	~CEDChar();
	CEDChar * prev,*next;		//��������� �� �������� ��-�� � ������
protected:
//	int internalNumber;			//���������� ����� ������ �� ������ �����
	int parentNumber;			//���������� ����� �������� � �����
friend CEDLine;
friend CEDPage;
friend void FormattedTR(const text_ref* pt);
friend void StripLines();
};


#endif _CED_STRUCT_