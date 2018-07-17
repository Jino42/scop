/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:32:57 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/17 15:32:58 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

cJSON			*json_load_src(const char *path, char *buffer)
{
	cJSON	*ptr;
	int		fd;

	if (!(fd = open(path, O_RDONLY)))
		return (NULL);
	read(fd, buffer, MAX_SOURCE_SIZE);
	close(fd);
	ptr = cJSON_Parse(buffer);
	if (!ptr)
		json_error(NULL);
	return (ptr);
}
