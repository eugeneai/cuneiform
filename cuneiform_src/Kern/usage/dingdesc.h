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

/**********  ���������  **********/
/*  �����      :  ��������� ��������                                          */
/*  ��������   :  05.11.99                                                    */
/*  ����       :  'DingDesc.H'                                                */
/*  ���������� :  ��������� � ������� ������������.                           */
/*  ���������� :  �������� ������� (��� ���������� ����������) ����� ������.  */
/*----------------------------------------------------------------------------*/
#ifndef __DINGDESC_H
#define __DINGDESC_H

#define   MaxMyDings      600//310
typedef struct tagRLT_DING
{
	int       Beg;
	int       End;
	int       Beg_Big;
	int       End_Big;
	int       Level;
	int       Width;
#define    RLT_DT_Unknown      0x00
#define    RLT_DT_Line         0x01
#define    RLT_DT_Ssel         0x02
#define    RLT_DT_Ukaz         0x04
#define    RLT_DT_Pointed      0x08
#define    RLT_DT_Refused      0x10
#define    RLT_DT_Doubt        0x20
	//�� ��������� ���� ����������� ��� �������� ������������� ������������
	char      Type;
}RLT_DING;
typedef struct tagRLT_DINGPOOL
{
	int       Skew;
	int       nHori;
	RLT_DING  Hori[MaxMyDings];
	int       nVert;
	RLT_DING  Vert[MaxMyDings];
#define    RLT_DS_Unknown      0x00
#define    RLT_DS_Normal       0x01
#define    RLT_DS_Delete       0x02
#define    RLT_DS_WasChanged   0x04
#define    RLT_DS_MadeOnBase   0x08
#define    RLT_DS_Created      0x10
	char      HoriStat[MaxMyDings];
	char      VertStat[MaxMyDings];
}RLT_DINGPOOL;

#endif   // __DINGDESC_H 
/*----------------------------------------------------------------------------*/
