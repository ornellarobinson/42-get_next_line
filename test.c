/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafin <orazafin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 10:40:17 by orazafin          #+#    #+#             */
/*   Updated: 2017/03/19 18:37:06 by orazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		open_file(char const *file)
{
	int fd;

	fd = open("/Users/robinson/Documents/Projects_42/Get_Next_Line/file_text.txt", O_RDONLY);
	return (fd);
}

int		end_read(char *str, char *tmp, char *buff, char **line)
{
	char *end_line;

	end_line = ft_strchr((const char *)buff, '\n');
    if (end_line != 0)
    {
        tmp = str;
        str = ft_strdup(end_line + 1);
        *end_line = 0;
        *line = ft_strjoin((char const *) tmp, (char const *) end_line);
        free(tmp);
        printf("%s\n", str);
        return (1);
    }
    return (0);
}

int		get_next_line(int fd, char **line)
{
	static char *str = NULL;
	char buff[BUFF_SIZE + 1];
	int read_octet;
	char *tmp;

	if (!fd)
		return (-1);
	while ((read_octet = read(fd, buff, BUFF_SIZE) != 0)
	&& (ft_strchr((const char *)buff, '\n')) == 0)
	{
		buff[read_octet] = '\0';
		if (!str)
			str = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(str, buff);
			free(str);
			str = tmp;
		}
	}
	return (end_read(str, tmp, buff, line));
}

int		main(int argc, char const *argv[])
{
	int fd;
	int value;
	char *line;

	if ((fd = open_file(argv[1])) == -1)
		return (-1);
	value = get_next_line(fd, &line);
	printf("%d\n", value);
	value = get_next_line(fd, &line);
	printf("%d\n", value);
	value = get_next_line(fd, &line);
	printf("%d\n", value);
	return (0);
}
