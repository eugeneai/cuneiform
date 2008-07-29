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

#include    <string.h>
#include "cstr.h"
#include "ccom.h"
#include "cap_drop.h"
#include "lang_def.h"
#define SS_NEG_HALF_SPACE 0x1e
#define SS_POS_HALF_SPACE 0x1f

CSTR_line capdrop_get_main(CSTR_line ln,CSTR_line  linef)
{
CCOM_comp       *cmp=0;
CSTR_rast       rst=0;
CCOM_USER_BLOCK ub;
Int32           num_ln,i;
CSTR_line       line;

rst= CSTR_GetNext(CSTR_GetFirstRaster(ln));
if( rst )
    cmp=CSTR_GetComp(rst);
if( cmp )
    {
    ub.code=CCOM_UB_CAPDROPLN;
    if( CCOM_GetUserBlock(cmp,&ub) && ub.size==sizeof(num_ln) )
        {
        memcpy(&num_ln,ub.data,ub.size);
        if( num_ln>=0 )
            {
            for(line=linef,i=0; line; i++,line = CSTR_NextLineFragm(line))
                {
                if( i==num_ln )
                    break;
                }
            }
        else
            {
            for(line=linef,i=0; line; i++,line = CSTR_NextLineFragm(line))
                {
                if( line!=num_ln )
                    break;
                }
            }
        return line;
        }
    }
return (CSTR_line)0;
}

Bool32	capdrop_test_fragment(Int32 version,Int32 fragm,CSTR_line *ln_cd,CSTR_line *ln_main)
{
CSTR_line   line, linef;
CSTR_attr   attr;

linef = line = CSTR_FirstLineFragm( fragm, version );
CSTR_GetLineAttr(line,&attr);
if( attr.Flags & CSTR_STR_CapDrop )
    {
    *ln_cd=line;
    *ln_main=capdrop_get_main(line,linef);
    if( !(*ln_main) )
        *ln_main = linef;
    return TRUE;
    }
do
    {
    line = CSTR_NextLineFragm(line);
    if( line )
        {
        CSTR_GetLineAttr(line,&attr);
        if( attr.Flags & CSTR_STR_CapDrop )
            {
            *ln_cd=line;
            *ln_main=capdrop_get_main(line,linef);
            if( !(*ln_main) )
            *ln_main = linef;
            return TRUE;
            }
        }
    }while( line );
return FALSE;
}

Word8   eng_let[]       =   "ETYOPAHKXCBM";
Word8   rus_let[]       =   "������������";
Word8   rus_let_ascii[] =   "������������";
void	capdrop_collection(Int32 version,Int32 i,CSTR_line ln_cd,CSTR_line ln_main)
{
CSTR_rast       mrst, crst;
CSTR_rast_attr  attr;
CSTR_attr       lattr;
CCOM_comp    *  comp;
RecRaster       rs;
UniVersions     uvr;

crst = CSTR_GetNext(CSTR_GetFirstRaster(ln_cd));
if( crst )
    {
    mrst = CSTR_GetFirstRaster(ln_main); // fict
    CSTR_GetLineAttr(ln_main,&lattr);
    mrst=CSTR_InsertRaster(mrst);
    if( mrst )
        {
        CSTR_GetAttr(crst,&attr);
        if( CSTR_GetImage (crst, (Word8 *)(&rs), CSTR_TYPE_IMAGE_RS) )
            {
            CSTR_GetCollectionUni(crst,&uvr) ;
            comp=CSTR_GetComp(crst);
            // store CapDrop to main line
            CSTR_SetAttr(mrst,&attr);
            CSTR_StoreCollectionUni(mrst,&uvr);
            CSTR_StoreRaster (mrst, &rs);
            CSTR_StoreScale(mrst,comp->scale);

            mrst=CSTR_InsertRaster(mrst);
            uvr.lnAltCnt=1;
            uvr.Alt[0].Code[0]=0;
            uvr.Alt[0].Liga=SS_POS_HALF_SPACE;
            uvr.Alt[0].Prob=150;
            CSTR_StoreCollectionUni(mrst,&uvr);
            CSTR_GetAttr(mrst,&attr);
            attr.flg|=CSTR_f_space;
            CSTR_SetAttr(mrst,&attr);
            // signing main line
            lattr.Flags |= CSTR_STR_CapDrop;
            CSTR_SetLineAttr(ln_main,&lattr);
            // clear alone CapDrop
            CSTR_ClearLine(ln_cd,-16000,32000);
            CSTR_GetLineAttr(ln_cd,&lattr);
            lattr.Flags -= CSTR_STR_CapDrop;
            CSTR_SetLineAttr(ln_cd,&lattr);
            }
        }
    }

return;
}
