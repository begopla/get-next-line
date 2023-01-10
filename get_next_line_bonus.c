/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:33:36 by bpla-rub          #+#    #+#             */
/*   Updated: 2022/12/07 10:08:05 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_and_store(int fd, char *buf, char *save)
{
	int		readed_bytes;
	char	*temp;

	readed_bytes = 1;
	while (readed_bytes != '\0')
	{
		readed_bytes = read(fd, buf, BUFFER_SIZE);
		if (readed_bytes == -1)
			return (0);
		else if (readed_bytes == 0)
			break ;
		buf[readed_bytes] = '\0';
		if (!save)
			save = ft_strdup("");
		temp = save;
		save = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strchr (buf, '\n'))
			break ;
	}
	return (save);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*new;
	int		i;
	int		j;

	if (!s)
		return (0);
	new = ft_create_str(s, start, len);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (j < len && i >= start)
		{
			new[j] = s[start + j];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	*extract(char *line)
{
	int		len;
	char	*str;

	len = 0;
	while (line[len] != '\n' && line[len] != '\0')
		len++;
	if (line[len] == '\0')
		return (0);
	str = ft_substr(line, len + 1, ft_strlen(line) - len);
	line[len + 1] = '\0';
	if (str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*maxsave[1024];
	size_t		intoverflow;

	intoverflow = (size_t)BUFFER_SIZE;
	if (fd < 0 || fd > 1024 || intoverflow <= 0)
		return (0);
	buf = malloc(sizeof(char) * (intoverflow + 1));
	if (!buf)
		return (0);
	line = read_and_store(fd, buf, maxsave[fd]);
	free(buf);
	if (!line)
		return (NULL);
	maxsave[fd] = extract(line);
	return (line);
}
