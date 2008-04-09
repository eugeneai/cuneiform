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

#include<malloc.h>
#include<stdio.h>
#include<string.h>

#include "cstr.h"
#include "ccom.h"
#include "rpstr.h"
#include "resource.h"
#include "dpuma.h"
#include "cor_incl.h"
#include "cap_drop.h"
#include "ligas.h"	// 12.06.2002 E.P.

//#include "myrpstr.h"

#define  MAX_KEG    40
#define  KEG_RANGE  34
Word16              wHeightRC      = 0;
Word16              wLowRC         = RPSTR_ERR_NO;
Bool32      snap_enable = TRUE;
Bool32      exit_enable = FALSE, skip_line=FALSE;;
Handle      hSnapSpell = 0,hSnapWordSpell = 0,hSnapMatch = 0, hSnapCapDrop = 0;
Handle      hSnapEndWord=NULL,hSnapStartWord=NULL;
Handle      hVertCompD;
Bool32      gbFax100 = FALSE;
Bool32      gbGarbage = TRUE;
Int8*       sp_err="no spell errors";
// from COR_SPEL.C
Bool32 correct_line_spell(CSTR_line line, CSTR_rast* re, CSTR_rast* rb, Int32 line_num, 
						  Bool32 disable_new_dict, Bool32 disable_check_word, Int32* rf);

extern Bool32   rpstr_correct_spell(CSTR_line ln,
    CSTR_rast *addbeg, CSTR_rast *addend, Int32 *linefrag,
    Int32 num_ln,Bool32 disable_new_dict, Bool32 disable_check_word);
extern Bool32 rpstr_txt_spell(char * s,Word8 lang);

extern int Snap_Console(char *text);;
extern Word8    language=3;

static Word8   s_lang4page = -1;

static Word8 set_lang4page(const Word8 lang)
{
   s_lang4page = lang;
   return s_lang4page;
}

static Word8 get_lang4page()
{
   return s_lang4page;
}

// memory funct
static void *   rpstr_alloc(Word32 len)
    {
    void *ma = malloc(len);
    if( !ma )
        return NULL;
    memset(ma,0,len);
    return ma;
    }
static void     rpstr_free(void *ptr,Word32 len) { free(ptr);};
static void *   rpstr_realloc(void *ptr,Word32 len) { return realloc(ptr,len);};
static void * (*my_alloc)(Word32 len)=rpstr_alloc;
static void   (*my_free)(void *,Word32 len)=rpstr_free;
static void * (*my_realloc)(void *,Word32 len)=rpstr_realloc;



static void show_spell(CSTR_rast c)
{
Word8   wrd[80],buf[160],*w=wrd, lang;
Bool32  nonrec=FALSE;
CSTR_rast_attr  attr;
UniVersions     uni;
CSTR_rast       co=c;
*w=0;
do{
    CSTR_GetAttr(c, &attr);
    c=CSTR_GetPrev(c);
    }
    while( c && attr.flg&(CSTR_f_let|CSTR_f_bad) );
if( !c )
    c=CSTR_GetNext(CSTR_GetFirstRaster(CSTR_GetRasterLine(co)));
else
    c=CSTR_GetNext(CSTR_GetNext(c));
CSTR_GetAttr(c,&attr);
for(lang=attr.language;c;c=CSTR_GetNext(c))
    {
    CSTR_GetAttr(c,&attr);
    if(!(attr.flg&(CSTR_f_let|CSTR_f_bad)) )
        break;
    if( attr.flg&CSTR_f_bad )
        nonrec=TRUE;
    CSTR_GetCollectionUni(c,&uni);
    strcat(w,uni.Alt[0].Code);
    }

strcpy(buf,"<");
strcat(buf,wrd);
strcat(buf,"> static : ");
if( rpstr_txt_spell(wrd,lang)        )
    strcat(buf,"y");
else
    strcat(buf," n");
Snap_Console(buf);
return;
}

Word32 myMonitorProc(Handle wnd,Handle hwnd,Word32 message,Word32 wParam,Word32 lParam)
{
int             ret=0;
Word32          pos;
CSTR_rast       r=(CSTR_rast)0;
CSTR_rast_attr  attr;

pos=LDPUMA_CSTR_GetPosition((int *)&r);

if (!is_turkish_language(language)) // 12.06.2002 E.P.
	language=3;

switch(message)
	{
    // ALT + KEY
    case WM_SYSKEYDOWN:
        switch((int)wParam)
        {
        case    'X':    // ALT + X
            exit_enable=TRUE;
            ret=-1;
            break;
        case    'S':
            if( r )
                {
                CSTR_GetAttr(r,&attr);
                if( attr.flg&(CSTR_f_bad|CSTR_f_let) )
                    show_spell(r);
                else
                    Snap_Console("�� �����");
                ret=1;
                }
            break;
        default:
            break;
        }
    break;
    // KEYS
	case WM_KEYDOWN:

		switch((int)wParam)
		{
        case    VK_ESCAPE:
            snap_enable = FALSE;
            Snap_Console("����������� �� �����");
            ret=-1;
            break;
        case    VK_RETURN:
        case    VK_SPACE:
            ret=-1;
            break;
        case    VK_F1:
            Snap_Console("ESC - �� ����� ��� �����");
            Snap_Console("F1  - �������");
            Snap_Console("F2  - ����� ������");
            Snap_Console("Alt+F  - ������ FRH");
            Snap_Console("Alt+S  - �������");
            Snap_Console("Alt+X  - ��������");
            Snap_Console("Home/End - ������/����� ������");
            Snap_Console("+/- - ���������/��������� �����");
            break;
        case    VK_F2:
            skip_line=TRUE;
            ret=-1;
            break;
        default:
            break;
        }
		break;
	}

return (Word32)(ret);
}

/////////////////////
// common functions
/////////////////////
//void kegl_snap_init();

RPSTR_FUNC(Bool32)  RPSTR_Init( Word16 wHeightCode , Handle hStorage)
{
wHeightRC = wHeightCode;
wLowRC    = RPSTR_ERR_NO;
snap_enable = TRUE;
exit_enable = FALSE;
LDPUMA_Init(0,NULL);
//kegl_snap_init();
LDPUMA_Registry(&hSnapSpell,"������� � �������������",NULL);
LDPUMA_RegistryHelp(hSnapSpell,"�������",FALSE);
LDPUMA_Registry(&hSnapWordSpell,"��������� �������� �������",hSnapSpell);
LDPUMA_Registry(&hSnapMatch,"�������� �������� �������",hSnapWordSpell);
LDPUMA_RegistryHelp(hSnapWordSpell,"��������� �������� �������",FALSE);
LDPUMA_Registry(&hSnapCapDrop,"��������� ��������� ������",hSnapSpell);
LDPUMA_RegistryHelp(hSnapCapDrop,"��������� ��������� ������",FALSE);

LDPUMA_Registry(&hSnapEndWord,"�������� �������� ���������",hSnapSpell);
LDPUMA_RegistryHelp(hSnapEndWord,"��������� ��� ��� ����� ������ ���������",FALSE);
LDPUMA_Registry(&hSnapStartWord,"�������� ������������ � ������",hSnapSpell);
LDPUMA_RegistryHelp(hSnapStartWord,"���������� ��� ��� ��������� �� ����� �������",FALSE);

LDPUMA_Registry(&hVertCompD,"���������� ���� � ������������ �������!",NULL);
LDPUMA_RegistryHelp(hVertCompD,"��������� ���������� ���� � ������������ �������",FALSE);
return TRUE;
}


RPSTR_FUNC(void)    RPSTR_Done(void)
{
wLowRC    = RPSTR_ERR_NO;
wHeightRC = 0;
snap_enable = TRUE;
exit_enable = FALSE;
LDPUMA_Done();
return;
}


RPSTR_FUNC(Word32)   RPSTR_GetReturnCode(void)
{
if( wLowRC == RPSTR_ERR_NO )
    return 0;
return (wHeightRC<<16)|(wLowRC-RPSTR_ERR_MIN);
}

RPSTR_FUNC(char*)   RPSTR_GetReturnString(Word32 dwError)
{
  Word16 rc = (Word16)(dwError & 0xFFFF + RPSTR_ERR_MIN);
	static char szBuffer[512];

	if( dwError >> 16 != wHeightRC)
    wLowRC = RPSTR_ERR_NOTIMPLEMENT;

  if( rc > 0 && rc <= RPSTR_ERR_MAX-RPSTR_ERR_MIN  )
    strcpy((char *)szBuffer,RPSTR_error_name [rc]);
	else
		return NULL;

	return szBuffer;
}

RPSTR_FUNC(Bool32) RPSTR_NewPage(void)
{
wLowRC    = RPSTR_ERR_NO;
snap_enable = TRUE;
exit_enable = FALSE;
return TRUE;
}

//Bool32 CorrectKegl(Int32 version);

//RPSTR_FUNC(Bool32) RPSTR_CorrectKegl(Int32 version)
//{
//  return CorrectKegl(version);
//}



RPSTR_FUNC(Bool32) RPSTR_CorrectIncline(Int32 version)
{
Int32   n=CSTR_GetMaxFragment(version),i;
for(i=0;i<=n;i++)
    {
    if( !incl_test_fragment(version,i) )
        {
        incl_ordering(version,i,incl_calculate(version,i));
        }
    }
return TRUE;
}

Bool32 correct_line_spell(CSTR_line line, CSTR_rast* re, CSTR_rast* rb, Int32 line_num, 
						  Bool32 disable_new_dict, Bool32 disable_check_word, Int32* rf)
{
	char            snapstr[256];
//	CSTR_attr       lattr;

	exit_enable = FALSE;
	snap_enable=TRUE;
	skip_line=FALSE;

//    CSTR_GetLineAttr(line,&lattr);
//    if( !(lattr.Flags & CSTR_STR_CapDrop) )
    if( !LDPUMA_SkipEx(hSnapSpell,TRUE,TRUE,1) && snap_enable )
        {
        sprintf(snapstr,"before spelling line %d",line_num);
        Snap_Console(snapstr);
        LDPUMA_RasterText("before spelling");
        LDPUMA_CSTR_Monitor(hSnapSpell,line,0,myMonitorProc);

        if( exit_enable )
            {
            LDPUMA_DestroyRasterWnd();
            return FALSE;
            }
        }

    if( !rpstr_correct_spell(line,rb, re, rf,line_num,disable_new_dict, disable_check_word) )
        {
        sprintf("speller error : %s ",sp_err);
        Snap_Console(snapstr);
        LDPUMA_DestroyRasterWnd();
        return FALSE;
        }
    if( !skip_line && !LDPUMA_SkipEx(hSnapSpell,TRUE,TRUE,1) && snap_enable )
        {
        sprintf(snapstr,"after spelling line %d",line_num);
        Snap_Console(snapstr);
        LDPUMA_RasterText("after spelling");
        LDPUMA_CSTR_Monitor(hSnapSpell,line,0,myMonitorProc);
        }
    if( exit_enable )
        {
        LDPUMA_DestroyRasterWnd();
        return FALSE;
        }

	return TRUE;
}

RPSTR_FUNC(Bool32) RPSTR_CorrectLineSpell(CSTR_line line, Int32 line_num, CSTR_rast* re, CSTR_rast* rb, Int32* rf)
{
//	CSTR_rast re=(CSTR_rast)0;
//	CSTR_rast rb=(CSTR_rast)0;
//	Int32 rf = -1;
	Bool32 disable_new_dict=FALSE, disable_check_word=FALSE;

	exit_enable = FALSE;
	snap_enable=TRUE;
	skip_line=FALSE;

	// 12.06.2002 E.P.
	if (is_turkish_language(language))
		disable_new_dict = TRUE;

//	if (!correct_line_spell(line, &re, &rb, line_num, disable_new_dict, disable_check_word, &rf))
	if (!correct_line_spell(line, re, rb, line_num, disable_new_dict, disable_check_word, rf))
		return FALSE;
/*
	if( re )
    {
		CSTR_rast_attr  attr;
		CSTR_GetAttr(re,&attr);
		attr.flg_spell |= CSTR_fa_spell_nocarrying;
		CSTR_SetAttr(re,&attr);
    }
*/
	if( !LDPUMA_SkipEx(hSnapSpell,TRUE,TRUE,1) )
		LDPUMA_DestroyRasterWnd();

	return TRUE;
}

RPSTR_FUNC(Bool32) RPSTR_CorrectSpell(Int32 version)
{
Int32           n,  i, rf=-1;
CSTR_line       line;
//char            snapstr[256];
CSTR_rast       rb=(CSTR_rast)0, re=(CSTR_rast)0;
Bool32          disable_new_dict=FALSE, disable_check_word=FALSE;
//CSTR_attr       lattr;

exit_enable = FALSE;
snap_enable=TRUE;
skip_line=FALSE;
n=CSTR_GetMaxNumber ();

// 12.06.2002 E.P.
if (is_turkish_language(language))
	disable_new_dict = TRUE;

LDPUMA_StartLoop( hSnapSpell, n );
for(i=1;i<=n;i++)
    {
	LDPUMA_LoopNext( hSnapSpell );
    line = CSTR_GetLineHandle (i, version);
    if( !line )
        continue;
    skip_line=FALSE;

	if (!correct_line_spell(line, &re, &rb, i, disable_new_dict, disable_check_word, &rf))
		return FALSE;

/*  �������� � ������� correct_line_spell

	CSTR_GetLineAttr(line,&lattr);
//    if( !(lattr.Flags & CSTR_STR_CapDrop) )
    if( !LDPUMA_SkipEx(hSnapSpell,TRUE,TRUE,1) && snap_enable )
        {
        sprintf(snapstr,"before spelling line %d",i);
        Snap_Console(snapstr);
        LDPUMA_RasterText("before spelling");
        LDPUMA_CSTR_Monitor(hSnapSpell,line,0,myMonitorProc);

        if( exit_enable )
            {
            LDPUMA_DestroyRasterWnd();
            return FALSE;
            }
        }


    if( !rpstr_correct_spell(line,&rb,&re,&rf,i,disable_new_dict, disable_check_word) )
        {
        sprintf("speller error : %s ",sp_err);
        Snap_Console(snapstr);
        LDPUMA_DestroyRasterWnd();
        return FALSE;
        }
    if( !skip_line && !LDPUMA_SkipEx(hSnapSpell,TRUE,TRUE,1) && snap_enable )
        {
        sprintf(snapstr,"after spelling line %d",i);
        Snap_Console(snapstr);
        LDPUMA_RasterText("after spelling");
        LDPUMA_CSTR_Monitor(hSnapSpell,line,0,myMonitorProc);
        }
    if( exit_enable )
        {
        LDPUMA_DestroyRasterWnd();
        return FALSE;
        }
*/
    }

if( re )
    {
    CSTR_rast_attr  attr;
    CSTR_GetAttr(re,&attr);
    attr.flg_spell |= CSTR_fa_spell_nocarrying;
    CSTR_SetAttr(re,&attr);
    }
if( !LDPUMA_SkipEx(hSnapSpell,TRUE,TRUE,1) )
    LDPUMA_DestroyRasterWnd();
return TRUE;
}

RPSTR_FUNC(Bool32) RPSTR_CollectCapDrops(Int32 version)
{
Int32   n=CSTR_GetMaxFragment(version),i;
CSTR_line   ln_cd, ln_main;
if( !LDPUMA_SkipEx(hSnapCapDrop,FALSE,FALSE,0)  )
    return FALSE;
for(i=0;i<=n;i++)
    {
    if( capdrop_test_fragment(version,i,&ln_cd,&ln_main) )
        {
        capdrop_collection(version,i,ln_cd,ln_main);
        }
    }
return TRUE;
}

RPSTR_FUNC(Bool32) RPSTR_GetExportData(Word32 dwType, void * pData)
{
	Bool32 rc = TRUE;
  #define RPSTR_VERSION_CODE 1
    Int32  vers = RPSTR_VERSION_CODE;
#define EXPORT(name) *(Word32*)(pData)=(Word32)name;
  wLowRC = RPSTR_ERR_NO;
	switch(dwType)
	{
//    case    RPSTR_FNCORRECTKEGL: //      post correction kegl
//        EXPORT(RPSTR_CorrectKegl );
//        break;
    case    RPSTR_FNNEWPAGE:    //      init new page
        EXPORT(RPSTR_NewPage);
        break;
    case    RPSTR_FNCORRECTSPELL:    //      init new page
        EXPORT(RPSTR_CorrectSpell);
        break;
    case    RPSTR_FNCORRECTLINESPELL:
        EXPORT(RPSTR_CorrectLineSpell);
        break;
    case    RPSTR_FNCORRECTINCLINE:
        EXPORT(RPSTR_CorrectIncline);
        break;
    case    RPSTR_FNCOLLECTCAPDROP:
        EXPORT( RPSTR_CollectCapDrops);
        break;
    case    RPSTR_FNNORMVERTSTR:
        EXPORT( RPSTR_NormalizeVertStr);
        break;

    default:
        wLowRC = RPSTR_ERR_NOTIMPLEMENT;
        rc = FALSE;
        break;
	}
#undef EXPORT
return rc;
}

RPSTR_FUNC(Bool32) RPSTR_SetImportData(Word32 dwType, void * pData)
{

  wLowRC = RPSTR_ERR_NO;
#define CASE_DATA(a,b,c)	case a: c = *(b *)pData; break
#define CASE_PDATA(a,b,c)	case a: c = (b)pData; break
	switch(dwType)
	{
	CASE_DATA(RPSTR_Bool32_Fax100,Bool32,gbFax100);
    case    RPSTR_FNIMP_ALLOC:
        my_alloc=pData;
        break;
    case    RPSTR_FNIMP_REALLOC:
        my_realloc=pData;
        break;
    case    RPSTR_FNIMP_FREE:
        my_free=pData;
        break;

	// 12.06.2002 E.P.
    case    RPSTR_FNIMP_LANGUAGE:
        language=*(Word8*)pData;
        set_lang4page(language);
        break;

#undef CASE_DATA
#undef CASE_PDATA

	default:
    wLowRC = RPSTR_ERR_NOTIMPLEMENT;
		return FALSE;
	}
return TRUE;
}


