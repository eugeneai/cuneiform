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

	/*
	Getting source bitmap and creating horisontal and vertical
	segments page bambuks simultaneously.

	Entry point is constructor
		THVSegBambuk( PTBMPReadBuffer reader, int h_filter_len, int v_filter_len  ).

	09-06-93 05:43pm, Basil
	*/

	#ifndef __SBAMBUK_H
	#	define __SBAMBUK_H

   #ifndef __LNSLANG_H
   #  include "lnslang.h"
	#endif


//	_TYPEDEFFAR( TBlackSeg   )
//	_TYPEDEFFAR( TSegBambuk  )
//	_TYPEDEFFAR( THVSegBambuk)
   #ifndef __BAMBUK_H
  	#	include "bambuk.h"
  	#endif
	#ifndef __XYDIM_H
  	#	include "xydim.h"
  	#endif
	#ifndef __ERROBJ_H
  	#	include "errobj.h"
  	#endif
   #ifndef __TGREADER_H    // under windows tiger lib
   #  include "tgreader.h"
   #endif

   #ifndef __PROCLINE_H
	#	include "procline.h"
	#endif
	#ifndef __FLTBUF_H
  	#	include "fltbuf.h"
  	#endif

	#ifndef __PARALINE_H
	#	include "paraline.h"
	#endif

	#define H_FLT_LEN  (int)16
//	#define V_FLT_LEN  (int)16


/*
* TBlackSeg **********************************************

	Simple black segment (or "interval") of bitmap line

*/

struct TBlackSeg
	{
int left;
int right;
BHandle dashHandle;  // handle of proper component dash
BHandle nLower;		// link to lower segments in raster line
							// this is indexes of proper Bambuk array elements
	};

typedef TBlackSeg FAR * FarBlackSeg;

/*
* TSegBambuk **********************************************

	TSegBambuk is bambuk of bitmap rows(or columns) of BlackSegments
	Has some methods of building which differs for horisontal and
	vertical cases.

	Objects of this class used as source when RasterBambuk is builded
	(no matter was this SegBambuk object created by vertical or
 	horisontal methods)
*/

class TSegBambuk :
	//public TBambuk< TBlackSeg >
	public THugeBambuk< TBlackSeg >
{
	private:
			BHandle curHEntry;
			int segLimit;
public:
BHandle segCount;

TSegBambuk( void ):
				THugeBambuk< TBlackSeg >(),
				//TBambuk< TBlackSeg >(),
				curHEntry(0),
				segCount(0),
				segLimit(0)
				{};

TSegBambuk( BHandle max_members, BEntry max_entries ):
				THugeBambuk< TBlackSeg >(max_members, max_entries),
				//TBambuk< TBlackSeg >(max_members, max_entries),
				curHEntry(0),
				segCount(0),
				segLimit(0)
				{};

Bool isOk( void )
	{
   	return (THugeBambuk< TBlackSeg >::isOk());
		//return (TBambuk< TBlackSeg >::isOk());
	};

	/** horisontal building routines **/
void hInitProcess( int left, int right, int h_filter_len )
			{
            SetupHConverter( left, right, h_filter_len, (TSegBambuk*)this, TRUE);
				curHEntry = 0;
				segLimit = (right - left + 1) / (h_filter_len+1);
			};

Bool hUpdate( void* new_line )
			{  
            assert( segLimit );
				if (memberRestCount() < segLimit)
            {

               if (!GrowMembers())
                  return WRONG();
				   if (memberRestCount() < segLimit)
                  return WRONG();
            }
				ConvertBWLine( new_line );
				curHEntry++;
				return TRUE;
			};

void addHorisontal( Int32 left, Int32 right )
			{
				BHandle new_member = addMember( curHEntry );
				segCount++;

            //========================= 06-21-95 02:27pm, just for optimization
				TBlackSeg & bs = ((*this)[new_member]);
            bs.left = left;
            bs.right = right;
            bs.dashHandle = NULLBHandle;
            bs.nLower = NULLBHandle;
            //========================= 06-21-95 02:27pm ======================
            /**
				THIS[new_member].left = left;
				THIS[new_member].right = right;
				THIS[new_member].dashHandle = NULLBHandle;
				THIS[new_member].nLower = NULLBHandle;
             **/
			};

	/** vertical building routines **/
Bool /*TSegBambuk::*/vUpdate(  Int32* new_line,
                           Int32* cur16,
                           Int32* prev16,
									int cur_row
	//									int width_dword ??
								);
Bool /*TSegBambuk::*/vUpdateFirst(   Int32* new_line,
                                 Int32* cur16,
											int cur_row       // at this version == 16
							 			);
Bool /*TSegBambuk::*/vUpdateLast(    Int32* cur16,
                                 Int32* last16,
											int bottom_row
							 			);

};


/*
* THVSegBambuk **********************************************

	THVSegBambuk object associates vertical and horisontal TSegBambuk's of
	the bitmap.
	Main feature is simultaneous creating of horisontal and vertical
 	vertions of TSegBambuk's objects	by single pass of source bitmap

	After HVBambuk has builded horisontal and vertical rasters can be
	processed independently.

*/

class THVSegBambuk : public TXYDim, public TErrObj
	{
public :
      int xres, yres;
TSegBambuk 	hBambuk;      // "bambuk" of horisontal segments
TSegBambuk	vBambuk;      // "bambuk" of vertical segments
	private:
#ifdef __TGREADER_H   // 01-29-94 04:19pm, Basil
public:
THVSegBambuk( TigerReader & reader );
private:
      Bool        makeIt(  TigerReader * reader,
								   TFltBuf*   filter
								);
#endif //__TGREADER_H

   }; // THVSegBambuk

	#endif // __SBAMBUK_H
