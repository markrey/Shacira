/*.SH.*/

/*
 *  Headerfile for module eb_err
 *
 *  Generated by C-Head Version 1.3
 *  (c) 1993 by 2i Industrial Informatics GmbH
 *
 *  This file has been extracted from the source file
 *  eb_err.cpp on Saturday March 23 2002  18:15:16
 */

#ifndef __eb_err__
#define __eb_err__


// Headerfiles
// ===========================================================================

#include "base/eb_base.hpp"


// ===========================================================================
// Definition cErrBase
// ---------------------------------------------------------------------------
//
// Kodierung der Fehlermeldungen in einem 32-Bit Long:
//
//    31           24 23           16 15            8 7 6 5         0
//   +---------------+---------------+---------------+---+-----------+
//   |P P P P P P P P|P P P P P P P P|P P P P P P P P|C C E E E E E E|
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// wobei:
//
//    PPP = der Modulpraefix als 3-Zeichen Eyecatcher
//    C   = die Fehlerklasse
//    EE  = der Fehlercode - 1
//
// Moegliche Fehlerklassen:
//
//    00 = (I) Informationen
//    01 = (W) Warnungen
//    10 = (E) Fehler
//    11 = (F) Fatale Fehler
//
// Die Ausgabe der Fehlermeldung erfolgt in folgender Syntax:
//
//    PPP-C-EE: Fehlermeldung
//
// cBase
//  +--cErrBase
//
// ===========================================================================

class __ECL_DLLEXPORT__ cErrBase : public cBase {

// Allgemeine Fehlercodes
// ======================

public:

   // Lesen der Fehlermeldungsdatei erzwingen
   static void initialize();

   typedef unsigned long ERR_TYPE; // 32-Bit

   #define ERR_PREFIX(c1,c2,c3)                 \
      (   (cErrBase::ERR_TYPE)(c1) * 0x01000000L  \
        + (cErrBase::ERR_TYPE)(c2) * 0x00010000L  \
        + (cErrBase::ERR_TYPE)(c3) * 0x00000100L )

   #define errInfo   0L    /* Informationen  */
   #define errWarn   64L   /* Warnungen      */
   #define errError  128L  /* Fehler         */
   #define errFatal  192L  /* Fatale Fehler  */

   enum ERR_CODE { errBase = ERR_PREFIX('E','R','R'),

      // Kein Fehler
      errNoError     = 0                , // Kein Fehler

      // Informationen
      errSorry       = errBase+errInfo  , // Noch nicht implementiert
      errMalformed                      , // Fehlercode-Textform ungueltig

      // Fehler
      errGeneral     = errBase+errError , // Allgemeiner Fehler
      errInvPointer                     , // Ungueltiger Zeiger
      errInvHandle                      , // Ungueltiges Handle
      errInvParam                       , // Ungueltiger Parameter
      errInit                           , // Fehler bei Initialisierung
      errTimeout                        , // Zeitueberschreitung
      errOverflow                       , // Ueberlauf jeglicher Art
      errUnderflow                      , // Unterlauf jeglicher Art

      // Fatale Fehler
      errNoMem       = errBase+errFatal , // Kein freier Speicher mehr
      errNoHandles                        // Keine freien Handles mehr

   };


// Konstruktor/Destruktor
// ======================

public:
   cErrBase(ERR_TYPE err)
      { ealloc(err); }
   cErrBase(ERR_TYPE err, const char *p1, const char *p2 = NULL)
      { ealloc(err); setParam(0, p1); setParam(1, p2); }
   cErrBase(ERR_TYPE err, const char *p1, const char *p2, const char *p3, const char *p4 = NULL)
      { ealloc(err); setParam(0, p1); setParam(1, p2); setParam(2, p3); setParam(3, p4); }
   cErrBase(const cErrBase& other)
      { eclone(other); }
   ~cErrBase()
      { efree(); }

   cErrBase& operator= (const cErrBase& right)
      { efree(); eclone(right); return *this; }



// Umwandlung
// ==========
// operator ERR_TYPE() - Ein Cast des Fehler-Objektes nach ERR_TYPE
//    liefert den urspruenglichen Fehlercode
//
// String() - Erzeugt die vollstaendige Fehlermeldung
//
// getCode() - liefert Fehlercode "EEEEEE" (ohne Klasse und Prefix)
// getClass() - liefert Fehlerklasse "CC" (errInfo, errWarn, errError, errFatal)
// getPrefix() - liefert Modulpraefix (oder 0)

private:
   void catMsg(char *& buf, size_t& size, const char *msg, size_t max = 0) const;
   void fmtMsg(char *& buf, size_t& size, const char *msg) const;

public:
   operator ERR_TYPE() const { return xerr ? xerr->err_code : errNoError; }
   const char *getString(char *buffer, size_t size, const char *add_text = NULL) const;

   int getClass() const    { return xerr ? (xerr->err_code & 0xC0) : errInfo; }
   int getCode() const     { return xerr ? (xerr->err_code & 0x3F)+1 : errNoError; }
   int getPrefix() const   { return xerr ? (xerr->err_code & 0xFFFFFF00) : 0; }


// Ausgabe
// =======
// operator<< - Das Fehlerobjekt kann seine Fehlermeldung auf einem Stream
//    ausgeben
//
// DbgOut() - Ausgabe der Fehlermeldung auf dem Debug-Kanal

public:
   friend __ECL_EXP1__ ostream& __ECL_EXP2__ operator<<(ostream& os, cErrBase const& err);
   void DbgOut(const char *add_text = NULL) const;


// Fehlerparameter
// ===============
// setParam() - Setzt einen optionalen Meldungsparameter. Es kann zwischen
//    verschiedenen Parametertypen gewaehlt werden.
// getParam() - Ermittelt einen Fehlerparameter in seiner textuellen Form

public:
   enum NUM_FMT { fmtDec, fmtHex };

   void setParam(int p, char ch);
   void setParam(int p, const char *txt);
   void setParam(int p, long num, NUM_FMT fmt = fmtDec);
   void setParam(int p, void *ptr);

   const char *getParam(int p) const;


// Daten
// =====
// err_code - [private] - Fehlercode
// param - Meldungsparameter

private:
   struct XERR {
      ERR_TYPE err_code;
      char *param[4];
      int refc;
   } *xerr;
   void ealloc(ERR_TYPE err);
   void eclone(const cErrBase &other);
   void efree();

};

__ECL_EXP1__ ostream& __ECL_EXP2__ operator<<(ostream& os, cErrBase const& err);


#endif

/*.EH.*/