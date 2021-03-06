/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 15:32:37 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/07/17 15:33:24 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

bool		json_error(void *ptr)
{
	if (ptr)
		(void)ptr;
	printf("Error JSON parse: %s\n", cJSON_GetErrorPtr());
	return (true);
}
