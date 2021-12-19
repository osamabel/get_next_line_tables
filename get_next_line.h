#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char	*str);
char	*read_and_store(int	fd, char **line,char **lost_chars);
char	*ft_strjoin(char **first, char **secend);
void	ft_strsplit(char *buffer, char **last_chars, char **lost_chars, size_t check);
size_t	check_end_of_line(char	*buf);
char	*ft_strdup(const char *s1);
void	creat_line(char	**line, char **lost_chars, char	**last_chars, char **buffer);
void	ft_strncpy(char *dest, const char *src, size_t len);
#endif