/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/18 10:36:24 by hmartzol          #+#    #+#             */
/*   Updated: 2016/07/18 11:58:46 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** for void *malloc(size_t size), free(void *ptr)
*/
#include <stdlib.h>

/*
** for int open(const char *pathname, int flags)
*/
#include <fcntl.h>

/*
** for int close(int fd), ssize_t read(int fd, void *buf, size_t count)
*/
#include <unistd.h>

/*
** for S_ISREG(m), int stat(const char *pathname, struct stat *buf), struct stat
*/
#include <sys/stat.h>

/*
** Can replace a standard succesive read of fixed size with a single full size
** (relative to the file) read (much faster for heavy files).
** Return the readed file size and the file itself in **out.
** Warning: will erase/loose the content of **out, for best use, pass &(char*)
** initialized at NULL.
** Return -1 if an error is encountered (dosen't change errno by itself, but
** errno might have a code error set by either stat, open, read or close)
** The content of **out might not be null, but will be freed if
** ft_bonus_read returns -1
*/

int	ft_bonus_read(const char *filepath, char **out)
{
	int			fd;
	struct stat	st;

	if (filepath == NULL || out == NULL || (stat(filepath, &st)) == -1
		|| !S_ISREG(st.st_mode) || st.st_size < 1
		|| (fd = open(filepath, O_RDONLY)) == -1)
		return (-1);
	if ((*out = (char*)malloc(sizeof(char) * st.st_size)) == NULL)
	{
		close(fd);
		return (-1);
	}
	if (read(fd, *out, st.st_size) == -1)
	{
		close(fd);
		free(*out);
		return (-1);
	}
	if (close(fd) == -1)
	{
		free(*out);
		return (-1);
	}
	return (st.st_size);
}
