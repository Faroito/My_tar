/*
** compress.c for compress in /home/timothee.couble/Epitech/Semester_2/C_Prog_Elem/CPE_2016_b2rush1
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sun Mar  5 19:46:22 2017 Timothée Couble
** Last update Sun Mar  5 23:09:50 2017 Timothée Couble
*/

#include "my.h"

void	compress_file(char *tar_name, char *zip_name)
{
  FILE		*tar_file;
  gzFile	zip_file;
  char		buffer[128];
  int		num_read;

  num_read = 0;
  if ((tar_file = fopen(tar_name, "rb")) == NULL)
    error("Error fopen\n");
  if ((zip_file = gzopen(zip_name, "wb")) == NULL)
    error("Error gzopen\n");
  while ((num_read = fread(buffer, 1, sizeof(buffer), tar_file)) > 0)
    gzwrite(zip_file, buffer, num_read);
  fclose(tar_file);
  gzclose(zip_file);
}

void	compress_tar(char *name)
{
  if (rename(name, "tmp.tar") == -1)
    error("Error rename\n");
  compress_file("tmp.tar", name);
  if (remove("tmp.tar") == -1)
    error("Error remove\n");
}
