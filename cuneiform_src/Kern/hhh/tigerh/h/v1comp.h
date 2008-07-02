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

//
//	������������������������������������������������������������������
//	��                                                              ��
//	��	Copyright (C) 1992 Cognitive Technology Corporation.    ��
//	��	All rights reserved. This program is proprietary and    ��
//	��      a trade secret of Cognitive Technology Corporation.     ��
//	��                                                              ��
//	������������������������������������������������������������������
//
//
//
//===========================================================================
//
//	Components extraction definition module
//
//===========================================================================
//
struct bw_segment
{
 INT b;
 INT w;
 BOX * box;
};

typedef struct bw_segment BWS;
//
//		Memory organisation
//
//		We reserve additional memory for
#define BOX_NUMBER	2048	// boxes, wich should allocate in
				// remaining memory (320 Kb now).
#define LINE_MAX_LTH	512	// maximal length of image string mesured
				// in bytes
#define SEG_MAX_NUM	1024	// maximal number of segments
//		Boxes and main numbers has dinamical structure organisation,
//	that means free elements are conected in the chains. For
//	this purpose are used fields mnfree and boxchain.
//
//		Main memory segment structure
//
//

struct main_memory_str
 {
//		Memory service
//
//		In _DSECT
BOX *boxalloc;	// box free chain start
MN  *mainalloc;	// main number free chain start
BWS *oldline;	// old line area
BWS *newline;	// new line area
//
PBYTE dcodeptr;	// current decoding line offset
PBYTE dcodeend;	// end of read line buffer ptr
//								lth=12
//		Line service
//
//WORD dotlength;		// number of dots in the line
//WORD bytelength;	// length of the line in bytes
WORD lineno;		// line counter
WORD reserv_v1comp;	// arround byte
//								lth=7
//
//		Big tables size counting and its allocation
//
//

//// MN mnstart[SEG_MAX_NUM];    // pool of main numbers
//// BWS line1start[SEG_MAX_NUM];    // line 1
//// BWS line2start[SEG_MAX_NUM];    // line 2
//   Big tables uses 36*SEG_MAX_NUM bytes (36 Kb now).
//// BYTE scan_buffer[0x4000+LINE_MAX_LTH];  // buffer for image reding

 MN  *mnstart; // [SEG_MAX_NUM];    // pool of main numbers
 BOX *boxstart;	   // box pool
 BWS *line1start; // [SEG_MAX_NUM];    // line 1
 BWS *line2start; //[SEG_MAX_NUM];    // line 2
//   Big tables uses 36*SEG_MAX_NUM bytes (36 Kb now).
 BYTE *scan_buffer; //[0x4000+LINE_MAX_LTH];  // buffer for image reading
};

