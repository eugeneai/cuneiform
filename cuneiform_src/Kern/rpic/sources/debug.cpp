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

# include "iolib.h"
//# include "layout.h"
//# include "extract.h"
//# include "kernel.h"
//# include "status.h"

# include "dpuma.h"
# include "debug.h"
//# include "pumadef.h"

//////////////////////////////////
Handle hDebugPictures = NULL;
Handle hRectanglePictures = NULL;
Handle hPolyPictures = NULL;
Handle hShowFirstAttempt = NULL;
Handle hShowAllGreat = NULL;
Handle hShowAllCancelledGreat = NULL;
Handle hShowCheckLetters = NULL;
Handle hShowBigLetters = NULL;
Handle hShowPossiblePics = NULL;
//Handle hDebugStrings = NULL;
//////////////////////////////////
void InitDebug()
{
	//layout = 0;

	LDPUMA_Registry(&hDebugPictures,"��������� ��������...",NULL);
    //LDPUMA_RegVariable(hDebugLayout,"���������� ������� �������.",&layout,"unsigned char");
	LDPUMA_RegistryHelp(hDebugPictures,"������ ��������� ��������",FALSE);

    LDPUMA_Registry(&hShowPossiblePics,"�������� ����������� �������� 1",hDebugPictures);
	LDPUMA_RegistryHelp(hShowPossiblePics,"���������� ����������� ��������, ���������� \
����� ������� �������.",FALSE);
 
	LDPUMA_Registry(&hShowBigLetters,"�������� �������",hDebugPictures);
	LDPUMA_RegistryHelp(hShowBigLetters,"���������� �������.",FALSE);


	LDPUMA_Registry(&hRectanglePictures,"�������� ����� ������������� ��������",hDebugPictures);
	LDPUMA_RegistryHelp(hRectanglePictures,"�������� ����� ������������� �������� \
(��������������� ������ ��������).",FALSE);

	LDPUMA_Registry(&hPolyPictures,"�������� ����� ��������������� ��������",hDebugPictures);
	LDPUMA_RegistryHelp(hPolyPictures,"�������� ����� ��������������� ��������. \
(������������� ������ ��������).",FALSE);

	LDPUMA_Registry(&hShowAllGreat,"�������� ��� ������ ���������� 1",hDebugPictures);
	LDPUMA_RegistryHelp(hShowAllGreat,"���������� ��� ������ ����������, \
�� ������� �� ������ ������� ����� ���������� ��������.",FALSE);

	LDPUMA_Registry(&hShowAllCancelledGreat,"�������� ��� ������������� ������ ���������� 1",hDebugPictures);
	LDPUMA_RegistryHelp(hShowAllCancelledGreat,"���������� ��� ������������� ������ ����������, \
�� ������� �� ������ ������� ����� ���������� ��������.",FALSE);

	LDPUMA_Registry(&hShowCheckLetters,"�������� �������� �� ��������� 1",hDebugPictures);
	LDPUMA_RegistryHelp(hShowCheckLetters,"���������� ������� �������� �� ���������",FALSE);

	LDPUMA_Registry(&hShowFirstAttempt,"�������� �������� 1",hDebugPictures);
	LDPUMA_RegistryHelp(hShowFirstAttempt,"���������� ��������, ���������� \
����� ������� �������.",FALSE);

	/*
#define REGVAR(a)	LDPUMA_RegVariable(hDebugLayout,#a,&a,"short int")

# ifdef LT_DEBUG
    LDPUMA_RegVariable(hDebugLayout,"LT_DebugGraphicsLevel",&LT_DebugGraphicsLevel,"int");

	REGVAR(bDebugTimeFlag);
	REGVAR(bDebugOptionCalibratePictureRemovingCriteria);
	REGVAR(bDebugOptionCalibrateDD_RemovingCriteria);
	REGVAR(bDebugOptionCalibrateLinearRemovingCriteria);
# endif
	REGVAR(bOptionForceOneColumn);
	REGVAR(bOptionBusinessCardsLayout);
	REGVAR(bOptionPointSizeAnalysis);
	REGVAR(bOptionSmartBreaking);
	REGVAR(bOptionInitialBreakingByPageMatrix);
	REGVAR(bOptionBlocksRemovingByPageMatrix);
	REGVAR(bOptionBlocksRemovingByDustDistribution);
	REGVAR(bOptionSpecialHorizontalCutting);
	REGVAR(bOptionWhiteStripsBreaking);
# ifdef SE_DEBUG
    REGVAR(SE_DebugGraphicsLevel);
# endif
# ifdef MA_DEBUG
    REGVAR(MA_DebugLevel);
# endif

#undef REGVAR
  */

}
/////////////////////////////////////////
void DoneDebug()
{
	/*
#define UNREGVAR(a)	LDPUMA_UnregVariable(&a)

# ifdef LT_DEBUG
    LDPUMA_UnregVariable(&LT_DebugGraphicsLevel);

	UNREGVAR(bDebugTimeFlag);
	UNREGVAR(bDebugOptionCalibratePictureRemovingCriteria);
	UNREGVAR(bDebugOptionCalibrateDD_RemovingCriteria);
	UNREGVAR(bDebugOptionCalibrateLinearRemovingCriteria);
# endif
	UNREGVAR(bOptionForceOneColumn);
	UNREGVAR(bOptionBusinessCardsLayout);
	UNREGVAR(bOptionPointSizeAnalysis);
	UNREGVAR(bOptionSmartBreaking);
	UNREGVAR(bOptionInitialBreakingByPageMatrix);
	UNREGVAR(bOptionBlocksRemovingByPageMatrix);
	UNREGVAR(bOptionBlocksRemovingByDustDistribution);
	UNREGVAR(bOptionSpecialHorizontalCutting);
	UNREGVAR(bOptionWhiteStripsBreaking);
# ifdef SE_DEBUG
    UNREGVAR(SE_DebugGraphicsLevel);
# endif
# ifdef MA_DEBUG
    UNREGVAR(MA_DebugLevel);
# endif

#undef UNREGVAR
  */
}
////////////////////////////////////////
