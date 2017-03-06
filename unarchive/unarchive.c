/*
** unarchive.c for unarchive in /home/timothee.couble/Epitech/Semester_2/C_Prog_Elem/CPE_2016_b2rush1
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sat Mar  4 22:36:23 2017 Timothée Couble
** Last update Sun Mar  5 22:37:15 2017 Timothée Couble
*/

#include "my.h"

t_tar	*file_header(char buffer[512])
{
  t_tar	*tar;

  if ((tar = malloc(sizeof(t_tar))) == NULL)
    error("Error malloc\n");
  if (my_strn_cpy(tar->name, buffer, 0, sizeof(tar->name)) < 1)
    return (NULL);
  my_strn_cpy(tar->mode, buffer, 100, sizeof(tar->mode));
  my_strn_cpy(tar->uid, buffer, 108, sizeof(tar->uid));
  my_strn_cpy(tar->gid, buffer, 116, sizeof(tar->gid));
  my_strn_cpy(tar->size, buffer, 124, sizeof(tar->size));
  my_strn_cpy(tar->mtime, buffer, 136, sizeof(tar->mtime));
  tar->typeflag = buffer[156];
  my_strn_cpy(tar->linkname, buffer, 157, sizeof(tar->linkname));
  my_strn_cpy(tar->magic, buffer, 257, sizeof(tar->magic));
  my_strn_cpy(tar->uname, buffer, 265, sizeof(tar->uname));
  my_strn_cpy(tar->gname, buffer, 297, sizeof(tar->gname));
  my_strn_cpy(tar->devmajor, buffer, 329, sizeof(tar->devmajor));
  my_strn_cpy(tar->devminor, buffer, 337, sizeof(tar->devminor));
  my_strn_cpy(tar->chksum, buffer, 148, sizeof(tar->chksum));
  if (my_get_octal(my_get_decimal(tar->chksum)) != add_all_struct(tar))
    return (NULL);
  return (tar);
}

void			read_file(t_tar *tar, int fd_arc, int fd_file)
{
  struct utimbuf	*time;
  int			size;
  char			*buffer;

  size = 0;
  if ((time = malloc(sizeof(struct utimbuf))) == NULL)
    error("Error malloc\n");
  if (chown(tar->name, my_get_decimal(tar->uid),
	    my_get_decimal(tar->gid)) == -1)
    error("Error chown\n");
  time->actime = my_get_decimal(tar->mtime);
  time->modtime = my_get_decimal(tar->mtime);
  while ((512 * size - my_get_decimal(tar->size)) < 0)
    size += 1;
  size = 512 * size;
  if ((buffer = malloc(sizeof(char) * (size + 1))) == NULL)
    error("Error malloc\n");
  if (read(fd_arc, buffer, size) == -1)
    error("Error read\n");
  if (write(fd_file, buffer, my_get_decimal(tar->size)) == -1)
    error("Error write\n");
  if (utime(tar->name, time) == -1)
    error("Error utime\n");
  free(buffer);
  free(time);
}

void	read_other(t_tar *tar)
{
  if (tar->typeflag == '5')
    mkdir(tar->name, my_get_decimal("40755"));
  else if (tar->typeflag == '2')
    {
      if (access(tar->name, F_OK) == 0)
	{
	  if (remove(tar->name) == -1)
	    error("Error remove\n");
	}
      if (symlink(tar->linkname, tar->name) == -1)
	error("Error symlink\n");
    }
  if (chown(tar->name, my_get_decimal(tar->uid),
	    my_get_decimal(tar->gid)) == -1)
    error("Error chown\n");
}

int	read_tar(int fd_arc, char *flags)
{
  t_tar	*tar;
  char	buffer[512];
  int	fd_file;

  if (read(fd_arc, buffer, 512) == -1)
    error("Error read\n");
  if ((tar = file_header(buffer)) == NULL)
    return (1);
  if (flags[4] == '1')
    printf("%s\n", tar->name);
  if (tar->typeflag == '0')
    {
      if ((fd_file = open(tar->name, O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
	error("Error open file\n");
      read_file(tar, fd_arc, fd_file);
      close(fd_file);
    }
  else
    read_other(tar);
  free(tar);
  return (0);
}

int	my_unarchive(int ac, char **av, char *flags)
{
  int	fd;
  int	i;

  if (flags[5] == '1')
    decompress_gz(av[2]);
  if (flags[1] == '0')
    i = 1;
  else
    i = 2;
  if (ac < i + 1)
    error("Usage: ./my_tar xf [archive_name]\n");
  if (access(av[i], F_OK) == -1)
    error("Archive doesn\'t exist\n");
  if ((fd = open(av[i], O_RDONLY)) == -1)
    error("Can't open file\n");
  while (read_tar(fd, flags) == 0);
  close(fd);
  if (flags[5] == '1')
    replace_archive(av[2]);
  return (0);
}
