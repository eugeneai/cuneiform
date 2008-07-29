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
 *              LTEXCOMP.C - Components extraction from matrix              *
 *                                                                          *
 ***************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "c_memory.h"
# include "layout.h"
# include "my_mem.h"
#include "minmax.h"


static BYTE *pMatrix = NULL;
static int  nWidth;
static int  nHeight;
static int  nSize;     // ������� ������������, ��� ��� -- ������ �������
static int  BlackMask; // ��� ��������; ���������� �������� -- PMC_ROOT

INTERVAL *pIntervals = NULL;
int nIntervals = 0;

INTERVAL *pPrevIntervals = NULL;
int nPrevIntervals = 0;

STRIP *pStripsPool      = NULL;
int   nStripsPoolLength = 0;
STRIP *pFreeStripsList  = NULL;

COMP  *pCompsPool       = NULL;
int   nCompsPoolLength  = 0;
COMP  *pFreeCompsList   = NULL;

COMP *pCompsList = NULL;
static int nNextCompNumber = 1;

/****************************************************************************
 *                                                                          *
 *                        Working with intervals                            *
 *                                                                          *
 ***************************************************************************/

void IntervalsInit (void)
{
    if (pIntervals == NULL)
    {
        // �������� -- �� �������� � ����: xBegin, xEnd (� COMP*);
        // nWidth � nHeight -- of PageMatrix;
        pIntervals
            = malloc (MAX (nHeight, nWidth) * sizeof (INTERVAL));

        if (pIntervals == NULL)
            ErrorNoEnoughMemory ("in LTEXCOMP.C,IntervalsInit,part 1");
    }

    if (pPrevIntervals == NULL)
    {
        pPrevIntervals
            = malloc (MAX (nHeight, nWidth) * sizeof (INTERVAL));

        if (pPrevIntervals == NULL)
            ErrorNoEnoughMemory ("in LTEXCOMP.C,IntervalsInit,part 2");
    }

    nIntervals     = 0;
    nPrevIntervals = 0;
}

void IntervalsBuild (int y)
{
    int x;
    BYTE *pLine = pMatrix + y * nWidth;

    nIntervals = 0;
    x = 0;

    for (;;)
    {
        while (x < nWidth && (pLine [x] & BlackMask) == 0)
            x++;

        if (x >= nWidth)
            break;

        pIntervals [nIntervals].xBegin = x;

        while (x < nWidth && (pLine [x] & BlackMask))
            x++;

        pIntervals [nIntervals].xEnd   = x;
        pIntervals [nIntervals].pComp = NULL;
        nIntervals++;
    }
}

void IntervalsStep (int y)
{
    INTERVAL *pTempIntervals;
    int  i, j, k;

    // swap(pIntervals, pPrevIntervals):
    pTempIntervals = pIntervals;
    pIntervals     = pPrevIntervals;
    pPrevIntervals = pTempIntervals;

    nPrevIntervals = nIntervals;

    IntervalsBuild (y);

    i = 0; // ������ ��������� ���������� ������
    j = 0; // ������ ��������� ������� ������

    // ��������� ������� ��������� � ������� �������� �� ��������� �� � EXC
    // (���������� ��������� � �������� �������������), ��� ���� �����������
    // "�����������" ������: � ������ ������ ������� ��������������� ��� ������
    // �������, � ������� ��� �������� ���������, � ���������� ��������
    //    ---              ---            ---         ---
    //         --- ,  ---      , � �����    ---  �  ---    .
    while (i < nPrevIntervals || j < nIntervals)
    {
        if (j == nIntervals ||
              (i != nPrevIntervals &&
               (pPrevIntervals [i].xEnd < pIntervals [j].xBegin)
              )
           )
        {
            i++;
        }
        else if (i == nPrevIntervals ||
                   j != nIntervals &&
                   pIntervals [j].xEnd < pPrevIntervals [i].xBegin)
        {
            CompAddInterval (CompNew (), y, &pIntervals [j]);
            j++;
        }
        else
        {
            if (pIntervals [j].pComp == NULL ||
                pIntervals [j].pComp == pPrevIntervals [i].pComp) // ��� ����������� �����������? (��. ��. ��������)
            {
                CompAddInterval (pPrevIntervals [i].pComp,
                                 y,
                                 &pIntervals [j]);
            }
            else // ������� �������� (���������������) ���������, �������������
            {    // ������ �����������. ������ ������ ����������� ���� ���������.
                COMP *pDeletedComp;
                COMP *pSumComp;

                pDeletedComp = pPrevIntervals [i].pComp;
                pSumComp     = pIntervals [j].pComp;

                // ����������� ���������. ������ ���������� �������������
                // �� ������ � �������� �� ������ ���������� (�������).
                CompsConnect (pSumComp, pDeletedComp);

                // "�������������" ���������� � ������� ���� �������
                // �� DeletedComp � SumComp
                for (k = i; k < nPrevIntervals; k++)
                {
                    if (pPrevIntervals [k].pComp == pDeletedComp)
                        pPrevIntervals [k].pComp = pSumComp;
                }

                for (k = 0; k < j; k++)
                {
                    if (pIntervals [k].pComp == pDeletedComp)
                        pIntervals [k].pComp = pSumComp;
                }

                CompDelete (pDeletedComp);
            }

            // ���� ��������� �� ������������, �� ������ �� ��� ������
            if (! (j + 1 != nIntervals &&
                   pIntervals [j + 1].xBegin <= pPrevIntervals [i].xEnd))
            {
                if (! (i + 1 != nPrevIntervals &&
                    pPrevIntervals [i + 1].xBegin <= pIntervals [j].xEnd))
                {
                    j++;
                }

                i++;
            }
            else if (! (i + 1 != nPrevIntervals &&
                   pPrevIntervals [i + 1].xBegin <= pIntervals [j].xEnd))
            {
                j++;
            }
        }
    }
}

void IntervalsFreeData (void)
{
    if (pIntervals != NULL)
    {
        free (pIntervals);
        pIntervals = NULL;
        nIntervals = 0;
    }

    if (pPrevIntervals != NULL)
    {
        free (pPrevIntervals);
        pPrevIntervals = NULL;
        nPrevIntervals = 0;
    }
}

/****************************************************************************
 *                                                                          *
 *              STRIPS - Working with strips                                *
 *                                                                          *
 ***************************************************************************/

static void RewriteAllStripsPointers
(
    STRIP *pStripsPool,
    STRIP *pOldStripsPool,
    int   nLength
)
{
    register STRIP *pStrip;
    register COMP  *pComp;
    register int   offset;

    if (pOldStripsPool == NULL || pStripsPool == pOldStripsPool)
        return;

    offset = (BYTE *) pStripsPool - (BYTE *) pOldStripsPool;

    for (pStrip = pStripsPool; pStrip < pStripsPool + nLength; pStrip++)
    {
        if (pStrip -> pNext != NULL)
            pStrip -> pNext = (STRIP *) ((BYTE *) pStrip -> pNext + offset);
    }

    for (pComp = pCompsList; pComp != NULL; pComp = pComp -> pNext)
    {
        if (pComp -> pStripsListBegin != NULL)
        {
            pComp -> pStripsListBegin =
                (STRIP *) ((BYTE *) pComp -> pStripsListBegin + offset);
        }

        if (pComp -> pStripsListEnd   != NULL)
        {
            pComp -> pStripsListEnd =
                (STRIP *) ((BYTE *) pComp -> pStripsListEnd + offset);
        }
    }
}

STRIP *StripNew (void)
{
    STRIP *pNew;

    if (pFreeStripsList == NULL)
    {
        STRIP *pOldStripsPool = pStripsPool;
        STRIP *pStrip;
        int   nOldLength      = nStripsPoolLength;

        if (pStripsPool == NULL)
        {
            nStripsPoolLength = STRIPS_POOL_FIRST_ALLOCATION;
        }
        else
        {
            nStripsPoolLength =
                (nStripsPoolLength / STRIPS_POOL_ALLOCATION_QUANTUM + 1)
                            * STRIPS_POOL_ALLOCATION_QUANTUM;
        }

        pStripsPool = (STRIP *)
            realloc (pStripsPool, nStripsPoolLength * sizeof (STRIP));

        if (pStripsPool == NULL)
            ErrorNoEnoughMemory ("in LTEXCOMP.C,StripNew,part 1");

        RewriteAllStripsPointers (pStripsPool, pOldStripsPool, nOldLength);

        pFreeStripsList = pStripsPool + nOldLength;

        for (pStrip = pFreeStripsList;
                 pStrip < pStripsPool + nStripsPoolLength - 1;
                     pStrip++)
        {
            pStrip -> pNext = pStrip + 1;
        }

        pStrip -> pNext = NULL;
    }

    if (pFreeStripsList == NULL)
        ErrorInternal ("pFreeStripsList == NULL in StripNew");

    pNew = pFreeStripsList;
    pFreeStripsList = pFreeStripsList -> pNext;

    memset (pNew, 0, sizeof (STRIP));
    return (pNew);
}

void StripDelete (STRIP *pStrip)
{
    pStrip -> pNext = pFreeStripsList;
    pFreeStripsList = pStrip;
}

/****************************************************************************
 *                                                                          *
 *              Working with components                                     *
 *                                                                          *
 ***************************************************************************/

static void RewriteAllCompsPointers
(
    COMP *pCompsPool,
    COMP *pOldCompsPool,
    int  nLength
)
{
    register COMP  *pComp;
    register INTERVAL *pInt;
    register int   offset;

    if (pOldCompsPool == NULL || pCompsPool == pOldCompsPool)
        return;

    offset = (BYTE *) pCompsPool - (BYTE *) pOldCompsPool;

    for (pComp = pCompsPool; pComp < pCompsPool + nLength; pComp++)
    {
        if (pComp -> pNext != NULL)
            pComp -> pNext = (COMP *) ((BYTE *) pComp -> pNext + offset);

        if (pComp -> pPrev != NULL)
            pComp -> pPrev = (COMP *) ((BYTE *) pComp -> pPrev + offset);
    }

    for (pInt = pIntervals;
             pInt < pIntervals + nIntervals;
                 pInt++)
    {
        if (pInt -> pComp != NULL)
            pInt -> pComp = (COMP *) ((BYTE *) pInt -> pComp + offset);
    }

    for (pInt = pPrevIntervals;
             pInt < pPrevIntervals + nPrevIntervals;
                 pInt++)
    {
        if (pInt -> pComp != NULL)
            pInt -> pComp = (COMP *) ((BYTE *) pInt -> pComp + offset);
    }

    pCompsList = (COMP *) ((BYTE *) pCompsList + offset);
}

COMP *CompNew (void)
{
    COMP *pNew;

    if (pFreeCompsList == NULL)
    {
        COMP *pOldCompsPool = pCompsPool;
        COMP *pComp;
        int  nOldLength     = nCompsPoolLength;

        if (pCompsPool == NULL)
        {
            nCompsPoolLength = COMPS_POOL_FIRST_ALLOCATION; //100
        }
        else
        {
            // ����� ������, ���� 50 (������, ��������� �� ��������� �����������)
            nCompsPoolLength =
                (nCompsPoolLength / COMPS_POOL_ALLOCATION_QUANTUM + 1)
                            * COMPS_POOL_ALLOCATION_QUANTUM;
        }

        pCompsPool = (COMP *)
            realloc (pCompsPool, nCompsPoolLength * sizeof (COMP));

        if (pCompsPool == NULL)
            ErrorNoEnoughMemory ("in LTEXCOMP.C,CompNew,part 1");

        pFreeCompsList = pCompsPool + nOldLength;

        for (pComp = pFreeCompsList;
                 pComp < pCompsPool + nCompsPoolLength - 1;
                     pComp++)
        {
            pComp -> pNext = pComp + 1;
        }

        pComp -> pNext = NULL;

        RewriteAllCompsPointers (pCompsPool, pOldCompsPool, nOldLength);
    }

    if (pFreeCompsList == NULL)
        ErrorInternal ("pFreeCompsList == NULL in CompNew");

    pNew = pFreeCompsList;
    pFreeCompsList = pFreeCompsList -> pNext;

    memset (pNew, 0, sizeof (COMP));

    pNew -> Number = nNextCompNumber++;
    pNew -> pNext = pCompsList;

    if (pCompsList != NULL)
        pCompsList -> pPrev = pNew;

    pCompsList = pNew;
    return (pNew);
}

void CompDelete (COMP *pComp)
{
    STRIP *pTemp;

    if (pComp == pCompsList)
        pCompsList = pCompsList -> pNext;

    if (pComp -> pPrev != NULL) pComp -> pPrev -> pNext = pComp -> pNext;
    if (pComp -> pNext != NULL) pComp -> pNext -> pPrev = pComp -> pPrev;

    while (pComp -> pStripsListBegin != NULL)
    {
        pTemp = pComp -> pStripsListBegin;
        pComp -> pStripsListBegin = pComp -> pStripsListBegin -> pNext;
        StripDelete (pTemp);
    }

    pComp -> pNext = pFreeCompsList;
    pFreeCompsList = pComp;
}

void CompAddInterval (COMP *pComp, int y, INTERVAL *pInterval)
{
    STRIP *pNew;

    pInterval -> pComp = pComp;

    if (! pComp -> bRectangleAccounted)
    {
        pComp -> xLeft   = pInterval -> xBegin;
        pComp -> yTop    = y;
        pComp -> xRight  = pInterval -> xEnd;
        pComp -> yBottom = y;
        pComp -> bRectangleAccounted = TRUE;
    }
    else
    {
        if (pInterval -> xBegin < pComp -> xLeft)
            pComp -> xLeft = pInterval -> xBegin;

        if (y < pComp -> yTop)
            pComp -> yTop = y;

        if (pInterval -> xEnd > pComp -> xRight)
            pComp -> xRight = pInterval -> xEnd;

        if (y > pComp -> yBottom)
            pComp -> yBottom = y;
    }

    pNew = StripNew ();

    pNew -> pNext  = pComp -> pStripsListBegin;
    pNew -> y      = y;
    pNew -> xBegin = pInterval -> xBegin;
    pNew -> xEnd   = pInterval -> xEnd;

    pComp -> pStripsListBegin = pNew;

    if (pComp -> pStripsListEnd == NULL)
        pComp -> pStripsListEnd = pNew;

    pComp -> nSquare += pNew -> xEnd - pNew -> xBegin;
}

// ����������� ���������. ������ ���������� �������������
// �� ������ � �������� �� ������ ���������� (�������).
// ������ ���������� ������� � ����������� � ������ � ��������
void CompsConnect (COMP *pComp1, COMP *pComp2)
{
    if (pComp2 -> xLeft < pComp1 -> xLeft)
        pComp1 -> xLeft = pComp2 -> xLeft;

    if (pComp2 -> yTop < pComp1 -> yTop)
        pComp1 -> yTop = pComp2 -> yTop;

    if (pComp2 -> xRight > pComp1 -> xRight)
        pComp1 -> xRight = pComp2 -> xRight;

    if (pComp2 -> yBottom > pComp1 -> yBottom)
        pComp1 -> yBottom = pComp2 -> yBottom;

    pComp1 -> pStripsListEnd -> pNext = pComp2 -> pStripsListBegin;
    pComp1 -> pStripsListEnd          = pComp2 -> pStripsListEnd;

    pComp2 -> pStripsListBegin = NULL;
    pComp2 -> pStripsListEnd   = NULL;
}

// �� ���� ������� (���������� � �-�����������) ����������
// �������� �������� ����� (������� ���).
void CompOR_Matrix (COMP *pComp, int Mask)
{
    STRIP *pStrip;
    BYTE  *p;

    for (pStrip = pComp -> pStripsListBegin;
             pStrip != NULL;
                 pStrip = pStrip -> pNext)
    {
        // ����� nWidth -- ��� ������ ������� ��������
        for (p = pMatrix + pStrip -> y * nWidth + pStrip -> xBegin;
                 p < pMatrix + pStrip -> y * nWidth + pStrip -> xEnd;
                     p++)
        {
            *p |= Mask;
        }
    }
}

void CompAND_Matrix (COMP *pComp, int Mask)
{
    STRIP *pStrip;
    BYTE  *p;

    for (pStrip = pComp -> pStripsListBegin;
             pStrip != NULL;
                 pStrip = pStrip -> pNext)
    {
        for (p = pMatrix + pStrip -> y * nWidth + pStrip -> xBegin;
                 p < pMatrix + pStrip -> y * nWidth + pStrip -> xEnd;
                     p++)
        {
            *p &= Mask;
        }
    }
}

void CompsBuild
(
    BYTE *_pMatrix,
    int   _nWidth,
    int   _nHeight,
    int   _nSize,
    int   _BlackMask
)
{
    int y;

    pMatrix    = _pMatrix;
    nWidth     = _nWidth;
    nHeight    = _nHeight;
    nSize      = _nSize;
    BlackMask  = _BlackMask;

    IntervalsInit (); // ����� ���� ��������� ������
                      // �� MAX(nWidth, nHeight) /����������/.
    for (y = 0; y < nHeight; y++)
    {
        IntervalsStep (y);
    }
}

void CompsFreeData (void)
{
    if (pCompsPool != NULL)
    {
        free (pCompsPool);
        pCompsPool       = NULL;
        nCompsPoolLength = 0;
        pFreeCompsList   = NULL;
    }

    pCompsList = NULL;
    nNextCompNumber = 1;

    if (pStripsPool != NULL)
    {
        free (pStripsPool);
        pStripsPool       = NULL;
        nStripsPoolLength = 0;
        pFreeStripsList   = NULL;
    }
}
