/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbinti-m <dbinti-m@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 00:47:49 by dbinti-m          #+#    #+#             */
/*   Updated: 2025/06/07 04:08:38 by dbinti-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char const *stash)
{
	size_t	len;
	char	*line;
	char	*newline;

	if (!stash || !(*stash))
		return (NULL);
	newline = ft_strchr(stash, '\n');
	if (newline)
		len = newline - stash + 1;
	else
		len = ft_strlen(stash);
	line = ft_strndup(stash, len);
	return (line);
}

char	*update_stash(char *stash)
{
	char	*npos;
	char	*new_stash;

	if (!stash || !(*stash))
		return (NULL);
	npos = ft_strchr(stash, '\n');
	if (!npos)
	{
		free (stash);
		return (NULL);
	}
	new_stash = ft_strdup(npos + 1);
	free (stash);
	if (!new_stash || !(*new_stash))
		return (free (new_stash), NULL);
	return (new_stash);
}

char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!(ft_strchr(stash, '\n')) && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free (buffer), free (stash), NULL);
		buffer[bytes] = '\0';
		temp = ft_strjoin(stash, buffer);
		if (!temp || !(*temp))
		{
			free (temp);
			free (buffer);
			return (free (stash), NULL);
		}
		free (stash);
		stash = temp;
	}
	return (free (buffer), stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd == -1)
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
	{
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}

/* #include <fcntl.h>    // for open()
#include <stdio.h>    // for printf()

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open failed");
        return (1);
    }

    while ((line = get_next_line(fd)))
    {
        printf("GNL: %s", line);
        free(line);
    }

    close(fd);
    return (0);
} */
