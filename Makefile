NAME		= minishell

CC			= gcc -g
CFLAGS		= -Wall -Wextra -Werror -I /Users/ancoulon/.local/include -I libcarbon/include -I include
RM			= rm -f

SRCS		= \
				$(wildcard source/*.c) \
				$(wildcard source/*/*.c)

OBJS		= $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			make -C libcarbon
			$(CC) $(CFLAGS) -L /Users/ancoulon/.local/lib -lreadline -L libcarbon -lcarbon -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			make -C libcarbon clean
			$(RM) $(OBJS)

fclean:		clean
			make -C libcarbon fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
