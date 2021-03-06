/*.SH.*/

/*
 *  Headerfile for module ew_listctls
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  ew_listctls.cpp on Wednesday April 10 2002  23:35:58
 */

#ifndef __ew_listctls__
#define __ew_listctls__


// Headerfiles
// ===========================================================================

#include "base/eb_elo.hpp"
#include "win/ew_controls.hpp"


// ===========================================================================
// Definition cwListElem
// ---------------------------------------------------------------------------
//
// Fuer jedes cwListElem-Objekt werden die folgenden Standardfelder definiert:
//
//  - Schluesselfeld (Key): Enthaelt einen eindeutigen Schluesselwert fuer den
//    zum cwListElem-Objekt gehoerenden Datensatz.
//
//  - Namensfeld (Name): Enthaelt einen als Objektnamen benutzbaren, kurzen
//    Text. Bei einem Mitarbeiter-Datensatz koennte das Namensfeld z.B. aus
//    der Kombination Vorname + Nachname bestehen.
//
//  - Beschreibungsfeld (Descr): Enthaelt einen als Objektbeschreibung benutz-
//    baren, laengeren Text. Bei einem Mitarbeiter-Datensatz koennte das Be-
//    schreibungsfeld z.B. aus der Kombination Vorname + Nachname + Wohnort +
//    Strasse + Telefon bestehen.
//
//  - Sinnbildfeld (Icon): Enthaelt ein den Typ des Datensatzes beschreiben-
//    des Icon.
//
// Das Schluessel- und Namensfeld muss auf jeden Fall geliefert werden.
//
// Aufbau der Elemente im Speicher:
//
//    +------------+----------------+---+------+---+------+-..-+---+------+
//    | Data of    | Derived class  | S . DATA | S . DATA |    | S . DATA |
//    | cwListElem | additional mem | 1 .  1   | 2 .  2   |    | n .  n   |
//    +------------+----------------+---+------+---+------+-..-+---+------+
//
//  - S<i> = Statusbyte von Feld <i>
//  - DATA<i> = Datenbereich von Feld <i>
//
// cBase
//  +--cwListElem
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwListElem : public cEloElement {
   ELO_DECLARE(cwListElem,cEloElement)
   friend class cwListCtl;

public:

   // Default-Konstruktor
   cwListElem(const cEloElementDescription *elem_descr = 0) :
      cEloElement(elem_descr) { init(); }
   // Konstruktor ueber Query
   cwListElem(csQuery *query) :
      cEloElement(query->getDescription()) { init(query); }
   // Konstruktor ueber Defaultfelder
   cwListElem(cString key, cString name, cString descr = cString(),
              const cEloElementDescription *elem_descr = 0);
   // Destruktor
   ~cwListElem();


   // Speicherverwaltung
   // ==================

   // new-Operator
   void *operator op_new1(size_t size, cwListCtl *ctl);
   // delete-Operator
   void operator op_delete1(void *ptr, cwListCtl *ctl);
   // delete-Operator (speziell fuer VCPP)
   void operator delete(void *ptr);


   // Element-Flags
   // =============

   // Flags
   enum FLAGS { eflStart = 1,
      eflChildsLoaded   = eflStart << 0,  // Child-Elemente bereits geladen?
      eflChildsPossible = eflStart << 1,  // Child-Elemente moeglich, aber nicht geladen?
      eflChildsAutoView = eflStart << 2,  // Child-Elemente automatisch anzeigen?
      eflPreventSelect  = eflStart << 3,  // Verhindere Rekursion bei Selektion
      eflDisplayBold    = eflStart << 4,  // Schriftart BOLD benutzen
      eflDisplayFgColor = eflStart << 5,  // Abweichende Vordergrundfarbe benutzen (fg_col)
      eflDisplayBgColor = eflStart << 6,  // Abweichende Hintergrundfarbe benutzen (bg_col)
      eflUser           = eflStart << 7   // Benutzerdefinierte Flags
   };

   // Alle aktuellen Element-Flags ermitteln
   inline int getFlags() const
      { return flags; }
   // Bestimmte aktuelle Element-Flags ermitteln
   inline int getFlags(int mask) const
      { return flags & mask; }
   // Bestimmte Element-Flags setzen
   void setFlags(int mask, bool set = true);


   // Allgemeines
   // ===========

   // Zeiger auf zugehoeriges ListCtl ermitteln
   inline cwListCtl *getListCtl() const
      { return ctl; }
   // Zeiger auf zusaetzlichen Speicherbereich ermitteln (oder 0)
   void *getAddDataPtr() const;

   // Benutzerspezifische Zusatzinformationen setzen
   void setUserData(void *buf);
   // Benutzerspezifische Zusatzinformationen erfragen
   void *getUserData(void *buf, int buf_size) const;
   // Laenge der benutzerspezifischen Zusatzinformationen erfragen
   int getUserDataLen() const;
   // Pufferadresse der benutzerspezifischen Zusatzinformationen erfragen
   void *getUserDataBuf();

   // Datensatz aus Query erneut einlesen ('query' muss aktuelle Daten haben)
   void refresh(csQuery *query);

   // Liefert die Abfrage, die das Element erzeugt hat
   csQuery *getQuery() const;
   // Liefert die Abfrage, die Kinder dieses Elementes erzeugt
   csQuery *getSubquery() const;


   // Schriftart, Farben
   // ==================

   // Wird Datensatz mit Schriftattribut BOLD angezeigt?
   bool isBold() const;
   // Schriftattribut BOLD setzen/ruecksetzen
   void setBold(bool bold = true);

   // Aktuelle Vordergrundfarbe erfragen (cdColor::None = Standardfarbe)
   cdColor getFgColor() const;
   // Aktuelle Hintergrundfarbe erfragen (cdColor::None = Standardfarbe)
   cdColor getBgColor() const;
   // Abweichende Vordergrundfarbe setzen (Standardfarbe = cdColor::None)
   void setFgColor(const cdColor& new_fg_col);
   // Abweichende Hintergrundfarbe setzen (Standardfarbe = cdColor::None)
   void setBgColor(const cdColor& new_bg_col);


   // Feldbeschreibung
   // ================

   // Feldzahl (excl. Default-Felder, d.h. bei 0 sind Defaultfelder verfuegbar)
   int getCount() const;

   // Ermittelt den Typ eines Feldes
   csQuery::TYPE getType(int fld) const;
   // Kann das Feld NULL-Werte enthalten?
   bool isNullable(int fld) const;
   // Darf das Feld vom Anwender bearbeitet werden?
   bool isEditable(int fld) const;

   // Ermittelt die maximale Groesse eines Feldes
   int getBufferSize(int fld) const;
   // Maximale Feldbreite [Zeichen]
   int getWidth(int fld) const;
   // Anzahl Nachkommastellen [Zeichen]
   int getPrec(int fld) const;

   // Ermittelt den (Datenbank-)Namen eines Feldes
   cString getFieldName(int fld) const;


   // Feldwerte
   // =========

   // Ermittelt den NULL-Wert des Feldes
   bool isNull(int fld) const;
   // Setzt den NULL-Zustand bei einem Feld
   void setNull(int fld) const;

   // Erzeugt die String-Repraesentation des Feldes
   bool get(int fld, char *buf, int size) const;
   // Erzeugt die cString-Repraesentation des Feldes
   bool get(int fld, cString& buf) const;
   // Schreibt den Inhalt des Feldes in eine Storage
   bool get(int fld, csStorage *buf) const;

   // Wert des Feldes ueber int setzen
   bool put(int fld, int _buf);
   // Wert des Feldes ueber double setzen
   bool put(int fld, double _buf);
   // Wert des Feldes ueber cTime setzen
   bool put(int fld, cTime _buf);
   // Wert des Feldes ueber cDate setzen
   bool put(int fld, cDate _buf);
   // Wert des Feldes ueber cDateTime setzen
   bool put(int fld, cDateTime _buf);
   // Wert des Feldes ueber char setzen
   bool put(int fld, char _buf);
   // Wert des Feldes ueber String setzen
   bool put(int fld, const char *buf);
   // Wert des Feldes eine Storage setzen
   bool put(int fld, const csStorage *buf);

   // Erzeugt (per new) ein mit dem Feld assoziiertes csStorage-Objekt (const)
   const csStorage *makeVar(int fld) const;
   // Erzeugt (per new) ein mit dem Feld assoziiertes csStorage-Objekt (non-const)
   csStorage *makeVar(int fld);
   // Erzeugt (per new) ein mit dem Feld kompatibles (eigenstaendiges) csStorage-Objekt
   csStorage *makeCompatibleVar(int fld) const;


   // Verkettung
   // ==========

   // Zeiger auf Vorgaengerelement ermitteln
   inline cwListElem *getPrev() const
      { return prev; }
   // Zeiger auf Nachfolgeelement ermitteln
   inline cwListElem *getNext() const
      { return next; }
   // Zeiger auf erstes Kindelement ermitteln
   inline cwListElem *getFirstChild() const
      { return head; }
   // Zeiger auf letztes Kindelement ermitteln
   inline cwListElem *getLastChild() const
      { return tail; }
   // Zeiger auf Elternelement ermitteln
   inline cwListElem *getParent() const
      { return parent; }

   // Ist Element in eine Liste eingekettet?
   inline bool isLinked() const
      { return prev || next; }
   // Ist Element ein Kindelement?
   inline bool isChild() const
      { return parent != 0; }
   // Hat Element Kindelemente?
   inline bool hasChilds() const
      { return head || tail; }


protected:

   // Ueberschriebene Events
   // ======================

   // Wird aufgerufen, um die eindeutige Signatur des ELO-Objektes zu erfragen
   cString onGetSignature() const;
   // Wird aufgerufen, um den eindeutigen (textuellen) Schluessel des ELO-Objektes zu erfragen
   cString onGetKey() const;
   // Wird aufgerufen, um den Namen des ELO-Objektes zu erfragen
   cString onGetName() const;
   // Wird aufgerufen, um die textuelle Beschreibung des ELO-Objektes zu erfragen
   cString onGetDescr() const;
   // Wird aufgerufen, um die ID oder den Index des assoziierten Symbols zu erfragen
   int onGetBitmapId(BITMAP_STYLE bs) const;


private:

   cwListCtl *ctl;               // ListCtl, in dem das Element angezeigt wird
   cdColor fg_col, bg_col;       // Evtl. abweichende Vorder- oder Hintergrundfarbe
   int flags;                    // Element-Flags

   cwListElem *prev, *next;      // Vorgaenger und Nachfolger in der Liste
   cwListElem *head, *tail;      // Erstes und letztes Kind-Element der Liste
   cwListElem *parent;           // Eltern-Knoten bei hierarchischer Struktur

   // Initialisierung aus Abfrage
   void init(csQuery *query = 0);

};


// ===========================================================================
// Definition cwListCtl
// ---------------------------------------------------------------------------
//
// cBase
//  +--cwWindow
//      +--cwControl
//          +--cwListCtl
//
// ===========================================================================

class __ECL_DLLEXPORT__ cwListCtl : public cwControl {
   ELO_DECLARE(cwListCtl,cwControl)
   friend class ccwListCtl;
   friend class cwListElem;

public:

   // Destruktor
   virtual ~cwListCtl();


   // Allgemeines
   // ===========

   // Array-Zugriffsoperator
   inline cwListElem * operator[](int idx) const
      { return onGetElemWithIndex(idx); }

   // Feld 'fld' als Element-Signatur benutzen
   void setSigOffField(int fld = csQuery::fldName);
   // User-Data (ab 'offset') fuer Element-Signatur setzen
   void setSigOffUserData(int offset = 0);

   // Standard-Aktionsbeschreibung einrichten
   void setupDefActionDescr(cEloActionDescription *new_action_descr);
   // Ausloesen des Events 'evtOperationExecuted'
   void callOperationEvent(cwListElem *elem, int event);

   // Versucht den Wert des Schluesselfeldes 'key_name' der zugrunde-
   // liegenden Query zu ermitteln, ohne dass ein Datensatz geladen
   // sein muss (oder 0 falls nicht ermittelbar)
   cString getKeyValue(cString key_name) const;


   // window-Flags
   // ============

   enum FLAGS { wflStart = cwControl::wflUser,
      wflAutoRequery    = wflStart << 0,  // Automatisches Requery bei Refresh?
      wflQueryExecuted  = wflStart << 1,  // Query mindestens einmal ausgefuehrt?
      wflColumnsInit    = wflStart << 2,  // Spalten bereits angelegt?
      wflUserDataInit   = wflStart << 3,  // Benutzerdaten bereits angelegt?
      wflInSelectAll    = wflStart << 4,  // Wird waehrend doSelectAllElems gesetzt
      wflUser           = wflStart << 5   // Benutzerdefinierte Flags
   };


   // window-Styles
   // =============

   // Styles
   enum STYLES { wsStart = cwControl::wsUser,
      wsAutoRequery     = wsStart << 0,   // Automatisches Requery bei Refresh (Default)
      wsUser            = wsStart << 1    // Benutzerdefinierte Styles
   };


   // Events
   // ======

   // Event-IDs dieser Klasse
   enum EVENTS { evtFirst = cwControl::evtUser,
     evtSelectionChanging,             // (EVFUNC_P)  Selektion vor Aenderung
     evtSelectionChanged,              // (EVFUNC_P)  Selektion geaendert
     evtListElemSelected,              // (EVFUNC_P)  Listenelement ausgewaehlt
     evtAllListElemsRefreshed,         // (EVFUNC_I)  Refresh der gesamten Liste durchfuehrt
     evtSingleListElemRefreshed,       // (EVFUNC_PI) Refresh eines Einzelelementes durchgefuehrt
     evtNewListElemsInserted,          // (EVFUNC_PI) Einfuegen neuer Elemente durchgefuehrt
     evtBeginDrag,                     // (EVFUNC_PI) Beginn einer Dragoperation
     evtBeginEdit,                     // (EVFUNC_PI) Beginn einer Edit-Operation
     evtStoreEdit,                     // (EVFUNC_PI) Edit-Operation beendet: Speichern
     evtDiscardEdit,                   // (EVFUNC_PI) Edit-Operation beendet: Verwerfen
     evtOperationExecuted,             // (EVFUNC_PI) ELO-Operation ausgefuehrt
     evtUser                           // Benutzerdefinierte Events
   };


   // Anmerkung:
   // ----------
   // Durch insertNewListElems() werden alle durch die angegebene Query gelieferte
   // Elemente in das List-Control eingefuegt. Voraussetzung ist jedoch, dass
   // die Insert-Query die gleiche Spaltenstruktur liefert wie die Original-
   // Query (also sinnvollerweise durch Ableitung daraus entstanden ist) und
   // dass die neuen Elemente nicht bereits im List-Control vorhanden sind.
   // Startet den Refresh aller Elemente

   // Startet den Refresh der gesamten Liste
   bool refreshAllListElems();
   // Startet den Refresh eines einzelnen Elementes
   bool refreshListElem(cwListElem *elem);
   // Startet das nachtraegliche Einfuegen eines bestimmten neuen Elementes
   bool insertNewListElem(csQuery *query, cString key, cwListElem *before, cwListElem *parent = 0);
   // Startet das nachtraegliche Einfuegen neuer Elemente
   bool insertNewListElems(csQuery *query, cwListElem *before, cwListElem *parent = 0);


   // List-Control einrichten
   // =======================

   // Anmerkungen:
   //  - Die manuelle Einrichtung der Felder ist beim Fuellen des List-Controls
   //    ueber eine Query nicht noetig!
   //  - Nachdem das erste Element angefordert wurde (allocElem), darf die Ein-
   //    richtung der Felder nicht mehr geaendert werden!

   enum HALIGN { haDefault = 0, haLeft, haCenter, haRight };
   enum VALIGN { vaDefault = 0, vaTop, vaCenter, vaBottom };

   enum FIELD_INFO_FLAGS {
      fifIsNotNull         = 1 << 0,   // Gesetzt, wenn Feld kann keine Nullwerte enthalten kann
      fifIsReadOnly        = 1 << 1,   // Gesetzt, wenn Feld schreibgeschuetzt sein soll
      fifIsInvisible       = 1 << 2,   // Gesetzt, wenn Feld unsichtbar sein soll
      fifHasSeparator      = 1 << 3    // Gesetzt, wenn nach Feld eine vert. Linie eingef. werden soll
   };

   struct FIELD_INFO {
      cString           name;          // Feldname
      csQuery::TYPE     type;          // Datentyp
      int               flags;         // Flags (vgl. oben)
      int               buffer_size;   // Puffergroesse (nur bei tString relevant)
      int               width;         // Maximale Feldbreite [Zeichen]
      int               prec;          // Anzahl Nachkommastellen [Zeichen]
      HALIGN            halign;        // Horizontale Ausrichtung des Feldinhaltes
      VALIGN            valign;        // Vertikale Ausrichtung des Feldinhaltes
      int               row;           // Anzeigeposition: Zeile (-1 falls gleiche Zeile wie voriges Feld)
      int               col;           // Anzeigeposition: Spalte (-1 falls naechste Spalte)
      int               join_rows;     // Zellenverbindung senkrecht: Anzahl weiterer Felder (0 = Default)
      int               join_cols;     // Zellenverbindung waagrecht: Anzahl weiterer Felder (0 = Default)
      cString           title;         // Titel-Text
      HALIGN            title_halign;  // Horizontale Ausrichtung des Spaltentitels
      VALIGN            title_valign;  // Vertikale Ausrichtung des Spaltentitels
   };

   // 1. List-Control (neu) einrichten, Anzahl Felder und Zeilen pro Datensatz setzen
   void resetListCtl(int field_count, int row_count = 1);
   // 2.1 Feld 'fld' einrichten (Muss fuer jedes Feld einmal aufgerufen werden!)
   void setupField(int fld, const FIELD_INFO& field_info);
   // 2.2 Feld 'fld' als String-Feld einrichten (Alternative zu 2.1)
   void setupField(int fld, cString name, cString title, int flags, int buffer_size, int width = -1);
   // 2.3 Feld 'fld' als Zahlen-Feld einrichten (Alternative zu 2.1)
   void setupField(int fld, cString name, cString title, csQuery::TYPE type, int flags, int width, int prec = 1);
   // 3. Konfiguration des List-Controls uebernehmen
   void setupListConfig(int key_len = 16, int name_len = 64, int descr_len = -1);


   // Spalten
   // =======

   // Anzahl Spalten ermitteln
   int getColumnCount() const;
   // Anzahl Zeilen (pro Datensatz) ermitteln
   int getRowCount() const;
   // Anzahl verbundener Zellen waagrecht ermitteln
   int getJoinColumns(int fld) const;
   // Anzahl verbundener Zellen senkrecht ermitteln
   int getJoinRows(int fld) const;
   // Feld ermitteln, das in Spalte 'col' angezeigt wird
   int getFieldFromColumn(int col, int row = 0) const;
   // Spalte ermitteln, in der Feld 'fld' angezeigt wird (-1 falls nicht angezeigt)
   int getColumnFromField(int fld) const;
   // Zeile ermitteln, in der Feld 'fld' angezeigt wird (-1 falls nicht angezeigt)
   int getRowFromField(int fld) const;


   // Elementverwaltung
   // =================

   // Einfache Erfragefunktionen
   // --------------------------

   // Erstes Element der Liste
   inline cwListElem *getFirstElem() const
      { return anchor_head; }
   // Letztes Element der Liste
   inline cwListElem *getLastElem() const
      { return anchor_tail; }
   // Element vor Referenzelement
   inline cwListElem *getPrevElem(cwListElem *elem) const
      { return elem ? elem->prev : anchor_tail; }
   // Element nach Referenzelement
   inline cwListElem *getNextElem(cwListElem *elem) const
      { return elem ? elem->next : anchor_head; }
   // Erstes Kindelement des Referenzelementes
   inline cwListElem *getFirstChildElem(cwListElem *elem) const
      { return elem ? elem->head : anchor_head; }
   // Letztes Kindelement des Referenzelementes
   inline cwListElem *getLastChildElem(cwListElem *elem) const
      { return elem ? elem->tail : anchor_tail; }
   // Elternelement des Referenzelementes
   inline cwListElem *getParentElem(cwListElem *elem) const
      { return elem ? elem->parent : 0; }

   // Element ueber Index erfragen
   inline cwListElem *getElemWithIndex(int idx) const
      { return onGetElemWithIndex(idx); }

   // Liefert die Abfrage, die das Element erzeugt hat (bzw. die Abfrage,
   // die die Kinder des Elementes erzeugt, wenn sub_query = true)
   inline csQuery *getQueryOfElem(const cwListElem *elem, bool sub_query = false) const
      { return onGetQueryOfElem(elem, sub_query); }


   // Verkettung
   // ----------

   // Ist Element in eine Liste eingekettet?
   inline bool isElemInserted(cwListElem *elem) const
      { return elem->isLinked() || elem->parent || anchor_head == elem; }
   // Ist Element 'elem' ein Kindelement?
   inline bool isElemChild(cwListElem *elem) const
      { return elem->isChild(); }
   // Hat Element 'elem' Kindelemente?
   inline bool hasElemChilds(cwListElem *elem) const
      { return elem->hasChilds(); }


   // Komplexere Erfragefunktionen
   // ----------------------------

   // Anzahl der selektierten Elemente ermitteln
   inline int getSelectedElemCount(bool walk = false) const
      { return onGetSelectedElemCount(walk); }
   // Selektierte Elemente ermitteln
   inline cwListElem *getSelectedElem(cwListElem *elem = 0, bool walk = false) const
      { return onGetSelectedElem(elem, walk); }
   // Element ueber Schluessel ermitteln
   inline cwListElem *getElemWithKey(cString key, cwListElem *parent = 0, bool walk = false) const
      { return onGetElemWithKey(key, parent, walk); }
   // Zaehlt Elemente von vorne her durch
   inline int getElemCountFromBegin(cwListElem *elem) const
      { return onGetElemCountFromBegin(elem); }
   // Zaehlt Elemente von hinten her durch
   inline int getElemCountFromEnd(cwListElem *elem) const
      { return onGetElemCountFromEnd(elem); }


   // Selektion
   // ---------

   // Einzelnes Element selektieren
   bool selectElem(cwListElem *elem, bool sel = true);
   // Einzelnes Element deselektieren
   bool deselectElem(cwListElem *elem);
   // Alle Elemente selektieren
   bool selectAllElems(cwListElem *parent = 0, bool walk = false);
   // Alle Elemente deselektieren
   bool deselectAllElems(cwListElem *parent = 0, bool walk = false);


   // Cursor
   // ------

   // Element mit Cursor erfragen
   inline cwListElem *getCursoredElem() const
      { return onGetCursoredElem(); }
   // Cursor auf Element setzen
   inline bool setCursoredElem(cwListElem *elem)
      { return onSetCursoredElem(elem); }


   // Sichtbarkeit
   // ------------

   // Sicherstellen, dass Element 'elem' (wenigstens teilweise) sichtbar ist
   inline bool ensureElemVisible(cwListElem *elem, bool partial_ok = true)
      { return onEnsureElemVisible(elem, partial_ok); }
   // Sicherstellen, dass Feld 'fld' (wenigstens teilweise) sichtbar ist
   inline bool ensureFieldVisible(int fld, bool partial_ok = true)
      { return onEnsureFieldVisible(fld, partial_ok); }


   // Element erzeugen
   // ----------------

   // Neues Element erzeugen (freigeben mit deleteElem)
   cwListElem *allocElem(const cEloElementDescription *elem_descr = 0);
   // Neues Element ueber Query erzeugen (freigeben mit deleteElem)
   cwListElem *allocElem(csQuery *query);
   // Neues Element ueber Defaultfelder erzeugen (freigeben mit deleteElem)
   cwListElem *allocElem(cString key, cString name, cString descr = cString(),
                         const cEloElementDescription *elem_descr = 0);


   // Einfuegen/Loeschen
   // ------------------

   // Am Anfang der Liste einfuegen
   bool insertElemAtBegin(cwListElem *new_elem, cwListElem *parent = 0, bool invd = false);
   // Am Ende der Liste einfuegen
   bool insertElemAtEnd(cwListElem *new_elem, cwListElem *parent = 0, bool invd = false);
   // Vor Referenzelement einfuegen
   bool insertElemBefore(cwListElem *new_elem, cwListElem *ref_elem = 0, cwListElem *parent = 0, bool invd = false);
   // Nach Referenzelement einfuegen
   bool insertElemAfter(cwListElem *new_elem, cwListElem *ref_elem = 0, cwListElem *parent = 0, bool invd = false);
   // Element aus Liste ausklinken (ohne loeschen)
   bool removeElem(cwListElem *elem, bool invd = false);
   // Alle Elemente unterhalb von 'parent' aus Liste ausklinken (ohne loeschen)
   bool removeAllElems(cwListElem *parent = 0, bool invd = false);
   // Element ausklinken und loeschen
   bool deleteElem(cwListElem *elem, bool invd = false);
   // Alle Elemente unterhalb von 'parent' ausklinken und loeschen
   bool deleteAllElems(cwListElem *parent = 0, bool invd = false);


   // Aufzaehlung
   // -----------

   // Prototyp fuer Callback-Funktionen von doWithAllElems()
   typedef bool (*ENUM_ELEM_FUNC)(cwListCtl *list, cwListElem *elem, void *data);

   // Ruft fuer jedes Element eine Funktion func auf
   bool doWithAllElems(ENUM_ELEM_FUNC func, void *data, cwListElem *parent = 0, bool walk = false);


   // Editieren
   // ---------

   // Edit-Operation fuer Feld 'fld' von Listenelement 'elem' beginnnen
   bool beginEdit(cwListElem *elem, int fld);
   // Edit-Operation beenden (oder abbrechen)
   void endEdit(bool cancel = false);
   // Rechteck des Edit-Controls fuer Feld 'fld' von Element 'elem' ermitteln
   cdRect getEditRect(cwListElem *elem, int fld) const;

   // Aktuelles Control ermitteln, das zur Bearbeitung benutzt wird (oder 0)
   inline cwControl *getEditCtl() const
      { return edit_ctl; }
   // Aktuell von Edit bearbeitetes Listenelement ermitteln (oder 0)
   inline cwListElem *getEditElem() const
      { return edit_elem; }
   // Aktuell von Edit bearbeitetes Listenfeld ermitteln (oder 0)
   inline int getEditField() const
      { return edit_fld; }


protected:

   // Ueberschriebene Events
   // ======================

   // Abbruch mit Speichern erlauben?
   bool onAllowStore();
   // Abbruch ohne Speichern erlauben?
   bool onAllowDiscard();
   // Schliessen des Fensters erlauben?
   bool onAllowClose(cwWindow *notify);

   // Inhalt refreshen (false -> Abbruch)
   bool onRefresh();
   // Wird aufgerufen, wenn sich das gebundene Datenobjekt geaendert hat
   void onEventModified();

   // Befehl ausfuehren (von Menu, Control oder Accelerator)
   bool onCommand(const cwCmdEvt& cmd);
   // Update Benutzerschnittstelle
   bool onCommandUI(cwCmdUI& cmd);

   // Wird aufgerufen, um zu erfragen, ob eine ELO-Element-Selektion moeglich ist
   bool onHasWindowElemSelection() const;
   // Wird aufgerufen, um die aktuelle ELO-Element-Selektion zu ermitteln
   bool onUpdateWindowElemSelection(cEloSelection& selection) const;
   // Wird aufgerufen, um den Zeiger auf ein aktuelles ELO-Selektionsobjekt zu ermitteln
   cEloSelection *onGetWindowElemSelection();
   // Wird aufgerufen, um den Zeiger auf die ELO-Aktionsbeschreibung zu ermitteln
   cEloActionDescription *onGetWindowActionDescription(const cEloSelection *selection) const;

   // Daten des Controls refreshen
   bool onRefreshCtl(csStorage *store);
   // Abfrage des Controls erneut durchfuehren
   bool onRequeryCtl(csQuery *query);
   // Daten des Controls pruefen
   DATAERR onCheckCtl(csStorage *store);
   // Daten des Controls speichern
   DATAERR onStoreCtl(csStorage *store);

   // Wird aufgerufen, um die durch 'mask' spezifizierten Window-Styles zu ermitteln
   int onGetStyles(int mask) const;
   // Wird aufgerufen, um Window-Styles zu setzen (add) und zu entfernen (remove)
   void onModifyStyles(int add, int remove, int os_add[], int os_remove[]);


   // Zusaetzliche Events
   // ===================

   // Wird aufgrufen beim Versuch, das Fenster waehrend der Abfrage zu schliessen
   virtual bool onErrorInQuery();

   // Wird aufgerufen, um den Beginn einer Drag-Operation bekanntzugeben
   virtual void onBeginDrag(cwListElem *elem, int mouse_button);
   // Wird aufgerufen, um den Beginn einer Edit-Operation bekanntzugeben
   virtual bool onBeginEdit(cwListElem *elem, int fld);
   // Wird aufgerufen, um das Ende einer Edit-Operation bekanntzugeben
   virtual bool onEndEdit(cwListElem *elem, int fld, cString text);
   // Wird aufgerufen, um das Rechteck fuer das Edit-Control zu ermitteln
   virtual cdRect onGetEditRect(cwListElem *elem, int fld) const;
   // Wird aufgerufen, um das Edit-Control zu erzeugen
   virtual cwControl *onMakeEditCtl(cwListElem *elem, int fld, const cdRect& rect);

   // Wird aufgerufen, bevor sich die Selektion aendert (true = Aenderung zulassen)
   virtual bool onSelectionChanging(cwListElem *elem);
   // Wird aufgerufen, wenn ein Element selektiert wurde
   virtual void onSelectionChanged(cwListElem *elem);
   // Wird aufgerufen, wenn Enter gedrueckt wurde oder bei Doppelklick
   virtual void onListElemSelected(cwListElem *elem);

   // Wird aufgerufen, um den Default-Text bei NULL-Werten zu ermitteln
   virtual cString onGetNullText();

   // Wird aufgerufen, um ein Element ueber dessen Schluessel zu ermitteln
   virtual cwListElem *onGetElemWithKey(cString key, cwListElem *parent, bool walk) const;
   // Wird aufgerufen, um ein Element ueber dessen Index zu ermitteln
   virtual cwListElem *onGetElemWithIndex(int idx) const;
   // Wird aufgerufen, um die Elemente von vorne her durchzuzaehlen
   virtual int onGetElemCountFromBegin(cwListElem *elem) const;
   // Wird aufgerufen, um die Elemente von hinten her durchzuzaehlen
   virtual int onGetElemCountFromEnd(cwListElem *elem) const;

   // Wird aufgrufen, um die Anzahl der selektierten Elemente zu ermitteln
   virtual int onGetSelectedElemCount(bool walk) const;
   // Wird aufgerufen, um die selektierten Elemente zu ermitteln
   virtual cwListElem *onGetSelectedElem(cwListElem *elem, bool walk) const = 0;
   // Wird aufgerufen, um die Selektion fuer ein einzelnes Element zu aendern
   virtual bool onSelectElem(cwListElem *elem, bool sel) = 0;
   // Wird aufgerufen, um die Selektion fuer alle Elemente zu aendern
   virtual bool onSelectAllElems(bool sel, cwListElem *parent, bool walk);

   // Wird aufgerufen, um das Element mit Cursor zu erfragen
   virtual cwListElem *onGetCursoredElem() const = 0;
   // Wird aufgerufen, um den Cursor auf ein Element zu setzen
   virtual bool onSetCursoredElem(cwListElem *elem) = 0;

   // Wird aufgerufen, um sicherzustellen, dass Element 'elem' sichtbar ist
   virtual bool onEnsureElemVisible(cwListElem *elem, bool partial_ok);
   // Wird aufgerufen, um sicherzustellen, dass Feld 'fld' sichtbar ist
   virtual bool onEnsureFieldVisible(int fld, bool partial_ok);

   // Wird aufgerufen, um ein Element an Position 'pos', 'ref_elem' anzuzeigen
   virtual bool onInsertElemAt(int pos, cwListElem *ref_elem, cwListElem *new_elem, cwListElem *parent, bool invd) = 0;
   // Wird aufgerufen, um ein Element von der Anzeige zu entfernen
   virtual bool onRemoveElem(cwListElem *elem, bool invd) = 0;
   // Wird aufgerufen, um alle Elemente unterhalb von 'parent' von der Anzeige zu entfernen
   virtual bool onRemoveAllElems(cwListElem *parent, bool invd) = 0;

   // Wird aufgerufen, bevor die Abfrage gestartet wird
   virtual bool onQueryPreStart(csQuery *query);
   // Wird aufgerufen, wenn die Abfrage gestartet wurde, um den Listeninhalt zu loeschen
   virtual bool onQueryStarted(csQuery *query);
   // Wird aufgerufen, wenn ein Datensatz verfuegbar ist, um ihn zur Liste hinzuzufuegen
   virtual bool onQueryData(csQuery *query);
   // Wird aufgerufen, wenn die Abfrage beendet ist, um die Selektion anzeigen
   virtual bool onQueryEnded(csQuery *query);
   // Wird aufgerufen, nachdem die Abfrage beendet wurde
   virtual void onQueryPostEnd(csQuery *query);

   // Wird aufgerufen, bevor die Einzelabfrage gestartet wird
   virtual bool onQuery1PreStart(cwListElem *elem, csQuery *query);
   // Wird aufgerufen, wenn die Einzelabfrage gestartet wurde
   virtual bool onQuery1Started(cwListElem *elem, csQuery *query);
   // Wird aufgerufen, wenn ein Datensatz der Einzelabfrage verfuegbar ist
   virtual bool onQuery1Data(cwListElem *elem, csQuery *query);
   // Wird aufgerufen, wenn die Einzelabfrage beendet ist
   virtual bool onQuery1Ended(cwListElem *elem, csQuery *query);
   // Wird aufgerufen, nachdem die Einzelabfrage beendet wurde
   virtual void onQuery1PostEnd(cwListElem *elem, csQuery *query);

   // Wird aufgerufen, bevor die Einfuegeabfrage gestartet wird
   virtual bool onInsQueryPreStart(cwListElem *before, cwListElem *parent, csQuery *query);
   // Wird aufgerufen, wenn die Einfuegeabfrage gestartet wurde
   virtual bool onInsQueryStarted(cwListElem *before, cwListElem *parent, csQuery *query);
   // Wird aufgerufen, wenn ein Datensatz der Einfuegeabfrage verfuegbar ist
   virtual bool onInsQueryData(cwListElem *before, cwListElem *parent, csQuery *query);
   // Wird aufgerufen, wenn die Einfuegeabfrage beendet ist
   virtual bool onInsQueryEnded(cwListElem *before, cwListElem *parent, csQuery *query);
   // Wird aufgerufen, nachdem die Einfuegeabfrage beendet wurde
   virtual void onInsQueryPostEnd(cwListElem *before, cwListElem *parent, csQuery *query);

   // Wird aufgerufen, wenn ein Element des Controls erzeugt wird
   virtual void onCreatingElement(cwListElem *elem);
   // Wird aufgerufen, wenn ein Element des Controls geloescht wird
   virtual void onDeletingElement(cwListElem *elem);

   // Wird aufgerufen, um die Abfrage zu erfragen, die das Element erzeugt hat
   virtual csQuery *onGetQueryOfElem(const cwListElem *elem, bool sub_query) const;

   struct SETUP_ROWCOL_INFO {
      const csQuery *query;      // Aktuelle Abfrage
      int old_row_count;         // Bisherige Zeilenzahl (pro Datensatz)
      int new_row_count;         // Neue Zeilenzahl (pro Datensatz)
      int old_column_count;      // Bisherige Spaltenzahl
      int new_column_count;      // Neue Spaltenzahl
   };

   struct FIELD_DESCR;
   struct SETUP_FIELD_INFO {
      const csQuery *query;      // Aktuelle Abfrage
      const FIELD_DESCR *descr;  // Beschreibung des aktuellen Feldes
      int disp_row;              // Zeile, in der das Feld angezeigt werden soll
      int disp_col;              // Spalte, in der das Feld angezeigt werden soll
      int join_x;                // Anzahl zu verbindender Zellen waagrecht
      int join_y;                // Anzahl zu verbindender Zellen senkrecht
      bool add;                  // Feld hinzufuegen?
   };

   // Wird aufgerufen, um die Anzahl zusaetzlich benoetigter Bytes im Element zu erfragen
   virtual int onGetAddByteCount() const;
   // Wird aufgerufen, um zu erfragen, ob mehrere Zeilen pro Datensatz unterstuetzt werden
   virtual bool onAllowsMultipleRows() const;
   // Wird aufgerufen, wenn sich die Spalten- oder Zeilenzahl (pro DS) geaendert hat
   virtual void onSetupRowCol(const SETUP_ROWCOL_INFO& info);
   // Wird aufgerufen, um in Spalte das Feld 'fld' zur Anzeige vorzubereiten
   virtual void onSetupField(int fld, const SETUP_FIELD_INFO& info);
   // Wird einmalig nach der Einrichtung der benutzerspezifischen Daten aufgerufen
   virtual void onPostUserDataInit();

   enum ELEM_ATTR {
      eatFontBold,               // Schriftart-Attribut "BOLD" geaendert
      eatColorFg,                // Farb-Attribut "Vordergrundfarbe" geaendert
      eatColorBg                 // Farb-Attribut "Hintergrundfarbe" geaendert
   };

   // Wird aufgerufen, wenn das Schriftart-Attribut eines Elementes aendert
   virtual void onElemAttrChanged(cwListElem *elem, ELEM_ATTR attr);


   // Verzoegerte Ausfuehrung
   // =======================

   enum  { ediStart = cwControl::ediUser,
      ediEndEdit,          // Verzoegerte Ausfuehrung von endEdit()
      ediNavigateEdit,     // Verzoegerte Ausfuehrung von endEdit(true) und Navigation
      ediUse               // ab hier Erweiterungen
   };

   // Verzoegertes Ausfuehren einer Operation
   void onExecDelayed(int id, void *data);


protected:

   // Interner Konstruktor
   cwListCtl(void *wnd);


   // Elementbeschreibung
   // ===================

   enum STATUSBYTE {
      sbmIsNull      = 0x01   // Das Feld hat den NULL-Zustand
   };

   struct FIELD_DESCR {
      int offset;                   // Offset (auf Statusbyte) in cwListElem
      int buffer_size;              // Groesse des Feldes (in Bytes)
      int disp_column;              // Feld wird angezeigt in Spalte 'disp_column'
      int disp_row;                 // Feld wird angezeigt in Zeile 'disp_row'
      int join_x;                   // Die naechsten 'join_x' Spalten verbinden
      int join_y;                   // Die naechsten 'join_y' Zeilen verbinden
      int disp_width;               // Maximale Anzeigebreite
      int disp_prec;                // Maximale Anzahl Nachkommastellen
      bool disp_thsnd_sep;          // Tausender-Separatoren anzeigen?
      bool disp_left_pad;           // Zahlen links mit 0en auffuellen?
      bool nullable;                // Darf das Feld den NULL-Zustand annehmen?
      bool editable;                // Darf das Feld vom Anwender bearbeitet werden?
      csQuery::HALIGN halign;       // Horizontale Ausrichtung des Feldinhaltes
      csQuery::VALIGN valign;       // Vertikale Ausrichtung des Feldinhaltes
      csQuery::HALIGN title_halign; // Horizontale Ausrichtung des Spaltentitels
      csQuery::VALIGN title_valign; // Vertikale Ausrichtung des Spaltentitels
      csQuery::TYPE type;           // Typ des Feldes (vgl. csQuery)
      cString title;                // Titel-Text (vgl. csQuery)
      cString name;                 // Feldname (vgl. csQuery)
   };

   // Alle Elemente freigeben
   void cleanup();
   // Alle Kind-Elemente von 'parent' freigeben
   void cleanup(cwListElem *parent);
   // Ausfuehren von 'onSelectElem'
   bool doSelectElem(cwListElem *elem, bool sel);
   // Ausfuehren von 'onSelectAllElems'
   bool doSelectAllElems(bool sel, cwListElem *parent, bool walk);


private:

   // Abfrage
   // =======

   cwListElem *ins_before;    // insertNewListElems(): Referenz-Element
   cwListElem *ins_parent;    // insertNewListElems(): Eltern-Element
   cwListElem *rfs_elem;      // refreshListElem(): Betroffenes Element

   // Wird von refreshAllListElems() zum Fuellen der Liste aufgerufen
   int onRefreshQuery(void *p1, int p2);
   // Wird von refreshListElem() zum Element-Refresh aufgerufen
   int onRefreshQuery1(void *p1, int p2);
   // Wird zum insertNewListElems() zum Einfuegen eines neuen Elementes aufgerufen
   int onInsertQuery(void *p1, int p2);


   // Elementverkettung
   // =================

   cwListElem *anchor_head;   // Erstes Element der Element-Liste
   cwListElem *anchor_tail;   // Letztes Element der Element-Liste


   // Elementbeschreibung
   // ===================

   int field_count;           // Anzahl Felder (incl. Default-Felder, d.h. mind. 4)
   int field_data_size;       // Gesamtgroesse Datenfelder = field_count * (buffer_size+1)
   FIELD_DESCR *field_descr;  // Array mit 'field_count' Feldbeschreibungen

   int user_data_size;        // Groesse der benutzerspezifischen Zusatzinformationen im Element
   int user_data_offset;      // Offset in die benutzerspezifischen Daten des Elementes
   int signature_offset;      // Offset des Textes, der als Element-Signatur verwendet wird

   int column_count;          // Anzahl Spalten (d.h. sichtbare Spalten)
   int row_count;             // Anzahl Zeilen (pro Datensatz)
   int old_column_count;      // Fuer setupListConfig: Bisherige Spaltenzahl
   int old_row_count;         // Fuer setupListConfig: Bisherige Zeilenzahl pro Datensatz
   int *field_column;         // Zuordnung: Spalte 'idx' zeigt Feld 'fld' an

   char *selected_elems;      // Key-Werte der selektierten Elemente (fuer Requery)
   int selected_count;        // Anzahl selektierter Elemente (fuer Requery)

   // Benutzerspezifische Zusatzinformationen einrichten
   bool setupUserData(int new_user_data_size);
   // Spalteninformationen aus der Query uebernehmen
   void setupColumns(csQuery *query);
   // Aktuelle Selektion speichern (vor Requery)
   void saveSelection();
   // Gespeicherte Selektion wieder herstellen (nach Requery)
   void restoreSelection();


   // Aktionsbeschreibung
   // ===================

   cEloActionDescription *action_descr;   // Default-Aktionsbeschreibung


   // Zellen-Editor
   // =============

   cwControl *edit_ctl;       // Zeiger auf aktuelles Edit-Control
   cwListElem *edit_elem;     // Momentan durch Edit bearbeitetes Element...
   int edit_fld;              // ... und Feld

   // Wird aufgerufen, wenn im Edit-Control die ENTER-Taste gedrueckt wird
   void onEvtEnterKey();
   // Wird aufgerufen, wenn im Edit-Control die ESC-Taste gedrueckt wird
   void onEvtEscKey();
   // Wird aufgerufen, wenn im Edit-Control eine Navigationstaste gedrueckt wird
   void onEvtNavKey(int p1);

};


#endif

/*.EH.*/
