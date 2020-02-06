# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 12:08:40 by dkathlee          #+#    #+#              #
#    Updated: 2020/02/06 15:21:30 by dkathlee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCDIR = srcs/
INCDIR = includes/
OBJDIR = obj/

SRCS =	printf.c parse_args.c flags.c utils.c percent.c float.c float_to_str.c \
		long_arith.c check_flags_and_specs.c parce_char_and_str.c

OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

CC = gcc
CFLAGS = -g

FTDIR = libft/
FTLIB = $(addprefix $(FTDIR), libft.a)
FTINC = -I $(FTDIR)includes
FTLNK = -L $(FTDIR)

all: obj $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(FTINC) -I $(INCDIR) $(CFLAGS) -o $@ -c $<

$(FTLIB):
	make -C $(FTDIR)

$(NAME): $(FTLIB) $(OBJS)
	cp libft/libft.a ./$(NAME)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

comp: all
	gcc -g -o q main.c libftprintf.a

clean:
	rm -rf $(OBJDIR)
	make -C $(FTDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FTDIR) fclean

re: fclean all

.PHONY: clean fclean all re
