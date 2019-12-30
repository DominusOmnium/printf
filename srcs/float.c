/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 14:20:21 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/30 17:29:26 by dkathlee         ###   ########.fr       */
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

char	*long_mul(char *nb1, char *nb2)
{
	char	*res;
	int		nb1_len;
	int		nb2_len;
	int		i;
	int		j;
	int		carry;

	nb1_len = ft_strlen(nb1);
	nb2_len = ft_strlen(nb2);
	res = ft_strnew(nb1_len + nb2_len);
	ft_memset(res, '0', nb1_len + nb2_len);
	i = nb1_len - 1;
	carry = 0;
	while (i >= 0)
	{
		j = nb2_len - 1;
		while (j >= 0 || carry)
		{
			long long tmp = (res[i + j + 1] - '0') + (nb1[i] - '0') * (j >= 0 ? (nb2[j] - '0') : 0) + carry;
			res[i + j + 1] = tmp % 10 + '0';
			carry = tmp / 10;
			j--;
		}
		i--;
	}
	return (res);
}

char	*long_pow(char *nbr, int pow)
{
	
}

/*char	*div_long_by_simple(char *divided, int divider)
{
	int	carry;
	int	i;

	carry = 0;
	i = ft_strlen()
	for (int i=(int)a.size()-1; i>=0; --i) {
		long long cur = a[i] + carry * 1ll * base;
		a[i] = int (cur / b);
		carry = int (cur % b);
	}
	while (a.size() > 1 && a.back() == 0)
		a.pop_back();
}*/

char	*float_to_str(t_double f, t_printf *p)
{
	char	*res;
	char	*tmp;
	char	*mantisa;

	mantisa = ft_itoa_base(f.parts.mantisa, "0123456789");
	tmp = long_mul(mantisa, "2220446049250313080847263336181640625");
	//char *tmp2 = ft_strnew(ft_strlen(tmp) + 1);
	tmp[0] = '1';
	//ft_strcpy(tmp2 + 1, tmp);
	tmp = long_mul(tmp, "8");
	calc_float_len(f, p);
	res = ft_strdup("float");
	return (res);
}
