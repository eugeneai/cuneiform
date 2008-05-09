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

//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
//                                                                              //
//                    Cognitive Technologies Ltd.                               //
//                                                                              //
//                    Data Storage Container                                    //
//                                                                              //
//                                                                              //
//                                                                              //
//                                                                              //
//                    started at 25 may 1998                                    //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////
#include <unistd.h>
#include "ctccontrol.h"
#include "compat_defs.h"
void SetReturnCode_cfio(Word16 rc);
//////////////////////////////////////////////////////////////////////////////////
//
CTCControl::CTCControl()
{
	char SystemTemp[_MAX_PATH];

	GetTempPath(CFIO_MAX_PATH, SystemTemp);
	SetFolder(CFIO_TEMP_FOLDER,SystemTemp);
	SetFolder(CFIO_FILE_FOLDER,SystemTemp);
	CFIO_STRCAT(SystemTemp,"STORAGE\\");
	SetFolder(CFIO_STORAGE_FOLDER,SystemTemp);
}
//////////////////////////////////////////////////////////////////////////////////
//
CTCControl::~CTCControl()
{
}
//////////////////////////////////////////////////////////////////////////////////
//
static char SFullPath[CFIO_MAX_PATH];
static char SDisk[CFIO_MAX_PATH];
static char SFolder[CFIO_MAX_PATH];
static char SFile[CFIO_MAX_PATH];
static char SExtension[CFIO_MAX_PATH];
static char SOut[CFIO_MAX_PATH];
//////////////////////////////////////////////////////////////////////////////////
//
PChar8 CTCControl::FileNameToFolder(PChar8 Buffer, PChar8 FolderName, PChar8 FileName, Word32 Size)
{
	PChar8      i, j; 
	Word32      SizeOfFolder = CFIO_STRLEN(FolderName);
	Word32      SizeOfFile =   CFIO_STRLEN(FileName);
	Word32      Shift = SizeOfFolder;

	if ( FolderName == FileName)
		return NULL;

	if ( ( SizeOfFolder + SizeOfFile )  < Size )
	{
		if ( Buffer != FolderName && Buffer != FileName)
			CFIO_STRCPY(Buffer, FolderName);

		if ( Buffer == FileName && Buffer != FolderName )
		{
			if ( FolderName[SizeOfFolder-1] == '\\' && FileName[0] == '\\' )
			{
				Shift--;
			}
			
			if ( FolderName[SizeOfFolder-1] != '\\' && FileName[0] != '\\' )
			{
				Shift++;
			}
		//	FileName = FolderName;
		//	FolderName = Buffer;
			for( i = Buffer, j = FolderName; i < &Buffer[Shift]; *(i + Shift) = *(i), *(i++) = *(j++) );
			
			if ( *i != '\\' && *(i-1) != '\\' )
			{
				*(i-1) = '\\';
			}
			return Buffer;
		}
		
		if ( Buffer[SizeOfFolder-1] == '\\' && FileName[0] == '\\' )
		{
			Buffer[SizeOfFolder-1] = 0x0;
		}
		
		if ( Buffer[SizeOfFolder-1] != '\\' && FileName[0] != '\\' )
		{
			CFIO_STRCAT(Buffer, "\\");
		}
		
		CFIO_STRCAT(Buffer, FileName);
	}
	else
		Buffer[0] = 0x0;

	return Buffer;

}
//////////////////////////////////////////////////////////////////////////////////
//
PChar8 CTCControl::MakeNameForStorage(PChar8 FileName, CTCStorageHeader * hStorageHead, Bool32 KeepFileName)
{
	  PChar8 i;
	//PChar8 j;
	//Word32 StorageFolderNameSize = 0;
	//Word32 FolderNameSize = 0;
	//Word32 FileNameSize = 0;
	//Word32 Append;
	
	if ( !FileName )
		return NULL;

	if ( strlen ( FileName ) > CFIO_MAX_PATH )
		return FileName;
	
	// �������� ����� ���������
	if ( hStorageHead )
	{
		CFIO_STRCPY( szBuffer, hStorageHead->GetStorageFolder() ); 
	}
	else
	{
		GetFolder(CFIO_STORAGE_FOLDER, &szBuffer[0]);
	}
	//��������� �� ����������
	CFIO_GETFOLDERSITEMS(szBuffer, SDisk, SFolder, SFile, SExtension);
	// ������ ���� � ������
	CFIO_STRCPY(szBuffer,SFolder);
	// ������ ������� �� �����, ��� ��� ��� ������ ����
	CFIO_STRCAT(szBuffer,SFile);

	i = &szBuffer[CFIO_STRLEN(szBuffer) - 1];
	
	i++;
	*i = '\\';
	*(i+1) = 0x0;

	CFIO_GETFOLDERSITEMS(FileName, SDisk, SFolder, SFile, SExtension);

	//  ��� ��������� ��������� ������ ��� ����� � �����������

	CFIO_MAKEPATH(SOut, NULL, NULL, SFile, SExtension);
	
	return SOut;
	
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::GetFolder(Word32 wFolder, PChar8 pcBuff)
{
	switch(wFolder)
	{
	case CFIO_TEMP_FOLDER :
		CFIO_STRCPY(pcBuff, (PChar8)szTempFolder);
		break;

	case CFIO_FILE_FOLDER :
		CFIO_STRCPY(pcBuff, (PChar8)szFileFolder);
		break;

	case CFIO_STORAGE_FOLDER :
		CFIO_STRCPY(pcBuff, (PChar8)szStorageFolder);
		break;

	default :
		return FALSE;
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::SetFolder(Word32 wFolder, PChar8 pcBuff)
{
	if ( strlen( pcBuff ) < _MAX_PATH )
	{
		switch(wFolder)
		{
		case CFIO_TEMP_FOLDER :
			CFIO_STRCPY((PChar8)szTempFolder, pcBuff);
			break;

		case CFIO_FILE_FOLDER :
			CFIO_STRCPY((PChar8)szFileFolder, pcBuff);
			break;

		case CFIO_STORAGE_FOLDER :
			CFIO_STRCPY((PChar8)szStorageFolder, pcBuff);
			break;

		default :
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
Handle CTCControl::OpenStorage( PChar8 lpName, Word32 wFlag )
{
	Handle  OpenedStorage = NULL;
	if ( wFlag & OS_OPEN )
	{
		OpenedStorage = OpenCompliteStorage( lpName, wFlag );
	}
	else
	{
		wFlag |= OS_CREATE;
		OpenedStorage = OpenNewStorage( lpName, wFlag );
	}
		
	return OpenedStorage;
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::CloseStorage(Handle  hStorage, Word32  wFlag)
{
	Word32   wCompliteFlag = 0;
	Word32   wCloseFlag = 0;

	if ( wFlag & CS_WITHOUT_SAVE ||
		 wFlag & CS_DELETE          )
	{
		if ( wFlag & CS_ALL )
			return CloseAllStorageFile( hStorage, wFlag );
		else
			return CloseStorageFile( hStorage, wFlag );
	}
	
	if ( wFlag & CS_ALL )
	{
		CompliteAllStorage( hStorage, wFlag );
		return CloseAllStorageFile( hStorage, wFlag );
	}
	else
	{
		return CloseStorageFile( CompliteStorage( hStorage, wFlag ) );
	}
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::DeleteStorage(PChar8 lpName)
{
	return (unlink(lpName) == 0);
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::WriteFileToStorage(Handle hStorage, Handle hFile, PChar8 lpName)
{
	char FileName[CFIO_MAX_PATH];
	// ����� ����� ����������.... ��� �� �����, ���� ���
	CTCStorageHeader * pStorageHeader = StorageList.GetItemHeader(hStorage);
	// ����� ����� ����� ........ ��� �� �����, ����� ����
	CTCFileHeader * pFileHeader = FileList.GetItemHeader(hFile);
	CTCGlobalFile * pFile;

	if ( pStorageHeader && pFileHeader)
	{
		if ( CFIO_STRLEN(lpName) < CFIO_MAX_PATH )
		{
			CFIO_STRCPY(FileName, lpName);
			AttachFileToStorage(hFile,hStorage,0);
			pFile = pFileHeader->GetFile();
			pFile->SetFileName(FileName);
			pFileHeader->KeepName();

			return TRUE;
		}
	}

	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
Handle CTCControl::ReadFileFromStorage(Handle hStorage, PChar8 lpName)
{
	char FileName[CFIO_MAX_PATH];
	// ����� ����� ����������.... ��� �� �����, ���� ���
	CTCStorageHeader * pStorageHeader = StorageList.GetItemHeader(hStorage);

	if ( pStorageHeader )
	{
		if ( FileNameToFolder(FileName, pStorageHeader->GetStorageFolder(), lpName, CFIO_MAX_PATH) )
		{
			return OpenFile(NULL,FileName,OSF_READ|OSF_WRITE|OSF_BINARY);
		}
	}

	return NULL;
}
//////////////////////////////////////////////////////////////////////////////////
//
Handle CTCControl::OpenFile(Handle hStorage, PChar8 lpName, Word32 wFlag)
{
	Word32 FileFlag = 0x0;

	if ( wFlag & OSF_CREATE )
		FileFlag |= CFIO_FILE_CREATE;
	
	if ( wFlag & OSF_OPEN )
		FileFlag |= CFIO_FILE_OPEN;
	
	if ( wFlag & OSF_READ )
		FileFlag |= CFIO_FILE_READ;
	
	if ( wFlag & OSF_WRITE )
		FileFlag |= CFIO_FILE_WRITE;

	if ( wFlag & OSF_BINARY )
		FileFlag |= CFIO_FILE_BINARY;

	if ( wFlag & OSF_IN_MEMORY )
		FileFlag |= CFIO_FILE_IN_MEMORY;

	if ( wFlag & OSF_TEMPORARY )
		FileFlag |= CFIO_FILE_TEMPORARY;

	return OpenFileAndAttach( lpName, FileFlag, hStorage);
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::CloseFile(Handle hFile, Word32 wFlag, Handle hStorage)
{

	if ( wFlag & CSF_SAVEDISK )
	{
		return CloseFileAndDettach(hFile, wFlag, hStorage);
	}
	if ( wFlag & CSF_SAVESTORAGE )
	{
		return CloseFileAndAttach(hFile, wFlag, hStorage);
	}
	if ( wFlag & CSF_DELETE )
	{
		return DeleteFileFromDisk(hFile);
	}
	if ( wFlag & CSF_WRITE )
	{
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::WriteFile(Handle hFile, PInt8 lpData, Word32 wSize)
{
	return WriteDataToFile(hFile, (void *) lpData, wSize);
}
//////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::ReadFromFile(Handle hFile, PInt8 lpData, Word32 wSize)
{
	return ReadDataFromFile(hFile, (void *)lpData, wSize);
}
//////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::Seek(Handle hFile, Word32 wBytes, Word32 wFrom)
{
	Word32 wDirect;

	switch ( wFrom )
	{
	case FS_END :
		wDirect = CFIO_GF_SEEK_END;
		break;
	case FS_BEGIN :
		wDirect = CFIO_GF_SEEK_BEG;
		break;
	case FS_CUR :
	default:
		wDirect = CFIO_GF_SEEK_CURR;
		break;
	}
	return SeekFilePointer( hFile, wBytes, wDirect);
}
//////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::Tell(Handle hFile)
{
	return TellFilePointer(hFile);
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::Flush(Handle hFile)
{
	return FlushFile(hFile);
}
//////////////////////////////////////////////////////////////////////////////////
//
Handle CTCControl::Alloc(Word32 wSize, Word32 wFlag, const char *cOwner, const char *Coment)
{
	int iTestFixed = 0;
	Bool32 Global = FALSE;
	Word32 GlobalFlag = 0x0;
	
	if ( wFlag & MAF_GPTR || wFlag & MAF_GNHD )
	{
		return NULL;
	}

#ifdef CFIO_USE_GLOBAL_MEMORY
	Global = TRUE;
#else
	Global = FALSE;
#endif

	if ( wFlag & MAF_GALL_GMEM_FIXED )
	{
		GlobalFlag |= GMEM_FIXED;
		iTestFixed = 1;
	}

	if ( wFlag & MAF_GALL_GMEM_MOVEABLE && !iTestFixed )
		GlobalFlag |= GMEM_MOVEABLE;

	if ( wFlag & MAF_GALL_GPTR )
		GlobalFlag |= GPTR;

	if ( wFlag & MAF_GALL_GHND )
		GlobalFlag |= GHND;

	if ( wFlag & MAF_GALL_GMEM_DDESHARE )
		GlobalFlag |= GMEM_DDESHARE;

	if ( wFlag & MAF_GALL_GMEM_DISCARDABLE && iTestFixed )
		GlobalFlag |= GMEM_DISCARDABLE;

	if ( wFlag & MAF_GALL_GMEM_LOWER )
		GlobalFlag |= GMEM_LOWER;

	if ( wFlag & MAF_GALL_GMEM_NOCOMPACT )
		GlobalFlag |= GMEM_NOCOMPACT;

	if ( wFlag & MAF_GALL_GMEM_NODISCARD )
		GlobalFlag |= GMEM_NODISCARD;

	if ( wFlag & MAF_GALL_GMEM_NOT_BANKED)
		GlobalFlag |= GMEM_NOT_BANKED;

	if ( wFlag & MAF_GALL_GMEM_NOTIFY )
		GlobalFlag |= GMEM_NOTIFY;
	
	if ( wFlag & MAF_GALL_GMEM_SHARE )
		GlobalFlag |= GMEM_SHARE;

	if ( wFlag & MAF_GALL_GMEM_ZEROINIT )
		GlobalFlag |= GMEM_ZEROINIT;

	return AllocNewMemory( GlobalFlag, wSize, Global, cOwner, Coment );
}
//////////////////////////////////////////////////////////////////////////////////
// GlobalRealloc
Handle CTCControl::ReAlloc(Handle hMemory, Word32 wNewSize, Word32 wFlag)
{
	Handle hNewMemory;
	Word32 wOldSize = 0;
	Word32 wOldFlag = 0;
	Word32 GlobalFlag = 0;
	void * Sorc;
	void * Desc;

	switch(wFlag)
	{
	case MRF_NEW_MEMORY:

		MemoryList.TakeItem(hMemory, &wOldSize, &wOldFlag);
		hNewMemory = Alloc(wNewSize,(wOldFlag == TRUE ? MAF_GALL_GHND : MAF_GALL_GPTR),"Realloced","No comment");

		if ( hNewMemory )
		{
			Desc = Lock(hNewMemory);
			Sorc = Lock(hMemory);
			CopyMemory(Desc, Sorc,(wOldSize < wNewSize ? wOldSize : wNewSize));
			Unlock(hNewMemory);
			Unlock(hMemory);
			Free(hMemory);
		}
		break;

	default :
		
		if ( wFlag & MAF_GALL_GMEM_MOVEABLE )
			GlobalFlag |= GMEM_MOVEABLE;

		if ( wFlag & MAF_GALL_GPTR )
			GlobalFlag |= GPTR;

		if ( wFlag & MAF_GALL_GHND )
			GlobalFlag |= GHND;

		if ( wFlag & MAF_GALL_GMEM_DDESHARE )
			GlobalFlag |= GMEM_DDESHARE;

		{
			CTCMemoryHeader * Memory = MemoryList.GetItem(hMemory);

			if ( Memory )
			{
				hNewMemory = GlobalReAlloc(hMemory, wNewSize, GlobalFlag);
				Memory->SetHandle(hNewMemory);
				Memory->SetSize(wNewSize);
			}
		}
	}

	return hNewMemory;
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::Free(Handle hMem)
{
	return FreeMemory(hMem);
}
//////////////////////////////////////////////////////////////////////////////////
//
LPVOID CTCControl::Lock(Handle hMem)
{
	return LockMemory(hMem);
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::Unlock(Handle hMem)
{
	return UnlockMemory(hMem);
}
//////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::WriteMemToFile(Handle hMem, PChar8 lpName)
{
	Handle  hFile = OpenFile(NULL, lpName, OSF_WRITE );
	Word32  wMemorySize;
	Word32  wMemoryFlag;
	Word32  Counter = 0;
	PInt8  pMem;

	if ( hFile && hMem)
	{
		MemoryList.TakeItem(hMem, &wMemorySize, &wMemoryFlag );
		Seek(hFile, 0, FS_END);
		pMem = (PInt8)Lock(hMem);
		
		if ( pMem )
		{
			Counter += WriteFile(hFile,pMem,wMemorySize);
		}

		Unlock(hMem);

		Flush(hFile);

		CloseFile(hFile,CSF_SAVEDISK,NULL);
	}
	return Counter;
}
//////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::ReadMemFromFile(PChar8 lpName, Handle * phMem, Word32 wFlag)
{
	Handle  hFile = OpenFile(NULL, lpName, OSF_READ|OSF_BINARY );
	Handle  hMem;
	PInt8  pMem;
	Word32  wFileSize;
	Word32  Counter = 0;

	if ( hFile )
	{
		wFileSize = Seek(hFile, 0, FS_END);
		Seek(hFile, 0, FS_BEGIN);
		hMem = Alloc(wFileSize,wFlag,"Readed from file","lpName");
		*phMem = hMem;

		if ( hMem )
		{
			pMem = (PInt8)Lock(hMem);
			
			if ( pMem )
			{
				Counter += ReadFromFile(hFile,pMem,wFileSize);
			}

			Unlock(hMem);
		}
		CloseFile(hFile,CSF_SAVEDISK,NULL);
	}
	return Counter;
}
//////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::WriteMemToStorage(Handle hMem, Handle hStorage, PChar8 lpName)
{
	Word32 wData;
	Handle hFile;

	if ( wData = WriteMemToFile(hMem, lpName) )
	{
		hFile = OpenFile(hStorage, lpName, OSF_READ|OSF_BINARY);
		
		if ( hFile )
		{
			if ( !CloseFile(hFile, CSF_SAVESTORAGE, hStorage) )
				wData = 0;
		}
		else
		{
			wData = 0;
		}
	}
	return wData;	
}
//////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::ReadMemFromStorage(Handle hStorage, PChar8 lpName, Handle * phMem)
{
	char NameForStorage[CFIO_MAX_PATH];
	Handle   hMem;
	Word32 Readed = 0;

	*phMem = NULL;
	CTCStorageHeader * hStorageHead = StorageList.GetItemHeader(hStorage);

	if ( hStorageHead )
	{
		FileNameToFolder(NameForStorage,hStorageHead->GetStorageFolder(), lpName, _MAX_PATH);
		
		Readed = ReadMemFromFile(NameForStorage, &hMem );
		
		if ( Readed )
			*phMem = hMem;
	}
	
		return Readed;	
}
//////////////////////////////////////////////////////////////////////////////////
//
Handle CTCControl::AllocNewMemory(Word32 wFlag, Word32 wSize, Bool32 bGlobal, const char *cOwner, const char *Coment)
{
	Handle hNewMemory = NULL;

	if ( bGlobal )
	{
		// alloc new memory;
		hNewMemory = CFIO_ALLOC(wFlag, wSize);
	}
	else
	{
		hNewMemory = (Handle) ::new char[wSize];
	}

	if ( hNewMemory )
	{
		//add to list
		if ( AddNewMemoryInList( hNewMemory, wSize, bGlobal, cOwner, Coment ) )
			return hNewMemory;
		else
			//or free back
			GlobalFree(hNewMemory);
	}

	return NULL;
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::AddNewMemoryInList( Handle hMemory, Word32 wSize, Word32  IsGlobal, const char *cOwner, const char *Coment)
{
	return MemoryList.AddItem(hMemory, wSize, IsGlobal, cOwner, Coment);
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::TakeMemory(Handle hMemory, Word32 * wMemorySize, Word32 * wMemoryFlag)
{
	return MemoryList.TakeItem(hMemory, wMemorySize, wMemoryFlag); 
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::GetMemory(Handle hMemory, PPCTCMemoryHeader pHeader)
{
	*pHeader = MemoryList.GetItem(hMemory);
	return pHeader != NULL;
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::DeleteMemoryFromList(Handle hMemory)
{
	return MemoryList.DeleteItem(hMemory);
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::LockatorMemoryInList(Handle hMemory, Bool32 bLock)
{
	return MemoryList.LockUnlockItem(hMemory, bLock);
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::FreeMemory(Handle hMemory, Word32 wFlag)
{
	Word32 wMemoryStatus;
	Word32 wMemorySize;
	
	if( TakeMemory(hMemory, &wMemorySize, &wMemoryStatus) )
	{
		// delete header from list
		if ( DeleteMemoryFromList(hMemory) )
		{
			//now memory free at MemoryHeader destructor
			//if ( !GlobalFree(hMemory) )
				return TRUE;
		}
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
LPVOID CTCControl::LockMemory(Handle hMemory)
{
	Word32 wMemoryStatus;
	Word32 wMemorySize;
	LPVOID pMemory = NULL;
	// �� , ��� �������� �������. ���������� ����� � ������,
	// �� ���� ��� ������, � ��� ��� ���������� ������ �� ������������, �� � 
	// ������� ��� �� �����
	//PCTCMemoryHeader pMemoryHeader;

	if ( TakeMemory(hMemory, &wMemorySize, &wMemoryStatus) )
	{
	//if ( GetMemory(hMemory, &pMemoryHeader) )
	//{
	//	wMemorySize = pMemoryHeader->GetSize();
	//	wMemoryStatus = pMemoryHeader->GetFlag();
		
		if ( wMemorySize && (wMemoryStatus&CFIO_MEMORY_GLOBAL) )
		{
			// if memory can be locked
			if ( LockatorMemoryInList(hMemory, TRUE) )
#ifdef CFIO_USE_GLOBAL_MEMORY
				pMemory = CFIO_LOCK(hMemory);
#else
				pMemory = hMemory;
#endif
		}
		else 
		{
			pMemory = hMemory;
		}
	}

	return	pMemory;
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::UnlockMemory(Handle hMemory)
{
	Word32 wMemoryStatus;
	Word32 wMemorySize;
	Bool32 bUnlock = FALSE;

	if ( TakeMemory(hMemory, &wMemorySize, &wMemoryStatus) )
	{
		if ( wMemorySize && (wMemoryStatus&CFIO_MEMORY_GLOBAL) )
		{
			// if memory can be unlocked
			if ( LockatorMemoryInList(hMemory, FALSE) )
#ifdef CFIO_USE_GLOBAL_MEMORY
				bUnlock = CFIO_UNLOCK(hMemory);
#else
				bUnlock = TRUE;
#endif
		}
	}
	return bUnlock;
}
//////////////////////////////////////////////////////////////////////////////////
//
Handle CTCControl::OpenFileAndAttach(PChar8 lpName, Word32 Flag, Handle Storage)
{
	CTCGlobalFile * pNewFile = NULL;
	Handle          hOpened;

	// ���� �� ����������
	// �� ��� �� DecompliteStorage
	//MAKEFULLPATH(szBuffer, lpName, _MAX_PATH);
	
	if ( CFIO_STRLEN(lpName) < _MAX_PATH )
		CFIO_STRCPY(szBuffer,lpName);
	else
		return NULL;

	if ( hOpened = FileList.FindFile(szBuffer) )
	{
		szBuffer[0] = 0x0;
		return hOpened;
	}
	
	pNewFile = new CTCGlobalFile(szBuffer, Flag);
	
	if ( pNewFile )
	{
		szBuffer[0] = 0x0;
		return AddFileInList(pNewFile, Flag, Storage );	
	}

	szBuffer[0] = 0x0;
	return NULL;
}
//////////////////////////////////////////////////////////////////////////////////
//
Handle CTCControl::AddFileInList(CTCGlobalFile * File, Word32 Flag, Handle Storage)
{
	Handle ret=FileList.AddItem(File, Flag, Storage);
	if (!ret)
		SetReturnCode_cfio(IDS_CFIO_ERR_CANT_OPEN_FILE);
	return ret;
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::DeleteFileFromList(Handle File, Word32 Flag, Handle Stotrage)
{
	return FileList.DeleteItem(File, Flag);
}
//////////////////////////////////////////////////////////////////////////////////
//
Handle CTCControl::AddStorageInList(CTCGlobalFile * lpNewStorageName, Word32 wNewFlag)
{
	return StorageList.AddItem(lpNewStorageName, wNewFlag);
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::CloseFileAndDettach(Handle File, Word32 Flag, Handle Storage)
{
	CTCFileHeader * CurrentFileHeader = FileList.GetItemHeader(File);
	CTCGlobalFile * CurrentFile;

	if ( CurrentFileHeader )
	{
		CurrentFileHeader->DetachFromStorage();
		CurrentFile = CurrentFileHeader->GetFile();
		FileList.DeleteItem(File);

		if ( CurrentFile )
		{
			//delete CurrentFile;        //AK   clear mistakes
			return TRUE;
		}
	}
	
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::CloseFileAndAttach(Handle File, Word32 Flag, Handle Storage)
{
	CTCFileHeader * CurrentFileHeader = FileList.GetItemHeader(File);

	if ( CurrentFileHeader)
	{
		if ( CurrentFileHeader->AttachToStorage(Storage) )
			return CurrentFileHeader->LockToStorage();
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::AttachFileToStorage(Handle File, Handle Storage, Word32 Flag)
{
	CTCFileHeader * AttachedFile = FileList.GetItemHeader(File);
	CTCStorageHeader * AttacherStorage = StorageList.GetItemHeader(Storage);

	if ( AttacherStorage && AttachedFile )
	{
		return AttachedFile->AttachToStorage(Storage);
	}
		
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::WriteDataToFile(Handle File, void * lpData, Word32 Size)
{
	CTCFileHeader * CurrentFileHeader = FileList.GetItemHeader(File);
	CTCGlobalFile * CurrentFile;
	Word32 WritedDataCount = 0;

	if ( CurrentFileHeader )
	{
		if ( CurrentFileHeader->CanWrite() )
		{
			CurrentFile = CurrentFileHeader->GetFile();
			WritedDataCount = CurrentFile->Write( lpData, sizeof(char), Size); 
		}
	}
	if (WritedDataCount!=Size)
		SetReturnCode_cfio(IDS_CFIO_ERR_CANT_WRITE);

	return WritedDataCount;
}
//////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::ReadDataFromFile(Handle File, void * lpData, Word32 Size)
{
	CTCGlobalFile * CurrentFile = FileList.GetItem(File);
	Word32 ReadedDataCount = 0;

	if ( CurrentFile )
	{
		ReadedDataCount = CurrentFile->Read( lpData, sizeof(char), Size); 
	}
	
	return ReadedDataCount;
}
//////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::SeekFilePointer(Handle File, Word32 Position, Word32 From)
{
	CTCGlobalFile * CurrentFile = FileList.GetItem(File);
	Word32 Seeker = 0;

	if ( CurrentFile )
	{
		Seeker = CurrentFile->Seek( Position, From ); 
	}
	
	return Seeker;

}
//////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::TellFilePointer(Handle File)
{
	CTCGlobalFile * CurrentFile = FileList.GetItem(File);
	Word32 Seeker = 0;

	if ( CurrentFile )
	{
		Seeker = CurrentFile->Tell(); 
	}
	
	return Seeker;
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::FlushFile(Handle File)
{
	CTCGlobalFile * CurrentFile = FileList.GetItem(File);

	if ( CurrentFile )
	{
		return CurrentFile->Flush(); 
	}

	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::DeleteFileFromDisk(Handle File)
{
	CTCGlobalFile * CurrentFile = FileList.GetItem(File);
	
	if ( CurrentFile )
	{
		CurrentFile->SetDelete();
		
		if ( FileList.DeleteItem(File) )
		{
			delete CurrentFile;
			return TRUE;
		}
	}
	
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::WriteItemToStorage(CTCStorageHeader * Storage, void * pItem, Word32 wSize)
{
	CTCGlobalFile * CurrentStorage = Storage->GetStorage();
	Word32 WritedDataCount = 0;

	if ( CurrentStorage )
	{
		WritedDataCount = CurrentStorage->Write(pItem, sizeof( char ), wSize);
	}
	return WritedDataCount;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::ReadItemFromStorage(CTCStorageHeader * Storage, void * lpData, Word32 wSize)
{
	CTCGlobalFile * CurrentStorage = Storage->GetStorage();
	Word32 ReadedDataCount = 0;

	if ( CurrentStorage )
	{
		ReadedDataCount = CurrentStorage->Read(lpData, sizeof( char ), wSize);
	}
	return ReadedDataCount;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define          COPYBUFFER                     512
char  CopyBuffer[COPYBUFFER];
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::WriteFileToStorage(CTCStorageHeader * Storage, CTCFileHeader * File)
{
	CTCFileHeader *    pItemHeader = File;
	CTCGlobalFile *    pStorage = Storage->GetStorage();
	CTCGlobalFile *    pItem;	
	STORAGEITEM        ItemInfo;
	Word32 FileSize =          0;
	Word32 FileRealBuffer =    0;
	Word32 WritedDataCount =   0;
	
	if ( Storage )
	{
		pItem = pItemHeader->GetFile();
		ItemInfo.siHeaderSize = sizeof ( ItemInfo );
		FileSize = ItemInfo.siItemSize = pItem->GetFileSize();
		ItemInfo.siFlag = pItemHeader->GetFlag();
		CFIO_STRCPY(ItemInfo.siName, MakeNameForStorage(pItem->GetFileName(),Storage,pItemHeader->HowName()));

		if ( FileSize )
		{
			WritedDataCount = WriteItemToStorage(Storage, &ItemInfo, sizeof ( ItemInfo ));

			while (FileSize)
			{
				FileRealBuffer = FileSize > COPYBUFFER ? COPYBUFFER : FileSize;
				
				pItem->Read(CopyBuffer, sizeof ( char ), FileRealBuffer);
				WritedDataCount += WriteItemToStorage(Storage, CopyBuffer, FileRealBuffer);
				
				FileSize -= FileRealBuffer;
			}
		}
	}
	return WritedDataCount;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Storage - pointer to storage,
// pInfo - pointer to INFO for File
// pFile - pointer to opened new file
Word32 CTCControl::ReadFileFromStorage(CTCStorageHeader * Storage, STORAGEITEM * pInfo, CTCGlobalFile ** pFile)
{
	STORAGEITEM                ItemInfo;
	CTCGlobalFile *            NewFile;
	Word32                     ReadedDataCount =   0;
	Word32                     FileSize;
	Word32                     FileRealBuffer;
	//Handle                     hNewFile;

	ReadedDataCount += ReadItemFromStorage(Storage, &ItemInfo, sizeof( ItemInfo ));
	
	(*pInfo).siHeaderSize = ItemInfo.siHeaderSize; 
	FileSize = (*pInfo).siItemSize = ItemInfo.siItemSize; 
	(*pInfo).siFlag = ItemInfo.siFlag; 
	// ������� ��� �����
	FileNameToFolder(ItemInfo.siName, Storage->GetStorageFolder(), ItemInfo.siName, _MAX_PATH);
	CFIO_STRCPY(pInfo->siName, ItemInfo.siName);
	
	if ( ItemInfo.siName )
	{
		NewFile = new CTCGlobalFile(ItemInfo.siName, CFIO_GF_CREATE|CFIO_GF_READ|ItemInfo.siFlag);
		*pFile = NewFile;
		
		// ���������, ��� ������ �������
		if ( ! NewFile->GetHandle() )
		{
			return 0;
		}
	}
	
	while ( FileSize )
	{
		FileRealBuffer = FileSize > COPYBUFFER ? COPYBUFFER : FileSize;
		
		ReadItemFromStorage(Storage, CopyBuffer, FileRealBuffer);
		ReadedDataCount += NewFile->Write(CopyBuffer, sizeof ( char ), FileRealBuffer);
		//NewFile->Flush();   // flushed when write

		FileSize -= FileRealBuffer;
	}
	
	return ReadedDataCount;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
char     StorageName[_MAX_PATH];
char     StorageFolder[_MAX_PATH + sizeof(Word32)];
Word32   * FolderSize = (Word32 *)StorageFolder;
Word32   StorageFlag;
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Handle CTCControl::CompliteStorage(Handle Storage, Word32 Flag)
{
	CTCFileHeader *    pItemHeader = NULL;
	CTCStorageHeader * pStorageHeader = StorageList.GetItemHeader(Storage);
	CTCGlobalFile *    pStorage;
	Word32             ComplitedItems = 0;
	Word32             ComplitedSpace = 0;
	Handle             ReStorage;
	// ������� ������ ��������� � ������� �����  fwrite
	// ���� ���� �� ������ �������� ������������ ����
	if ( pStorageHeader )
	{
		pStorage = pStorageHeader->GetStorage();
		CFIO_STRCPY(StorageName,pStorage->GetFileName());
		
		// ������� ��� ��������...
		CFIO_STRCPY(&StorageFolder[sizeof(*FolderSize)],pStorageHeader->GetStorageFolder());
		*FolderSize = strlen(&StorageFolder[sizeof(*FolderSize)]) + sizeof(*FolderSize);
		StorageFlag = pStorageHeader->GetFlag();
		
		// �������
		pStorage->SetDelete();
		StorageList.DeleteItem(Storage);
		//delete pStorage; // deleted at header destructor 
		// ������� ����� � ��� �� ������
		// GlobalFile
		pStorage = new CTCGlobalFile( &StorageName[0], CFIO_GF_CREATE );
		// Handle 
		ReStorage = StorageList.AddItem(pStorage,StorageFlag);
		// Header
		pStorageHeader = StorageList.GetItemHeader(ReStorage);
	}
	else
	{
		return 0;
	}
		ComplitedSpace += WriteItemToStorage(pStorageHeader, 
			                                 (void *) StorageFolder,
											 *FolderSize);

	// �������� ���������
	while ( pItemHeader = FileList.GetItemHeader(FileList.GetAttachedFileHeader(Storage, (pItemHeader == NULL ? NULL : pItemHeader->GetNext()))) )
	{
		if ( pItemHeader->CanWrite() && ( Flag|CS_FILE_DELETE || Flag|CS_FILE_SAVE) )
		{
			pItemHeader->LockToStorage();
		}
		//  ���������� ����
		ComplitedSpace += WriteFileToStorage(pStorageHeader, pItemHeader); 
		ComplitedItems++;

	}
	// ������ ����������� ��������
	pStorageHeader->AddFlag(CFIO_GF_COMPLITE);
	
	// ��������� ����� ��������� ���������
	// StorageList.DeleteItem(ReStorage);
	// delete pStorage; // deleted at header destructor 

	return ReStorage;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::DecompileStorage(Handle Storage)
{
	CTCGlobalFile      * pExtractFile;
	CTCStorageHeader   * StorageHeader = StorageList.GetItemHeader(Storage);
	CTCGlobalFile      * pStorage = StorageHeader->GetStorage();
	STORAGEITEM          ExtractInfo;
	Word32               StorageSize = 0;
	Word32               ReadedFromStorage = 0;
	Word32               ItemSize;
	Word32               NextItem = 0;
	Word32               ReadItem;
	Word32               SFolderSize = 0;
	Handle               hExtractFile;

	StorageSize = pStorage->Seek(0,CFIO_GF_SEEK_END);

	// ������ ������� ��� ��������
	pStorage->Seek(NextItem,CFIO_GF_SEEK_BEG);
	
	ReadItemFromStorage(StorageHeader, (void *)StorageFolder, sizeof(*FolderSize) );
	NextItem += *FolderSize;
	StorageSize -= NextItem;
	ReadItemFromStorage(StorageHeader, (void *)&StorageFolder[sizeof(*FolderSize)], *FolderSize - sizeof(*FolderSize) );
	StorageFolder[*FolderSize] = 0x0;
	// ������� � �����
	// �� ������� - ����� �� ���������
	//STRCPY(StorageHeader->GetStorageFolder(),&StorageFolder[sizeof(*FolderSize)]);
	// � ��� ���������
	while (StorageSize)
	{
		pStorage->Seek(NextItem,CFIO_GF_SEEK_BEG);
		ReadItem = ReadFileFromStorage(StorageHeader, &ExtractInfo, &pExtractFile);
		ItemSize = ExtractInfo.siHeaderSize + ExtractInfo.siItemSize;
		
		StorageSize -= ItemSize;
		NextItem += ItemSize;

		if ( ItemSize == ReadItem )
		{
			ReadedFromStorage += ItemSize;
			hExtractFile = AddFileInList(pExtractFile, ExtractInfo.siFlag, Storage);
			FileList.GetItemHeader(hExtractFile)->AttachToStorage(Storage);
		}
		else
		{
			// close file if not successful
			delete pExtractFile;
		}
	}

	return ReadedFromStorage;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Handle CTCControl::OpenCompliteStorage(PChar8 lpName, Word32 Flag)
{
	CTCGlobalFile *    pNewStorage = NULL;
	CTCStorageHeader * hStorageHeader;
	Handle             hNewStorage;

	pNewStorage = new CTCGlobalFile(lpName,CFIO_GF_WRITE|CFIO_GF_READ|CFIO_GF_BINARY);
	hNewStorage = AddStorageInList(pNewStorage, Flag);	
	
	if ( hNewStorage )
	{
		hStorageHeader = StorageList.GetItemHeader(hNewStorage);
		DecompileStorage(hNewStorage);
		return hNewStorage;
	}
	else
	{
		return NULL;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Handle CTCControl::OpenNewStorage(PChar8 lpName, Word32 Flag)
{
	CTCGlobalFile * pNewStorage = NULL;
	Handle          hOpened;

	CFIO_MAKEFULLPATH(szBuffer, lpName,_MAX_PATH);

	if ( hOpened = StorageList.FindStorage(szBuffer) )
		return hOpened;

	pNewStorage = new CTCGlobalFile(szBuffer, CFIO_GF_CREATE|CFIO_GF_READ|CFIO_GF_BINARY);
	
	if ( pNewStorage )
	{
		return AddStorageInList(pNewStorage, Flag );	
	}
	
	return NULL;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� ��������� (���� ������ �� �����������), ����� ������ �����
Bool32 CTCControl::CloseStorageFile(Handle Storage, Word32 Flag)
{
	CTCStorageHeader * pStorageHeader = StorageList.GetItemHeader(Storage);
	CTCGlobalFile * pStorage;
	CTCGlobalFile * pFile;
	CTCFileHeader * pFileHeader = NULL;
	char StorageFolder[_MAX_PATH];

	if ( Flag & CS_FILE_DELETE )
	{
		if ( CFIO_STRLEN(pStorageHeader->GetStorageFolder()) < _MAX_PATH )
			CFIO_STRCPY(StorageFolder,pStorageHeader->GetStorageFolder());
	}
	else
	{
		StorageFolder[0] = 0x0;
	}

	// ��������� ���������
	if ( pStorageHeader )
	{
		pStorage = pStorageHeader->GetStorage();

		if ( Flag & CS_DELETE )
			pStorage->SetDelete();

		StorageList.DeleteItem(Storage);
		//delete pStorage; deleted at destructor
	}
	// ��������� ����� ������������� � ���������
	while ( pFileHeader = FileList.GetItemHeader(FileList.GetAttachedFileHeader(Storage/*, pFileHeader*/)) )
	{
		pFile = pFileHeader->GetFile();

		if ( Flag & CS_FILE_DELETE )
		{
			pFile->SetDelete();
		}

		FileList.DeleteItem(pFileHeader->GetHandle());
		//delete pFile; //deleted at header destructor

	}

	if ( StorageFolder[0] != 0x0)
		CFIO_DELETEFOLDER(StorageFolder);

	return FALSE;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Word32 CTCControl::CompliteAllStorage(Handle Storage, Word32 Flag)
{
	// ���� �� ������� ��������� - �������� ���
	if ( Storage == NULL )
	{
		while ( !StorageList.IsEmpty() )
		{
			CompliteStorage(StorageList.GetFirstItemHeader()->GetHandle(), Flag);
		}

		return StorageList.IsEmpty();
	}
	// ���� ���� ������� ��������� - �������� ������ ���
	else
	{
		return (CompliteStorage(Storage, Flag) != NULL);
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
Bool32 CTCControl::CloseAllStorageFile(Handle Storage, Word32 Flag)
{
	// ���� �� ������� ��������� - ��������� ���
	if ( Storage == NULL )
	{
		while ( !StorageList.IsEmpty() )
		{
			CloseStorageFile(StorageList.GetFirstItemHeader()->GetHandle(), Flag);
		}

		return StorageList.IsEmpty();
	}
	// ���� ���� ������� ��������� - ��������� ������ ���
	else
	{
		return CloseStorageFile(Storage, Flag);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//end of file
