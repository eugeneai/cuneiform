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

#ifndef __XSTACK_H
   #define __XSTACK_H

   #ifndef __XPOOL_H
   #  include "xpool.h"
   #endif

template <class T>
class XStack : private XPool
{
	public:
      XStack( Int32 max_cnt = 0, Int32 cur_cnt = 0 ):
         XPool(), MaxCnt(0), CurCnt(0) {  Create(max_cnt, cur_cnt); };
      ~XStack(void){ Destroy(); };
      Bool     Create( Int32 max_cnt, Int32 cur_cnt = 0 ); // differs of Resize by no realloc
      Bool     CreateOf( Int32 init_cnt ){  return Create( init_cnt, init_cnt ); }
      void     Destroy();
      Bool     Resize( Int32 new_max_cnt ); // reallocation
      void     SetCurCnt( Int32 new_cnt );  // does not resize!
      Bool     operator !() const
         {  return   ( !*(XPool*)this )     ||
                     ( CurCnt > MaxCnt )    ||
                     ( GetVolume() != (Int32)(MaxCnt*sizeof(T)) );
			};
      T&       operator  []( Int32 i ) const
         {  assert(GetData()!=NULL); assert(i<CurCnt); return *((T*)(GetData())+i);};
      T*       GetPtr()  const {  return (T*)(GetData()); };
      Int32    GetCurCnt() const { return CurCnt; };
      Int32    GetMaxCnt() const { return MaxCnt; };
      T*       Push( Int32* no=NULL ); // fix space for new element
      Bool     Push( T* t, Int32* no=NULL );
      Bool     Push( T& t, Int32* no=NULL ){ return Push(&t, no); };
		T*       Pop();

		T*       Top(); // returns temporary pointer to last element;
                      // later element can be relocated (after push())

      Err16    Read( XFile & bf, Bool32 swap_bytes = FALSE );
      Bool     Write( XFile & bf ) const;

      void     MemSet( Word8 pattern ){ XPool::MemSet(pattern); };

   private:
               Int32   MaxCnt;
               Int32   CurCnt;
      Bool     Copy( T* dst, T* src )
         {  //*dst=*src;
            memcpy( dst, src, sizeof(T) );
            return TRUE;
         };

/** 22.03.97 22:07
  public:          // The obsolete methods: for backward compatibility.
		void     flush  () {Destroy();};
//		T      * ptr( Indx num )        { return &(*this)[num]; }
		T      * firstPtr(void)         { return (T *)GetData();}
		Word32   volume( void )         {  return MaxCnt;}
		T      & GetLast(void)          {  return (*this)[(Indx)(CurCnt -1)];}
**/
};
 
template < class T >
Bool     XStack< T >::Create( Int32 max_cnt, Int32 cur_cnt )
	{  assert(max_cnt>=cur_cnt);
      if ( !XPool::Create( max_cnt*sizeof(T) ) )
         {  CurCnt = 0;MaxCnt = 0;RETFALSE; }
		CurCnt = cur_cnt;
		MaxCnt = max_cnt;
		return TRUE;
	};
 
template < class T >
void     XStack< T >::SetCurCnt( Int32 new_cnt ) // does not resize!
	{
		assert( new_cnt <= MaxCnt );
		CurCnt = new_cnt;
	};
 
template < class T >
void     XStack< T >::Destroy()
   {  XPool::Destroy();
		CurCnt = MaxCnt = 0;
	};

 
template < class T >
Bool     XStack< T >::Resize( Int32 new_max_cnt )
	{
      if ( !XPool::Realloc( new_max_cnt*sizeof(T) ) )
			RETFALSE;
		MaxCnt = new_max_cnt;
      CurCnt =  mini( CurCnt, new_max_cnt );
		return TRUE;
	};
 
template < class T >
T*       XStack< T >::Push( Int32* no ) // fix space for new element
{
		assert( CurCnt <= MaxCnt );
      if ( CurCnt == MaxCnt )
         if (!Resize( maxi( CurCnt*2, 1 ) ))
            RETNULL;

      assert( CurCnt < MaxCnt );
		T* pt = (T*)GetData();
      if (pt==NULL)
         RETNULL;
		pt+=(Indx)CurCnt;
      if (no)
         *no = CurCnt;
		CurCnt++;
      return pt;
}

template < class T >
Bool     XStack< T >::Push( T* t, Int32* no )
	{
		assert( CurCnt <= MaxCnt );
      if ( CurCnt == MaxCnt )
         if (!Resize( maxi( CurCnt*2, 1 ) ))
            RETFALSE;

      assert( CurCnt < MaxCnt );
		T* pt = (T*)GetData();
      if (pt==NULL)
         RETFALSE;
		pt+=(Indx)CurCnt;
		if ( ( t!=NULL ) && !Copy( pt, t) )
			RETFALSE;
      if (no)
         *no = CurCnt;
		CurCnt++;
		return TRUE;
	};
 
template < class T >
T*       XStack< T >::Pop(void)
	{
		if (CurCnt==0) RETNULL;
		T* pt = (T*)GetData();
		assert(pt!=NULL);
		CurCnt--;
		pt+=(Indx)CurCnt;
		return pt;
	};
 
template < class T >
T*       XStack< T >::Top(void)
	{
		if (CurCnt==0)
         return NULL;
		T* pt = (T*)GetData();
		assert(pt!=NULL);
		pt+=(Indx)(CurCnt-1);
		return pt;
	};
 
template < class T >
Err16 XStack< T >::Read( XFile & bf, Bool32 swap_bytes )
	{
      RETIFERR( XPool::Read(bf, swap_bytes) );
		if ( (GetVolume() % sizeof(T)) != 0)
         RETERR( ER_CORRUPTED );
		CurCnt = MaxCnt = (GetVolume() / sizeof(T));
		assert(!!*this);
      return ER_NONE;
	};
 
template < class T >
Bool     XStack< T >::Write( XFile & bf ) const
	{
      if(!XPool::Write(bf, CurCnt*sizeof(T)))   RETFALSE;
		return TRUE;
	}

#endif // __TAGSTACK_H
