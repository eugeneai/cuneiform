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
/*  ��������   :  01.03.01                                                    */
/*  ����       :  'UN_Err.H'                                                  */
/*  ���������� :  ���� ��������.                                              */
/*  ���������� :  ���������� ����������� �������.                             */
/*----------------------------------------------------------------------------*/
#define RV_FALSE       0   // FALSE  ��� ����� (����-�����)
#define RV_TRUE        1   // TRUE   ��� � �������
#define RV_EMPTY       2   // EMPTY  ��� � �������, �� ������� �� �������
#define RV_DOUBT       3   // DOUBT  �� ��� � �������, �� �� ����-�����
#define RV_POSITIVE    4   // TRUE   ��� � �������, ����� �������������
#define RV_NEGATIVE    5   // TRUE   ��� � �������, ����� �������������
#define RV_CONTINUE    6   // TRUE   ��� � �������, ���������� ��������
/*----------------------------------------------------------------------------*/
#define ER_ROUGH_NONE                0   // ��� � �������
#define ER_ROUGH_OTHER_LIBRARY       1   // ������ ������ ����������
#define ER_ROUGH_NOT_SUCH_ERROR_CODE 2   // ��� ������ ���� ������
#define ER_ROUGH_CALL_REFUSED        3   // ����� ������� ��������������
#define ER_ROUGH_NORMAL              4   // ��� ������            
/*----------------------------------------------------------------------------*/
#define ER_DETAIL_NONE               0   // ��� � �������
#define ER_DETAIL_WAS_YET_INIT       1   // ��� ���� �������������
#define ER_DETAIL_WAS_NOT_INIT       2   // ��� �� ���� �������������
#define ER_DETAIL_BAD_UNICAL_NUMBER  3   // ������ ���������� �����
#define ER_DETAIL_TOO_MUCH_CALLS     4   // ������� ����� �������
#define ER_DETAIL_NOT_MADE_SUCH_DATA 5   // �� ���������� ����� ������
#define ER_DETAIL_NO_COMMENT         6   // ��� ������������
#define ER_DETAIL_EMPTY_FUNC         7   // �������-��������
#define ER_DETAIL_MAKET_FUNC         8   // �������-����� (�������.����.������)
#define ER_DETAIL_BAD_PARAMETRS      9   // ������ ���������
#define ER_DETAIL_NO_MEMORY         10   // ��� ������
/*--------- ��������� ���� ���� �� ������ ������ -----------------------------*/
#define ER_DETAIL_FUNC_CPAGE        11   // ������ ������� �� 'CPAGE'
#define ER_DETAIL_FUNC_DPUMA        12   // ������ ������� �� 'DPUMA'
/*----------------------------------------------------------------------------*/
