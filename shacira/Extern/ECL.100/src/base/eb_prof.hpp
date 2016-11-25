/*.SH.*/

/*
 *  Headerfile for module eb_prof
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  eb_prof.cpp on Friday December 21 2001  21:59:10
 */

#ifndef __eb_prof__
#define __eb_prof__


// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"
#include "base/eb_str.hpp"


// ===========================================================================
// Definition cProfile
// ---------------------------------------------------------------------------
//
// cBase
//  +--cProfile
//
// Anmerkungen:
//  - Die Funktionen getAppList() und getKeyList() benutzen das Windows-API
//    und arbeiten mit einem zwar grossen, aber begrenzten Puffer. Bei Mehr-
//    bedarf muessen diese Funktionen neu implementiert werden.
//  - Binaerdaten werden unter __ECL_W32__ (bis jetzt) nicht unterstuetzt!
//  - Ab heute (18.08.2001) schon! Aber nur fuer benannte Profiles!
//  - getAppList() und getKeyList() (bis jetzt) nicht unter __ECL_OS2__!
//
// ===========================================================================

class __ECL_DLLEXPORT__ cProfile : public cBase {

public:

   // Konstruktor
   cProfile(cString prf_name = 0, cString def_app_path = 0);
   // Destruktor
   ~cProfile();


   // Oeffnen, Schliessen
   // ===================

   // Profile oeffnen (im Modus PRIVATE oder CURUSR)
   bool open(cString prf_name, cString def_app_path);
   // Profile oeffnen (im Modus PUBLIC)
   bool open(cString def_app_path = 0);
   // Profile schliessen
   void close();


   // Lesen
   // =====

   // Pruefen, ob ein Eintrag in der vorhanden ist
   // - falls key nicht angegeben, pruefen ob Applikation vorhanden ist
   // - falls app_path und key nicht angegeben, pruefen ob INI-Datei vorhanden ist
   bool exist(cString app_path = 0, cString key = 0) const;

   // Binaere Daten einlesen
   size_t read(cString app_path, cString key, void *data, size_t size) const;
   // Zeichenkette einlesen
   cString read(cString app_path, cString key, cString def_val = 0) const;
   // Zahl einlesen
   long read(cString app_path, cString key, long def_val) const;


   // Schreiben
   // =========

   // Binaere Daten schreiben, liefert false bei Misserfolg
   bool write(cString app_path, cString key, void *data, size_t size) const;
   // Zeichenkette schreiben, liefert false bei Misserfolg
   // - falls data nicht angegeben, wird der key geloescht
   // - falls data und key fehlt, wird die gesamte Applikation geloescht
   bool write(cString app_path, cString key = 0, cString data = 0) const;
   // Zahl schreiaben, liefert false bei Misserfolg
   bool write(cString app_path, cString key, long data) const;


   // Applikations- und Keyliste
   // ==========================

   class ITERATOR {
      friend class cProfile;
      char *pos;
      char *buf;
      int len;
   public:
      ITERATOR() { buf = pos = NULL; len = 0;}
      ~ITERATOR() { if (buf) free(buf); }
      void alloc(int s) { if (!buf) buf = (char*)malloc(len=s); }
   };

   // Applikationsliste laden, liefert false falls Funktion nicht verfuegbar
   bool getAppList(ITERATOR &it);
   // Keyliste laden, liefert false falls Funktion nicht verfuegbar
   bool getKeyList(ITERATOR &it, cString app_path);
   // Iteration der Liste wieder auf Startwert
   void resetList(ITERATOR &it) { it.pos = it.buf; }
   // Naechsten Namen holen, leere Zeichenkette beim Ende
   cString getNext(ITERATOR &it);

   // cProfile::ITERATOR it;
   // cString app_path;
   // getAppList(it);
   // while ((app_path=getNext(it)).Length()) { ... }


private:

   enum {
      buf_size = 1024,     // maximale Laenge einer Zeile
      dir_size = 0x7FFF    // Puffergroesse fuer Applikations/Keyliste
   };

   EBHDL anchor_hdl, prf_hdl;
   cString prf_name, def_app_path;

};


#endif

/*.EH.*/