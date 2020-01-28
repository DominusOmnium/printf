/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 10:51:29 by dkathlee          #+#    #+#             */
/*   Updated: 2020/01/28 13:25:14 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <wchar.h>

static t_double				get_float(t_printf *p)
{
	t_double	res;

	if (p->spec == sp_L)
		res.f = (double)va_arg(p->args, long double);
	else
		res.f = va_arg(p->args, double);
	return (res);
}

static t_ldouble				get_lfloat(t_printf *p)
{
	t_ldouble	res;

	if (p->spec == sp_L)
		res.f = va_arg(p->args, long double);
	else
		res.f = va_arg(p->args, double);
	return (res);
}

static unsigned long long	get_uint(t_printf *p)
{
	unsigned long long	res;

	if (p->spec == sp_hh)
		res = (unsigned char)va_arg(p->args, unsigned long long);
	else if (p->spec == sp_h)
		res = (unsigned short)va_arg(p->args, unsigned long long);
	else if (p->spec == sp_l)
		res = (unsigned long)va_arg(p->args, unsigned long long);
	else if (p->spec == sp_ll)
		res = va_arg(p->args, unsigned long long);
	else if (p->spec == sp_j)
		res = (uintmax_t)va_arg(p->args, unsigned long long);
	else if (p->spec == sp_z)
		res = (size_t)va_arg(p->args, unsigned long long);
	else if (p->spec == sp_t)
		res = (ptrdiff_t)va_arg(p->args, unsigned long long);
	else
		res = (unsigned int)va_arg(p->args, unsigned long long);
	return (res);
}

static long long			get_int(t_printf *p)
{
	long long	res;

	if (p->spec == sp_hh)
		res = (char)va_arg(p->args, long long);
	else if (p->spec == sp_h)
		res = (short)va_arg(p->args, long long);
	else if (p->spec == sp_l)
		res = (long)va_arg(p->args, long long);
	else if (p->spec == sp_ll)
		res = va_arg(p->args, long long);
	else if (p->spec == sp_j)
		res = (intmax_t)va_arg(p->args, long long);
	else if (p->spec == sp_z)
		res = (size_t)va_arg(p->args, long long);
	else if (p->spec == sp_t)
		res = (ptrdiff_t)va_arg(p->args, long long);
	else
		res = (int)va_arg(p->args, long long);
	return (res);
}

static char					*pointer_to_str(t_printf *p)
{
	char		*tmp;
	char		*res;
	long long	pnt;

	pnt = va_arg(p->args, long long);
	tmp = ft_itoa_base(pnt, "0123456789abcdef");
	res = ft_strnew((!pnt && !p->precision ? 0 : ft_strlen(tmp)) + 2);
	res[0] = '0';
	res[1] = 'x';
	if (!(!pnt && !p->precision))
		ft_strcpy(res + 2, tmp);
	ft_memdel((void**)&tmp);
	return (res);
}

long						get_char(t_printf *p)
{
	long	res;

	if (p->type == type_percent)
		return ('%');
	if (p->spec == sp_l)
		res = (unsigned int)va_arg(p->args, unsigned int);
	else
		res = (char)va_arg(p->args, int);
	return (res);
}

char						*char_to_str(int c)
{
	char	*res;

	if (c <= 127)
	{
		res = ft_strnew(1);
		res[0] = c;
	}
	if (c > 127 && c <= 2047)
	{
		res = ft_strnew(2);
		res[0] = (c >> 6) + 192;
		res[1] = ((c & 63) + 128);
	}
	if (c > 2047 && c <= 65535)
	{
		res = ft_strnew(3);
		res[0] = (c >> 12) + 224;
		res[1] = ((c >> 6) & 63) + 128;
		res[2] = ((c & 63) + 128);
	}
	if (c >= 65536)
	{
		res = ft_strnew(4);
		res[0] = (c >> 18) + 240;
		res[1] = ((c >> 12) & 63) + 128;
		res[2] = ((c >> 6) & 63) + 128;
		res[3] = ((c & 63) + 128);
	}
	return (res);
}

char						*str_w(wchar_t *str, t_printf *p)
{
	char	*res;
	char	*tmp;
	char	*tmp1;

	res = ft_memalloc(1);
	while (*str != '\0')
	{
		tmp = char_to_str((int)*str);
		if (((int)(ft_strlen(res) + ft_strlen(tmp)) > p->precision)
												&& p->precision != -1)
				break ;
		tmp1 = ft_strjoin(res, tmp);
		ft_memdel((void**)&res);
		res = tmp1;
		ft_memdel((void**)&tmp);
		str++;
	}
	return (res);
}

char						*get_str_from_arg(const char **format, t_printf *p)
{
	char	*res;
	void	*tmp;

	if (p->type & (type_char | type_percent))
		res = char_to_str(get_char(p));
	else if (p->type == type_str && p->spec == sp_l)
	{
		tmp = va_arg(p->args, wchar_t*);
		res = tmp ? str_w(tmp, p) : ft_strcpy(ft_strnew(6), "(null)");
	}
	else if (p->type == type_str && p->spec != sp_l)
	{
		tmp = va_arg(p->args, char*);
		res = tmp ? ft_strdup(tmp) : ft_strcpy(ft_strnew(6), "(null)");
	}
	else if (p->type == type_float && p->spec != sp_L)
		res = float_to_str((t_double){.f = va_arg(p->args, double)}, p);
	else if (p->type == type_float && p->spec == sp_L)
		res = lfloat_to_str((t_ldouble){.f = va_arg(p->args, long double)}, p);
	else if (p->type == type_int)
		res = ft_itoa(get_int(p));
	else if (p->type == type_unsigned)
		res = ft_itoa_base(get_uint(p), "0123456789");
	else if (p->type == type_pointer)
		res = pointer_to_str(p);
	else if (p->type & (type_hex_high | type_hex_low))
		res = ft_itoa_base(get_uint(p), p->type & type_hex_low ?
									"0123456789abcdef" : "0123456789ABCDEF");
	else if (p->type == type_octal)
		res = ft_itoa_base(get_uint(p), "01234567");
	return (res);
}
