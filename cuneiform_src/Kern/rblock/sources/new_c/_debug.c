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
# include "layout.h"
# include "extract.h"
# include "kernel.h"
# include "status.h"

# include "dpuma.h"
# include "pumadef.h"

//////////////////////////////////
Handle hDebugLayout = NULL;
Handle hDebugStrings = NULL;
Handle hShowString = NULL;
Handle hShowCells = NULL;
Handle hDebugCancelPicturesAndTables = NULL;
Handle hDebugCancelGreatComp = NULL;
Handle hShowAlgoritm;
Handle hPageBeforeEditing = NULL;
Handle hPageMatrix = NULL;
Handle hInitialBreaking = NULL;
Handle hInclineCalculating = NULL;
//Handle hBlocksAfterFirstExtraction = NULL;
Handle hBlocksBreaking = NULL;
Handle hBlocksGlueing = NULL;
Handle hFirstDustAbsorbtion = NULL;
Handle hRemoveEmptyBlocks = NULL;
Handle hSecondDustAbsorbtion = NULL;
Handle hAlgoritmWork = NULL;
Handle hNotWholeLine = NULL;
Handle hHystogramNull = NULL;
Handle hNotUseAntonCross = NULL;
//Handle hUseCLine = NULL;
Handle hSetTrivAverHeight = NULL;//George, 12.11.01 (dd.mm.yy)


Word32 ZagolovokBreakingCoeff = 3;
//////////////////////////////////
void InitDebug()
{
	layout = 0;

//Beg of Almi Corr
//	LDPUMA_Registry(&hDebugLayout,SNAP_ROOT_LAYOUT,NULL);
	LDPUMA_Registry(&hDebugLayout,SNAP_LAYOUT_LAYOUT,NULL);
//End of Almi 05.12.00; �� ������ ���������, �� � ��� �����; (�� ���� ��� ˸��)
    LDPUMA_RegVariable(hDebugLayout,"���������� ������� �������.",&layout,"unsigned char");
	LDPUMA_RegistryHelp(hDebugLayout,"� ���������� ����� ���������� �������� ������ \
������� �� 1 �� 4",TRUE);

	LDPUMA_RegVariable(hDebugLayout,"����������� ��� ��������� ���������� * 2.",
		&ZagolovokBreakingCoeff,"unsigned int");
	//LDPUMA_RegistryHelp(hDebugLayout,"rrrrrrrrrrrrr",TRUE);

	/*
	LDPUMA_Registry(&hDebugCancelGreatComp,"�������� ������� ����������",hDebugLayout);
	LDPUMA_RegistryHelp(hDebugCancelGreatComp,"������� ���������� �� ����� ������������ \
�������������.",FALSE);

	LDPUMA_Registry(&hDebugCancelPicturesAndTables,"�������� �������� � �������",hDebugLayout);
	LDPUMA_RegistryHelp(hDebugCancelPicturesAndTables,"���������� ������ � \
���������� � ������������",FALSE);
    

	LDPUMA_Registry(&hShowAlgoritm,"������ ���������",hDebugLayout);
	LDPUMA_RegistryHelp(hShowAlgoritm,"�������� �������� ������ �������������. \
���� ��� ������ �� ����� ����������",FALSE);
    */



	LDPUMA_Registry(&hAlgoritmWork,"������ ���������",hDebugLayout);
	LDPUMA_RegistryHelp(hAlgoritmWork,"���������� ������� �������������.",FALSE);



	LDPUMA_Registry(&hNotWholeLine,"�������� ���������� ����� �� �������� ������.",hAlgoritmWork);
	LDPUMA_RegistryHelp(hNotWholeLine,"�������� ���������� ����� �� �������� ������.",FALSE);
    
	LDPUMA_Registry(&hNotUseAntonCross,"�������� �������� ����������� ������������ ���������.",hAlgoritmWork);
	LDPUMA_RegistryHelp(hNotUseAntonCross,"�������� ������������ ������� �������� ����������� ������������ ���������.",FALSE);

	LDPUMA_Registry(&hHystogramNull,"�������� ��������� ����. ���������.",hAlgoritmWork);
	LDPUMA_RegistryHelp(hHystogramNull,"�������� ��������� ��������� � ������������ \
 ������������, (�������� � ������ ������ ��� ��������� ������� ��������������� ���������).",FALSE);

  //George, 12.11.01 (dd.mm.yy)
	LDPUMA_Registry(&hSetTrivAverHeight,"����������� ���������� nAverageHeight",hAlgoritmWork);
	LDPUMA_RegistryHelp(hSetTrivAverHeight,"�������� ���������� �������� � ���� nAverageHeight " \
                                         "�� ����������� (�������) ������� ���������� ��������",FALSE);


	LDPUMA_Registry(&hPageBeforeEditing,"�������� ����� �������",hDebugLayout);
	LDPUMA_RegistryHelp(hPageBeforeEditing,"���������� ���������� �� �������� \
����� ������� ������",FALSE);

	LDPUMA_Registry(&hPageMatrix,"���������� PageMatrix",hDebugLayout);
	LDPUMA_RegistryHelp(hPageMatrix,"���������� ������� ���������� PageMatrix \
(������� ��������)",FALSE);

	LDPUMA_Registry(&hInitialBreaking,"��������� ���������",hDebugLayout);
	LDPUMA_RegistryHelp(hInitialBreaking,"���������� ��������� ��������� �������� \
�� ����� � ���������� ������������� PageMatrix'a",FALSE);

	LDPUMA_Registry(&hInclineCalculating,"���������� ���� �������",hDebugLayout);
	LDPUMA_RegistryHelp(hInclineCalculating,"���������� ������� ���������� ���� \
������� ��������",FALSE);

	/*
	LDPUMA_Registry(&hBlocksAfterFirstExtraction,"����� ����� ������� ���������",hShowAlgoritm);
	LDPUMA_RegistryHelp(hBlocksAfterFirstExtraction,"���������� ������",FALSE);
	*/

	LDPUMA_Registry(&hBlocksBreaking,"���������",hDebugLayout);
	LDPUMA_RegistryHelp(hBlocksBreaking,"���������� ������� ��������� ������",FALSE);

	LDPUMA_Registry(&hBlocksGlueing,"�������",hDebugLayout);
	LDPUMA_RegistryHelp(hBlocksGlueing,"���������� ��������� ������� ������",FALSE);

	LDPUMA_Registry(&hFirstDustAbsorbtion,"������ ���� ���������� ������",hDebugLayout);
	LDPUMA_RegistryHelp(hFirstDustAbsorbtion,"���������� ����� ����� ������� ����� \
���������� ������",FALSE);

	LDPUMA_Registry(&hRemoveEmptyBlocks,"�������� ������ ������",hDebugLayout);
	LDPUMA_RegistryHelp(hRemoveEmptyBlocks,"���������� ������� �������� ������ ������",FALSE);

	LDPUMA_Registry(&hSecondDustAbsorbtion,"������ ���� ���������� ������",hDebugLayout);
	LDPUMA_RegistryHelp(hSecondDustAbsorbtion,"���������� ����� ����� ������� ����� \
�������� ������",FALSE);
/*
	LDPUMA_Registry(&hDebugStrings,SNAP_ROOT_STRINGS,NULL);
    LDPUMA_RegVariable(hDebugStrings,"���������� ������� �������.",&layout,"unsigned char");
	LDPUMA_RegistryHelp(hDebugStrings,"� ���������� ����� ���������� �������� ������ \
������� �� 5 �� 8",TRUE);

	LDPUMA_Registry(&hShowString,"�������� ���������� ������",hDebugStrings);
	LDPUMA_RegistryHelp(hShowString,"������ ����� ���������� ����������������.",FALSE);

	LDPUMA_Registry(&hShowCells,"�������� ���������� ������ � ������������",hDebugStrings);
	LDPUMA_RegistryHelp(hShowCells,"����� �������������� ������ � �������� \
� ��� ����������.",FALSE);
*/
//	LDPUMA_Registry(&hUseCLine,"������ � ����������� �����",NULL);


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

}
/////////////////////////////////////////
void DoneDebug()
{
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
}
////////////////////////////////////////
void EnableDebug()
{
	
# ifdef LT_DEBUG
    switch (layout)
    {
        case 0:  LT_DebugGraphicsLevel = 0;  break;
        case 1:  LT_DebugGraphicsLevel = 1;  break;
        case 2:  LT_DebugGraphicsLevel = 2;  break;
        case 3:  LT_DebugGraphicsLevel = 3;  break;
        case 4:  LT_DebugGraphicsLevel = 4;  break;
        case 5:  LT_DebugGraphicsLevel = 1;  break;
        case 6:  LT_DebugGraphicsLevel = 1;  break;
        case 7:  LT_DebugGraphicsLevel = 1;  break;
        case 8:  LT_DebugGraphicsLevel = 1;  break;
        case 9:  LT_DebugGraphicsLevel = 0;  break;
        case 10: LT_DebugGraphicsLevel = 0;  break;
    }
# endif
# ifdef SE_DEBUG
    switch (layout)
    {
        case 0:  SE_DebugGraphicsLevel = 0;  break;
        case 1:  SE_DebugGraphicsLevel = 0;  break;
        case 2:  SE_DebugGraphicsLevel = 0;  break;
        case 3:  SE_DebugGraphicsLevel = 0;  break;
        case 4:  SE_DebugGraphicsLevel = 0;  break;
        case 5:  SE_DebugGraphicsLevel = 1;  break;
        case 6:  SE_DebugGraphicsLevel = 2;  break;
        case 7:  SE_DebugGraphicsLevel = 3;  break;
        case 8:  SE_DebugGraphicsLevel = 4;  break;
        case 9:  SE_DebugGraphicsLevel = 0;  break;
        case 10: SE_DebugGraphicsLevel = 0;  break;
    }
# endif
# ifdef MA_DEBUG
    switch (layout)
    {
        case 0:  MA_DebugLevel = 0;  break;
        case 1:  MA_DebugLevel = 0;  break;
        case 2:  MA_DebugLevel = 0;  break;
        case 3:  MA_DebugLevel = 0;  break;
        case 4:  MA_DebugLevel = 0;  break;
        case 5:  MA_DebugLevel = 0;  break;
        case 6:  MA_DebugLevel = 0;  break;
        case 7:  MA_DebugLevel = 0;  break;
        case 8:  MA_DebugLevel = 0;  break;
        case 9:  MA_DebugLevel = 1;  break;
        case 10: MA_DebugLevel = 2;  break;
    }
#endif
}
