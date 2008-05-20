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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "c_types.h"
#include "func.h"
#include "ccom.h"
#include "exc.h"
#include "loc.h"

#define CREATE_STATUS
#include "status.h"

#include "dpuma.h"
#include "newfunc.h"

#include "layout.h"

extern INT nIncline;

PROOT root_file = NULL;
WORD run_options = 0;


DWORD progress_set_percent (DWORD volume)
{
	DWORD rc = 0;
	if(fnProgressStep_rsel)
		rc  = !fnProgressStep_rsel(volume);
	return rc;
};
void progress_finish(void)
{
	if(fnProgressFinish_rsel)
		fnProgressFinish_rsel();
};

#undef malloc
#undef realloc
#undef free

void * DebugMalloc(size_t size)
{
	char * buf = (char*)malloc(size);
	return buf;
};
void * DebugRealloc(void * old_blk,size_t size)
{
	char *buf = (char*)realloc(old_blk,size);
	return buf;
};
void   DebugFree(void * p)
{
	free(p);
};

void * TigerAllocateMemory(DWORD size)
{
	return DebugMalloc(size);
};
void TigerFreeMemory(void * mem)
{
	DebugFree(mem);
};
void * TigerReallocateMemory(void * mem,DWORD size)
{
	return DebugRealloc(mem,size);
};


extern BYTE work_raster[], work_raster_1[];
extern WORD lpool_lth;
extern BYTE lpool[];
static BYTE make_fill[] = {0, 1, 3, 7, 15, 31, 63, 127, 255};
static  INT comp_max_w=128,comp_min_w=0, comp_max_h=64,comp_min_h=0;
MN * c_locomp (PBYTE raster, INT bw, INT h, INT upper, INT left)
{
return LOC_CLocomp (raster, bw, h, upper, left); 
}


PBYTE make_raster_CCOM(CCOM_comp *cmp)
{
INT    h,d,dd,k,i,ii;
RecRaster  rs;

memset(work_raster,0,cmp->rw*cmp->h);
CCOM_GetRaster(cmp, &rs);
h  = rs.lnPixHeight;
d  = REC_GW_WORD8(rs.lnPixWidth); // align to 8 bytes in RecRaster
dd = (rs.lnPixWidth+7)/8;         // aling to 1 byte  in standart
for(k=ii=i=0;k<h;k++,i+=d,ii+=dd)
    {
    memcpy( &work_raster[ii],&rs.Raster[i],dd);
    }
 
return work_raster;
}


PBYTE make_extended_raster_CCOM(CCOM_comp *cmp)
{
INT    h,d,dd,k,i,ii;
RecRaster  rs;

memset(work_raster,0,cmp->rw*cmp->h);
CCOM_GetExtRaster(cmp, &rs);
h  = rs.lnPixHeight;
d  = REC_GW_WORD8(rs.lnPixWidth); // align to 8 bytes in RecRaster
dd = (rs.lnPixWidth+7)/8;         // aling to 1 byte  in standart
for(k=ii=i=0;k<h;k++,i+=d,ii+=dd)
    {
    memcpy( &work_raster[ii],&rs.Raster[i],dd);
    }
 
return work_raster;
}

/* FIXME: PROOT does not have a pComp. Don't know what should be done, so
 * I disabled this.
*/
CCOM_comp *get_CCOM_comp(PROOT r)
{
	/*return (CCOM_comp *)r->pComp;*/ 
    printf("ERROR: get_CCOM_comp (rselstr) was called. Now is the time to fix this bug.");
    exit(1);
}

BOOL save_MN(MN *mn)
{
extern Int32 exthCCOM; 
CCOM_comp * p=REXC_MN2CCOM((Handle)exthCCOM,(Handle)mn);
if( !p )
    return FALSE;

if(!AddRoot(p, FALSE))
    return FALSE;

BlockAccountRoot(pCurrentBlock, &pRoots[nRoots-1]);
return TRUE;
}
