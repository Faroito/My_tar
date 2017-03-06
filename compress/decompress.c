/*
** decompress.c for decompress in /home/timothee.couble/Epitech/Semester_2/C_Prog_Elem/CPE_2016_b2rush1
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sun Mar  5 22:10:30 2017 Timothée Couble
** Last update Sun Mar  5 23:10:48 2017 Timothée Couble
*/

#include "my.h"

void		decompress_file(char *zip_name, char *tar_name)
{
  gzFile	zip_file;
  FILE		*tar_file;
  char		buffer[128];
  int		num_read;

  num_read = 0;
  if ((zip_file = gzopen(zip_name, "rb")) == NULL)
    error("Error gzopen\n");
  if ((tar_file = fopen(tar_name, "wb")) == NULL)
    error("Error fopen\n");
  while ((num_read = gzread(zip_file, buffer, sizeof(buffer))) > 0)
    fwrite(buffer, 1, num_read, tar_file);
  gzclose(zip_file);
  fclose(tar_file);
}

void	replace_archive(char *name)
{
  if (remove(name) == -1)
    error("Error remove\n");
  if (rename("tmp.tar.gz", name) == -1)
    error("Error rename\n");
}

void	decompress_gz(char *name)
{
  if (rename(name, "tmp.tar.gz") == -1)
    error("Error rename\n");
  decompress_file("tmp.tar.gz", name);
}
