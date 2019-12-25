/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 10:17:24 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/25 16:34:24 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reset(t_printf *p)
{
	p->flags = (t_flags){false, false, false, false, false};
	p->precision = -1;
	p->width = -1;
	p->spec = sp_none;
	p->type = type_none;
}

int		is_flag(char c)
{
	if (c == '+' || c == '-' || c == ' ' || c == '0' || c == '#')
		return (true);
	return (false);
}

int		is_spec(char c)
{
	if (c == 'h' || c == 'l' || c == 'L' || c == 'j' || c == 'z' || c == 't')
		return (true);
	return (false);
}

int		is_type(char c)
{
	if (c == 'd' || c == 'i' || c == 'u' || c == 'o' || c == 'x' || c == 'X'
		|| c == 'f' || c == 'F' || c == 'c' || c == 's' || c == 'p' || c == '%'
		|| c == 'U')
		return (true);
	return (false);
}
