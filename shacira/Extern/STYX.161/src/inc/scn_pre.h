/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [scn_pre.h]           STYX-konform preprocessing                         */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/* export prefix "SPP_" */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef scn_pre_INCL
#define scn_pre_INCL


#include "standard.h"
#include "symbols.h"
#include "hmap.h"
#include "scn_base.h"


#ifdef __cplusplus
extern "C" {
#endif


/* 
  <p>The STYX system comes up with a macro preprocessing facility -
  <br>based on the following macro definition syntax and evaluation process
  during the lexical analysis:
  <p><table cellspacing=10 noborder>
  <tr>
  <td><b>#include</b> Path</td>
  <td>supports modular grammar design
  <br>The macro will be replaced by the content of source file 'Path' and
      then rescanned.
  </td>
  </tr>
  <tr>
  <td><b>#macro</b> Name ( FormalParameter , ... ) = Text <b>#end</b></td>
  <td>supports text replacement
  <br>Parameter and replacement text are optional.
  <br>The macro will be collected by the preprocessing module and
      skipped by the scanner.
  <br>A macro expression ( Name ActualParameter Delimiter ... ) will be
      replaced by the previous definition and then rescanned.
  </td>
  </tr>
  <tr>
  <td>' Delimiter</td>
  <td>introduces another - the second - character as delimiter for the
      actual macro parameter.
  <br>Spaces will be used as default delimiter.
      To reactive the default behaviour specify ' -.
  <br>The scanner skips these token.
  </td>
  </tr>
  <tr>
  <td><b>#undefine</b> Name</td>
  <td>revokes a previous definition
  </td>
  </tr>
  <tr>
  <td><b>#if[n]def</b> Name IfPart <b>#else</b> ElsePart <b>#end</b></td>
  <td>supports conditional parsing
  <br>Dependant on the existence of macro 'Name' the scanner skips the
      'ElsePart' or 'IfPart'.
  <br>Its possible to introduce environment variables as macros.
  </td>
  </tr>
  </table>
  <br>
  <p>You can use this preprocessing facility if your regular grammar defines
  the above kind of macros in the same way -
  <br>apart from token names and keywords.
  ( see below and <a href="styx_cfg.htm"><b>styx</b> reference</a> )
  <br>
  <p>Note:
  <p>The reentrant version of the preprocessing module expects that the
     preprocessor ( constructed by the function 'SPP_init_reentrant' )
     will be added to the scan stream as value of the context variable 'SPP_premac'.
  <br>
*/

/* -------------------- Types & Macros ------------------------------------ */

AbstractType( SPP_T )  /* Abstract preprocessing type */
;

/* 
  <p><b>Identifier for the ( macro ) token names</b>
*/

#define SPP_TOK_IDE         0 // Identifier
#define SPP_TOK_MACDFN      1 // Macro
#define SPP_TOK_MACSEP      2 // Delimiter
#define SPP_TOK_MACINC      3 // Include
#define SPP_TOK_MACCOND     4 // Condition
#define SPP_TOK_MACDEL      5 // Undefine

/* 
  <p><b>Identifier for macro token keywords</b>
*/

#define SPP_PAT_START       6  // #macro
#define SPP_PAT_END         7  // #end
#define SPP_PAT_IFDEF       8  // #ifdef
#define SPP_PAT_IFNDEF      9  // #ifndef
#define SPP_PAT_ELSE        10 // #else
#define SPP_PAT_INC         11 // #include
#define SPP_PAT_UNDEFINE    12 // #undefine
#define SPP_PAT_ENDIF       13 // #endif

/* 
  <p><b>Identifier for include path and character set</b>
*/

#define SPP_INC_PATH        14
#define SPP_INC_CHARSET     15

/* -------------------- Macro Expansion ----------------------------------- */

void SPP_init(MAP(long,symbol) pPreParMap)
/* initializes STYX-konform macro preprocessing
   'pPreParMap': re-definitions for macro token names,
                 initial macro token keywords,
                 include path and characterset
*/
;

SPP_T SPP_init_reentrant(MAP(long,symbol) pPreParMap)
/* reentrant version of SPP_init */
;

void SPP_addCtxMacro(symbol pMacNam)
/* adds ( lower case symbol ) 'pMacNam' as pre-defined macro */
;

void SPP_addCtxMacro_reentrant(SPP_T pPP, symbol pMacNam)
/* reentrant version of SPP_addCtxMacro */
;

void SPP_quit(void);         /* terminates STYX-konform macro preprocessing */
void SPP_quit_reentrant(SPP_T pPP);    /* reentrant version of SPP_quit     */

int SPP_premac
    (
      Scn_Stream pStream, c_string cTokNam, c_string cTokVal, symbol* cMacVal
    )
/* preprocesses current token of non-binary scan stream 'pStream'
   'cTokNam': name of separated token
   'cTokVal': value of separated token
   'cMacVal': preprocessing result ( see [scn_base] )
   ( cTokNam, cTokVal: single byte or utf-8 characterset )
*/
;



#ifdef __cplusplus
}
#endif

#endif