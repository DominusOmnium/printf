# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 12:08:40 by dkathlee          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2019/12/11 19:59:13 by marvin           ###   ########.fr        #
=======
#    Updated: 2019/12/17 12:03:26 by dkathlee         ###   ########.fr        #
>>>>>>> 499b6db8c11c6d50e3c1e34720c3d4128b2716bc
#                                                                              #
# **************************************************************************** #

NAME = q
NAME1 = libftprintf.a

SRCDIR = srcs/
INCDIR = includes/
OBJDIR = obj/

SRCS =	main.c parse_args.c

OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

CC = gcc
CFLAGS = -ggdb

FTDIR = libft/
FTLIB = $(addprefix $(FTDIR), libft.a)
FTINC = -I $(FTDIR)includes
FTLNK = -L $(FTDIR)

all: obj $(FTLIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(FTINC) -I $(INCDIR) $(CFLAGS) -o $@ -c $<

$(FTLIB):
	make -C $(FTDIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(FTLIB) $(FTLNK) $(FTINC) -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FTDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FTDIR) fclean

re: fclean all

.PHONY: clean fclean all re
