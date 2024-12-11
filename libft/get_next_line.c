/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:37/54 by kfreyer           #+#    #+#             */
/*   Updated: 2024/09/09 17:37:54 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*crud_stash(t_op op, char *new_stash, int fd)
{
	static char	*stash[MAX_FD];
	char		*tmp;

	if (op == SET_STASH)
	{
		free(stash[fd]);
		stash[fd] = ft_strdup(new_stash);
	}
	if (op == DELETE_STASH)
	{
		free(stash[fd]);
		stash[fd] = NULL;
	}
	if (op == UPDATE_STASH)
	{
		tmp = ft_strjoin(stash[fd], new_stash);
		free(stash[fd]);
		stash[fd] = tmp;
	}
	if (op == GET_STASH)
		if (stash[fd])
			return (ft_strdup(stash[fd]));
	return (NULL);
}

char	*truncate_stash(int fd)
{
	char	*cur_stash;
	char	*ret;
	size_t	count;

	cur_stash = crud_stash(GET_STASH, NULL, fd);
	count = 0;
	if (!cur_stash)
		return (cur_stash);
	while (count < ft_strlen(cur_stash))
	{
		if (cur_stash[count++] == '\n')
		{
			ret = ft_substr(cur_stash, 0, count);
			if (count == ft_strlen(cur_stash))
				crud_stash(DELETE_STASH, NULL, fd);
			else
				crud_stash(SET_STASH, cur_stash + count, fd);
			free(cur_stash);
			return (ret);
		}
	}
	crud_stash(DELETE_STASH, NULL, fd);
	return (cur_stash);
}

char	*get_next_line(int fd, bool unset)
{
	char		*buffer;
	long int	bytes_read;

	if (unset)
		return (crud_stash(DELETE_STASH, NULL, fd));
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		crud_stash(UPDATE_STASH, buffer, fd);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	buffer = NULL;
	if (bytes_read < 0)
		return (crud_stash(DELETE_STASH, NULL, fd));
	return (truncate_stash(fd));
}
