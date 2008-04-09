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

#include <stdio.h>
#include <string.h>

#define el(i) (base+i)
#define cmp(a,b) comp_func(base+a,b)
#define swap(a,b) { memcpy(swbuf,base+a,siz); memcpy (base+a, base+b,siz); memcpy(base+b,swbuf,siz);}
#define mov(a,b) memcpy (a,b,siz);

void    q_sort( char *base, size_t N, size_t siz,
		        int (*comp_func)( const void *, const void * ) )

{
 char swbuf[256];
 size_t NN;
 size_t root;
 char reg;
 size_t left,right,curr;

  if (N <= 2)
  { if (N <= 1)return;
    if (cmp(0,base+siz) > 0) swap(0,siz);
    return;
  }
  base -= siz;	NN = N * siz;

  reg = 0;
  root = N/2; root*=siz; while (root)
  { mov (swbuf,el(root)); goto piramida; ret_1: root-=siz;}

  reg = 1; root = siz;
  while (N > 2)
   { mov (swbuf,el(NN)); mov (el(NN),el(siz)); N--; NN -=siz; goto piramida; ret_2:; }
  swap(siz, siz+siz); return;

piramida: curr = root;

p_iter:
	left = curr+curr; if (left > NN) goto RET;
	right = left+siz;
	if (cmp(left,swbuf) > 0)
	 {
	  if ((right <= NN) && (cmp(right,el(left)) > 0))
	   { mov (el(curr),el(right)); curr = right; goto p_iter; }
	  mov (el(curr), el(left)); curr = left; goto p_iter;
	 }
	if ((right <= NN) && (cmp(right,swbuf) > 0))
	 {  mov (el(curr),el(right)); curr = right; goto p_iter; }
RET:
	mov (el(curr),swbuf);
	if (reg) goto ret_2; else goto ret_1;
}

