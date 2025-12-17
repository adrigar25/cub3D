/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agarcia <agarcia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:09:47 by agarcia           #+#    #+#             */
/*   Updated: 2025/05/22 17:59:42 by agarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_extract_line(char **reminder)
{
	char	*line;
	char	*new_reminder;
	size_t	i;
	size_t	len;

	if (!reminder || !*reminder || !**reminder)
		return (NULL);
	i = 0;
	while ((*reminder)[i] && (*reminder)[i] != '\n')
		i++;
	len = i + ((*reminder)[i] == '\n');
	line = malloc(len + 1);
	if (!line)
		return (free(*reminder), *reminder = NULL, NULL);
	i = -1;
	while (++i < len)
		line[i] = (*reminder)[i];
	line[i] = '\0';
	if ((*reminder)[len] == '\0')
		return (free(*reminder), *reminder = NULL, line);
	new_reminder = ft_strdup(*reminder + len);
	if (!new_reminder)
		return (free(line), free(*reminder), *reminder = NULL, NULL);
	return (free(*reminder), *reminder = new_reminder, line);
}

static char	*ft_read_until_nl(int fd, char **reminder)
{
	char	*temp;
	int		bytes_read;
	char	buffer[BUFFER_SIZE + 1];

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(*reminder), *reminder = NULL, NULL);
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*reminder, buffer);
		if (!temp)
			return (free(*reminder), *reminder = NULL, NULL);
		free(*reminder);
		*reminder = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*reminder);
}

char	*get_next_line(int fd)
{
	static char	*reminder[2048];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!reminder[fd])
		reminder[fd] = ft_strdup("");
	if (!reminder[fd] || !ft_read_until_nl(fd, &reminder[fd]))
		return (NULL);
	line = ft_extract_line(&reminder[fd]);
	if (!line)
		return (free(reminder[fd]), reminder[fd] = NULL, NULL);
	return (line);
}
