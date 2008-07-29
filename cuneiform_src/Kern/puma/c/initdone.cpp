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
#include <stdio.h>
#include <string.h>

#define __FRHSTRUC_H

#include "mpuma.h"

Bool32 ModulesInit(Handle  ghStorage)
{
	// CONTEINERS
	if(!CLINE_Init(PUMA_MODULE_CLINE,NULL))
	{
		SetReturnCode_puma(CLINE_GetReturnCode());
		goto lError;
	}
	if(!CFIO_Init(PUMA_MODULE_CFIO,NULL))
	{
		SetReturnCode_puma(CFIO_GetReturnCode());
		goto lError;
	}
	/*
	ghStorage = OpenStorage(szStorage,OS_CREATE);
	if(ghStorage==NULL)
	{
		SetReturnCode_puma(IDS_ERR_CREATESTORAGE);
		goto lError;
	}
	*/
	if(!CIMAGE_Init(PUMA_MODULE_CIMAGE,NULL))
	{
		SetReturnCode_puma(CIMAGE_GetReturnCode());
		goto lError;
	}
	if(!CCOM_Init(PUMA_MODULE_CCOM,NULL))   //  ����� ������������� ���������� CCOM �����
	{               //  ������� ������ ���������
		SetReturnCode_puma(CCOM_GetReturnCode());
		goto lError;
	}
	if(!CPAGE_Init(PUMA_MODULE_CPAGE,ghStorage))
	{
		SetReturnCode_puma(CPAGE_GetReturnCode());
		goto lError;
	}
	if(!CSTR_Init(PUMA_MODULE_CSTR,ghStorage))
	{
		SetReturnCode_puma(CSTR_GetReturnCode());
		goto lError;
	}
	// RECOGNITIONS
	if(!REXC_Init(PUMA_MODULE_REXC,NULL)) // ������������� ���������� ������ ���������
	{
		SetReturnCode_puma(REXC_GetReturnCode());
		goto lError;
	}
//	REXC_SetImportData(REXC_OcrPath, GetModulePath());
	if(!RLINE_Init(PUMA_MODULE_RLINE,ghStorage))
	{
		SetReturnCode_puma(RLINE_GetReturnCode());
		goto lError;
	}

    if(!RRECCOM_Init(PUMA_MODULE_RRECCOM,ghStorage))
	{
 		SetReturnCode_puma(RRECCOM_GetReturnCode());
		goto lError;
	}
	RRECCOM_SetImportData(RRECCOM_OcrPath, GetModulePath());

    if(!RSL_Init(PUMA_MODULE_RSL,ghStorage))
	{
 		SetReturnCode_puma(RSL_GetReturnCode());
		goto lError;
	}
	if(!RSTUFF_Init(PUMA_MODULE_RSTUFF,ghStorage))
	{
		SetReturnCode_puma(RSTUFF_GetReturnCode());
		goto lError;
	}
	if(!RMARKER_Init(PUMA_MODULE_RBLOCK,ghStorage))
	{
 		SetReturnCode_puma(RMARKER_GetReturnCode());
		goto lError;
	}
	if(!RBLOCK_Init(PUMA_MODULE_RBLOCK,ghStorage))
	{
		SetReturnCode_puma(RBLOCK_GetReturnCode());
		goto lError;
	}
	if(!RSELSTR_Init(PUMA_MODULE_RBLOCK,ghStorage))
	{
		SetReturnCode_puma(RSELSTR_GetReturnCode());
		goto lError;
	}
    RSTR_SetImportData(RSTR_OcrPath, GetModulePath());
	RSTR_SetImportData(RSTR_pchar_temp_dir, GetModuleTempPath());
	if(!RSTR_Init(PUMA_MODULE_RSTR,ghStorage))
	{
		SetReturnCode_puma(RSTR_GetReturnCode());
		goto lError;
	}

	if(!RFRMT_Init(PUMA_MODULE_RFRMT,ghStorage))
	{
		SetReturnCode_puma(RFRMT_GetReturnCode());
		goto lError;
	}
	if(!RIMAGE_Init(PUMA_MODULE_RIMAGE,ghStorage))
	{
		SetReturnCode_puma(RIMAGE_GetReturnCode());
		goto lError;
	}
	// �������������� ����������� �������
	if(!RPSTR_Init(PUMA_MODULE_RPSTR,ghStorage))
	{
		SetReturnCode_puma(RPSTR_GetReturnCode());
		goto lError;
	}
	if(!RPIC_Init(PUMA_MODULE_RPIC,ghStorage))
	{
		SetReturnCode_puma(RPIC_GetReturnCode());
		goto lError;
	}
	if(!CED_Init(PUMA_MODULE_CED,ghStorage))
	{
		SetReturnCode_puma(CED_GetReturnCode());
		goto lError;
	}
	if(!ROUT_Init(PUMA_MODULE_ROUT,ghStorage))
	{
		SetReturnCode_puma(ROUT_GetReturnCode());
		goto lError;
	}
	else
	{
		char szRec6AllFilename[260];
		//strcpy(szRec6AllFilename,GetModulePath()); JussiP: disabled this old path function thingy.
		strcpy(szRec6AllFilename,"rec6all.dat");
		if(!ROUT_LoadRec6List(szRec6AllFilename))
		{
			SetReturnCode_puma(ROUT_GetReturnCode());
			goto lError;
		}
	}

#ifdef _USE_RVERLINE_
	if(!RVERLINE_Init(PUMA_MODULE_RVERLINE,ghStorage))
	{
		SetReturnCode_puma(RVERLINE_GetReturnCode());
		goto lError;
	}
#endif //_USE_RVERLINE_

#ifdef _USE_RMSEGMENT_
	if(!RMSEGMENT_Init(PUMA_MODULE_RMSEGMENT,ghStorage))
	{
		SetReturnCode_puma(RMSEGMENT_GetReturnCode());
		goto lError;
	}
#endif //_USE_RMSEGMENT_

	if(!RCORRKEGL_Init(PUMA_MODULE_RCORRKEGL,ghStorage))
	{
		goto lError;
	}
//#ifdef _DEBUG

	My_SJTL_Init();
	if( !LDPUMA_Skip(hDebugEnableSaveJtl) )
	{
		My_SJTL_open("one.frm", "one.jtl");
	}
/* FIXME: could not figure out what to do with this in Linux, so disabled it.
	_CrtMemCheckpoint( &g_dbgMemState );
*/
//#endif
return TRUE;
lError:
		ModulesDone(ghStorage);
return FALSE;
}
//////////////////////////////////////////
Bool32 ModulesDone(Handle  ghStorage)
{
	Bool32 rc = TRUE;

	ROUT_Done();
	CED_Done();
//#ifdef _DEBUG
if( !LDPUMA_Skip(hDebugEnableSaveJtl) )
{
    My_SJTL_close();
}
//#endif
	My_SJTL_Done();
	RCORRKEGL_Done();
	RPIC_Done();
	RIMAGE_Done();
	RFRMT_Done();
	RSL_Done();
    REXC_Done();
	RLINE_Done();
	RMARKER_Done();
	RBLOCK_Done();
	RSELSTR_Done();
	RSTR_Done();
	CSTR_Done();
	CCOM_Done();
	CPAGE_Done();
	CIMAGE_Done();
	CLINE_Done();
	RPSTR_Done();
	RSTUFF_Done();
	RRECCOM_Done();

#ifdef _USE_RVERLINE_
	RVERLINE_Done();
#endif //_USE_RVERLINE_

#ifdef _USE_RMSEGMENT_
	RMSEGMENT_Done();
#endif //_USE_RMSEGMENT_

/*
	if(ghStorage)
		CloseStorage(ghStorage,CS_ALL);
		*/
	CFIO_Done();
	return rc;
}
//////////////////////////////////////////
#ifdef _DEBUG
char * GetModulesString(Word32 dwError)
{
	Word16 low = (Word16)(dwError &  0xFFFF);
	Word16 hei = (Word16)(dwError >> 16);
	static char szString[512] ;
	sprintf(szString,"Unknown code error 0x%X",dwError);

		switch(hei)
		{
		case PUMA_MODULE_RSTR:
			sprintf(szString,"RSTR: %s",RSTR_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_REXC:
			sprintf(szString,"REXC: %s",REXC_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_CCOM:
			sprintf(szString,"CCOM: %s",CCOM_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_CSTR:
			sprintf(szString,"CSTR: %s",CSTR_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_RLINE:
			sprintf(szString,"RLINE: %s",RLINE_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_CPAGE:
			sprintf(szString,"CPAGE: %s",CPAGE_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_RBLOCK:
			sprintf(szString,"RBLOCK: %s",RBLOCK_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_CFIO:
			sprintf(szString,"CFIO: %s",CFIO_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_CIMAGE:
			sprintf(szString,"CIMAGE: %s",CIMAGE_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_RFRMT:
			sprintf(szString,"RFRMT: %s",RFRMT_GetReturnString(dwError));
			return szString;

		case PUMA_MODULE_RSL:
			sprintf(szString,"RSL: %s",RSL_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_RIMAGE:
			sprintf(szString,"RIMAGE: %s",RIMAGE_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_RPSTR:
			sprintf(szString,"RPSTR: %s",RPSTR_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_RPIC:
			sprintf(szString,"RPIC: %s",RPIC_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_CED:
			sprintf(szString,"CED: %s",CED_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_ROUT:
			sprintf(szString,"ROUT: %s",ROUT_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_RSTUFF:
			sprintf(szString,"PUMA_MODULE_RSTUFF: %s",RSTUFF_GetReturnString(dwError));
			return szString;

#ifdef _USE_RVERLINE_
		case PUMA_MODULE_RVERLINE:
			sprintf(szString,"PUMA_MODULE_RVERLINE: %s",RVERLINE_GetReturnString(dwError));
			return szString;
#endif //_USE_RVERLINE_

		case PUMA_MODULE_RRECCOM:
			sprintf(szString,"RRECCOM: %s",RRECCOM_GetReturnString(dwError));
			return szString;
		case PUMA_MODULE_RCORRKEGL:
			sprintf(szString,"RCORRKEGL: %s",RCORRKEGL_GetReturnString(dwError));
			return szString;
#ifdef _USE_RMSEGMENT_
		case PUMA_MODULE_RMSEGMENT:
			sprintf(szString,"RMSEGMENT: %s",RMSEGMENT_GetReturnString(dwError));
			return szString;
#endif
		}
	return szString;
}

#else
//////////////////////////////////////////////////////////////////////
char * GetModulesString(Word32 dwError)
{
	Word16 low = (Word16)(dwError &  0xFFFF);
	Word16 hei = (Word16)(dwError >> 16);
	static char szString[512];
	Word32 	id = IDS_ERR_UNKNOWN;


		switch(hei)
		{
		case PUMA_MODULE_RSTR:
			switch(low)
			{
				case 9: //	"User break", �������� �������������
				case 1: //  "No error",
					id = IDS_ERR_NO;
					break;
				case 2: //	"Not enough memory", �� ������� ������
					id = IDS_ERR_NO_MEMORY;
					break;
				case 3: //	"Not implement", �� �������������� �-��
					id = IDS_ERR_NOTIMPLEMENT;
					break;
				case 4: //	"Null poiner assigned", ������� ���������
				case 5: //	"Bad value of argument", ������������ ��������
				case 6: //	"Internal error", ������ ���������� ������
				case 7: //	"Tools: No place in the kit", ��� ����� �� ���������� ������
					break;
				case 8: //	"Can't load recog tables", ��� ������ ������� ������������� ��� �������
					id = IDS_ERR_NOTABLE;
					break;
			}
		break;
		case PUMA_MODULE_REXC:
			switch(low)
			{
				case 1: //	"No error",
					id = IDS_ERR_NO;
					break;
                case 18: //	"Not enough memory", �� ������� ������
				case 2: //	"Not enough memory", �� ������� ������
					id = IDS_ERR_NO_MEMORY;
					break;
				case 3: //	"Not inmpement", �� �������������� �-��
					id = IDS_ERR_NOTIMPLEMENT;
					break;
				case 4: //	"Internal error - call developer", ������ ���������� ������
				case 5: //	"Can't open DumpFile", ��������
				case 6: //	"DumpFile writing error", ��������
				case 7: //	"External CallBack error", ��������
				case 8: //	"Bad Parameters of call", �������� ���������� ������
				case 12: //	"Can't import", ������ �������
				case 13: //	"Can't export", ������ ��������
				case 17: //	"Already init", ��� �������������������
                    break;
/*				case 19: //	"Can't get orientation", ������ ���������� ���������� ��������
                    id = IDS_ERR_CANNOTGETORIENTATION;
                    break;
*/				case 20: //"Bad image information" �������������� ���. � ���
					break;
				case 9: //	"Empty Page", ������ ��������
					id = IDS_ERR_EMPTYPAGE;
					break;
				case 10: //"Can't init eventual-library", �� ���������������� ������������ ���������� (��� �������: //
				case 15: //	"Can't init language", ������ �������� ������ �����
				case 16: //	"Can't init networks", ����� �������� ��������� ����
					id = IDS_ERR_NOTABLE;
					break;
				case 11: //"Different versions of REXC and CCOM", ����������� ������
					id = IDS_ERR_DIFVERSION;
					break;
				case 14: //	"Language not exist", �� �������������� ����
					id = IDS_ERR_UNKNOWN_LANGUAGE;
					break;
			}
		break;
		case PUMA_MODULE_CCOM:
			switch(low)
			{
				case 1: // "No error",
					id = IDS_ERR_NO;
					break;
				case 2: //	"Not enough memory", �� ������� ������
					id = IDS_ERR_NO_MEMORY;
					break;
				case 3: //	"Not implement", �� �������������� �-��
					id = IDS_ERR_NOTIMPLEMENT;
					break;
				case 4: //	"Null poiner assigned", ������� ���������
				case 5: //	"Bad value of argument" ������������ ��������
					break;
			}
			break;
		case PUMA_MODULE_CSTR:
			switch(low)
			{
				case 1: // "No error",
					id = IDS_ERR_NO;
					break;
				case 2: //	"Not enough memory", �� ������� ������
					id = IDS_ERR_NO_MEMORY;
					break;
				case 3: //	"Not implement", �� �������������� �-��
					id = IDS_ERR_NOTIMPLEMENT;
					break;
				case 4: //	"Null poiner assigned", ������� ���������
				case 5: //	"Bad value of argument", ������������ ��������
				case 6: //	"Assigned Line is absent", ��� ��������� ������
				case 7: //	"Can't rewrite used Line", ���������� ������ � ��������� ����������� (��� ��������: //
				case 8: //	"Structure of line has become rotten", ������ ��������� (��� �������: //
				case 9: //	"Internal error", ������ ���������� ��������������� ������
				case 10: //	"Can't convert to raster" ������ �������������� (��������: // ���������� � �����
					break;
			}
		break;
		case PUMA_MODULE_RLINE:
		break;
		case PUMA_MODULE_RLTABLE:
		break;
		case PUMA_MODULE_CPAGE:
			switch(low)
			{
			case 0://	������ ���
					id = IDS_ERR_NO;
					break;
			case 1://   �� �����������
					id = IDS_ERR_NOTIMPLEMENT;
					break;
 			case 2://   ��� ������
					id = IDS_ERR_NO_MEMORY;
					break;
 			case 3://   ���������� ������
 			case 6://   ���������� ������
				break;
 			case 4://   ������ ������ �����
					id = IDS_ERR_FILEREAD;
					break;
 			case 5://   ������ ������ �����
					id = IDS_ERR_FILEWRITE;
					break;
 			case 7://   ������������� ������
					id = IDS_ERR_DIFVERSION;
					break;
			}
		break;
		case PUMA_MODULE_RBLOCK:
			switch (low)
			{
			case 0: //IDS_ERR_NO: ������ ���
					id = IDS_ERR_NO;
					break;
			case 1:	// IDS_ERR_NOTIMPLEMENT	������� �� �����������.
					id = IDS_ERR_NOTIMPLEMENT;
					break;
			case 2: // IDS_ERR_NO_MEMORY	�� ������� ����������� ������.
					id = IDS_ERR_NO_MEMORY;
					break;
			case 4: //IDS_ERR_EMPTYPAGE: ������ ��������
					id = IDS_ERR_EMPTYPAGE;
					break;
			}
		break;
		case PUMA_MODULE_CFIO:
		break;
		case PUMA_MODULE_CIMAGE:
			switch(low)
			{
		case 0	: // IDS_CIMAGE_ERR_NO	������ ���.
					id = IDS_ERR_NO;
					break;
		case 1	: // IDS_CIMAGE_ERR_NOTIMPLEMENT	������� �� �����������.
					id = IDS_ERR_NOTIMPLEMENT;
					break;
		case 2	: // IDS_CIMAGE_ERR_NO_MEMORY	�� ������� ����������� ������.
					id = IDS_ERR_NO_MEMORY;
					break;
		case 3	: // IDS_CIMAGE_DLL_NOT_INITIALISING	������ �� ���������������
		case 4	: // IDS_CIMAGE_INVALID_IMAGE_NAME	������ � ����� ��������
		case 5	: // IDS_CIMAGE_INVALID_IMAGE_INFO	������ � ���������� ��������
		case 6	: // IDS_CIMAGE_INVALID_IMAGE_DATA	������ � ������ ��������
		case 7	: // IDS_CIMAGE_INVALID_IMAGES_CONTAINER	���������� ������ ����������
		case 8	: // IDS_CIMAGE_NO_IMAGE_FOUND	�������� �� ���l���
		case 9	: // IDS_CIMAGE_INVALID_DIB	������ � DIB ��� ����������� ������ DIB
		case 10	: // IDS_CIMAGE_DIB_FORMAT_NOT_SUPPORTED	������ ������ DIB �� �������������� ���� �����������
		case 11	: // IDS_CIMAGE_UNABLE_COPY_DIB	�� ������� ���������� DIB
		case 12	: // IDS_CIMAGE_INVALID_FRAME_SIZE	�������� ������ ������� �����������
		case 13	: // IDS_CIMAGE_NO_SUPPORT_DIB_FORMAT_FOR_THIS_ACTION	������ �������� � ������ DIB ���������� ���� ����������
		case 14	: // IDS_CIMAGE_DIB_AND_FRAME_COLORS_CONFLICT	�������������� �������� ��������
		case 15	: // IDS_CIMAGE_UNABLE_REPLACE_DIB	�� ������� �������� ����� �������� DIB
		case 16	: // IDS_CIMAGE_UNABLE_USE_IMPORT_CALLBACK	������ �� ������� ��������
		case 17	: // IDS_CIMAGE_CALLBACK_NO_PRESENT	��� ������� ��������
		case 18	: // IDS_CIMAGE_INVALID_PARAMETR	����� � ����������
		case 19	: // IDS_CIMAGE_IMAGE_NAME_REPEATED	�������� � ����� ������ ��� ����
			break;
			}
		break;
		case PUMA_MODULE_RFRMT:
		break;

		case PUMA_MODULE_RSL:
		break;

		case PUMA_MODULE_SLINEDOT:
		break;

		case PUMA_MODULE_RIMAGE:
			switch(low)
			{
			case 0	: // IDS_RIMAGE_ERR_NO	������ ���� �� ����������
					id = IDS_ERR_NO;
					break;
			case 1	: // IDS_RIMAGE_DLL_NOT_INITIALISING	��������� �� ���������������
			case 2	: // IDS_RIMAGE_ERR_NOTIMPLEMENT	������ ������ �� �������� ���������� ��� ������
				break;
			case 3	: // IDS_RIMAGE_ERR_NO_MEMORY	�� ������� ������
					id = IDS_ERR_NO_MEMORY;
					break;
			case 32	: // IDS_RIMAGE_NOTSUPPORTED_INDEX_COLOR	��������������� ����� �� ����� ���� ������������ �� ��������
                    id = IDS_ERR_UNSUPPORTED_IMAGE_FORMAT;
                    break;
			case 4	: // IDS_RIMAGE_NO_IMAGE_FOUND	�� ���� ������� ��������
			case 5	: // IDS_RIMAGE_UNDER_CONSTRUCTION	������ ������� ��������� � ������ �����������
			case 6	: // IDS_RIMAGE_INVALID_EXTERNAL_DIB	������ � DIB
			case 7	: // IDS_RIMAGE_INVALID_FUNCTION_PARAMETR	������� ������� �������
			case 8	: // IDS_RIMAGE_DIB_COMPRESSION_NOT_SUPPORTED	������ DIB ���� �� ������������
			case 9	: // IDS_RIMAGE_DIB_JPEG_NOT_SUPPORTED	DIB ������ 5 �� JPEG ��������� �� ��������������
			case 10	: // IDS_RIMAGE_INTERNAL_MODULE_ERROR	���������� ������ ����������
			case 11	: // IDS_RIMAGE_ONLY_ONE_DIB	���� DIB ��� ��������������!
			case 12	: // IDS_RIMAGE_UNABLE_WRITE_DIB	������ �������� DIB � CIMAGE
			case 13	: // IDS_RIMAGE_DIB_NOT_ATTACHED	���������� �������� ���������� �� ��������� DIB
			case 14	: // IDS_RIMAGE_CANNOT_CREATE_NEW_DIB	������ ������� ����� DIB
			case 15	: // IDS_RIMAGE_NOT_OPENED	�������� DIB �� ��� ������
			case 16	: // IDS_RIMAGE_PREPARE_TO_CREATE	����� ������� ����� DIB
			case 17	: // IDS_RIMAGE_CANNOT_SET_DIB	������ �������� �������� ��� ���������
				break;
			case 18	: // IDS_RIMAGE_CANT_BINARYZE	�� ���� ������������ ��������
						id = IDS_ERR_UNSUPPORTED_IMAGE_FORMAT;
						break;
			case 19	: // IDS_RIMAGE_CANNOT_INVERT_IMAGE	�� ���� ������������� ��������
			case 20	: // IDS_RIMAGE_DIB_CANT_TO_BE_BINARISED	����� �������� �� ������������
			case 21	: // IDS_RIMAGE_DIB_OUT_FORMAT_NOT_BINARISED	�������� ������ DIB ��� ���������� �� ��������
			case 22	: // IDS_RIMAGE_OUTCOME_DIB_NOT_LINK_TO_INCOME	��������  DIB �� ������������� ��������� �� ��������
			case 23	: // IDS_RIMAGE_CANT_TURN_DIB	��������� ��������� ��������
			case 24	: // IDS_RIMAGE_CIMAGE_MEMORY_ERROR	������ ���������� CIMAGE ��� ������������ ������
			case 25	: // IDS_RIMAGE_CANNOT_ROTATE_IMAGE	��������� �������� �� ��������
			case 26	: // IDS_RIMAGE_CANNT_SAVE_OUTCOMING_DIB	���������� ��������� �� ������� ���������� � ���������� Cimage
			case 27	: // IDS_RIMAGE_ANGLE_LEAST_MINIMUM	������� �����  ���� ��� ��������
			case 28	: // IDS_RIMAGE_ANGLE_GREAT_MAXIMUM	������� ������� ���� ��� ��������
			case 29	: // IDS_RIMAGE_EXIT_BY_USER	�������� ���������� �������
			case 30	: // IDS_RIMAGE_UNKNOWN_ERROR	�������������� ������. �������� � �������� � ������ ������.
			case 31	: // IDS_RIMAGE_ZERO_NUMERATOR_OR_DENUMERATOR	���� �� ���� - ��������� ��� ����������� - �������
				break;
			}
		break;
		case PUMA_MODULE_RPSTR:
			break;
		case PUMA_MODULE_RPIC:
			switch(low)
			{
			case 0	: // IDS_CIMAGE_ERR_NO	������ ���.
					id = IDS_ERR_NO;
					break;
			case 1	: // IDS_CIMAGE_ERR_NOTIMPLEMENT	������� �� �����������.
					id = IDS_ERR_NOTIMPLEMENT;
					break;
			case 2	: // IDS_CIMAGE_ERR_NO_MEMORY	�� ������� ����������� ������.
						id = IDS_ERR_NO_MEMORY;
						break;
			}
			break;
		case PUMA_MODULE_RANALFRM:
			/*switch(low)
			{
		case 0	: // IDS_CIMAGE_ERR_NO	������ ���.
				id = IDS_ERR_NO;
				break;
		case 1	: // IDS_CIMAGE_ERR_NOTIMPLEMENT	������� �� �����������.
				id = IDS_ERR_NOTIMPLEMENT;
				break;
		case 2	: // IDS_CIMAGE_ERR_NO_MEMORY	�� ������� ����������� ������.
					id = IDS_ERR_NO_MEMORY;
					break;
			}*/
			break;
		case PUMA_MODULE_CED:
			break;
		case PUMA_MODULE_ROUT:
			break;
		case PUMA_MODULE_RSTUFF:
			break;
		case PUMA_MODULE_RVERLINE:
			break;
		case PUMA_MODULE_RCORRKEGL:
			break;
		case PUMA_MODULE_RNORM:
			switch (low)
			{
				case 0://	������ ���
					id = IDS_ERR_NO;
					break;
				case 3: //	"Not inmpement", �� �������������� �-��
					id = IDS_ERR_NOTIMPLEMENT;
					break;
				case 19: //	"Can't get orientation", ������ ���������� ���������� ��������
                    id = IDS_ERR_CANNOTGETORIENTATION;
                    break;
			}
			break;

		case PUMA_MODULE_RRECCOM:
			switch (low)
			{
				case 0://	������ ���
					id = IDS_ERR_NO;
					break;
				case 3: //	"Not inmpement", �� �������������� �-��
					id = IDS_ERR_NOTIMPLEMENT;
					break;
			}
			break;

		}
		sprintf(szString," %s ",GetResourceString(id));

	return szString;
}
#endif
