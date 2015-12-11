#include "file.h"

void file_open(FILE** F, const char* filename, const char* mode)
{
  if((*F = fopen(filename, mode)) == NULL)
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Openning file.", ERR_FILE);
    }
}

void file_close(FILE** F)
{
  if(fclose(*F))
    {
      error_print(__FILE__, __LINE__, __FUNCTION__,
		  "Closing file.", ERR_FILE);      
    }
  *F = NULL;
}


unsigned long int get_size(FILE *F)
{
  unsigned long 
    curr_position = ftell(F),
    end_position;

  fseek(F, 0, SEEK_END);
  end_position = ftell(F);
  fseek(F, curr_position, SEEK_SET);

  return(end_position);
}
