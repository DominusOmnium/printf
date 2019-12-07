/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:53:15 by marvin            #+#    #+#             */
/*   Updated: 2019/12/03 16:53:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reset(t_printf *p)
{
	p->flags = (t_flags){false, false, false, false, false};
	p->precision = -1;
	p->width = -1;
	p->spec = sp_none;
}

int		ft_printf(const char *format, ...)
{
	va_list		args;
	t_printf	*p;

	va_start(args, format);
	p = ft_memalloc(sizeof(t_printf));
	reset(p);
	p->print_num = 0;
	p->print = NULL;
	while (format)
	{
		if ()
	}
	write(1, p->print, p->print_num);
	return (0);
}


int		main()
{
	return (ft_printf("", 1));
}
