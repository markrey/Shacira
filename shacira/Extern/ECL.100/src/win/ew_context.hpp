/*.SH.*/

/*
 *  Headerfile for module ew_context
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  ew_context.cpp on Thursday February 14 2002  14:59:35
 */

#ifndef __ew_context__
#define __ew_context__


// Headerfiles
// ===========================================================================

#include "draw/ed_context.hpp"
#include "win/ew_windows.hpp"


// ===========================================================================
// Definition cwContext
// ---------------------------------------------------------------------------
//
// Kontext fuer Zeichenoperationen auf dem Client-Bereich eines Fensters.
//
//  cEclObject
//   +--cdContext
//       +--cwContext
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwContext : public cdContext {
   ECL_DECLARE(cwContext, cdContext)
   friend class ccwView;
   friend class cwView;

public:

   // Draw-Kontext fuer den Client-Bereich von 'win' erzeugen
   inline cwContext(cwWindow *win) { init(win); }
   // Destruktor
   ~cwContext();


private:

   // Konstruktor fuer ccwView
   inline cwContext(void *ctxt);
   // Initialisierung
   void init(cwWindow *win);

};


// ===========================================================================
// Definition cwInfoContext
// ---------------------------------------------------------------------------
//
// Kontext fuer Anfragen ueber Zeichenoperationen auf Bildschirm-Fenstern.
//
//  cEclObject
//   +--cdContext
//       +--cwInfoContext
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwInfoContext : public cdContext {
   ECL_DECLARE(cwInfoContext, cdContext)

public:

   // Anfrage-Kontext fuer Zeichenoperation auf dem Bildschirm erzeugen
   inline cwInfoContext() { init(); }
   // Destruktor
   ~cwInfoContext();


private:

   // Initialisierung
   void init();

};


#endif

/*.EH.*/
