NAME		= minishell

ifeq ($(USER),ancoulon)
RL_LIB		= /Users/ancoulon/.local/lib
RL_INC		= /Users/ancoulon/.local/include
endif
ifeq ($(USER),maperrea)
RL_LIB		= /Users/maperrea/.brew/opt/readline/lib
RL_INC		= /Users/maperrea/.brew/opt/readline/include
endif

CC			= gcc -g #-fsanitize=address
CFLAGS		= -Wall -Wextra -Werror -I $(RL_INC) -I libcarbon/include -I include
RM			= rm -f

SRCDIR		= source
SRCS		= \
				$(wildcard $(SRCDIR)/*.c) \
				$(wildcard $(SRCDIR)/*/*.c)

OBJDIR		= object
OBJS		= $(subst $(SRCDIR), $(OBJDIR), $(SRCS:.c=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
				$(CC) -O3 $(CFLAGS) -c $^ -o $@

all:		$(NAME)

$(OBJDIR):
			mkdir $(OBJDIR) $(subst $(SRCDIR), $(OBJDIR), $(shell find $(SRCDIR)/*/ -type d))

$(NAME):	$(OBJDIR) $(OBJS)
			make -C libcarbon
			$(CC) $(CFLAGS) -L $(RL_LIB) -lreadline -L libcarbon -lcarbon -o $(NAME) $(OBJS)

clean:
			make -C libcarbon clean
			$(RM) -r $(OBJDIR)

fclean:		clean
			make -C libcarbon fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
