/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:57:14 by marvin            #+#    #+#             */
/*   Updated: 2019/12/26 11:44:33 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stddef.h>
# include "libft.h"

typedef enum
{
	sp_none, sp_hh, sp_h, sp_l, sp_ll, sp_L, sp_j, sp_z, sp_t
}	t_spec;
typedef enum
{
	type_none, type_int = 1, type_char = 2, type_unsigned = 4, type_octal = 8,
	type_hex_low = 16, type_hex_high = 32, type_float = 64, type_pointer = 128,
	type_percent = 256, type_str = 512
}	t_type;
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
	va_list	args;
}				t_printf;
char			*get_str_from_arg(const char **format, t_printf *p);
void			set_flags(char **str, t_printf *p);
void			reset(t_printf *p);
int				is_flag(char c);
int				is_spec(char c);
int				is_type(char c);
int				check_str(char *str, char c);
void			parcing_format(const char **f, t_printf *p);
void			check_flags(const char *f, t_printf *p);
void			check_flags_and_specs(const char **f, t_printf *p);
void			set_precision(char **str, t_printf *p);
int				set_width(char **str, t_printf *p);
void			set_minus(char **str, int cl, t_printf *p);
#endif
