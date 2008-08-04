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

//#include "Recdefs.h"
#include "linedefs.h"
//#include "LnsDefs.h"


#define CLINE_HorizantalLine   1
#define CLINE_VerticalLine     0

#define CLINE_HalfOtstup       4
#define CLINE_Otstup           8

#define CLINE_MaxVerticsNumber        4

typedef void* CLINE_handle;

typedef union
{
	struct {NR_PoinLine data;Int32 res[2];} point_line;
	struct {NR_DefiLine data;} defi_line;
} SPECLINE;

typedef struct SL_POLOY_struct
{
 Int16   count;
 Point16 Vertex[CLINE_MaxVerticsNumber];
} CLINE_SL_POLY;

typedef struct Interval_Data_struct
{
  Int32  Pos;
  Int32  Lent;
} DInterval;

typedef const DInterval* CPDInterval;

typedef struct Event_Data_struct
{
  Bool32          Hori;                    //�����.(1) ��� ������.(0)
  Bool32          Increase;                //���������� ��� ��������� �������
  Int32           Lev_0;                   //������� ������� ���������
  int             Width;
  Int32           EventLength;
} DEvent;

typedef const DEvent* CPDEvent;


#define DirectedUpwards       0  //defines for Direction
#define DirecteDownwards      1
#define DirectedForBothSides  2

typedef struct CutPoint_Data_struct
{
  Bool32           Direction;
  Int32            Level;                            //������� ������
  Word8            reserv;
} DCutPoint;

typedef const DCutPoint* CPDCutPoint;

#define  CLINE_InitialPointHasCrossPoint  1  //defines for Component
#define  CLINE_MiddleHasCrossPoint        2
#define  CLINE_EndPointHasCrossPoint      4

typedef struct Component_Data_struct
{
  Bool32    CrossPointFlag;
  Int32     BeginPoint;
  Int32     EndPoint;
} DComponent;

typedef const DComponent* CPDComponent;

typedef struct Lns_Data_struct
{
 Point16 Anew;
 Point16 Bnew;
} DLns;

typedef const DLns* CPDLns;

typedef struct Line_Data_struct
{
  Word32          Flags;                   // common use info
  Word32          Tail;                    // ������� ����� �� ��������
  Rect32          rect;                    // ������������� �����
  Bool32          ProcessingType;          // ��� ��������� �����(���. ��� ����.)
  Int32           LineEventsLength;        // ����� ������ ����� �����
  double          Degree;
  Handle           RelationshipIndex;       // ������ ������� ���������
  Bool32          FlagCalculatedWidth;
  Bool32          FlagExtensible;
  Bool32          FlagDot;                 // ��������������� ����� ����� ��������
  Bool32          FlagBad;
  Bool32          FlagLongStrip;

  NR_SimpLine     Line;                    // ���������� �������� �����
  Int32           Status;                  // ������� ����� � ���������
  NORM_DATATYPES  Type;                    // *Unknown, *Simple, *Defis, *Pointed
  LINE_DIR        Dir;
  char            Qual;                    // quality (or estimation) at percents
  char            Dens;                    // density at percents
  SPECLINE        Specline;                // (NR_DefiLine), (NR_PoinLine)
  CLINE_SL_POLY   poly;
  Int32           n_event;                 //����� �������
  DLns            lns_data;
} DLine;

typedef const DLine* CPDLine;

