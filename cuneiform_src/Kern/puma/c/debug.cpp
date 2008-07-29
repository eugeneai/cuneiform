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

#include <stdio.h>

#include "mpuma.h"
#include "dpuma.h"
#include "pumadef.h"
////////////////////////
void InitDebug()
{
	Handle hDebugCancel = NULL;
	Handle hDebugOk = NULL;

        LDPUMA_Init(0,NULL);

LDPUMA_RegistryHelp(hDebugRoot,
"<�������������: �.��������> � ���������� ���� ������� \
����� ���������� � �������� ������� �������� ���������� ������������� � �������. "
                ,NULL);
        LDPUMA_RegVariable(NULL,"���� �������������.",&gnLanguage,"unsigned");
        LDPUMA_RegVariable(NULL,"���� �������.",&gbOneColumn,"unsigned");
        LDPUMA_RegVariable(NULL,"��������� ��������.",&gbSpeller,"unsigned");
        LDPUMA_RegVariable(NULL,"����.",&gbFax100,"unsigned");
        LDPUMA_RegVariable(NULL,"��������� �������.",&gbDotMatrix,"unsigned");
        LDPUMA_RegVariable(NULL,"�������� �������� � RTF.",&gbBold,"unsigned");
        LDPUMA_RegVariable(NULL,"�������� ������ � RTF.",&gbItalic,"unsigned");
        LDPUMA_RegVariable(NULL,"�������� ������ � RTF.",&gbSize,"unsigned");
        LDPUMA_RegVariable(NULL,"������������� � RTF.",&gnFormat,"unsigned");
        LDPUMA_RegVariable(NULL,"���� ��������� ��������.",&gnPictures,"unsigned");
        LDPUMA_RegVariable(NULL,"���� ��������� ������.",&gnTables,"unsigned");
        LDPUMA_RegVariable(NULL,"������������� �������.",&gbAutoRotate,"unsigned");
        LDPUMA_RegVariable(NULL,"������� �������� ��� ��������� ���� ��������:",&nDebugReturnCode,"unsigned");
#ifdef _DEBUG
        LDPUMA_RegVariable(NULL,"������� �������� ��� ��������� ����� ������:",&nDebugAllocMemory,"unsigned");
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� ���������� ����������
        LDPUMA_Registry(&hDebugRoot,SNAP_ROOT_, NULL);
        LDPUMA_RegistryHelp(hDebugRoot,
"<�������������: �.��������> � �������� ���������� ����� ��������� ��� �������� � ������ �������� ����� ������ ���������. \
������ ��������� ������� ��� �� ���� ��������, ��� � �� ���������� ������������� \
������������� ������������� ��� ������� ���������.(��� ��������� ����� ������� � �������� � ���������� \
�������� ������� )."
                ,FALSE);

//������� �������
 LDPUMA_Registry(&hDebugMainDebug,SNAP_ROOT_MAIN_DEBUG, NULL);
 LDPUMA_RegistryHelp(hDebugMainDebug,"��� ����������� �����-���� �� ����� ���� ������� ����� �������������� ��������������� �� �� ������������ � ������� ������ ��������.",FALSE);
//������� ������������
 LDPUMA_Registry(&hDebugMainTimeControl,SNAP_ROOT_MAIN_TIME_CONTROL, NULL);
 LDPUMA_RegistryHelp(hDebugMainTimeControl,"��������� �������� �� �������� ������ ���������",FALSE);

        LDPUMA_Registry(&hDebugCancel,SNAP_SELECT_DISABLE, hDebugRoot);
        LDPUMA_RegistryHelp(hDebugCancel,
                "����� ����������� �������, ������� �������� ���������� ������ ��� �������."
                ,FALSE);
		//
		// �������� ! ��� ����� ����������� � ������� �� ������ !
		//

        LDPUMA_Registry(&hDebugCancelBinarize,          "���� �����������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelBinarize,
                "���� ����������� �� ���������� �����������."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelComponent,         "���� ��������� ���������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelComponent,
                "���� ��������� ��������� �� �����-����� �����������."
                ,FALSE);
		LDPUMA_Registry(&hDebugCancelTurn,				"���� �������� �����������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelTurn,
                "���� �������� ��������� ����������� � ������ ��������� ����� ������������ � ��� �������������."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelSearchLines,       "���� ������ �����.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelSearchLines,
                "���� ������ ����� �� �����-����� �����������."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelOrtoMove,   "���� ����������������� ������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelOrtoMove,
                "���� ����������������� ������."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelSearchDotLines,       "���� ������ �������� �����.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelSearchDotLines,
                "���� ��������� �������� ����� �� �����������."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelVerifyLines,       "���� ������ �����.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelVerifyLines,
                "���� ������� ����� ���������� ����� ��� ������������ ��������."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelRemoveLines,       "���� �������� �����.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelRemoveLines,
                "���� �������� ����� ���������� � ���������� ��� �������� �����. "
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelComponentSecond,	"���� ��������� ��������� ����� �������� �����.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelComponentSecond,
                "���� ��������� ��������� ����� �������� �����. "
                ,FALSE);
	    LDPUMA_Registry(&hDebugCancelSearchPictures,    "���� ������ ��������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelSearchPictures,
                "���� ������ �������� �� ����� ���������� �����������."
                ,FALSE);
	    LDPUMA_Registry(&hDebugCancelSearchNegatives,    "���� ������ ���������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelSearchNegatives,
                "���� ������ ���������."
                ,FALSE);

	    LDPUMA_Registry(&hDebugCancelLinePass3,    "���� �������� ������� �� ������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelLinePass3,
                "���� �������� ������� �� ������."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelSearchTables,      "���� ������ ������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelSearchTables,
                "���� ������ ������ �� ����� ���������� ������."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelExtractBlocks,		"���� ��������������� Layout(�).", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelExtractBlocks,
                "���� ��������������� Layout(�). "
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelVertCells,		"���� �������������� ������������ ����������� ����� ������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelVertCells,
                "���� �������������� ������������ ����������� ����� ������."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelStrings,           "���� ��������� �����.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelStrings,
                "���� ��������� �����. \
���� ��������� ����� ������ � ������������ ������� ������ ���������. ��� ������ �������� � ��������� ��������� �� ���� �����."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelRecognition,       "���� ������������� �����.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelRecognition,
                "���� ������������� ����� ������ � ������������ ������� ������ ���������. ��� ������ �������� � ��������� ��������� �� ���� �����."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelStringsPass2,      "���� ������������� ����� ������ ��������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelStringsPass2,
                "���� ������������� ����� ������ ��������."
                ,FALSE);
	    LDPUMA_Registry(&hDebugCancelPostSpeller,        "���� ��������������� �� �������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelPostSpeller,
                "���� ��������������� �� �������."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelPostRecognition,    "���� ��������� ����� ����� �������������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelPostRecognition,
                "���� ��������� ����� ����� �������������. � ��� ������ ����������� �����."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelConsoleOutputText,	 "���� ���������� ������ �����������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelConsoleOutputText,
                "���� ���������� ������ ����������� ������������� ����� � �������."
                ,FALSE);
			LDPUMA_Registry(&hDebugCancelPropertyConsole,  "�������� RTF-������ ����������� � �������.", hDebugCancelConsoleOutputText);
			LDPUMA_RegistryHelp(hDebugCancelPropertyConsole,
					"�������� ��� �������, ���� �� ������, ����� ���������� ������������ ������� ������� ������� 12 �������."
					,FALSE);
			LDPUMA_Registry(&hDebugCancelConsoleKeglOutput,"�������� ������ �������.", hDebugCancelConsoleOutputText);
			LDPUMA_RegistryHelp(hDebugCancelConsoleKeglOutput,"�������� ��� �������, ���� ������ ���������� ������ �������. ������ ����� ������� ������� ������.",FALSE);
        LDPUMA_Registry(&hDebugCancelFormatted,         "���� ��������������.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelFormatted,
                "���� ��������������."
                ,FALSE);
        LDPUMA_Registry(&hDebugCancelFictive,         "��������� ����.", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelFictive,
                "��������� ���� ��������� ��� ���������� ������ ����������."
                ,FALSE);

        LDPUMA_Registry(&hDebugOk,SNAP_SELECT_ENABLE, hDebugRoot);
        LDPUMA_RegistryHelp(hDebugOk,
                "����� ����������� �������, ������� ��������� ���������� ������ ��� �������."
                ,FALSE);


        LDPUMA_Registry(&hDebugCancelAutoTemplate,   "���� ����������� ������� �������������.", hDebugOk);
        LDPUMA_RegistryHelp(hDebugCancelAutoTemplate,
                "���� ��������������� ����������� ������� �������������."
                ,FALSE);
        LDPUMA_Registry(&hDebugHandLayout,   "���� ������ �������� (Layout).", hDebugOk);
        LDPUMA_RegistryHelp(hDebugHandLayout,
"�������� ����������� ����� ������������ ����� OLE ������� <Layout.ocx>. \
��� �������� ������ ����� ����� ���������� ����������� � ���������������� ���� ������ ��������� �������� \
REGSVR32 Layout.ocx"
                ,FALSE);
			LDPUMA_Registry(&hDebugLayoutToFile,  "��������  LAYOUT � ����.", hDebugHandLayout);
			LDPUMA_RegistryHelp(hDebugLayoutToFile,
					"����������� ���� ������� ��������� ��������� ������� Layout � �����. \
	��� ����� �������� � ���������� ���� �������. ��� ����� ����� �������� � �������� ������ ������."
					,FALSE);
			LDPUMA_RegVariable(hDebugLayoutToFile,"��� ����� ��� ����./����. LAYOUT",szLayoutFileName,"char *");

			LDPUMA_Registry(&hDebugLayoutFromFile,"��������� LAYOUT �� �����.", hDebugHandLayout);
			LDPUMA_RegistryHelp(hDebugLayoutFromFile,
					"����������� ���� ������� ��������� ��������� ������� Layout �� �����. \
	��� ����� �������� � ���������� ���� �������. ��� ����� ����� �������� � �������� ������ ������."
					,FALSE);
			LDPUMA_RegVariable(hDebugLayoutFromFile,"��� ����� ��� ����./����. LAYOUT",szLayoutFileName,"char *");

        LDPUMA_Registry(&hDebugPrintBlocksCPAGE,"���� ���������� ������ ���������� CPAGE.", hDebugOk);
        LDPUMA_RegistryHelp(hDebugPrintBlocksCPAGE,
                "���� ���������� ������ ����������� ���������� �������� �������� CPAGE . ���������� ���������� ����� ����� Layout"
                ,FALSE);
	    LDPUMA_Registry(&hDebugCancelRanalFrm,"���� ����������������� ������", hDebugCancel);
        LDPUMA_RegistryHelp(hDebugCancelRanalFrm,
                "���� ������� � ����������������� ������."
                ,FALSE);
		LDPUMA_Registry(&hDebugEnableSaveJtl,  "���� ������ JTL �����.", hDebugOk);
        LDPUMA_RegistryHelp(hDebugEnableSaveJtl,
                "���� ������ JTL �����."
                ,FALSE);

        LDPUMA_Registry(&hDebugEnableSaveCstr1,  "���� ���������� CSTR before pass1.", hDebugOk);
        LDPUMA_RegistryHelp(hDebugEnableSaveCstr1,
                "���� ���������� ����� ����� �������� 1."
                ,FALSE);
        LDPUMA_Registry(&hDebugEnableSaveCstr2,  "���� ���������� CSTR before pass2.", hDebugOk);
        LDPUMA_RegistryHelp(hDebugEnableSaveCstr2,
                "���� ���������� ����� ����� �������� 2."
                ,FALSE);
        LDPUMA_Registry(&hDebugEnableSaveCstr3,  "���� ���������� CSTR before pass3.", hDebugOk);
        LDPUMA_RegistryHelp(hDebugEnableSaveCstr3,
                "���� ���������� ����� ����� �������� 3."
                ,FALSE);
        LDPUMA_Registry(&hDebugEnableSaveCstr4,  "���� ���������� ���������� CSTR.", hDebugOk);
        LDPUMA_RegistryHelp(hDebugEnableSaveCstr4,
                "���� ���������� ��������� �����."
                ,FALSE);

			LDPUMA_Registry(&hDebugEnablePrintFormatted,         "���� ���������� ������ ����������� ��������������.", hDebugOk);
			LDPUMA_RegistryHelp(hDebugEnablePrintFormatted,
					"���� ���������� ������ ����������� ��������������. ���� ���� ���� �������, �����, � ���������� ������, ���������� ��� ��������� ����� __tmp__.fed � __tmp__.rtf"
					,FALSE);

		LDPUMA_Registry(&hDebugEnableSearchSegment,    "���� ������� ������ ����������.", hDebugOk);
        LDPUMA_RegistryHelp(hDebugEnableSearchSegment,
                "���� ������� ������ ����������."
                ,FALSE);
		// ��������� CPAGE
        LDPUMA_Registry(&hDebugCPAGEStorage,SNAP_CPAGE_STORAGE, hDebugRoot);
/////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� �����
        LDPUMA_Registry(&hDebugRootStuff,SNAP_ROOT_STUFF,NULL);
		LDPUMA_RegistryHelp(hDebugRootStuff,
				"�����������, ���������, ������ � ����������� �����, ��������� ��������"
				, FALSE);
		// �����������
        LDPUMA_Registry(&hDebugBinarize,SNAP_STUFF_BINARIZE,hDebugRootStuff/*NULL*/);
        /*
        LDPUMA_RegistryHelp(hDebugBinarize,
                "<�������������: �.�����������> ���� ��������� ��������� �����������. \
��� �������� ��������� ��������� �������� ����������� ������������ � ���� "NAME_IMAGE_INPUT" \
�������������� - � ���� Main."
                ,FALSE);*/
        LDPUMA_RegistryHelp(hDebugBinarize,
                "<�������������: �.�������> ���� ����������� ������� � ����� ����������� \"�� ��������\". \
��� �������� ��������� ��������� �������� ����������� ������������ � ���� "NAME_IMAGE_INPUT" \
�������������� - � ���� Main."
                ,FALSE);
		//������������
        LDPUMA_Registry(&hDebugAutoTemplate,SNAP_STUFF_AUTOTEMPLATE,hDebugRootStuff/*NULL*/);
        LDPUMA_RegistryHelp(hDebugAutoTemplate,SNAP_STUFF_AUTOTEMPLATE,FALSE);
		//��������� � ������ �����
        LDPUMA_Registry(&hDebugLines,SNAP_STUFF_LINES , hDebugRootStuff/*NULL*/ );
        LDPUMA_RegistryHelp(hDebugLines,
                "<�������������: �.��������> ���� ��������� � ������ �����."
                ,FALSE);

          // alik �������� ��� �������
        LDPUMA_Registry(&hDebugRSL,SNAP_STUFF_RSL , hDebugLines );
        LDPUMA_RegistryHelp(hDebugRSL,
                "<�������������: ����> �������� ��� �������."
                ,FALSE);

		// ����������� �����
        LDPUMA_Registry(&hDebugLines,SNAP_STUFF_VER_LINES , hDebugRootStuff );
/////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� ��������
        LDPUMA_Registry(&hDebugRootLayout,SNAP_ROOT_LAYOUT, NULL);
		LDPUMA_RegistryHelp(hDebugRootLayout,
				"��������� ������, ����������, �����, ��������� �����"
				, FALSE);
		// ����� ��������
        LDPUMA_Registry(&hDebugPictures,SNAP_LAYOUT_PICTURES , hDebugRootLayout );
        // ����� ���������
        LDPUMA_Registry(&hDebugNeg,SNAP_LAYOUT_NEG , hDebugRootLayout );
		// ������ ����� ����������
        LDPUMA_Registry(&hDebugSegment,SNAP_LAYOUT_SEGMENT , hDebugRootLayout );
        // ����� ����
        LDPUMA_Registry(&hDebugFon,SNAP_LAYOUT_FON , hDebugRootLayout );

		// ��������� ������
        LDPUMA_Registry(&hDebugTables,SNAP_LAYOUT_TABLES, hDebugRootLayout);
        LDPUMA_RegistryHelp(hDebugTables,
                "<�������������: A.��������> ���� ��������� ������. ��������� ������ �� ������ �������� \
������ ����� ���������� ����� ��������� �����."
                ,FALSE);
		//������ � ������������� �����������
		Handle hVertCells;
		Handle hNegaCells;
	LDPUMA_Registry(&hVertCells,"������ � ������������� �������� ������",hDebugRootLayout);
	LDPUMA_Registry(&hNegaCells,"������ � ����������� �������� ������",hDebugRootLayout);

		// ��������� ����������
        LDPUMA_Registry(&hDebugLayout,SNAP_LAYOUT_LAYOUT, hDebugRootLayout);
        LDPUMA_RegistryHelp(hDebugLayout,
                "<�������������: �.��������, �.��������> ���� ��������������� Layout(�). \
�������� Level ��������� �� ������� ����������� ������. ��� ���� �������, ��� ���������. \
����������� ��������� - 3. � ���������� ������� ������� �������� �������."
                ,FALSE);
		// ��������� �����
        LDPUMA_Registry(&hDebugStrings,SNAP_LAYOUT_STRINGS, hDebugRootLayout);
        LDPUMA_RegistryHelp(hDebugStrings,
                "<�������������: �.��������, �.��������> ���� ��������� �����. \
������ ����� ��������������� Layout(�). ��������� ����� �������� ������ ����� ����� \
��������� ���������."
                ,FALSE);
		//��������� �����
        LDPUMA_Registry(&hDebugPostLines,SNAP_LAYOUT_POST_LINES, hDebugRootLayout);
		LDPUMA_RegistryHelp(hDebugRootLayout,
				"�������� ������������ �����"
				, FALSE);
		// �������� ������������ �����
        LDPUMA_Registry(&hDebugSVLines,SNAP_LAYOUT_SHOR_LINES, hDebugPostLines);
        LDPUMA_RegistryHelp(hDebugSVLines,
                "<�������������: A.��������> ����� � �������� �������� ������������ �����."
                ,FALSE);
        LDPUMA_RegVariable(hDebugSVLines,"����� ����������",&gKillVSLComponents,"unsigned");
        LDPUMA_Registry(&hDebugSVLinesStep,SNAP_SHOR_LINES_STEP, hDebugSVLines);
        LDPUMA_RegistryHelp(hDebugSVLinesStep,
                "��������� ������."
                ,FALSE);
        LDPUMA_Registry(&hDebugSVLinesData,SNAP_SHOR_LINES_DATA, hDebugSVLines);
        LDPUMA_RegistryHelp(hDebugSVLinesData,
                "���� �� ���� �� �������������"
                ,FALSE);
/////////////////////////////////////////////////////////////////////////////////////////////////////
// �������������
        LDPUMA_Registry(&hDebugRootRecognition,SNAP_ROOT_RECOGNITION, NULL);
        LDPUMA_RegistryHelp(hDebugRootRecognition,
                "������������� �����, �������"
                ,FALSE);
		// ������������� �����
        LDPUMA_Registry(&hDebugRecognition,SNAP_RECG_RECOGNITION, hDebugRootRecognition/*NULL*/);
        LDPUMA_RegistryHelp(hDebugRecognition,
                "<�������������: �.������> ���� ������������� �����. ����� ������ �������� \
��������� ���."
                ,FALSE);
		// �������
        LDPUMA_Registry(&hDebugSpell,SNAP_RECG_SPELL, hDebugRootRecognition/*NULL*/);
/////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������������
        LDPUMA_Registry(&hDebugRootFormatting,SNAP_ROOT_CONVERTERS, NULL);
        LDPUMA_RegistryHelp(hDebugRootFormatting,
                "��������������, ��������� �����"
                ,FALSE);
		//�������������� � ���������
        LDPUMA_Registry(&hDebugConverters,SNAP_FRMT_CONVERTERS, hDebugRootFormatting/*NULL*/);
        LDPUMA_RegistryHelp(hDebugConverters,
                "<�������������: �.����������> ���� �������������� � ��������������� ����������� \
� RTF ������."
                ,FALSE);
		// ��������� �����
        LDPUMA_Registry(&hDebugCeglCorr,SNAP_KEGL_CORRECT, hDebugRootFormatting/*NULL*/);
        /*
        LDPUMA_Registry(&hDebugCancelStringsColor,              "�������� ����������� ����� ������� � ����.", hDebugRoot);
        LDPUMA_RegistryHelp(hDebugCancelStringsColor,
                "�������� ����������� ����� ������� � ����"
                ,FALSE);
*/
        //LDPUMA_RegVariable(hDebugRoot,"�������� ����� � RTF.",gpSerifName,"char *");
        //LDPUMA_RegVariable(hDebugRoot,"����������� ����� � RTF.",gpSansSerifName,"char *");
        //LDPUMA_RegVariable(hDebugRoot,"������������ ����� � RTF.",gpCourierName,"char *");

}
///////////////////////
void DoneDebug()
{
        LDPUMA_UnregVariable(szLayoutFileName);
        LDPUMA_Done();
}
