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

static Word8 start_pos[]={
		8,
		7,
		6,6, 					/* 2 dup (6) */
		5,5,5,5, 				/* 4 dup (5) */
		4,4,4,4,4,4,4,4, 			/* 8 dup (4) */
		3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3, 	/* 16 dup (3)*/
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 	/* 32 dup (2)*/
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 	/* 64 dup (1)*/
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 	/* 128 dup (0)*/
		};
static Word8 last_pos[]={
		8,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		4,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		5,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		4,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		6,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		4,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		5,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		4,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		7,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		4,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		5,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		4,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		6,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		4,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		5,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		4,		0,1,0,
		2,		0,1,0,
		3,		0,1,0,
		2,		0,1,0,
		7 
        };
