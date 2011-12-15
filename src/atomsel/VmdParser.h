/** \file
 *  This C header file was generated by $ANTLR version 3.1.3 Mar 18, 2009 10:09:25
 *
 *     -  From the grammar source file : Vmd.g
 *     -                            On : 2011-11-09 16:48:04
 *     -                for the parser : VmdParserParser *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The parser VmdParser has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 * 
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef pVmdParser, which is returned from a call to VmdParserNew().
 *
 * The methods in pVmdParser are  as follows:
 *
 *  - VmdParser_start_return      pVmdParser->start(pVmdParser)
 *  - VmdParser_orSelection_return      pVmdParser->orSelection(pVmdParser)
 *  - VmdParser_andSelection_return      pVmdParser->andSelection(pVmdParser)
 *  - VmdParser_selection_return      pVmdParser->selection(pVmdParser)
 *  - VmdParser_literals_return      pVmdParser->literals(pVmdParser)
 *  - VmdParser_range_return      pVmdParser->range(pVmdParser)
 *  - VmdParser_regex_return      pVmdParser->regex(pVmdParser)
 *  - VmdParser_relOp_return      pVmdParser->relOp(pVmdParser)
 *  - VmdParser_addExpr_return      pVmdParser->addExpr(pVmdParser)
 *  - VmdParser_addOp_return      pVmdParser->addOp(pVmdParser)
 *  - VmdParser_multExpr_return      pVmdParser->multExpr(pVmdParser)
 *  - VmdParser_multOp_return      pVmdParser->multOp(pVmdParser)
 *  - VmdParser_unaryExpr_return      pVmdParser->unaryExpr(pVmdParser)
 *  - VmdParser_unaryOp_return      pVmdParser->unaryOp(pVmdParser)
 *  - VmdParser_expExpr_return      pVmdParser->expExpr(pVmdParser)
 *  - VmdParser_expOp_return      pVmdParser->expOp(pVmdParser)
 *  - VmdParser_factor_return      pVmdParser->factor(pVmdParser)
 * 
 * 
 * 
 * 
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD licence"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_VmdParser_H
#define _VmdParser_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */
 
#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct VmdParser_Ctx_struct VmdParser, * pVmdParser;



#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule 
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif

/* ========================
 * BACKTRACKING IS ENABLED
 * ========================
 */
typedef struct VmdParser_start_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_start_return;

typedef struct VmdParser_orSelection_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_orSelection_return;

typedef struct VmdParser_andSelection_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_andSelection_return;

typedef struct VmdParser_selection_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_selection_return;

typedef struct VmdParser_literals_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_literals_return;

typedef struct VmdParser_range_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_range_return;

typedef struct VmdParser_regex_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_regex_return;

typedef struct VmdParser_relOp_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_relOp_return;

typedef struct VmdParser_addExpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_addExpr_return;

typedef struct VmdParser_addOp_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_addOp_return;

typedef struct VmdParser_multExpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_multExpr_return;

typedef struct VmdParser_multOp_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_multOp_return;

typedef struct VmdParser_unaryExpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_unaryExpr_return;

typedef struct VmdParser_unaryOp_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_unaryOp_return;

typedef struct VmdParser_expExpr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_expExpr_return;

typedef struct VmdParser_expOp_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_expOp_return;

typedef struct VmdParser_factor_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    VmdParser_factor_return;



/** Context tracking structure for VmdParser
 */
struct VmdParser_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_PARSER   pParser;
    /* globalAttributeScopeDef(scope)
     */


     VmdParser_start_return (*start)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_orSelection_return (*orSelection)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_andSelection_return (*andSelection)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_selection_return (*selection)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_literals_return (*literals)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_range_return (*range)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_regex_return (*regex)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_relOp_return (*relOp)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_addExpr_return (*addExpr)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_addOp_return (*addOp)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_multExpr_return (*multExpr)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_multOp_return (*multOp)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_unaryExpr_return (*unaryExpr)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_unaryOp_return (*unaryOp)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_expExpr_return (*expExpr)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_expOp_return (*expOp)	(struct VmdParser_Ctx_struct * ctx);
     VmdParser_factor_return (*factor)	(struct VmdParser_Ctx_struct * ctx);
     ANTLR3_BOOLEAN (*synpred1_Vmd)	(struct VmdParser_Ctx_struct * ctx);
     ANTLR3_BOOLEAN (*synpred2_Vmd)	(struct VmdParser_Ctx_struct * ctx);
     ANTLR3_BOOLEAN (*synpred3_Vmd)	(struct VmdParser_Ctx_struct * ctx);
     ANTLR3_BOOLEAN (*synpred10_Vmd)	(struct VmdParser_Ctx_struct * ctx);
    // Delegated rules
    const char * (*getGrammarFileName)();
    void	    (*free)   (struct VmdParser_Ctx_struct * ctx);
    /* @headerFile.members() */
    pANTLR3_BASE_TREE_ADAPTOR	adaptor;
    pANTLR3_VECTOR_FACTORY		vectors;
    /* End @headerFile.members() */
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pVmdParser desres_msys_VmdParserNew         (pANTLR3_COMMON_TOKEN_STREAM instream);
ANTLR3_API pVmdParser desres_msys_VmdParserNewSSD      (pANTLR3_COMMON_TOKEN_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the parser will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif 
#define WITHINBONDS      20
#define FUNCTION      13
#define UNARYOP      15
#define NEQUAL      11
#define T__40      40
#define REGEXVAL      29
#define T__41      41
#define KEYWORD      12
#define TO      27
#define LIT      28
#define RELATION      14
#define REGEX      18
#define LITERAL      17
#define NOT      26
#define AND      4
#define OF      23
#define EOF      -1
#define SAME      24
#define ALPHA      30
#define AS      25
#define MOREEQ      9
#define WS      32
#define T__33      33
#define T__34      34
#define T__35      35
#define PBWITHIN      22
#define T__36      36
#define LESSEQ      7
#define MORE      8
#define T__37      37
#define BINARYOP      16
#define T__38      38
#define T__39      39
#define EQUAL      10
#define OR      5
#define EXWITHIN      21
#define LESS      6
#define WITHIN      19
#define DIGIT      31
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for VmdParser
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
