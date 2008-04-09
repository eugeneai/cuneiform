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

	#ifndef __RBAMBUK_H
	#define __RBAMBUK_H

   #ifndef __LNSLANG_H
   #  include "lnslang.h"
	#endif

//_TYPEDEFFAR( TRasterBambuk )

	#ifndef __FARARRAY_H
	#	include "FarArray.h"
	#endif

	#ifndef __SBAMBUK_H
	#	include "SBambuk.h"
	#endif


/*
* TRasterBambuk*******************************************

	Bambuk of Rasters to Dashes

*/


struct TDash {
	BHandle firstSegHandle;    // points to first segment (handle of segbambuk)
	BEntry  firstSegEntry;     // first segment column/row (entry of segbambuk)
	BEntry  rasterEntry;       // own entry in raster bambuk
};

class TRasterBambuk : public TBambuk< TDash > {
	public:
TRasterBambuk( TSegBambuk* sb, BHandle max_dashes, BEntry max_rasters ):
	TBambuk< TDash >(max_dashes, max_rasters),
	ok( FALSE ),
	nextRasterEntry(0),
	count(0)
	{
		if (TBambuk< TDash >::isOk())
			ok = makeIt( sb );      // false if too many dashes or rasters
	};

Bool isOk( void ) { return (TBambuk< TDash >::isOk() && ok); };
Int32 totalRasterCount( void ) { return (count); };
	private:
      Int32 count;     // result count of rasters
      Int32 nextRasterEntry;
      Bool ok;
      Bool makeIt( TSegBambuk* sb );

      void completeDash( BHandle dash_handle ){;};
		BHandle startDash( 	BHandle segment_handle,
									BEntry segment_entry,
									BEntry raster_entry = NULLBEntry
								){
			BHandle dash_handle;
			if (raster_entry==NULLBEntry){ // this is first line in component
				raster_entry = nextRasterEntry++;
            if (raster_entry > lastEntry())
               return NULLBHandle;
				count++;
			};
			if ((dash_handle = addMember( raster_entry )) != NULLBHandle){
				(*this)[ dash_handle ].firstSegHandle = segment_handle;
				(*this)[ dash_handle ].firstSegEntry  = segment_entry;
				(*this)[ dash_handle ].rasterEntry	  = raster_entry;
			};
			return (dash_handle);
		};
      void joinRasters( BEntry first, BEntry second );

		BEntry rasterEntry( TBlackSeg* seg ){
			assert( seg->dashHandle != NULLBHandle );
			return ((*this)[seg->dashHandle].rasterEntry);
		};

};

	#endif // __RBAMBUK_H
