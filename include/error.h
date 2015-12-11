/**************************************************************************/
/**************************************************************************/
/* Name ........ : error.h                                                */
/* Role ........ : Manage errors and print to standard error stream.      */
/*                                                                        */
/* Author ...... : Morgan Barbier <morgan.barbier@ensicaen.fr>            */
/* Version ..... : V1.0 2013-01-20                                        */
/* Licence ..... : CC                                                     */
/**************************************************************************/
/**************************************************************************/
#ifndef __ERROR_H__
#define __ERROR_H__


#define ERR_ALLOC  -1
#define ERR_MATH   -2
#define ERR_FILE   -3
#define ERR_FORMAT -4

/**************************************************************************/
/**************************************************************************/
/*  Function print on the error outuput the 'message' and exit with       */
/*  the 'error_number' which can be:                                      */
/*  ERR_ALLOC  for allocation issue                                       */
/*  ERR_MATH   for mathematical issue                                     */
/*  ERR_FILE   for issue with file                                        */
/*  ERR_FORMAT for issue with format.                                     */
/*                                                                        */
/*  The following arguments MUST to reveive predefined marcros:           */
/*  'file_name' receive the macro __FILE__                                */
/*  'line' receive the macro __LINE__                                     */
/*  'func_name' receive the macro __FUNCTION__                            */
/**************************************************************************/
/**************************************************************************/
void error_print(const char* file_name, const int line, const char* func_name, 
		 const char* message, int error_number);




#endif /* __ERROR_H__ */
