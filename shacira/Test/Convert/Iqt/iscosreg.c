/*.SS.***********************************************************************
*
*  BESCHREIBUNG:
*
*  HISTORY:
*
*  VERSION:
*     VERSION:  1.3              AUTOR:
*     DATUM:    14.12.95         TELEFON:
*
*  BEMERKUNGEN:
* 
**.ES.**********************************************************************/

/*.SM.***********************************************************************
*
*  MODUL-NAME: ISCOSREG.CPC
*
*  BESCHREIBUNG:
*     Definition der Tabelle IscosRegTab, die alle B & R - Register
*     beschreibt, und Belegen der Tabelle mit Werten.
*     Einspritzregister fuer 1 Station, 1 Aggragat, 6 Spritzphasen
*     Die Endekennung {0xffff} muss immer da sein.
*     Block - und <> 0 - Bits wurden entfernt,ebenso die Conver-
*     tierungsroutinen.
*
*  HISTORY:
*     21.01.93 -JG-     Implementierung
*                       (Uebernahme von Common ,neu sortiert und
*                       unbenuzte Register entfernt bzw. neue Register
*                       eingefuehrt)
*     21.06.93 -MBa-    TP_RD_LSPEC eingefuehrt und XDIAGM2E ..
*                       XDIAGM36 durch IDIAGM2E .. IDIAGM36 ersetzt
*     30.08.93 -PR-     Konvertierungsfunktion fuer XSOELVW wieder
*                       wieder eingefuegt (!).
*     29.09.93 -TSchw-  Bei folgenden Kernzugsregistern wurden die
*                       Filterfunktionen entfernt (Forderung MBa):
*                       XSSFZU3:PFlt_XSSFZU3, XSFZKPT:PFlt_XSFZKPT,
*                       XSSFAU9:PFlt_XSSFAU9, XSFAKPT:PFlt_XSFAKPT,
*                       XSFASTP:PFlt_XSFASTP, XSFAKP2:PFlt_XSFAKP2,
*                       XSFZSTP:PFlt_XSFZSTP, XSFZKP2:PFlt_XSFZKP2 
*     04.11.93 -MBa-    grosse Aufraeumaktion fuer BUR
*     16.02.94 -TSchw-  Folgende Register neu eingefuegt:
*                         - Fuer Option Atmen und Praegen:
*                           IAPS_NRSTUF und IAPSSPWEG
*                         - Fuer Werkzeugschnellspannen:
*                           IWZS_SNSP, XXSNSP1 statt XRFAST1,
*                           XXSNSP2 statt XRFAST2
*                         - Fuer Kernzuege Ausschrauben:
*                           IKES_ARL    IKESTAVWO   IKESTAVSA
*                           IKESTAAAU   IKESTAVSAU  IKESSAWSA
*                           IKES_AZNS   IKES_AUESB  IKESVAUSG
*                           IKESPAUSD   IKESPAUSND  IKESVAEING
*                           IKESPAEIND  IKESPAEINND
*     18.02.94 -MBa-    XRFAST1 und XRFAST2 exisiteren wieder         
*                       XXSNSP1 und XXSNSP2 werden mit REG_RD_SPEC
*                       gelesen; XRFAST1 in IWZISACTPOS umbenannt
*                       XRFAST2 in IQTINSPSTXT umbenannt
*     22.02.94 -PR-     Register fuer Qualitaetskontrolle und
*                       Selektierweiche eingefuegt
*     22.03.94 -MBa-    Register fuer Heizungsoptimierung eingefuegt
*     21.04.94 -MBa-    Filterfunktion fuer XSNAUSW rausgeschmissen
*     07.06.94 -MBa-    XFORMMIN ist im Download
*     14-02-95 -WS-     XSOELVW ab 01.01.2 nicht mehr auf Datentr.
*     25.07.96 -HAns-   ITEXT_5 fuer Parameter-Kennungen eingefuegt.
*     26.07.96 -HAns-   define TP_RD_DINJ,TP_DSK_DL und TP_DSK_D_DL
*                       implementiert.
*     29.07.96 -HAns-   XSRSSVOR_1, XSRSVVOR_1, XSRSSNACH_1 und 
*                       XSRSVNACH_1 eingefuegt.
*                       XSNRUEK, XSSRUK1 und XSVRUK1 nicht mehr im DL 
*                       sowie SPS-Register IqtDummy angehaengt.
*     23.08.96 -HAns-   XWZGENMOD bis XWOIKGAIN fuer Seite 89.1 (KS.01.03)
*                       eingefuegt.
*                       XAWGENMOD bis XAWIKZGAIN fuer Seite 89.2 (KS.01.03)
*                       eingefuegt.
*     13-09-96 -PR-     ISCOS-Register fuer frei progr. Kernzuege 
*							   eingefuehrt (IKE...). 
*     05.11.96 -HAns-   Neue Sonderregister XIQSON30 -XIQSON68 eingefuegt.
*     06.11.96 -HAns-   rfast1 -> WZisakt und rfast2 -> IqtSPSTxt umbenannt.
*                       XRFAST1 und XRFAST2 exisiteren wieder als freie Fast-Register
*     12.11.96 -HAns-   Flt_WayToVolSoll an XSSPH11 bis XSSPH15 angefuegt.
*                       Flt_WayToVolSoll an XSSDOS1, XSSRUK1, XSSUM11, XSRSSVOR_1
*								und XSRSSNACH_1 vergeben.
*     27.11.96 -HAns-   PL1GenMod bis PLikDGest2 eingefuegt.
*                       XDIAGM37 bis XDIAGM54 eingefuegt.
*                       Nur die FG-Woerter sind ULONG     
*                       (IDIAGM2E, IDIAGM31, IDIAGM34,
*                        XDIAGM4C, XDIAGM4F, XDIAGM52)
*     28.11.96 -HAns-   XSDRGENMOD - XSDRITDAUFB eingefuegt.
*     04.12.96 -HAns-   XXSVH10 - XXSVOL1 herausgenommen, da nicht benutzt.
*                       XSSVH11 - XSSVH15 herausgenommen, da nicht benutzt.
*     06.12.96 -HAns-   XSEGPUST und XSEGPUST2 eingefuegt
*     10.12.96 -HAns-   Flt_INJ_SPEED von XSVPH11 und Flt_INJ_PRES_SOLL von
*                       XSPPH11 entfernt, da unnoetig.
*     30.12.96 -HAns-   XDOSNCARD bis XAIINAKT16 implementiert.
*     13.01.97 -HAns-   XAWGWEG, XSNGDREHM1 - XSNGDREHM2 eingefuegt.
*     15.01.97 -HAns-   IHES_BLOPT und IHES_BLOPT2 in Download aufgenommen.
*     17.01.97 -HAns-   XLVSTVERZ10 - XLVSTBLAS40 eingefuegt.
*                       XSTV1V - XSTV4B RegType Download herausgenommen und
*                       SPS-Register mit IqtDummy und Flt_Blasluft10To100 
*                       versehen.
*     24.01.97 -HAns-   Flt_DnToDvSoll an XSWPL11 und XSWPL12 angefuegt.
*     27.01.97 -HAns-   Filterfunktion fuer XSNAUSW wieder angefuegt.
*                       Filterunktion Flt_WayToVolSoll an XSRSVVOR_1 bis 
*                       XSRSVVOR_2, XSRSVNACH_1 bis XSRSNACH_2 und 
*                       XSVPH11 bis XSVPH16 eingefuegt.
*     13.02.97 -HAns-   XSPIPHYDMAX eingefuegt.
*     17.02.97 -HAns-   Flt_WayToVolSoll an XPG_YSCAL01 - XPG_YSCAL39 angefuegt.
*                       Flt_WayToVolSoll in Flt_WHToVS_Soll umbenannt, sowie
*                       Flt_HydrToSpecSoll durch Flt_WHToVS_Soll ersetzt.
*     18.02.97 -HAns-   Prozessgrafikregister fuer 4Farbmaschinen ausgelegt.
*     04.03.97 -HAns-   Filterfunktion an XXSPOL1 angehaengt.
*                       Register fuer Verknuepfung Handling mit Kern eingefuegt.
*                       XFPKZANDFHK
*     06.03.97 -HAns-   IHZ_TEMPMOD bis IHZ_KUELKAN von TP_RD_INJ nach TP_RD_SPEC
*                       geaendert.
*     11.03.97 -HAns-   IAGGRVOR2 bis IDOS4 eingefuegt.
*     20.10.97 -HAns-   XSPSCPUTYPE eingefuegt.
*     23.10.97 -HAns-   XPLGWEG1,2 und XSNG_UMDR1,2 eingefuegt.
*		10.11.97 -PR-     IKEPRGNO eingefuegt, IKEEINRICHT mit Konvertierungsfunktion
*								CStatFuncInv versehen.
*		                  IKE_NRSCHRAUB, IKE_NRWEND, IKE_SPERRMASKE eingefuehrt.								
*     20.11.97 -HAns-   DOsnCard, DOi_Akt, DIsnCard, DIi_Akt, AOinAkt01 bis 16,
*                       AOsnFor01 bis 16, AIsnCard und AIinAkt01 bis 16 heraus-
*                       genommen.
*     25.11.97 -HAns-   XDIAGMAXMOD - XDIAGMODTYP, XFDIAGDAKT bis XFDIAGA_F16
*                       aufgenommen.
*     28.11.97 -HAns-   Register der Seiten 87.1 und 87.2 herausgenommen:
*                       Iy8007soll, Iy7019soll, Iy8025soll, IY7008soll, IY8003soll
*                       Ib8007ist, I4b3ist, Iy8007ist, Ib8025ist, Iy7019ist,
*                       Iy8025ist, I5b5ist, Iy7008ist, I5b4ist, Iy8003ist
*     30.11.97 -HAns-   Folgende Register wurden neu eingefuegt:
*                       XAKT_DVAL1 - 7, XFOR_DVAL1 - 7, XAKT1AVAL01 - 16,
*                       XFOR1AVAL01 - 16, XAKT2AVAL01 - 16 und XFOR2AVAL01 - 16
*                       IAKTOUTPUT1 bis n, IAKTINPUT1 bis n und IFORCEOUTPUT1 bis n
*                       entfernt, da diese nicht mehr verwendet werden.
*     02.12.97 -HAns-   XSPSWEGMTYP (WegMess-Type) aufgenommen.
*     05.12.97 -HAns-   XDIAGMODTYP in XDIAGINDTAB geaendert.
*     08.12.97 -HAns-   Conv CaMxDb fuer XAKT2AVAL01 - 08 und XFOR2AVAL01 - 04
*                       eingefuegt.
*     16.12.97 -HAns-   ConvDMAnalog fuer freiauswaehlbare Diagnoseseite angefuegt.
*     26.01.98 -HAns-   XOPM_SPSTXT aufgenommen.                                      
*		13.04.99 -TSchw-  XPG_PRES_AREA01-04 geht nicht mehr auf Datentraeger.
*		16.04.99 -TSchw-  Prozessgraphikregister mit TP_PGDSK_DL oder
*								TP_PGDSK_D_DL markiert, damit diese Register in 
*								eine eigene Teildatei auf dem Datentraeger 
*								geschrieben werden.
*		20.04.99 -TSchw-  Bei XPG_YMAX01-04 PFlt_XPG_YMAX eingefuegt.
*		23.04.99 -TSchw-  Die Register der frei programmierbaren Kernzuege,
*								die auf Datentraeger gehen, mit TP_COREDSK_BG_DL
*								markiert, damit sie in eigenen Teildateien
*								gespeichert und separat eingelesen werden koennen
*								(siehe CORE).
*     24.01.00 -HAns-   Freiauswaehlbare Diagnoseseite: XAKT1AVAL09 - 16 Konvertierungsf.
*                       XAKT2AVAL09 und XFOR2AVAL05 Konvertierungsfunktion angefuegt.
*     02.08.00 -HAns-   XFPKZANDFHK Reg-Type von TP_STD nach TP_COREDSK_BG_DL
*                       geaendert (laut J.Helmensdorfer).
*     09.04.01 -HAns-   RegType von XZISSST (Aktuelle Schluesselschalterstellung)
*                       von TP_BG_DL nach TP_DL geaendert. (Der Wert wird in cycfast beschrieben)
*     12.04.01 -HAns-   IKBA0INPUT - IKBA3INPUT neu eingefuegt, SPS-Tasten-
*                       Register f�r neues Crashlogbuch
*     10.07.02 -HA-     Register fuer Werkzeugauswerfer und Wenden eingefuegt (XWDM_BETART bis XDTGENMOD).
*                       XOPS_NEUST, XOPSNKARTON un XOPINKARTON eingefuegt.
*     11.07.02 -HA-     Register BA_FOER und FBST fuer Seite 71.0 eingefuegt
*     12.07.02 -HA-     Register fuer Wegmessslineal Seite 49 (XSESSVOR11 bis XSEISNLPKT2) eingefuegt.
*                       XAWSPZUR fuer Seite 52.0 eingefuegt.
*                       XIQTSSACT und XSNRUK2 aufgenommen.
*                       XZHS_WASSER eingefuegt.
*                       XHXSNIF bis XHXSNPARITY eingefuegt (Seite 39.9)
*                       IOS_DIFKT1 bis IOSNDIPAR4 eingefuegt.
*                       IOINDIIST, IOINDOIST eingefuegt.
*                       Alte Airpress-Register OPxx herausgenommen.
*     15.07.02 -HA-     XAPD_TYPE, XAPD_MODE, XAPSPSYST und XAPIPSYST eingefuegt.
*                       XAPITUEB1 bis XAPITUEB4 eingefuegt.
*                       XRAMPE1_D1 bis XRAMPE5_D4 und XWKZDUES_D1  -  XWKZDUES_D4 eingefuegt.
*                       XAIR_ON bis XSPRES5_D4 eingefuegt.
*     02.10.02 -HA-     XWZA_BA_FHK bis XWZAVZUR2 eingefuegt.
*     29.10.02 -HA-     XMSKSSNDUR1,2 eingefuegt.       
*     05.11.02 -HA-     XXTKUHL eingefuegt.
*     20.11.02 -HA-     XHXINPAGEAW eingefuegt.
*     25.11.02 -HA-     XHXSNIF_2, XHXSNPROTO_2, XHXSNBAUD_2, XHXSNDATBIT_2, XHXSNSTPBIT_2,
*                       XHXSNPARITY_2 eingefuegt.
*     23.01.03 -HA-     XSn_Anfa, ssdos1a, spph11a, svph11a, stph11a, ssph11a, spph12a,
*                       svph12a, stph12a, ssph12a, spph13a, svph13a, stph13a, XSn_Anf2a,
*                       spnidra, spnidr2A fuer Produktionsstart S. 40.2 eingefuegt
*     12.03.03 -HA-     XDTS_NUM und XDTI_NUM eingefuegt.
*
*  VERSION:
*     VERSION:  1.3              AUTOR:    H.Anselm
*     DATUM:    14.12.95         TELEFON:  338
*
*  UMGEBUNG:
*     ZIELRECHNER:          Industrie-PC
*     PROGRAMMIERSPRACHE:   C
*
*  BEMERKUNGEN:
*     ACHTUNG ! ACHTUNG ! ACHTUNG ! ACHTUNG ! ACHTUNG ! ACHTUNG
*     Die Tabelle IscosRegTab muss nach Registernummern aufsteigend
*     geordnet sein. Dies ist zwingend vorgeschrieben. Ist dies nicht
*     der Fall, so fuehrt dies zu schrecklichen und unauffindbaren
*     Fehlern beim Zugriff auf die Register.
*
*****************************************************************************
*
*  FUNKTIONEN: keine
*
**.EM.**********************************************************************/


/*.SI.**********************************************************************/

#include <syntax.h>

/* #define USE_ONLY_PAGES */
#define IMPORT_DSCONV
#define IMPORT_FLTFUNC

#include <iqtdstr.h>
#include <symreg.h>
#include <symbit.h>
#include <spsdiag.h>

/*.EI.**********************************************************************/


#define PPCCOM_CHANNEL2 4

/* Abkuerzungen fuer Konstanten (TP = Type) */
#define TP_STD             REG_INT
#define TP_D               REG_DINT
#define TP_BG              REG_INT| REG_BG
#define TP_RD_FAST         REG_INT| REG_RD| REG_RD_FAST
#define TP_RD_INJ          REG_INT| REG_RD| REG_RD_INJ
#define TP_RD_SLOW         REG_INT| REG_RD| REG_RD_SLOW
#define TP_RD_SPEC         REG_INT| REG_RD| REG_RD_SPEC
#define TP_RD_DINJ         REG_DINT| REG_RD| REG_RD_INJ
#define TP_RD_LSPEC        REG_DINT| REG_RD| REG_RD_SPEC
#define TP_RD_FAST_D       REG_DINT| REG_RD| REG_RD_FAST
#define TP_DSK             REG_INT| REG_DISK_TOOL
#define TP_BG              REG_INT| REG_BG
#define TP_DL              REG_INT| REG_WR| REG_WR_DOWN
#define TP_D_DL            REG_DINT| REG_WR| REG_WR_DOWN
#define TP_BG_DL           REG_INT| REG_BG| REG_WR| REG_WR_DOWN
#define TP_DSK_BG          REG_INT| REG_DISK_TOOL| REG_BG
#define TP_DSK_BG_DL       REG_INT| REG_DISK_TOOL| REG_BG| REG_WR| REG_WR_DOWN
#define TP_DSK_BG_D_DL     REG_DINT| REG_DISK_TOOL| REG_BG| REG_WR| REG_WR_DOWN
#define TP_DSK_DL          REG_INT| REG_DISK_TOOL| REG_WR| REG_WR_DOWN
#define TP_DSK_D_DL        REG_DINT| REG_DISK_TOOL| REG_WR| REG_WR_DOWN
#define TP_PGDSK_DL        REG_INT| REG_DISK_PG| REG_WR| REG_WR_DOWN
#define TP_PGDSK_D_DL      REG_DINT| REG_DISK_PG| REG_WR| REG_WR_DOWN
#define TP_COREDSK_BG_DL   REG_INT| REG_DISK_CORE| REG_BG| REG_WR| REG_WR_DOWN


const ISCOSREG_TYPE IscosRegTab [] =
/*
 RegNr          RegType       FltFunc
 |              |             |  ConvFunc
 |              |             |  |       IscosNr
 |              |             |  |       |  IscosAdr
 |              |             |  |       |  |            BlockBit
 |              |             |  |       |  |            |  <>0-Bit
 |              |             |  |       |  |            |  |      */
{
{XXSWEG1,       TP_RD_FAST,   0, NOFUNC, 0, xsweg1,      0, 0},
{XXSWEG2,       TP_RD_FAST,   0, NOFUNC, 0, xsweg2,      0, 0},
{XXTDOS1,       TP_RD_FAST,   0, NOFUNC, 0, xtdos1,      0, 0},
{XXWDRE1,       TP_RD_FAST,   0, NOFUNC, 0, xwdre1,      0, 0},
{XXTZYKL,       TP_RD_FAST,   0, NOFUNC, 0, xtzykl,      0, 0},
{XXNSTEP,       TP_RD_FAST,   0, NOFUNC, 0, xnstep,      0, 0},
{XXNPASE,       TP_RD_FAST,   0, NOFUNC, 0, xnpase,      0, 0},
{XXFZUHK,       TP_RD_FAST,   0, NOFUNC, 0, xfzuhk, 0, 0},
{XXSNSP1,       TP_RD_SPEC,   0, NOFUNC, 0, xsnsp1,      0, 0},
{XXSNSP2,       TP_RD_SPEC,   0, NOFUNC, 0, xsnsp2,      0, 0},
{XXKOEL,        TP_RD_FAST,   0, NOFUNC, 0, xkoel,       0, 0},
{XXKPERR,       TP_RD_FAST,   0, NOFUNC, 0, xkperr,      0, 0},
{XXNMACO,       TP_RD_FAST,   0, NOFUNC, 0, xnmaco,      0, 0},
{XXNWECO,       TP_RD_FAST,   0, NOFUNC, 0, xnweco,      0, 0},
{XXSWEG4,       TP_RD_FAST,   0, NOFUNC, 0, xsweg4,      0, 0},
{XXNAHUB,       TP_RD_FAST,   0, NOFUNC, 0, xnahub,      0, 0},
{XXTNIDR,       TP_RD_FAST,   0, NOFUNC, 0, xtnidr,      0, 0},
{XXNFSS,        TP_RD_FAST,   0, NOFUNC, 0, xnfss,       0, 0},
{IWZISACTPOS,   TP_RD_FAST,   0, NOFUNC, 0, WZisakt,     0, 0},
{IQTINSPSTXT,   TP_RD_FAST,   0, NOFUNC, 0, IqtSPSTxt,   0, 0},
/*------------------------ Reserve-Register mit TP_RD_FAST ---------------- */
{XRFAST3,       TP_RD_FAST,   0, NOFUNC, 0, rfast3,      0, 0},
{XRFAST4,       TP_RD_FAST,   0, NOFUNC, 0, rfast4,      0, 0},
{XRFAST5,       TP_RD_FAST,   0, NOFUNC, 0, rfast5,      0, 0},
{XRFAST6,       TP_RD_FAST,   0, NOFUNC, 0, rfast6,      0, 0},
{XRFAST7,       TP_RD_FAST,   0, NOFUNC, 0, rfast7,      0, 0},
{XRFAST8,       TP_RD_FAST,   0, NOFUNC, 0, rfast8,      0, 0},
{XRFAST9,       TP_RD_FAST,   0, NOFUNC, 0, rfast9,      0, 0},
{XRFAST1,       TP_RD_FAST,   0, NOFUNC, 0, rfast1,      0, 0},
{XRFAST2,       TP_RD_FAST,   0, NOFUNC, 0, rfast2,      0, 0},
/* ------------------------------------------------------------------------- */
{XXPFINM,       TP_RD_INJ,    0, NOFUNC, 0, xpfinm,      0, 0},
/* ------------------------------------------------------------------------ */
{XXSPH10,       TP_RD_INJ,    0, NOFUNC, 0, xsph10,      0, 0},
{XXSPH11,       TP_RD_INJ,    0, NOFUNC, 0, xsph11,      0, 0},
{XXSPH12,       TP_RD_INJ,    0, NOFUNC, 0, xsph12,      0, 0},
{XXSPH13,       TP_RD_INJ,    0, NOFUNC, 0, xsph13,      0, 0},
{XXSPH14,       TP_RD_INJ,    0, NOFUNC, 0, xsph14,      0, 0},
{XXSPH15,       TP_RD_INJ,    0, NOFUNC, 0, xsph15,      0, 0},
{XXSPOL1,       TP_RD_INJ,    PFlt_POLSTER1, NOFUNC, 0, xspol1, 0, 0},
/* ------------------------------------------------------------------------ */
{XXTPH11,       TP_RD_INJ,    0, NOFUNC, 0, xtph11,      0, 0},
{XXTPH12,       TP_RD_INJ,    0, NOFUNC, 0, xtph12,      0, 0},
{XXTPH13,       TP_RD_INJ,    0, NOFUNC, 0, xtph13,      0, 0},
{XXTPH14,       TP_RD_INJ,    0, NOFUNC, 0, xtph14,      0, 0},
{XXTPH15,       TP_RD_INJ,    0, NOFUNC, 0, xtph15,      0, 0},
{XXTPH16,       TP_RD_INJ,    0, NOFUNC, 0, xtph16,      0, 0},
/* ------------------------------------------------------------------------ */
{XXPPH11,       TP_RD_INJ,    0, NOFUNC, 0, xpph11,      0, 0},
{XXPPH12,       TP_RD_INJ,    0, NOFUNC, 0, xpph12,      0, 0},
{XXPPH13,       TP_RD_INJ,    0, NOFUNC, 0, xpph13,      0, 0},
{XXPPH14,       TP_RD_INJ,    0, NOFUNC, 0, xpph14,      0, 0},
{XXPPH15,       TP_RD_INJ,    0, NOFUNC, 0, xpph15,      0, 0},
{XXPPH16,       TP_RD_INJ,    0, NOFUNC, 0, xpph16,      0, 0},
/* ------------------------------------------------------------------------ */
{XAX0EC,        TP_DSK_BG_DL, 0, NOFUNC, 0, Ax0ec,       0, 0},
{XAX0ED,        TP_DSK_BG_DL, 0, NOFUNC, 0, Ax0ed,       0, 0},
{XAX0EE,        TP_DSK_BG_DL, 0, NOFUNC, 0, Ax0ee,       0, 0},
{XSSFZU1,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssfzu1,      0, 0},
{XSSFZU2,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssfzu2,      0, 0},
{XSSFZU3,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssfzu3,      0, 0},
{XSFZKPT,       TP_DSK_BG_DL, 0, NOFUNC, 0, sfzkpt,      0, 0},
{XSFZSTP,       TP_DSK_BG_DL, 0, NOFUNC, 0, sfzstp,      0, 0},
{XSFZKP2,       TP_DSK_BG_DL, 0, NOFUNC, 0, sfzkp2,      0, 0},
{XSSFZU,        TP_DSK_BG_DL, 0, NOFUNC, 0, ssfzu,       0, 0},
{XSSFAU1,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssfau1,      0, 0},
{XSSFAU2,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssfau2,      0, 0},
{XSSFAU3,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssfau3,      0, 0},
{XSSFAU4,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssfau4,      0, 0},
{XSSFAU5,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssfau5,      0, 0},
{XSSFAU6,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssfau6,      0, 0},
{XSSFAU7,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssfau7,      0, 0},
{XSSFAU8,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssfau8,      0, 0},
{XSSFAU9,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssfau9,      0, 0},
{XSFAKPT,       TP_DSK_BG_DL, 0, NOFUNC, 0, sfakpt,      0, 0},
{XSFASTP,       TP_DSK_BG_DL, 0, NOFUNC, 0, sfastp,      0, 0},
{XSFAKP2,       TP_DSK_BG_DL, 0, NOFUNC, 0, sfakp2,      0, 0},
{XSSFAUF,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssfauf,      0, 0},
{XSSAUS1,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssaus1,      0, 0},
{XSSAUS2,       TP_DSK_BG_DL, PFlt_XSSAUS2, NOFUNC, 0, ssaus2, 0, 0},
{XSSAUS3,       TP_DSK_BG_DL, PFlt_XSSAUS3, NOFUNC, 0, ssaus3, 0, 0},
{XSSAUSR,       TP_STD,       0, NOFUNC, 0, ssausr,      0, 0},
{XSVZU1,        TP_DSK_BG_DL, 0, NOFUNC, 0, svzu1,       0, 0},
{XSVZU2,        TP_DSK_BG_DL, 0, NOFUNC, 0, svzu2,       0, 0},
{XSVAUF1,       TP_DSK_BG_DL, 0, NOFUNC, 0, svauf1,      0, 0},
{XSVAUF2,       TP_DSK_BG_DL, 0, NOFUNC, 0, svauf2,      0, 0},
{XSVAUF3,       TP_DSK_BG_DL, 0, NOFUNC, 0, svauf3,      0, 0},
{XSVAUS1,       TP_DSK_BG_DL, 0, NOFUNC, 0, svaus1,      0, 0},
{XSVAUS2,       TP_DSK_BG_DL, 0, NOFUNC, 0, svaus2,      0, 0},
{XSVAZUR,       TP_DSK_BG_DL, 0, NOFUNC, 0, svazur,      0, 0},
{XSPNIDR,       TP_DSK_BG_DL, 0, NOFUNC, 0, spnidr,      0, 0},
{XSFZUHK,       TP_DSK_BG_DL, PFlt_XSFZUHK, {PCsksoll, 0}, 0, sfzuhk,0, 0},
{XSPEINR,       TP_DSK_BG_DL, 0, NOFUNC, 0, speinr,      0, 0},
{XSPSPR,        TP_DSK_BG_DL, 0, {PCsksoll, 0}, 0, spspr,0, 0},
{XSPSTH1,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spsth1, 0, 0},
{XSPSTH2,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spsth2, 0, 0},
{XSFSSED,       TP_DSK_BG_DL, 0, NOFUNC, 0, sfssed,      0, 0},
/* ------------------------------------------------------------------------ */
{XSTPH11,       TP_DSK_BG_DL, 0, NOFUNC, 0, stph11,      0, 0},
{XSTPH12,       TP_DSK_BG_DL, 0, NOFUNC, 0, stph12,      0, 0},
{XSTPH13,       TP_DSK_BG_DL, 0, NOFUNC, 0, stph13,      0, 0},
{XSTPH14,       TP_DSK_BG_DL, 0, NOFUNC, 0, stph14,      0, 0},
{XSTPH15,       TP_DSK_BG_DL, 0, NOFUNC, 0, stph15,      0, 0},
{XSTPH16,       TP_DSK_BG_DL, 0, NOFUNC, 0, stph16,      0, 0},
/* ------------------------------------------------------------------------ */
{XSSPH11,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, ssph11, 0, 0},
{XSSPH12,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, ssph12, 0, 0},
{XSSPH13,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, ssph13, 0, 0},
{XSSPH14,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, ssph14, 0, 0},
{XSSPH15,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, ssph15, 0, 0},
{XSSUM11,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, ssum11, 0, 0},
{XSSDOS1,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, ssdos1, 0, 0},
{XSSRUK1,       TP_DSK_BG,    PFlt_WHToVS_Soll, NOFUNC, 0, IqtDummy,0, 0},
{XSWPL11,       TP_DSK_BG_DL, PFlt_DnToDvSoll,  NOFUNC, 0, swpl11, 0, 0},
{XSWPL12,       TP_DSK_BG_DL, PFlt_DnToDvSoll,  NOFUNC, 0, swpl12, 0, 0},
{XSPST11,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spst11, 0, 0},
{XSPST12,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spst12, 0, 0},
{XSS1DOS,       TP_DSK_BG_DL, 0, NOFUNC, 0, ss1dos,      0, 0},
{XKXEMPF,       TP_DSK_BG_DL, 0, NOFUNC, 0, kxempf,      0, 0},
{XSVRUK1,       TP_DSK_BG,    0, NOFUNC, 0, IqtDummy,    0, 0},
/* ------------------------------------------------------------------------ */
{XSVPH11,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, svph11, 0, 0},
{XSVPH12,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, svph12, 0, 0},
{XSVPH13,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, svph13, 0, 0},
{XSVPH14,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, svph14, 0, 0},
{XSVPH15,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, svph15, 0, 0},
{XSVPH16,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, svph16, 0, 0},
/* ------------------------------------------------------------------------ */
{XSPUM11,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spum11, 0, 0},
{XSPUM12,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spum12, 0, 0},
{XSPUM13,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spum13, 0, 0},
{XSPUM14,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spum14, 0, 0},
{XSPUM15,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spum15, 0, 0},
/* ------------------------------------------------------------------------ */
{XSPPH11,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spph11, 0, 0},
{XSPPH12,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spph12, 0, 0},
{XSPPH13,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spph13, 0, 0},
{XSPPH14,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spph14, 0, 0},
{XSPPH15,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spph15, 0, 0},
{XSPPH16,       TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, spph16, 0, 0},
/* ------------------------------------------------------------------------- */
{IWAS_FKT,      TP_DSK_BG_DL, 0, NOFUNC, 0, WAs_fkt,     0, 0},
{IWAS_WPVOR,    TP_DSK_BG_DL, 0, NOFUNC, 0, WAs_Wpvor,   0, 0},
{IWAS_HUBZ ,    TP_DSK_BG_DL, 0, NOFUNC, 0, WAs_Hubz,    0, 0},
{IWASTVORNE,    TP_DSK_BG_DL, 0, NOFUNC, 0, WAstVorne,   0, 0},
{IWASTVOR,      TP_DSK_BG_DL, 0, NOFUNC, 0, WAstVor,     0, 0},
{IWASTZUR,      TP_DSK_BG_DL, 0, NOFUNC, 0, WAstZur,     0, 0},
{IKE_PAUSFA,    TP_DSK_BG_DL, 0, NOFUNC, 0, KE_pAusfa ,  0, 0},
{IKE_PEINFA0,   TP_DSK_BG_DL, 0, NOFUNC, 0, KE_pEinfa0,  0, 0},
{IKE_VAUSFA0,   TP_DSK_BG_DL, 0, NOFUNC, 0, KE_vAusfa0,  0, 0},
{IKE_VAUSFA1,   TP_DSK_BG_DL, 0, NOFUNC, 0, KE_vAusfa1,  0, 0},
{IKE_VEINFA0,   TP_DSK_BG_DL, 0, NOFUNC, 0, KE_vEinfa0,  0, 0},
{ILVSNEIN0,     TP_DSK_BG_DL, 0, NOFUNC, 0, LVsnEin0,    0, 0},
{ILVSNEIN1,     TP_DSK_BG_DL, 0, NOFUNC, 0, LVsnEin1,    0, 0},
{ILVSNEIN2,     TP_DSK_BG_DL, 0, NOFUNC, 0, LVsnEin2,    0, 0},
{ILVSNEIN3,     TP_DSK_BG_DL, 0, NOFUNC, 0, LVsnEin3,    0, 0},
{XSSENTN,       TP_DSK_BG_DL, 0, NOFUNC, 0, ssentn,      0, 0},
{XSK1EIN,       TP_DSK_BG_DL, 0, NOFUNC, 0, sk1ein,      0, 0},
{XSK1AUS,       TP_DSK_BG_DL, 0, NOFUNC, 0, sk1aus,      0, 0},
{XSK2EIN,       TP_DSK_BG_DL, 0, NOFUNC, 0, sk2ein,      0, 0},
{XSK2AUS,       TP_DSK_BG_DL, 0, NOFUNC, 0, sk2aus,      0, 0},
{XSK1EIV,       TP_DSK_BG_DL, 0, NOFUNC, 0, sk1eiv,      0, 0},
{XSK1AUV,       TP_DSK_BG_DL, 0, NOFUNC, 0, sk1auv,      0, 0},
{XSK2EIV,       TP_DSK_BG_DL, 0, NOFUNC, 0, sk2eiv,      0, 0},
{XSK2AUV,       TP_DSK_BG_DL, 0, NOFUNC, 0, sk2auv,      0, 0},
{XSNK1EI,       TP_DSK_BG_DL, 0, NOFUNC, 0, snk1ei,      0, 0},
{XSNK1AU,       TP_DSK_BG_DL, 0, NOFUNC, 0, snk1au,      0, 0},
{XSNK2EI,       TP_DSK_BG_DL, 0, NOFUNC, 0, snk2ei,      0, 0},
{XSNK2AU,       TP_DSK_BG_DL, 0, NOFUNC, 0, snk2au,      0, 0},
{XSTZYKL,       TP_DSK_BG_DL, 0, NOFUNC, 0, stzykl,      0, 0},
{XSTDOS1,       TP_DSK_BG_DL, 0, NOFUNC, 0, stdos1,      0, 0},
{XSTMOTA,       TP_DSK_BG_DL, 0, NOFUNC, 0, stmota,      0, 0},
{XSTWASA,       TP_DSK_BG_DL, 0, NOFUNC, 0, stwasa,      0, 0},
{XSTVDOS,       TP_DSK_BG_DL, 0, NOFUNC, 0, stvdos,      0, 0},
{XSTINTR,       TP_DSK_BG_DL, 0, NOFUNC, 0, stintr,      0, 0},
{XSTKUHL,       TP_DSK_BG_DL, 0, NOFUNC, 0, stkuhl,      0, 0},
{XSTAGGR,       TP_DSK_BG_DL, 0, NOFUNC, 0, staggr,      0, 0},
{XSTNIDR,       TP_DSK_BG_DL, 0, NOFUNC, 0, stnidr,      0, 0},
{XSTPAUS,       TP_DSK_BG_DL, 0, NOFUNC, 0, stpaus,      0, 0},
{XSTAUS1,       TP_DSK_BG_DL, 0, NOFUNC, 0, staus1,      0, 0},
{XSTAUS2,       TP_DSK_BG_DL, 0, NOFUNC, 0, staus2,      0, 0},
{XSTV1V,        TP_DSK_BG,    PFlt_Blasluft10To100, NOFUNC, 0, IqtDummy, 0, 0},
{XSTV1B,        TP_DSK_BG,    PFlt_Blasluft10To100, NOFUNC, 0, IqtDummy, 0, 0},
{XSTV2V,        TP_DSK_BG,    PFlt_Blasluft10To100, NOFUNC, 0, IqtDummy, 0, 0},
{XSTV2B,        TP_DSK_BG,    PFlt_Blasluft10To100, NOFUNC, 0, IqtDummy, 0, 0},
{XSTV3V,        TP_DSK_BG,    PFlt_Blasluft10To100, NOFUNC, 0, IqtDummy, 0, 0},
{XSTV3B,        TP_DSK_BG,    PFlt_Blasluft10To100, NOFUNC, 0, IqtDummy, 0, 0},
{XSTV4V,        TP_DSK_BG,    PFlt_Blasluft10To100, NOFUNC, 0, IqtDummy, 0, 0},
{XSTV4B,        TP_DSK_BG,    PFlt_Blasluft10To100, NOFUNC, 0, IqtDummy, 0, 0},
{XSTK1EI,       TP_DSK_BG_DL, 0, NOFUNC, 0, stk1ei,      0, 0},
{XSTK1AU,       TP_DSK_BG_DL, 0, NOFUNC, 0, stk1au,      0, 0},
{XSTK2EI,       TP_DSK_BG_DL, 0, NOFUNC, 0, stk2ei,      0, 0},
{XSTK2AU,       TP_DSK_BG_DL, 0, NOFUNC, 0, stk2au,      0, 0},
{XSOELVW,       TP_BG_DL,     0, NOFUNC, 0, soelvw,  0, 0},
{XSNFIN,        TP_DSK_BG_DL, 0, NOFUNC, 0, snfin,       0, 0},
{XSNFETZ,       TP_BG_DL,     0, NOFUNC, 0, snfetz,      0, 0},
{XSNKERN,       TP_DSK_BG_DL, 0, NOFUNC, 0, snkern,      0, 0},
{XSNRUEK,       TP_DSK_BG,    0, NOFUNC, 0, IqtDummy,    0, 0},
{XSNPHMX,       TP_DSK_BG_DL, PFlt_XSNPHMX, NOFUNC, 0, snphmx, 0, 0},
{XSFAGGR,       TP_DSK_BG_DL, 0, NOFUNC, 0, sfaggr,      0, 0},
{XSNAGGR,       TP_DSK_BG_DL, 0, NOFUNC, 0, snaggr,      0, 0},
{XSNNIDR,       TP_DSK_BG_DL, 0, NOFUNC, 0, snnidr,      0, 0},
{XSFAUSF,       TP_DSK_BG_DL, 0, NOFUNC, 0, sfausf,      0, 0},
{XSNAUSW,       TP_DSK_BG_DL, PFlt_XSNAUSW, NOFUNC, 0, snausw, 0, 0},
{XSNRUK2,       TP_DSK_BG,    0, NOFUNC, 0, IqtDummy,    0, 0},
{XSNVWS1,       TP_DSK_BG_DL, 0, NOFUNC, 0, snvws1,      0, 0},
{XSNVWS2,       TP_DSK_BG_DL, 0, NOFUNC, 0, snvws2,      0, 0},
{XSNVWS3,       TP_DSK_BG_DL, 0, NOFUNC, 0, snvws3,      0, 0},
{XSNVWS4,       TP_DSK_BG_DL, 0, NOFUNC, 0, snvws4,      0, 0},
{XSNVWS5,       TP_DSK_BG_DL, 0, NOFUNC, 0, snvws5,      0, 0},
{XSSWP1,        TP_DSK_BG_DL, 0, NOFUNC, 0, sswp1,       0, 0},
{XSSWP2,        TP_DSK_BG_DL, 0, NOFUNC, 0, sswp2,       0, 0},
{XSSWP3,        TP_DSK_BG_DL, 0, NOFUNC, 0, sswp3,       0, 0},
{XSSWP4,        TP_DSK_BG_DL, 0, NOFUNC, 0, sswp4,       0, 0},
{XSSWP5,        TP_DSK_BG_DL, 0, NOFUNC, 0, sswp5,       0, 0},
{XSTZ1,         TP_DSK_BG_DL, 0, NOFUNC, 0, stz1,        0, 0},
{XSTZ2,         TP_DSK_BG_DL, 0, NOFUNC, 0, stz2,        0, 0},
{XSTZ3,         TP_DSK_BG_DL, 0, NOFUNC, 0, stz3,        0, 0},
{XSTZ4,         TP_DSK_BG_DL, 0, NOFUNC, 0, stz4,        0, 0},
{XSTZ5,         TP_DSK_BG_DL, 0, NOFUNC, 0, stz5,        0, 0},
{XSTDUES1,      TP_DSK_BG_DL, 0, NOFUNC, 0, stdues1,     0, 0},
{XSVAG1V,       TP_DSK_BG_DL, 0, NOFUNC, 0, svag1v,      0, 0},
{XSVAG1Z,       TP_DSK_BG_DL, 0, NOFUNC, 0, svag1z,      0, 0},
{XSAGPFO,       TP_DSK_BG_DL, 0, NOFUNC, 0, sagpfo,      0, 0},
{XZISSST,       TP_DL,        0, NOFUNC, 0, zissst,      0, 0},
{XSVK1EI,       TP_DSK_BG_DL, 0, NOFUNC, 0, svk1ei,      0, 0},
{XSPK1EI,       TP_DSK_BG_DL, 0, NOFUNC, 0, spk1ei,      0, 0},
{XSVK1AU,       TP_DSK_BG_DL, 0, NOFUNC, 0, svk1au,      0, 0},
{XSPK1AU,       TP_DSK_BG_DL, 0, NOFUNC, 0, spk1au,      0, 0},
{XSVK2EI,       TP_DSK_BG_DL, 0, NOFUNC, 0, svk2ei,      0, 0},
{XSPK2EI,       TP_DSK_BG_DL, 0, NOFUNC, 0, spk2ei,      0, 0},
{XSVK2AU,       TP_DSK_BG_DL, 0, NOFUNC, 0, svk2au,      0, 0},
{XSPK2AU,       TP_DSK_BG_DL, 0, NOFUNC, 0, spk2au,      0, 0},
{XKNUVER,       TP_STD,       0, NOFUNC, 0, knuver,      0, 0},
{XKNUTYP,       TP_STD,       0, NOFUNC, 0, knutyp,      0, 0},
/* ---------------- CPU-Type der SPS -------------------------------------- */
{XSPSCPUTYPE,   TP_RD_SPEC,   0, NOFUNC, 0, SPSCPUType,  0, 0},
/* ---------------- WegMess-Type der SPS ---------------------------------- */
{XSPSWEGMTYP,   TP_RD_SPEC,   0, NOFUNC, 0, SPSWegMTyp,  0, 0},
/* ------------------------------------------------------------------------ */
{XHXINPAGEAW,   TP_RD_SPEC,   0, NOFUNC, 0, HXinPageAW,  0, 0},
/* ---------------- Airpress ---------------------------------------------- */
{XAPITUEB1,     TP_RD_INJ,    0, NOFUNC, 0, APitUeb1,    0, 0},
{XAPITUEB2,     TP_RD_INJ,    0, NOFUNC, 0, APitUeb2,    0, 0},
{XAPITUEB3,     TP_RD_INJ,    0, NOFUNC, 0, APitUeb3,    0, 0},
{XAPITUEB4,     TP_RD_INJ,    0, NOFUNC, 0, APitUeb4,    0, 0},
/* ------------------------------------------------------------------------ */
{XZHS_WASSER,   TP_DSK_BG_DL, 0, NOFUNC, 0, ZHs_Wasser,  0, 0},
/* ------------------------------------------------------------------------ */
{XMSKSSNDUR1,   TP_DL,        0, NOFUNC, 0, MSksSnDur1, 0, 0},
{XMSKSSNDUR2,   TP_DL,        0, NOFUNC, 0, MSksSnDur2, 0, 0},
/*------------------------ nachtraeglich definierte Register -------------- */
{XXSWEG4_SHOW,  TP_RD_FAST,   0, NOFUNC, 0, xsweg4,      0, 0},
/*------------------------ Zusaetzlich Reserveregister -------------------- */
{XKEINSI,       TP_DSK_BG_DL, 0, NOFUNC, 0, keinsi,      0, 0},
{XIQSON0,       TP_STD,       0, NOFUNC, 0, iqson0,      0, 0},
{XIQSON1,       TP_STD,       0, NOFUNC, 0, iqson1,      0, 0},
{XIQSON2,       TP_STD,       0, NOFUNC, 0, iqson2,      0, 0},
{XIQSON3,       TP_STD,       0, NOFUNC, 0, iqson3,      0, 0},
{XIQSON4,       TP_STD,       0, NOFUNC, 0, iqson4,      0, 0},
{XIQSON5,       TP_STD,       0, NOFUNC, 0, iqson5,      0, 0},
{XIQSON6,       TP_STD,       0, NOFUNC, 0, iqson6,      0, 0},
{XIQSON7,       TP_STD,       0, NOFUNC, 0, iqson7,      0, 0},
{XIQSON8,       TP_STD,       0, NOFUNC, 0, iqson8,      0, 0},
{XIQSON9,       TP_STD,       0, NOFUNC, 0, iqson9,      0, 0},
{XIQSONA,       TP_STD,       0, NOFUNC, 0, iqsona,      0, 0},
{XIQSONB,       TP_STD,       0, NOFUNC, 0, iqsonb,      0, 0},
{XIQSONC,       TP_STD,       0, NOFUNC, 0, iqsonc,      0, 0},
{XIQSOND,       TP_STD,       0, NOFUNC, 0, iqsond,      0, 0},
{XIQSONE,       TP_STD,       0, NOFUNC, 0, iqsone,      0, 0},
{XIQSONF,       TP_STD,       0, NOFUNC, 0, iqsonf,      0, 0},
{XIQSON10,      TP_STD,       0, NOFUNC, 0, iqson10,     0, 0},
{XIQSON11,      TP_STD,       0, NOFUNC, 0, iqson11,     0, 0},
{XIQSON12,      TP_STD,       0, NOFUNC, 0, iqson12,     0, 0},
{XIQSON13,      TP_STD,       0, NOFUNC, 0, iqson13,     0, 0},
{XIQSON14,      TP_STD,       0, NOFUNC, 0, iqson14,     0, 0},
{XIQSON15,      TP_STD,       0, NOFUNC, 0, iqson15,     0, 0},
{XIQSON16,      TP_STD,       0, NOFUNC, 0, iqson16,     0, 0},
{XIQSON17,      TP_STD,       0, NOFUNC, 0, iqson17,     0, 0},
{XIQSON18,      TP_STD,       0, NOFUNC, 0, iqson18,     0, 0},
{XIQSON19,      TP_STD,       0, NOFUNC, 0, iqson19,     0, 0},
{XIQSON1A,      TP_STD,       0, NOFUNC, 0, iqson1a,     0, 0},
{XIQSON1B,      TP_STD,       0, NOFUNC, 0, iqson1b,     0, 0},
{XIQSON1C,      TP_STD,       0, NOFUNC, 0, iqson1c,     0, 0},
{XIQSON1D,      TP_STD,       0, NOFUNC, 0, iqson1d,     0, 0},
{XIQSON1E,      TP_STD,       0, NOFUNC, 0, iqson1e,     0, 0},
{XIQSON1F,      TP_STD,       0, NOFUNC, 0, iqson1f,     0, 0},
{XIQSON20,      TP_STD,       0, NOFUNC, 0, iqson20,     0, 0},
{XIQSON21,      TP_STD,       0, NOFUNC, 0, iqson21,     0, 0},
{XIQSON22,      TP_STD,       0, NOFUNC, 0, iqson22,     0, 0},
{XIQSON23,      TP_STD,       0, NOFUNC, 0, iqson23,     0, 0},
{XIQSON24,      TP_STD,       0, NOFUNC, 0, iqson24,     0, 0},
{XIQSON25,      TP_STD,       0, NOFUNC, 0, iqson25,     0, 0},
{XIQSON26,      TP_STD,       0, NOFUNC, 0, iqson26,     0, 0},
{XIQSON27,      TP_STD,       0, NOFUNC, 0, iqson27,     0, 0},
{XIQSON28,      TP_STD,       0, NOFUNC, 0, iqson28,     0, 0},
{XIQSON29,      TP_STD,       0, NOFUNC, 0, iqson29,     0, 0},
{XIQSON2A,      TP_STD,       0, NOFUNC, 0, iqson2a,     0, 0},
{XIQSON2B,      TP_STD,       0, NOFUNC, 0, iqson2b,     0, 0},
{XIQSON2C,      TP_STD,       0, NOFUNC, 0, iqson2c,     0, 0},
{XIQSON2D,      TP_STD,       0, NOFUNC, 0, iqson2d,     0, 0},
{XIQSON2E,      TP_STD,       0, NOFUNC, 0, iqson2e,     0, 0},
{XIQSON2F,      TP_STD,       0, NOFUNC, 0, iqson2f,     0, 0},
/*------------------------ Reserve-Register mit TP_RD_INJ ----------------- */
{XRINJ1,        TP_RD_INJ,    0, NOFUNC, 0, rinj1,       0, 0},
{XRINJ2,        TP_RD_INJ,    0, NOFUNC, 0, rinj2,       0, 0},
{XRINJ3,        TP_RD_INJ,    0, NOFUNC, 0, rinj3,       0, 0},
{XRINJ4,        TP_RD_INJ,    0, NOFUNC, 0, rinj4,       0, 0},
{XRINJ5,        TP_RD_INJ,    0, NOFUNC, 0, rinj5,       0, 0},
{XRINJ6,        TP_RD_INJ,    0, NOFUNC, 0, rinj6,       0, 0},
{XRINJ7,        TP_RD_INJ,    0, NOFUNC, 0, rinj7,       0, 0},
{XRINJ8,        TP_RD_INJ,    0, NOFUNC, 0, rinj8,       0, 0},
/*------------------------ Register fuer die Diagnoseseiten --------------- */
/*------------------------ Register fuer die Diagnoseseite 87.0 ----------- */
{XDIAGM1,       TP_RD_SPEC,   0, NOFUNC, 0, diagm1,      0, 0},
{XDIAGM2,       TP_RD_SPEC,   0, NOFUNC, 0, diagm2,      0, 0},
{XDIAGM3,       TP_RD_SPEC,   0, NOFUNC, 0, diagm3,      0, 0},
{XDIAGM4,       TP_RD_SPEC,   0, NOFUNC, 0, diagm4,      0, 0},
{XDIAGM5,       TP_RD_SPEC,   0, NOFUNC, 0, diagm5,      0, 0},
{XDIAGM6,       TP_RD_SPEC,   0, NOFUNC, 0, diagm6,      0, 0},
{XDIAGM7,       TP_RD_SPEC,   0, NOFUNC, 0, diagm7,      0, 0},
{XDIAGM8,       TP_RD_SPEC,   0, NOFUNC, 0, diagm8,      0, 0},
{XDIAGM9,       TP_RD_SPEC,   0, NOFUNC, 0, diagm9,      0, 0},
{XDIAGMA,       TP_RD_SPEC,   0, NOFUNC, 0, diagma,      0, 0},
{XDIAGMB,       TP_RD_SPEC,   0, NOFUNC, 0, diagmb,      0, 0},
{XDIAGMC,       TP_RD_SPEC,   0, NOFUNC, 0, diagmc,      0, 0},
{XDIAGMD,       TP_RD_SPEC,   0, NOFUNC, 0, diagmd,      0, 0},
{XDIAGME,       TP_RD_SPEC,   0, NOFUNC, 0, diagme,      0, 0},
{XDIAGMF,       TP_RD_SPEC,   0, NOFUNC, 0, diagmf,      0, 0},
{XDIAGM10,      TP_RD_SPEC,   0, NOFUNC, 0, diagm10,     0, 0},
{XDIAGM11,      TP_RD_SPEC,   0, NOFUNC, 0, diagm11,     0, 0},
{XDIAGM12,      TP_RD_SPEC,   0, NOFUNC, 0, diagm12,     0, 0},
{XDIAGM13,      TP_RD_SPEC,   0, NOFUNC, 0, diagm13,     0, 0},
{XDIAGM14,      TP_RD_SPEC,   0, NOFUNC, 0, diagm14,     0, 0},
{XDIAGM15,      TP_RD_SPEC,   0, NOFUNC, 0, diagm15,     0, 0},
{XDIAGM16,      TP_RD_SPEC,   0, NOFUNC, 0, diagm16,     0, 0},
{XDIAGM17,      TP_RD_SPEC,   0, NOFUNC, 0, diagm17,     0, 0},
{XDIAGM18,      TP_RD_SPEC,   0, NOFUNC, 0, diagm18,     0, 0},
{XDIAGM19,      TP_RD_SPEC,   0, NOFUNC, 0, diagm19,     0, 0},
{XDIAGM1A,      TP_RD_SPEC,   0, NOFUNC, 0, diagm1a,     0, 0},
{XDIAGM1B,      TP_RD_SPEC,   0, NOFUNC, 0, diagm1b,     0, 0},
{XDIAGM1C,      TP_RD_SPEC,   0, NOFUNC, 0, diagm1c,     0, 0},
{XDIAGM1D,      TP_RD_SPEC,   0, NOFUNC, 0, diagm1d,     0, 0},
{XDIAGM1E,      TP_RD_SPEC,   0, NOFUNC, 0, diagm1e,     0, 0},
{XDIAGM1F,      TP_RD_SPEC,   0, NOFUNC, 0, diagm1f,     0, 0},
{XDIAGM20,      TP_RD_SPEC,   0, NOFUNC, 0, diagm20,     0, 0},
{XDIAGM21,      TP_RD_SPEC,   0, NOFUNC, 0, diagm21,     0, 0},
{XDIAGM22,      TP_RD_SPEC,   0, NOFUNC, 0, diagm22,     0, 0},
{XDIAGM23,      TP_RD_SPEC,   0, NOFUNC, 0, diagm23,     0, 0},
{XDIAGM24,      TP_RD_SPEC,   0, NOFUNC, 0, diagm24,     0, 0},
{XDIAGM25,      TP_RD_SPEC,   0, NOFUNC, 0, diagm25,     0, 0},
{XDIAGM26,      TP_RD_SPEC,   0, NOFUNC, 0, diagm26,     0, 0},
{XDIAGM27,      TP_RD_SPEC,   0, NOFUNC, 0, diagm27,     0, 0},
{XDIAGM28,      TP_RD_SPEC,   0, NOFUNC, 0, diagm28,     0, 0},
{XDIAGM29,      TP_RD_SPEC,   0, NOFUNC, 0, diagm29,     0, 0},
{XDIAGM2A,      TP_RD_SPEC,   0, NOFUNC, 0, diagm2a,     0, 0},
{XDIAGM2B,      TP_RD_SPEC,   0, NOFUNC, 0, diagm2b,     0, 0},
{XDIAGM2C,      TP_RD_SPEC,   0, NOFUNC, 0, diagm2c,     0, 0},
{XDIAGM2D,      TP_RD_SPEC,   0, NOFUNC, 0, diagm2d,     0, 0},
{IDIAGM2E,      TP_RD_LSPEC,  0, NOFUNC, 0, diagm2e,     0, 0}, /* ULONG */ 
{IDIAGM2F,      TP_RD_SPEC,   0, NOFUNC, 0, diagm2f,     0, 0},
{IDIAGM30,      TP_RD_SPEC,   0, NOFUNC, 0, diagm30,     0, 0},
{IDIAGM31,      TP_RD_LSPEC,  0, NOFUNC, 0, diagm31,     0, 0}, /* ULONG */ 
{IDIAGM32,      TP_RD_SPEC,   0, NOFUNC, 0, diagm32,     0, 0},
{IDIAGM33,      TP_RD_SPEC,   0, NOFUNC, 0, diagm33,     0, 0},
{IDIAGM34,      TP_RD_LSPEC,  0, NOFUNC, 0, diagm34,     0, 0}, /* ULONG */ 
{IDIAGM35,      TP_RD_SPEC,   0, NOFUNC, 0, diagm35,     0, 0},
{IDIAGM36,      TP_RD_SPEC,   0, NOFUNC, 0, diagm36,     0, 0},
/*------------------------ Register fuer die Diagnoseseite 87.0 Agg. 2 ---- */
{XDIAGM37,      TP_RD_SPEC,   0, NOFUNC, 0, diagm37,     0, 0},
{XDIAGM38,      TP_RD_SPEC,   0, NOFUNC, 0, diagm38,     0, 0},
{XDIAGM39,      TP_RD_SPEC,   0, NOFUNC, 0, diagm39,     0, 0},
{XDIAGM3A,      TP_RD_SPEC,   0, NOFUNC, 0, diagm3a,     0, 0},
{XDIAGM3B,      TP_RD_SPEC,   0, NOFUNC, 0, diagm3b,     0, 0},
{XDIAGM3C,      TP_RD_SPEC,   0, NOFUNC, 0, diagm3c,     0, 0},
{XDIAGM3D,      TP_RD_SPEC,   0, NOFUNC, 0, diagm3d,     0, 0},
{XDIAGM3E,      TP_RD_SPEC,   0, NOFUNC, 0, diagm3e,     0, 0},
{XDIAGM3F,      TP_RD_SPEC,   0, NOFUNC, 0, diagm3f,     0, 0},
{XDIAGM40,      TP_RD_SPEC,   0, NOFUNC, 0, diagm40,     0, 0},
{XDIAGM41,      TP_RD_SPEC,   0, NOFUNC, 0, diagm41,     0, 0},
{XDIAGM42,      TP_RD_SPEC,   0, NOFUNC, 0, diagm42,     0, 0},
{XDIAGM43,      TP_RD_SPEC,   0, NOFUNC, 0, diagm43,     0, 0},
{XDIAGM44,      TP_RD_SPEC,   0, NOFUNC, 0, diagm44,     0, 0},
{XDIAGM45,      TP_RD_SPEC,   0, NOFUNC, 0, diagm45,     0, 0},
{XDIAGM46,      TP_RD_SPEC,   0, NOFUNC, 0, diagm46,     0, 0},
{XDIAGM47,      TP_RD_SPEC,   0, NOFUNC, 0, diagm47,     0, 0},
{XDIAGM48,      TP_RD_SPEC,   0, NOFUNC, 0, diagm48,     0, 0},
{XDIAGM49,      TP_RD_SPEC,   0, NOFUNC, 0, diagm49,     0, 0},
{XDIAGM4A,      TP_RD_SPEC,   0, NOFUNC, 0, diagm4a,     0, 0},
{XDIAGM4B,      TP_RD_SPEC,   0, NOFUNC, 0, diagm4b,     0, 0},
{XDIAGM4C,      TP_RD_LSPEC,  0, NOFUNC, 0, diagm4c,     0, 0}, /* ULONG */ 
{XDIAGM4D,      TP_RD_SPEC,   0, NOFUNC, 0, diagm4d,     0, 0},
{XDIAGM4E,      TP_RD_SPEC,   0, NOFUNC, 0, diagm4e,     0, 0},
{XDIAGM4F,      TP_RD_LSPEC,  0, NOFUNC, 0, diagm4f,     0, 0}, /* ULONG */ 
{XDIAGM50,      TP_RD_SPEC,   0, NOFUNC, 0, diagm50,     0, 0},
{XDIAGM51,      TP_RD_SPEC,   0, NOFUNC, 0, diagm51,     0, 0},
{XDIAGM52,      TP_RD_LSPEC,  0, NOFUNC, 0, diagm52,     0, 0}, /* ULONG */ 
{XDIAGM53,      TP_RD_SPEC,   0, NOFUNC, 0, diagm53,     0, 0},
{XDIAGM54,      TP_RD_SPEC,   0, NOFUNC, 0, diagm54,     0, 0},
/* ----------------------- Seite 17.2 ------------------------------------- */
{XDIAGM15A,     TP_RD_SPEC,   0, NOFUNC, 0, diagm15a,    0, 0},
{XDIAGM15B,     TP_RD_SPEC,   0, NOFUNC, 0, diagm15b,    0, 0},
{XDIAGM15C,     TP_RD_SPEC,   0, NOFUNC, 0, diagm15c,    0, 0},
{XDIAGM15D,     TP_RD_SPEC,   0, NOFUNC, 0, diagm15d,    0, 0},
{XDIAGM15E,     TP_RD_SPEC,   0, NOFUNC, 0, diagm15e,    0, 0},
{XDIAGM15F,     TP_RD_SPEC,   0, NOFUNC, 0, diagm15f,    0, 0},
{XDIAGM160,     TP_RD_SPEC,   0, NOFUNC, 0, diagm160,    0, 0},
{XDIAGM161,     TP_RD_SPEC,   0, NOFUNC, 0, diagm161,    0, 0},
{XDIAGM162,     TP_RD_SPEC,   0, NOFUNC, 0, diagm162,    0, 0},
{XDIAGM163,     TP_RD_SPEC,   0, NOFUNC, 0, diagm163,    0, 0},
{XDIAGM164,     TP_RD_SPEC,   0, NOFUNC, 0, diagm164,    0, 0},
{XDIAGM165,     TP_RD_SPEC,   0, NOFUNC, 0, diagm165,    0, 0},
{XDIAGM166,     TP_RD_SPEC,   0, NOFUNC, 0, diagm166,    0, 0},
{XDIAGM16B,     TP_RD_SPEC,   0, NOFUNC, 0, diagm16b,    0, 0},
/* ------------------------------------------------------------------------ */
{XFORMACT,      TP_RD_SPEC,   0, NOFUNC, 0, formact,     0, 0},
/* ---------------- neue zusaetzliche Sonderregister ---------------------- */
{XIQSON30,      TP_STD,       0, NOFUNC, 0, iqson30,     0, 0},
{XIQSON31,      TP_STD,       0, NOFUNC, 0, iqson31,     0, 0},
{XIQSON32,      TP_STD,       0, NOFUNC, 0, iqson32,     0, 0},
{XIQSON33,      TP_STD,       0, NOFUNC, 0, iqson33,     0, 0},
{XIQSON34,      TP_STD,       0, NOFUNC, 0, iqson34,     0, 0},
{XIQSON35,      TP_STD,       0, NOFUNC, 0, iqson35,     0, 0},
{XIQSON36,      TP_STD,       0, NOFUNC, 0, iqson36,     0, 0},
{XIQSON37,      TP_STD,       0, NOFUNC, 0, iqson37,     0, 0},
{XIQSON38,      TP_STD,       0, NOFUNC, 0, iqson38,     0, 0},
{XIQSON39,      TP_STD,       0, NOFUNC, 0, iqson39,     0, 0},
{XIQSON3A,      TP_STD,       0, NOFUNC, 0, iqson3a,     0, 0},
{XIQSON3B,      TP_STD,       0, NOFUNC, 0, iqson3b,     0, 0},
{XIQSON3C,      TP_STD,       0, NOFUNC, 0, iqson3c,     0, 0},
{XIQSON3D,      TP_STD,       0, NOFUNC, 0, iqson3d,     0, 0},
{XIQSON3E,      TP_STD,       0, NOFUNC, 0, iqson3e,     0, 0},
{XIQSON3F,      TP_STD,       0, NOFUNC, 0, iqson3f,     0, 0},
{XIQSON40,      TP_STD,       0, NOFUNC, 0, iqson40,     0, 0},
{XIQSON41,      TP_STD,       0, NOFUNC, 0, iqson41,     0, 0},
{XIQSON42,      TP_STD,       0, NOFUNC, 0, iqson42,     0, 0},
{XIQSON43,      TP_STD,       0, NOFUNC, 0, iqson43,     0, 0},
{XIQSON44,      TP_STD,       0, NOFUNC, 0, iqson44,     0, 0},
{XIQSON45,      TP_STD,       0, NOFUNC, 0, iqson45,     0, 0},
{XIQSON46,      TP_STD,       0, NOFUNC, 0, iqson46,     0, 0},
{XIQSON47,      TP_STD,       0, NOFUNC, 0, iqson47,     0, 0},
{XIQSON48,      TP_STD,       0, NOFUNC, 0, iqson48,     0, 0},
{XIQSON49,      TP_STD,       0, NOFUNC, 0, iqson49,     0, 0},
{XIQSON4A,      TP_STD,       0, NOFUNC, 0, iqson4a,     0, 0},
{XIQSON4B,      TP_STD,       0, NOFUNC, 0, iqson4b,     0, 0},
{XIQSON4C,      TP_STD,       0, NOFUNC, 0, iqson4c,     0, 0},
{XIQSON4D,      TP_STD,       0, NOFUNC, 0, iqson4d,     0, 0},
{XIQSON4E,      TP_STD,       0, NOFUNC, 0, iqson4e,     0, 0},
{XIQSON4F,      TP_STD,       0, NOFUNC, 0, iqson4f,     0, 0},
{XIQSON50,      TP_STD,       0, NOFUNC, 0, iqson50,     0, 0},
{XIQSON51,      TP_STD,       0, NOFUNC, 0, iqson51,     0, 0},
{XIQSON52,      TP_STD,       0, NOFUNC, 0, iqson52,     0, 0},
{XIQSON53,      TP_STD,       0, NOFUNC, 0, iqson53,     0, 0},
{XIQSON54,      TP_STD,       0, NOFUNC, 0, iqson54,     0, 0},
{XIQSON55,      TP_STD,       0, NOFUNC, 0, iqson55,     0, 0},
{XIQSON56,      TP_STD,       0, NOFUNC, 0, iqson56,     0, 0},
{XIQSON57,      TP_STD,       0, NOFUNC, 0, iqson57,     0, 0},
{XIQSON58,      TP_STD,       0, NOFUNC, 0, iqson58,     0, 0},
{XIQSON59,      TP_STD,       0, NOFUNC, 0, iqson59,     0, 0},
{XIQSON5A,      TP_STD,       0, NOFUNC, 0, iqson5a,     0, 0},
{XIQSON5B,      TP_STD,       0, NOFUNC, 0, iqson5b,     0, 0},
{XIQSON5C,      TP_STD,       0, NOFUNC, 0, iqson5c,     0, 0},
{XIQSON5D,      TP_STD,       0, NOFUNC, 0, iqson5d,     0, 0},
{XIQSON5E,      TP_STD,       0, NOFUNC, 0, iqson5e,     0, 0},
{XIQSON5F,      TP_STD,       0, NOFUNC, 0, iqson5f,     0, 0},
{XIQSON60,      TP_STD,       0, NOFUNC, 0, iqson60,     0, 0},
{XIQSON61,      TP_STD,       0, NOFUNC, 0, iqson61,     0, 0},
{XIQSON62,      TP_STD,       0, NOFUNC, 0, iqson62,     0, 0},
{XIQSON63,      TP_STD,       0, NOFUNC, 0, iqson63,     0, 0},
{XIQSON64,      TP_STD,       0, NOFUNC, 0, iqson64,     0, 0},
{XIQSON65,      TP_STD,       0, NOFUNC, 0, iqson65,     0, 0},
{XIQSON66,      TP_STD,       0, NOFUNC, 0, iqson66,     0, 0},
{XIQSON67,      TP_STD,       0, NOFUNC, 0, iqson67,     0, 0},
{XIQSON68,      TP_STD,       0, NOFUNC, 0, iqson68,     0, 0},
/*------------------------ Zusaetzlich def. Schummelregister -------------- */
{XXNAHUB_SOLL,  TP_STD,       0, NOFUNC, 0, xnahub,      0, 0},
/* ---------------- Airpress-Register ------------------------------------- */
{XAPD_TYPE,     TP_DSK_BG_DL, 0, NOFUNC, 0, APd_Type,    0, 0},
{XAPD_MODE,     TP_DSK_BG_DL, 0, NOFUNC, 0, APd_Mode,    0, 0},
{XAPSPSYST,     TP_DSK_BG_DL, 0, NOFUNC, 0, APspSysT,    0, 0},
{XAPIPSYST,     TP_RD_FAST,   0, NOFUNC, 0, APipSysT,    0, 0},
/* ------------------------------------------------------------------------ */
{XOPM_SPSTXT,   TP_RD_FAST,   0, NOFUNC, 0, OPm_SPSTxt,  0, 0},
/* ------------------------------------------------------------------------ */
{XHZIT_VERZ1,   TP_RD_SPEC,   0, NOFUNC, 0, HZit_Verz1,  0, 0},
{XHZIT_VERZ2,   TP_RD_SPEC,   0, NOFUNC, 0, HZit_Verz2,  0, 0},
{XXTKUHL,       TP_RD_FAST,   0, NOFUNC, 0, xtkuhl,      0, 0},
/* ----------------------- Kartonzaehler ---------------------------------- */
{XOPS_NEUST,    TP_STD,       0, NOFUNC, 0, OPs_Neust,   0, 0},
{XOPSNKARTON,   TP_DSK_BG_DL, 0, NOFUNC, 0, OPsnKarton,  0, 0},
{XOPINKARTON,   TP_RD_FAST,   0, NOFUNC, 0, OPinKarton,  0, 0},
/* ------------------------------------------------------------------------ */
{XTABSWKZ,      TP_DSK_BG_DL, 0, NOFUNC, 0, tabswkz,     0, 0},
{XTABSZYL1,     TP_DSK_BG_DL, 0, NOFUNC, 0, tabszyl1,    0, 0},
{XTABSZYL2,     TP_DSK_BG_DL, 0, NOFUNC, 0, tabszyl2,    0, 0},
{XFORMMIN,      TP_DL,        0, NOFUNC, 0, formmin,     0, 0},
{IROSNPROGRAMM, TP_DSK_BG_DL, 0, NOFUNC, 0, ROsnProgr,   0, 0}, 
{IROS_ABLAGE,   TP_DSK_BG_DL, 0, NOFUNC, 0, ROs_Ablag,   0, 0},  
{IROSTYSGM,     TP_DSK_BG_DL, 0, NOFUNC, 0, ROstYSgm,    0, 0},  
{IROSTXVOR,     TP_DSK_BG_DL, 0, NOFUNC, 0, ROstXvor,    0, 0},  
{IROSTAUSVOR,   TP_DSK_BG_DL, 0, NOFUNC, 0, ROstAwVor,   0, 0},  
{IROSTGRFEIN,   TP_DSK_BG_DL, 0, NOFUNC, 0, ROstGrEin,   0, 0},  
{IROSTGRFAUS,   TP_DSK_BG_DL, 0, NOFUNC, 0, ROstGrAus,   0, 0},  
{IROSTAUSZUR,   TP_DSK_BG_DL, 0, NOFUNC, 0, ROstAwZur,   0, 0},  
{IROSTXZUR,     TP_DSK_BG_DL, 0, NOFUNC, 0, ROstXzur,    0, 0},  
{IROSTB_C,      TP_DSK_BG_DL, 0, NOFUNC, 0, ROstB_C,     0, 0},  
{IROSTYABL,     TP_DSK_BG_DL, 0, NOFUNC, 0, ROstYAbl,    0, 0},  
{IROSTFORMZU,   TP_DSK_BG_DL, 0, NOFUNC, 0, ROstFormZu,  0, 0},  
{IROSTBANDTAKT, TP_DSK_BG_DL, 0, NOFUNC, 0, ROstBTakt,   0, 0}, 
{IROSTABBLASEN, TP_DSK_BG_DL, 0, NOFUNC, 0, ROstABlas,   0, 0},  
{IROSTAUSBIS,   TP_DSK_BG_DL, 0, NOFUNC, 0, ROstAusbis,  0, 0}, 
{IROSTZUEBW,    TP_DSK_BG_DL, 0, NOFUNC, 0, ROstZuebw,   0, 0}, 
{IROSNSONDABL,  TP_DSK_BG_DL, 0, NOFUNC, 0, ROsnSoAbl,   0, 0},
{IA0INPUT,      TP_RD_SPEC,   0, NOFUNC, 0, A0Input,     0, 0},
{IA1INPUT,      TP_RD_SPEC,   0, NOFUNC, 0, A1Input,     0, 0}, 
{IA2INPUT,      TP_RD_SPEC,   0, NOFUNC, 0, A2Input,     0, 0}, 
{IA3INPUT,      TP_RD_SPEC,   0, NOFUNC, 0, A3Input,     0, 0}, 
/*------------------------ 3. Stufe fuer Wkz schliesen Seite 50 ----------- */
{ISESSFZU2,     TP_DSK_BG_DL, 0, NOFUNC, 0, SEssFzu2,    0, 0},
{ISESVFZU3,     TP_DSK_BG_DL, 0, NOFUNC, 0, SEsvFzu3,    0, 0},
/* ----------------------- Seite 17.1 Zeitanalyse ------------------------- */
{IWKZSCHL,      TP_RD_INJ,    0, NOFUNC, 0, Iwkzschl,    0, 0},
{IWKZSICH,      TP_RD_INJ,    0, NOFUNC, 0, Iwkzsich,    0, 0},
{ISCHLDRAUFB,   TP_RD_INJ,    0, NOFUNC, 0, Ischldraufb, 0, 0},
{IAGGRVOR,      TP_RD_INJ,    0, NOFUNC, 0, Iaggrvor,    0, 0},
{IEINSPR,       TP_RD_INJ,    0, NOFUNC, 0, Ieinspr,     0, 0},
{IDOS,          TP_RD_INJ,    0, NOFUNC, 0, Idos,        0, 0},
{IKUEHL,        TP_RD_INJ,    0, NOFUNC, 0, Ikuehl, 0, 0},
{IWKZOEFFN,     TP_RD_INJ,    0, NOFUNC, 0, Iwkzoeffn,   0, 0},
{IAUSWVOR,      TP_RD_INJ,    0, NOFUNC, 0, Iauswvor,    0, 0},
{IAUSWZUR,      TP_RD_INJ,    0, NOFUNC, 0, Iauswzur,    0, 0},
{IPAUSZEIT,     TP_RD_INJ,    0, NOFUNC, 0, Ipauszeit, 0, 0},
{IZYKZEIT,      TP_RD_DINJ,   0, NOFUNC, 0, Izykzeit,    0, 0}, /* ULONG */
/* ----------------------- Seite 89.0 Zeitanalyse ------------------------- */
{IMSSSK11,      TP_D,         0, NOFUNC, 0, IMSssK11,    0, 0}, /* ULONG */
{IMSSSOFF1,     TP_STD,       0, NOFUNC, 0, IMSssOff1,   0, 0},
{IMSSSK12,      TP_D,         0, NOFUNC, 0, IMSssK12,    0, 0}, /* ULONG */ 
{IMSSSOFF2,     TP_STD,       0, NOFUNC, 0, IMSssOff2,   0, 0},
{IMSSSK13,      TP_D,         0, NOFUNC, 0, IMSssK13,    0, 0}, /* ULONG */ 
{IMSSSOFF3,     TP_STD,       0, NOFUNC, 0, IMSssOff3,   0, 0},
{IMSSSK14,      TP_D,         0, NOFUNC, 0, IMSssK14,    0, 0}, /* ULONG */ 
{IMSSSOFF4,     TP_STD,       0, NOFUNC, 0, IMSssOff4,   0, 0},
{IMSISK11,      TP_RD_LSPEC,  0, NOFUNC, 0, IMSisK11,    0, 0}, /* ULONG */ 
{IMSISOFF1,     TP_RD_SPEC,   0, NOFUNC, 0, IMSisOff1,   0, 0},
{IMSISK12,      TP_RD_LSPEC,  0, NOFUNC, 0, IMSisK12,    0, 0}, /* ULONG */ 
{IMSISOFF2,     TP_RD_SPEC,   0, NOFUNC, 0, IMSisOff2,   0, 0},
{IMSISK13,      TP_RD_LSPEC,  0, NOFUNC, 0, IMSisK13,    0, 0}, /* ULONG */ 
{IMSISOFF3,     TP_RD_SPEC,   0, NOFUNC, 0, IMSisOff3,   0, 0},
{IMSISK14,      TP_RD_LSPEC,  0, NOFUNC, 0, IMSisK14,    0, 0}, /* ULONG */ 
{IMSISOFF4,     TP_RD_SPEC,   0, NOFUNC, 0, IMSisOff4,   0, 0},
{IMSISAKT1,     TP_RD_SPEC,   0, NOFUNC, 0, IMSisAkt1,   0, 0},
{IMSISAKT2,     TP_RD_SPEC,   0, NOFUNC, 0, IMSisAkt2,   0, 0},
{IMSISAKT3,     TP_RD_SPEC,   0, NOFUNC, 0, IMSisAkt3,   0, 0},
{IMSISAKT4,     TP_RD_SPEC,   0, NOFUNC, 0, IMSisAkt4,   0, 0},
{IMSINAKT,      TP_RD_SPEC,   0, NOFUNC, 0, IMSinAkt,    0, 0},
{IMSINSTAT,     TP_RD_SPEC,   0, NOFUNC, 0, IMSinStat,   0, 0},
{IDIAGOUT,      TP_STD,       0, NOFUNC, 0, IDiagOut,    0, 0},
{IGENMOD,       TP_STD,       0, NOFUNC, 0, IGenMod,     0, 0},
{ISSCMD,        TP_STD,       0, NOFUNC, 0, SSCmd,       0, 0},
/* ------------------------------------------------------------------------ */
{IAPS_WAHL,     TP_DSK_BG_DL, 0, NOFUNC, 0, APs_Wahl,    0, 0},
{IAPS_STUFEN,   TP_DSK_BG_DL, 0, NOFUNC, 0, APs_Stufen,  0, 0},
{IAPSTVERZ,     TP_DSK_BG_DL, 0, NOFUNC, 0, APstVerz,    0, 0},
{IAPSPLOCK1,    TP_DSK_BG_DL, 0, NOFUNC, 0, APspLock1,   0, 0},
{IAPSTAKTIO1,   TP_DSK_BG_DL, 0, NOFUNC, 0, APstAktio1,  0, 0},
{IAPSPLOCK2,    TP_DSK_BG_DL, 0, NOFUNC, 0, APspLock2,   0, 0},
{IAPSTAKTIO2,   TP_DSK_BG_DL, 0, NOFUNC, 0, APstAktio2,  0, 0},
{IAPSPLOCK3,    TP_DSK_BG_DL, 0, NOFUNC, 0, APspLock3,   0, 0},
{IAPSTAKTIO3,   TP_DSK_BG_DL, 0, NOFUNC, 0, APstAktio3,  0, 0},
{IAPSPLOCK4,    TP_DSK_BG_DL, 0, NOFUNC, 0, APspLock4,   0, 0},
{IAPSSSTART,    TP_DSK_BG_DL, 0, NOFUNC, 0, APssStart,   0, 0},
{IAPS_NRSTUF,   TP_DSK_BG_DL, 0, NOFUNC, 0, APs_NrStuf,  0, 0},
{IAPSSPWEG,     TP_DSK_BG_DL, 0, NOFUNC, 0, APssPWeg,    0, 0},
{IKESV3IN1,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsv3In1,    0, 0},
{IKESV4IN1,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsv4In1,    0, 0},
{IKESV1IN2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsv1In2,    0, 0},
{IKESV2IN2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsv2In2,    0, 0},
{IKESV3IN2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsv3In2,    0, 0},
{IKESV4IN2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsv4In2,    0, 0},
{IKESV3OU1,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsv3Ou1,    0, 0},
{IKESV4OU1,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsv4Ou1,    0, 0},
{IKESV1OU2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsv1Ou2,    0, 0},
{IKESV2OU2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsv2Ou2,    0, 0},
{IKESV3OU2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsv3Ou2,    0, 0},
{IKESV4OU2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsv4Ou2,    0, 0},
{IKESP3IN1,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsp3In1,    0, 0},
{IKESP4IN1,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsp4In1,    0, 0},
{IKESP1IN2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsp1In2,    0, 0},
{IKESP2IN2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsp2In2,    0, 0},
{IKESP3IN2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsp3In2,    0, 0},
{IKESP4IN2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsp4In2,    0, 0},
{IKESP3OU1,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsp3Ou1,    0, 0},
{IKESP4OU1,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsp4Ou1,    0, 0},
{IKESP1OU2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsp1Ou2,    0, 0},
{IKESP2OU2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsp2Ou2,    0, 0},
{IKESP3OU2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsp3Ou2,    0, 0},
{IKESP4OU2,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsp4Ou2,    0, 0},
{IKES_ARL,      TP_DSK_BG_DL, 0, NOFUNC, 0, KEs_Arl,     0, 0},
{IKESTAVWO,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEstAVWo,    0, 0},
{IKESTAVSA,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEstAVSa,    0, 0},
{IKESTAAAU,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEstAAAu,    0, 0},
{IKESTAVSAU,    TP_DSK_BG_DL, 0, NOFUNC, 0, KEstAVSAu,   0, 0},
{IKESSAWSA,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEssAWSa,    0, 0},
{IKES_AZNS,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEs_AZnS,    0, 0},
{IKES_AUESB,    TP_DSK_BG_DL, 0, NOFUNC, 0, KEs_AUeSb,   0, 0},
{IKESVAUSG,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEsvAusG,    0, 0},
{IKESPAUSD,     TP_DSK_BG_DL, 0, NOFUNC, 0, KEspAusD,    0, 0},
{IKESPAUSND,    TP_DSK_BG_DL, 0, NOFUNC, 0, KEspAusNd,   0, 0},
{IKESVAEING,    TP_DSK_BG_DL, 0, NOFUNC, 0, KEsvAEinG,   0, 0},
{IKESPAEIND,    TP_DSK_BG_DL, 0, NOFUNC, 0, KEspAEinD,   0, 0},
{IKESPAEINND,   TP_DSK_BG_DL, 0, NOFUNC, 0, KEspAEinNd,  0, 0},
{IWZS_SNSP,     TP_DSK_BG_DL, 0, NOFUNC, 0, WZs_SnSp,    0, 0},
{ICLYEAR,       TP_STD,       0, NOFUNC, 0, ClYear,      0, 0},
{ICLMONTH,      TP_STD,       0, NOFUNC, 0, ClMonth,     0, 0},
{ICLMDAY,       TP_STD,       0, NOFUNC, 0, ClMDay,      0, 0},
{ICLHOUR,       TP_STD,       0, NOFUNC, 0, ClHour,      0, 0},
{ICLMIN,        TP_STD,       0, NOFUNC, 0, ClMin,       0, 0},
{IHES_BLOPT,    TP_D_DL,      0, NOFUNC, 0, HEs_BlOpt,   0, 0}, /* ULONG */ 
{IHES_BLOPT2,   TP_D_DL,      0, NOFUNC, 0, HEs_BlOpt2,  0, 0}, /* ULONG */ 
{XSEGPUST,      TP_DL,        0, NOFUNC, 0, SEgpUSt,     0, 0},
{XSEGPUST2,     TP_DL,        0, NOFUNC, 0, SEgpUSt2,    0, 0},
{XAWGWEG,       TP_DL,        0, NOFUNC, 0, AWgweg,      0, 0},
{XSNGDREHM1,    TP_DL,        0, NOFUNC, 0, SNgdrehm1,   0, 0},
{XSNGDREHM2,    TP_DL,        0, NOFUNC, 0, SNgdrehm2,   0, 0},
/* ------------------------------------------------------------------------ */
{XPLGWEG1,      TP_DL,        0, NOFUNC, 0, PLgweg1,     0, 0},
{XPLGWEG2,      TP_DL,        0, NOFUNC, 0, PLgweg2,     0, 0},
/*------------------------ SPS Texte -------------------------------------- */
{ITEXT_5,       TP_RD_SPEC,   0, NOFUNC, 0, IText_5,     0, 0},
{ITEXT_1,       TP_RD_SPEC,   0, NOFUNC, 0, IText_1,     0, 0},
{ITEXT_2,       TP_RD_SPEC,   0, NOFUNC, 0, IText_2,     0, 0},
{ITEXT_3,       TP_RD_SPEC,   0, NOFUNC, 0, IText_3,     0, 0},
{ITEXT_4,       TP_RD_SPEC,   0, NOFUNC, 0, IText_4,     0, 0},
{IENDADDR,      TP_STD,       0, NOFUNC, 0, IEndAddr,    0, 0},
/*------------------------ Qualitaetskontrolle ---------------------------- */
{IQUSNASZ,      TP_DSK_BG_DL, 0, NOFUNC, 0, QUsnasz,     0, 0},
{IQUSNASST,     TP_DSK_BG_DL, 0, NOFUNC, 0, QUsnasst,    0, 0},
{IQUSNPTZY,     TP_DSK_BG_DL, 0, NOFUNC, 0, QUsnptzy,    0, 0},
{IQUSNPTST,     TP_DSK_BG_DL, 0, NOFUNC, 0, QUsnptst,    0, 0},
{IQUSTVWO,      TP_DSK_BG_DL, 0, NOFUNC, 0, QUstvwo,     0, 0},
{IQUINANZ1,     TP_RD_INJ,    0, NOFUNC, 0, QUinanz1,    0, 0},
{IQUINANZ2,     TP_RD_INJ,    0, NOFUNC, 0, QUinanz2,    0, 0},
{IQUINANZ3,     TP_RD_INJ,    0, NOFUNC, 0, QUinanz3,    0, 0},
{IQUINANZ4,     TP_RD_INJ,    0, NOFUNC, 0, QUinanz4,    0, 0},
/*------------------------ Selektierweiche -------------------------------- */
{IQUS_SELEK,    TP_DSK_BG_DL, 0, NOFUNC, 0, QUs_Selek,   0, 0},
{IQUS_ANGUS,    TP_DSK_BG_DL, 0, NOFUNC, 0, QUs_Angus,   0, 0},
{IQUSTVERZ,     TP_DSK_BG_DL, 0, NOFUNC, 0, QUstVerz,    0, 0},
/*------------------------------------------------------------------------- */
{IHZ_CURREG,    TP_STD,       0, NOFUNC, 0, HZ_CurReg,   0, 0},
{IHZ_TEMPMOD,   TP_RD_SPEC,   0, NOFUNC, 0, HZ_TempMod,  0, 0},
{IHZ_TEMPKAN,   TP_RD_SPEC,   0, NOFUNC, 0, HZ_TempKan,  0, 0},
{IHZ_HEIZMOD,   TP_RD_SPEC,   0, NOFUNC, 0, HZ_HeizMod,  0, 0},
{IHZ_HEIZKAN,   TP_RD_SPEC,   0, NOFUNC, 0, HZ_HeizKan,  0, 0},
{IHZ_KUELMOD,   TP_RD_SPEC,   0, NOFUNC, 0, HZ_KuelMod,  0, 0},
{IHZ_KUELKAN,   TP_RD_SPEC,   0, NOFUNC, 0, HZ_KuelKan,  0, 0},
/* ----------------------- Register Schneckenrueckzug vor und nach Pl. ---- */
{XSRSSVOR_1,    TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, SRSsvor_1,  0, 0},
{XSRSVVOR_1,    TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, SRSvvor_1,  0, 0},
{XSRSSNACH_1,   TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, SRSsnach_1, 0, 0},
{XSRSVNACH_1,   TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, SRSvnach_1, 0, 0},
/*------------------------ Diagnoseseite 17.1 fuer Mehrfarbmaschinen------- */
{IAGGRVOR2,     TP_RD_INJ,    0, NOFUNC, 0, Iaggrvor2,   0, 0},
{IEINSPR2,      TP_RD_INJ,    0, NOFUNC, 0, Ieinspr2,    0, 0},
{IDOS2,         TP_RD_INJ,    0, NOFUNC, 0, Idos2,       0, 0},
{IAGGRVOR3,     TP_RD_INJ,    0, NOFUNC, 0, Iaggrvor3,   0, 0},
{IEINSPR3,      TP_RD_INJ,    0, NOFUNC, 0, Ieinspr3,    0, 0},
{IDOS3,         TP_RD_INJ,    0, NOFUNC, 0, Idos3,       0, 0},
{IAGGRVOR4,     TP_RD_INJ,    0, NOFUNC, 0, Iaggrvor4,   0, 0},
{IEINSPR4,      TP_RD_INJ,    0, NOFUNC, 0, Ieinspr4,    0, 0},
{IDOS4,         TP_RD_INJ,    0, NOFUNC, 0, Idos4,       0, 0},
/* ----------------------- Register fuer Seite 89.1 ----------------------- */
{XWZGENMOD,     TP_STD,       0, NOFUNC, 0, WZGenMod,     0, 0},
{XWSSKOFF,      TP_STD,       0, NOFUNC, 0, WSskOff,      0, 0},
{XWSSKGAIN,     TP_STD,       0, NOFUNC, 0, WSskGain,     0, 0},
{XWOSKOFF,      TP_STD,       0, NOFUNC, 0, WOskOff,      0, 0},
{XWOSKGAIN,     TP_STD,       0, NOFUNC, 0, WOskGain,     0, 0},
{XWSIKOFF,      TP_RD_SPEC,   0, NOFUNC, 0, WSikOff,      0, 0},
{XWSIKGAIN,     TP_RD_SPEC,   0, NOFUNC, 0, WSikGain,     0, 0},
{XWOIKOFF,      TP_RD_SPEC,   0, NOFUNC, 0, WOikOff,      0, 0},
{XWOIKGAIN,     TP_RD_SPEC,   0, NOFUNC, 0, WOikGain,     0, 0},
/* ----------------------- Register fuer Seite 89.2 ----------------------- */
{XAWGENMOD,     TP_STD,       0, NOFUNC, 0, AWGenMod,     0, 0},
{XAWSKVOFF,     TP_STD,       0, NOFUNC, 0, AWskVOff,     0, 0},
{XAWSKVGAIN,    TP_STD,       0, NOFUNC, 0, AWskVGain,    0, 0},
{XAWSKZOFF,     TP_STD,       0, NOFUNC, 0, AWskZOff,     0, 0},
{XAWSKZGAIN,    TP_STD,       0, NOFUNC, 0, AWskZGain,    0, 0},
{XAWIKVOFF,     TP_RD_SPEC,   0, NOFUNC, 0, AWikVOff,     0, 0},
{XAWIKVGAIN,    TP_RD_SPEC,   0, NOFUNC, 0, AWikVGain,    0, 0},
{XAWIKZOFF,     TP_RD_SPEC,   0, NOFUNC, 0, AWikZOff,     0, 0},
{XAWIKZGAIN,    TP_RD_SPEC,   0, NOFUNC, 0, AWikZGain,    0, 0},
/* ---------------- Abgleichseite 89.3 ------------------------------------ */
{XPL1GENMOD,    TP_STD,       0, NOFUNC, 0, PL1GenMod,    0, 0},
{XPL2GENMOD,    TP_STD,       0, NOFUNC, 0, PL2GenMod,    0, 0},
{XPLSKRAMPE1,   TP_STD,       0, NOFUNC, 0, PLskRampe1,   0, 0},
{XPLSKRAMPE2,   TP_STD,       0, NOFUNC, 0, PLskRampe2,   0, 0},
{XPLSKGEST1,    TP_STD,       0, NOFUNC, 0, PLskGest1,    0, 0},
{XPLSKGEST2,    TP_STD,       0, NOFUNC, 0, PLskGest2,    0, 0},
{XPLIKARAMP1,   TP_RD_SPEC,   0, NOFUNC, 0, PLikARamp1,   0, 0},
{XPLIKARAMP2,   TP_RD_SPEC,   0, NOFUNC, 0, PLikARamp2,   0, 0},
{XPLIKDRAMP1,   TP_RD_SPEC,   0, NOFUNC, 0, PLikDRamp1,   0, 0},
{XPLIKDRAMP2,   TP_RD_SPEC,   0, NOFUNC, 0, PLikDRamp2,   0, 0},
{XPLIKAGEST1,   TP_RD_SPEC,   0, NOFUNC, 0, PLikAGest1,   0, 0},
{XPLIKAGEST2,   TP_RD_SPEC,   0, NOFUNC, 0, PLikAGest2,   0, 0},
{XPLIKDGEST1,   TP_RD_SPEC,   0, NOFUNC, 0, PLikDGest1,   0, 0},
{XPLIKDGEST2,   TP_RD_SPEC,   0, NOFUNC, 0, PLikDGest2,   0, 0},
/* ---------------- END Abgleichseite 89.3 -------------------------------- */
/*----------------- Airpress ---------------------------------------------- */
{XAIR_ON,    TP_DSK_BG_DL,    0, NOFUNC, 0,  air_on    ,0, 0},
{XDUES_ZU,   TP_DSK_BG_DL,    0, NOFUNC, 0,  dues_zu   ,0, 0},
{XSTVERZ_D1, TP_DSK_BG_DL,    0, NOFUNC, 0,  stverz_d1 ,0, 0},
{XSTVERZ_D2, TP_DSK_BG_DL,    0, NOFUNC, 0,  stverz_d2 ,0, 0},
{XSTVERZ_D3, TP_DSK_BG_DL,    0, NOFUNC, 0,  stverz_d3 ,0, 0},
{XSTVERZ_D4, TP_DSK_BG_DL,    0, NOFUNC, 0,  stverz_d4 ,0, 0},
{XSTACT1_D1, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact1_d1 ,0, 0},
{XSTACT1_D2, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact1_d2 ,0, 0},
{XSTACT1_D3, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact1_d3 ,0, 0},
{XSTACT1_D4, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact1_d4 ,0, 0},
{XSPRES1_D1, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres1_d1 ,0, 0},
{XSPRES1_D2, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres1_d2 ,0, 0},
{XSPRES1_D3, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres1_d3 ,0, 0},
{XSPRES1_D4, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres1_d4 ,0, 0},
{XSTACT2_D1, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact2_d1 ,0, 0},
{XSTACT2_D2, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact2_d2 ,0, 0},
{XSTACT2_D3, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact2_d3 ,0, 0},
{XSTACT2_D4, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact2_d4 ,0, 0},
{XSPRES2_D1, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres2_d1 ,0, 0},
{XSPRES2_D2, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres2_d2 ,0, 0},
{XSPRES2_D3, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres2_d3 ,0, 0},
{XSPRES2_D4, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres2_d4 ,0, 0},
{XSTACT3_D1, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact3_d1 ,0, 0},
{XSTACT3_D2, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact3_d2 ,0, 0},
{XSTACT3_D3, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact3_d3 ,0, 0},
{XSTACT3_D4, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact3_d4 ,0, 0},
{XSPRES3_D1, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres3_d1 ,0, 0},
{XSPRES3_D2, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres3_d2 ,0, 0},
{XSPRES3_D3, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres3_d3 ,0, 0},
{XSPRES3_D4, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres3_d4 ,0, 0},
{XSTACT4_D1, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact4_d1 ,0, 0},
{XSTACT4_D2, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact4_d2 ,0, 0},
{XSTACT4_D3, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact4_d3 ,0, 0},
{XSTACT4_D4, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact4_d4 ,0, 0},
{XSPRES4_D1, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres4_d1 ,0, 0},
{XSPRES4_D2, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres4_d2 ,0, 0},
{XSPRES4_D3, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres4_d3 ,0, 0},
{XSPRES4_D4, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres4_d4 ,0, 0},
{XSTACT5_D1, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact5_d1 ,0, 0},
{XSTACT5_D2, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact5_d2 ,0, 0},
{XSTACT5_D3, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact5_d3 ,0, 0},
{XSTACT5_D4, TP_DSK_BG_DL,    0, NOFUNC, 0,  stact5_d4 ,0, 0},
{XSPRES5_D1, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres5_d1 ,0, 0},
{XSPRES5_D2, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres5_d2 ,0, 0},
{XSPRES5_D3, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres5_d3 ,0, 0},
{XSPRES5_D4, TP_DSK_BG_DL,    0, NOFUNC, 0,  spres5_d4 ,0, 0},
/*---------------------------- Ende Airpress ------------------------------*/
/* ---------------- Diagnoseseite Schliessdruckaufbau 87.5 ---------------- */
{XSDRGENMOD,    TP_STD,       0, NOFUNC, 0, SDRGenMod,    0, 0},
{XSDRSTAUFV,    TP_STD,       0, NOFUNC, 0, SDRstAufV,    0, 0},
{XSDRSTAUFB,    TP_STD,       0, NOFUNC, 0, SDRstAufB,    0, 0},
{XSDRITAAUFV,   TP_RD_SPEC,   0, NOFUNC, 0, SDRitAAufV,   0, 0},
{XSDRITDAUFV,   TP_RD_SPEC,   0, NOFUNC, 0, SDRitDAufV,   0, 0},
{XSDRITAAUFB,   TP_RD_SPEC,   0, NOFUNC, 0, SDRitAAufB,   0, 0},
{XSDRITDAUFB,   TP_RD_SPEC,   0, NOFUNC, 0, SDRitDAufB,   0, 0},
/* ---------------- END Diagnoseseite Schliessdruckaufbau 87.5 ------------ */
{XAWSPZUR,      TP_DSK_BG_DL, 0, NOFUNC, 0, AWspZur,      0, 0},
/* ---------------- Seite 69.0 Blasluftzeiten in 1/100 sec ---------------- */
{XLVSTVERZ10,   TP_DSK_BG_DL, PFlt_Blasluft100To10, NOFUNC, 0, LVstVerz10, 0, 0},
{XLVSTVERZ20,   TP_DSK_BG_DL, PFlt_Blasluft100To10, NOFUNC, 0, LVstVerz20, 0, 0},
{XLVSTVERZ30,   TP_DSK_BG_DL, PFlt_Blasluft100To10, NOFUNC, 0, LVstVerz30, 0, 0},
{XLVSTVERZ40,   TP_DSK_BG_DL, PFlt_Blasluft100To10, NOFUNC, 0, LVstVerz40, 0, 0},
{XLVSTBLAS10,   TP_DSK_BG_DL, PFlt_Blasluft100To10, NOFUNC, 0, LVstBlas10, 0, 0},
{XLVSTBLAS20,   TP_DSK_BG_DL, PFlt_Blasluft100To10, NOFUNC, 0, LVstBlas20, 0, 0},
{XLVSTBLAS30,   TP_DSK_BG_DL, PFlt_Blasluft100To10, NOFUNC, 0, LVstBlas30, 0, 0},
{XLVSTBLAS40,   TP_DSK_BG_DL, PFlt_Blasluft100To10, NOFUNC, 0, LVstBlas40, 0, 0},
/* ---------------- END Seite 69.0 Blasluftzeiten in 1/100 sec ------------ */
/* ---------------- Max. hydraulik Druck ---------------------------------- */
{XSPIPHYDMAX,   TP_RD_INJ,    0, NOFUNC, 0, SPIpHydMax,   0, 0},
/* ------------------------------------------------------------------------ */
{XFPKZANDFHK,   TP_COREDSK_BG_DL, 0, NOFUNC, 0, FPKZandFHK, 0, 0},
/* ---------------- Max. Schneckenumdrehung ------------------------------- */
{XSNG_UMDR1,    TP_DL,        0, NOFUNC, 0, SNg_Umdr1,    0, 0},
{XSNG_UMDR2,    TP_DL,        0, NOFUNC, 0, SNg_Umdr2,    0, 0},
/* ---------------- Freiauswaehlbare Diagnoseseite ------------------------ */
{XDIAGMAXMOD,   TP_RD_SPEC,   0, NOFUNC, 0, DiagMaxMod,   0, 0},
{XDIAGRDIND,    TP_STD,       0, NOFUNC, 0, DiagRDInd,    0, 0},
{XDIAGWRIND,    TP_STD,       0, NOFUNC, 0, DiagWRInd,    0, 0},
{XDIAGSYSTYP,   TP_RD_SPEC,   0, NOFUNC, 0, DiagSysTyp,   0, 0},
{XDIAGBUSNR,    TP_RD_SPEC,   0, NOFUNC, 0, DiagBusNr,    0, 0},
{XDIAGMODNR,    TP_RD_SPEC,   0, NOFUNC, 0, DiagModNr,    0, 0},
{XDIAGINDTAB,   TP_RD_SPEC,   0, NOFUNC, 0, DiagIndTab,   0, 0},
/* ------------------------------------------------------------------------ */
{XFDIAGDAKT,    TP_RD_LSPEC,  0, NOFUNC, 0, FDiagDAKT,    0, 0}, /* ULONG */ 
{XFDIAGDFOR,    TP_D,         0, NOFUNC, 0, FDiagDFOR,    0, 0}, /* ULONG */ 
/* ------------------------------------------------------------------------ */
{XFDIAGA_A01,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A01, 0, 0},
{XFDIAGA_A02,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A02, 0, 0},
{XFDIAGA_A03,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A03, 0, 0},
{XFDIAGA_A04,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A04, 0, 0},
{XFDIAGA_A05,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A05, 0, 0},
{XFDIAGA_A06,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A06, 0, 0},
{XFDIAGA_A07,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A07, 0, 0},
{XFDIAGA_A08,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A08, 0, 0},
{XFDIAGA_A09,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A09, 0, 0},
{XFDIAGA_A10,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A10, 0, 0},
{XFDIAGA_A11,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A11, 0, 0},
{XFDIAGA_A12,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A12, 0, 0},
{XFDIAGA_A13,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A13, 0, 0},
{XFDIAGA_A14,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A14, 0, 0},
{XFDIAGA_A15,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A15, 0, 0},
{XFDIAGA_A16,   TP_RD_SPEC,   0, {PConvDMAnalog,DIAG_IST},  0, FDiagA_A16, 0, 0},
/* ------------------------------------------------------------------------ */
{XFDIAGA_F01,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F01, 0, 0},
{XFDIAGA_F02,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F02, 0, 0},
{XFDIAGA_F03,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F03, 0, 0},
{XFDIAGA_F04,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F04, 0, 0},
{XFDIAGA_F05,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F05, 0, 0},
{XFDIAGA_F06,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F06, 0, 0},
{XFDIAGA_F07,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F07, 0, 0},
{XFDIAGA_F08,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F08, 0, 0},
{XFDIAGA_F09,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F09, 0, 0},
{XFDIAGA_F10,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F10, 0, 0},
{XFDIAGA_F11,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F11, 0, 0},
{XFDIAGA_F12,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F12, 0, 0},
{XFDIAGA_F13,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F13, 0, 0},
{XFDIAGA_F14,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F14, 0, 0},
{XFDIAGA_F15,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F15, 0, 0},
{XFDIAGA_F16,   TP_STD,       0, {PConvDMAnalog,DIAG_SOLL}, 0, FDiagA_F16, 0, 0},
/* ------------------------------------------------------------------------ */
{XAKT_DVAL1,    TP_RD_LSPEC,  0, NOFUNC, 0, AKT_Dval1,    0, 0}, /* ULONG */ 
{XAKT_DVAL2,    TP_RD_LSPEC,  0, NOFUNC, 0, AKT_Dval2,    0, 0}, /* ULONG */ 
{XAKT_DVAL3,    TP_RD_LSPEC,  0, NOFUNC, 0, AKT_Dval3,    0, 0}, /* ULONG */ 
{XAKT_DVAL4,    TP_RD_LSPEC,  0, NOFUNC, 0, AKT_Dval4,    0, 0}, /* ULONG */ 
{XAKT_DVAL5,    TP_RD_LSPEC,  0, NOFUNC, 0, AKT_Dval5,    0, 0}, /* ULONG */ 
{XAKT_DVAL6,    TP_RD_LSPEC,  0, NOFUNC, 0, AKT_Dval6,    0, 0}, /* ULONG */ 
{XAKT_DVAL7,    TP_RD_LSPEC,  0, NOFUNC, 0, AKT_Dval7,    0, 0}, /* ULONG */ 
/* ------------------------------------------------------------------------ */
{XFOR_DVAL1,    TP_D,         0, NOFUNC, 0, FOR_Dval1,    0, 0}, /* ULONG */ 
{XFOR_DVAL2,    TP_D,         0, NOFUNC, 0, FOR_Dval2,    0, 0}, /* ULONG */ 
{XFOR_DVAL3,    TP_D,         0, NOFUNC, 0, FOR_Dval3,    0, 0}, /* ULONG */ 
{XFOR_DVAL4,    TP_D,         0, NOFUNC, 0, FOR_Dval4,    0, 0}, /* ULONG */ 
{XFOR_DVAL5,    TP_D,         0, NOFUNC, 0, FOR_Dval5,    0, 0}, /* ULONG */ 
{XFOR_DVAL6,    TP_D,         0, NOFUNC, 0, FOR_Dval6,    0, 0}, /* ULONG */ 
{XFOR_DVAL7,    TP_D,         0, NOFUNC, 0, FOR_Dval7,    0, 0}, /* ULONG */ 
/* ------------------------------------------------------------------------ */
{XAKT1AVAL01,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval01, 0, 0},
{XAKT1AVAL02,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval02, 0, 0},
{XAKT1AVAL03,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval03, 0, 0},
{XAKT1AVAL04,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval04, 0, 0},
{XAKT1AVAL05,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval05, 0, 0},
{XAKT1AVAL06,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval06, 0, 0},
{XAKT1AVAL07,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval07, 0, 0},
{XAKT1AVAL08,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval08, 0, 0},
{XAKT1AVAL09,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval09, 0, 0},
{XAKT1AVAL10,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval10, 0, 0},
{XAKT1AVAL11,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval11, 0, 0},
{XAKT1AVAL12,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval12, 0, 0},
{XAKT1AVAL13,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval13, 0, 0},
{XAKT1AVAL14,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval14, 0, 0},
{XAKT1AVAL15,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval15, 0, 0},
{XAKT1AVAL16,   TP_RD_SPEC,   0, NOFUNC, 0, AKT1Aval16, 0, 0},
/* ------------------------------------------------------------------------ */
{XFOR1AVAL01,   TP_STD,       0, NOFUNC, 0, FOR1Aval01,   0, 0},
{XFOR1AVAL02,   TP_STD,       0, NOFUNC, 0, FOR1Aval02,   0, 0},
{XFOR1AVAL03,   TP_STD,       0, NOFUNC, 0, FOR1Aval03,   0, 0},
{XFOR1AVAL04,   TP_STD,       0, NOFUNC, 0, FOR1Aval04,   0, 0},
{XFOR1AVAL05,   TP_STD,       0, NOFUNC, 0, FOR1Aval05,   0, 0},
{XFOR1AVAL06,   TP_STD,       0, NOFUNC, 0, FOR1Aval06,   0, 0},
{XFOR1AVAL07,   TP_STD,       0, NOFUNC, 0, FOR1Aval07,   0, 0},
{XFOR1AVAL08,   TP_STD,       0, NOFUNC, 0, FOR1Aval08,   0, 0},
{XFOR1AVAL09,   TP_STD,       0, NOFUNC, 0, FOR1Aval09,   0, 0},
{XFOR1AVAL10,   TP_STD,       0, NOFUNC, 0, FOR1Aval10,   0, 0},
{XFOR1AVAL11,   TP_STD,       0, NOFUNC, 0, FOR1Aval11,   0, 0},
{XFOR1AVAL12,   TP_STD,       0, NOFUNC, 0, FOR1Aval12,   0, 0},
{XFOR1AVAL13,   TP_STD,       0, NOFUNC, 0, FOR1Aval13,   0, 0},
{XFOR1AVAL14,   TP_STD,       0, NOFUNC, 0, FOR1Aval14,   0, 0},
{XFOR1AVAL15,   TP_STD,       0, NOFUNC, 0, FOR1Aval15,   0, 0},
{XFOR1AVAL16,   TP_STD,       0, NOFUNC, 0, FOR1Aval16,   0, 0},
/* ------------------------------------------------------------------------ */
{XAKT2AVAL01,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval01, 0, 0},
{XAKT2AVAL02,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval02, 0, 0},
{XAKT2AVAL03,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval03, 0, 0},
{XAKT2AVAL04,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval04, 0, 0},
{XAKT2AVAL05,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval05, 0, 0},
{XAKT2AVAL06,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval06, 0, 0},
{XAKT2AVAL07,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval07, 0, 0},
{XAKT2AVAL08,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval08, 0, 0},
{XAKT2AVAL09,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval09, 0, 0},
{XAKT2AVAL10,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval10,   0, 0},
{XAKT2AVAL11,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval11,   0, 0},
{XAKT2AVAL12,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval12,   0, 0},
{XAKT2AVAL13,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval13,   0, 0},
{XAKT2AVAL14,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval14,   0, 0},
{XAKT2AVAL15,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval15,   0, 0},
{XAKT2AVAL16,   TP_RD_SPEC,   0, NOFUNC, 0, AKT2Aval16,   0, 0},
/* ------------------------------------------------------------------------ */
{XFOR2AVAL01,   TP_STD,       0, NOFUNC, 0, FOR2Aval01, 0, 0},
{XFOR2AVAL02,   TP_STD,       0, NOFUNC, 0, FOR2Aval02, 0, 0},
{XFOR2AVAL03,   TP_STD,       0, NOFUNC, 0, FOR2Aval03, 0, 0},
{XFOR2AVAL04,   TP_STD,       0, NOFUNC, 0, FOR2Aval04, 0, 0},
{XFOR2AVAL05,   TP_STD,       0, NOFUNC, 0, FOR2Aval05, 0, 0},
{XFOR2AVAL06,   TP_STD,       0, NOFUNC, 0, FOR2Aval06,   0, 0},
{XFOR2AVAL07,   TP_STD,       0, NOFUNC, 0, FOR2Aval07,   0, 0},
{XFOR2AVAL08,   TP_STD,       0, NOFUNC, 0, FOR2Aval08,   0, 0},
{XFOR2AVAL09,   TP_STD,       0, NOFUNC, 0, FOR2Aval09,   0, 0},
{XFOR2AVAL10,   TP_STD,       0, NOFUNC, 0, FOR2Aval10,   0, 0},
{XFOR2AVAL11,   TP_STD,       0, NOFUNC, 0, FOR2Aval11,   0, 0},
{XFOR2AVAL12,   TP_STD,       0, NOFUNC, 0, FOR2Aval12,   0, 0},
{XFOR2AVAL13,   TP_STD,       0, NOFUNC, 0, FOR2Aval13,   0, 0},
{XFOR2AVAL14,   TP_STD,       0, NOFUNC, 0, FOR2Aval14,   0, 0},
{XFOR2AVAL15,   TP_STD,       0, NOFUNC, 0, FOR2Aval15,   0, 0},
{XFOR2AVAL16,   TP_STD,       0, NOFUNC, 0, FOR2Aval16,   0, 0},
/* ---------------- Istwertbereich der Heizung ---------------------------- */
{XXKSR01,       TP_STD,       0, NOFUNC, 0, xksr01,       0, 0},
{XXKSR02,       TP_STD,       0, NOFUNC, 0, xksr02,       0, 0},
{XXKSR03,       TP_STD,       0, NOFUNC, 0, xksr03,       0, 0},
{XXKSR04,       TP_STD,       0, NOFUNC, 0, xksr04,       0, 0},
{XXKSR05,       TP_STD,       0, NOFUNC, 0, xksr05,       0, 0},
{XXKSR06,       TP_STD,       0, NOFUNC, 0, xksr06,       0, 0},
{XXKSR07,       TP_STD,       0, NOFUNC, 0, xksr07,       0, 0},
{XXKSR08,       TP_STD,       0, NOFUNC, 0, xksr08,       0, 0},
{XXKSR09,       TP_STD,       0, NOFUNC, 0, xksr09,       0, 0},
{XXKSR10,       TP_STD,       0, NOFUNC, 0, xksr10,       0, 0},
{XXKSR11,       TP_STD,       0, NOFUNC, 0, xksr11,       0, 0},
{XXKSR12,       TP_STD,       0, NOFUNC, 0, xksr12,       0, 0},
{XXKSR13,       TP_STD,       0, NOFUNC, 0, xksr13,       0, 0},
{XXKSR14,       TP_STD,       0, NOFUNC, 0, xksr14,       0, 0},
{XXKSR15,       TP_STD,       0, NOFUNC, 0, xksr15,       0, 0},
{XXKSR16,       TP_STD,       0, NOFUNC, 0, xksr16,       0, 0},
{XXKER01,       TP_STD,       0, NOFUNC, 0, xker01,       0, 0},
{XXKER02,       TP_STD,       0, NOFUNC, 0, xker02,       0, 0},
{XXKER03,       TP_STD,       0, NOFUNC, 0, xker03,       0, 0},
{XXKER04,       TP_STD,       0, NOFUNC, 0, xker04,       0, 0},
{XXKER05,       TP_STD,       0, NOFUNC, 0, xker05,       0, 0},
{XXKER06,       TP_STD,       0, NOFUNC, 0, xker06,       0, 0},
{XXKER07,       TP_STD,       0, NOFUNC, 0, xker07,       0, 0},
{XXKER08,       TP_STD,       0, NOFUNC, 0, xker08,       0, 0},
{XXKER09,       TP_STD,       0, NOFUNC, 0, xker09,       0, 0},
{XXKER10,       TP_STD,       0, NOFUNC, 0, xker10,       0, 0},
{XXKER11,       TP_STD,       0, NOFUNC, 0, xker11,       0, 0},
{XXKER12,       TP_STD,       0, NOFUNC, 0, xker12,       0, 0},
{XXKER13,       TP_STD,       0, NOFUNC, 0, xker13,       0, 0},
{XXKER14,       TP_STD,       0, NOFUNC, 0, xker14,       0, 0},
{XXKER15,       TP_STD,       0, NOFUNC, 0, xker15,       0, 0},
{XXKER16,       TP_STD,       0, NOFUNC, 0, xker16,       0, 0},
{XXKIR01,       TP_STD,       0, NOFUNC, 0, xkir01,       0, 0},
{XXKIR02,       TP_STD,       0, NOFUNC, 0, xkir02,       0, 0},
{XXKIR03,       TP_STD,       0, NOFUNC, 0, xkir03,       0, 0},
{XXKIR04,       TP_STD,       0, NOFUNC, 0, xkir04,       0, 0},
{XXKIR05,       TP_STD,       0, NOFUNC, 0, xkir05,       0, 0},
{XXKIR06,       TP_STD,       0, NOFUNC, 0, xkir06,       0, 0},
{XXKIR07,       TP_STD,       0, NOFUNC, 0, xkir07,       0, 0},
{XXKIR08,       TP_STD,       0, NOFUNC, 0, xkir08,       0, 0},
{XXKIR09,       TP_STD,       0, NOFUNC, 0, xkir09,       0, 0},
{XXKIR10,       TP_STD,       0, NOFUNC, 0, xkir10,       0, 0},
{XXKIR11,       TP_STD,       0, NOFUNC, 0, xkir11,       0, 0},
{XXKIR12,       TP_STD,       0, NOFUNC, 0, xkir12,       0, 0},
{XXKIR13,       TP_STD,       0, NOFUNC, 0, xkir13,       0, 0},
{XXKIR14,       TP_STD,       0, NOFUNC, 0, xkir14,       0, 0},
{XXKIR15,       TP_STD,       0, NOFUNC, 0, xkir15,       0, 0},
{XXKIR16,       TP_STD,       0, NOFUNC, 0, xkir16,       0, 0},
{XXKGWPW,       TP_STD,       0, NOFUNC, 0, xkgwpw,       0, 0},
{XXKGWPE,       TP_STD,       0, NOFUNC, 0, xkgwpe,       0, 0},
{XXKGWNE,       TP_STD,       0, NOFUNC, 0, xkgwne,       0, 0},
{XXKGWNW,       TP_STD,       0, NOFUNC, 0, xkgwnw,       0, 0},
{XTKXTHB,       TP_STD,       0, NOFUNC, 0, tkxthb,       0, 0},
{XXKBLNR,       TP_STD,       0, NOFUNC, 0, xkblnr,       0, 0},
/* ---------------- Sollwertbereich der Heizung --------------------------- */
{XSNREGL,       TP_STD,       0, NOFUNC, 0, snregl,       0, 0},
{XSNGRUP,       TP_STD,       0, NOFUNC, 0, snregl,       0, 0},
{XSKTEMP,       TP_STD,       0, NOFUNC, 0, sktemp,       0, 0},
{XSKGWNW,       TP_STD,       0, NOFUNC, 0, skgwnw,       0, 0},
{XSKGWNE,       TP_STD,       0, NOFUNC, 0, skgwne,       0, 0},
{XSKGWPW,       TP_STD,       0, NOFUNC, 0, skgwpw,       0, 0},
{XSKGWPE,       TP_STD,       0, NOFUNC, 0, skgwpe,       0, 0},
{XSNMCW,        TP_STD,       0, NOFUNC, 0, snmcw,        0, 0},
{XSNXPH,        TP_STD,       0, NOFUNC, 0, snxph,        0, 0},
{XSNXPK,        TP_STD,       0, NOFUNC, 0, snxpk,        0, 0},
{XSNTN,         TP_STD,       0, NOFUNC, 0, sntv,         0, 0},
{XSNTV,         TP_STD,       0, NOFUNC, 0, sntn,         0, 0},
{XSNTOH,        TP_STD,       0, NOFUNC, 0, sntoh,        0, 0},
{XSNTOK,        TP_STD,       0, NOFUNC, 0, sntok,        0, 0},
{XSNSHY,        TP_STD,       0, NOFUNC, 0, snshy,        0, 0},
{XSNY,          TP_STD,       0, NOFUNC, 0, sny,          0, 0},
{XSNYMIN,       TP_STD,       0, NOFUNC, 0, snymin,       0, 0},
{XSNYMAX,       TP_STD,       0, NOFUNC, 0, snymax,       0, 0},
{XSNTM,         TP_STD,       0, NOFUNC, 0, sntm,         0, 0},
{XSNSPDS,       TP_STD,       0, NOFUNC, 0, sntm,         0, 0},
{XSNONOF,       TP_STD,       0, NOFUNC, 0, sntm,         0, 0},
{XSNSSOL,       TP_STD,       0, NOFUNC, 0, sntm,         0, 0},
{XSNSTEL,       TP_STD,       0, NOFUNC, 0, sntm,         0, 0},
{XSNTHTY,       TP_STD,       0, NOFUNC, 0, sntm,         0, 0},
{XSNMESS,       TP_STD,       0, NOFUNC, 0, sntm,         0, 0},
{XSNFUNC,       TP_STD,       0, NOFUNC, 0, sntm,         0, 0},
{XSNLOOP,       TP_STD,       0, NOFUNC, 0, sntm,         0, 0},
{XSNCNTY,       TP_STD,       0, NOFUNC, 0, sntm,         0, 0},
/* ------------------------------------------------------------------------ */
{XIQTSSACT,     TP_RD_FAST,   0, NOFUNC, 0, IqtSSAct,     0, 0},
/* ---------------- Register fuer Aggregat mit Wegmesssystem -------------- */
{XSESSVOR11,    TP_DSK_BG_DL, 0, NOFUNC, 0, SEssVor11,    0, 0},
{XSESSVOR12,    TP_DSK_BG_DL, 0, NOFUNC, 0, SEssVor12,    0, 0},
{XSESSZUR11,    TP_DSK_BG_DL, 0, NOFUNC, 0, SEssZur11,    0, 0},
{XSESSZUR12,    TP_DSK_BG_DL, 0, NOFUNC, 0, SEssZur12,    0, 0},
{XSESSNLPKT1,   TP_STD,       0, NOFUNC, 0, SEssNlpkt1,   0, 0},
{XSESSNLPKT2,   TP_STD,       0, NOFUNC, 0, SEssNlpkt2,   0, 0},
{XSEISNLPKT1,   TP_RD_FAST,   0, NOFUNC, 0, SEisNlpkt1,   0, 0},
{XSEISNLPKT2,   TP_RD_FAST,   0, NOFUNC, 0, SEisNlpkt2,   0, 0},
/* ---------------- Register fuer SPS-Tasten Crashlogbuch ----------------- */
{IKBA0INPUT,    TP_RD_FAST,   0, NOFUNC, 0, KbA0Input,    0, 0},
{IKBA1INPUT,    TP_RD_FAST,   0, NOFUNC, 0, KbA1Input,    0, 0}, 
{IKBA2INPUT,    TP_RD_FAST,   0, NOFUNC, 0, KbA2Input,    0, 0}, 
{IKBA3INPUT,    TP_RD_FAST,   0, NOFUNC, 0, KbA3Input,    0, 0}, 
/* -------- Register fuer Produktionsstart S. 40.2 ------------------ */
{XXSN_ANFA ,    TP_DSK_BG_DL, 0, NOFUNC, 0, XSn_Anfa ,    0, 0},           /* Anzahl Anfahrzyklen */
{XSSDOS1A ,     TP_DSK_BG_DL, PFlt_WHToVS_Soll,NOFUNC,  0, ssdos1a, 0, 0}, /* Plastivizierweg */
{XSPPH11A  ,    TP_DSK_BG_DL, PFlt_WHToVS_Soll,NOFUNC , 0, spph11a, 0, 0}, /* Einspritzdruck p1 */
{XSTPH11A  ,    TP_DSK_BG_DL, PFlt_WHToVS_Soll,NOFUNC , 0, stph11a, 0, 0}, /* Einspritzzeit t1 */
{XSPPH12A  ,    TP_DSK_BG_DL, PFlt_WHToVS_Soll,NOFUNC , 0, spph12a, 0, 0}, /* Einspritzdruck p2 */
{XSTPH12A  ,    TP_DSK_BG_DL, PFlt_WHToVS_Soll,NOFUNC , 0, stph12a, 0, 0}, /* Einspritzzeit t2 */
{XSPPH13A  ,    TP_DSK_BG_DL, PFlt_WHToVS_Soll,NOFUNC , 0, spph13a, 0, 0}, /* Einspritzdruck p3 */
{XSTPH13A  ,    TP_DSK_BG_DL, PFlt_WHToVS_Soll,NOFUNC , 0, stph13a, 0, 0}, /* Einspritzzeit t3 */
{XXSN_ANF2A,    TP_DSK_BG_DL, 0, NOFUNC, 0, XSn_Anf2a,    0, 0},           /* Anzahl Anfahrzyklen Wkz-Druck */
{XSPNIDRA  ,    TP_DSK_BG_DL, 0, NOFUNC, 0, spnidra  ,    0, 0},           /* Druck werkzeugsicherung1 */  
{XSPNIDR2A ,    TP_DSK_BG_DL, 0, NOFUNC, 0, spnidr2a ,    0, 0},           /* Druck werkzeugsicherung2 */  
/* -------- Indizierte Register, Weg-/Volumenumschaltung ------------ */
{XSVPH11A ,     TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, svph11a, 0, 0},       /* Einspritzgeschw. v1 */ 
{XSVPH12A ,     TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, svph12a, 0, 0},       /* Einspritzgeschw. v2 */
{XSVPH13A ,     TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, svph13a, 0, 0},       /* Einspritzgeschw. v3 */ 
{XSSPH11A ,     TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, ssph11a, 0, 0},       /* Umschaltpunkt s1 */
{XSSPH12A ,     TP_DSK_BG_DL, PFlt_WHToVS_Soll, NOFUNC, 0, ssph12a, 0, 0},       /* Umschaltpunkt s2 */
/* ------------------------------------------------------------------------ */
{XHXSNIF    ,   TP_DSK_BG_DL, 0, NOFUNC, 0, HXsnIF,       0, 0}, 
{XHXSNPROTO ,   TP_DSK_BG_DL, 0, NOFUNC, 0, HXsnProto,    0, 0}, 
{XHXSNBAUD  ,   TP_DSK_BG_DL, 0, NOFUNC, 0, HXsnBaud,     0, 0}, 
{XHXSNDATBIT,   TP_DSK_BG_DL, 0, NOFUNC, 0, HXsnDatBit,   0, 0}, 
{XHXSNSTPBIT,   TP_DSK_BG_DL, 0, NOFUNC, 0, HXsnStpBit,   0, 0}, 
{XHXSNPARITY,   TP_DSK_BG_DL, 0, NOFUNC, 0, HXsnParity,   0, 0}, 
{XHXSNIF_2,     TP_DSK_BG_DL, 0 ,NOFUNC, 0, HXsnIF_2,     0, 0},
{XHXSNPROTO_2,  TP_DSK_BG_DL, 0 ,NOFUNC, 0, HXsnProto2,   0, 0}, 
{XHXSNBAUD_2,   TP_DSK_BG_DL, 0 ,NOFUNC, 0, HXsnBaud_2,   0, 0}, 
{XHXSNDATBIT_2, TP_DSK_BG_DL, 0 ,NOFUNC, 0, HXsnDatBi2,   0, 0}, 
{XHXSNSTPBIT_2, TP_DSK_BG_DL, 0 ,NOFUNC, 0, HXsnStpBi2,   0, 0}, 
{XHXSNPARITY_2, TP_DSK_BG_DL, 0 ,NOFUNC, 0, HXsnParit2,   0, 0},
/* ---------------- Register fuer frei programmierbare Kernzuege */
{IKEPRGNO,   	 TP_COREDSK_BG_DL, 0, NOFUNC, 0, KEprgno,   0, 0}, /* CORE */
{IKE_NRSCHRAUB, TP_RD_FAST,   0, NOFUNC, 0, KE_NrSchraub,   0, 0},
{IKE_NRWEND,    TP_RD_FAST,   0, NOFUNC, 0, KE_NrWend,   0, 0},
{IKE_SPERRMASKE, TP_RD_FAST,   0, NOFUNC, 0, KE_SperrMaske,   0, 0},
{IKEEINRICHT,   TP_COREDSK_BG_DL, 0, {PCStatFuncInv, 0}, 0, KEeinricht,   0, 0}, /* CORE */
{IKEGRUNDST,    TP_STD,       0, NOFUNC, 0, KEgrundst,    0, 0},
{IKEPGMSTAT,    TP_BG_DL,     0, NOFUNC, 0, KEpgmstat,    0, 0},
{IKEPARUPD,     TP_STD,       0, NOFUNC, 0, KEparupd,     0, 0},
{IKEPGMLINES,   TP_COREDSK_BG_DL, 0, NOFUNC, 0, KEpgmlines,   0, 0}, /* CORE */
{IKEDLENABLE,   TP_STD,       0, NOFUNC, 0, KEdlenable,   0, 0},
{IKEDLSTAT,     TP_STD,       0, NOFUNC, 0, KEdlstat,     0, 0},
{IKESYNC,       TP_STD,       0, NOFUNC, 0, KEsync,       0, 0},
{IKEIST1,       TP_RD_FAST,   0, NOFUNC, 0, KEIst1,       0, 0},
{IKEIST2,       TP_RD_FAST,   0, NOFUNC, 0, KEIst2,       0, 0},
{IKEIST3,       TP_RD_FAST,   0, NOFUNC, 0, KEIst3,       0, 0},
{IKEIST4,       TP_RD_FAST,   0, NOFUNC, 0, KEIst4,       0, 0},
{IKEIST5,       TP_RD_FAST,   0, NOFUNC, 0, KEIst5,       0, 0},
{IKEIST6,       TP_RD_FAST,   0, NOFUNC, 0, KEIst6,       0, 0},
{IKEIST7,       TP_RD_FAST,   0, NOFUNC, 0, KEIst7,       0, 0},
{IKEIST8,       TP_RD_FAST,   0, NOFUNC, 0, KEIst8,       0, 0},
{IKEIST9,       TP_RD_FAST,   0, NOFUNC, 0, KEIst9,       0, 0},
{IKELINENO,     TP_STD,       0, NOFUNC, 0, KELineNo,     0, 0},
{IKEERROR1,     TP_RD_FAST_D, 0, NOFUNC, 0, KEError1,     0, 0},
{IKEERROR2,     TP_RD_FAST_D, 0, NOFUNC, 0, KEError2,     0, 0},
{IKEERROR3,     TP_RD_FAST_D, 0, NOFUNC, 0, KEError3,     0, 0},
{IKEERROR4,     TP_RD_FAST_D, 0, NOFUNC, 0, KEError4,     0, 0},
{IKEERROR5,     TP_RD_FAST_D, 0, NOFUNC, 0, KEError5,     0, 0},
{IKEERROR6,     TP_RD_FAST_D, 0, NOFUNC, 0, KEError6,     0, 0},
{IKEERROR7,     TP_RD_FAST_D, 0, NOFUNC, 0, KEError7,     0, 0},
{IKEERROR8,     TP_RD_FAST_D, 0, NOFUNC, 0, KEError8,     0, 0},
{IKEERROR9,     TP_RD_FAST_D, 0, NOFUNC, 0, KEError9,     0, 0},
{IKEERROR,      TP_RD_FAST_D, 0, NOFUNC, 0, KEError,      0, 0},
{IKEEVALID,     TP_RD_FAST,   0, NOFUNC, 0, KEEvalid,     0, 0},
{IKEEPOS1,      TP_RD_FAST,   0, NOFUNC, 0, KEExpSoll1,   0, 0},
{IKEEPOS2,      TP_RD_FAST,   0, NOFUNC, 0, KEExpSoll2,   0, 0},
{IKEEPOS3,      TP_RD_FAST,   0, NOFUNC, 0, KEExpSoll3,   0, 0},
{IKEEPOS4,      TP_RD_FAST,   0, NOFUNC, 0, KEExpSoll4,   0, 0},
{IKEEPOS5,      TP_RD_FAST,   0, NOFUNC, 0, KEExpSoll5,   0, 0},
{IKEEPOS6,      TP_RD_FAST,   0, NOFUNC, 0, KEExpSoll6,   0, 0},
{IKEEPOS7,      TP_RD_FAST,   0, NOFUNC, 0, KEExpSoll7,   0, 0},
{IKEEPOS8,      TP_RD_FAST,   0, NOFUNC, 0, KEExpSoll8,   0, 0},
{IKEEPOS9,      TP_RD_FAST,   0, NOFUNC, 0, KEExpSoll9,   0, 0},

/*------------------------ Prozessgrafik ---------------------------------- */
{XPG_WORK,         TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_WORK01,       TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, modework,   0, 0},
{XPG_WORK02,       TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, modework+1, 0, 0},
{XPG_WORK03,       TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, modework+2, 0, 0},
{XPG_WORK04,       TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, modework+3, 0, 0},
/* ------------------------------------------------------------------------ */
{XPG_START_WORK,   TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_START_WORK01, TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, startwork,  0, 0},
{XPG_START_WORK02, TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, startwork+1,0, 0},
{XPG_START_WORK03, TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, startwork+2,0, 0},
{XPG_START_WORK04, TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, startwork+3,0, 0},
/* ------------------------------------------------------------------------ */
{XPG_STOP_WORK,    TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_STOP_WORK01,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, stopwork,   0, 0},
{XPG_STOP_WORK02,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, stopwork+1, 0, 0},
{XPG_STOP_WORK03,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, stopwork+2, 0, 0},
{XPG_STOP_WORK04,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, stopwork+3, 0, 0},
/* ------------------------------------------------------------------------ */
{XPG_IST_WORK,     TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_IST_WORK01,   TP_RD_DINJ,   0, NOFUNC, PPCCOM_CHANNEL2, istwork,    0, 0},
{XPG_IST_WORK02,   TP_RD_DINJ,   0, NOFUNC, PPCCOM_CHANNEL2, istwork+1,  0, 0},
{XPG_IST_WORK03,   TP_RD_DINJ,   0, NOFUNC, PPCCOM_CHANNEL2, istwork+2,  0, 0},
{XPG_IST_WORK04,   TP_RD_DINJ,   0, NOFUNC, PPCCOM_CHANNEL2, istwork+3,  0, 0},
/* ------------------------------------------------------------------------ */
{XPG_REFIST_WORK,  TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_REFIST_WORK01,TP_PGDSK_D_DL,0, NOFUNC, PPCCOM_CHANNEL2, refwork,    0, 0},
{XPG_REFIST_WORK02,TP_PGDSK_D_DL,0, NOFUNC, PPCCOM_CHANNEL2, refwork+1,  0, 0},
{XPG_REFIST_WORK03,TP_PGDSK_D_DL,0, NOFUNC, PPCCOM_CHANNEL2, refwork+2,  0, 0},
{XPG_REFIST_WORK04,TP_PGDSK_D_DL,0, NOFUNC, PPCCOM_CHANNEL2, refwork+3,  0, 0},
/* ------------------------------------------------------------------------ */
{XPG_TOL_WORK,     TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_TOL_WORK01,   TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolwork,    0, 0},
{XPG_TOL_WORK02,   TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolwork+1,  0, 0},
{XPG_TOL_WORK03,   TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolwork+2,  0, 0},
{XPG_TOL_WORK04,   TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolwork+3,  0, 0},
/*------------------------ Prozessgrafik, Anforderung Messwertaufn. ------- */
{XSTARTREC,        TP_STD,       0, NOFUNC, PPCCOM_CHANNEL2, startrec,   0, 0}, 
/* ------------------------------------------------------------------------ */
{XPG_PRES_AREA,    TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_PRES_AREA01,  TP_DL,        0, NOFUNC, PPCCOM_CHANNEL2, pres_area,  0, 0},
{XPG_PRES_AREA02,  TP_DL,        0, NOFUNC, PPCCOM_CHANNEL2, pres_area+1,0, 0},
{XPG_PRES_AREA03,  TP_DL,        0, NOFUNC, PPCCOM_CHANNEL2, pres_area+2,0, 0},
{XPG_PRES_AREA04,  TP_DL,        0, NOFUNC, PPCCOM_CHANNEL2, pres_area+3,0, 0},
/*------------------------ Prozessgrafik, Betriebsart --------------------- */
{XPG_MODE,         TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_MODE01,       TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, pg_mode,    0, 0},
{XPG_MODE02,       TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, pg_mode+1,  0, 0},
{XPG_MODE03,       TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, pg_mode+2,  0, 0},
{XPG_MODE04,       TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, pg_mode+3,  0, 0},
/*------------------------ Prozessgrafik, Messzeit ------------------------ */
{XPG_MEASTIME,     TP_STD,    PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_MEASTIME01,   TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, meastime,   0, 0},
{XPG_MEASTIME02,   TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, meastime+1, 0, 0},
{XPG_MEASTIME03,   TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, meastime+2, 0, 0},
{XPG_MEASTIME04,   TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, meastime+3, 0, 0},
/*------------------------ Prozessgrafik, Intervall ----------------------- */
{XPG_INTERVAL,     TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_INTERVAL01,   TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, interval  , 0, 0},
{XPG_INTERVAL02,   TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, interval+1, 0, 0},
{XPG_INTERVAL03,   TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, interval+2, 0, 0},
{XPG_INTERVAL04,   TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, interval+3, 0, 0},
/*------------------------ Prozessgrafik, Verzoegerungszeit --------------- */
{XPG_DELAY,        TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_DELAY01,      TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, delay,      0, 0},
{XPG_DELAY02,      TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, delay+1,    0, 0},
{XPG_DELAY03,      TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, delay+2,    0, 0},
{XPG_DELAY04,      TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, delay+3,    0, 0},
/*------------------------ Prozessgrafik, Max. Weg fuer x-Achse ----------- */
{XPG_MAXX,         TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_MAXX01,       TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, x_scale,    0, 0},
{XPG_MAXX02,       TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, x_scale+1,  0, 0},
{XPG_MAXX03,       TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, x_scale+2,  0, 0},
{XPG_MAXX04,       TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, x_scale+3,  0, 0},
/*------------------------ Prozessgrafik, Soll-Ist Vergleich durchfuehren - */
{XPG_COMPARE,      TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_COMPARE01,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch, 0, 0},
{XPG_COMPARE02,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+1, 0, 0},
{XPG_COMPARE03,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+2, 0, 0},
{XPG_COMPARE04,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+3, 0, 0},
{XPG_COMPARE05,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+4, 0, 0},
{XPG_COMPARE06,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+5, 0, 0},
{XPG_COMPARE07,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+6, 0, 0},
{XPG_COMPARE08,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+7, 0, 0},
{XPG_COMPARE09,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+8, 0, 0},
{XPG_COMPARE10,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+9, 0, 0},
{XPG_COMPARE11,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+10,0, 0},
{XPG_COMPARE12,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+11,0, 0},
{XPG_COMPARE13,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+12,0, 0},
{XPG_COMPARE14,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+13,0, 0},
{XPG_COMPARE15,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+14,0, 0},
{XPG_COMPARE16,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+15,0, 0},
{XPG_COMPARE17,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+16,0, 0},
{XPG_COMPARE18,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+17,0, 0},
{XPG_COMPARE19,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+18,0, 0},
{XPG_COMPARE20,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+19,0, 0},
{XPG_COMPARE21,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+20,0, 0},
{XPG_COMPARE22,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+21,0, 0},
{XPG_COMPARE23,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+22,0, 0},
{XPG_COMPARE24,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+23,0, 0},
{XPG_COMPARE25,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+24,0, 0},
{XPG_COMPARE26,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+25,0, 0},
{XPG_COMPARE27,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+26,0, 0},
{XPG_COMPARE28,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+27,0, 0},
{XPG_COMPARE29,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+28,0, 0},
{XPG_COMPARE30,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+29,0, 0},
{XPG_COMPARE31,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+30,0, 0},
{XPG_COMPARE32,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+31,0, 0},
{XPG_COMPARE33,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+32,0, 0},
{XPG_COMPARE34,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+33,0, 0},
{XPG_COMPARE35,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+34,0, 0},
{XPG_COMPARE36,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+35,0, 0},
{XPG_COMPARE37,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+36,0, 0},
{XPG_COMPARE38,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+37,0, 0},
{XPG_COMPARE39,    TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tol_switch+38,0, 0},
/*------------------------ Prozessgrafik, Toleranz ------------------------ */
{XPG_TOLERANCE,    TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,           0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_TOLERANCE01,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance   ,0, 0},
{XPG_TOLERANCE02,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+ 1,0, 0},
{XPG_TOLERANCE03,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+ 2,0, 0},
{XPG_TOLERANCE04,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+ 3,0, 0},
{XPG_TOLERANCE05,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+ 4,0, 0},
{XPG_TOLERANCE06,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+ 5,0, 0},
{XPG_TOLERANCE07,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+ 6,0, 0},
{XPG_TOLERANCE08,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+ 7,0, 0},
{XPG_TOLERANCE09,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+ 8,0, 0},
{XPG_TOLERANCE10,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+ 9,0, 0},
{XPG_TOLERANCE11,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+10,0, 0},
{XPG_TOLERANCE12,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+11,0, 0},
{XPG_TOLERANCE13,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+12,0, 0},
{XPG_TOLERANCE14,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+13,0, 0},
{XPG_TOLERANCE15,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+14,0, 0},
{XPG_TOLERANCE16,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+15,0, 0},
{XPG_TOLERANCE17,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+16,0, 0},
{XPG_TOLERANCE18,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+17,0, 0},
{XPG_TOLERANCE19,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+18,0, 0},
{XPG_TOLERANCE20,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+19,0, 0},
{XPG_TOLERANCE21,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+20,0, 0},
{XPG_TOLERANCE22,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+21,0, 0},
{XPG_TOLERANCE23,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+22,0, 0},
{XPG_TOLERANCE24,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+23,0, 0},
{XPG_TOLERANCE25,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+24,0, 0},
{XPG_TOLERANCE26,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+25,0, 0},
{XPG_TOLERANCE27,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+26,0, 0},
{XPG_TOLERANCE28,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+27,0, 0},
{XPG_TOLERANCE29,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+28,0, 0},
{XPG_TOLERANCE30,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+29,0, 0},
{XPG_TOLERANCE31,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+30,0, 0},
{XPG_TOLERANCE32,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+31,0, 0},
{XPG_TOLERANCE33,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+32,0, 0},
{XPG_TOLERANCE34,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+33,0, 0},
{XPG_TOLERANCE35,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+34,0, 0},
{XPG_TOLERANCE36,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+35,0, 0},
{XPG_TOLERANCE37,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+36,0, 0},
{XPG_TOLERANCE38,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+37,0, 0},
{XPG_TOLERANCE39,  TP_PGDSK_DL,  0, NOFUNC, PPCCOM_CHANNEL2, tolerance+38,0, 0},
/*------------------------ Prozessgrafik, Toleranz ------------------------ */
{XPG_YSCAL,        TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_YSCAL01,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal,    0, 0},
{XPG_YSCAL02,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+ 1, 0, 0},
{XPG_YSCAL03,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+ 2, 0, 0},
{XPG_YSCAL04,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+ 3, 0, 0},
{XPG_YSCAL05,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+ 4, 0, 0},
{XPG_YSCAL06,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+ 5, 0, 0},
{XPG_YSCAL07,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+ 6, 0, 0},
{XPG_YSCAL08,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+ 7, 0, 0},
{XPG_YSCAL09,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+ 8, 0, 0},
{XPG_YSCAL10,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+ 9, 0, 0},
{XPG_YSCAL11,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+10, 0, 0},
{XPG_YSCAL12,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+11, 0, 0},
{XPG_YSCAL13,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+12, 0, 0},
{XPG_YSCAL14,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+13, 0, 0},
{XPG_YSCAL15,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+14, 0, 0},
{XPG_YSCAL16,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+15, 0, 0},
{XPG_YSCAL17,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+16, 0, 0},
{XPG_YSCAL18,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+17, 0, 0},
{XPG_YSCAL19,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+18, 0, 0},
{XPG_YSCAL20,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+19, 0, 0},
{XPG_YSCAL21,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+20, 0, 0},
{XPG_YSCAL22,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+21, 0, 0},
{XPG_YSCAL23,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+22, 0, 0},
{XPG_YSCAL24,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+23, 0, 0},
{XPG_YSCAL25,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+24, 0, 0},
{XPG_YSCAL26,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+25, 0, 0},
{XPG_YSCAL27,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+26, 0, 0},
{XPG_YSCAL28,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+27, 0, 0},
{XPG_YSCAL29,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+28, 0, 0},
{XPG_YSCAL30,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+29, 0, 0},
{XPG_YSCAL31,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+30, 0, 0},
{XPG_YSCAL32,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+31, 0, 0},
{XPG_YSCAL33,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+32, 0, 0},
{XPG_YSCAL34,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+33, 0, 0},
{XPG_YSCAL35,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+34, 0, 0},
{XPG_YSCAL36,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+35, 0, 0},
{XPG_YSCAL37,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+36, 0, 0},
{XPG_YSCAL38,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+37, 0, 0},
{XPG_YSCAL39,      TP_PGDSK_DL,PFlt_WHToVS_Soll, NOFUNC, PPCCOM_CHANNEL2, yscal+38, 0, 0},
/*------------------------ Prozessgrafik, Toleranz ------------------------ */
{XPG_YMAX,         TP_STD,   PTabs, NOFUNC, PPCCOM_CHANNEL2, 0,          0, 0},
/*------------------------ Prozessgrafik, Index: FE; FE_NR ---------------- */
{XPG_YMAX01,       TP_PGDSK_DL,  PFlt_XPG_YMAX, NOFUNC, PPCCOM_CHANNEL2, ymax,       0, 0},
{XPG_YMAX02,       TP_PGDSK_DL,  PFlt_XPG_YMAX, NOFUNC, PPCCOM_CHANNEL2, ymax+1,     0, 0},
{XPG_YMAX03,       TP_PGDSK_DL,  PFlt_XPG_YMAX, NOFUNC, PPCCOM_CHANNEL2, ymax+2,     0, 0},
{XPG_YMAX04,       TP_PGDSK_DL,  PFlt_XPG_YMAX, NOFUNC, PPCCOM_CHANNEL2, ymax+3,     0, 0},
/* ------------------------------------------------------------------------ */
{XPG_TOL_ERRS,     TP_STD,       0, NOFUNC, PPCCOM_CHANNEL2, tol_errs,   0, 0},
/* ------------------------------------------------------------------------ */
{XPG_FREE_REG0,    TP_STD,       0, NOFUNC, PPCCOM_CHANNEL2, free_reg0,  0, 0},
{XPG_FREE_REG1,    TP_STD,       0, NOFUNC, PPCCOM_CHANNEL2, free_reg1,  0, 0},
{XPG_FREE_REG2,    TP_STD,       0, NOFUNC, PPCCOM_CHANNEL2, free_reg2,  0, 0},
{XPG_FREE_REG3,    TP_STD,       0, NOFUNC, PPCCOM_CHANNEL2, free_reg3,  0, 0},
{XPG_FREE_REG4,    TP_STD,       0, NOFUNC, PPCCOM_CHANNEL2, free_reg4,  0, 0},
{XPG_FREE_REG5,    TP_STD,       0, NOFUNC, PPCCOM_CHANNEL2, free_reg5,  0, 0},
{XPG_FREE_REG6,    TP_STD,       0, NOFUNC, PPCCOM_CHANNEL2, free_reg6,  0, 0},
{XPG_FREE_REG7,    TP_STD,       0, NOFUNC, PPCCOM_CHANNEL2, free_reg7,  0, 0},
{XPG_FREE_REG8,    TP_STD,       0, NOFUNC, PPCCOM_CHANNEL2, free_reg8,  0, 0},
{XPG_FREE_REG9,    TP_STD,       0, NOFUNC, PPCCOM_CHANNEL2, free_reg9,  0, 0},
/* ----------------------- Werkzeug Wenden -------------------------------- */
{XWDM_BETART,      TP_DSK_BG_DL, 0, NOFUNC, 0,               WDm_Betart, 0, 0},
{XWDM_STAPKT,      TP_DSK_BG_DL, 0, NOFUNC, 0,               WDm_Stapkt, 0, 0},
{XWDSTVERZ,        TP_DSK_BG_DL, 0, NOFUNC, 0,               WDstVerz,   0, 0},
{XWDSV11,          TP_DSK_BG_DL, 0, NOFUNC, 0,               WDsv11,     0, 0},
{XWDSV12,          TP_DSK_BG_DL, 0, NOFUNC, 0,               WDsv12,     0, 0},
{XWDSV21,          TP_DSK_BG_DL, 0, NOFUNC, 0,               WDsv21,     0, 0},
{XWDSV22,          TP_DSK_BG_DL, 0, NOFUNC, 0,               WDsv22,     0, 0},
{XWDSP11,          TP_DSK_BG_DL, 0, NOFUNC, 0,               WDsp11,     0, 0},
{XWDSP12,          TP_DSK_BG_DL, 0, NOFUNC, 0,               WDsp12,     0, 0},
{XWDSP21,          TP_DSK_BG_DL, 0, NOFUNC, 0,               WDsp21,     0, 0},
{XWDSP22,          TP_DSK_BG_DL, 0, NOFUNC, 0,               WDsp22,     0, 0},
{XWDSVEINRGR,      TP_DSK_BG_DL, 0, NOFUNC, 0,               WDsvEinrgr, 0, 0},
{XWDSVGEREG,       TP_DSK_BG_DL, 0, NOFUNC, 0,               WDsvgereg,  0, 0},
{XWDST,            TP_RD_FAST,   0, NOFUNC, 0,               WDst,       0, 0},
/* ----------------------- Werkzeug Drehteller-Parameter ------------------ */
{XDTISABS,         TP_RD_SPEC,   0, NOFUNC, 0,               DTisAbs,    0, 0},
{XDTISRELA,        TP_RD_SPEC,   0, NOFUNC, 0,               DTisRela,   0, 0},
{XDTSABESCHL,      TP_STD,       0, NOFUNC, 0,               DTsaBeschl, 0, 0},
{XDTIABESCHL,      TP_RD_SPEC,   0, NOFUNC, 0,               DTiaBeschl, 0, 0},
{XDTSTVERZ,        TP_STD,       0, NOFUNC, 0,               DTstVerz,   0, 0},
{XDTITVERZ,        TP_RD_SPEC,   0, NOFUNC, 0,               DTitVerz,   0, 0},
{XDTS_VOFF1,       TP_STD,       0, NOFUNC, 0,               DTs_VOff1,  0, 0},
{XDTI_VOFF1,       TP_RD_SPEC,   0, NOFUNC, 0,               DTi_VOff1,  0, 0},
{XDTS_VOFF2,       TP_STD,       0, NOFUNC, 0,               DTs_VOff2,  0, 0},
{XDTI_VOFF2,       TP_RD_SPEC,   0, NOFUNC, 0,               DTi_VOff2,  0, 0},
{XDTS_SKGES,       TP_STD,       0, NOFUNC, 0,               DTs_Skges,  0, 0},
{XDTI_SKGES,       TP_RD_SPEC,   0, NOFUNC, 0,               DTi_Skges,  0, 0},
{XDTS_SKGER,       TP_STD,       0, NOFUNC, 0,               DTs_Skger,  0, 0},
{XDTI_SKGER,       TP_RD_SPEC,   0, NOFUNC, 0,               DTi_Skger,  0, 0},
{XDTS_ZIELF,       TP_STD,       0, NOFUNC, 0,               DTs_Zielf,  0, 0},
{XDTI_ZIELF,       TP_RD_SPEC,   0, NOFUNC, 0,               DTi_Zielf,  0, 0},
{XDTS_SWEITE,      TP_STD,       0, NOFUNC, 0,               DTs_Sweite, 0, 0},
{XDTI_SWEITE,      TP_RD_SPEC,   0, NOFUNC, 0,               DTi_Sweite, 0, 0},
/* ----------------------- Werkzeugauswerfer ------------------------------ */
{XWZA_BA,          TP_DSK_BG_DL, 0, NOFUNC, 0,               WZA_BA,     0, 0},
{XWZA_SPKTV,       TP_DSK_BG_DL, 0, NOFUNC, 0,               WZA_Spktv,  0, 0},
{XWZA_AUSWH,       TP_DSK_BG_DL, 0, NOFUNC, 0,               WZA_Auswh,  0, 0},
{XWZA_WZVOR,       TP_DSK_BG_DL, 0, NOFUNC, 0,               WZA_Wzvor,  0, 0},
{XWZA_AKZVOR,      TP_DSK_BG_DL, 0, NOFUNC, 0,               WZA_Akzvor, 0, 0},
{XWZA_AKZZUR,      TP_DSK_BG_DL, 0, NOFUNC, 0,               WZA_Akzzur, 0, 0},
{XWZAPVOR,         TP_DSK_BG_DL, 0, NOFUNC, 0,               WZApvor,    0, 0},
{XWZAPZUR,         TP_DSK_BG_DL, 0, NOFUNC, 0,               WZApzur,    0, 0},
{XWZAVVOR1,        TP_DSK_BG_DL, 0, NOFUNC, 0,               WZAvvor1,   0, 0},
{XWZAVVOR2,        TP_DSK_BG_DL, 0, NOFUNC, 0,               WZAvvor2,   0, 0},
{XWZAVZUR,         TP_DSK_BG_DL, 0, NOFUNC, 0,               WZAvzur,    0, 0},
{XDTGENMOD,        TP_STD,       0, NOFUNC, 0,               DTGenMod,   0, 0},
/* ----------------------- Werkzeugauswerfer ------------------------------ */
{XWZA_BA_FHK,      TP_DSK_BG_DL, 0, NOFUNC, 0,               WZA_BA_FHK, 0, 0},
{XWZA_BA2,         TP_DSK_BG_DL, 0, NOFUNC, 0,               WZA_BA2,    0, 0},
{XWZA_SPKTV2,      TP_DSK_BG_DL, 0, NOFUNC, 0,               WZA_Spktv2, 0, 0},
{XWZA_AUSWH2,      TP_DSK_BG_DL, 0, NOFUNC, 0,               WZA_Auswh2, 0, 0},
{XWZA_WZVOR2,      TP_DSK_BG_DL, 0, NOFUNC, 0,               WZA_Wzvor2, 0, 0},
{XWZA_AKZVOR2,     TP_DSK_BG_DL, 0, NOFUNC, 0,               WZA_Akzvo2, 0, 0},
{XWZA_AKZZUR2,     TP_DSK_BG_DL, 0, NOFUNC, 0,               WZA_Akzzu2, 0, 0},
{XWZAPVOR2,        TP_DSK_BG_DL, 0, NOFUNC, 0,               WZApvor2,   0, 0},
{XWZAPZUR2,        TP_DSK_BG_DL, 0, NOFUNC, 0,               WZApzur2,   0, 0},
{XWZAVVOR12,       TP_DSK_BG_DL, 0, NOFUNC, 0,               WZAvvor12,  0, 0},
{XWZAVVOR22,       TP_DSK_BG_DL, 0, NOFUNC, 0,               WZAvvor22,  0, 0},
{XWZAVZUR2,        TP_DSK_BG_DL, 0, NOFUNC, 0,               WZAvzur2,   0, 0},
/* ----------------------- Werkzeug Wenden mit CAN-Winkelkodierer --------- */
{XDTS_NUM,         TP_D,         0, NOFUNC, 0,               DTs_Num,    0, 0},
{XDTI_NUM,         TP_RD_LSPEC,  0, NOFUNC, 0,               DTi_Num,    0, 0},
/*------------------------ Heizungsregister Zylinderheizung --------------- */
{INJHEAT_SOLL,            TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_TOL_WIDE_DOWN,   TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_TOL_NARROW_DOWN, TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_TOL_WIDE_UP,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_TOL_NARROW_UP,   TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_MCW,             TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_XPH,             TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_XPK,             TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_TN,              TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_TV,              TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_HEAT_PERIOD,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_COOL_PERIOD,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_HYST,            TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_WORK_POINT,      TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_MIN_STELL,       TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_MAX_STELL,       TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_MOTOR_TIME,      TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_STELL_PERIOD,    TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_ON_OFF,          TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_CURRENT_SOLL,    TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_SOLL_STELL,      TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_THERM_TYPE,      TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_MEASURE_SWITCH,  TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_FUNCTION,        TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_LOOP_NUMBER,     TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_CONVERTER_TYPE,  TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_IST,             TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_ED,              TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_CURRENT_IST,     TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{INJHEAT_OPTMODE,         TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
/*------------------------ Heizungsregister Werkzeugheizung --------------- */
{TOOLHEAT_SOLL,           TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_TOL_WIDE_DOWN,  TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_TOL_NARROW_DOWN,TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_TOL_WIDE_UP,    TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_TOL_NARROW_UP,  TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_MCW,            TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_XPH,            TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_XPK,            TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_TN,             TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_TV,             TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_HEAT_PERIOD,    TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_COOL_PERIOD,    TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_HYST,           TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_WORK_POINT,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_MIN_STELL,      TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_MAX_STELL,      TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_MOTOR_TIME,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_STELL_PERIOD,   TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_ON_OFF,         TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_CURRENT_SOLL,   TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_SOLL_STELL,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_THERM_TYPE,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_MEASURE_SWITCH, TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_FUNCTION,       TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_LOOP_NUMBER,    TP_DSK,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_CONVERTER_TYPE, TP_DSK,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_IST,            TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_ED,             TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_CURRENT_IST,    TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TOOLHEAT_OPTMODE,        TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
/*------------------------ Heizungsregister Temperiergeraete -------------- */
{TEMPHEAT_SOLL,           TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_TOL_WIDE_DOWN,  TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_TOL_NARROW_DOWN,TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_TOL_WIDE_UP,    TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_TOL_NARROW_UP,  TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_MCW,            TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_XPH,            TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_XPK,            TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_TN,             TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_TV,             TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_HEAT_PERIOD,    TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_COOL_PERIOD,    TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_HYST,           TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_WORK_POINT,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_MIN_STELL,      TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_MAX_STELL,      TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_MOTOR_TIME,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_STELL_PERIOD,   TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_ON_OFF,         TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_CURRENT_SOLL,   TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_SOLL_STELL,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_THERM_TYPE,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_MEASURE_SWITCH, TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_FUNCTION,       TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_LOOP_NUMBER,    TP_DSK,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_CONVERTER_TYPE, TP_DSK,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_IST,            TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_ED,             TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_CURRENT_IST,    TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{TEMPHEAT_OPTMODE,        TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
/*------------------------ Heizungsregister Oelvorwaermung ---------------- */
{OILHEAT_SOLL,            TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_TOL_WIDE_DOWN,   TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_TOL_NARROW_DOWN, TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_TOL_WIDE_UP,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_TOL_NARROW_UP,   TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_MCW,             TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_XPH,             TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_XPK,             TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_TN,              TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_TV,              TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_HEAT_PERIOD,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_COOL_PERIOD,     TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_HYST,            TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_WORK_POINT,      TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_MIN_STELL,       TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_MAX_STELL,       TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_MOTOR_TIME,      TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_STELL_PERIOD,    TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_ON_OFF,          TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_CURRENT_SOLL,    TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_SOLL_STELL,      TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_THERM_TYPE,      TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_MEASURE_SWITCH,  TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_FUNCTION,        TP_DSK_BG, PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_LOOP_NUMBER,     TP_DSK,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_CONVERTER_TYPE,  TP_DSK,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_IST,             TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_ED,              TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_CURRENT_IST,     TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{OILHEAT_OPTMODE,         TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
/*-- Allgem. Heizungsregister, Zugriff mit Reglernummer als ersten Index -- */
{GENHEAT_SOLL,            TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_TOL_WIDE_DOWN,   TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_TOL_NARROW_DOWN, TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_TOL_WIDE_UP,     TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_TOL_NARROW_UP,   TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_MCW,             TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_XPH,             TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_XPK,             TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_TN,              TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_TV,              TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_HEAT_PERIOD,     TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_COOL_PERIOD,     TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_HYST,            TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_WORK_POINT,      TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_MIN_STELL,       TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_MAX_STELL,       TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_MOTOR_TIME,      TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_STELL_PERIOD,    TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_ON_OFF,          TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_CURRENT_SOLL,    TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_SOLL_STELL,      TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_THERM_TYPE,      TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_MEASURE_SWITCH,  TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_FUNCTION,        TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_LOOP_NUMBER,     TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_CONVERTER_TYPE,  TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_IST,             TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_ED,              TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_CURRENT_IST,     TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{GENHEAT_OPTMODE,         TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
/* ----- Reserve-Heizungsgruppe, Zugriff wie auf TEMPHEAT und TOOLHEAT ---- */
{RESHEAT_SOLL,            TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_TOL_WIDE_DOWN,   TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_TOL_NARROW_DOWN, TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_TOL_WIDE_UP,     TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_TOL_NARROW_UP,   TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_MCW,             TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_XPH,             TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_XPK,             TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_TN,              TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_TV,              TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_HEAT_PERIOD,     TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_COOL_PERIOD,     TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_HYST,            TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_WORK_POINT,      TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_MIN_STELL,       TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_MAX_STELL,       TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_MOTOR_TIME,      TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_STELL_PERIOD,    TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_ON_OFF,          TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_CURRENT_SOLL,    TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_SOLL_STELL,      TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_THERM_TYPE,      TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_MEASURE_SWITCH,  TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_FUNCTION,        TP_BG,     PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_LOOP_NUMBER,     TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_CONVERTER_TYPE,  TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_IST,             TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_ED,              TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_CURRENT_IST,     TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
{RESHEAT_OPTMODE,         TP_STD,    PHeatFltFunc, NOFUNC, 0, 0,         0, 0},
/*----------------- Airpress ---------------------------------------------- */
{XRAMPE1_D1,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp1D1,   0, 0}, 
{XRAMPE1_D2,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp1D2,   0, 0}, 
{XRAMPE1_D3,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp1D3,   0, 0}, 
{XRAMPE1_D4,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp1D4,   0, 0}, 
{XRAMPE2_D1,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp2D1,   0, 0}, 
{XRAMPE2_D2,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp2D2,   0, 0}, 
{XRAMPE2_D3,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp2D3,   0, 0}, 
{XRAMPE2_D4,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp2D4,   0, 0}, 
{XRAMPE3_D1,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp3D1,   0, 0}, 
{XRAMPE3_D2,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp3D2,   0, 0}, 
{XRAMPE3_D3,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp3D3,   0, 0}, 
{XRAMPE3_D4,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp3D4,   0, 0}, 
{XRAMPE4_D1,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp4D1,   0, 0}, 
{XRAMPE4_D2,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp4D2,   0, 0}, 
{XRAMPE4_D3,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp4D3,   0, 0}, 
{XRAMPE4_D4,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp4D4,   0, 0}, 
{XRAMPE5_D1,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp5D1,   0, 0}, 
{XRAMPE5_D2,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp5D2,   0, 0}, 
{XRAMPE5_D3,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp5D3,   0, 0},   
{XRAMPE5_D4,    TP_DSK_BG_DL, 0, NOFUNC, 0, APstRmp5D4,   0, 0},   
/* ------------------------------------------------------------------------ */
{XWKZDUES_D1,   TP_DSK_BG_DL, 0, NOFUNC, 0, WKZDues_D1,   0, 0}, 
{XWKZDUES_D2,   TP_DSK_BG_DL, 0, NOFUNC, 0, WKZDues_D2,   0, 0}, 
{XWKZDUES_D3,   TP_DSK_BG_DL, 0, NOFUNC, 0, WKZDues_D3,   0, 0},   
{XWKZDUES_D4,   TP_DSK_BG_DL, 0, NOFUNC, 0, WKZDues_D4,   0, 0}, 
/* ------------------------------------------------------------------------ */
/*-- fuer S. 66.0 - 66.2 Konfigurierbare digitale/analoge  Ein-/Ausgaenge --*/
{IOINDIIST,               TP_RD_FAST,      0, NOFUNC, 0, IOinDIist,      0, 0},
{IOINDOIST,               TP_RD_FAST,      0, NOFUNC, 0, IOinDOist,      0, 0},
/* ------------------------------------------------------------------------ */                                                       
{IOS_DIFKT1,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOs_DIfkt1,     0, 0},
{IOS_DIFKT2,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOs_DIfkt2,     0, 0},
{IOS_DIFKT3,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOs_DIfkt3,     0, 0},
{IOS_DIFKT4,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOs_DIfkt4,     0, 0},
/* ------------------------------------------------------------------------ */                                                       
{IOS_DOFKT1,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOs_DOfkt1,     0, 0},
{IOS_DOFKT2,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOs_DOfkt2,     0, 0},
{IOS_DOFKT3,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOs_DOfkt3,     0, 0},
{IOS_DOFKT4,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOs_DOfkt4,     0, 0},
/* ------------------------------------------------------------------------ */                                                             
{IOSTDOAKT1,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOstDOakt1,     0, 0},
{IOSTDOAKT2,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOstDOakt2,     0, 0},
{IOSTDOAKT3,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOstDOakt3,     0, 0},
{IOSTDOAKT4,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOstDOakt4,     0, 0},
/* ------------------------------------------------------------------------ */                                                             
{IOSNDOPAR1,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnDOpar1,     0, 0},
{IOSNDOPAR2,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnDOpar2,     0, 0},
{IOSNDOPAR3,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnDOpar3,     0, 0},
{IOSNDOPAR4,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnDOpar4,     0, 0},
/* ------------------------------------------------------------------------ */                                                       
{IOS_AOFKT1,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOs_AOfkt1,     0, 0},
{IOS_AOFKT2,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOs_AOfkt2,     0, 0},
{IOS_AOFKT3,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOs_AOfkt3,     0, 0},
{IOS_AOFKT4,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOs_AOfkt4,     0, 0},
/* ------------------------------------------------------------------------ */                          
{IOINAOIST1,              TP_RD_FAST,      0, NOFUNC, 0, IOinAOist1, 0, 0},
{IOINAOIST2,              TP_RD_FAST,      0, NOFUNC, 0, IOinAOist2, 0, 0},
{IOINAOIST3,              TP_RD_FAST,      0, NOFUNC, 0, IOinAOist3, 0, 0},
{IOINAOIST4,              TP_RD_FAST,      0, NOFUNC, 0, IOinAOist4, 0, 0},
/* ------------------------------------------------------------------------ */
{SZINSUB,                 TP_D_DL,         0, NOFUNC, 0, SZinSUB,        0, 0},
{BA_FOER,                 TP_DSK_BG_DL,    0, NOFUNC, 0, BA_foer,        0, 0}, 
{FBST,                    TP_DSK_BG_DL,    0, NOFUNC, 0, FBst   ,        0, 0},
/* ------------------------------------------------------------------------ */
{IOSNDOPA21,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnDOpa21,     0, 0},
{IOSNDOPA22,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnDOpa22,     0, 0},
{IOSNDOPA23,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnDOpa23,     0, 0},
{IOSNDOPA24,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnDOpa24,     0, 0},
/* ------------------------------------------------------------------------ */
{IOSNDIPAR1,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnDIpar1,     0, 0},
{IOSNDIPAR2,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnDIpar2,     0, 0},
{IOSNDIPAR3,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnDIpar3,     0, 0},
{IOSNDIPAR4,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnDIpar4,     0, 0},
/* ------------------------------------------------------------------------ */
{IOSNAOPAR1,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnAOpar1,     0, 0},
{IOSNAOPAR2,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnAOpar2,     0, 0},
{IOSNAOPAR3,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnAOpar3,     0, 0},
{IOSNAOPAR4,              TP_DSK_BG_DL,    0, NOFUNC, 0, IOsnAOpar4,     0, 0},
/* ------------------------------------------------------------------------ */
{0xffff}                            /* ENDEKENNUNG: muss IMMER da sein */
};

