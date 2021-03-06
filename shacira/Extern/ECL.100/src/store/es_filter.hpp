/*.SH.*/

/*
 *  Headerfile for module es_filter
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  es_filter.cpp on Friday March 08 2002  14:58:36
 */

#ifndef __es_filter__
#define __es_filter__


// Headerfiles
// ===========================================================================

#include "store/es_query.hpp"


// ===========================================================================
// Definition csFilter
// ---------------------------------------------------------------------------
//
// cBase
//  +--csBaseStorage
//      +--csFilter
//
// ===========================================================================

class __ECL_DLLEXPORT__ csFilter : public csBaseStorage {
   ECL_DECLARE(csFilter,csBaseStorage)
   friend class csQuery;

public:

   // Copy-Konstruktor
   csFilter(const csFilter& other);


   // Filter-Funktionen
   // =================

   // Filtern eines Text-Wertes (liefert Text)
   inline void filter(const csQuery *query, cString& text) const
      { onFilterText(query, text); }
   // Filtern eines Schluesselwertes (liefert ein Icon)
   inline void filter(const csQuery *query, cString key, cIcon& icon) const
      { onFilterIcon(query, key, icon); }
   // Filtern eines Schluesselwertes (liefert eine Bitmap)
   inline void filter(const csQuery *query, cString key, cBitmap& bmp) const
      { onFilterBitmap(query, key, bmp); }

   // Ermittelt die Feldgroesse NACH der Filterung
   inline int calcSize(const csQuery *query, int size) const
      { return onCalcSize(query, size); }


   // Aufzaehlwerte
   // =============
   // Basiert ein Filter auf einer aufzaehlbaren Menge von Werten, koennen
   // diese erfragt werden. Damit kann z.B. eine Drop-Selektion basierend
   // auf den moeglichen Werten des Filters erstellt werden.

   // Anzahl moeglicher Werte liefern (0 falls kein Aufzaehltyp)
   inline int getValueCount() const
      { return onGetValueCount(); }
   // Wertepaar (Schluessel,Text) von Position 'idx' der Liste liefern
   inline bool getValue(int idx, cString& key, cString& text) const
      { return onGetValue(idx, key, text); }
   // Query erzeugen, welche die Aufzaehlwerte liefert (0 falls kein Aufzaehltyp)
   inline csQuery *makeValueQuery() const
      { return onMakeValueQuery(); }


protected:

   // Konstruktor (Protected)
   csFilter(int _flags = 0);


   // Zusaetzliche Events
   // ===================

   // Wird aufgerufen, um einen Text-Wert zu filtern
   virtual void onFilterText(const csQuery *query, cString& text) const;
   // Wird aufgerufen, um einen Schluesselwert in ein Icon umzuwandeln
   virtual void onFilterIcon(const csQuery *query, cString key, cIcon& icon) const;
   // Wird aufgerufen, um einen Schluesselwert in eine Bitmap umzuwandeln
   virtual void onFilterBitmap(const csQuery *query, cString key, cBitmap& bmp) const;
   // Wird aufgerufen, um die Feldgroesse NACH der Filterung zu ermitteln
   virtual int onCalcSize(const csQuery *query, int size) const;

   // Wird aufgerufen, um die Anzahl moeglicher Aufzaehlwerte zu erfragen
   virtual int onGetValueCount() const;
   // Wird aufgerufen, um ein Wertepaar (Schluessel,Text) zu erfragen
   virtual bool onGetValue(int idx, cString& key, cString& text) const;
   // Wird aufgerufen, um eine Query ueber alle Aufzaehlwerte zu erzeugen
   virtual csQuery *onMakeValueQuery() const;

};


// ===========================================================================
// Definition csFmtFilter
// ---------------------------------------------------------------------------
//
// Stellt einen einfachen Filter auf der Basis von sprintf zur Verfuegung.
// Der im Konstruktor uebergebene Formatstring muss genau ein '%s' enthalten.
// Beispiele: "%s DM", "(%s)", "x=%s"
//
// cBase
//  +--csBaseStorage
//      +--csFilter
//          +--csFmtFilter
//
// ===========================================================================

class __ECL_DLLEXPORT__ csFmtFilter : public csFilter {
   ECL_DECLARE(csFmtFilter,csFilter)

public:

   // Konstruktor
   csFmtFilter(cString _fmt, int _flags = 0);
   // Copy-Konstruktor
   csFmtFilter(const csFmtFilter& other);

protected:

   // Wird aufgerufen, um einen Text-Wert zu filtern
   void onFilterText(const csQuery *query, cString& text) const;
   // Wird aufgerufen, um die Feldgroesse NACH der Filterung zu ermitteln
   int onCalcSize(const csQuery *query, int size) const;

private:

   cString fmt;

};


// ===========================================================================
// Definition csDecodeFilter
// ---------------------------------------------------------------------------
//
// ACHTUNG: Wird der csDecodeFilter ueber ein Query-Objekt konstruiert, muss
//          letzteres das "Permanent"-Flag gesetzt haben!
//
// cBase
//  +--csBaseStorage
//      +--csFilter
//          +--csDecodeFilter
//
// ===========================================================================

class __ECL_DLLEXPORT__ csDecodeFilter : public csFilter, public cEventTarget {
   ECL_DECLARE(csDecodeFilter,csFilter)

public:

   // Konstruktion ueber Query-Abfrage
   csDecodeFilter(csQuery *query, int flags = 0);
   // Konstruktion ueber Encoded Keys
   csDecodeFilter(const char *str1, ...);
   // Konstruktion ueber Encoded Keys (+ Flags)
   csDecodeFilter(int flags, const char *str1, ...);
   // Copy-Konstruktor
   csDecodeFilter(const csDecodeFilter& other);
   // Destruktor
   virtual ~csDecodeFilter();


   // Flags
   // =====

   enum FLAGS { fStart = csFilter::fUser,
      fEncodedKeys = fStart << 0,  // Schluessel in Enums kodiert: "key$name"
      fShowKeys    = fStart << 1,  // Schluessel mit anzeigen, Format: "key (name)"
      fUser        = fStart << 2   // Benutzerdefinierte Flags
   };


protected:

   // Wird aufgerufen, um einen Text-Wert zu filtern
   void onFilterText(const csQuery *query, cString& text) const;
   // Wird aufgerufen, um die Feldgroesse NACH der Filterung zu ermitteln
   int onCalcSize(const csQuery *query, int size) const;

   // Wird aufgerufen, um die Anzahl moeglicher Aufzaehlwerte zu erfragen
   int onGetValueCount() const;
   // Wird aufgerufen, um ein Wertepaar (Schluessel,Text) zu erfragen
   bool onGetValue(int idx, cString& key, cString& text) const;


private:

   struct NODE {
      NODE(int _key, const char *_name, bool _encoded_keys);
      NODE(const char *_key, const char *_name);
      char key[12];
      cString name;
      NODE *next;
   };

   NODE *anchor, *last;
   int max_name_size;

   void init(csQuery *query);
   void init(const char *str1, va_list arg_ptr);
   void deleteNodes();

   int onQueryEvent(void *p1, int p2);

};


#endif

/*.EH.*/
