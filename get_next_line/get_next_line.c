/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antomart <antomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 15:18:07 by antomart          #+#    #+#             */
/*   Updated: 2020/07/07 15:42:03 by antomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned int ft_strlen(char *str)
{
	unsigned int i;
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_strchr(char *str, int c)
{
	int i;
	int len;
	i = 0;
	if (!str)
		return(0);
	len = ft_strlen(str);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] != c && i == len)
		return (0);
	return (1);
}

char *ft_strdup(char *str)
{
	int i;
	int len;
	char *str2;
	i = 0;
	len = ft_strlen(str);
	str2 = (char *)malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}

char *ft_strjoin(char *str1, char *str2)
{
	int i;
	int j;
	int len1;
	int len2;
	char *str3;
	i = 0;
	j = 0;
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	str3 = (char *)malloc(sizeof(char)* (len1 + len2 +1));
	while (str1[i])
	{
		str3[i] = str1[i];
		i++;
	}
	while(str2[j])
	{
		str3[i + j] = str2[j];
		j++;
	}
	str3[i + j] = '\0';
	return(str3);
}

char *ft_substr(char *str, int start, int len)
{
	int i;
	char *str2;
	i = 0;
	str2 = (char *)malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		str2[i] = str[start + i];
		i++;
	}
	str2[i] = '\0';
	return(str2);
}

int read_line(char **line, char **s)
{
	char *aux;
	int len;
	len = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\0')
		len++;
	if ((*s)[len] == '\n')
	{
		*line = ft_substr((*s), 0, len);
		aux = ft_strdup(&(*s)[len + 1]);
		free(*s);
		(*s) = aux;
	}
	else
	{
		*line = ft_strdup(*s);
		free(*s);
		(*s) = NULL;
		return (0);
	}
	return (1);
}

int get_next_line(char **line)
{
	char *aux;
	int n_bytes;
	char buff[BUFFER_SIZE + 1];
	static char *s;

	if (!line)
		return (-1);
	while (ft_strchr(s, '\n') == 0)
	{
		n_bytes = read(0, buff, BUFFER_SIZE);
		if (n_bytes < 0)
			return (-1);
		if (n_bytes == 0)
			break;
		buff[n_bytes] = '\0';
		if (!s)
			s = ft_strdup(buff);
		else
		{
			aux = ft_strjoin(s, buff);
			free(s);
			s = aux;
		}
	}
	if (!s && n_bytes == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return(read_line(line, &s));
}