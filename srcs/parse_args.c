/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 10:51:29 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/26 13:53:06 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static double				get_float(t_printf *p)
{
	double	res;

	if (p->spec == sp_L)
		res = va_arg(p->args, long double);
	else
		res = va_arg(p->args, double);
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

char						*get_str_from_arg(const char **format, t_printf *p)
{
	char	*res;
	char	*tmp;

	if (p->type & (type_char | type_percent))
	{
		res = ft_strnew(1);
		res[0] = (p->type == type_char) ? (char)va_arg(p->args, int) : '%';
	}
	else if (p->type == type_str)
	{
		tmp = va_arg(p->args, char*);
		res = tmp ? ft_strdup(tmp) : ft_strcpy(ft_strnew(6), "(null)");
	}
	/*else if (p->type == type_float)
		res = double_to_str(get_float(p));*/
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
