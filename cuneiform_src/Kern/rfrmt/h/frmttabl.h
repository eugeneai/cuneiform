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

// ============================================================================
// Written by Shahverdiev  Alik
// This file cration date: 24.02.99
//
// FrmtTabl.h 
//
// ============================================================================
#ifndef __frmttabl_h__
#define __frmttabl_h__

#define  DefFontSize          24
#define  TablTrgaph           108 
#define  TablMinKeglSize      12

#define  NOBOLD               0x0004           
#define  NOCURSIV             0x0008           
#define  NOSIZE               0x0020           
 

//       wFont bits 
#define  TG_EDW_SERIF         1
#define  TG_EDW_GELV          2      //��� �����.
#define  TG_EDW_BOLD          4
#define  TG_EDW_ITALIC        16
#define  TG_EDW_UNDERLINE     64
#define  TG_EDW_NARROW        128     // user defined

extern   float      Twips;
extern   Word32     FlagMode; 
extern   CHAR       lpMyNameSerif[MAX_PATH];
extern   CHAR       lpMyNameNonSerif[MAX_PATH];
extern   CHAR       lpMyNameMono[MAX_PATH];
extern   Int16      get_font_name(Int16 FontNumber);

#ifdef __cplusplus
	extern "C" {
#endif

Word32 GetTablCount(void);
void   ViewTable(void);
void   GetTableRect( Word32 NumberTable , Rect16* RectTable,Word32* UserNumber );
BOOL   WriteTable( Word32 IndexTable, RtfSectorInfo* SectorInfo/*, CString* TableString*/ ,BOOL OutPutMode );
//void   TablePutChar( CString* TableString, BYTE sym );

#ifdef __cplusplus
	}
#endif

class CTableRow;
class CTablePhCell;
class CTableString;
class CTableWord;
class CTableChar;

void  GetFragmLines( Int32 m_NumberFragm , Point32* m_point );
BOOL  CheckLine( CSTR_line* Comingline );
void  AddLetter( CSTR_rast* rast , Word8*  m_ucCode , Word8* m_ucFontNumber );
void  Write_SetPhCellParam( Handle h_Page, Handle h_Table, CTableRow* rTableRow, Point32 m_TempPhPoint,
																										 Int32 CountStrCellInPn, Int32 FlagPhisicalGroup , Int32 NumberPhysicalGroup );
/////////////////////////////////////////////////////////////////////////////
//����� ��� �������
class CMyTable //: public CObject
{
public:
  CMyTable();
 ~CMyTable();

  CTableRow*    GetCurrentTableRow( void );   
  void          Write(/*CString* TableString,*/RtfSectorInfo* SectorInfo,BOOL OutPutMode);

  Rect32        RectTable;
  std::vector<CTableRow*>/*CObArray*/	    m_arTableRows;
  WORD          m_wIndex;  
  Int32         m_CountRows;  
  Int32         m_CountColumns;
};

/////////////////////////////////////////////////////////////////////////////
//����� ��� ������ �������
class CTableRow// : public CObject
{
public:
  CTableRow();
 ~CTableRow();

  CTablePhCell* GetCurrentPhCell( void );
  void	        Write(/*CString* TableString,*/RtfSectorInfo* SectorInfo);

  std::vector<CTablePhCell*>/*CObArray*/	    m_arPhCells;
  WORD		    m_wHeight;
  WORD          m_wPosX;
  WORD          m_wPosY;
  WORD          m_wIndex;  
  WORD          m_wCountPhCells;
  Handle        m_hEdTableRow; 
};

/////////////////////////////////////////////////////////////////////////////
//����� ��� ������ �������
class CTablePhCell// : public CObject
{
public:
  CTablePhCell();
 ~CTablePhCell();
  
  CTableString* GetCurrentString( void );
  void          SetPhCellParam(Bool32 FlagTerminalPhCell, Int32   NumberPhysicalGroup , 
  Bool32        FlagPhisicalGroup , Point32 m_TempPhPoint      );
  void          FillPhCell(Int32 m_FragmentNumber);
  void          Write_Header(/*CString* TableString,*/ RtfSectorInfo* SectorInfo);
  void          Write(/*CString* TableString,*/ RtfSectorInfo* SectorInfo);
  void          SetPhCellFragmentFormattingAndAlignment(); 
  void          SetPhCellFlag( void );

  std::vector<CTableString*>/*CObArray*/	    m_arStrings;
  std::vector <RECT> RectFragmentInPhCell;

  Rect32        RectPhCell;//����� �������� ���������� �������������� - ������ ������ (������� � ��������)
  Rect32        RectTable;
  Point32       m_PhCellPoint;

  WORD	        m_wIndex;
  Bool32	    m_FlagTerminalPhCell;
  Bool32        m_FlagPhisicalGroup;
  Int32         m_NumberPhysicalGroup;  
  Int32         m_FragmentNumber;
  Int32         m_LeftIndent;
  WORD     	    m_wCountStrings;
  Bool32        m_PhCellFragmentFormatting;       //Hor. formatting
  Bool32        m_PhCellFragmentAlignment;        //Ver. formatting
  Handle        m_hEdTableCell; 
  DWORD         m_Flags;
  
  union
  {
	Word8		m_u8BoundsType[4];//���������� � ���� ������ ������:L,R,T,B !!!Art
	Word32		m_u32BoundsType;
  };
};

/////////////////////////////////////////////////////////////////////////////
// ����� ��� ������ ������ �������
class CTableString//: public CObject
{
public:
  CTableString();
 ~CTableString();

  CTableWord*   GetCurrentWord( void );
  void  	    ExtractWordsFromString( CSTR_line line );
  void          ExtractNextWord( CSTR_line* line );
  void	        Write(/*CString* TableString,*/ RtfSectorInfo* SectorInfo);  
  void          MyCorrectKegl( Int16 width ); 
  Int16         GetRealSizeForKegl( char* str,Int16 FontSize,Int16 FontNumber );

  /*CObArray*/std::vector<CTableWord*>      m_arWords;

  WORD	        m_wIndex;    
  WORD          m_wCountWords;
  DWORD         m_Flags;
};

/////////////////////////////////////////////////////////////////////////////
// CTableWord class
class CTableWord//: public CObject
{
public:
  CTableWord();
 ~CTableWord();
  
  CTableChar*   GetCurrentChar(void);
  void          AddLetter2Word( CSTR_rast* rast ); 
  void          SetWordRectAndProb( CSTR_rast* rast );
  void	        Write(/*CString* TableString,*/ RtfSectorInfo* SectorInfo);
  void          WriteWordForCorrectKegl(char* TmpTableString);

  std::vector<CTableChar*>/*CObArray*/      m_arChars;
  RECT	        m_rectWord;

  WORD	        m_wCountChars;
  WORD	        m_wIndex;
  WORD	        m_wEDIndex;
  WORD	        m_wFontNumber;
  WORD	        m_wFontPointSize;
  WORD          m_wUnderline;
  WORD          m_wBold;
  WORD          m_wItalic; 
  WORD          m_wProb;
  BYTE          m_bSpell; 
  DWORD         m_Flags;
};

/////////////////////////////////////////////////////////////////////////////
// CTableChar class
class CTableChar//: public CObject
{
public:
  CTableChar();
 ~CTableChar();

  void          AddingLetter( CSTR_rast* rast ,int index );  
  BOOL	        Write();

  RECT	        m_rectChar;
  struct
  {
  BYTE	        m_bChar;
  BYTE	        m_bProbability;
  } m_chrVersions[REC_MAX_VERS];//!!! Art
  BYTE          m_blanguage;
  BYTE          m_bFlg_spell;
  WORD          m_wCountAlt; 
  WORD          m_wFontNumber; 
  WORD	        m_wIndex;
  DWORD         m_Flags;
 };

#endif

