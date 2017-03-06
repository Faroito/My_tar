/*
** archive.c for archive.c in /home/timothee.couble/Epitech/Semester_2/C_Prog_Elem/CPE_2016_b2rush1
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sat Mar  4 16:41:32 2017 Timothée Couble
** Last update Mon Mar  6 10:02:58 2017 Timothée Couble
*/

#include "my.h"

void	file_struct_2(t_tar *tar, struct stat sb)
{
  access_mode(tar->mode, sb);
  my_put_in_str(my_get_octal(sb.st_uid), tar->uid, sizeof(tar->uid));
  my_put_in_str(my_get_octal(sb.st_gid), tar->gid, sizeof(tar->gid));
  my_put_in_str(my_get_octal(sb.st_size), tar->size, sizeof(tar->size));
  my_get_mtime(sb.st_mtime, tar->mtime);
  my_put_in_str(my_get_octal(major(sb.st_rdev)),
		tar->devmajor, sizeof(tar->devmajor));
  my_put_in_str(my_get_octal(minor(sb.st_rdev)),
                tar->devminor, sizeof(tar->devminor));
  my_str_cpy(tar->magic, "ustar", sizeof(tar->magic));
  my_str_cpy(tar->version, "00", sizeof(tar->version));
  my_str_cpy(tar->prefix, "\0", sizeof(tar->prefix));
}

t_tar		*file_struct(char *name, struct stat sb)
{
  t_tar		*tar;
  struct group  *group_name;

  if ((tar = malloc(sizeof(t_tar))) == NULL)
    error("Error malloc\n");
  my_str_cpy(tar->name, name, sizeof(tar->name));
  file_struct_2(tar, sb);
  tar->typeflag = testing_file(sb.st_mode, name);
  if (tar->typeflag == '2')
    read_symlink(tar, name);
  else
    my_str_cpy(tar->linkname, "\0", sizeof(tar->linkname));
  my_str_cpy(tar->uname, getlogin(), sizeof(tar->uname));
  if ((group_name = getgrgid(sb.st_gid)) == NULL)
    error("Error getgrgid\n");
  my_str_cpy(tar->gname, group_name->gr_name, sizeof(tar->gname));
  my_put_in_str(add_all_struct(tar), tar->chksum, sizeof(tar->chksum) - 1);
  tar->chksum[7] = ' ';
  return (tar);
}

int		write_file(int fd_dest, char *name, int size, int block_nb)
{
  char          *read_buffer;
  int		fd_src;
  int		i;

  i = size;
  if ((fd_src = open(name, O_RDONLY)) == -1)
    error("Can\'t open\n");
  block_nb += size / 512;
  if ((read_buffer = malloc(sizeof(char) * (512 * block_nb + 1))) == NULL)
    error("Error malloc\n");
  if (read(fd_src, read_buffer, size + 1) == -1)
    error("Error read\n");
  while (i < 512 * block_nb)
    read_buffer[i++] = 0;
  if (write(fd_dest, read_buffer, 512 * block_nb) == -1)
    error("Error write\n");
  free(read_buffer);
  close(fd_src);
  return (block_nb + 1);
}

int		write_tar(int fd_dest, char *name, char *flags)
{
  struct stat   sb;
  t_tar         *tar;
  int           block_nb;

  if (flags[3] == '1' || flags[4] == '1')
    printf("%s\n", name);
  block_nb = 1;
  if ((stat(name, &sb)) == -1)
    error("Can\'t stat file\n");
  tar = file_struct(name, sb);
  if (write(fd_dest, tar, 512) == -1)
    error("Error write\n");
  if (tar->typeflag != '5' && tar->typeflag != '2')
    block_nb += write_file(fd_dest, name, sb.st_size, block_nb);
  else if (tar->typeflag == '5')
    block_nb += write_repository(fd_dest, tar->name, flags);
  free(tar);
  return (block_nb);
}

int	my_archive(int ac, char **av, char *flags)
{
  int   i;
  int   fd;
  int	nb_block;

  nb_block = 0;
  if (flags[0] == '0')
    i = 2;
  else
    i = 3;
  if (ac < i + 1)
    error("Usage: ./my_tar cf [archive_name] [file ...]\n");
  file_exist(ac, av, flags);
  if ((fd = open(av[i - 1], O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
    return (84);
  while (i < ac)
    {
      nb_block += write_tar(fd, av[i], flags);
      i += 1;
    }
  end_file(fd, nb_block);
  close(fd);
  if (flags[5] == '1')
    compress_tar(av[2]);
  return (0);
}
