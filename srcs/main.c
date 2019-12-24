/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:53:15 by marvin            #+#    #+#             */
/*   Updated: 2019/12/24 14:04:13 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_percent(const char **format, t_printf *p)
{
	char	*tmp;
	char	*tmp1;

	(*format)++;
	check_flags_and_specs(format, p);
	tmp = get_str_from_arg(format, p);
	set_flags(&tmp, p);
	set_precision(&tmp, p);
	set_width(&tmp, p);
	tmp1 = ft_strjoin(p->print, tmp);
	ft_memdel((void**)&(p->print));
	p->print_num += ft_strlen(tmp);
	if (p->type == type_char && ft_strlen(tmp) == 0)
		p->print_num++;
	ft_memdel((void**)&(tmp));
	p->print = tmp1;
}

void	parse_string(const char **format, t_printf *p)
{
	int		i;
	char	*tmp;
	char	*tmp1;

	i = 0;
	while ((*format)[i] != '%' && (*format)[i] != 0)
		i++;
	p->print_num += i;
	tmp1 = ft_strsub(*format, 0, i);
	tmp = ft_strjoin(p->print, tmp1);
	ft_memdel((void**)&(p->print));
	ft_memdel((void**)&tmp1);
	p->print = tmp;
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

int		main(void)
{
	printf("%d\n", printf("befor**%#.10x**after\n", 10));
	return (0);
}
