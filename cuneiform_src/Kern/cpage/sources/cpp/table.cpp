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

/*#include <windows.h>*/

#define __CPAGE__

#include "globus.h"
#include "cpage.h"
#include "backup.h"
#include "polyblock.h"
#include "resource.h"

// ���������� �������������� �� TYPE_DESC � CPAGE_TABLE
Word32 TYPE_DESK_to_CPAGE_TABLE(TABLE_DESC * lpDataIn,Word32 SizeIn,CPAGE_TABLE * lpDataOut,Word32 SizeOut)
{
	Word32 rc = 0;
	if(lpDataOut == NULL)
		return sizeof(CPAGE_TABLE);

	if(sizeof(TABLE_DESC) != SizeIn ||
		sizeof(CPAGE_TABLE) != SizeOut ||
		lpDataIn == NULL)
	{
		SetReturnCode_cpage(IDS_ERR_DISCREP);
		return 0;
	}

    memset(lpDataOut,0,SizeOut);

	lpDataOut->prop = *lpDataIn;
	// �������� ��������� �������� ����� �������
	if(lpDataIn->nHorLines>0 &&
		lpDataIn->nHorLines>0)
	{
		int c_current = 0;
		int number = 0;
		Point32 p = {0,0};

		for(int c_row = 0; c_row < lpDataIn->nHorLines - 1; c_row++)
			for( int c_col = 0;c_col < lpDataIn->nVerLines - 1; c_col++)
			{
                _ASSERT((c_row*(lpDataIn->nVerLines - 1)+c_col)<MaxCells);
				if(c_row && lpDataIn->Cell[c_row*(lpDataIn->nVerLines - 1)+c_col].TypeBound[TABLE_CELL_TOP] & CELL_BOUND_PSEVDO)
				{// ��� ��������������� ����������� ������
					p = lpDataOut->cell[c_row - 1][c_col].PhCoord;
					c_current = lpDataOut->cell[c_row - 1][c_col].Number;
				}
				else if(!c_col || !(lpDataIn->Cell[c_row*(lpDataIn->nVerLines - 1) + c_col].TypeBound[TABLE_CELL_LEF] & CELL_BOUND_PSEVDO))
				{// ���� ������������ ����������� �����
					c_current = ++lpDataOut->PhNumber;
					p.x = c_col;
					p.y = c_row;
				}
				else
				{// ���� ���. ����������� ������ � ��� ����. ������
					p = lpDataOut->cell[c_row][c_col - 1].PhCoord;
					c_current = lpDataOut->cell[c_row][c_col - 1].Number;
				}

				lpDataOut->cell[c_row][c_col].Number = c_current;
				lpDataOut->cell[c_row][c_col].PhCoord = p;
				lpDataOut->cell[c_row][c_col].Block = -1;
				lpDataOut->cell[p.y][p.x].GeCount++;
			}
			rc = sizeof(*lpDataOut);
	}
	else
		_ASSERT(FALSE);

	return rc;
}
//##########################################################
Word32 CPAGE_TABLE_to_TYPE_DESK( CPAGE_TABLE * lpDataIn,Word32 SizeIn,TABLE_DESC * LpDataOut,Word32 SizeOut)
{
	Word32 rc = 0;

	if(LpDataOut == NULL)
			return sizeof(TABLE_DESC);

	if(sizeof(TABLE_DESC) != SizeOut ||
		sizeof(CPAGE_TABLE) != SizeIn ||
		lpDataIn == NULL)
	{
		SetReturnCode_cpage(IDS_ERR_DISCREP);
		return 0;
	}

	*LpDataOut = lpDataIn->prop;
	rc = sizeof(TABLE_DESC);
	return rc;
}

