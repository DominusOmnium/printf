/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 10:51:29 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/24 10:21:57 by dkathlee         ###   ########.fr       */
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
	else
		res = (int)va_arg(p->args, long long);
	return (res);
}

char						*get_str_from_arg(const char **format, t_printf *p)
{
	char	*res;
	char	*tmp;

	if (p->type == type_char)
	{
		res = ft_strnew(1);
		res[0] = (char)va_arg(p->args, int);
	}
	else if (p->type == type_str)
	{
		tmp = va_arg(p->args, char*);
		res = ft_strcpy(ft_strnew(ft_strlen(tmp)), tmp);
	}
	/*else if (p->type == type_float)
		res = double_to_str(get_float(p));*/
	else if (p->type == type_int)
		res = ft_itoa(get_int(p));
	/*else if (p->type == type_pointer)
		res = pointer_to_str(va_arg(p->args, void*));*/
	else/* if (p->type & (type_unsigned | type_hex_high | type_hex_low | type_octal))*/
		res = ft_itoa(get_uint(p));
	return (res);
}
