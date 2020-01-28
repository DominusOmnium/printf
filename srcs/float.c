/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 14:20:21 by dkathlee          #+#    #+#             */
/*   Updated: 2020/01/28 16:10:29 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*insert_point(char *nbr, int len, int exponent, t_printf *p)
{
	char	*tmp;
	int		pr;
	int		itmp;

	pr = p->precision == -1 ? 7 : p->precision + 1;
	tmp = ft_strnew(len - 52 + pr + 1);
	if (exponent >= 1023)
	{
		ft_memcpy(tmp, nbr, len - 52);
		tmp[len - 52] = '.';
		ft_memcpy(tmp + len - 51, nbr + len - 52, pr > 52 ? 52 : pr);
		ft_memset(tmp + len + 1, '0', pr - 52 <= 0 ? 0 : pr - 52);
	}
	else
	{
		ft_memcpy(tmp, "0.", 2);
		itmp = 52 + (1023 - exponent) - len > pr ? pr : 52 + (1023 - exponent) - len;
		ft_memset(tmp + 2, '0', itmp);
		if (pr - itmp > 0)
			ft_memcpy(tmp + 2 + itmp, nbr, pr - itmp > len ? len : pr - itmp);
		ft_memset(tmp + itmp + len + 2, '0', pr - len - itmp + 1 <= 0 ? 0 : pr - len - itmp);
	}
	return (tmp);
}

static char	*insert_point_long(char *nbr, int len, int exponent, t_printf *p)
{
	char	*tmp;
	int		pr;
	int		itmp;

	pr = p->precision == -1 ? 7 : p->precision + 1;
	tmp = ft_strnew(len - 63 + pr + 1);
	if (exponent >= 16383)
	{
		ft_memcpy(tmp, nbr, len - 63);
		tmp[len - 63] = '.';
		ft_memcpy(tmp + len - 62, nbr + len - 63, pr > 63 ? 63 : pr);
		ft_memset(tmp + len + 1, '0', pr - 63 <= 0 ? 0 : pr - 63);
	}
	else
	{
		ft_memcpy(tmp, "0.", 2);
		itmp = 63 + (16383 - exponent) - len > pr ? pr : 63 + (16383 - exponent) - len;
		ft_memset(tmp + 2, '0', itmp);
		if (pr - itmp > 0)
			ft_memcpy(tmp + 2 + itmp, nbr, pr - itmp > len ? len : pr - itmp);
		ft_memset(tmp + itmp + len + 2, '0', pr - len - itmp + 1 <= 0 ? 0 : pr - len - itmp);
	}
	return (tmp);
}


static void	float_round(char **nbr, int len)
{
	char	tmp;
	int		i;

	len--;
	i = len;
	if ((*nbr)[len] >= '5')
	{	
		while (((*nbr)[--len] >= '5' || (*nbr)[len] == '.') && len != -1)
		{
			if ((*nbr)[len] != '9')
				break ;
			if ((*nbr)[len] == '.')
				continue ;
			(*nbr)[len] = '0';
		}
		if (len == -1)
		{
			tmp = (*nbr)[++len];
			(*nbr)[len] = '1';
			while (++len != i)
			{
				(*nbr)[len] = tmp;	
				tmp = (*nbr)[len + 1];
			}
		}
		else
			(*nbr)[len]++;
	}
	(*nbr)[i] = 0;
}

char	*float_to_str(t_double f, t_printf *p)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		itmp;

	tmp2 = ft_itoa_base(f.parts.mantisa, "0123456789");
	tmp = long_mul(tmp2, "2220446049250313080847263336181640625");
	ft_memdel((void**)&tmp2);
	itmp = 52 - ft_strlen(tmp);
	tmp2 = ft_strnew(ft_strlen(tmp) + itmp + 1);
	tmp2[0] = '1';
	ft_memset(tmp2 + 1, '0', itmp);
	ft_strcpy(tmp2 + itmp + 1, tmp);
	ft_memdel((void**)&tmp);
	if (f.parts.exponent >= 1023)
		tmp3 = long_pow("2", f.parts.exponent - 1023);
	else
		tmp3 = long_pow("5", 1023 - f.parts.exponent);
	tmp = long_mul(tmp2, tmp3);
	ft_memdel((void**)&tmp3);
	ft_memdel((void**)&tmp2);
	tmp2 = insert_point(tmp, ft_strlen(tmp), f.parts.exponent, p);
	ft_memdel((void**)&tmp);
	float_round(&tmp2, ft_strlen(tmp2));
	if (f.parts.sign == 1)
	{
		tmp = tmp2;
		tmp2 = ft_strnew(ft_strlen(tmp2) + 1);
		tmp2[0] = '-';
		ft_strcpy(tmp2 + 1, tmp);
		ft_memdel((void**)&tmp);
	}
	return (tmp2);
}

char	*lfloat_to_str(t_ldouble f, t_printf *p)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		itmp;

	tmp2 = ft_itoa_base(f.parts.mantisa, "0123456789");
	tmp = long_mul(tmp2, "108420217248550443400745280086994171142578125");
	ft_memdel((void**)&tmp2);
	itmp = 63 - ft_strlen(tmp);
	tmp2 = ft_strnew(ft_strlen(tmp) + itmp + 1);
	tmp2[0] = '1';
	ft_memset(tmp2 + 1, '0', itmp);
	ft_strcpy(tmp2 + itmp + 1, tmp);
	ft_memdel((void**)&tmp);
	if (f.parts.exponent >= 16383)
		tmp3 = long_pow("2", f.parts.exponent - 16383);
	else
		tmp3 = long_pow("5", 16383 - f.parts.exponent);
	tmp = long_mul(tmp2, tmp3);
	ft_memdel((void**)&tmp3);
	ft_memdel((void**)&tmp2);
	tmp2 = insert_point_long(tmp, ft_strlen(tmp), f.parts.exponent, p);
	ft_memdel((void**)&tmp);
	float_round(&tmp2, ft_strlen(tmp2));
	if (f.parts.sign == 1)
	{
		tmp = tmp2;
		tmp2 = ft_strnew(ft_strlen(tmp2) + 1);
		tmp2[0] = '-';
		ft_strcpy(tmp2 + 1, tmp);
		ft_memdel((void**)&tmp);
	}
	return (tmp2);
}
