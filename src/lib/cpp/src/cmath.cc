/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/*
    STANDARD MATHS FUNCTION DEFINITIONS

    These routines define the standard C maths functions which C++
    overloads.  Most are from cmath, although a couple are from cstdlib.
*/

#include <cstdlib>
#include <cmath>
using namespace std ;

long std::abs ( long a )
{
    return ( labs ( a ) ) ;
}

ldiv_t std::div ( long a, long b )
{
    return ( ldiv ( a, b ) ) ;
}

#if 0
float std::abs ( float ) ;
float std::acos ( float ) ;
float std::asin ( float ) ;
float std::atan ( float ) ;
float std::atan2 ( float, float ) ;
float std::ceil ( float ) ;
float std::cos ( float ) ;
float std::cosh ( float ) ;
float std::exp ( float ) ;
float std::fabs ( float ) ;
float std::floor ( float ) ;
float std::fmod ( float, float ) ;
float std::frexp ( float, int * ) ;
float std::modf ( float, float * ) ;
float std::ldexp ( float, int ) ;
float std::log ( float ) ;
float std::log10 ( float ) ;
float std::pow ( float, float ) ;
float std::pow ( float, int ) ;
float std::sin ( float ) ;
float std::sinh ( float ) ;
float std::sqrt ( float ) ;
float std::tan ( float ) ;
float std::tanh ( float ) ;
#endif

double std::abs ( double a )
{
    return ( fabs ( a ) ) ;
}

#if 0
double std::pow ( double, int ) ;
#endif

#if 0
long double std::abs ( long double ) ;
long double std::acos ( long double ) ;
long double std::asin ( long double ) ;
long double std::atan ( long double ) ;
long double std::atan2 ( long double, long double ) ;
long double std::ceil ( long double ) ;
long double std::cos ( long double ) ;
long double std::cosh ( long double ) ;
long double std::exp ( long double ) ;
long double std::fabs ( long double ) ;
long double std::floor ( long double ) ;
long double std::fmod ( long double, long double ) ;
long double std::frexp ( long double, int * ) ;
long double std::modf ( long double, long double * ) ;
long double std::ldexp ( long double, int ) ;
long double std::log ( long double ) ;
long double std::log10 ( long double ) ;
long double std::pow ( long double, long double ) ;
long double std::pow ( long double, int ) ;
long double std::sin ( long double ) ;
long double std::sinh ( long double ) ;
long double std::sqrt ( long double ) ;
long double std::tan ( long double ) ;
long double std::tanh ( long double ) ;
#endif
