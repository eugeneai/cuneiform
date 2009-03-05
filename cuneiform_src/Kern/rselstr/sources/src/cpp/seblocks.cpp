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
 *              S T R I N G S   E X T R A C T I O N                         *
 *                                                                          *
 *              Written in 1991 by Yuri Panchul                             *
 *                                                                          *
 *              SEBLOCKS.C                                                  *
 *                                                                          *
 ***************************************************************************/

# include "extract.h"
# include "c_memory.h"
# include "my_mem.h"


BLOCK **pBlockPointer = NULL;
int nBlocks;
int nMinBlock;
int nMaxBlock;
int nCurrentBlock;
BLOCK *pCurrentBlock;

void BlocksAccessTableBuild (void)
{
    DWORD i(0);
	INT w(0);
    BLOCK *p;

	int PrevMin, CurrMin;
	int  AllBlocksIsDone;
	long BlockNumber;

    nMinBlock = 0;
    nMaxBlock = 0;

    for (i = 0; i < nRoots; i++)
    {
        w = pRoots[i].nBlock;
        if ((w != DUST_BLOCK_NUMBER) && (w != REMOVED_BLOCK_NUMBER ))
        {
            if (w < nMinBlock || nMinBlock == 0)
                nMinBlock = w;

            if (w > nMaxBlock || nMaxBlock == 0)
                nMaxBlock = w;
        }
    }

    if (nMinBlock == 0 || nMaxBlock == 0)
        ErrorInternal ((PSTR)"No blocks");

    nBlocks = nMaxBlock + 1;
    pBlockPointer =(BLOCK**) malloc (nBlocks * sizeof (BLOCK *));

    if (pBlockPointer == NULL)
        ErrorNoEnoughMemory ((Word8*)"in SEBLOCKS.C,BlocksAccessTableBuild,part 1");

    memset (pBlockPointer, 0, nBlocks * sizeof (BLOCK *));

	//*********************************** Rom
	PrevMin = 0;
	AllBlocksIsDone = FALSE;
	while(!AllBlocksIsDone)
	{
		CurrMin = 32000;
		AllBlocksIsDone = TRUE;
		for (p = pBlocksList; p != NULL; p = p -> pNext)
		{
			BlockNumber = p->nUserNum;
			if((BlockNumber>PrevMin)&&(BlockNumber<CurrMin))
			{
				CurrMin = BlockNumber;
				AllBlocksIsDone = FALSE;
			}
		}
		PrevMin = CurrMin;


		for (p = pBlocksList; p != NULL; p = p -> pNext)
		{
			if ((p -> Type == BLOCK_TEXT)&&(p->nUserNum == CurrMin))
				pBlockPointer [p -> nNumber] = p;
		}
	}
	//*******************************************************
}

void BlocksAccessTableFree (void)
{
    if (pBlockPointer != NULL)
    {
        free (pBlockPointer);
        pBlockPointer = NULL;
    }
}
