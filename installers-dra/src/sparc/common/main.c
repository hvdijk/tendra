/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdlib.h>

#define SPARCTRANS_CODE

#include "config.h"

#include "flags.h"
#include "tempdecs.h"
#include "comment.h"
#include "translat.h"
#include "main_reads.h"	
#include "basicread.h"
#include "addrtypes.h"
#include "makecode.h"
#include "flpt.h"
#include "exptypes.h"
#include "exp.h"
#include "installglob.h"
#include "out.h"
#include "externs.h"
#include "special.h"
#include "labels.h"

#include "target_v.h"
#include "reader_v.h"
#include "construct_v.h"
#ifdef NEWDIAGS
#include "diag_v.h"
#include "dg_version.h"
#endif
#ifdef NEWDWARF
#include "dw2_iface.h"
#include "dw2_vsn.h"
#include "dw2_abbrev.h"
#include "dw2_common.h"
static bool dump_abbrev = 0 ;
#endif

#if DWARF
#include "dwarf_mc.h"
#endif

extern int good_trans ;

#include "debug.h"
/*
  IDENTIFIER PREFIXES
*/

char *local_prefix = "", *name_prefix = "" ;


/*
  LOCAL FLAGS
*/

extern int redo_structparams ;
bool do_tlrecursion = 0 ;
#if 0
bool do_innerprocs = 0 ;
#endif

extern int crit_inline;
extern int crit_decs;
extern int crit_decsatapp;
extern int show_inlining;

int do_dynamic_init=1;    /* Only applies to SunOS */

/*
  OPEN INPUT AND OUTPUT FILES
*/

static void 
open_files ( char * infname, char * outfname ){

  if ( !initreader ( infname ) ) {
    fprintf ( stderr, "%s : cannot open input file %s\n",
	      sparctrans, infname ) ;
    exit ( EXIT_FAILURE ) ;
  }

  if ( strcmp ( outfname, "-" ) == 0 ) {
    /* "-" by convention means stdout */
    as_file = stdout ;
  } 
  else {
    as_file = fopen ( outfname, "w" ) ;
    if ( as_file == NULL ) {
      fprintf ( stderr, "%s : cannot open output file %s\n",
		sparctrans, outfname ) ;
      exit ( EXIT_FAILURE ) ;
    }
  }
  return ;
}


/*
  MAIN ROUTINE
*/

int 
main ( int argc, char ** argv )
{
  int a = 1 ;
  char *arg ;
  char *infname ;
  char *outfname ;
  bool errflg = 0 ;
  
  /* initialise executable name */
  sparctrans = argv [0] ;
  for ( arg = sparctrans ; *arg ; arg++ ) {
    if ( *arg == '/' ) sparctrans = arg + 1 ;
  }
  
  /* initialise output file */
  as_file = stdout ;
  
  /* errors messages are output on stdout, ensure they get out */
  setbuf ( stdout, NULL ) ;
  setbuf ( stderr, NULL ) ;

  /* set defaults for options */
  do_inlining = 1 ;			/* do inline */
  do_special_fns = 1 ;			/* do special functions */
  do_loopconsts = 1 ;			/* do loop constant extraction */
  do_foralls = 1;			/* do do foralls optimisation */
  do_unroll = 1;			/* do unroll loops */
  
  redo_structfns = 0 ;			/* structure results are normal */
  redo_structparams = 1 ;		/* structure parameters are odd */
  diagnose = 0 ;			/* not in diagnostics mode */
#ifdef NEWDIAGS
  diag_visible = 0;
  extra_diags = 0;
#endif
#ifdef NEWDWARF
  dwarf2 = 0;
#endif
  do_profile = 0 ;			/* not in profiling mode */
  PIC_code = 0 ;			/* don't do PIC */
  do_alloca = 1 ;			/* inline alloca */
  tempdecopt = 1 ;			/* do the tempdec optimisation */
  sysV_abi = SYSV_ABI ;			/* SYSV version */
  sysV_assembler = SYSV_AS ;		/* SYSV version */
  optim_level = 2 ;			/* default, equivalent to -O2 */
  g_reg_max = ( sysV_abi ? 4 : 7 ) ;	/* number of G registers */

    
  flpt_const_overflow_fail = 1;		/* constant floating point arithmetic
					   fails installation, if overflow */
  strict_fl_div = 1;			/* don't mult by 1/constant */
  round_after_flop = 0;			/* don't round every time */
  do_dynamic_init = 1;                  /* Only applies to SunOS*/
  
#define GET_0_1 ((arg[2] == '1') ? 1 : 0)
    /* process program arguments */
    while ( a < argc && ( arg = argv [a], arg [0] == '-' ) ) {
      switch ( arg [1] ) {
	case 'A' : do_alloca = GET_0_1 ; break ;
	case 'B' : flpt_const_overflow_fail = GET_0_1; break;	
	case 'C' : do_loopconsts = GET_0_1; break ;
	case 'D' : PIC_code = GET_0_1 ; break ;
	case 'E' : extra_checks = 0 ; break ;
	case 'F' : do_foralls = GET_0_1 ; break ;
	case 'H' : {
	  diagnose = 1 ;
#ifdef NEWDIAGS
	  if (arg[2] != 'O')
	    diag_visible = 1;
#endif
	  break ;
	}
	case 'I' : do_inlining = GET_0_1 ; break ;
#ifdef NEWDWARF
        case 'J' : 
	  diagnose = 1;
	  extra_diags = 1;
	  dwarf2 = 1;
	  break;
#endif
	case 'K' : break;
	case 'M' : strict_fl_div = GET_0_1 ; break ;
	case 'N' : do_prom = 1 ; break ;
	case 'O' : {
	  /* optimisation level */
	  optim_level = atoi ( arg + 2 ) ;
	  if ( optim_level < 0 ) optim_level = 0 ;
	  if ( optim_level > 4 ) optim_level = 4 ;
	  break ;
	}
	
	case 'P' : do_profile = 1 ; break ;	      
	case 'Q' : exit(EXIT_SUCCESS); break;
	case 'R' : round_after_flop = GET_0_1; break;
#ifdef NEWDWARF
	case 'T' :
	  dump_abbrev = 1;
	  diagnose = 1;
	  extra_diags = 1;
	  dwarf2 = 1;
	  break;
#endif
	case 'U' : do_unroll = GET_0_1; break;
	
	case 'V':
	IGNORE fprintf(stderr, "DERA ANDF Sparc translator (TDF version %d.%d)\n",
		      MAJOR_VERSION, MINOR_VERSION);
	IGNORE fprintf(stderr, "reader %d.%d: ", reader_version,
		      reader_revision);
	IGNORE fprintf(stderr, "construct %d.%d: ", construct_version,
		      construct_revision);
	IGNORE fprintf(stderr, "target %d.%d: ", target_version,
		      target_revision);
#if (DWARF == 1)
	IGNORE fprintf(stderr, "dwarf %d.%d: ", DWARF_MAJOR,
		      DWARF_MINOR);
#endif
#ifdef NEWDIAGS
	IGNORE fprintf(stderr, "diag_info %d.%d:\n%s   ", diag_version,
		 diag_revision, DG_VERSION);
#endif
#ifdef NEWDWARF
	IGNORE fprintf(stderr, "dwarf2 %d.%d: ", DWARF2_MAJOR,
		 DWARF2_MINOR);
#endif
	IGNORE fprintf(stderr, "\n");
	IGNORE fprintf(stderr, "system %s: ", target_system);
#ifdef __DATE__
	IGNORE fprintf(stderr, "installer compilation %s", __DATE__);
#endif
	break;
	     
	case 'W' : break;
	case 'X' : {
	  /* disable all optimisations */
	  optim_level = 0 ;
	  tempdecopt = 0 ;
	  do_inlining = 0 ;
	  do_loopconsts = 0 ;
	  do_foralls = 0 ;
	  do_tlrecursion = 0 ;
	  do_unroll = 0;
	  break ;
	}
	case 'Z' : report_versions = 1 ; break ;

/* undocumented sparc specific flags below here */

	case 'a' : sysV_abi = 1 ; g_reg_max = 4 ; break ;
	case 'c' : do_comment = 1 ; break ;
	case 'g' : library_key = 2 ; break ;
	case 'l' : library_key = 1 ; break ;
	case 'i':
	switch (arg[2]) {
	  case 'i':
	  crit_inline = atoi(arg+3);
	  break;
	  case 'd':
	  crit_decs = atoi(arg+3);
	  break;
	  case 'a':
	  crit_decsatapp = atoi(arg+3);
	  break;
	  case 's':
	  fprintf(stderr,"count %d decs %d decs@app %d\n",
		  crit_inline, crit_decs, crit_decsatapp);
	  show_inlining = 1;
	  break;
	  default:
	  fprintf(stderr,"Incorrect inline option %c\n",arg[2]);
	}
	break;
	case 'r' : {
	  /* number of G registers */
	  g_reg_max = atoi ( arg + 2 ) ;
	  if ( g_reg_max < 4 ) g_reg_max = 4 ;
	  if ( g_reg_max > 7 ) g_reg_max = 7 ;
	  break ;
	}
	case 't' : tempdecopt = 0 ; break ;
	
	case 'u' : {
	  separate_units = 1 ;
#if 0	
	  current_alloc_size = first_alloc_size ;
#endif	
	  case 'n': {
	    do_dynamic_init = GET_0_1;
	  }
	  break ;
	}

	default : {
	  fprintf ( stderr, "%s : unknown option, %s\n",
		    sparctrans, arg ) ;
	  break ;
	}
      }
      a++ ;
    }

    /* we expect two further filename arguments */
    if ( argc == a + 2 ) {
      infname = argv [a] ;
      outfname = argv [ a + 1 ] ;
    } 
    else if ( argc == a + 1 ) {
      infname = argv [a] ;
      outfname = "-" ;
    } 
    else {
      if ( argc == a )
	fprintf ( stderr, "%s : input file missing\n", sparctrans );
      errflg = 1 ;
    }

    /* check ABI conformance */
    if ( sysV_abi && ( g_reg_max > 4 ) ) {
      fprintf ( stderr, "%s : -r%d conflicts with SYSV ABI\n",
		sparctrans, g_reg_max ) ;
    }

    /* quit if arguments were wrong */
    if ( errflg ) {
      exit ( EXIT_FAILURE ) ;
    }

    /* switch off certain optimisations in diagnostics mode */
#ifdef NEWDIAGS
    if ( diag_visible ) {
#else
    if ( diagnose ) {
#endif
      optim_level = 0 ;
      tempdecopt = 0 ;
      do_inlining = 0 ;
      do_loopconsts = 0 ;
      do_foralls = 0 ;
      all_variables_visible = 1;	/* set vis flag for all declarations */
    }	

    /* initialise nowhere */
    setregalt ( nowhere.answhere, 0 ) ;
    nowhere.ashwhere.ashsize = 0 ;
    nowhere.ashwhere.ashsize = 0 ;

    /* initialise name prefixes and label numbers */
    name_prefix = ( sysV_assembler ? "" : "_" ) ;
    local_prefix = ( sysV_assembler ? ".." : "$$" ) ;
    lab_prefix = ( sysV_assembler ? ".L" : "L." ) ;
    crt_labno = 101 ;

    /* other initialisation routines */
    init_flpt () ;
#include "inits.h"
    top_def = null ;

    /* main decoding routines */
    open_files ( infname, outfname ) ;
    init_translator () ;
#ifdef NEWDWARF
    if ( dump_abbrev ) {
	/* Dump abbreviations table */
	do_abbreviations () ;
	dwarf2_prelude () ;
	make_dwarf_common () ;
	dwarf2_postlude () ;
    } else
#endif
    d_capsule () ;
    exit_translator () ;
    if ( good_trans ) exit ( EXIT_FAILURE ) ;

    /* check for output errors and close the output file */
    if ( ferror ( as_file ) != 0 || fclose ( as_file ) != 0 ) {
      fprintf ( stderr, "%s : output file error, %s\n",
		sparctrans, outfname ) ;
      exit ( EXIT_FAILURE ) ;
    }

    /* success */
    exit ( EXIT_SUCCESS ) ;
#ifdef lint
    return 0;
#endif
}