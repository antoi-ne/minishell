NAME		= msh

CC			= clang -O3
CFLAGS		= -Wall -Wextra -Werror -I libcarbon/include -I include
RM			= rm -f

SRCS		= \
				$(wildcard source/*.c) \
				$(wildcard source/*/*.c)



OBJS		= $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			make -C libcarbon
			$(CC) $(CFLAGS) -lreadline -L libcarbon -lcarbon -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re