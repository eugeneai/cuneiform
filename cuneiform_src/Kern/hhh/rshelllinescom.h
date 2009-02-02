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

// RShellLinesCom.h: interface for the ShellLine's functions.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//
//	Description: ShellLine's functions and classes definition
//
//	Implemented: by B.M. Shahverdiev
//
//
#include "globus.h"

#ifdef __RSHELLLINES_EXPORTS__
  #define RSHELLLINES_FUNC  FUN_EXPO
#else
  #define RSHELLLINES_FUNC  FUN_IMPO
#endif


#define VerticalLine     0
#define HorizantalLine   1

#define HalfOtstup       4
#define Otstup           4
#define MaxNumber        4

#define MIN_H_NO_CLEAN  10

#include "cline.h"

#include "cpage.h"

#include "compat_defs.h"
//#include "decl.h"

//#define SecondPath       2
//#define ThirdPath        3

/*
struct CLineImage
{
	int Wide;
	int Height;
	int bytewide;
	Word8* lp;
	int fl_delete;
	Word8* pmasp;
	int size_mas;
	CLineImage();
	~CLineImage();
	int SetDibPtr(Word8* lpDibData,int wide,int heght,int bwide);
	Word8* GetPmasp(Rect32* pRc);
};
*/
struct DOT_STRUCT
 {
  Int32 left;
  Int32 right;
  Int32 top;
  Int32 bottom;
  Int32 i_left;
  Int32 i_top;
  Int32 i_right;
  BOOL  flag;
 };
/*
class  CSL_POLY:public CObject
{
public:
  CSL_POLY(){count=4;}
 ~CSL_POLY(){}

 Int16   count;
 Point32 Vertex[MaxNumber];
};
*/
//extern "C" {

typedef struct group_lines_mass
{
    CLINE_handle* hLinesMass;
    int           numder_of_lines;
    int           number_of_cp;
    Int32*        m_arCutPointsL;
    Int32*        m_arCutPointsR;
    Int32*        m_arFrequency;
    Int32         m_top;
    Int32         m_bottom;
    Int32         GroupOffset;
    Int32         GroupVerOffset;
} GLM;

/////////////////////////////////////////////////////////////////////////////
// Interval's class
/*class RSHELLLINES_CLASS CInterval:public CObject
{
public:
  CInterval(){}
 ~CInterval(){}

  Int32  Pos;
  Int32  Lent;
};
*/
/////////////////////////////////////////////////////////////////////////////
// Rect32's class
/*class RSHELLLINES_CLASS CPRect32:public CObject
{
public:
  CPRect32(){m_flag=TRUE;};
 ~CPRect32(){};

  Rect32  rect;
  BOOL    m_flag;
};
*/

/////////////////////////////////////////////////////////////////////////////
// Event's class
/*class RSHELLLINES_CLASS CEvent:public CObject
{
public:
  CEvent();
 ~CEvent();

  Bool            Hori;                    //�����.(1) ��� ������.(0)
  Bool            Increase;                //���������� ��� ��������� �������
  Int32           Lev_0;                   //������� ������� ���������
  int             Width;
  Int32           EventLength;

  CObArray        m_arIntervals;

  int             GetCountIntervals(void);
  CInterval*      GetInterval(int i);
  CInterval*      GetNewInterval(void);
*/
  void            SetEventWidth(CLINE_handle hEvent, DEvent* pEvent, Word32* LineHist, Word32 RectBegin, Word32 LineLength); //
/*};
*/
/////////////////////////////////////////////////////////////////////////////
// Stripe's class
/*class RSHELLLINES_API CStripe:public CObject
{
public:
  CStripe();
 ~CStripe();

  Int32           Level;                   //������� ������

  CObArray        m_arIntervals;

  int             GetCountIntervals(void);
  CInterval*      GetInterval(int i);
  CInterval*      GetNewInterval(void);
};
*/
/////////////////////////////////////////////////////////////////////////////
// CutPoint's class

//#define DirectedUpwards       0  //defines for Direction
//#define DirecteDownwards      1
//#define DirectedForBothSides  2
/*
class RSHELLLINES_CLASS CCutPoint:public CObject
{
public:
  CCutPoint();
 ~CCutPoint();

  int    Direction;
  Int32  Level;                            //������� ������

  CObArray        m_arIntervals;

  int             GetCountIntervals(void);
  CInterval*      GetInterval(int i);
  CInterval*      GetNewInterval(void);
};
*/
/////////////////////////////////////////////////////////////////////////////
// Component's class

#define  InitialPointHasCrossPoint  1  //defines for Component
#define  MiddleHasCrossPoint        2
#define  EndPointHasCrossPoint      4
/*
class RSHELLLINES_API CComponent:public CObject
{
public:
  CComponent();
 ~CComponent();

  int    CrossPointFlag;
  Int32  BeginPoint;
  Int32  EndPoint;
};
*/
/////////////////////////////////////////////////////////////////////////////
// �DotLines's class
/*class RSHELLLINES_API CDotLine:public CObject
{
public:
  CDotLine();
 ~CDotLine();

  CPRect32        m_LeftDot;       // ����� �����
  CPRect32        m_RightDot;      // ������ �����
  BOOL            m_LeftDotState;  //FALSE-����� �� ����� ���. ������������
  BOOL            m_RightDotState; //FALSE-����� �� ����� ����.������������

  CObArray        m_arDots;        // ��� ����� ��� ����������
  CWordArray      m_dist;          // ��� ���������� ����� �������

  BOOL            m_Flag;          //���� == FALSE �� ������ �������� �����

  int             GetCountOfDots(void);
  CPRect32*       GetDot(int i);
  void            AddDot(CPRect32*);
  void            SetLeftDot(CPRect32* in_dot);
  void            SetRightDot(CPRect32* in_dot);
};
*/
// For Flags
//#define LI_IsTrue       0x00000040 			// ��������� ���������� �����
//#define LI_IsFalse      0x00000080			// �� �����
//#define LI_Pointed      0x00001000          // ��������

// For Status
#define ST_Unknown      0x00000000 			//
#define ST_Basil_Short  0x00000001			//
#define ST_Good         0x00000002          //
#define ST_Bad          0x00000004          //

/////////////////////////////////////////////////////////////////////////////
// Line's class
//class CPageLines;
/*
class RSHELLLINES_API CLine:public CObject
{
public:
  CLine();
 ~CLine();
*/
RSHELLLINES_FUNC(void)            InitLine(DLine* linedata);  //
/*  Word32          Flags;                   // common use info
  Word32          Tail;                    // ������� ����� �� ��������
  Point32         BeginPoint;
  Point32         EndPoint;
  Rect32          rect;                    // ������������� �����
  BOOL            ProcessingType;          // ��� ��������� �����(���. ��� ����.)
  int             Width;
  Int32           LineEventsLength;        // ����� ������ ����� �����
  double          Degree;
  int             RelationshipIndex;       // ������ ������� ���������
  BOOL            FlagCalculatedWidth;
  BOOL            FlagExtensible;
  BOOL            FlagDot;                 // ��������������� ����� ����� ��������
  BOOL            FlagBad;
  BOOL            FlagLongStrip;
  int             PathNumber;              // ����� �������

  NR_SimpLine     Line;                    // ���������� �������� �����
  NR_SimpLine     LineMid;                 // ������� ����� �����
  Int32           Status;                  // ������� ����� � ���������
  NORM_DATATYPES  Type;                    // *Unknown, *Simple, *Defis, *Pointed
  LINE_DIR        Dir;
  char            Qual;                    // quality (or estimation) at percents
  char            Dens;                    // density at percents
  void            *Specline;               // (NR_DefiLine), (NR_PoinLine)
  CSL_POLY        poly;

  CObArray        m_arStripes;             // ��� ������ � ���������
  CObArray        m_arStripesVerticalLine; // ��� ������ � ��������� ��� ������������ �����
//  CObArray        m_arCorrectedStripes;    // ������ � ��������� ����� ���������
  CObArray        m_arEvents;              // ���������
  CObArray        m_arCutPoints;           // ����� ����������� � �������������� �������
  CObArray        m_arComponents;          // ���������� ����� � ���������� ����� �����������
//take'em away!  CWordArray      m_arSeparationPoints;    // ����� ������� ����� �� ��������(����������)
  CWordArray      m_arFriendsIndex;        // ������� ������������� �����

*/
  BOOL            SetLineNormDataTypes(NORM_DATATYPES, DLine* line); //
/*  NORM_DATATYPES  GetLineNormDataTypes(void);

  int             GetCountStripes(void);
  CStripe*        GetStripe(int i);
  CStripe*        GetNewStripe();

  int             GetCountStripesVerticalLine(void);
  CStripe*        GetStripeVerticalLine(int i);
*/  void            GetNewStripeVerticalLine(DEvent* eventdata); //

/*  int             GetCountEvents(void);
  CEvent*         GetNewEvent();
  CEvent*         GetEvent(int i);

//  int             GetCountCorrectedStripes(void);
//  CStripe*        GetNewCorrectedStripe();
//  CStripe*        GetCorrectedStripe(int i);

  int             GetCountCutPoints(void);
  CCutPoint*      GetNewCutPoint();
  CCutPoint*      GetCutPoint(int i);

  int             GetCountComponents(void);
  CComponent*     GetNewComponent();
  CComponent*     GetComponent(int i);
*/
  void            SetLineProcessingType(DLine* linedata); //
  void            SetWidth(CLINE_handle line, DLine* pCLine); //
  void            SetLength(CLINE_handle line, DLine* pCLine); //
  void            SetComponentsCrossPointFlag(CLINE_handle line, DLine* pCLine); //

RSHELLLINES_FUNC(Bool32)          CheckSeparationPoints(CLINE_handle hLine, CLINE_handle hComp = NULL); //

  void            SetSeparationPoints(CLINE_handle hContainer, CLINE_handle hLine, DLine* pCLine, Bool32 PLines); //
  void            SetCutPoints(CLINE_handle line, DLine* pCLine); //
  void            SetNewLine(CLINE_handle hContainer, CPDLine pCLine, Int32 IntervalBeg, Int32 IntervalEnd, CLINE_handle hLineOld, Bool32 PossibleSymbolAboveLine); //
  void            SetDegree(DLine* line); //
  BOOL            CheckPoint(CLINE_handle line, int CurPoint); //
//  void            CheckShortVerticalLines(CPageLines* PLines);
  void            ConvertStructs(CLINE_handle line, DLine* pCLine, Int32 nIncline); //
  void            FindTailComponent(CLINE_handle line, DLine* pCLine); //
  void            GetCorrectLine_End_X(CLINE_handle line, DLine* pCLine); //
  void            GetComponentBeg_Y_End_Y(Int32 Beg, Int32 End, Int32* Beg_X, Int32* End_X, Int32* Beg_Y, Int32* End_Y, CLINE_handle hLine, Bool32 ProcessingType); //
  Bool32          IfExistCutLine(CLINE_handle hContainer, DLine* pCLine, int left,int right); //
/*  int             SetVStripeMasMaxSize(int size);
};
*/
/////////////////////////////////////////////////////////////////////////////
// CGroupOfFriendLines class
/*class RSHELLLINES_CLASS CGroupOfFriendLines:public CObject
{
public:
  CGroupOfFriendLines();
 ~CGroupOfFriendLines();

  CWordArray      m_arFriendsIndex;        // ������� ������������� ����� (m_arLines)
  CWordArray      m_arCutPointsL;           // ����� ����������� (left for interval)
  CWordArray      m_arCutPointsR;           // ����� ����������� (right for interval)
  CWordArray      m_arFrequency;           // � �������

  double          Degree;                  // +- 0.05
  BOOL            ProcessingType;          // ��� ��������� �����(���. ��� ����.)
  int             RelationshipIndex;       // ������ ������� ���������
  WORD            m_top;
  WORD            m_bottom;

  int             GetCountOfFriendLines(void);
};
*/
/////////////////////////////////////////////////////////////////////////////
// CGroupOfExtensibleLines class
/*class RSHELLLINES_CLASS CGroupOfExtensibleLines:public CObject
{
public:
  CGroupOfExtensibleLines();
 ~CGroupOfExtensibleLines();

  double          Degree;                  // +- 0.05
  BOOL            ProcessingType;          // ��� ��������� �����(���. ��� ����.)
  CWordArray      m_arFriendsIndex;        // ������� ������������� ����� (m_arLines)

  int             GetCountOfExtensibleLines(void);
};
*/
/////////////////////////////////////////////////////////////////////////////
// PageLine's class
/*class RSHELLLINES_CLASS CPageLines:public CObject
{
public:
  CPageLines();
 ~CPageLines();

  BOOL                     FlagDot;  //���� == TRUE �� ����������� �������� �����

  CObArray                 m_arLines;
  CObArray                 m_arNewDotLines;  // �������� ����� ��������� �� ������� ���������
  CObArray                 m_arGroupOfFriendLines;
  CObArray                 m_arGroupOfExtensibleLines;
  CObArray                 m_arComps;
  CObArray                 m_arDotComps;
  CLineImage*              m_pImage;

  int                      GetCountLines(void);
  CLine*                   GetNewLine(void);
  CLine*                   GetLine(int i);

  int                      GetCountNewDotLines(void);
  CDotLine*                GetNewDotLine(void);
  CDotLine*                GetDotLine(int i);
  void                     DrowRectForChains(void);

  int                      GetCountGroupOfFriendLines(void);
  CGroupOfFriendLines*     GetNewGroupOfFriendLines(void);
  CGroupOfFriendLines*     GetGroupOfFriendLines(int i);

  int                      GetCountGroupOfExtensibleLines(void);
  CGroupOfExtensibleLines* GetNewGroupOfExtensibleLines(void);
  CGroupOfExtensibleLines* GetGroupOfExtensibleLines(int i);

  int                      GetCountComps(void);
  CSL_POLY*                GetNewComp(void);
  CSL_POLY*                GetComp(int i);

  int                      GetCountDotComps(void);
  CPRect32*                GetNewDotComp(void);
  CPRect32*                GetDotComp(int i);
  void                     DrowRectForDotComp(void);
*/
  BOOL                     IsItNewLine(CLINE_handle hContainer, DLine* pLineCP, Int32 GroupVerOffset, Bool32 IfDrawResult); //
  BOOL                     CheckLinesForExtensible(CLINE_handle hLine, GLM* hGroupEx); //
  BOOL                     CheckLinesImpositionForExtensible(CLINE_handle hLine, GLM* hGroupEx); //
  BOOL                     CheckLinesDegreeForExtensible(CLINE_handle hLine, GLM* hGroupEx); //
//  BOOL                     CheckGroupsForExtensible(void);

RSHELLLINES_FUNC(void)       FindFriendLines(CLINE_handle hContainer, GLM* friendlinesmass); //
RSHELLLINES_FUNC(void)       DrawFriendLines(CLINE_handle hContainer, GLM* friendlinesmass); //

RSHELLLINES_FUNC(void)       FindGroupOfExtensibleLines(CLINE_handle hContainer, GLM* friendlinesmass, Bool32 IfDrawResult); //
  void                     DrawGroupOfExtensibleLines(CLINE_handle hContainer, GLM* hGroup, int CountLines); //

RSHELLLINES_FUNC(void)       FindLosedVerticalLines(CLINE_handle hContainer, GLM* friendlinesmass, CLINE_handle hFictContainer, int CountLines, Bool32 IfDrawResult); //
RSHELLLINES_FUNC(void)       DrawLosedVerticalLines(GLM* friendlinesmass, int CountLines); //

//  void                     GetBigComps(Handle hCComp);
RSHELLLINES_FUNC(void)       DrawBigComps(CLINE_handle hContainer); //

RSHELLLINES_FUNC(void)       FindDotLines(Handle hCCOM,Handle hCPAGE, CLINE_handle hContainer); //
  BOOL                     GetDotComps(Handle hCCOM,Handle hCPAGE, HANDLE &hbuf,LPSTR &pDotBuffer, Int32 *CountDotComps); //
  void                     FindChains(Handle hCCOM, LPSTR &pDotBuffer, Int32 CountDotComps, CLINE_handle hContainer); //
  void                     CheckChains(Handle hCCOM, LPSTR &pDotBuffer, Int32 BegIndex,Int32 CountDots, CLINE_handle hContainer); //
  void                     AddNewDotLines(Handle hCCOM, LPSTR &pDotBuffer, Int32 CountDots, CLINE_handle hContainer); //
  void                     UnionBreakup(CLINE_handle hContainer); //

RSHELLLINES_FUNC(void)       SetLinesAndCompsRelationship(CLINE_handle hContainer, CLINE_handle hFictContainer); //

RSHELLLINES_FUNC(void)       DrowAllLines(CLINE_handle hContainer, Handle hDrowAllLines); //
/*  int                      SetImage(Handle hCPage);
};
*/
RSHELLLINES_FUNC(Bool32) FindLineFrag(CLINE_handle processedline, Bool32 OnlyPosyAndStat, Bool32 Is2ndPath, CLINE_handle hContainer, Bool32 IfNeedFragment = TRUE, Bool32 IfStraightFrag = FALSE); //
RSHELLLINES_FUNC(Bool32) FindLineAttr(CLINE_handle line, DLine* pCLine, Bool32 AbleSeeOldAttr); //
RSHELLLINES_FUNC(Bool32) GetNextPartOfLine(CLINE_handle hContainer, CLINE_handle hLine/*, CPDLine oldlinedata*/); //

void                       AddLine2Group(GLM* hGroup, CLINE_handle hLine);
RSHELLLINES_FUNC(void)      DeleteGroup(GLM* hGroup, int CountLines);
RSHELLLINES_FUNC(void)      DrawFragsForAllLines(CLINE_handle hContainer, Handle hDebugDrawAllLineFragments);
RSHELLLINES_FUNC(Int32)     CountBlackRaster(CPDLine pLine, CPDLine pLineExt, Bool32 IsHor, Int32 delta, Handle hDrawRaster);
RSHELLLINES_FUNC(Bool32)    SetExtLines(CLINE_handle hExtContainer, CLINE_handle hContainer, CLINE_handle* hLinesMass, Int32 CountLines);
RSHELLLINES_FUNC(Bool32)    RSL_CorrectDoubleLines(CLINE_handle hLine1, CLINE_handle hLine2);
RSHELLLINES_FUNC(Bool32)    RSL_SplitLine(CLINE_handle hLine, CLINE_handle hContainer);

//possible return values for RSL_VerifyShortLine
#define RSL_IS_LINE 0
#define RSL_BIG_ANGLE_DIFF 1
#define RSL_NO_COMP_FOUND 2
#define RSL_BAD_RASTER_FORM 3
#define RSL_BAD_LINE_PARAMS 4

#define MAX_CROSS_POINTS 4

RSHELLLINES_FUNC(Int32)    RSL_VerifyShortLine(CPDLine pLine, Handle hCCOM, PAGEINFO* page_info, Word8 lang, Word8 debug_flags, Int32 *cross_point = NULL);
RSHELLLINES_FUNC(Bool)  SL_GetRaster(Rect32* rect, Word8** ppData, PAGEINFO* page_info/*, CIMAGEBITMAPINFOHEADER* image_info*/); //


//}
