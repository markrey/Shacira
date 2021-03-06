/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [bnf.h]                      Type: BNF                                   */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef bnf_INCL
#define bnf_INCL


#include "prs_dfn.h"


#ifdef __cplusplus
extern "C" {
#endif


/*  
   [bnf] implements a more abstract interface to the more technical definition
   of a context free grammar, provided by the above parse module [prs].
*/

/* ---------------------- Types --------------------------------------------- */

AbstractType(BNF_BNF); /* Abstract BNF type               */
AbstractType(BNF_NTM); /* Abstract nonterminal type       */
AbstractType(BNF_TOK); /* Abstract token type             */
AbstractType(BNF_KEY); /* Abstract keyword type           */
AbstractType(BNF_PRD); /* Abstract production type        */
AbstractType(BNF_MBR); /* Abstract production symbol type */

/* --------------------------- Create & Delete ------------------------------ */

BNF_BNF BNF_create(PLR_Tab PTab)
/* creates a BNF-view from the parse table 'PTab' */
;

void BNF_delBNF(BNF_BNF Bnf);          /* deletes BNF-view 'Bnf'            */

/* ---------------------------- Access to BNF-view -------------------------- */

/* ------------------------ Language and startsymbols ----------------------- */

c_string BNF_language(BNF_BNF Bnf);    /* Language name                     */
int      BNF_startCnt(BNF_BNF Bnf);    /* Number of startsymbols            */
BNF_NTM BNF_startNth(BNF_BNF Bnf, int Nth); /* Nth startsymbol ( Nth >= 1 ) */

/* ---------------------------- Nonterminals -------------------------------- */

int     BNF_ntCnt(BNF_BNF Bnf);          /* Number of nonterminals          */
BNF_NTM BNF_ntNth(BNF_BNF Bnf, int Nth); /* Nth nonterminal ( Nth >= 1 )    */
int      BNF_ntIntern(BNF_BNF Bnf, BNF_NTM Nt); /* Nonterminal to symbol id */
c_string BNF_ntName(BNF_BNF Bnf, BNF_NTM Nt);   /* Nonterminal to name      */
BNF_NTM BNF_ntId(BNF_BNF Bnf, c_string NtName); /* Name to nonterminal      */
BNF_NTM BNF_internNt(BNF_BNF Bnf, int symbol);  /* Symbol id to nonterminal */

/* ---------------------------- Productions --------------------------------- */

int      BNF_ntProdCnt(BNF_BNF Bnf, BNF_NTM Nt);   /* Number of productions */

BNF_PRD BNF_ntProdNth(BNF_BNF Bnf, BNF_NTM Nt, int Nth)
/* Nth production ( Nth >= 1 ) */
;

int      BNF_prodIntern(BNF_BNF Bnf, BNF_PRD Prd); /* Production to id      */
c_string BNF_prodName(BNF_BNF Bnf, BNF_PRD Prd);   /* Production to name    */

BNF_PRD BNF_ntProdId(BNF_BNF Bnf, BNF_NTM Nt, c_string ProdName)
/* Name to production */
;

BNF_NTM BNF_prodNtId(BNF_BNF Bnf, BNF_PRD Prd);  /* Production nonterminal  */
BNF_PRD BNF_internProd(BNF_BNF Bnf, int symbol); /* Id to production        */

/* ------------------------ Production symbols ------------------------------ */

int BNF_prodMbrCnt(BNF_BNF Bnf, BNF_PRD Prd)
/* Number of production symbols */
;

BNF_MBR BNF_prodMbrNth(BNF_BNF Bnf, BNF_PRD Prd, int Nth)
/* Nth production symbol ( Nth >= 1 ) */
;

c_bool BNF_isMbrNtm(BNF_BNF Bnf, BNF_MBR Mbr)
/* Production symbol is nonterminal ? */
;

c_bool BNF_isMbrTok(BNF_BNF Bnf, BNF_MBR Mbr)
/* Production symbol is token ? */
;

c_bool BNF_isMbrKey(BNF_BNF Bnf, BNF_MBR Mbr)
/* Production symbol is keyword ? */
;

BNF_NTM BNF_MbrNtm(BNF_BNF Bnf, BNF_MBR Mbr)
/* Production symbol to nonterminal */
;

BNF_TOK BNF_MbrTok(BNF_BNF Bnf, BNF_MBR Mbr); /* Production symbol to token */

BNF_KEY BNF_MbrKey(BNF_BNF Bnf, BNF_MBR Mbr)
/* Production symbol to keyword */
;


/* -------------------------------- Tokens ---------------------------------- */

int      BNF_tokCnt(BNF_BNF Bnf);                 /* Number of tokens       */
BNF_TOK  BNF_tokNth(BNF_BNF Bnf, int Nth);        /* Nth token ( Nth >= 1 ) */
int      BNF_tokIntern(BNF_BNF Bnf, BNF_TOK Tok); /* Token to symbol id     */
c_string BNF_tokName(BNF_BNF Bnf, BNF_TOK Tok);   /* Token to name          */
BNF_TOK BNF_tokId(BNF_BNF Bnf, c_string TokName); /* Name to token          */
BNF_TOK BNF_internTok(BNF_BNF Bnf, int symbol);   /* Symbol id to token     */

/* ------------------------------- Keywords --------------------------------- */

int     BNF_keyCnt(BNF_BNF Bnf);          /* Number of keywords             */
BNF_KEY BNF_keyNth(BNF_BNF Bnf, int Nth); /* Nth keyword ( Nth >= 1 )       */
int      BNF_keyIntern(BNF_BNF Bnf, BNF_KEY Key);  /* Keyword to symbol id  */
c_string BNF_keyName(BNF_BNF Bnf, BNF_KEY Key);    /* Keyword to name       */
BNF_KEY  BNF_keyId(BNF_BNF Bnf, c_string KeyName); /* Name to keyword       */
BNF_KEY  BNF_internKey(BNF_BNF Bnf, int symbol);   /* Symbol id to keyword  */


#ifdef __cplusplus
}
#endif

#endif
