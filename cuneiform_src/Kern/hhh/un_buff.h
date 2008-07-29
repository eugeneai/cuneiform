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

/*------------------------------------------------------------------------------------------------*/
/**
    \file   UN_Buff.CPP
    \brief  �������� ������� ������ �� ������� ����������
    \author ��������� ��������
    \date   26.04.2005
*/
/*------------------------------------------------------------------------------------------------*/
/*  N-� �������� 26.04.2005:
    - ���������� � ��������� ����������, ������������� � ������ "UN_Buff.CPP" � 02.03.2001  */
/*------------------------------------------------------------------------------------------------*/
/**********  ���������  **********/
/*  �����      :  ��������� ��������                                          */
/*  ��������   :  03.02.01                                                    */
/*  ����       :  'UN_Buff.H'                                                 */
/*  ���������� :  ���������, ������� � ��������� ������� ������ � �������.    */
/*  ���������� :  ����������� ������ � �������.                               */
/*----------------------------------------------------------------------------*/
const int MAX_BUF_PART = 100; ///< ������������ ���������� ����������� ������ �� ������
typedef struct tagUN_BUFF
{
    /*  ���������� ���������� ������  */
    void     *vBuff; ///< ��� �� ������! ��������� �� ����� ���������� � ��������� ������
    int       SizeBuff; ///< ������ ������ ����������
    /*  ���� ��������� ����� ������  */
    void     *vCurr; ///< ��� �� ������! ��������� �� ��������� ������ � ������
    int       SizeCurr; ///< ������ ��������� ������
    /*  ��������������� ����� ������  */
    int       nPart; ///< ������� ������ ������ �������������
    void     *vPart[MAX_BUF_PART]; ///< ������ ������� ��������������� ������ ������
    char      TypePart[MAX_BUF_PART]; ///< ������ ����� �������������� ������
    char      AimPart[MAX_BUF_PART]; ///< ������ ����� �������������� ������
    int       SizePartUnits[MAX_BUF_PART]; ///< ������ �������� ������ � �������������� ������
    int       nPartUnits[MAX_BUF_PART]; ///< ������ ���������� ������ � �������������� ������
    int       SizePartTotal[MAX_BUF_PART]; ///< ������ �������� �������������� ������
}UN_BUFF;
/*------------------------------------------------------------------------------------------------*/
/**
    \brief ������� �������� ��������� ���������� ����� �� ������
    \param p_vB [in/out] - ��������� �� ����� ���������� (� ��������� ������)
*/
void CleanLastDataPart (void *p_vB);
/**
    \brief ������� �������� ��������� ���������� ����� �� ������
    \param p_vB [in/out] - ��������� �� ����� ���������� (� ��������� ������)
*/
void EndLastDataPart (void *p_vB, const char Aim, const char Type, const int SizeU, const int nU);
/**
    \brief ������� ���������� ��������� ������ ������ �� ������
    \param p_vB [in]  - ��������� �� ����� ���������� (� ��������� ������)
    \param Aim [in]   - �������������� ��������� ���������� ������
    \param Type [in]  - ��� ��������� ���������� ������
    \param SizeU [in] - �������� ������ � ��������� ���������� ������
    \param nU [in]    - �������� ������ � ��������� ���������� ������
*/
int  FindSuchData (const void *p_vB, const int WhatData);
/**
    \brief ������� ���������� �� ������ ������ ���������� ���� � ���������� �������� ����������
    \param p_vB [in]     - ��������� �� ����� ���������� (� ��������� ������)
    \param WhatData [in] - ��� ������, ������� ���� ����� �� ������
    \param WhatAim [in]  - �������������� ������, ������� ���� ����� �� ������
*/
int  FindSuchAimedData (const void *p_vB, const int WhatData, const int WhatAim);
/**
    \brief ������� ���������� �� ������ ��������� ������ ������ ���������� ����
    \param p_vB [in]     - ��������� �� ����� ���������� (� ��������� ������)
    \param WhatData [in] - ��� ������, ������� ���� ����� �� ������
    \param IndPrev [in]  - ������ ��������� ��������� ������ ���������� ����
*/
int  FindNextSuchData (const void *p_vB, const int WhatData, const int IndPrev);
/*------------------------------------------------------------------------------------------------*/
