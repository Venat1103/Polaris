/*
 * build_config.c
 *
 *  Created on: 22-Jun-2026
 *      Author: soham
 */

/*
If the #pragma message and #warning and #error is put in a header file
and the header file is required multiple times it leads to spam of messages
and warnings and error in the compiler output, a source file is the solution
*/

#include "build_config.h"

/////////////////
// DEVELOPMENT //
/////////////////

#if defined(DEBUG_LOGGING)
    #pragma message "Debug logging enabled"
#else
    #pragma message "Debug logging disabled"
#endif

//////////////
// FEATURES //
//////////////

#if defined (MEASURE_CHAMBER_PRESSURE)
    #pragma message "Measuring chamber pressure"
#else
    #pragma message "Not measuring chamber pressure"
#endif

/////////////////////
// ACTUATION SYSTEM //
/////////////////////

#if defined(ACTUATION_THRUST_VECTOR) && defined(ACTUATION_CONTROL_SURFACE)
    #error "Cannot define both ACTUATION_THRUST_VECTOR and ACTUATION_CONTROL_SURFACE"
#endif

#if defined(ACTUATION_THRUST_VECTOR)
    #pragma message "Using thrust vector control"
#elif defined(ACTUATION_CONTROL_SURFACE)
    #pragma message "Using control surface"
#else
    #pragma message "No control mode selected"
#endif
