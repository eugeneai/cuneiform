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

#ifndef PPS_MAC
#pragma message(__FILE__)
#endif
#ifndef __SNPTOOLS_H
#define __SNPTOOLS_H


   #include <string.h>
   #ifndef __GLOBUS_H
      #include "globus.h"
   #endif
   #include "wrgb.h"
   #include "ctmacros.h"


   #include "snpdefs.h"

/////////////////////////////////////////////////////////////////////
// Final set of routines to be used
//
#ifndef DPUMA_SNAP
#ifndef NO_SNP
   static __SnpToolBox* __pSnpToolBox = NULL;
   // this variable will be in all modules with include of snaptool.h
   // internal usage!

   //static
   //void SnpSetTools(__SnpToolBox* tools)
   //{ __pSnpToolBox=tools; };
   #define SnpSetTools(tools) { __pSnpToolBox=tools; };

   //static
   //Bool SnpIsActive(void)
   //{ return __pSnpToolBox!=NULL; };
   #define SnpIsActive() (__pSnpToolBox!=NULL)

   #define SnpLog           (__pSnpToolBox->fLog           )
   #define SnpStatusLine    (__pSnpToolBox->fStatusLine    )
   #define SnpDrawRect      (__pSnpToolBox->fDrawRect      )
   #define SnpHideRects     (__pSnpToolBox->fHideRects     )
   #define SnpDrawLine      (__pSnpToolBox->fDrawLine      )
   #define SnpHideLines     (__pSnpToolBox->fHideLines     )
   #define SnpDrawFocusRect (__pSnpToolBox->fDrawFocusRect )
   #define SnpSetZoneOn     (__pSnpToolBox->fSetZoneOn     )
   #define SnpSetZoneOff    (__pSnpToolBox->fSetZoneOff    )
   #define SnpUpdateViews   (__pSnpToolBox->fUpdateViews   )
   #define SnpMessBoxOk     (__pSnpToolBox->fMessBoxOk     )
   #define SnpMessBoxYesNo  (__pSnpToolBox->fMessBoxYesNo  )
   #define SnpGetUserString (__pSnpToolBox->fGetUserString )
   #define SnpGetUserLong   (__pSnpToolBox->fGetUserLong   )
   #define SnpGetUserRect   (__pSnpToolBox->fGetUserRect   )
   #define SnpGetUserPoint  (__pSnpToolBox->fGetUserPoint  )
   #define SnpWaitUserInput (__pSnpToolBox->fWaitUserInput )
   #define SnpNotifyAppl    (__pSnpToolBox->fNotifyAppl    )
   #define SnpDrawRaster    (__pSnpToolBox->fDrawRaster    )
   #define SnpRasterText    (__pSnpToolBox->fRasterText    )
   #define SnpRasterHeader  (__pSnpToolBox->fRasterHeader  )
   #define SnpZoomToRect    (__pSnpToolBox->fZoomToRect    )

// TODO: (3/4) insert new function define here ^^^ (before this comment)
// For last (4/4/) step you should realize new function on application
// level and initialize created field of __SnpToolBox
////////////////////////////////////////////////////////////////////////

   //////////////////////////////////////////////////////////////
   // SnpTreeNode hanling routines
   //

   /*static            // SnpTreeNode construction and connection;*/
   void SnpAddNode(  // should be called from dll's XxxRegisterSnpTree();
         SnpTreeNode *  node, // on module's static data segment
         char *         name, // user readable
         SnpTreeNode *  parent
         // eliminated, 21 oct 96:
         // SnpTreeNode *  elder_brother
                  )
   {
   //////////////////////////////////////////////
   // before 21 oct 96
   /*
      memset( node, 0, sizeof(SnpTreeNode) );
      node->Parent = parent;
      node->Prev   = elder_brother;
      if (elder_brother != NULL)
         elder_brother->Next = node;
      if ((parent != NULL) && (elder_brother == NULL))
         parent->FirstChild = node;
      strncpy(node->Name, name, sizeof(node->Name)-1 );
    */
   ///////////////////////////////////////////////
   ///// 21 oct 96 : elder_brother set automatically

      memset( node, 0, sizeof(SnpTreeNode) );
      node->Parent = parent;
      strncpy(node->Name, name, sizeof(node->Name)-1 );
      // set node->Next & node->Prev:
      if (parent !=NULL)
      {
         SnpTreeNode* kid=NULL;
         if (parent->FirstChild != NULL)
         {  kid =parent->FirstChild;
            while (kid->Next!=NULL)
               kid=kid->Next;
            kid->Next = node;
            node->Prev= kid;
         }
         else  // first child in family!
            parent->FirstChild = node;
      };
   };

   static  // internal usage, dont call directly
   void __SnpIterParent( SnpTreeNode* node, Bool activate )
   {
   #ifdef __cplusplus
      SnpTreeNode* child = node->GetFirstBaby();
   #else
      SnpTreeNode* child = node->FirstChild;
   #endif
      while (child != NULL)
      {  if (activate)
         {  if (child->IterParent > 0)
               child->IterParent--;
         }
         else
            child->IterParent++;
         __SnpIterParent(child, activate);
   #ifdef __cplusplus
         child = child->GetNext();
   #else
         child = child->Next;
   #endif
      };
   };

   static
   void    SnpFreezeChilds(
      SnpTreeNode* node,
      Bool32       freeze )
   {
      if (freeze)
      {
         if (!( node->Status & STN_FROZENCHILDS ))
         {
            __SnpIterParent(node, FALSE); // freeze subtree
            node->Status |= STN_FROZENCHILDS;
         };
      }
      else
      {
         if ( node->Status & STN_FROZENCHILDS )
         {
            __SnpIterParent(node, TRUE ); // unfreeze subtree
            node->Status &= ~STN_FROZENCHILDS;
         };
      };
   };

   /*static*/
   Bool16 SnpSkip( SnpTreeNode* node )
      // checks node for skip (no activity) condition;
      // for iterative nodes decreases SkipCnt;
      // NOTE: call it once per iteration
   {

#ifndef PPS_MAC
      if ( !SnpIsActive()         // snap is not active at all
   || node->IterParent > 0        // parent iterated
   || NOT_ACTIVE(node->Status)    // no node activity
   || ((node->IterStop > 0) &&           // iteration was set...
//16.12.96 16:05 VP      (node->IterCur != node->IterStop) // ... but another
       (node->IterCur < node->IterStop) // ... but another
      )
         )
         return TRUE;   // Skip it, baby!

      ///////////// node about to be activated ///////////
      SnpNotifyAppl(node);            // notify application
      return FALSE;
#else
      return TRUE;
#endif
   };

   /*static*/
   void    SnpStartLoop( // call in dll before start of loop
      SnpTreeNode* node, // node inside loop
      Word32 iter_total  // iteration count, 0 if unknown
                       )
   {
      node->IterTotal = iter_total;
      node->IterCur = 0;
      if (     node->IterStop > 0
//            && !(node->Status & STN_FROZENCHILDS)
         )
      {
         //__SnpIterParent(node, FALSE); // freeze subtree
         //node->Status |= STN_FROZENCHILDS;
         SnpFreezeChilds(node, TRUE);
      };
   }

   /*static*/
   void    SnpLoopNext( // call in dll at start of next iteration
      SnpTreeNode* node
                      )
   {
      node->IterCur++;
      if ( node->IterCur == node->IterStop )
      {
         SnpFreezeChilds(node, FALSE); // unfreeze
         return;
      };
/** 16.12.96 16:06, VP
      if (     node->IterStop > 0
            //&& node->IterCur == (node->IterStop+1) // next after stop
            //&& !(node->Status & STN_FROZENCHILDS))
         )
      {
         SnpFreezeChilds(node, TRUE); // freeze
         //__SnpIterParent(node, FALSE); // freeze subtree
         //node->Status |= STN_FROZENCHILDS;
      };
***/
   };

#else
      /*
   // Snp toggled off, lets define stubs
   static void SnpSetTools(__SnpToolBox* tools){;};
   static Bool SnpIsActive(void) { return FALSE; };

   static int    SnpLog( const char* s, ...) { return 0;};
   static void   SnpStatusLine( char* s, ...){;};
   static void   SnpDrawRect(Rect16* rc, Int32 skew, Word32 rgb_color,
      Int32 pen_width,Word32 key){;};
   static void   SnpHideRects(Word32 key){;};
   static void   SnpDrawLine(Point16* start, Point16* end, Int32 skew,
      Word32 rgb_color,Int16 pen_width,Word32 key ){;};
   static void   SnpHideLines(Word32 key){;};
   static void   SnpDrawFocusRect(Rect16* rc){;};
   static Word32 SnpSetZoneOn(Rect16*  zone_rect,
      Word32   rgb_color,char* status_line_comment,
      Word32  users_zone_handle, FTOnMouseDown  on_mouse_down )
      { return 0; };
   static void   SnpSetZoneOff( Word32 zone_handle ){;};
   static void   SnpUpdateViews(void){;};
   static void   SnpMessBoxOk( char * message ){;};
   static Bool16 SnpMessBoxYesNo( char * message ){ return TRUE;};
   static Bool16 SnpGetUserString (char * static_text,
      char * result_string, Word32 result_string_length ){ return FALSE; };
   static Bool16 SnpGetUserLong(char * static_text,
      Int32 * result_long) { return FALSE;};
   static Bool16 SnpGetUserRect( Rect16* rect ){return FALSE;};
   static Bool16 SnpGetUserPoint(Point16* pnt){return FALSE;};
   static Word32 SnpWaitUserInput(SnpTreeNode* cur_node)
      {  return 0; };
   static void SnpNotifyAppl(SnpTreeNode* cur_node){;};
   // tree manipulation
   static void   SnpRasterText(char *Text){;};
   static void SnpAddNode( SnpTreeNode *  node, char * name,
      SnpTreeNode * parent ) {;};
   static void    __SnpIterParent( SnpTreeNode* node, Bool activate ){;};
   static void    SnpStartLoop( SnpTreeNode* node, Word32 iter_total ){;};
   static void    SnpLoopNext( SnpTreeNode* node ){;};
   static Bool16  SnpSkip( SnpTreeNode* node ){ return TRUE; };
*/
       void SnpSetTools(__SnpToolBox* tools);
       Bool SnpIsActive(void);

       int    SnpLog( const char* s, ...);
       void   SnpStatusLine( char* s, ...);
       void   SnpDrawRect(Rect16* rc, Int32 skew, Word32 rgb_color,
         Int32 pen_width,Word32 key);
       void   SnpHideRects(Word32 key);
       void   SnpDrawLine(Point16* start, Point16* end, Int32 skew,
         Word32 rgb_color,Int16 pen_width,Word32 key );
       void   SnpHideLines(Word32 key);
       void   SnpDrawFocusRect(Rect16* rc);
       Word32 SnpSetZoneOn(Rect16*  zone_rect,
         Word32   rgb_color,char* status_line_comment,
         Word32  users_zone_handle, FTOnMouseDown  on_mouse_down );
       void   SnpSetZoneOff( Word32 zone_handle );
       void   SnpUpdateViews(void);
       void   SnpMessBoxOk( char * message );
       Bool16 SnpMessBoxYesNo( char * message );
       Bool16 SnpGetUserString (char * _text,
         char * result_string, Word32 result_string_length );
       Bool16 SnpGetUserLong(char * _text,
         Int32 * result_long);
       Bool16 SnpGetUserRect( Rect16* rect );
       Bool16 SnpGetUserPoint(Point16* pnt);
       Word32 SnpWaitUserInput(SnpTreeNode* cur_node);
       void SnpNotifyAppl(SnpTreeNode* cur_node);
      // tree manipulation
       void   SnpRasterText(char *Text);
      void SnpAddNode( SnpTreeNode *  node, char * name,
         SnpTreeNode * parent ) ;
   void    __SnpIterParent( SnpTreeNode* node, Bool activate );
   void    SnpStartLoop( SnpTreeNode* node, Word32 iter_total );
   void    SnpLoopNext( SnpTreeNode* node );
   Bool16  SnpSkip( SnpTreeNode* node );

#endif
#else

#ifdef __cplusplus
   extern "C" {
#endif

	int  SnpLog(const char * s,...);
	void SnpStatusLine(const char * s,...);
   void SnpSetTools(__SnpToolBox* tools);
   Bool SnpIsActive(void);

   void   SnpDrawRect(Rect16* rc, Int32 skew, Word32 rgb_color,
      Int32 pen_width,Word32 key);
   void   SnpHideRects(Word32 key);
   void   SnpDrawLine(Point16* start, Point16* end, Int32 skew,
      Word32 rgb_color,Int16 pen_width,Word32 key );
   void   SnpHideLines(Word32 key);
   void   SnpDrawFocusRect(Rect16* rc);
   Word32 SnpSetZoneOn(Rect16*  zone_rect,
      Word32   rgb_color,char* status_line_comment,
      Word32  users_zone_handle, FTOnMouseDown  on_mouse_down );
   void   SnpSetZoneOff( Word32 zone_handle );
   void   SnpUpdateViews(void);
   void   SnpMessBoxOk( char * message );
   Bool16 SnpMessBoxYesNo( char * message );
   Bool16 SnpGetUserString (char * static_text,
      char * result_string, Word32 result_string_length );
   Bool16 SnpGetUserLong(char * static_text,
      Int32 * result_long);
   Bool16 SnpGetUserRect( Rect16* rect );
   Bool16 SnpGetUserPoint(Point16* pnt);
   Word32 SnpWaitUserInput(SnpTreeNode* cur_node);
   void SnpNotifyAppl(SnpTreeNode* cur_node);
   // tree manipulation
   void   SnpRasterText(char *Text);
   void   SnpDrawRaster(RecRaster * raster);

   void		SnpAddNode( SnpTreeNode*  node, char * name,SnpTreeNode* parent );
   void    __SnpIterParent( SnpTreeNode* node, Bool activate );
   void    SnpStartLoop( SnpTreeNode* node, Word32 iter_total );
   void    SnpLoopNext( SnpTreeNode* node );
   Bool16  SnpSkip( SnpTreeNode* node );
	void	SnpZoomToRect(Rect16 * lpRect);
	void	SnpRasterHeader(char * lpText,Word32 num);


#ifdef __cplusplus
   }
#endif

#endif
#endif
