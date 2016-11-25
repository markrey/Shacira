/*.SH.*/

/*
 *  Headerfile for module edb_var
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  edb_var.cpp on Wednesday March 20 2002  22:46:35
 */

#ifndef __edb_var__
#define __edb_var__


// Headerfiles
// ===========================================================================

#include "base/eb_sema.hpp"
#include "store/es_var.hpp"
#include "dbi/edb_sql.hpp"
#include "dbi/edb_transaction.hpp"
#include "dbi/edb_cursor_ex.hpp"


// ===========================================================================
// Definition cdbVar
// ---------------------------------------------------------------------------
//
// Ermoeglicht das Binden einer Read-Only-Storage an einen SQL-SELECT-
// Befehl. Dieser muss so formuliert sein, dass genau ein Datensatz mit
// einer Ergebnisvariablen geliefert wird. Werden Parametervariablen an
// die cdbVar gebunden, aktualisiert sich diese automatisch bei Aenderung
// einer der Parametervariablen.
//
// cBase
//  +--csBaseStorage
//      +--csStorage
//          +--csVar
//              +--cdbVar
//
// ===========================================================================

class __ECL_DLLEXPORT__ cdbVar : public csVar, public cdbTAObject {
   ECL_DECLARE(cdbVar,csVar)

public:

   // Default-Konstruktor
   cdbVar(cdbTransaction *ta, SQL::SELECT select, int flags = 0);
   // Default-Konstruktor
   cdbVar(cdbTransaction *ta, SQL::SELECT select, int width, int prec, int flags = 0);
   // Default-Konstruktor
   cdbVar(cdbTransaction *ta, SQL::SELECT select, TYPE type, int flags = 0);
   // Default-Konstruktor
   cdbVar(cdbTransaction *ta, SQL::SELECT select, TYPE type, int width, int prec, int flags = 0);
   // Destruktor
   ~cdbVar();


   // Flags
   // =====

   enum FLAGS { fStart = csVar::fUser,
      fWasFetched = fStart << 0,  // Variablenwert bereits geladen
      fUser       = fStart << 1   // Benutzerdefinierte Flags
   };


   // Parametervariablen
   // ==================

   // Binden einer Parametervariablen
   void bind(int n, csStorage *store);
   // Anzahl gebundener Parametervariablen erfragen
   int getBindCount() const;


   // Sonstiges
   // =========

   // Auszufuehrendes SELECT-Statement erfragen
   inline SQL::SELECT getSQL() const
      { return select; }


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um den Wert evtl. neu zu laden
   bool onRefetch();
   // Wird aufgerufen, um zu pruefen, ob das Feld Read-Only ist
   bool onCheckReadOnly() const;

   // Wird aufgerufen, um die Aktion 'func' auszufuehren
   void onExecAction(cdbDatabase *db, int func);
   // Wird aufgerufen, um den Abbruch der aktuellen Aktion anzufordern
   void onStopAction();
   // Wird aufgerufen, um eine textuelle Signatur der Aktion zu ermitteln
   cString onGetSignature();


private:

   SQL::SELECT select;        // Auszufuehrendes SELECT-Statement
   cEventSem wait_action;     // Warten auf Beendigung einer Aktion
   cErrBase last_error;       // Zuletzt aufgetretener Fehler
   bool last_rc;              // Ergebnis der letzten DB-Operation

   struct VARS;
   VARS *bind_vars;           // Zeiger auf Feld mit Parametervariablen

   // Intern: Ausfuehren der Aktionen bei refetch()
   void execRefetch(cdbDatabase *db);
   // Intern: Wird aufgerufen, wenn sich eine der gebundenen Variablen aendert
   void onEvtBindVarModified();

};


#endif

/*.EH.*/