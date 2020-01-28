/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 10:22:41 by dkathlee          #+#    #+#             */
/*   Updated: 2020/01/28 13:02:49 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parcing_format(const char **f, t_printf *p)
{
	if (**f == 'd' || **f == 'i' || **f == 'D' || **f == 'I')
		p->type = type_int;
	else if (**f == 'u' || **f == 'U')
		p->type = type_unsigned;
	else if (**f == 'o' || **f == 'O')
		p->type = type_octal;
	else if (**f == 'x')
		p->type = type_hex_low;
	else if (**f == 'X')
		p->type = type_hex_high;
	else if (**f == 'f')
		p->type = type_float;
	else if (**f == 'c' || **f == 'C')
		p->type = type_char;
	else if (**f == 's' || **f == 'S')
		p->type = type_str;
	else if (**f == 'p')
		p->type = type_pointer;
	else if (**f == '%')
		p->type = type_percent;
	if (ft_isupper(**f) && **f != 'X')
	{
		if (**f == 'C' || **f == 'S')
			p->spec = sp_l;
		else
			p->spec = (**f == 'F') ? sp_L : sp_ll;
	}
	if (p->type != type_none)
		(*f)++;
}

void	check_flags(const char *f, t_printf *p)
{
	if (*f == '#')
		p->flags.hashtag = TRUE;
	else if (*f == '-')
		p->flags.minus = TRUE;
	else if (*f == '+')
		p->flags.plus = TRUE;
	else if (*f == ' ')
		p->flags.space = TRUE;
	else if (*f == '0')
		p->flags.zero = TRUE;
	if (*f == 'h' && *(f + 1) == 'h' && p->spec < sp_hh)
		p->spec = sp_hh;
	else if (*f == 'h' && *(f + 1) != 'h' && *(f - 1) != 'h' && p->spec < sp_h)
		p->spec = sp_h;
	else if (*f == 'l' && *(f + 1) != 'l' && p->spec < sp_l)
		p->spec = sp_l;
	else if (*f == 'l' && *(f + 1) == 'l' && p->spec < sp_ll)
		p->spec = sp_ll;
	else if (*f == 'j' && p->spec < sp_j)
		p->spec = sp_j;
	else if (*f == 'z' && p->spec < sp_z)
		p->spec = sp_z;
	else if (*f == 't' && p->spec < sp_t)
		p->spec = sp_t;
	else if (*f == 'L')
		p->spec = sp_L;
}

void	check_flags_and_specs(const char **f, t_printf *p)
{
	while (**f && (is_flag(**f) || is_spec(**f) ||
					ft_isdigit(**f) || **f == '.'))
	{
		check_flags(*f, p);
		if (**f > '0' && **f <= '9')
		{
			p->width = (p->width == -1) ? ft_atoi(*f) : p->width;
			while (ft_isdigit(**f))
				(*f)++;
		}
		else if (**f == '.')
		{
			(*f)++;
			p->precision = (p->precision == -1) ? ft_atoi(*f) : p->precision;
			while (ft_isdigit(**f))
				(*f)++;
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

	if ((p->type & (type_char | type_percent | type_float)) || p->precision == -1)
		return ;
	cl = ft_strlen(*str);
	cl = (cl == 0) ? 1 : cl;
	zn = (**str == '-') ? TRUE : FALSE;
	if (p->type == type_str && cl > p->precision && p->precision != -1)
	{
		tmp = ft_strnew(p->precision);
		ft_strncpy(tmp, *str, p->precision);
	}
	else if (p->precision > cl && p->type == type_pointer)
	{
		tmp = ft_strnew(p->precision + 2);
		ft_strncpy(tmp, *str, 2);
		ft_memset(tmp + 2, '0', p->precision - cl + 2);
		ft_strncpy(tmp + p->precision + 4 - cl, *str + 2, cl - 2);
	}
	else if (p->precision > cl - (zn ? 1 : 0) && p->type != type_str)
	{
		tmp = ft_strnew(zn ? (p->precision + 1) : p->precision);
		if (zn)
			tmp[0] = **str;
		ft_memset(zn ? (tmp + 1) : tmp, '0', p->precision - cl + (zn ? 1 : 0));
		zn ? ft_strcpy(tmp + p->precision - cl + 2, *str + 1) :
				ft_strcpy(tmp + p->precision - cl, *str);
	}
	else if (p->precision == 0 && **str == '0' && p->type != type_pointer)
		tmp = ft_strnew(0);
	else
		return ;
	ft_memdel((void**)str);
	*str = tmp;
}

int		set_width(char **str, t_printf *p)
{
	char	*tmp;
	int		cur_len;

	cur_len = ft_strlen(*str);
	cur_len = (cur_len == 0 && p->type == type_char) ? 1 : cur_len;
	if (cur_len >= p->width)
		return (cur_len);
	if (p->flags.minus)
		set_minus(str, cur_len, p);
	else
	{
		tmp = ft_strnew(p->width);
		if ((**str == '+' || **str == '-' || p->flags.space) && p->flags.zero &&
			p->precision == -1 && (p->type & (type_float | type_int | type_unsigned)))
		{
			tmp[0] = **str;
			ft_memset(tmp + 1, '0', p->width - cur_len);
			ft_strcpy(tmp + p->width - cur_len + 1, *str + 1);
		}
		else if (**str == '0' && ft_tolower(*(*str + 1)) == 'x' && p->flags.zero &&
			(p->type & (type_hex_high | type_hex_low)) && p->precision == -1)
		{
			ft_strncpy(tmp, *str, 2);
			ft_memset(tmp + 2, '0', p->width - cur_len);
			ft_strcpy(tmp + p->width - cur_len + 2, *str + 2);
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
	return (p->width);
}
