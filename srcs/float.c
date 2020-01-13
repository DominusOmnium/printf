/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 14:20:21 by dkathlee          #+#    #+#             */
/*   Updated: 2020/01/13 18:29:48 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		calc_float_len(t_double f, t_printf *p)
{
	int	res;

	res = 0;
	while (f.f >= 1.0)
	{
		f.f /= 10;
		res++;
	}
	if (p->precision == 0)
		return (res);
	if (res == 0)
		res++;
	return (res + ((p->precision == -1) ? 7 : p->precision + 1));
}

char	*remove_leading_zeros(char **num)
{
	int		i;
	char	*res;

	i = 0;
	while ((*num)[i] == '0')
		i++;
	res = ft_strdup(*num + i);
	ft_memdel((void**)num);
	return (res);
}

char	*long_mul(char *nb1, char *nb2)
{
	char	*res;
	int		tmp;
	int		i;
	int		j;
	int		carry;

	tmp = ft_strlen(nb2);
	res = ft_strnew(ft_strlen(nb1) + tmp);
	ft_memset(res, '0', ft_strlen(nb1) + tmp);
	i = ft_strlen(nb1) - 1;
	while (i >= 0)
	{
		j = tmp - 1;
		carry = 0;
		while (j >= 0 || carry)
		{
			int tmp = (res[i + j + 1] - '0') + (nb1[i] - '0') * (j >= 0 ? (nb2[j] - '0') : 0) + carry;
			res[i + j + 1] = tmp % 10 + '0';
			carry = tmp / 10;
			j--;
		}
		i--;
	}
	res = remove_leading_zeros(&res);
	return (res);
}

char	*long_mul1(char *nb1, char *nb2)
{
	char	*res;
	int		tmp;
	int		i;
	int		j;
	int		carry;

	tmp = ft_strlen(nb2);
	res = ft_strnew(ft_strlen(nb1) + tmp);
	ft_memset(res, '0', ft_strlen(nb1) + tmp);
	i = ft_strlen(nb1) - 1;
	while (i >= 0)
	{
		j = tmp - 1;
		carry = 0;
		while (j >= 0 || carry)
		{
			int tmp = (res[i + j + 1] - '0') + (nb1[i] - '0') * (j >= 0 ? (nb2[j] - '0') : 0) + carry;
			res[i + j + 1] = tmp % 10 + '0';
			carry = tmp / 10;
			j--;
		}
		i--;
	}
	res = remove_leading_zeros(&res);
	return (res);
}

char	*long_pow(char *nbr, int pow)
{
	char	*res;
	char	*tmp;

	res = ft_strdup(nbr);
	while (pow > 1)
	{
		tmp = res;
		res = long_mul(res, nbr);
		ft_memdel((void**)&tmp);
		pow--;
	}
	return (res);
}

static char	*insert_point(char *nbr, int len, int exponent, t_printf *p)
{
	char	*tmp;
	int		itmp;

	tmp = ft_strnew(len + (exponent >= 1023 ? 1 : 1023 - exponent + 1));
	if (exponent >= 1023)
	{
		ft_memcpy(tmp, nbr, len - 52);
		tmp[len - 52] = '.';
		ft_memcpy(tmp + len - 51, nbr + len - 52, (p->precision == -1 ? 7 : p->precision + 1));
	}
	else
	{
		itmp = 52 + (1023 - exponent) - len;
		ft_memcpy(tmp, "0.", 2);
		if (p->precision != -1)
			itmp = itmp > p->precision + 1 ? p->precision + 1 : itmp;
		else
			itmp = itmp > 7 ? 7 : itmp;
		ft_memset(tmp + 2, '0', itmp);
		if ((p->precision == -1 ? 7 : p->precision + 1) - itmp > 0)
			ft_memcpy(tmp + 2 + itmp, nbr, (p->precision == -1 ? 7 : p->precision + 1) - itmp);
	}
	return (tmp);
}

char	*float_round(char **nbr, int len)
{
	char	*res;

	if ((*nbr)[len - 1] < '5')
	{
		res = ft_strsub(*nbr, 0, len - 1);
		ft_memdel((void**)nbr);
	}
	else
	{
		return (*nbr);
		//while ()
	}
	return (res);
}

char	*float_to_str(t_double f, t_printf *p)
{
	char	*tmp;
	char	*tmp2;
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
		tmp = long_mul(long_pow("2", f.parts.exponent - 1023), tmp2);
	else
		tmp = long_mul(tmp2, long_pow("5", 1023 - f.parts.exponent));
	ft_memdel((void**)&tmp2);
	tmp2 = insert_point(tmp, ft_strlen(tmp), f.parts.exponent, p);
	tmp2 = float_round(&tmp2, ft_strlen(tmp2));
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
