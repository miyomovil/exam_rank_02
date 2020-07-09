/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antomart <antomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 16:50:36 by antomart          #+#    #+#             */
/*   Updated: 2020/07/09 17:36:10 by antomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif

#include <unistd.h>
#include <stdlib.h>

int get_next_line(char **line);

#endif