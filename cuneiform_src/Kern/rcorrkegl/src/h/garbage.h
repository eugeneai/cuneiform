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

/*----------------  ���� ��������� ��������������  -----------------*/

/* �������
  "�������" - �� ��������, ������������ �� ������� ��� ���������, ������ >=RELY_LET, 
  "��������������" - �� ��, �� ����� ���� ��������
*/

#define  RELY_LET  220       //������� ������� ������

Word8 stick_like[]={"/\\<>(){}[]!1����IiJjlrTtf"};   //"��������" �����

//��� �������� �������� ���������

#define  G_GOOD0  6           //���������� ����������� ����� �������
#define  G_GOOD1  2           //����������� ����� ������� ��� �������������� ��������
#define  G_HIGH_NOM    1      //���� �������� � ������� ������� ����� ������������ �� ��������
#define  G_HIGH_DENOM  2
#define  G_PUNCT      10      //���� ���������� ��� ����� ������� ��������� <=NBIG
#define  G_BIG         2

//

#define  SMALL_FRAG  20      //������ ���������� ��������� ������������ ��������

//condition1

#define  CON1_HIGH          3   //����������� ���������� � ������� �������
#define  CON1_HIGH_L_NOM    1   //���� � ������� ������� ����� ���� �������
#define  CON1_HIGH_L_DENOM  3   //
#define  CON1_HIGH_M_NOM    1   // �� �� � ������, ����� ��� ����������
#define  CON1_HIGH_M_DENOM  2   //
#define  CON1_PUNCT_NOM     2   //���� ����������
#define  CON1_PUNCT_DENOM   1   //

#define  CON1_LET_NOM       1   //���� ������������
#define  CON1_LET_DENOM     2   //
#define  CON1_PUNCT         5   //���� ���������� ��� ����� ������������ >=CON1_LET
#define  CON1_LET           3    

//condition3

#define  CON3_GOOD          1   //���������� ������� ���
#define  CON3_HIGH          4   //���������� � ������� ������� �
#define  CON3_HIGH_NOM      3   //�� ���� ����� ���� �������
#define  CON3_HIGH_DEHOM    4   //
#define  CON3_PUNCT         5   //���� ���������� , ����� ������� >CON3_BIG
#define  CON3_PUNCT_MIN     4   //���������� ����������
//#define  CON3_BIG           2   

//condition4

#define  CON4_GOOD          2   //���������� �������

//����� ��������

#define  PN_KEGL            4   //������ �� ����� 1/PN_KEGL
