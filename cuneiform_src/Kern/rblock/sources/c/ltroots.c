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
 *                                                                          *
 *                   P A G E   L A Y O U T                                  *
 *                                                                          *
 *              Written in 1991 by Yuri Panchul                             *
 *                                                                          *
 *              LTROOTS.C - working with roots file                         *
 *                                                                          *
 ***************************************************************************/

# include <fcntl.h>
# include <stdio.h>
/*# include <crtdbg.h>*/

# include "c_memory.h"
# include "iolib.h"
# include "layout.h"
# include "my_mem.h"
#include "compat_defs.h"

# ifdef LT_STAND_ALONE
ROOT  *pRoots = NULL;
DWORD   nRoots = 0;
# endif

ROOT  *pAfterRoots;

INT  nOriginalRoots;
ROOT *pAfterOriginalRoots;

ROOT_EXT *pRootExts      = NULL;
ROOT_EXT *pAfterRootExts = NULL;
int nRootExts = 0;

int nRootSpaceWidth;
int nRootSpaceHeight;
RECTANGLE rRootSpace;

int   nPageHeight;
int   nSuitablePageHeight;
int   nPageOffset;

ROOT_STRIP *pRootStrips = NULL;
int nRootStrips = 0;

int nRootStripsStep;
int nRootStripsOffset;

# ifdef LT_STAND_ALONE
# define ROOTS_MEMORY_QUANTUM   1024

BOOL RootsLoadFile (PSTR pFilename)
{
/*    typedef int HANDLE;*/

    HANDLE hFile;
    ROOT   RootRecord;

    RootsFreeData ();

    hFile = open (pFilename, O_RDONLY | O_BINARY);

    if (hFile == -1)
    {
        ErrorFile ();
        return (FALSE);
    }

    while (read (hFile, &RootRecord, sizeof (ROOT)) == sizeof (ROOT))
    {
        RootRecord.bReached   = FALSE;

        if (nRoots % ROOTS_MEMORY_QUANTUM == 0)
        {
            pRoots = realloc (pRoots,
                              (size_t) ((nRoots / ROOTS_MEMORY_QUANTUM + 1)
                                * ROOTS_MEMORY_QUANTUM * sizeof (ROOT)));
        }

        nRoots++;

        if (pRoots == NULL)
        {
            ErrorNoEnoughMemory ("in LTROOTS.C,RootsLoadFile,part 1");
            nRoots = 0;
            close (hFile);
            return (FALSE);
        }

        pRoots [nRoots - 1] = RootRecord;
    }

    close (hFile);
    return (TRUE);
}
# endif

void CalculatePageParameters (void)
{
    ROOT *pRoot;

    pAfterRoots = pRoots + nRoots;

    nOriginalRoots      = nRoots;
    pAfterOriginalRoots = pAfterRoots;

    if (nRoots == 0)
    {
        rRootSpace.xLeft   = 0;
        rRootSpace.yTop    = 0;
        rRootSpace.xRight  = -1;
        rRootSpace.yBottom = -1;
    }
    else
    {
        rRootSpace.xLeft   = pRoots [0].xColumn;
        rRootSpace.yTop    = pRoots [0].yRow;
        rRootSpace.xRight  = pRoots [0].xColumn + pRoots [0].nWidth  - 1;
        rRootSpace.yBottom = pRoots [0].yRow    + pRoots [0].nHeight - 1;
    }

    for (pRoot = pRoots; pRoot < pAfterRoots; pRoot++)
    {
        pRoot -> bReached = FALSE;

        if (rRootSpace.xLeft   > pRoot -> xColumn)
            rRootSpace.xLeft   = pRoot -> xColumn;

        if (rRootSpace.yTop    > pRoot -> yRow)
            rRootSpace.yTop    = pRoot -> yRow;

        if (rRootSpace.xRight  < pRoot -> xColumn + pRoots -> nWidth  - 1)
            rRootSpace.xRight  = pRoot -> xColumn + pRoots -> nWidth  - 1;

        if (rRootSpace.yBottom < pRoot -> yRow    + pRoots -> nHeight - 1)
            rRootSpace.yBottom = pRoot -> yRow    + pRoots -> nHeight - 1;
    }

    nRootSpaceWidth  = rRootSpace.xRight  - rRootSpace.xLeft + 1;
    nRootSpaceHeight = rRootSpace.yBottom - rRootSpace.yTop  + 1;
/*
    printf ("[%d, %d]-[%d, %d] : w: %d h: %d\n",
            (int) rRootSpace.xLeft,
            (int) rRootSpace.yTop,
            (int) rRootSpace.xRight,
            (int) rRootSpace.yBottom,
            (int) nRootSpaceWidth,
            (int) nRootSpaceHeight);
    LT_Getch ();
*/

    nPageHeight         = nRootSpaceHeight;
    nSuitablePageHeight = nRootSpaceHeight * 2;
    nPageOffset         = nRootSpaceHeight / 2;
}

void RootStripsCalculate (void)
{
    ROOT *pRoot;
    int  yMin, yMax; // ������������ -- ��� �������� ������ 
                     // � ����� ������� �������� ���� ����� (�� ���������)
    int  iStrip;
    int  iStripBegin;
    int  iStripEnd;

    if (nRoots == 0)
        ErrorInternal ("nRoots == 0");

    // ���������� ����������� � ������������ ��������
    // ������� �������� ("�����").
    yMin = pRoots [0].yRow;
    yMax = pRoots [0].yRow + pRoots [0].nHeight - 1;

    for (pRoot = pRoots; pRoot < pAfterRoots; pRoot++)
    {
        if (pRoot -> yRow < yMin)
            yMin = pRoot -> yRow;

        if (pRoot -> yRow + pRoot -> nHeight - 1 > yMax)
            yMax = pRoot -> yRow + pRoot -> nHeight - 1;
    }

    nRootStripsOffset = yMin;
    nRootStripsStep   = 128;
    nRootStrips       = (yMax - yMin
                         + (nRootStripsStep - 1))
                        / nRootStripsStep
                        + 1;
    // �� ���� nRootStrips -- ��� ��������� ������
    // � (yMax - yMin) ������� 128; ��������, ��� ����������
    // yMax � yMin ��� ������ 128 � ����

	if(pRootStrips)// Piter
	{
		free(pRootStrips);// Piter
		pRootStrips=NULL;// Piter
	}// Piter
    pRootStrips = malloc (nRootStrips * sizeof (ROOT_STRIP));
    if (pRootStrips==NULL)
            ErrorNoEnoughMemory ("in LTROOTS.C,RootStripsCalculate,part 1");
    memset (pRootStrips, 0, nRootStrips * sizeof (ROOT_STRIP));

    for (pRoot = pRoots; pRoot < pAfterRoots; pRoot++)
    {
        iStripBegin = (pRoot -> yRow
                       - nRootStripsOffset)
                      / nRootStripsStep;

        iStripEnd   = (pRoot -> yRow + pRoot -> nHeight - 1
                       - nRootStripsOffset)
                      / nRootStripsStep;
		_ASSERT(nRootStrips>iStripEnd); // Piter
		_ASSERT(nRootStrips>iStripBegin);// Piter
        for (iStrip = iStripBegin; iStrip <= iStripEnd; iStrip++)
        {
            if (pRootStrips [iStrip].pBegin == NULL ||
                pRoot < pRootStrips [iStrip].pBegin)
            {
                pRootStrips [iStrip].pBegin = pRoot;
            }

            if (pRootStrips [iStrip].pEnd == NULL ||
                pRoot > pRootStrips [iStrip].pEnd)
            {
                pRootStrips [iStrip].pEnd   = pRoot;
            }
        }
    }
}

void RootStripsGetLoopParameters
(
    int yTop,
    int yBottom,
    ROOT **ppBegin,
    ROOT **ppAfter
)
{
    int  iStripBegin;
    int  iStripEnd;
    ROOT *pBegin;
    ROOT *pEnd;
    int  iStrip;

    if (nRootStripsStep == 0)
        ErrorInternal ("nRootStripsStep == 0");

    iStripBegin = (yTop
                   - nRootStripsOffset)
                  / nRootStripsStep;

    iStripEnd   = (yBottom
                   - nRootStripsOffset)
                  / nRootStripsStep;

    if (iStripBegin <  0)           iStripBegin = 0;
    if (iStripEnd   <  0)           iStripEnd   = 0;
    if (iStripBegin >= nRootStrips) iStripBegin = nRootStrips - 1;
    if (iStripEnd   >= nRootStrips) iStripEnd   = nRootStrips - 1;

    if (iStripBegin > iStripEnd)
        EXCHANGE_INTS (iStripBegin, iStripEnd);

    pBegin = NULL;
    pEnd   = NULL;

    for (iStrip = iStripBegin; iStrip <= iStripEnd; iStrip++)
    {
        if (pRootStrips [iStrip].pBegin == NULL)
            continue;

        if (pBegin == NULL)
        {
            pBegin = pRootStrips [iStrip].pBegin;
            pEnd   = pRootStrips [iStrip].pEnd;
        }
        else
        {
            if (pRootStrips [iStrip].pBegin < pBegin)
                pBegin = pRootStrips [iStrip].pBegin;

            if (pRootStrips [iStrip].pEnd   > pEnd)
                pEnd   = pRootStrips [iStrip].pEnd;
        }
    }

    if ((pBegin == NULL) != (pEnd == NULL))
        ErrorInternal ("(pBegin == NULL) != (pEnd == NULL)");

    if (pBegin == NULL)
    {
        *ppBegin = NULL;
        *ppAfter = NULL;
    }
    else
    {
        *ppBegin = pBegin;
        *ppAfter = pEnd + 1;
    }
}

void RootsRemoveFromRulers (void)
{
    ROOT *p;
    int  x, y;
    extern void del_root (INT row, INT col, INT h, INT w);

    for (p = pRoots; p < pAfterRoots; p++)
    {
        if (p -> nBlock == REMOVED_BLOCK_NUMBER)
        {
            x = p -> xColumn;
            y = p -> yRow;

            REAL_XY (x, y);
//          del_root (y, x, p -> nHeight, p -> nWidth);
        }
    }
}

void RootsSaveNonLayoutData (void)
{
    int i;

    if (pRootExts != NULL)
        ErrorInternal ("RootsSaveNonLayoutData: pRootExts != NULL");

    nRootExts = nRoots;

    pRootExts = (PROOT_EXT) malloc (nRootExts * sizeof (ROOT_EXT));

    if (pRootExts == NULL)
            ErrorNoEnoughMemory ("in LTROOTS.C,RootStripsCalculate,part 2");

    pAfterRootExts = pRootExts + nRootExts;

    for (i = 0; i < nRootExts; i++)
    {
        pRootExts [i].wSegmentPtr = pRoots [i].u1.u2.wSegmentPtr;
        pRootExts [i].wLength     = pRoots [i].u1.u2.wLength;
    }
}

void RootsRestoreNonLayoutData_ForDustAndRemoved (void)
{
    int i;

    if (pRootExts == NULL)
        ErrorInternal ("RootsRestoreNonLayoutData: pRootExts == NULL");

    for (i = 0; i < nRootExts; i++)
    {
        if (pRoots [i].nBlock == DUST_BLOCK_NUMBER ||
            pRoots [i].nBlock == REMOVED_BLOCK_NUMBER)
        {
            pRoots [i].u1.u2.wSegmentPtr = pRootExts [i].wSegmentPtr;
            pRoots [i].u1.u2.wLength     = pRootExts [i].wLength;
        }
    }
}

void RootsRestoreNonLayoutData_ForBlock (BLOCK *p)
{
    ROOT *pRoot, *pNext;

    if (pRootExts == NULL)
        ErrorInternal ("RootsRestoreNonLayoutData: pRootExts == NULL");

    if (p -> pRoots == NULL)
        return;

    for (pRoot = p -> pRoots; pRoot != NULL; pRoot = pNext)
    {
        pNext = pRoot -> u1.pNext;
        pRoot -> u1.u2.wSegmentPtr = pRootExts [pRoot - pRoots].wSegmentPtr;
        pRoot -> u1.u2.wLength     = pRootExts [pRoot - pRoots].wLength;
    }
}

void RootsRestoreNonLayoutData (void)
{
    int i;

    if (pRootExts == NULL)
        ErrorInternal ("RootsRestoreNonLayoutData: pRootExts == NULL");

    for (i = 0; i < nRootExts; i++)
    {
        pRoots [i].u1.u2.wSegmentPtr = pRootExts [i].wSegmentPtr;
        pRoots [i].u1.u2.wLength     = pRootExts [i].wLength;
    }

    free (pRootExts);

    pRootExts      = NULL;
    pAfterRootExts = NULL;
    nRootExts      = 0;
}

void RootsFreeData (void)
{
# ifdef LT_STAND_ALONE
    if (pRoots != NULL)
    {
        free (pRoots);
        pRoots = NULL;
        pAfterRoots = NULL;
        nRoots = 0;
    }
# endif

    if (pRootExts != NULL)
    {
        free (pRootExts);
        pRootExts = NULL;
        pAfterRootExts = NULL;
    }

    if (pRootStrips != NULL)
    {
        free (pRootStrips);
        pRootStrips = NULL;
        nRootStrips = 0;
    }
}
