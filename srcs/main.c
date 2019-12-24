/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:53:15 by marvin            #+#    #+#             */
/*   Updated: 2019/12/24 09:09:31 by marvin           ###   ########.fr       */
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
		if (**f != '0')
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
		else
			(*f)++;
	}
	parcing_format(f, p);
}

void	set_hashtag(char **str, t_printf *p)
{
	char	*tmp;

	if (**str == '-' || **str == '0')
		return ;
	tmp = ft_strnew(ft_strlen(*str) + 1);
	*tmp = '+';
	ft_strcpy(tmp + 1, *str);
	ft_memdel((void**)str);
	*str = tmp;
}

void	set_flags(char **str, t_printf *p)
{
	if (p->type == type_str || p->type == type_char)
		return;
	if (p->flags.plus && (p->type & (type_float | type_int | type_unsigned)) != 0)
		set_hashtag(str, p);
}

void	set_precision(char **str, t_printf *p)
{
	char	*tmp;
	int		cl;
	char	zn;

	cl = ft_strlen(*str);
	if ((p->type & (type_char | type_percent | type_str)) != 0
									|| cl >= p->precision)
		return ;
	zn = (**str == '-' || **str == '+') ? true : false;
	tmp = ft_strnew(zn ? (p->precision + 1) : p->precision);
	ft_memset(zn ? (tmp + 1) : tmp, '0', p->precision - cl);
	if (zn)
		tmp[0] = **str;
	zn ? ft_strcpy(tmp + p->precision - cl + 1, *str + 1) :
			ft_strcpy(tmp + p->precision - cl, *str);
	ft_memdel((void**)str);
	*str = tmp;
}

void	set_width(char **str, t_printf *p)
{
	char	*tmp;
	int		cur_len;

	cur_len = ft_strlen(*str);
	if (cur_len >= p->width)
		return ;
	tmp = ft_strnew(p->width);
	if (p->flags.minus)
	{
		tmp = ft_strcpy(tmp, *str);
		ft_memset(tmp + cur_len,
				(p->flags.zero && p->precision == -1) ? '0' : ' ', p->width - cur_len);
	}
	else
	{
		ft_memset(tmp,
				(p->flags.zero && p->precision == -1) ? '0' : ' ', p->width - cur_len);
		ft_strcpy(tmp + p->width - cur_len, *str);
	}
	ft_memdel((void**)str);
	*str = tmp;
}

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
	/*printf("**%020p**", c);*/
	ft_printf("%d\n", ft_printf("befor**%020.10d**after\n", -20));
	return (0);
}
