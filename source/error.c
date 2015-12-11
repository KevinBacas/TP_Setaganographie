#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void error_print(const char* file_name, const int line, const char* func_name, 
		const char* message, int error_number)
{
  fprintf(stderr,"ERROR: in %s() (%s:l.%d)\n%s\n",
	  func_name,
	  file_name,
	  line,
	  message);
  exit(error_number);
}
