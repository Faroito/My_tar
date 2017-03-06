/*
** my_archive.c for archive in /home/timothee.couble/Epitech/Semester_2/C_Prog_Elem/Rush1
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Fri Mar  3 20:54:07 2017 Timothée Couble
** Last update Sun Mar  5 22:24:03 2017 Timothée Couble
*/

#include "my.h"

int	check_flags(char letter, char *flags)
{
  char  flag[6];
  int   i;

  flag[0] = 'c';
  flag[1] = 'x';
  flag[2] = 'f';
  flag[3] = 't';
  flag[4] = 'v';
  flag[5] = 'z';
  i = 0;
  while (i < 6)
    {
      if (flag[i] == letter)
	{
	  flags[i] = '1';
	  return (1);
	}
      i++;
    }
  printf("my_tar: invalid option -- '%c'\n", letter);
  exit(84);
  return (0);
}

void	check_tiret(char *str, char *flags)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      check_flags(str[i], flags);
      i ++;
    }
}

void	init_flags(char *flags)
{
  int	i;

  i = 0;
  while (i < 6)
    {
      flags[i] = '0';
      i += 1;
    }
}

int	main(int ac, char **av)
{
  char	*flags;

  if ((flags = malloc(sizeof(char) * 6)) == NULL)
    return (84);
  init_flags(flags);
  if (ac < 2)
    return (0);
  check_tiret(av[1], flags);
  if (flags[2] == '0')
    error("my_tar: Error to write (missing -f option?)\n");
  else if (flags[0] == '1' && flags[1] == '0' && flags[3] != '1')
    my_archive(ac, av, flags);
  else if (flags[0] == '0' && flags[1] == '1' && flags[3] != '1')
    my_unarchive(ac, av, flags);
  else if (flags[3] == '1' && flags[0] == '0' && flags[1] == '0')
    my_list_files(ac, av);
  else
    error("my_tar: Flags conflits\n");
  free(flags);
  return (0);
}
