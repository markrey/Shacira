/*.SH.*/

/*
 *  Headerfile for module eb_object
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  eb_object.cpp on Saturday November 17 2001  16:59:25
 */

#ifndef __eb_object__
#define __eb_object__


// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"


// Runtime-Type-Information (light)
// ===========================================================================

// ECL_DECLARE - Jede ECL-Klasse muss diese Anweisung enthalten. Die Para-
// meter geben den Klassennamen und den Namen der jeweiligen Basisklasse an.
//
#define ECL_DECLARE(CLASS,BASECLASS) \
protected: \
   const char *__getClassName() const \
      { return #CLASS; } \
   bool __isKindOf(const char *kind) const \
      { if ( strcmp(kind, CLASS::__getClassName()) == 0 ) return true; \
        return BASECLASS::__isKindOf(kind); } \
private:

// ECL_CAST - Mit Hilfe dieser Anweisung kann ein durch einen Zeiger spezifi-
// ziertes Objekt in einen gegebenen ECL-Typ CLASS gewandelt werden, wenn das
// Objekt von dieser Klasse abgeleitet wurde. Andernfalls wird ein 0-Zeiger
// geliefert.
//
#define ECL_CAST(CLASS,PTREXPR) \
   ((CLASS*)cEclObject::__cast(#CLASS,PTREXPR))

// ECL_ISKINDOF - Diese Funktion prueft, ob das durch den Zeiger spezifizierte
// Objekt vom Typ CLASS ist oder davon abgeleitet wurde. ECL_ISKINDOF kann wie
// eine Methode des Objektes verwendet werden.
//
#define ECL_ISKINDOF(CLASS) \
   isKindOf(#CLASS)


// ===========================================================================
// Definition cEclObject
// ---------------------------------------------------------------------------
//
// Basisklasse fuer ECL-Objekte. Realisiert folgende Features:
//
//    - Runtime-Type-Information
//    - Serialisierung (noch nicht implementiert)
//
// cEclObject
//
// ===========================================================================

class __ECL_DLLEXPORT__ cEclObject {

public:

   // Virtueller Destruktor (Wichtig bei Mehrfachvererbung!)
   virtual ~cEclObject();


   // ECL-RTTI
   // ========

   // Klassenname der aktuellen Instanz ermitteln
   inline const char * getClassName() const
      { return __getClassName(); }
   // Pruefen, ob die Instanz vom Typ 'kind' (oder davon abgeleitet) ist
   inline bool isKindOf(const char *kind) const
      { return __isKindOf(kind); }


protected:

   // ECL-RTTI-Events
   // ===============

   virtual const char *__getClassName() const
      { return "cEclObject"; }
   virtual bool __isKindOf(const char *kind) const
      { return strcmp(kind, "cEclObject") == 0; }

public:

   static cEclObject *__cast(const char *class_name, cEclObject *ptr);

};


#endif

/*.EH.*/
