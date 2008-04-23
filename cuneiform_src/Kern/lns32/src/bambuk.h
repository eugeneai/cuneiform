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

#ifndef __BAMBUK_H
#	define __BAMBUK_H

	/* "Bambuk" is a grass that grows...
	*	1) ...from number of fixed previously roots
	*	2) ...always upward
	* 	3) ...as fast as possible;
	*/

   #ifndef __LNSLANG_H
   #  include "lnslang.h"
	#endif


	#ifndef __FARARRAY_H
	#	include "fararray.h"
	#endif

typedef 	Int32 BHandle ;
typedef 	Int32 BEntry  ;

#define NULLBHandle  (BHandle)	0xFFFF
#define NULLBEntry   (BEntry)	0xFFFF

struct  EntryInfo
	{
		BHandle first;
 		BHandle last;
		BHandle count;
	};

template <class T> class /*HUGE*/ TBambuk //: public TFarHeap
{
public :

TBambuk( void )
	{};

TBambuk( BHandle max_members_count, BEntry max_entry_count )
		{
			createBambuk( max_members_count, max_entry_count);
			if (!isOk())
				destroyBambuk();
		};


/* virtual */ Bool isOk( void )
		{  return (ok); };

Bool        createBambuk( BHandle max_members_count, BEntry max_entry_count )
      {  //assert( max_members_count > 0 );
         //assert( max_entry_count > 0 );

			nextHandle 	= 0;
			ok = 	( 	members.create( max_members_count) &&
						links	.create( max_members_count ) &&
						entries.create( max_entry_count 	)
					);
			if (ok){
				cleanLinks();
				cleanEntries();
			};
			return (ok);
		};

void     appendMember( BEntry entry_point, BHandle member_handle )
		{
			assert(entry_point < entries.lastHandle());
			assert( member_handle != NULLBHandle );
			assert( links[ member_handle ] == NULLBHandle ); // member is single
			if (noEntry( entry_point )) {
				entries[ entry_point ].first 	=
				entries[ entry_point ].last 	= member_handle;
				entries[ entry_point ].count  = 1;
			}
			else {
				assert( links[ entries[ entry_point ].last ] == NULLBHandle );
				links[ entries[ entry_point ].last ] 	= member_handle;
				entries[ entry_point ].last				= member_handle;
				entries[ entry_point ].count++;
			};
		};


BHandle 		addMember( BEntry entry_point )
		{
         assert(entry_point <= entries.lastHandle());
			if (nextHandle >= members.lastHandle())
				return NULLBHandle;


			links[ nextHandle ] = NULLBHandle;
			if (noEntry( entry_point )) {
				entries[ entry_point ].first 	=
				entries[ entry_point ].last 	= nextHandle;
				entries[ entry_point ].count  = 1;
			}
			else {
				assert( links[ entries[ entry_point ].last ] == NULLBHandle );
				links[ entries[ entry_point ].last ] 	= nextHandle;
				entries[ entry_point ].last				= nextHandle;
				entries[ entry_point ].count++;
			};
			return (nextHandle++);
		};

BHandle 		firstEntryMember( BEntry entry_point )
		{ return entries[ entry_point ].first; }

BHandle 		lastEntryMember( BEntry entry_point )
		{ return entries[ entry_point ].last; }

BHandle 		memberEntryCount( BEntry entry_point )
		{ return entries[ entry_point ].count; }

BHandle     memberTotalCount( void )
		{ return (nextHandle); }

BHandle     memberVolume( void )
		{ return (members.volume()); }

BHandle     memberRestCount( void )
		{ return (members.volume() - nextHandle); }

BHandle 		nextMember( BHandle cur_member )
		{ return links[ cur_member ]; }

BEntry      lastEntry( void )
		{ return (entries.lastHandle()); }

void        appendMemberList( BEntry senior, BEntry junior )
		{	assert( !noEntry(junior) );
			assert( !noEntry(senior) );

			assert( links[ entries[ senior ].last ] == NULLBHandle );
			assert( links[ entries[ junior ].last ] == NULLBHandle );

			links[ entries[ senior ].last ] = entries[ junior ].first;
			entries[ senior ].last = entries[ junior ].last;
			entries[ senior ].count += entries[ junior ].count;

			entries[ junior ].first	= NULLBHandle;
			entries[ junior ].last 	= NULLBHandle;
			entries[ junior ].count	= 0;
		};

T HUGE & operator [] ( BHandle cur_member)
		{ return members[cur_member];};

Bool        shrinkBambuk(  BHandle new_members_count,
									BEntry new_entries_count = 0 )
	{
		assert( isOk() );
//      assert( new_members_count > 0 );
		BHandle 	old_members_count = members.volume();
		assert( new_members_count < old_members_count );
		BEntry	old_entries_count = entries.volume();
		assert( new_entries_count < old_entries_count );

		if (!members.shrink(new_members_count))
			return WRONG();
		if (!links.shrink(new_members_count))
			return WRONG();

		if (	(new_entries_count > 0)
          	&&
				(!entries.shrink(new_entries_count))
      	)	return WRONG();

		/*
		if (old_members_count < new_members_count)
			cleanLinks( old_members_count );
		if (old_entries_count < new_entries_count)
			cleanEntries( old_members_count );
		*/
		return TRUE;
	};

void        destroyBambuk( void )
		{
			members.flash();
			links  .flash();
			entries.flash();
			nextHandle = 0;
			ok = FALSE;
		};
void        cleanMembers( T  * zero_member, Int32 from );
void        cleanLinks( Int32 from = 0 );
void        cleanEntries( Int32 from = 0 );



~TBambuk( void )
		{ destroyBambuk(); };

private :

	TFarArray<T> 	 	   	members;      	// members data
	TFarArray<BHandle>  		links;        	// next member links
	TFarArray<EntryInfo>		entries;      	// entries info (first, last, count);
	BHandle						nextHandle;   	// next free member handle
   Bool                    ok;            // FALSE if object is not correct

   Bool        noEntry( BEntry entry )
		{ return (entries[ entry ].count == 0);
		};
};
/*
template <class T>
void TBambuk<T>::appendMemberList( BEntry senior, BEntry junior )
	{
		assert( !noEntry(junior) );
		assert( !noEntry(senior) );

		assert( links[ entries[ senior ].last ] == NULLBHandle );

		links[ entries[ senior ].last ] = links[ entries[ junior ].first ];
		entries[ senior ].last = entries[ junior ].last;
		entries[ senior ].count += entries[ junior ].count;

		entries[ junior ].first	= NULLBHandle;
		entries[ junior ].last 	= NULLBHandle;
		entries[ junior ].count	= 0;
	};
*/
template <class T>
void  TBambuk<T>::cleanEntries( Int32 from )
	{	assert( isOk() );
		EntryInfo zeroEntry = { NULLBHandle, NULLBHandle, 0 };
		entries.fill( &zeroEntry, from );
	};

template <class T>
void  TBambuk<T>::cleanMembers( T  * zero_member, Int32 from )
	{	assert( isOk() );
		members.fill(  zero_member, from );
	};

template <class T>
void  TBambuk<T>::cleanLinks( Int32 from )
	{	assert( isOk() );
   	BHandle handle = NULLBHandle;
		links.fill( &handle, from );
	};

/* HUGE version for large member count */
template <class T> class HUGE THugeBambuk //: public TFarHeap 
{

public :



THugeBambuk( void )
	{};

THugeBambuk( BHandle max_members_count, BEntry max_entry_count )
		{
			createBambuk( max_members_count, max_entry_count);
			if (!isOk())
				destroyBambuk();
		};



/* virtual */ Bool isOk( void )
		{  return (ok); };

Bool        createBambuk( BHandle max_members_count, BEntry max_entry_count )
		{	// assert( max_members_count > 0 );
			// assert( max_entry_count > 0 );

			nextHandle 	= 0;
			ok = 	( 	members.create( max_members_count) &&
						links	.create( max_members_count ) &&
						entries.create( max_entry_count 	)
					);
			if (ok){
				cleanLinks();
				cleanEntries();
			};
			return (ok);
		};

void     appendMember( BEntry entry_point, BHandle member_handle )
		{	assert( member_handle != NULLBHandle );
			assert( links[ member_handle ] == NULLBHandle ); // member is single
			if (noEntry( entry_point )) {
				entries[ entry_point ].first 	=
				entries[ entry_point ].last 	= member_handle;
				entries[ entry_point ].count  = 1;
			}
			else {
				assert( links[ entries[ entry_point ].last ] == NULLBHandle );
				links[ entries[ entry_point ].last ] 	= member_handle;
				entries[ entry_point ].last				= member_handle;
				entries[ entry_point ].count++;
			};
		};

Bool  GrowMembers(void)
   {
      if (!members.Grow()) // increase twice
			return FALSE;
      if (!links.Grow()) // increase twice
			return FALSE;
      return TRUE;
   }

BHandle 		addMember( BEntry entry_point )
		{	

#ifndef NO_REALLOCATION
         if (nextHandle >= members.lastHandle())
         {
            if (!GrowMembers())
               return NULLBHandle;
            if (nextHandle >= members.lastHandle())
				   return NULLBHandle;
         }
#else
         if (nextHandle >= members.lastHandle())
				return NULLBHandle;
#endif // NO_REALLOCATION


			links[ nextHandle ] = NULLBHandle;
			if (noEntry( entry_point )) {
				entries[ entry_point ].first 	=
				entries[ entry_point ].last 	= nextHandle;
				entries[ entry_point ].count  = 1;
			}
			else {
				assert( links[ entries[ entry_point ].last ] == NULLBHandle );
				links[ entries[ entry_point ].last ] 	= nextHandle;
				entries[ entry_point ].last				= nextHandle;
				entries[ entry_point ].count++;
			};
			return (nextHandle++);
		};

BHandle 		firstEntryMember( BEntry entry_point )
		{ return entries[ entry_point ].first; }

BHandle 		lastEntryMember( BEntry entry_point )
		{ return entries[ entry_point ].last; }

BHandle 		memberEntryCount( BEntry entry_point )
		{ return entries[ entry_point ].count; }

BHandle     memberTotalCount( void )
		{ return (nextHandle); }

BHandle     memberVolume( void )
		{ return (members.volume()); }

BHandle     memberRestCount( void )
		{ return (members.volume() - nextHandle); }

BHandle 		nextMember( BHandle cur_member )
		{ return links[ cur_member ]; }

BEntry      lastEntry( void )
		{ return (entries.lastHandle()); }

void        appendMemberList( BEntry senior, BEntry junior )
		{	assert( !noEntry(junior) );
			assert( !noEntry(senior) );

			assert( links[ entries[ senior ].last ] == NULLBHandle );
			assert( links[ entries[ junior ].last ] == NULLBHandle );

			links[ entries[ senior ].last ] = entries[ junior ].first;
			entries[ senior ].last = entries[ junior ].last;
			entries[ senior ].count += entries[ junior ].count;

			entries[ junior ].first	= NULLBHandle;
			entries[ junior ].last 	= NULLBHandle;
			entries[ junior ].count	= 0;
		};

T HUGE & operator [] ( BHandle cur_member)
		{ return members[cur_member];};

Bool        shrinkBambuk(  BHandle new_members_count,
								BEntry new_entries_count = 0 )
	{
		assert( isOk() );
//		assert( new_members_count > 0 );
		BHandle 	old_members_count = members.volume();
		assert( new_members_count < old_members_count );
		BEntry	old_entries_count = entries.volume();
		assert( new_entries_count < old_entries_count );

		if (!members.shrink(new_members_count))
			return WRONG();
		if (!links.shrink(new_members_count))
			return WRONG();

		if (	(new_entries_count > 0)
          	&&
				(!entries.shrink(new_entries_count))
      	)	return WRONG();

		/*
		if (old_members_count < new_members_count)
			cleanLinks( old_members_count );
		if (old_entries_count < new_entries_count)
			cleanEntries( old_members_count );
		*/
		return TRUE;
	};

void        destroyBambuk( void )
		{
			members.flash();
			links  .flash();
			entries.flash();
			nextHandle = 0;
			ok = FALSE;
		};
void        cleanMembers( T  * zero_member, Int32 from );
void        cleanLinks( Int32 from = 0 );
void        cleanEntries( Int32 from = 0 );



~THugeBambuk( void )
		{ destroyBambuk(); };

private :

	THugeArray<T> 	 	   	members;      	// members data
	TFarArray<BHandle>  		links;        	// next member links
	TFarArray<EntryInfo>		entries;      	// entries info (first, last, count);
	BHandle						nextHandle;   	// next free member handle
   Bool                    ok;            // FALSE if object is not correct

   Bool        noEntry( BEntry entry )
		{ return (entries[ entry ].count == 0);
		};
};
/*
template <class T>
void THugeBambuk<T>::appendMemberList( BEntry senior, BEntry junior )
	{
		assert( !noEntry(junior) );
		assert( !noEntry(senior) );

		assert( links[ entries[ senior ].last ] == NULLBHandle );

		links[ entries[ senior ].last ] = links[ entries[ junior ].first ];
		entries[ senior ].last = entries[ junior ].last;
		entries[ senior ].count += entries[ junior ].count;

		entries[ junior ].first	= NULLBHandle;
		entries[ junior ].last 	= NULLBHandle;
		entries[ junior ].count	= 0;
	};
*/
template <class T>
void  THugeBambuk<T>::cleanEntries( Int32 from )
	{	assert( isOk() );
		EntryInfo zeroEntry = { NULLBHandle, NULLBHandle, 0 };
		entries.fill( &zeroEntry, from );
	};

template <class T>
void  THugeBambuk<T>::cleanMembers( T  * zero_member, Int32 from )
	{	assert( isOk() );
		members.fill(  zero_member, from );
	};

template <class T>
void  THugeBambuk<T>::cleanLinks( Int32 from )
	{	assert( isOk() );
   	BHandle handle = NULLBHandle;
		links.fill( &handle, from );
	};

#endif
