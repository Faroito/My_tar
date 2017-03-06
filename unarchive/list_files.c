/*
** list_files.c for my_list_files in /home/timothee.couble/Epitech/Semester_2/C_Prog_Elem/CPE_2016_b2rush1
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sun Mar  5 19:22:15 2017 Timothée Couble
** Last update Sun Mar  5 22:37:08 2017 Timothée Couble
*/

#include "my.h"

int	read_list(int fd_arc)
{
  int   size;
  char	file_size[12];
  char	buffer[512];
  char	name[100];

  if (read(fd_arc, buffer, 512) == -1)
    error("Error read\n");
  if ((my_strn_cpy(name, buffer, 0, sizeof(name))) < 1)
    return (1);
  my_strn_cpy(file_size, buffer, 124, sizeof(file_size));
  printf("%s\n", name);
  if (buffer[156] == '0')
    {
      size = 0;
      while ((512 * size - my_get_decimal(file_size)) < 0)
	{
	  if (read(fd_arc, buffer, 512) == -1)
	    error("Error read\n");
	  size += 1;
	}
    }
  return (0);
}

int	my_list_files(int ac, char **av)
{
  int	fd;

  if (ac < 3)
    error("Usage: ./my_tar tf [archive_name]\n");
  if (access(av[2], F_OK) == -1)
    error("Archive doesn\'t exist\n");
  if ((fd = open(av[2], O_RDONLY)) == -1)
    error("Can't open file\n");
  while (read_list(fd) == 0);
  close(fd);
  return (0);
}
