/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:57:14 by marvin            #+#    #+#             */
/*   Updated: 2019/12/03 16:57:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

typedef enum
{
	sp_l, sp_ll, sp_h, sp_hh, sp_L, sp_none
}				t_spec;
typedef enum
{
	type_int, type_char, type_unsigned, type_octal, type_hex, type_str,
	type_float, type_pointer, type_percent
}				t_type;
typedef struct	s_flags
{
	t_uint8	minus;
	t_uint8	plus;
	t_uint8	space;
	t_uint8	hashtag;
	t_uint8	zero;
}				t_flags;
typedef struct	s_printf
{
	int		print_num;
	char	*print;
	t_flags	flags;
	t_spec	spec;
	t_type	type;
	int		width;
	int		precision;
}				t_printf;
