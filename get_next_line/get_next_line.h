/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: trstn4 <trstn4@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 13:52:50 by tvan-bee      #+#    #+#                 */
/*   Updated: 2022/12/07 12:41:17 by trstn4        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

char	*ft_strchr(char *s, char c);
int		ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2, unsigned int i, unsigned int j);
char	*ft_substr(char *s, size_t len);

#endif
