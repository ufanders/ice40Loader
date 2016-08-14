/* 
 * File:   HardwareProfile.h
 * Author: ufanders
 *
 * Created on August 13, 2016, 3:52 PM
 */

#ifndef HARDWAREPROFILE_H
#define HARDWAREPROFILE_H

#ifdef	__cplusplus
extern "C" {
#endif

// These definitions are set in the MPLAB Project settings.  If you are starting
// a new project, you should start by modifying one of the pre-existing .mcp 
// files.  To modify the macro used, in MPLAB IDE, click on Project -> Build 
// Options... -> Project -> MPLAB XXX C Compiler -> Preprocessor Macros -> 
// Add.... Note that you may also have to add this macro to the assembler 
// (MPLAB XXX Assembler tab).
#if defined(HWP_PIC32MX460F512L_EX16)
	#include "HWP_PIC32MX460F512L_EX16.h"
#elif defined(HWP_PIC32MX270F256D_EX16)
        #include "HWP_PIC32MX270F256D_EX16.h"
#else
	#error "No extended HWP .h included.  Add the appropriate compiler macro to the MPLAB project."
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* HARDWAREPROFILE_H */

