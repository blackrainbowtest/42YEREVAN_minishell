/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <aramarak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 11:33:49 by aramarak          #+#    #+#             */
/*   Updated: 2025/09/20 11:34:31 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "status.h"

int	last_status(int mode, int new_value)
{
	static int	status;

	status = 0;
	if (mode == 1)
		status = new_value;
	return (status);
}
