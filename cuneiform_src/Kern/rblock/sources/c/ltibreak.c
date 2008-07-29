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



/****************************************************************************
 *                                                                          *
 *                   P A G E   L A Y O U T                                  *
 *                                                                          *
 *              Written in 1991 by Yuri Panchul                             *
 *                                                                          *
 *              LTIBREAK.C - Initial breaking of page                       *
 *                                                                          *
 ***************************************************************************/

# include "layout.h"
# include "dpuma.h"

extern Handle hInitialBreaking;

// ��������� ���� nBlock ���� �� ����� ���������� (���������)
void SetRootsBlocks (int nShift)
{
    ROOT *pRoot;
    RECTANGLE r;
    int  nBlock;

    for (pRoot = pRoots; pRoot < pAfterRoots; pRoot++)
    {
        if (pRoot -> nBlock >= FIRST_REGULAR_BLOCK_NUMBER)
            continue;

        r.xLeft   = XY_COMPRESS (pRoot -> xColumn);
        r.yTop    = XY_COMPRESS (pRoot -> yRow);

        // ����� ������������� (����) ����� �� ������� ��������,
        // � ������� � ����� ������� ��� ����� ����� �����
        // (�������� �� ��� ���� PAGE_MATRIX_MARK_SHIFT � �.�.,
        // �� ��� ��� �� ��� �����������)
        nBlock = PageMatrix [(r.yTop << PAGE_MATRIX_WIDTH_SHIFT) + r.xLeft]
                 >> PAGE_MATRIX_MARK_SHIFT;

        if (nBlock >= FIRST_REGULAR_BLOCK_NUMBER)
        { // �� ���� ���� ���� ��������� (��� ������)
          // � ��������������� ���������� ("���������������")
            pRoot -> nBlock = nBlock + nShift;
            continue;
        }

        // ���� ���� �� ��������� � ��� �������� �����������

        r.xRight  = XY_COMPRESS (pRoot -> xColumn + pRoot -> nWidth - 1);

        nBlock = PageMatrix [(r.yTop << PAGE_MATRIX_WIDTH_SHIFT) + r.xRight]
                 >> PAGE_MATRIX_MARK_SHIFT;

        if (nBlock >= FIRST_REGULAR_BLOCK_NUMBER)
        {
            pRoot -> nBlock = nBlock + nShift;
            continue;
        }

        r.yBottom = XY_COMPRESS (pRoot -> yRow    + pRoot -> nHeight - 1);

        nBlock = PageMatrix [(r.yBottom << PAGE_MATRIX_WIDTH_SHIFT) + r.xLeft]
                 >> PAGE_MATRIX_MARK_SHIFT;

        if (nBlock >= FIRST_REGULAR_BLOCK_NUMBER)
        {
            pRoot -> nBlock = nBlock + nShift;
            continue;
        }

        nBlock = PageMatrix [(r.yBottom << PAGE_MATRIX_WIDTH_SHIFT) + r.xRight]
                 >> PAGE_MATRIX_MARK_SHIFT;

        if (nBlock >= FIRST_REGULAR_BLOCK_NUMBER)
        {
            pRoot -> nBlock = nBlock + nShift;
            continue;
        }
    }
}

// ������ ������� �������� � ����������� ������������� ������
// ����, ����� � ��������; �������� �������� �������,
// ������������� ������ �� ��������� � ��������� ������:
void ClearSeries (COMP *pBegin, COMP *pEnd)
{
    COMP *pComp;

    // ������ ������� ��������, �������� ������ ������� �����:
    // ����, ����� � ��������
    for (pComp = pBegin; pComp != pEnd; pComp = pComp -> pNext)
    {
        CompAND_Matrix (pComp, PMC_FLAGS_MASK);
    }
}

void InitialBreakingProceed (void)
{
    int i;
    int nCompShift;
    int nComp;
    COMP *pCompSeriesBegin;
    COMP *pComp;

    // ����������, � ������ ���� ����� ��� ���� ����� ��������:
    // (�������� -- � "���������")
    for (i = 0; i < nRoots; i++)
    {
        pRoots [i].nBlock =
            IS_LAYOUT_DUST (pRoots [i]) ?
                DUST_BLOCK_NUMBER :
                REMAINDER_BLOCK_NUMBER; // ������������ ����� � ����, ��� �������� ���� ����
    }

    if (! bOptionInitialBreakingByPageMatrix)
        return;

    CompsBuild
    (
        PageMatrix,
        PAGE_MATRIX_WIDTH,   // ����������� ������ �������
        PAGE_MATRIX_HEIGHT,  // ����������� ������ �������
        PAGE_MATRIX_SIZE,    // ��� :)
        PMC_ROOT             // "����" ���������� ����������
    );

    nCompShift       = 0;
    nComp            = 0;          // ������� (��������) ���-�� ���������
    pCompSeriesBegin = pCompsList; // ������ ������ ���������

    for (pComp = pCompsList; pComp != NULL; pComp = pComp -> pNext)
    {
        if (nComp == COMP_SERIES_LENGTH)
        {
            // ��������� ���� nBlock ���� �� ����� ���������� (���������)
            SetRootsBlocks (nCompShift);

# ifdef LT_DEBUG
            //if (LT_DebugGraphicsLevel >= 4)
			// �������� ����� ������� �� ����� ������� ��������
      // (��, � �����-��, ��������� -- �� �� ��� �� � �����)
      if (!LDPUMA_Skip(hInitialBreaking))
                LT_GraphicsPageMatrixOutput ("Comps series");
# endif

            // ������ ������� ��������, �������� ������ ������� �����:
            // ����, ����� � �������� (��� ��������� � pCompSeriesBegin
            // �� �������; � ������ ������ -- �� ���������)
            ClearSeries (pCompSeriesBegin, pComp);

            nCompShift += nComp;
            nComp = 0;
            pCompSeriesBegin = pComp;
        }

        // ��������� ������, �������� "�� ����������" ��������
        // ����� (���, ��� ������������� � ������� ��� ������ PMC_ROOT;
        // ����� �������, ����� �� ���������� ����� ��������� ���������
        // ������ �� ������� ��������
        CompOR_Matrix
        (
            pComp,
            (nComp + FIRST_REGULAR_BLOCK_NUMBER) << PAGE_MATRIX_MARK_SHIFT
        );

        nComp++;
    }

    // ��������� ���� nBlock ���� �� ����� ���������� (���������)
    // (��� ������� -- ����� ������������ �� nComp (<- ������� � ������))
    SetRootsBlocks (nCompShift);
    // ������ ������� ��������, �������� ������ ������� �����:
    // ����, ����� � �������� (������� ��������� � ����� ���������
    // -- ������� �������� � ��������� ����� ���������� � �������� (�������))
    ClearSeries (pCompSeriesBegin, NULL);

    nNextBlockNumber = nCompShift + nComp + 1;
    CompsFreeData ();      // ��� �������: � ������ ���������,
    IntervalsFreeData ();  // � ������, � (����������) ���������.

    // ��������: � ������ ���� (� ���� nBlock) -- ������ � ����������;
    // � ������� �������� -- ��, ��� ���� �� ����� � ��� �������.
}

void InitialBreakingFreeData (void)
{
}
