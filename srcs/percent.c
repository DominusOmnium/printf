/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 10:22:41 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/24 14:01:27 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		if (**f > '0' && **f <= '9')
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
	if (zn)
		tmp[0] = **str;
	ft_memset(zn ? (tmp + 1) : tmp, '0', p->precision - cl + (zn ? 1 : 0));
	zn ? ft_strcpy(tmp + p->precision - cl + 2, *str + 1) :
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
		ft_memset(tmp + cur_len, (p->flags.zero && p->precision == -1) ?
									'0' : ' ', p->width - cur_len);
	}
	else
	{
		ft_memset(tmp, (p->flags.zero && p->precision == -1) ?
									'0' : ' ', p->width - cur_len);
		ft_strcpy(tmp + p->width - cur_len, *str);
	}
	ft_memdel((void**)str);
	*str = tmp;
}
