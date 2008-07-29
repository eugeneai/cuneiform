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
 *              S T R I N G S   E X T R A C T I O N                         *
 *                                                                          *
 *              Written in 1991 by Yuri Panchul                             *
 *                                                                          *
 *              SEBREAK.C - horizontal breaking of glued components         *
 *                                                                          *
 ***************************************************************************/

# include <stdlib.h>

# include	"extract.h"
# include	"func.h"
# include	"struct.h"
#include    "ccom.h"
#include	"evn.h"
#include	"newfunc.h"
#include "minmax.h"
# define EXTENDED_RASTER_MAX_WIDTH  RASTER_MAX_WIDTH
# define EXTENDED_RASTER_MAX_HEIGHT (RASTER_MAX_HEIGHT * 2)

extern Int32 exthCCOM;

BYTE *pRaster;
int   nRasterWidth;
int   nRasterHeight;
int   nRasterByteWidth;

int   aRasterHystogram [EXTENDED_RASTER_MAX_HEIGHT];
int   yRasterUpBreakLimit;
int   yRasterDownBreakLimit;
int   yRasterBreakLine;

int   nOldRoots;
ROOT  *pOldAfterRoots;

extern  CCOM_comp *get_CCOM_comp(PROOT r);
extern  PBYTE make_raster_CCOM(CCOM_comp *cmp);
extern  PBYTE make_extended_raster_CCOM(CCOM_comp *cmp);

void RotatePageToReal (void);// Piter

static int nQuantityOfOnes [256] =
{
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};

void FormOneRootString (int iRoot)
{
    StringNewDescriptor ();
    StringAddLetter1 (iRoot);
    pRoots [iRoot].bType |= ROOT_USED;

    StringCalculateParameters (&String);
    String.uFlags  |= SF_SPECIAL;

# ifdef SE_DEBUG
    if (SE_DebugGraphicsLevel >= 3)
        LT_GraphicsCurrentStringOutput ("One-root string");
# endif

    StringAddToList ();
}

BOOL IsInterStringsComponent (ROOT *pRoot)
{
    int yTop    = pRoot -> yRow;
    int yBottom = pRoot -> yRow + pRoot -> nHeight - 1;
    STRING *pString;
    int nHighestOwnStringTall = 0; /* To avoid warning under Mac */
    int nCrossings = 0;

    for (pString = pStringsList; pString != NULL; pString = pString -> pNext)
    {
        ROOT *pFirstRoot = & pRoots [pString -> pLettersList [0]];

        if (! (yBottom < pString -> yTop || yTop > pString -> yBottom) &&
               (pRoot == pFirstRoot ||
                pRoot -> xColumn + pRoot -> nWidth - 1 <=
                      pFirstRoot -> xColumn + pFirstRoot -> nWidth - 1))
        {
            nCrossings++;

            if (nCrossings == 1 ||
                pString -> yMiddleBottom - pString -> yMiddleTop + 1
                    > nHighestOwnStringTall)
            {
                nHighestOwnStringTall =
                    pString -> yMiddleBottom - pString -> yMiddleTop + 1;
            }
        }
    }

    if (nCrossings == 1 &&
        pRoot -> nHeight > nHighestOwnStringTall * 5 / 2)
    {
        return (TRUE);
    }

    if (nCrossings > 1 &&
        (pRoot -> bType & ROOT_RECOGNIZED) != 0 &&
        pRoot -> nHeight > nHighestOwnStringTall * 2)
    {
        return (TRUE);
    }

    return (FALSE);
}

BOOL IsGluedComponent (STRING *pString, ROOT *pRoot)
{
    STRING *pUp, *pDown;
    int yUpLine;
    int yDownLine;

    for (pUp = pString -> pUp;
             pUp != NULL && (pUp -> uFlags & SF_SPECIAL);
                 pUp = pUp -> pUp)
    {
    }

    for (pDown = pString -> pDown;
             pDown != NULL && (pDown -> uFlags & SF_SPECIAL);
                 pDown = pDown -> pDown)
    {
    }

    if (pUp != NULL)
    {
        yUpLine = (pUp -> yMiddleTop + pUp -> yMiddleBottom) / 2;
    }

    if (pDown != NULL)
    {
        yDownLine = (pDown -> yMiddleTop + pDown -> yMiddleBottom) / 2;
    }

    if (pUp != NULL &&
        pRoot -> yRow <= yUpLine
            &&
        ! (pUp -> xRight < pRoot -> xColumn - 2 * pRoot -> nWidth  /* SWEE1 */
           || pRoot -> xColumn + 3 * pRoot -> nWidth < pUp -> xLeft))
    {
        yRasterUpBreakLimit   = pUp     -> yMiddleBottom - pRoot -> yRow;
        yRasterDownBreakLimit = pString -> yMiddleTop    - pRoot -> yRow;
    }
    else if (pDown != NULL &&
             pRoot -> yRow + pRoot -> nHeight - 1 >= yDownLine
                 &&                                         /* SWEE1 */
             ! (pDown -> xRight < pRoot -> xColumn - 2 * pRoot -> nWidth
                || pRoot -> xColumn + 3 * pRoot -> nWidth < pDown -> xLeft))
    {
        yRasterUpBreakLimit   = pString -> yMiddleBottom - pRoot -> yRow;
        yRasterDownBreakLimit = pDown   -> yMiddleTop    - pRoot -> yRow;
    }
    else
    {
        return (FALSE);
    }

    return (TRUE);
}

void RasterHystogramBuild (void)
{
    int y, o, i;

    memset (aRasterHystogram, 0, sizeof (aRasterHystogram));

    for (y = 0, o = 0; y < nRasterHeight; y++, o += nRasterByteWidth)
    {
        for (i = 0; i < nRasterByteWidth; i++)
            aRasterHystogram [y] += nQuantityOfOnes [pRaster [o + i]];
    }
}

BOOL GluedLettersProcess (ROOT *pRoot)
{
    int oBreakLine, oAfterBreakLine;
    MN  *mn;
    CCOM_comp *pComp;
    ROOT *pPreviousAfterRoots = pAfterRoots;
	ROOT *pTmpRoot;
    INT  yRealRow, xRealColumn;
	int nMN = 0;
	//Word32 RootShift;

    if (pRoot -> nWidth  > EXTENDED_RASTER_MAX_WIDTH ||
        pRoot -> nHeight > EXTENDED_RASTER_MAX_HEIGHT)
    {
        return (FALSE);
    }

    REAL_XY (pRoot -> xColumn, pRoot -> yRow);

    yRealRow    = pRoot -> yRow;
    xRealColumn = pRoot -> xColumn;

    nRasterWidth     = pRoot -> nWidth;
    nRasterHeight    = pRoot -> nHeight;
    nRasterByteWidth = (nRasterWidth + 7) / 8;

    pComp = get_CCOM_comp (pRoot);

    if (pComp -> scale == 0)
    {
        //online_comp (pComp);
        //pRaster = make_raster ();
        pRaster = make_raster_CCOM( pComp);

    }
    else
    {
        //pRaster = make_extended_raster_CCOM (pComp);
        pRaster = make_extended_raster_CCOM( pComp );
    }

    IDEAL_XY (pRoot -> xColumn, pRoot -> yRow);

    RasterHystogramBuild ();

    yRasterBreakLine = (yRasterUpBreakLimit + yRasterDownBreakLimit) / 2;

    if (yRasterBreakLine > RASTER_MAX_HEIGHT ||
        nRasterHeight - yRasterBreakLine > RASTER_MAX_HEIGHT)
    {
        return (FALSE);
    }

# ifdef SE_DEBUG
    if (SE_DebugGraphicsLevel >= 1)
        LT_GraphicsBreakingOutput ("Glued component");
# endif

    oBreakLine      = yRasterBreakLine * nRasterByteWidth;
    oAfterBreakLine = (yRasterBreakLine + 1) * nRasterByteWidth;

    memset (pRaster + oBreakLine, 0, oAfterBreakLine - oBreakLine);
    mn = c_locomp (pRaster, nRasterByteWidth, nRasterHeight,
                   yRealRow     /* pRoot -> yRow    */,
                   xRealColumn  /* pRoot -> xColumn */);

    if (mn == NULL)
    {
        return (FALSE);
    }

	for (pTmpRoot = pCurrentBlock -> pRoots;
	(pTmpRoot -> u1.pNext != NULL)&&(pTmpRoot != NULL);
	pTmpRoot = pTmpRoot -> u1.pNext)
	{
	}


	//RootShift = (pRoots - pRoot)/sizeof(pRoot);
	//RootShift = pRoot - pRoots;
    for (; mn != NULL; mn = mn -> mnnext)
    {
        if( save_MN (mn) )
            {
		    CalculatePageParameters ();// Piter
		    RootStripsCalculate ();// Piter

			nMN++;
			IDEAL_XY ((pAfterRoots - 1)->xColumn, (pAfterRoots - 1)->yRow);
            (pAfterRoots - 1)-> nBlock = nCurrentBlock;

           }
    }
	//pRoot = pRoots + RootShift;

	CCOM_Delete(exthCCOM, pRoot->pComp);

	if (pCurrentBlock -> pRoots == pRoot)
	{
		//pTmpRoot = pRoot-> u1.pNext;
		pCurrentBlock -> pRoots = pRoot-> u1.pNext;
	}

	for (pTmpRoot = pCurrentBlock -> pRoots;
	     (pTmpRoot -> u1.pNext != NULL)&&(pTmpRoot != NULL);
		 pTmpRoot = pTmpRoot -> u1.pNext)
	{
			 if(pTmpRoot->u1.pNext == pTmpRoot)
			 {
				 pTmpRoot->u1.pNext = pTmpRoot->u1.pNext->u1.pNext;
			 }
	}


	/** It's right **/
	/*
	BlocksHystogramsFreeData ();// Piter
	BlocksAccessTableFree ();// Piter
    BlocksExtract (); // Piter
    BlocksAccessTableBuild ();// Piter
    BlocksHystogramsBuild ();// Piter
	pCurrentBlock = pBlockPointer [nCurrentBlock];
	/******************************/

	pPreviousAfterRoots = pAfterRoots - nMN;// Piter

    {
        ROOT *p;

        for (p = pPreviousAfterRoots; p < pAfterRoots; p++)
        {
            IDEAL_XY (p -> xColumn, p -> yRow);
            p -> bType |= ROOT_HORZ_BREAKED;
        }
    }

# ifdef SE_DEBUG
    if (SE_DebugGraphicsLevel >= 1)
    {
        ROOT *p;

        for (p = pPreviousAfterRoots; p < pAfterRoots; p++)
        {
            nRasterWidth     = p -> nWidth;
            nRasterHeight    = p -> nHeight;
            nRasterByteWidth = (nRasterWidth + 7) / 8;

            pComp = get_CCOM_comp (p);

            if (pComp -> scale == 0)
            {
                //online_comp (pComp);
                //pRaster = make_raster ();
                pRaster = make_raster_CCOM( pComp );
            }
            else
            {
                //pRaster = make_extended_raster (pComp);
                pRaster = make_raster_CCOM( pComp );
            }

            LT_GraphicsRasterOutput ("Cutted component");
        }
    }
# endif

    return (TRUE);
}

void AddAllCuttedComponentsToStrings (void)
{
    return;
/*
    ROOT *pRoot;
    STRING *pString;
    int yMiddleLine;

    for (pRoot = pOldAfterRoots; pRoot < pAfterRoots; pRoot++)
    {
        for (pString = pStringsList;
                 pString != NULL;
                     pString = pString -> pNext)
        {
            yMiddleLine = (pString -> yMiddleTop + pString -> yMiddleBottom)/2;

            if (yMiddleLine >= pRoot -> yRow &&
                yMiddleLine <= pRoot -> yRow + pRoot -> nHeight)
            {
                break;
            }
        }

        pString -> bNeedUpdate = TRUE;
    }
*/
}

void StringsProcessSpecials (void)
{
    STRING *pString;
    ROOT        *pRoot;
    int         i, j;
    int         nDeleted;
    BOOL        bSpecialsFounded = FALSE;

    nOldRoots      = nRoots;
    pOldAfterRoots = pAfterRoots;

    for (pString = pStringsUpList; pString != NULL; pString = pString -> pDown)
    {
		if (pCurrentBlock->nUserNum == IS_IN_TABLE)
		{
			continue;
		}

        if (pString -> nSpecialsLetters == 0 ||
            (pString -> uFlags & SF_SPECIAL))
        {
            continue;
        }

        bSpecialsFounded = TRUE;

        i = 0;
        j = 0;
        nDeleted = 0;

        pRoot = &pRoots [pString -> pLettersList [i]];

        if (  (pRoot -> bType & ROOT_SPECIAL_LETTER) &&
            ! (pRoot -> bType & ROOT_SPECIAL_DUST)   &&
            IsInterStringsComponent (pRoot))
        {
            pRoot -> bType &= ~ROOT_SPECIAL_LETTER;
            FormOneRootString (pString -> pLettersList [i]);
            i++;
            nDeleted++;
        }

        for (; i < pString -> nLetters; i++)
        {
            pRoot = &pRoots [pString -> pLettersList [i]];

            if (pRoot -> bType & ROOT_SPECIAL_DUST)
            {
                nDeleted++;
                pRoot -> bType &= ~(ROOT_SPECIAL_DUST | ROOT_USED);
                continue;
            }

            if ((pRoot -> bType & ROOT_SPECIAL_LETTER) &&
                IsGluedComponent (pString, pRoot))
            {
                GluedLettersProcess (pRoot);
                nDeleted++;
                continue;
            }

            pRoot -> bType &= ~ROOT_SPECIAL_LETTER;
            pString -> pLettersList [j++] = pString -> pLettersList [i];
        }

        pString -> nLetters    -= nDeleted;

        if (nDeleted != 0)
            pString -> uFlags |= SF_NEED_UPDATE;
    }

    if (bSpecialsFounded)
    {
        AddAllCuttedComponentsToStrings ();
        StringsListUpdate ();
    }
}
