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

#ifndef __TABL_H
#define __TABL_H

#include "wind32.h"

//#define DEMO
#ifdef DEMO
  //#define uint  unsigned int
  #define KNOT struct h_knot
  KNOT { KNOT *next,*back; };
  typedef struct {int i;} PAR;
  typedef struct {int i;} STAT_STR;
  typedef struct {STAT_STR *stat_str; int dx_col,dy_col,dsym_col,dy_Low,dy_Upp;} STAT_COL;
  typedef int (*FUN_POMP)(void);
  typedef void (*FUN_MESS)(WORD wPar,DWORD lPar);
  typedef struct hSTRET
  { short xn,xk,yn,yk;
    float k;
    short thickness;
    float angle;
    BYTE FeatOrient;
    BYTE TypeLine;
    short LenShadow;
  } STRET;
  typedef struct { KNOT ***beg_as; KNOT *beg_free;
         int kx,ky,dx,dy,xmin,ymin; BOUND *bnd; } AS;
  //typedef struct {int i;};
#endif
#define SUB_TREE
typedef struct hSUB_ALLOC
{
	char **Ptr;//[NumPtr][SizePtr[i]]������ ���������� (���������.�����.������-��)
  int NumPtr,CurrPtr;//����� ����������, ������ �����. ��������
  long *SizePtr,Size;//[NumPtr]������ ���� ��������� � ����� ����� ������-��
  long CurrPos;      //������� � �����.��������

} SUB_ALLOC;

#define SIZE_SEGL 65500L

//������� ��������� ���������� � ��������� ������
//---�������� �����(=> � ������) �� ����� �����
typedef struct hHIER_LINE
{
	int NumLev;    //����� V- ��� H-�������
  BYTE *TypeLine;//[NumLev] ���� ����� �� V- ��� H-�������
} HIER_LINE;

//---�������� �����/�������� ������� (�����������, ��������� ��������
//�������� ��������. ����/����� �������)
typedef struct hKNOT_TABL
{
	int beg,end;//������. ������ ��������. ���� ����
  char *Name;   //��� ���� | NULL | "NO_OCR" => ����� ����� ���� �� ���� OCR-��
} KNOT_TABL;
typedef struct hCAPTION_TABLE
{
	int NumLev;  //����� ������� �����/��������
  int *NumCol; //[NumLev] ����� ���� �������
  KNOT_TABL **TreeCapt; //[NumLev][NumCol[NumLev]] ���� ������ �� �������
} CAPTION_TABLE;
//--- V- ��� H-��������, ������������ �� ��������� ������ � �������
typedef struct hHIER_CELL_TXT
{
	int NumCol; //����� ����(H|V), ������ ������� ������ ���������. ��������
  int *IndCol;//[NumCol] ������� ���������������� ����
} HIER_CELL_TXT;
//---������.���-��� � ������������ �����
typedef struct hLINE_INTRVL
{
	int Interval,sko;//�������� �� ����.������-����� � ��� �.�.�
  BYTE TypeLine;
  BYTE Align;
} LINE_INTRVL;
typedef struct hLINE_APRIOR
{
	int Num;          //����� V- ��� H-�����
  LINE_INTRVL *Line;//[Num] - ������� ���������� V- ��� H-�����
} LINE_APRIOR;
//---����� �������� �����!!!ADD XOR � �.�.!!!
#ifndef DEMO
typedef struct hCONTENT
{
	uint Digit:1,      //�����
  Letter:1,          //�����
  LowerCase:1,       //��������� �� ����� �����
  UpperCase:1,       //--//-- �������
  PunctuationMarks:1,//����� ����������
  MultiPoints:1,     //����������
  Indice:1,          //�������
  Fraction:1,        //�����
  ProperName:1,      //������ ����� ������ - ��� �����������
  All:1,             //����� ������
  buf:6;             //������
  BYTE *SpecSymb;    //����� ����������� � ����� �-������ ��������� ���������
                     //���� ��� NULL
} CONTENT;
#endif
#define IN_NO -30000
//���������� �����
#define ALG_BEG 0
#define ALG_END 1
#define ALG_CENTER 2
#define TRUEinBLOCK 2
//���� �����
#define ROOT 0
#define TXT  1
#define CELL 2
#define CELL_CAPT 3
#define HIER_V 4
#define HIER_H 5

#define INDEF -32000

#ifndef DEMO
typedef struct hINF_CELL
{
	CONTENT Content;
  uint JustH:2,   //�����.������������(LEFT/RIGHT/CENTER)
  JustV:2,        //����. ������������(TOP/BOTTOM/CENTER)
  FontSizeConst:1,//���������� ������ ������ � �������
  FontStyle:3,    //���������� ���.������ Normal|Bold|Italic
  MultiStr:1,     //������������� ������
  MultiWord:1,    //������������ ������
  TreeCell:1,     //�������� �� ����������� ��������� ������
  SortedNumber:2, //���� �� ������� �� ������� ���� �����(TRUE),
                  //���� � �������� ��������� �����(TRUEinBLOCK)
                  //���� ��� ������� (FALSE) (����� ����� ������ ���
                  //����, CONTENT �������=DIGIT
  buf:3;          //������
} INF_CELL;
#endif

typedef struct hPAR_TABL
{
	char *TitleTable;
  int NumColV;
  HIER_LINE HierLineH,HierLineV;
  CAPTION_TABLE CaptionH,CaptionV;
  HIER_CELL_TXT HierCellTxtH,HierCellTxtV;
  LINE_APRIOR LineH,LineV;
  INF_CELL *InfCell;//[NumColV]
} PAR_TABL;
typedef struct hSMP_LINE
{
	int Coor,Interval,sko;//����-�� ��� �����,�������� �� ������ ,�.�.�. ���������
  BYTE TypeLine; //��� �����
  BYTE Align;
  int Num;       //����� ���������, ������������ � ���� ��������
  int LenShad;   //����� �����.���������
  int Ave;       //����������� ����-�� ���������
  int AveThick;  //����������� ������� �����
} SMP_LINE;
typedef struct hCOOR_IDENT
{
	short Coor,Thick;
  BYTE Id; //TRUE ��� FALSE, ���� ����� �� ������������� �������� �����,
  BYTE TypeLine;
} COOR_IDENT;
typedef struct hKNOTT
{
	struct hKNOTT *next,*back,*up,*down;
  RECT Rect;//������./�����. ����� ���� ���� ������� ������.�����
  int InBegFrm,NumFrm;//������ �����.����� � ����� ����� ����
  int InColA;         //������ ������.�����(ParTabl.InfCell[InColA])
  //int InTerm;       //������ ��������.������(sym[InTerm][nstr][ncomp])
  //���� InTerm �.�. ��������� � ����� InBegFrm
  uint OrderChild:4,  //UNSORT,VER,HOR,MATR,TABL,FORMUL,TERM
       Type:4,        //TXT,TITLE,CELL,CELL_TITLE,CELL_CAPT,HIER_V,HIER_H
       AllowOCR:1,    //TRUE/FALSE - ������ �� ���� ���� �� ������-��� ��������
       JustH:2,       //�����.������������: ALG_BEG/ALG_END/ALG_CENTER
       JustV:2,       //����. ������������: --/--
       dummi:3;
  //� ������ AllowOCR=FALSE �.�. ������ �� ������ ������ ������� ����
  //��� ������ �.�. ������ ����. �������:
  //--������.�������--
  //1. InBegFrm - ������ ������ � �������. ������� �����
  //2. union {int InBegFrm,NumFrm; char *str;}
  //3. InBegFrm,NumFrm - ParTabl.CaptionV.TreeCapt[InBegFrm][NumFrm]
  //4. ������ ����� ���� char *str;
  //������ 3 ������������ ����, ���. �� ���� OCR-��, ���� ����. ������ => �� ���
  //������ 1 ��������, ���� �������� ����. �������. ������ ��� ����� => �� ���
  //����� �/��������� 2 � 4:
  //(2) �� ������ ���, ��� �����. ��������. ������� � ����� ���-���� ���� �����
  //����� ������ � ����������� ����, ���. �� ���� ��������
  char *Name;
  struct hKNOTT *RefOrt; //������ �� ���� ����� ���������. ��������
  struct hKNOTT *RefH;   //������������.������ �� V-�����
  //�������: ���� ���� ��� ��������.�����, �� �� ����� ���������� � down,
  //����� �����. ������ (? � ������ �� ���������� ���� str � ReferOrt?)
  //??� ����� �� ������ ������ �/���������.����������, �.�. InTerm - ���
  //������ ������������� ����.������ � ������ �.�. �� �����������
  //��� ���������� ������ � �������������� �� ���� ������������� �� �����.TREE
} KNOTT;
typedef struct hTREE2
{
	KNOTT *Root,*free; //������ � ������ ������ ������. ��������� ������
  int NumKnot;       //����� ����� ����� � �����. ������������
  int NumSeg;KNOT **ArrSeg; //���������. ������
} TREE2;
typedef struct hSEG_ARR
{
	KNOT3 *free; //������ ������ ������. ��������� ������
  int NumKnot;//����� ����� ����� � �����. ������������
  int NumSeg;KNOT **ArrSeg; //���������. ������
} SEG_ARR;
typedef struct hLINE_KNOT //�������� ����� ��� ����� ������
{
	int beg;       //��� V-Line ��� ����� ������� ������� �����
  int BegTxt;    //��������� ����-��
  BYTE Thick;    //�������
  BYTE TypeLine; //���
} LINE_KNOT;
typedef struct hKNOT_TMP {KNOTT *Knot; int in;} KNOT_TMP;

typedef struct hSTAT_CELL //���������� �� ������
{
	int dx,   //��������.������
      dyLow,//-/- ������ �����.
      dyUpp,//-/- ������ ������.
      dsym, //-/- ���������.��������
      dstr, //-/- ��������. ��������
      HeiStr;//������ ������ � ��������.����������
} STAT_CELL;
typedef struct hINDEX_SORT {int ind,value;} INDEX_SORT;

typedef struct hINF_TREE
{
	 int       TypeDoc; //�������: PLAIN - PlainText, ...
  TREE2     Tree;//������
  KNOTT     *Table,*HierV,*HierH;//��������� ���� ������
  KNOTT     **TermV;//[NumTV] - ��������. V-�����
  int       NumTV;
  STAT_CELL *StatCell;////[NumTV] - ����-�� �� ����. V-������
  PAR_TABL  ParTabl;
  PAR       *ParStr;
  LINE_KNOT *LineVK,*LineHK;//[nH],[nV]-��������� ������ ������������� � ���-��
  int       nH,nV;
  //++������� �������� �����
  int       InLineBotTabl;
  //++���-�� ����. �����
  KNOTT     **ColT;//[NumT] - ��������. ������
  int       NumT;
  //++�������� �����
  float     slope;
  int       DislocationX,DislocationY;//��������� ������
  int       MonoSpace,MonoSpaceTrue; //������� ������ � �����.���������
  int       SizeXGlob,SizeYGlob;
  int       NumFrm;
  //++�������� ��������.�����
  BOUND     bnd_page,*bnd_col,**bnd_str;
  FRAME     ***sym;
  int       k_colt,**k_sym;
  Int16  	*k_str;
  STAT_COL  *StatCol;
  POS_STR   **PosStr;
  char      FilePrc[255];//��� ����� ��������.���������
  SUB_ALLOC SubTree;
  FUN_POMP  pump;
  FUN_MESS  FunMessage;
} INF_TREE;

int FilterLineNorveg(STRET *LineV,short *NumLV,STRET *LineH,short *NumLH,
    RECT bnd,short Thick,RECT *BndTabl,short *TopCapt,short *BottomCapt);
int IdentApriorLineV(STRET *LineV,short *NumLV,STRET *LineH,short *NumLH,
 short Thick,RECT *BndTabl,PAR_TABL *ParTabl,short *DelCoor,COOR_IDENT *CoorId);
int DivFrmBox(FRAME **frm,int k_frm,RECT *box,int NumBox,int reg,int DelFrm,
    int *intr);
KNOTT* IncKnot(KNOTT *up,KNOTT *after,KNOTT **free);
void FillFieldKNOTT(KNOTT *ptr,int Left,int Right,int Top,int Bottom,
int InBegFrm,int NumFrm,int InColA,
uint OrderChild,uint Type,uint AllowOCR,uint JustH,uint JustV,char *Name);
int FindLineNumPage(STRET *LineH,short NumLH,FRAME **frm,int NumFrm,
    short TopCapt,RECT *RectTabl,int *Coor);
int CreateTree(BOUND BndTxt,RECT *RectAll,RECT *RectTabl,STRET *LineV,short NumLV,
    STRET *LineH,short NumLH,FRAME **frm,int NumFrm,short Thick,INF_TREE *Inf);
int compKNOTT_InColA(KNOTT **a,KNOTT **b);
int EstSizeKnott(FRAME **f,int NumKnot,KNOTT **Knot,int DYmin,int DYmax,
    int MinNum,int *DYest,int Reg);
int EstSizesCompCell(KNOTT **TermV,int NumCol,STAT_CELL *StatCell,FRAME **f);
int EstInterval(AS *As,int Upp,int Low,int *dstr,int *dsym,int MinNum);
int EstIntervalKnott(FRAME **f,int NumKnot,KNOTT **Knot,
    int MinNum,int Upp,int Low,int *dstr,int *dsym);
int CalcHistCell(int NumKnot,KNOTT **Knot,FRAME **frm,int Orient,int Pixel,
    int *MinCoor,int *MaxCoor,int **Hist,int *NumHist);
int DivColH(FRAME **f,KNOTT *Col,STAT_CELL *StatCell,int *NumIntr,int *intr,
    float k1,float k2,LINE_KNOT *LineHK,int Reg);
int compINDEX_SORT(INDEX_SORT *a,INDEX_SORT *b);
int compLINE_KNOT(LINE_KNOT *a,LINE_KNOT *b);
int SortHorLine(LINE_KNOT *LineHK,int NumH,LINE_KNOT *LineVK,int NumV,
    KNOTT *Root,KNOTT ***colt1,int *k_colt1,FRAME **frm,STAT_CELL *StatCell);
void DelTree(TREE2 *Tree);
void ClearStatCell(STAT_CELL *s);
int EstOneString(FRAME **frm,int k_frm,FRAME ****str1,int **ksym1,int *k_str1);
int PASC InitParTabl(char *File,PAR_TABL *ParTabl);
int PASC FreeParTabl(PAR_TABL *p);

//==Stack

typedef struct hSTACK
{
	KNOTT **arr;//[size] ������ ����������
  int pos;//������ �����.������.�������
  int size;//������
} STACK;
int NewStack(int size,STACK *St);
void DelStack(STACK *St);
int PushStack(KNOTT *ptr,STACK *St);
KNOTT *PopStack(STACK *St);
void ClearStack(STACK *St);
int OverflowStack(STACK *St);

/*int FilterPiecesLinesKnot(KNOTT *Knot,int flL,int flR,int flU,int flD,
    int ThickH,int ThickV,int ThickAbsH,int ThickAbsV,int ThickRel,
    FRAME **frm);*/
int FilterPiecesLinesKnot(KNOTT *Knot,int flL,int flR,int flU,int flD,
      int ThickH,int ThickV,int ThickAbsH,int ThickAbsV,int ThickRel,
      FRAME **fRm1,LINE_KNOT *LineH,LINE_KNOT *LineV,STAT_CELL *StatCell);
//LINE_KNOT *LineH,LINE_KNOT *LineV,STAT_CELL *StatCell);

//== TREE2-Utilites

KNOTT *NextKnot(KNOTT *Curr,STACK *St);

//*********�������� SubAllocator***********
int InitSubAlloc(long Size,SUB_ALLOC *Sub);
char *Submalloc(uint size,SUB_ALLOC *s);
void DeleteSubAlloc(SUB_ALLOC *s);
void ClearSubAlloc(SUB_ALLOC *s);

//*********Plain Text ����������� � ����� �������� ������ ���-��*********
int SearchInterval(FRAME **frm,int k_frm,int **beg1,int **end1,
    int *k_int1,BOUND *bnd,int ave_dir,int ave_ort,int reg,int *NumMax);
int SearchColHist(FRAME **frm,int k_frm,BOUND *bnd,int ave_x,int ave_y,int reg,
    int *k_int,int **intr1,int **begI,int **endI,int *NumMax);
int AddLine(LINE_KNOT **Line1,int *nCurr,int *nMax,int Coor,int Thres);
int CreateTreePlainTxt(BOUND BndTxt,STRET *LineV,short NumLV,STRET *LineH,
    short NumLH,FRAME **frm,int NumFrm,INF_TREE *Inf,int size_x,int size_y);

//== Serv. func

void ImageKnot(KNOTT *ptr,LINE_KNOT *LineVK,LINE_KNOT *LineHK,int col,
int line_style,int fill,int ColFrm,FRAME **f,int NumFrm,int NumVK,int NumHK);
void TestKNOTT(KNOTT *ptr,LINE_KNOT *LineVK,LINE_KNOT *LineHK,int NumFrm,int NumVK,int NumHK);
int ImageTree(KNOTT *Root,LINE_KNOT *LineVK,LINE_KNOT *LineHK,
  FRAME **f,int NumFrm,int NumVK,int NumHK);

#include "undef32.h"

#endif
