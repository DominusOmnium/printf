/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 11:49:26 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/25 15:32:13 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_percent(const char **format, t_printf *p)
{
	char	*tmp;
	char	*tmp1;
	int		pr;

	(*format)++;
	check_flags_and_specs(format, p);
	if (p->type == type_none)
		return ;
	tmp = get_str_from_arg(format, p);
	set_flags(&tmp, p);
	set_precision(&tmp, p);
	pr = set_width(&tmp, p);
	p->print = ft_realloc(p->print, p->print_num, p->print_num + pr);
	ft_memcpy(p->print + p->print_num, tmp, pr);
	p->print_num += pr;
	ft_memdel((void**)&(tmp));
}

void	parse_string(const char **format, t_printf *p)
{
	int		i;

	i = 0;
	while ((*format)[i] != '%' && (*format)[i] != 0)
		i++;
	p->print = ft_realloc(p->print, p->print_num, p->print_num + i);
	ft_memcpy(p->print + p->print_num, *format, i);
	p->print_num += i;
	*format += i;
}

int		ft_printf(const char *format, ...)
{
	t_printf	*p;
	int			print_num;

	p = ft_memalloc(sizeof(t_printf));
	va_start(p->args, format);
	p->print_num = 0;
	p->print = ft_strnew(0);
	while (*format)
	{
		reset(p);
		if (*format == '%')
			parse_percent(&format, p);
		else
			parse_string(&format, p);
	}
	write(1, p->print, p->print_num);
	ft_memdel((void**)&(p->print));
	print_num = p->print_num;
	ft_memdel((void**)&p);
	return (print_num);
}
