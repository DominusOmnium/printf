# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 12:08:40 by dkathlee          #+#    #+#              #
#    Updated: 2020/01/14 09:26:36 by dkathlee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCDIR = srcs/
INCDIR = includes/
OBJDIR = obj/

SRCS =	printf.c parse_args.c flags.c utils.c percent.c float.c long_arith.c

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
