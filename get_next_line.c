/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:36:51 by hyeongki          #+#    #+#             */
/*   Updated: 2022/03/27 00:14:15 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*cut_line(char *save)
{
	char	*ret;
	int		i;
	char	*tmp;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	ret = ft_substr(save, 0, i + 1);
	tmp = ft_substr(save, i + 2, ft_strlen(save));
	free(save);
	save = tmp;
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf;
	ssize_t		read_byte;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	read_byte = 1;
	while (!(ft_strchr(save, '\n')) && read_byte != 0)
	{	
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_byte] = 0;
		if (!save)
			tmp = ft_strdup(buf);
		else
			tmp = ft_strjoin(save, buf);
		free(save);
		save = tmp;
	}
	free(buf);
	return (cut_line(save));
}
