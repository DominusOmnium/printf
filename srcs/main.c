/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:53:15 by marvin            #+#    #+#             */
/*   Updated: 2019/12/19 23:56:56 by marvin           ###   ########.fr       */
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

int		is_flag(char c)
{
	if (c == '+' || c == '-' || c == ' ' || c == '0' || c == '#')
		return (true);
	return (false);
}

int		is_type(char c)
{
	if (c == 'd' || c == 'i' || c == 'u' || c == 'o' || c == 'x' || c == 'X'
		|| c == 'f' || c == 'F' || c == 'c' || c == 's' || c == 'p' || c == '%')
		return (true);
	return (false);
}

void	parcing_format(const char **f, t_printf *p)
{
	if (**f == 'd' || **f == 'i')
		p->type = type_int;
	else if (**f == 'u')
		p->type = type_unsigned;
	else if (**f == 'o')
		p->type = type_octal;
	else if (**f == 'x')
		p->type = type_hex_low;
	else if (**f == 'X')
		p->type = type_hex_high;
	else if (**f == 'f')
		p->type = type_float;
	else if (**f == 'c')
		p->type = type_char;
	else if (**f == 's')
		p->type = type_str;
	else if (**f == 'p')
		p->type = type_pointer;
	else if (**f == '%')
		p->type = type_percent;
	if (ft_isupper(**f))
		p->spec = (**f == 'F') ? sp_L : sp_ll;
	(*f)++;
}

void	check_flags(const char *f, t_printf *p)
{
	if (*f == '#')
		p->flags.hashtag = true;
	else if (*f == '-')
		p->flags.minus = true;
	else if (*f == '+')
		p->flags.plus = true;
	else if (*f == ' ')
		p->flags.space = true;
	else if (*f == '0')
		p->flags.zero = true;
	if (*f == 'h' && *(f + 1) == 'h' && p->spec < sp_hh)
		p->spec = sp_hh;
	else if (*f == 'h' && *(f + 1) != 'h' && p->spec < sp_h)
		p->spec = sp_h;
	else if (*f == 'l' && *(f + 1) != 'l' && p->spec < sp_l)
		p->spec = sp_l;
	else if (*f == 'l' && *(f + 1) == 'l' && p->spec < sp_ll)
		p->spec = sp_ll;
	else if (*f == 'L')
		p->spec = sp_L;
}
void	check_flags_and_specs(const char **f, t_printf *p)
{
	while (!is_type(**f) && **f)
	{
		check_flags(*f, p);
		while (ft_isdigit(**f))
		{
			p->width = (p->width == -1) ? ft_atoi(*f) : p->width;
			(*f)++;
			if (**f == '.')
			{
				(*f)++;
				p->precision = ft_atoi(*f);
			}
		}
		(*f)++;
	}
	parcing_format(f, p);
}

void	parse_percent(const char **format, t_printf *p)
{
	char	*tmp;
	char	*tmp1;

	(*format)++;
	check_flags_and_specs(format, p);
	tmp = get_str_from_arg(format, p);
	

	
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

	p = ft_memalloc(sizeof(t_printf));
	va_start(p->args, format);
	reset(p);
	p->print_num = 0;
	p->print = ft_strnew(0);
	while (*format)
	{
		if (*format == '%')
			parse_percent(&format, p);
		else
			parse_string(&format, p);
	}
	write(1, p->print, p->print_num);
	ft_memdel((void**)&p->print);
	ft_memdel((void**)&p);
	return (p->print_num);
}

int		main(void)
{
	/*printf("**%12.5d**", 15);*/
	ft_printf("%d\n", ft_printf("befor**% +-10.20lld**after\n", 5));
	return (0);
}
