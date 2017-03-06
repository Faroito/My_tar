##
## Makefile for Makefile in /home/timothee.couble/Default
## 
## Made by Timothée Couble
## Login   <timothee.couble@epitech.net>
## 
## Started on  Tue Nov  8 14:50:00 2016 Timothée Couble
## Last update Mon Mar  6 13:56:37 2017 Timothée Couble
##

SRC		=	archive/archive.c		\
			archive/get_file_description.c	\
			archive/recursivly.c		\
			archive/end_file.c		\
			archive/read_symlink.c		\
			unarchive/unarchive.c		\
			unarchive/list_files.c		\
			compress/compress.c		\
			compress/decompress.c		\
			program/functions.c		\
			program/change_base.c		\
			program/my_tar.c

OBJ		=	$(SRC:.c=.o)

CFLAGS          +=      -W -Wall -Wextra -pedantic -Iinclude

NAME		=	my_tar

RM		=       rm -f

GCC		=       gcc -g -o

LIB		=	-lz

all:    $(NAME)

$(NAME):	$(OBJ)
	$(GCC) $(NAME) $(OBJ) $(LIB) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:     fclean all

.PHONY: all clean fclean re
