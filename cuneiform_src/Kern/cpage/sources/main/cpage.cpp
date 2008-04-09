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

#define __CPAGE__

#include "resource.h"
#include "cpage.h"
#include "backup.h"
#include "namedata.h"
//
//
//

#define SAVE_COMPRESSED  // ��������� ������ � ������ � ����������� ����

extern PtrList<BACKUPPAGE> Page;
extern Handle              hCurPage;
extern PtrList<NAMEDATA>	NameData;

#define PAGE_H(page) Page.GetItem(page)
#define PAGE_N(page) PAGE_H(Page.GetHandle(page))

#define _BLOCK_H(page,block) page.Block.GetItem(block)
#define _BLOCK_N(page,block) _BLOCK_H(page,page.Block.GetHandle(block))

#define BLOCK_H_H(page,block) _BLOCK_H(PAGE_H(page),block)
#define BLOCK_H_N(page,block) _BLOCK_N(PAGE_H(page),block)
#define BLOCK_N_N(page,block) _BLOCK_N(PAGE_N(page),block)

//###########################################
CPAGE_FUNC(Handle) CPAGE_CreatePage(Word32 type,void * lpdata, Word32 size)
{
	PROLOG;
  SetReturnCode(IDS_ERR_NO);

  Handle hPage = Page.AddTail(BACKUPPAGE());


  if(hPage)
  {
	if(!Page.GetItem(hPage).SetData(type,lpdata,size))
	{
		Page.Del(hPage);
		hPage = NULL;
		if(hCurPage == hPage)
			hCurPage = NULL;
	}
	else
		hCurPage = hPage;
  }
  EPILOG;
  return hPage;
}
//###########################################
CPAGE_FUNC(Word32)  CPAGE_GetPageType(Handle page)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	Word32 rc = PAGE_H(page).GetType();
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(void) CPAGE_DeletePage(Handle page)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	Page.Del(page);
	if(hCurPage == page)
		hCurPage = NULL;
	EPILOG;
}
//###########################################
CPAGE_FUNC(void) CPAGE_ClearBackUp(Handle page)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	PAGE_H(page).Clear();
	EPILOG;
}
//###########################################
CPAGE_FUNC(Handle) CPAGE_BackUp(Handle page)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	Handle rc = PAGE_H(page).BackUp();
	EPILOG;
	return rc;
}
//###########################################

CPAGE_FUNC(Bool32) CPAGE_Undo(Handle page,Handle num)
{
	PROLOG;
	Bool32 rc = FALSE;
	SetReturnCode(IDS_ERR_NO);
	if(num==NULL)
	{
		Word32 number = CPAGE_GetBuckUpCount(page);
		if(number)
		{
			Word32 cur = CPAGE_GetBuckUpCurPos(page);
			if(cur == 0)
			{
				rc = FALSE;
				goto lOut;
			}
			num = CPAGE_GetBuckUpHandle(page,cur - 1);
		}
		else
		{
			rc = FALSE;
			goto lOut;
		}
	}
	rc = PAGE_H(page).Undo(num);
lOut:EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Bool32) CPAGE_Redo(Handle page,Handle num)
{
	PROLOG;
	Bool32 rc = FALSE;
	SetReturnCode(IDS_ERR_NO);
	if(num==NULL)
	{
		Word32 number = CPAGE_GetBuckUpCount(page);
		if(number)
		{
			Word32 cur = CPAGE_GetBuckUpCurPos(page);
			if(cur == (number - 1))
			{
				rc = FALSE;
				goto lOut;
			}
			num = CPAGE_GetBuckUpHandle(page,cur + 1);
		}
		else
		{
			rc = FALSE;
			goto lOut;
		}
	}
	rc = PAGE_H(page).Redo(num);
lOut:EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Word32) CPAGE_GetBuckUpCount(Handle page)
{
	PROLOG;
	Word32 rc = PAGE_H(page).BackUpPage.GetCount();
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Handle) CPAGE_GetBuckUpHandle(Handle page,Word32 number)
{
	PROLOG;
	Handle rc = PAGE_H(page).BackUpPage.GetHandle(number);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Word32) CPAGE_GetBuckUpCurPos(Handle page)
{
	PROLOG;
	Word32 rc = PAGE_H(page).GetCurPos();
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Handle)	CPAGE_CreateBlock(Handle page, Word32 Type, Word32 UserNum , Word32 Flags,void * lpData, Word32 Size)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	
#ifdef _DEBUG
	_ASSERT(CPAGE_GetNameInternalType(Type));
#endif
	
	Handle rc = PAGE_H(page).CreateBlock(Type ,UserNum ,Flags ,lpData , Size);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Bool32) CPAGE_SetPageData(Handle page ,Word32 type,void * lpdata, Word32 size)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
#ifdef _DEBUG
	_ASSERT(CPAGE_GetNameInternalType(type));
#endif
	Bool32 rc = PAGE_H(page).SetData( type, lpdata, size);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Word32) CPAGE_GetPageData(Handle page ,Word32 type,void * lpdata, Word32 size)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	
#ifdef _DEBUG
	_ASSERT(CPAGE_GetNameInternalType(type));
#endif
	
	DefConvertInit();
	Word32 rc = PAGE_H(page).GetData( type, lpdata, size);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Word32)  CPAGE_GetBlockType(Handle page,Handle block)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	Word32 rc = BLOCK_H_H(page,block).GetType();
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Word32)  CPAGE_GetBlockUserNum(Handle page,Handle block)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	Word32 rc = BLOCK_H_H(page,block).GetUserNum();
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(void)    CPAGE_SetBlockUserNum(Handle page,Handle block,Word32 user)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	BLOCK_H_H(page,block).SetUserNum(user);
	EPILOG;
}
//###########################################
CPAGE_FUNC(Word32)  CPAGE_GetBlockFlags(Handle page,Handle block)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	Word32 rc = BLOCK_H_H(page,block).GetFlags();
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(void)    CPAGE_SetBlockFlags(Handle page,Handle block,Word32 flags)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	BLOCK_H_H(page,block).SetFlags(flags);
	EPILOG;
}
//###########################################
CPAGE_FUNC(Bool32)  CPAGE_SetBlockData(Handle page,Handle block,Word32 Type, void * lpData, Word32 Size)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
#ifdef _DEBUG
	_ASSERT(CPAGE_GetNameInternalType(Type));
#endif
	Bool32 rc = BLOCK_H_H(page,block).SetData(Type,lpData, Size);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Word32)  CPAGE_GetBlockData(Handle page,Handle block,Word32 Type, void * lpData, Word32 Size)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
#ifdef _DEBUG
	_ASSERT(CPAGE_GetNameInternalType(Type));
#endif
	DefConvertInit();
	Word32 rc = BLOCK_H_H(page,block).GetData(Type, lpData, Size);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Word32) CPAGE_GetCountPage()
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	Word32 rc = Page.GetCount();
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Word32) CPAGE_GetCountBlock(Handle page)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	Word32 rc = PAGE_H(page).Block.GetCount();
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(void)  CPAGE_DeleteBlock(Handle page,Handle block)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	PAGE_H(page).Block.Del(block);
	EPILOG;
}
//###########################################
#define VERSION_FILE            0xF002
#define VERSION_FILE_COMPRESSED 0xF003

CPAGE_FUNC(Bool32)  CPAGE_SavePage(Handle page,Int8 * lpName)
{
	PROLOG;
	Bool32 rc = FALSE;
	SetReturnCode(IDS_ERR_NO);
	Handle file = myOpenSave((char *)lpName);

	if(file)
	{
#ifdef SAVE_COMPRESSED
		Word32 vers = VERSION_FILE_COMPRESSED;
#else
		Word32 vers = VERSION_FILE;
#endif
		if(myWrite(file,&vers,sizeof(vers))==sizeof(vers))
		{
			if(page)
			{
				int count = 1;
				rc = myWrite(file,&count,sizeof(count))==sizeof(count);
#ifdef SAVE_COMPRESSED
				rc = PAGE_H(page).SaveCompress(file);
#else
				rc = PAGE_H(page).Save(file);
#endif
			}
			else
			{	int i;
				int count = Page.GetCount();
				rc = myWrite(file,&count,sizeof(count))==sizeof(count);
				for(i=0;i<count && rc == TRUE;i++)
#ifdef SAVE_COMPRESSED
					rc = PAGE_N(i).SaveCompress(file);
#else
					rc = PAGE_N(i).Save(file);
#endif
			}
		}
		myClose(file);
	}
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Handle)  CPAGE_RestorePage(Bool32 remove,Int8 * lpName)
{
	PROLOG;
	Handle rc = NULL;
	Word32 nCurPage = (Word32)-1;
	Bool decompress=FALSE;

	SetReturnCode(IDS_ERR_NO);

	Handle file = myOpenRestore((char *)lpName);
	if(file)
	{
		int i;
		int count;

		Word32 vers = 0;
		if(myRead(file,&vers,sizeof(vers))==sizeof(vers))
		{
			if (vers==VERSION_FILE_COMPRESSED)
			   decompress=TRUE;
			else
				if(vers!=VERSION_FILE)
				{
					SetReturnCode(IDS_ERR_OLDFILEVERSION);
					myClose(file);
					return FALSE;
				}
			{
				if(remove)
				{
					Page.Clear();
					NameData.Clear();
				}

				if(myRead(file,&count,sizeof(count))==sizeof(count))
					for(i=0;i<count ;i++)
					{
						BACKUPPAGE page;
						if(decompress ? page.RestoreCompress(file) : page.Restore(file))
							rc = Page.AddTail(page);
						else 
							break;
					}
			}
		}
		myClose(file);
	}
	EPILOG;
return rc;
}
//###########################################
CPAGE_FUNC(Handle)  CPAGE_GetHandlePage(Word32 page)
{
	PROLOG;
	Handle rc = Page.GetHandle(page);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Handle)  CPAGE_GetHandleBlock(Handle page,Word32 block)
{
	PROLOG;
	Handle rc = PAGE_H(page).Block.GetHandle(block);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(CPAGE_CONVERTOR)  CPAGE_SetConvertorPages(CPAGE_CONVERTOR data)
{
	PROLOG;
	CPAGE_CONVERTOR rc = SetConvertorPages(data);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(CPAGE_CONVERTOR)  CPAGE_SetConvertorBlocks(Handle page,CPAGE_CONVERTOR data)
{
	PROLOG;
CPAGE_CONVERTOR rc = SetConvertorBlocks(data);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Word32)  CPAGE_GetUserPageType()
{
	PROLOG;
	/*
	static Word32 number = 0x10000000;
	return number++;
	*/
	Word32 rc = CPAGE_GetUserBlockType();
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Word32)  CPAGE_GetUserBlockType()
{
	PROLOG;
	static Word32 number = 1;
	char Name[260];
	sprintf(Name,"UserType:%i",number++);
	Word32 rc = CPAGE_GetInternalType(Name);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Handle)  CPAGE_GetPageFirst(Word32 type)
{
	PROLOG;
	int count = Page.GetCount();
#ifdef _DEBUG
	_ASSERT(CPAGE_GetNameInternalType(type));
#endif
	DefConvertInit();
	for(int i = 0;i<count;i++)
	{
		if(!type ||
		   PAGE_N(i).GetType()==type || 
		   PAGE_N(i).Convert(type,NULL,0))
			break;
	}
	Handle rc = i < count ? Page.GetHandle(i):NULL;
	EPILOG;
	return rc;
}	
//###########################################
CPAGE_FUNC(Handle)  CPAGE_GetPageNext(Handle page,Word32 type)
{
	PROLOG;
	int count = Page.GetCount();
	int pos   = Page.GetPos(page) + 1;

#ifdef _DEBUG
	_ASSERT(CPAGE_GetNameInternalType(type));
#endif
	DefConvertInit();
	for(int i = pos; i<count && i>=0 ;i++)
	{
		if(!type ||
			PAGE_N(i).GetType()==type || 
		    PAGE_N(i).Convert(type,NULL,0))
			break;
	}
	Handle rc = i < count ? Page.GetHandle(i):NULL;
	EPILOG;
	return rc;
}	
//###########################################
CPAGE_FUNC(Handle)  CPAGE_GetBlockFirst(Handle page, Word32 type)
{
	PROLOG;
	int count = PAGE_H(page).Block.GetCount();
/*	
#ifdef _DEBUG
	_ASSERT(CPAGE_GetNameInternalType(type));
#endif
*/	
	DefConvertInit();
	for(int i = 0;i<count;i++)
	{
		if(!type ||
			BLOCK_H_N(page,i).GetType()==type || 
		    BLOCK_H_N(page,i).Convert(type,NULL,0))
			break;
	}
	Handle rc = i < count ? PAGE_H(page).Block.GetHandle(i):NULL;
	EPILOG;
	return rc;
}	
//###########################################
CPAGE_FUNC(Handle)  CPAGE_GetBlockNext(Handle page,Handle block, Word32 type)
{
	PROLOG;
	int count = PAGE_H(page).Block.GetCount();
	int pos   = PAGE_H(page).Block.GetPos(block) + 1;
/*	
#ifdef _DEBUG
	_ASSERT(CPAGE_GetNameInternalType(type));
#endif
*/	
	DefConvertInit();
	for(int i = pos; i<count && i>=0 ;i++)
	{
		if(!type ||
		    BLOCK_H_N(page,i).GetType()==type || 
		    BLOCK_H_N(page,i).Convert(type,NULL,0))
			break;
	}
	Handle rc = i < count ? PAGE_H(page).Block.GetHandle(i):NULL;
	EPILOG;
	return rc;
}	
//###########################################
CPAGE_FUNC(Bool32)  CPAGE_DeleteAll()
{
	CPAGE_CONVERTOR ConvertorPages = {0,DefConvertPage}; // Piter
	PROLOG;
	Bool32 rc = TRUE;
	Page.Clear();
	NameData.Clear();
	SetConvertorPages(ConvertorPages); // Piter
	hCurPage = NULL;
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Word32)  CPAGE_GetCurrentPage( )
{
	PROLOG;
	Word32 rc = CPAGE_GetNumberPage(hCurPage);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Bool32)  CPAGE_SetCurrentPage(Word32 page)
{
	PROLOG;
	Bool32 rc = TRUE;
	if( page>=CPAGE_GetCountPage() || 
		page == (Word32)-1)
	{
		SetReturnCode(IDS_ERR_NOPAGE);
		rc = FALSE;
	}
	else
		hCurPage = CPAGE_GetHandlePage(page);

	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Word32)  CPAGE_GetNumberPage( Handle hPage )
{
	PROLOG;
	Word32 rc = (Word32)-1;
	if(hPage)
		rc = (Word32)Page.GetPos(hPage);
	EPILOG;
	return rc;
}
//###########################################
// ���� ����� ������������� ���� � ������, ����� ����� ����� �������� ������ ����,
// �������� ������ ���. ������ ��� � ������ ��� �������.
//
CPAGE_FUNC(Bool32)  CPAGE_UpdateBlocks( Handle hPage, Word32 type )
{
	PROLOG;
	Bool32  rc = TRUE;
	Word32	size = 0;
	char *	lpData = NULL;
	Word32  temporaray = 0;

	SetReturnCode(IDS_ERR_NO);
#ifdef _DEBUG
	_ASSERT(CPAGE_GetNameInternalType(type));
#endif

	SetReturnCode(IDS_ERR_NO);

	Handle hBlock = CPAGE_GetBlockFirst(hPage,type);
	if(!hBlock)
	{
		rc = TRUE;
		goto lOut;
	}
	// �������� ��������� ����� � ������ ������. 
	// ��� ����� ������������� ������������.
	temporaray = CPAGE_GetInternalType("temporary");
	while(hBlock)
	{
		Handle hNextBlock = CPAGE_GetBlockNext(hPage,hBlock,type);// type - ������������� ��� �����
		Word32 dwType	  = CPAGE_GetBlockType(hPage,hBlock); // dwType - �������� ��� �����
		if(dwType != type) // ���� ����������� ����������� �� ���� dwType !
		{
			Word32 UserNum = CPAGE_GetBlockUserNum(hPage,hBlock);
			Word32 Flags   = CPAGE_GetBlockFlags(hPage,hBlock);
			if(lpData == NULL)
			{ // ��������� ����������� ������ � ������� ������.
				size = CPAGE_GetBlockData(hPage,hBlock,type,NULL,0);
				if(size)
				{
					lpData = (char *)myAlloc(size);
					if(!lpData)
					{
						rc = FALSE;
						SetReturnCode(IDS_ERR_NO_MEMORY);
						break;
					}
				}
				else
				{
					SetReturnCode(IDS_ERR_DISCREP);
					rc = FALSE;
					break;
				}
			}
			if(CPAGE_GetBlockData(hPage,hBlock,type,lpData,size)==size)
			{
				CPAGE_DeleteBlock(hPage,hBlock);
				if(!CPAGE_CreateBlock(hPage,temporaray, UserNum , Flags, lpData, size))
				{
					SetReturnCode(IDS_ERR_NO_MEMORY);
					rc = FALSE;
					break;
				}
			}
		}
		hBlock = hNextBlock;
	}
	// ����������� ��������� �����
	if(lpData) // �������� �� ������������� ����� ������
	{
		myFree(lpData);
		for(hBlock = CPAGE_GetBlockFirst(hPage,temporaray);
			hBlock;
			hBlock = CPAGE_GetBlockNext(hPage,hBlock,temporaray))
		{
			BLOCK_H_H(hPage,hBlock).SetType(type);
		}
	}
lOut:EPILOG;
return rc;
}
//###########################################
CPAGE_FUNC(Word32)  CPAGE_GetBlockInterNum(Handle page,Handle block)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	Word32 rc = BLOCK_H_H(page,block).GetInterNum();
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(void)    CPAGE_SetBlockInterNum(Handle page,Handle block,Word32 inter)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
	BLOCK_H_H(page,block).SetInterNum(inter);
	EPILOG;
}
//###########################################
CPAGE_FUNC(Bool32)  CPAGE_GetBlockDataPtr(Handle page,Handle block,Word32 Type, void ** lpData)
{
	PROLOG;
	SetReturnCode(IDS_ERR_NO);
#ifdef _DEBUG
	_ASSERT(CPAGE_GetNameInternalType(Type));
#endif
	Bool32 rc = BLOCK_H_H(page,block).GetDataPtr(Type, lpData);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(Word32)  CPAGE_GetInternalType(char * name)
{
	PROLOG;
	Word32 rc = 0;
	NAMEDATA nd(name);
	SetReturnCode(IDS_ERR_NO);
	rc = (Word32)NameData.FindFirst(nd);
	if(!rc)
		rc = (Word32)NameData.AddTail(nd);
	EPILOG;
	return rc;
}
//###########################################
CPAGE_FUNC(char *)  CPAGE_GetNameInternalType(Word32 type)
{
	char * rc = NULL;
	PROLOG;
	SetReturnCode(IDS_ERR_NO);

	if(type != NULL)
		rc = NameData.GetItem((Handle)type);
	EPILOG;
	return rc;
}
