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

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//   ������������
//   ������:     CImage.dll - 31 Jan 2000
//               RDIB.dll   - 31 Jan 2000
//////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "cricontrol.h"
#include "crimemory.h"
/////////////////////////////////////////////////
//#define RIMAGE_DUMP_ENABLE

#ifdef RIMAGE_DUMP_ENABLE
#include "PumaMemoryToFileDumper.h"
#endif
//////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CRIControl::CRIControl()
{
	mpSourceDIB      = NULL;
	mpDestinationDIB = NULL;
	mpBinarizator    = NULL;
	mpTurner         = NULL;
	mpInvertor       = NULL;
	mpRotator        = NULL;
	mp_TurnedDIB     = NULL;
	mbMarginsFlag    = FALSE;
	DIBOpeningType   = FALSE;
	mcLastDIBName[0] = 0x0;

	/*
#define DecFunction(a) FNCIMAGE##a a; if(!CIMAGE_GetExportData(CIMAGE_FN_##a, &a)) \
				printf("CIMAGE_GetExportData == FALSE : %-3i,%s \n",a,CIMAGE_GetReturnString(CIMAGE_GetReturnCode()));
// \
	DecFunction(GetData);
	DecFunction(ReplaceData);
	DecFunction(GetCallbackImage);
	DecFunction(WriteCallbackImage);
	DecFunction(WriteDIB);
	DecFunction(ReadDIB);
	DecFunction(GetImageInfo);
	DecFunction(DeleteImage);
	DecFunction(FreeCopedDIB);

#undef  DecFunction
  */
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CRIControl::~CRIControl()
{
	if ( mpBinarizator )
		delete mpBinarizator;

	if ( mpTurner )
		delete mpTurner;

	if ( mpInvertor )
		delete mpInvertor;

	if ( mpRotator )
		delete mpRotator;

	if ( mpDestinationDIB )
		delete mpDestinationDIB;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Bool32 CRIControl::SetMargins(PRIMAGEMARGINS pMargins)
{
	SetReturnCode_rimage(IDS_RIMAGE_UNDER_CONSTRUCTION);
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Bool32 CRIControl::Binarise(PChar8 cDIBIn, PChar8 cDIBOut, Word32 wFlag, Word32 UseMargins)
{
	Bool32 Ret = TRUE;
	CTBinarize bType = CTBIN_UNKNOWN;
	// ��������� ��������
	if ( !OpenSourceDIB(cDIBIn) )
	{
		return FALSE;
	}
	
		/*
    if ( !SupportedIndexColorImage(mpSourceDIB) )
    {
        CloseSourceDIB();
		SetReturnCode_rimage(IDS_RIMAGE_NOTSUPPORTED_INDEX_COLOR);
		return FALSE;
    }
		*/
	// ������� �����
	if ( ! CreateDestinatonDIB(1) )           // create DIB 1 bit per pixel         
	{
        CloseSourceDIB();
		SetReturnCode_rimage(IDS_RIMAGE_CANNOT_CREATE_NEW_DIB);
		return FALSE;
	}
	//��������� �����������
	if ( !mpBinarizator )
	{
		mpBinarizator = new CRIBinarizator(&mcProgress);
	}
	// ���������� ���� ��������
	if ( !mpBinarizator->SetRasters(mpSourceDIB, mpDestinationDIB) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_CANNOT_SET_DIB);
		Ret = FALSE;
	}

	if ( wFlag < 4 )
	{
		bType = CTBIN_DEZA;
	}
	else
	{
		bType = CTBIN_KRONROD;
	}
	// ����������
	if ( !mpBinarizator->Binarize(bType, wFlag) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_CANT_BINARYZE);
		Ret = FALSE;
	}
	//��������� ����� � ��������� � �����������
	if ( !CloseDestinationDIB(cDIBOut) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_UNDER_CONSTRUCTION);
		Ret = FALSE;
	}

	//��������� ��������
	if ( !CloseSourceDIB() )
	{
		SetReturnCode_rimage(IDS_RIMAGE_UNDER_CONSTRUCTION);
		Ret = FALSE;
	}
	return Ret;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Bool32 CRIControl::Rotate(PChar8  cDIBIn, PChar8  cDIBOut, Int32 High, Int32 Low, Word32 UseMargins)
{
	Bool32 Ret = TRUE;
	Bool32 NoDest = FALSE;

	// ��������� ��������
	if ( !OpenSourceDIB(cDIBIn) )
	{
		return FALSE;
	}
	
	if ( mpDestinationDIB )
	{
		SetReturnCode_rimage(IDS_RIMAGE_INTERNAL_MODULE_ERROR);
		return FALSE;
	}

	mpDestinationDIB = new CTDIB;

	//��������� ��������
	if ( !mpRotator )
	{
		mpRotator = new CRRotator(&mcProgress);
	}

	// �������� ������ ���
	mcLastDIBName[0] = 0x0;

	if ( !mpRotator->Rotate(mpSourceDIB, mpDestinationDIB, High, Low) )
	{
		Word16 wRet = GetReturnCode_rimage();
// !!! Art ������� - ������ ��� ������� �� ������, � ���������, � �� ������ �������
//������-��...
		//		Handle hDIBtoSet;
		PVOID  pDIBtoSet;

		if ( (wRet == IDS_RIMAGE_ZERO_NUMERATOR_OR_DENUMERATOR ||
			  wRet == IDS_RIMAGE_ANGLE_LEAST_MINIMUM )         &&
			  mpSourceDIB->GetDIBPtr( &pDIBtoSet )
			  /*mpSourceDIB->GetDIBHandle(&hDIBtoSet)*/ )
		{
//			SetDIB(cDIBOut, hDIBtoSet);
			WriteDIB(cDIBOut, pDIBtoSet);
			SetReturnCode_rimage(IDS_RIMAGE_ERR_NO);
			NoDest = Ret = TRUE;
		}
		else
		{
			SetReturnCode_rimage(IDS_RIMAGE_CANNOT_ROTATE_IMAGE);
			Ret = FALSE;
		}
	}
	else
	{
		WriteDIBtoBMP("Allex.DIBBeforeDeskew.bmp",mpSourceDIB);
		WriteDIBtoBMP("Allex.DIBAfterDeskew.bmp",mpDestinationDIB);
	}

	//��������� ����� � ��������� � �����������
	if ( !CloseDestinationDIB(cDIBOut) )
	{
		if ( NoDest == FALSE )
		{
			SetReturnCode_rimage(IDS_RIMAGE_CANNT_SAVE_OUTCOMING_DIB);
			Ret = FALSE;
		}
	}

	strcpy(mcLastDIBName, cDIBOut);

	//��������� ��������
	if ( !CloseSourceDIB() )
	{
		SetReturnCode_rimage(IDS_RIMAGE_UNDER_CONSTRUCTION);
		Ret = FALSE;
	}
	return Ret;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Bool32 CRIControl::Turn(PChar8  cDIBIn, PChar8  cDIBOut, Word32 wFlag, Word32 UseMargins)
{
	Int32     NewWidth;
	Int32     NewHeight;
	Bool32    bRet = FALSE;
	//void *   pSDIB;

	if ( wFlag != RIMAGE_TURN_90 && wFlag != RIMAGE_TURN_270 && wFlag != RIMAGE_TURN_180 )
	{
		SetReturnCode_rimage(IDS_RIMAGE_INVALID_FUNCTION_PARAMETR);
		return FALSE;
	}

	if ( mp_TurnedDIB != NULL )
	{
		SetReturnCode_rimage(IDS_RIMAGE_INTERNAL_MODULE_ERROR);
		return FALSE;
	}
	// ��������� ��������
	if ( !OpenSourceDIB(cDIBIn) )
	{
		return FALSE;
	}
	NewWidth = ( wFlag == RIMAGE_TURN_180 ? mpSourceDIB->GetImageWidth() : mpSourceDIB->GetImageHeight() );
	NewHeight = ( wFlag == RIMAGE_TURN_180 ? mpSourceDIB->GetImageHeight() : mpSourceDIB->GetImageWidth() );
	/*
	if ( !mpSourceDIB->GetDIBPtr( &pSDIB ) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_INVALID_EXTERNAL_DIB);
		return FALSE;
	}
	*/
	//��������� ��������
	if ( !mpTurner )
	{
		mpTurner = new CRTurner;
	}

	// ������� ���������
	if ( mpDestinationDIB )
	{
		SetReturnCode_rimage(IDS_RIMAGE_INTERNAL_MODULE_ERROR);
		return FALSE;
	}

	mpDestinationDIB = new CTDIB;
	RIMAGEComment("Turn - temporary destination DIB");
	mpDestinationDIB->SetExternals( RIMAGEAlloc, RIMAGEFree, RIMAGELock, RIMAGEUnlock);

	if ( mpDestinationDIB->CreateDIBBegin(NewWidth, 
		                                  NewHeight,
										  mpSourceDIB->GetPixelSize()) &&
	     mpDestinationDIB->CopyPalleteFromDIB(mpSourceDIB) &&
		 mpDestinationDIB->CopyDPIFromDIB(mpSourceDIB) &&
		 mpDestinationDIB->CreateDIBEnd()  )
	{
		bRet = mpTurner->TurnDIB(mpSourceDIB, mpDestinationDIB, wFlag );	
	}

	

	// ������
	/*
	if ( !(mp_TurnedDIB = mpTurner->TurnDIB(pSDIB, wFlag)) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_CANT_TURN_DIB);
		return FALSE;
	}
	*/

	/*
	//��������� ����� � ��������� � �����������
	if ( !WriteDIB(cDIBOutt, mp_TurnedDIB) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_UNABLE_WRITE_DIB);
		return FALSE;
	}

	if ( !mpTurner->FreeDIB(mp_TurnedDIB) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_INVALID_EXTERNAL_DIB);
		return FALSE;
	}

	mp_TurnedDIB = NULL;
	*/ 
	//��������� ����� � ��������� � �����������
	if ( !CloseDestinationDIB(cDIBOut) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_CANNT_SAVE_OUTCOMING_DIB);
		bRet = FALSE;
	}
	//��������� ��������
	if ( !CloseSourceDIB() )
	{
		SetReturnCode_rimage(IDS_RIMAGE_UNDER_CONSTRUCTION);
		bRet = FALSE;
	}
	return bRet;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Bool32 CRIControl::Inverse(PChar8  cDIBIn, PChar8  cDIBOut, Word32 UseMargins)
{
	Bool32    bErrors = TRUE;
	// �������� �� ��������� DIB � ��������������
	// �������� ����������� mpDescinationDIB � ������ mpSourceDIB
	if ( !OpenDestinationDIBfromSource( cDIBIn ) )
	{
		return FALSE;
	}
	
	//��������� ��������
	if ( !mpInvertor )
	{
		mpInvertor = new CRInvertor;
	}
	
	// �����������
	if ( !mpInvertor->Inverse(mpDestinationDIB) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_CANNOT_INVERT_IMAGE);
		bErrors = FALSE;
	}

	//��������� ����� � ��������� � �����������
	if ( !SetDestinationDIBtoStorage(cDIBOut) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_UNABLE_WRITE_DIB);
		bErrors = FALSE;
	}

	return bErrors;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� ��� ������������
Bool32 CRIControl::GetDIB(PChar8  cDIB, PHandle phDIB)
{
	// ����� � ������������, ��� � ����� ����!
	if ( CIMAGE_ReadDIB((PWord8)cDIB, phDIB, TRUE) )
		return TRUE;

	SetReturnCode_rimage(IDS_RIMAGE_NO_IMAGE_FOUND);
	return FALSE;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// �������� ��� ������������
Bool32 CRIControl::SetDIB(PChar8  cDIB, Handle hDIB)
{
	if ( CIMAGE_WriteDIB((PWord8)cDIB, hDIB, TRUE) )
		return TRUE;

	SetReturnCode_rimage(IDS_RIMAGE_UNABLE_WRITE_DIB);
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� c �������������
Bool32 CRIControl::WriteDIB(PChar8  cDIB, Handle hDIB)
{
	if ( CIMAGE_WriteDIB((PWord8)cDIB, hDIB, FALSE) )
		return TRUE;

	SetReturnCode_rimage(IDS_RIMAGE_NO_IMAGE_FOUND);
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� � �������������
Bool32 CRIControl::ReadDIB(PChar8  cDIB, PHandle phDIB)
{
	if ( CIMAGE_ReadDIB((PWord8)cDIB, phDIB, FALSE) )
		return TRUE;

	SetReturnCode_rimage(IDS_RIMAGE_UNABLE_WRITE_DIB);
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close Source DIB
Bool32 CRIControl::CloseSourceDIB()
{
	
	Handle    hDIB;

	if ( mpSourceDIB == NULL )
	{
		SetReturnCode_rimage(IDS_RIMAGE_NOT_OPENED);
		return FALSE;
	}

	if ( mpSourceDIB->GetDIBHandle(&hDIB) )
	{
		RIMAGEUnlock(hDIB);
	}

	delete mpSourceDIB;
	CIMAGE_FreeCopedDIB(hDIB);

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Bool32 CRIControl::OpenSourceDIB(PChar8  cDIBName)
{
	Handle  hDIBIn;
	PVOID   pDIB;
	
	if ( !ReadDIB(cDIBName, &hDIBIn) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_NO_IMAGE_FOUND);
		return FALSE;
	}

	if ( !(pDIB = RIMAGELock(hDIBIn) ) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_INTERNAL_MODULE_ERROR);
		return FALSE;
	}

	mpSourceDIB = new CTDIB(hDIBIn);

	if ( !mpSourceDIB->SetDIBbyPtr(pDIB) )
	{
		delete mpSourceDIB;
		mpSourceDIB = NULL;
		SetReturnCode_rimage(IDS_RIMAGE_DIB_NOT_ATTACHED);
		return FALSE;
	}

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//������� ��������� DIB ���� �������, ��� ��������
Bool32 CRIControl::CloseDestinationDIB(PChar8  cDIBName)
{
	Handle hDIB = NULL;
	PVOID  pDIB = NULL;

	if ( DIBOpeningType == TRUE )
	{
		return SetDestinationDIBtoStorage(cDIBName);
	}

	if ( !mpDestinationDIB )
		return FALSE;

	if ( !mpDestinationDIB->GetDIBHandle(&hDIB) ||
		 !mpDestinationDIB->GetDIBPtr( &pDIB )     )
	{
		delete mpDestinationDIB;
		mpDestinationDIB = NULL;
		return FALSE;
	}
	
	if ( !WriteDIB(cDIBName, pDIB) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_NO_IMAGE_FOUND);
		return FALSE;
	}

	/*
	while ( mpDestinationDIB )
	{
		if ( mpDestinationDIB->DestroyDIB() )
		{
			hDIB = NULL;
		}
		else
		{
			if ( mpDestinationDIB->GetDIBHandle(&hDIB) )
			{
				RIMAGEUnlock(hDIB);
				RIMAGEFree(hDIB);
			}
			else
			{
				delete mpDestinationDIB;
				mpDestinationDIB = NULL;
			}
		}
	}
	*/
	delete mpDestinationDIB;
	mpDestinationDIB = NULL;

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// Creating new DIB by CTDIB class and 4 RIMAGE functions
Bool32 CRIControl::CreateDestinatonDIB(Word32 BitCount)
{
	Word32 wNewHeight;
	Word32 wNewWidth;
	Word32 wXResolution;
	Word32 wYResolution;
	CTDIBRGBQUAD       BWQuads[2] = {{0x00,0x00,0x00,0x00},{0xff,0xff,0xff,0x00} };
	

	if ( mpSourceDIB == NULL )
	{
		SetReturnCode_rimage(IDS_RIMAGE_NOT_OPENED);
		return FALSE;
	}

	mpDestinationDIB = new CTDIB;
	
	RIMAGEComment("CreateDestinationDIB - temporary DIB");
	if ( !mpDestinationDIB->SetExternals(RIMAGEAlloc, RIMAGEFree, RIMAGELock, RIMAGEUnlock) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_PREPARE_TO_CREATE);
		delete mpDestinationDIB;
		mpDestinationDIB = NULL;
		return FALSE;
	}

	wNewHeight = (mbMarginsFlag ? abs(mrMargins.rmBottomMarg - mrMargins.rmTopMarg) : mpSourceDIB->GetLinesNumber());
	wNewWidth = (mbMarginsFlag ? abs(mrMargins.rmLeftMarg - mrMargins.rmRightMarg) : mpSourceDIB->GetLineWidth());
	mpSourceDIB->GetResolutionDPM( &wXResolution, &wYResolution);

	if ( !mpDestinationDIB->CreateDIBBegin( wNewWidth, wNewHeight, BitCount) )
	{
		return FALSE;
	}
	
	if ( !mpDestinationDIB->SetResolutionDPM(wXResolution, wYResolution) )
	{
		//return FALSE;
	}

	if ( !mpDestinationDIB->SetRGBQuad(0, BWQuads[0] ) )
	{
		return FALSE;
	}

	if ( !mpDestinationDIB->SetRGBQuad(1, BWQuads[1] ) )
	{
		return FALSE;
	}
	
	if ( !mpDestinationDIB->CreateDIBEnd() )
	{
		return FALSE;
	}
	return TRUE;
}

Bool32 CRIControl::OpenDestinationDIBfromSource(PChar8  cDIBName)
{
	Handle  hDIBIn;
	PVOID   pDIB;
	
	if ( mpSourceDIB != NULL )
		return FALSE;

	if ( !ReadDIB(cDIBName, &hDIBIn) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_NO_IMAGE_FOUND);
		return FALSE;
	}

	if ( !(pDIB = RIMAGELock(hDIBIn) ) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_INTERNAL_MODULE_ERROR);
		return FALSE;
	}

	mpDestinationDIB = new CTDIB(hDIBIn);

	if ( !mpDestinationDIB->SetDIBbyPtr(pDIB) )
	{
		delete mpSourceDIB;
		mpDestinationDIB = NULL;
		SetReturnCode_rimage(IDS_RIMAGE_DIB_NOT_ATTACHED);
		return FALSE;
	}

	DIBOpeningType = TRUE;
	return TRUE;
}

Bool32 CRIControl::SetDestinationDIBtoStorage(PChar8  cDIBName)
{
	Handle hSDIB;
	Bool32  bErrors = TRUE;
	
	if ( DIBOpeningType == FALSE)
	{
		return CloseDestinationDIB(cDIBName);
	}
	// ����������� � ���� ��������� � CIMAGE ��� ��������
	if ( mpDestinationDIB == NULL )
		return FALSE;
	
	if ( !mpDestinationDIB->GetDIBHandle(&hSDIB) )
		return FALSE;

	if ( !SetDIB(cDIBName, hSDIB ) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_NO_IMAGE_FOUND);
		return FALSE;
	}
	
	
	if ( !CIMAGE_FreeCopedDIB(hSDIB) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_CIMAGE_MEMORY_ERROR);
		bErrors = FALSE;
	}

	delete mpDestinationDIB;
	mpDestinationDIB = NULL;
	DIBOpeningType = FALSE;

	return bErrors;
}

Bool32 CRIControl::Roll(PChar8 cDIBIn, PChar8 cDIBOut, Int32 Num, Int32 Denum, Word32 bUseMargins)
{
	Bool32 Ret = TRUE;

	// ��������� ��������
	if ( !OpenSourceDIB(cDIBIn) )
	{
		return FALSE;
	}

	if ( mpDestinationDIB )
	{
		SetReturnCode_rimage(IDS_RIMAGE_INTERNAL_MODULE_ERROR);
		return FALSE;
	}
	mpDestinationDIB = new CTDIB;

	//��������� ��������
	if ( !mpRotator )
	{
		mpRotator = new CRRotator;
	}

	if ( !mpRotator->Roll(mpSourceDIB, mpDestinationDIB, Num, Denum) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_CANNOT_ROTATE_IMAGE);
		Ret = FALSE;
	}

	//��������� ����� � ��������� � �����������
	if ( !CloseDestinationDIB(cDIBOut) )
	{
		SetReturnCode_rimage(IDS_RIMAGE_CANNT_SAVE_OUTCOMING_DIB);
		Ret = FALSE;
	}

	//��������� ��������
	if ( !CloseSourceDIB() )
	{
		SetReturnCode_rimage(IDS_RIMAGE_UNDER_CONSTRUCTION);
		Ret = FALSE;
	}
	return Ret;
}

Bool32 CRIControl::SetProgressCallBacks(PRIMAGECBPRogressStart pcbStart, PRIMAGECBPRogressStep pcbStep, PRIMAGECBPRogressFinish pcbFinish)
{
	return mcProgress.SetExternals((CRPStart)pcbStart, (CRPFinish)pcbFinish, (CRPStep)pcbStep);
}

Bool32 CRIControl::StartProgress()
{
	return mcProgress.Start();
}

Bool32 CRIControl::RotatePoint(PChar8 cDIB, Int32 iX, Int32 iY, PInt32 prX, PInt32 prY)
{
	Bool32 bRet = FALSE;

	if ( mpRotator && strcmp(cDIB, mcLastDIBName) == 0 )
	{
		bRet = mpRotator->RotatePoint(iX, iY, prX, prY);
	}

	return bRet;
}

Bool32 CRIControl::WriteDIBtoBMP(PChar8 cName, PCTDIB pDIB)
{
#ifdef RIMAGE_DUMP_ENABLE
	
	Word32  wBMPSize = pDIB->GetDIBSize() + 14;
	PumaMemoryToFileDumper BMPDump(cName);
	
	BMPDump.AddDump("BM",2);
	BMPDump.AddDump((char *)&wBMPSize,4);
	wBMPSize = 0;
	BMPDump.AddDump((char *)&wBMPSize,4);
	wBMPSize = 14 + pDIB->GetHeaderSize() + pDIB->GetRGBPalleteSize();
	BMPDump.AddDump((char *)&wBMPSize,4);
	BMPDump.AddDump(pDIB->GetPtrToHeader(), pDIB->GetDIBSize());
	BMPDump.EndDump();

#endif
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// end of file
