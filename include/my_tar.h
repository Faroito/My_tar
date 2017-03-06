/*
** my_tar.h for my_tar in /home/timothee.couble/Epitech/Semester_2/C_Prog_Elem/Rush2
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Fri Mar  3 23:05:59 2017 Timothée Couble
** Last update Sun Mar  5 22:57:44 2017 Timothée Couble
*/

#ifndef MY_TAR_H
# define MY_TAR_H

typedef struct  s_tar
{                                /* byte offset */
  char  name[100];               /*   0 */
  char  mode[8];                 /* 100 */
  char  uid[8];                  /* 108 */
  char  gid[8];                  /* 116 */
  char  size[12];                /* 124 */
  char  mtime[12];               /* 136 */
  char  chksum[8];               /* 148 */
  char  typeflag;                /* 156 */
  char  linkname[100];           /* 157 */
  char  magic[6];                /* 257 */
  char  version[2];              /* 263 */
  char  uname[32];               /* 265 */
  char  gname[32];               /* 297 */
  char  devmajor[8];             /* 329 */
  char  devminor[8];             /* 337 */
  char  prefix[167];             /* 345 */
                                 /* 512 */
}		t_tar;

void    error(char *msg);
void    my_str_cpy(char *str1, char *str2, int n);
void    my_put_in_str(unsigned int nbr, char *str, int max);
int     my_get_octal(unsigned int nb);
void    file_exist(int ac, char **av, char *flags);
int     my_archive(int ac, char **av, char *flags);
int     add_all_struct(t_tar *tar);
char    testing_file(mode_t st_mode, char *name);
void    my_get_mtime(int nb, char *str);
void    access_mode(char *str, struct stat sb);
void	read_symlink(t_tar *tar, char *name);
int	write_repository(int fd_dest, char *name_dir, char *flags);
int	write_tar(int fd_dest, char *name, char *flags);
void    end_file(int fd, int nb_block);
int     my_unarchive(int ac, char **av, char *flags);
int     my_strn_cpy(char *str1, char *str2, int i, int max);
int     my_list_files(int ac, char **av);
long long	my_get_decimal(char *str);
void    compress_tar(char *name);
void	decompress_gz(char *name);
void	replace_archive(char *name);
int     my_power_rec(int nb, int p);

#endif /* !MY_TAR_H */
