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

// TableClass.h: interface for the TableClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLECLASS_H__AD968403_FBCC_11D2_BB1B_0000E8D9FDF6__INCLUDED_)
#define AFX_TABLECLASS_H__AD968403_FBCC_11D2_BB1B_0000E8D9FDF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cttypes.h"
#include "ptrname.h"

///////////////////////////////////////////////////////
class TableCell
{
	Int32	m_nNumber;	// ����� ������ ���������� ������� ( ������� � 1 )
	Point32 m_PhCoord;	// ���������� �������� � ���������� ������
	Int32   m_nBlock;	// ����� ���������
	Int32	m_nGeCount;	// ����� �������������� �����, �������� � ����������

public:
	TableCell();
	~TableCell();
	inline operator Point32(){ return m_PhCoord;};
	inline operator Int32()  { return m_nBlock;};
	inline Int32 GetGeCount(){ return m_nGeCount;};
	inline Bool32 IsPhysic() { return m_nGeCount > 1;};
	inline Point32 operator=(Point32 p){ m_PhCoord = p; return p;};
	inline Int32 operator=(Int32   n){ m_nNumber = n; return n;};
	inline Int32 & Fragment(){ return m_nBlock;};
	inline Int32 & GeCount() { return m_nGeCount;};
};
///////////////////////////////////////////////////////
class TableLine
{
private:
	Int32 m_nCoord; // ���������� X - ��� ������������ Y - ��� ��������������
	//Int32 m_nItems;	// ����� ��������� �����

#define LINE_REALY	0x00000001 // �������� ������� �����
#define LINE_VISUAL	0x00000003 // ������� ������� ����� ( ������ �������� !!)

	PtrName<Word32> m_lpProperty; // �������� ��������� �����

public:
	TableLine();
	~TableLine();

	Bool32	Create(Int32 nCoord,Word32 nItems);
	void	Delete();

	Bool32	Attach(Handle hPage);
	Bool32	Store(Handle hPage);
	void    Remove(Handle hPage);

	inline void   SetRealy(Word32 nItem,Bool32 b){
		if(b)
			m_lpProperty[nItem] |= LINE_REALY;
		else
			m_lpProperty[nItem] &= ~LINE_REALY;
		}
	inline void   SetVisual(Word32 nItem,Bool32 b){
		if(b)
			m_lpProperty[nItem] |= LINE_VISUAL;
		else {
				m_lpProperty[nItem] &=~LINE_VISUAL;
				SetRealy(nItem,TRUE);
			}
		}

	inline Bool32 IsRealy(Word32 nItem){ return m_lpProperty[nItem] & LINE_REALY; };
	inline Bool32 IsVisual(Word32 nItem){ return m_lpProperty[nItem] & LINE_VISUAL; };
	inline operator Int32(){ return m_nCoord;};
};
///////////////////////////////////////////////////////
class TableClass
{
private:
	//Word32		m_nVer;			// ����� ������������ �����
	//Word32		m_nHor;			// ����� �������������� �����
	Int32		m_nSkew2048;	// ������ �������
	Handle		m_hBlock;
	Handle      m_hPage;
	Word32      m_nPhNumber;    // ����� ���������� �����

	PtrName<TableLine> m_lpVerLines;// �������������� ���������� ������������ �����
	PtrName<TableLine> m_lpHorLines;// ������������ ���������� �������������� �����
	PtrName<TableCell> m_lpCell;    // ������ �������

public:
	TableClass();
	~TableClass();

	Bool32			Create(Int32 Skew2048, Word32 nVer,Int32 * lpVCor, Word32 nHor,Int32 * lpHCor);// ������� �������
	void			Delete();// ���������� ���������� ������.
	void			Update();// ������� ���������� �����.

	static TableClass * Attach(Handle hPage,Handle hBlock);// ������� ��������� �� ���������� ���������� � CPAGE
	Handle			Store(Handle hPage); // ��������� ������� � �������� ��������. ���������� ���������� ���������
	void			Remove(); // ������� �� CPAGE
	TableClass *	GetNext();// �������� ��������� �������



	inline Word32 GetNumberGeCell(){ return GetNumberColumn()*GetNumberRow();};
	inline Word32 GetNumberPhCell(){ return GetNumberGeCell();};

	inline Int32 GetSkew2048(){ return m_nSkew2048;};
	inline void  SetSkew2048(Int32 nSkew){ m_nSkew2048 = nSkew ;};

	inline Word32 GetNumberColumn() { return m_lpVerLines.GetSize() - 1;};
	inline Word32 GetNumberRow()	{ return m_lpHorLines.GetSize() - 1;};

	inline TableLine & GetHLine(Word32 nLine)	{
		_ASSERT(nLine>=0 && nLine<m_lpHorLines.GetSize());
		return m_lpHorLines[nLine];
		}

	inline TableLine & GetVLine(Word32 nLine)	{
		_ASSERT(nLine>=0 && nLine<m_lpVerLines.GetSize());
		return m_lpVerLines[nLine];
		}
	inline TableCell & GetCell(Point32 pt){
		_ASSERT(GetNumberRow()>(Word32)pt.y &&
				GetNumberColumn()>(Word32)pt.x &&
				pt.y>=0 &&
				pt.x>=0);
		return m_lpCell[pt.y*GetNumberColumn() + pt.x];
		}

};

#endif // !defined(AFX_TABLECLASS_H__AD968403_FBCC_11D2_BB1B_0000E8D9FDF6__INCLUDED_)
