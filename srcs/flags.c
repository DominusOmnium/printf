/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 10:13:33 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/24 10:26:14 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_plus(char **str, t_printf *p)
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

static void	set_hashtag(char **str, t_printf *p)
{
}

void		set_flags(char **str, t_printf *p)
{
	if (p->type == type_str || p->type == type_char)
		return ;
	if (p->flags.plus &&
			(p->type & (type_float | type_int | type_unsigned)) != 0)
		set_plus(str, p);
	if (p->flags.hashtag &&
			(p->type & (type_hex_high | type_hex_high | type_octal)) != 0)
		set_hashtag(str, p);
}
