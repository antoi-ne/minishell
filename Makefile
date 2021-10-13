NAME		= minishell

ifeq ($(USER),ancoulon)
RL_LIB		= /Users/ancoulon/.local/lib
RL_INC		= /Users/ancoulon/.local/include
endif
ifeq ($(USER),maperrea)
RL_LIB		= /Users/maperrea/.brew/opt/readline/lib
RL_INC		= /Users/maperrea/.brew/opt/readline/include
endif
ifeq ($(USER),alpeliss)
RL_LIB		= /Users/alpeliss/.brew/opt/readline/lib
RL_INC		= /Users/alpeliss/.brew/opt/readline/include
endif



CC			= gcc -g #-fsanitize=address
CFLAGS		= -I $(RL_INC) -I libcarbon/include -I include
RM			= rm -f

SRCDIR		= source
SRCS		= source/main.c								\
				source/builtins/builtins_cd.c			\
				source/builtins/builtins_env.c			\
				source/builtins/builtins_export.c		\
				source/builtins/builtins_pwd.c			\
				source/builtins/builtins_echo.c			\
				source/builtins/builtins_exit.c			\
				source/builtins/builtins_get.c			\
				source/builtins/builtins_unset.c		\
				source/engine/engine_check_path.c		\
				source/engine/engine_execute.c			\
				source/engine/execute_progs.c			\
				source/env/env_all.c					\
				source/env/env_free.c					\
				source/env/env_get.c					\
				source/env/env_init.c					\
			   	source/env/env_set.c					\
				source/env/env_unset.c					\
				source/parser/apply_pipes.c				\
				source/parser/parser_heredoc.c			\
		 		source/parser/parser_tokenize.c			\
				source/parser/msh_parser_expand_dqs.c 	\
				source/parser/parser_lexer.c			\
	  			source/parser/parser_weld_tokens.c		\
				source/parser/parser.c					\
				source/parser/parser_redirection.c		\
				source/parser/progs_handle.c			\
				source/parser/parser_expand.c			\
	   			source/parser/parser_retval.c			\
	   			source/parser/token_adder.c				\
				source/reader/reader_start.c			\
				source/utils/utils_exit.c				\
				source/utils/utils_is_number.c			\
			  	source/utils/utils_printerror.c		

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
