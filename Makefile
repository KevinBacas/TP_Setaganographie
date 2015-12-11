CC      = gcc

SRCDIR  = source/
INCDIR  = include/
OBJDIR  = object/
BINDIR  = bin/
EXE     = stegano

CFLAGS  = -W -Wall -Wextra -pedantic -ansi -I$(INCDIR) -g
LDFLAGS = -lm

SRCS    = $(wildcard $(SRCDIR)*.c)
TMP     = $(SRCS:.c=.o)
OBJS    = $(subst $(OBJDIR)main.o,, $(subst $(SRCDIR), $(OBJDIR), $(TMP)))


.PHONY : clean


$(BINDIR)$(EXE) : $(SRCDIR)main.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@  $(LDFLAGS)

$(OBJDIR)%.o : $(SRCDIR)%.c $(INCDIR)%.h
	$(CC) $(CFLAGS) $< -c -o $@


clean :
	rm -rf ./*~
	rm -rf $(SRCDIR)*~
	rm -rf $(INCDIR)*~
	rm -rf $(OBJDIR)*
	rm -rf $(BINDIR)*


