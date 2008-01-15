" ex:syntax=vim
"
" Vim syntax file
" Language: lexi (lexical analyser tool)
" Maintainer: Jeroen Ruigrok van der Werven <asmodai@tendra.org>
"
" NOTE: TenDRA lexi lexical analyser tool syntax file.
"
"----------------------------------------------------------------------------
"                                 CREDITS
"----------------------------------------------------------------------------
" Jeroen Ruigrok van der Werven <asmodai@tendra.org>
"----------------------------------------------------------------------------
"
" $TenDRA$
"

" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version <  600
	syntax clear
elseif exists("b:current_syntax")
	finish
endif

"============================================================================
" LEXI MATCHES
"============================================================================
" COMMENTS

syn region lexiComment	start="^\s*\/\*" end="\*\/\s*"

" IDENTIFIERS

syn match lexiIdentifier	"[a-zA-Z_]*"
syn match lexiSIDIdentifier	"\$[a-zA-Z_]*"

" STRING

syn match  lexiSpecial	display contained "\\\(x\x\+\|\o\{1,3}\|.\|$\)"
syn region lexiString	start=+L\="+ skip=+\\\\\|\\"+ end=+"+ contains=lexiSpecial

" KEYWORDS

syn keyword lexiKeyword	ELSE IF GROUP KEYWORD MAPPING TOKEN white

syn match lexiOperator	"->"

"============================================================================
" COLOUR ASSIGNMENT
"============================================================================
" Define the default highlighting.
" For version 5.7 and earlier: only when not done already
" For version 5.8 and later: only when an item doesn't have highlighting yet
if version >= 508 || !exists("did_lexi_syn_inits")
	if version < 508
		let did_lexi_syn_inits = 1
		command -nargs=+ HiLink hi link <args>
	else
		command -nargs=+ HiLink hi def link <args>
	endif

	HiLink lexiComment	Comment
	HiLink lexiIdentifier	Identifier
	HiLink lexiKeyword	Type
	HiLink lexiOperator	Grey
	HiLink lexiSIDIdentifier Statement
	HiLink lexiSpecial	SpecialChar
	HiLink lexiString	String
	HiLink lexiType		Type

	delcommand HiLink
endif

let b:current_syntax = "lexi"