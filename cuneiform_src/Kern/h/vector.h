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


#ifndef PPS_MAC
#pragma message(__FILE__)
#endif
#ifndef VECTOR_H
#define VECTOR_H

struct tagChunk;  // forward definition

typedef struct bw_segmentv
{
 Int16 b;
 Int16 w;
 struct tagChunk * box;
 #define SEG_DELIM -0x7000
} BWSV;


typedef struct tagChunk {
BWSV *		 	first_int;      // If != NULL structure is in use
struct tagChunk * 	master;		// Master chunk (can be NULL)
struct tagChunk * 	dragon;		// Chunk who is ate this chunk
Int32			area;		// area in pixels
Int16			height,
			yline;		// y offset of chunk in letter box
Int16			nintervals;	// number of intervals
Word16			wide : 1,       // wide chunk
			v_deleted : 1;  // chunk was deleted
#define MAX_CHUNK	64
} Chunk;

typedef struct tagVector {
Point16 beg,end;
Int32 incline;   // 2048 * tangens
#define INCLINE_UNKNOWN	(-0x41414141)	  ///	      _______
Int32  len;  // -1 - It isn't vector;  metric Eucleede � x� + y�
Int32 Mx,My;
Int32 Cx,Cy;  // debug purposes
Int32 area;
Word8 Mn; // normalized moment
Word8 reserve[3];
#define MAX_VECT	64
#define NORMA_FACTOR	12
}  Vector;

typedef struct tagSegmVersion {
Word8 s;    // segment code
#define UNREC_SEG	100
Int16 prob; // probability
} SegmVersion;

typedef struct tagSegment {
#define MAX_VERS	3
#define MAX_SEG		48
SegmVersion sgm[MAX_VERS+1];
Vector * chunk;
} Segment;


typedef struct tagSegmRec {
Word16 segm;
Word16 let;
Word8 prob;
#define MAX_REC_SEG		14
} SegmRec;

#endif
