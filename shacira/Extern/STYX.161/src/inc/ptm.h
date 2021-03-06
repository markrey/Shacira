/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [ptm.h]                   Type: Parse Tree / Term                        */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef ptm_INCL
#define ptm_INCL


#include "otab.h"
#include "binimg.h"
#include "list.h"
#include "sink.h"


#ifdef __cplusplus
extern "C" {
#endif


/* ============================ Parse Tree ================================ */

/*  
   [ptm] implements the parse i.e. derivation tree as special term data type.

   Term representation

     Three forms of term representation are supported by the construction functions.

     C: This is an efficient representation which lacks an explicit list node
        for the childs of a nonterminal node.

     Xaron: This is a Lisp-like representation with an explicit list node
            for the childs of a nonterminal node. ( used by the xaron project )

     ABS: This is a special optimized representation of the abstract parse tree only
          with all keywords and comments discarded. For a traversal of the tree you
          must use the abstract variant of the generated function interface.

   Definition of the symbol position

     1. Terminal         : Position of the first terminal character
     2. Nonterminal      : Position of the first terminal character if exists
     3. Empty production : Position of the first character of the next terminal
*/

/* ------------------------ Types ------------------------------------------- */

AbstractType(PT_Term); /* Abstract parse tree type          */
AbstractType(PT_Itr);  /* Abstract parse tree iterator type */

/* ----------------------- Construction & Disposing ------------------------- */

PT_Term PT_newTNode(symbol cfgsym, short symcls, symbol value)
/* C: creates a node for
      token 'cfgsym' of type 'symcls' and 'value'
*/
;

PT_Term XPT_newTNode(symbol cfgsym, short symcls, symbol value)
/* Xaron: creates a node for
          token 'cfgsym' of type 'symcls' and 'value'
*/
;

PT_Term PT_newNtNode(symbol cfgsym, symbol prdsym, PT_Term parts)
/* C: creates a node for nonterminal 'cfgsym',
      production 'prdsym' and child nodes 'parts'
*/
;

PT_Term XPT_newNtNode(symbol cfgsym, symbol prdsym, List(PT_Term) parts)
/* Xaron: creates a node for nonterminal 'cfgsym',
          production 'prdsym' and child nodes 'parts'
*/
;

PT_Term PT_updVal(PT_Term PTree, Any_T value)
/* updates token node 'PTree' with 'value'; returns 'PTree' */
;

PT_Term PT_updPos(PT_Term PTree, symbol file, long row, long col)
/* updates node 'PTree' with the position 'file', 'row' and 'col';
   returns 'PTree'
*/
;

PT_Term PT_consT(PT_Term left, PT_Term right)
/* C: child node concatenation:
      child list = cons('left','right')
*/
;

List(PT_Term) XPT_consT(PT_Term left, List(PT_Term) right)
/* Xaron: child node concatenation:
          child list = cons('left','right')
*/
;

PT_Term PT_copyPos(PT_Term left, PT_Term right)
/* assigns position of node 'right' to node 'left';
   returns 'left'
*/
;

PT_Term PT_copyNode(PT_Term PTree)
/* copies node 'PTree' ( without child nodes ) */
;

void PT_delT(PT_Term PTree);           /* removes parse tree / term 'PTree' */

/* ----------------------- Accessing ---------------------------------------- */

/* 
  <p><b>Recognizer</b>
*/

c_bool PT_isXaron(PT_Term PTree)
/* whether 'PTree' is a Xaron-konform parse tree / term */
;

c_bool PT_isNonTerm(PT_Term PTree)
/* whether 'PTree' starts with a nonterminal node */
;

c_bool PT_isCFG(PT_Term PTree)
/* whether 'PTree' is an embedded language node */
;

c_bool PT_isToken(PT_Term PTree);      /* whether 'PTree' is a token node   */
c_bool PT_isKey(PT_Term PTree);        /* whether 'PTree' is a keyword node */
c_bool PT_isComment(PT_Term PTree);    /* whether 'PTree' is a comment node */

c_bool PT_hasPos(PT_Term PTree)
/* whether node 'PTree' contains position informations */
;


/* 
  <p><b>Selection</b>
*/

symbol PT_product(PT_Term PTree)
/* production symbol of node 'PTree';
   assertion: PT_isNonTerm(PTree)
*/
;

symbol PT_symbol(PT_Term PTree);       /* symbol of node 'PTree' ( NT,T )   */

short PT_symtyp(PT_Term PTree)
/* symbol type of node 'PTree' ( NT/T, see [cfg_dfn] ) */
;

symbol PT_value(PT_Term PTree)
/* token value of node 'PTree'
   assertion: ! PT_isNonTerm(PTree) && ! PT_isCFG(PTree)
*/
;

PT_Term PT_cfg(PT_Term PTree)
/* embedded language of node 'PTree'
   assertion: PT_isCFG(PTree)
*/
;


symbol PT_file(PT_Term PTree)
/* position - source file of node 'PTree'
   assertion: PT_hasPos(PTree)
*/
;

long PT_row(PT_Term PTree)
/* position - source line of node 'PTree'
   assertion: PT_hasPos(PTree)
*/
;

long PT_col(PT_Term PTree)
/* position - source column of node 'PTree'
   assertion: PT_hasPos(PTree)
*/
;


PT_Term PT_next(PT_Term PTree)
/* C: next node / rest of child list 'PTree' or NULL */
;

PT_Term PT_parts(PT_Term PTree)
/* C: child list ( first node ) of node 'PTree'
      assertion: PT_isNonTerm(PTree)
*/
;

List(PT_Term) XPT_parts(PT_Term PTree)
/* Xaron: child list of node 'PTree'
          assertion: PT_isNonTerm(PTree)
*/
;

List(PT_Term)* XPT_parts_ref(PT_Term PTree)
/* Xaron: pointer reference to child list of node 'PTree'
          assertion: PT_isNonTerm(PTree)
*/
;


/* 
  <p><b>Convenience macros for identifying a certain nonterminal,
  token or production </b>
*/

#define PT_THISNTM(t,s) ( ( PT_isNonTerm(t) && PT_symbol(t)  == (s) ) ? \
                          C_True : C_False )
#define PT_THISTOK(t,s) ( ( PT_isToken(t)   && PT_symbol(t)  == (s) ) ? \
                          C_True : C_False )
#define PT_THISPRD(t,p) ( ( PT_isNonTerm(t) && PT_product(t) == (p) ) ? \
                          C_True : C_False )

/* ----------------------------- Searching ---------------------------------- */

int PT_cntST_ex
    (
      PT_Term PTree, c_bool (*filter)(PT_Term PTree, Any_T any), Any_T any
    )
/* number of nodes t within child list of node 'PTree'
   sacrifying condition filter(t,any) = False
*/
;

int PT_cntST(PT_Term PTree, c_bool (*filter)(PT_Term PTree))
/* number of nodes t within child list of node 'PTree'
   sacrifying condition filter(t) = False
*/
;

PT_Term PT_nthST_ex
        (
          PT_Term PTree, int nth,
          c_bool (*filter)(PT_Term PTree, Any_T any), Any_T any
        )
/* 'nth' node t within child list of node 'PTree'
   sacrifying condition filter(t,any) = False
   [nth=1..PT_cntST_ex]
*/
;

PT_Term PT_nthST(PT_Term PTree, int nth, c_bool (*filter)(PT_Term PTree))
/* 'nth' node t within child list of node 'PTree'
   sacrifying condition filter(t) = False
   [nth=1..PT_cntST]
*/
;

int PT_symbolCnt(PT_Term PTree, symbol cfgsym, c_bool filter)
/* filter --> number of nodes with symbol 'cfgsym'
   else   --> number of token and nonterminal nodes
              ( skipping keywords and comments )
   within child list of node 'PTree'
*/
;

PT_Term PT_nthSymbol(PT_Term PTree, symbol cfgsym, int nth, c_bool filter)
/* filter --> 'nth' node with symbol 'cfgsym'
   else   --> 'nth' token or nonterminal node
              ( skipping keywords and comments )
   within child list of node 'PTree' [nth=1..PT_symbolCnt]
*/
;

PT_Term PT_r_find
        (
          PT_Term PTree, c_bool (*pred)(PT_Term PTree, StdCPtr any), StdCPtr any
        )
/* first subterm t of parse tree / term 'PTree'
   sacrifying condition pred(t,any) ( recursive )
*/
;

PT_Term PT_l_find
        (
          PT_Term PTree, c_bool (*pred)(PT_Term PTree, StdCPtr any), StdCPtr any
        )
/* first subterm t of parse tree / term 'PTree'
   sacrifying condition pred(t,any) ( non-recursive )
*/
;


/* -------------------------- Term Iterator --------------------------------- */

/* 
  <p><b>Traversal order</b>
  <p>All nodes will be visited in pre and post order.
*/

#define PT_ROOT   1 // root / start order
#define PT_PRAE   2 // pre order
#define PT_POST   3 // post order

PT_Itr PT_newIT(PT_Term PTree)
/* creates an iterator for parse tree / term 'PTree' */
;

void    PT_delIT(PT_Itr iter);      /* removes term iterator 'iter'         */
PT_Itr  PT_copyIT(PT_Itr iter);     /* copies term iterator 'iter'          */

short PT_stateIT(PT_Itr iter)
/* current traversal order of term iterator 'iter'
   ( PT_PRAE / PT_POST )
*/
;

PT_Term PT_termIT(PT_Itr iter);     /* current node of term iterator 'iter' */

OT_Tab PT_stackIT(PT_Itr iter)
/* current node stack of term iterator 'iter' */
;

c_bool PT_df_getIT(PT_Itr iter)
/* next node of term iterator 'iter'
   in depth first, prae/post order ;
   returns False on end-of-term
*/
;

c_bool PT_bf_getIT(PT_Itr iter)
/* next node of term iterator 'iter'
   in breast first, prae/post order;
   returns False on end-of-term
*/
;

c_bool PT_filterIT(PT_Itr iter, c_bool (*get)(PT_Itr iter))
/* next node of term iterator 'iter' in prae/post order
   sacrifying filter condition get(iter),
   skipping comments and keywords;
   returns False on end-of-term i.e. notfound
*/
;

void PT_skipIT(PT_Itr iter)
/* skips subterms of current node in term iterator 'iter'
   assertion: current traversal order = PT_PRAE
*/
;


/* ---------------------- Convenient iterator macros ------------------------ */

/*   For - statement with basic iterators. Make sure to
     free the iterator if you leave the loop via break.
*/

#define PT_FORALL(it,tr)      for( (it)   = PT_newIT(tr);            \
                                   ( PT_df_getIT(it) )               \
                                   ? C_True : ( PT_delIT(it), C_False ); )
#define PT_FORALL_F(it,tr)    for( (it)   = PT_newIT(tr);            \
                                   ( PT_filterIT(it,PT_df_getIT) )   \
                                   ? C_True : ( PT_delIT(it), C_False ); )
#define PT_FORALL_BF(it,tr)   for( (it)   = PT_newIT(tr);            \
                                   ( PT_bf_getIT(it) )               \
                                   ? C_True : ( PT_delIT(it), C_False ); )
#define PT_FORALL_BF_F(it,tr) for( (it)   = PT_newIT(tr);            \
                                   ( PT_filterIT(it,PT_bf_getIT) )   \
                                   ? C_True : ( PT_delIT(it), C_False ); )
#define PT_BREAK(it)          { PT_delIT(it); break; }

/* ----------------------- Hashing & Predicates ----------------------------- */

long PT_hash(PT_Term PTree);     /* hash value of parse tree / term 'PTree' */

c_bool PT_equal(PT_Term left, PT_Term right)
/* term 'left' = term 'right' ? */
;

c_bool PT_subterm(PT_Term left, PT_Term right)
/* term 'left' <= term 'right' ? */
;


/* ---------------------------- Binary Image -------------------------------- */

void PT_fputT(BinImg_T img, PT_Term PTree)
/* unloads parse tree / term 'PTree'
   to binary image 'img' (reentrant)
*/
;

void PT_putT(PT_Term PTree)
/* unloads parse tree / term 'PTree'
   to the current ( previously opened ) image
*/
;

void PT_fgetT(BinImg_T img, PT_Term* PTree)
/* loads parse tree / term 'PTree'
   from binary image 'img' (reentrant)
*/
;

void PT_getT(PT_Term* PTree)
/* loads parse tree / term 'PTree'
   from the current ( previously opened ) image
*/
;


/* ------------------------------- Printing --------------------------------- */

void PT_prind(PT_Term PTree, int ind)
/* prints parse tree / term 'PTree' to stdout
   ( with indent 'ind' )
*/
;

void PT_prind_utf8(PT_Term PTree, int ind)
/* prints utf8 parse tree / term 'PTree' to stdout
   ( with indent 'ind' )
*/
;

void PT_prind_rawutf8(PT_Term PTree, int ind)
/* prints utf8 parse tree / term 'PTree' to stdout
   ( printable ascii or hex, with indent 'ind' )
*/
;

void PT_print(PT_Term PTree); /* prints parse tree / term 'PTree' to stdout */

void PT_print_utf8(PT_Term PTree)
/* prints utf8 parse tree / term 'PTree' to stdout */
;

void PT_print_rawutf8(PT_Term PTree)
/* prints utf8 parse tree / term 'PTree' to stdout
   ( printable ascii or hex )
*/
;

void PT_TermToString(PT_Term PTree)
/* prints value of parse tree / term 'PTree' to stdout */
;

void PT_TermToSink(PT_Term PTree, Sink snk)
/* prints value of parse tree / term 'PTree' to sink 'snk'
   ( without comments )
*/
;


/* ----------------------------- Normalizer --------------------------------- */

PT_Term PT_keycom_Skip(PT_Term x)
/* C: skips comment and keyword nodes in child list 'x';
      returns first token / nonterminal node or NULL
*/
;

List(PT_Term) XPT_keycom_Skip(List(PT_Term) x)
/* Xaron: skips comment and keyword nodes in child list 'x';
          returns next token / nonterminal node or NULL
*/
;

PT_Term PT_ignkey_Skip(PT_Term x, ROW(PT_Term) coms)
/* skips 'ign#'-production, comment and keyword nodes
   in parse tree / term 'x', collecting comment nodes in 'coms';
   returns next token / nonterminal node
*/
;

PT_Term PT_ign_Skip(PT_Term x)
/* skips 'ign#'-production, comment and keyword nodes
   in parse tree / term 'x';
   returns next token / nonterminal node
*/
;


/* -------------------------- Xaron Support --------------------------------- */

void PT_references(PT_Term x, StdCPtr (*act)(StdCPtr r))
/* performs 'act' on all pointer and symbol references in node 'x'
   ( garbage collection service for xaron )
*/
;


/* ========================== Parse Tree (ABS) ============================== */

/*  
   The above mentioned special optimzed form of an abstract parse tree can be
   produced with the following - non-reentrant - unload/load-API.

         parse tree         --- unload --->
                                              binary image
         parse tree (ABS)  <---  load  ---

*/

/* ------------------------ Types & Macros ---------------------------------- */

AbstractHugeType(PT_Abs_Term); /* Abstract parse tree type [ABS] */

#define PT_Abs_nonterm(X)   ((symbol)(((long __HUGE*)(X))[0]))
#define PT_Abs_token(X)     ((symbol)(((long __HUGE*)(X))[0]))
#define PT_Abs_product(X)   ((symbol)(((long __HUGE*)(X))[1]))
#define PT_Abs_value(X)     ((symbol)(((long __HUGE*)(X))[2]))
#define PT_Abs_part(X,N)    ((PT_Abs_Term)(((long __HUGE*)(X))[2+(N)]))
#define PT_Abs_cfg(X)       ((PT_Abs_Term)(((long __HUGE*)(X))[2+(1)]))

#define PT_Abs_isToken(X)   (PT_Abs_product(X) == (symbol)NULL)
#define PT_Abs_isNonTerm(X) (PT_Abs_product(X) != (symbol)NULL)
#define PT_Abs_isCFG(X) \
  (PT_Abs_product(X) == (symbol)NULL && PT_Abs_value(X) == NULL)

/* ------------------------- Init & Quit ------------------------------------ */

void PT_putBgn(void);                  /* initializes abstract term putting */
void PT_putEnd(void);                  /* quits abstract term putting       */
void PT_getBgn(void);                  /* initializes abstract term getting */
void PT_getEnd(void);                  /* quits abstract term getting       */

/* ------------------------------ Put & Get --------------------------------- */

long PT_Symbol_to_Ref(symbol s);   /* reference corresponding to symbol 's' */
long PT_putSymbol(symbol s);       /* creates a reference for symbol 's'    */

void PT_putAllSymbols(void)
/* puts all symbol references
   to the current ( previously opened ) binary image
*/
;

void PT_getAllSymbols(void)
/* gets all symbol references
   from the current ( previously opened ) binary image
*/
;

symbol PT_getSymbol(long RefId)
/* symbol corresponding to reference 'RefId' */
;

long PT_Term_to_Ref(PT_Term PTree)
/* abstract term reference corresponding to parse tree 'PTree'
   ( unload phase )
*/
;

PT_Abs_Term PT_Ref_to_Term(long __HUGE* nodes, long RefId)
/* abstract term in node array 'nodes'
   corresponding to reference 'RefId'
   ( load phase )
*/
;

long PT_putAbsNode(PT_Term PTree)
/* creates an abstract term reference for parse tree 'PTree' */
;

void PT_putAbsT(void)
/* puts all abstract term references
   to the current ( previously opened ) binary image
*/
;

long __HUGE* PT_getAbsT(void)
/* gets all abstract term references
   from the current ( previously opened ) binary image
*/
;

long __HUGE* PT_patchAbsT(long __HUGE* nodes)
/* patches all abstract term references
   in node array 'nodes'; returns 'nodes'
*/
;


/* ------------------------- Disposing -------------------------------------- */

void PT_delAbsT(long __HUGE* nodes)
/* removes node array 'nodes' with abstract term references */
;



#ifdef __cplusplus
}
#endif

#endif
