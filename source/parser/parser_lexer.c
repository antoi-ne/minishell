#include "msh.h"
#include "carbon.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>

static void	end_document_redirect(char *input, int *pipefd)
{
	free(input);
	close(pipefd[1]);
	close(pipefd[0]);
	exit(EXIT_SUCCESS);
}

static int	here_document_redirect(t_token *delimiter)
{
	char	*input;
	int		pipefd[2];
	pid_t	pid;
	int		retval;

	if (pipe(pipefd) < 0)
		utils_exit(EXIT_FAILURE, NULL);
	pid = fork();
	if (pid < 0)
		utils_exit(EXIT_FAILURE, NULL);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			input = readline("> ");
			if (input == NULL || str_cmp(input, delimiter->data) == 0)
				break ;
			if (delimiter->is_string == 0)
				input = msh_parser_expand_dqs(input, 0, 0);
			write(pipefd[1], input, str_len(input));
			write(pipefd[1], "\n", 1);
			free(input);
		}
		end_document_redirect(input, pipefd);
	}
	else
	{
		waitpid(pid, &retval, 0);
		close(pipefd[1]);
		if (retval != EXIT_SUCCESS)
		{
			close(pipefd[0]);
			return (-1);
		}
	}
	return (pipefd[0]);
}

static int	parse_redirection(t_lexer *lexer)
{
	int	fd;

	if (lexer->n_node == NULL || lexer->n_token->type != TT_WORD)
		return (utils_printerror
			(NULL, "syntax error: no token after redirection"));
	if (str_cmp(lexer->c_token->data, "<") == 0)
	{
		fd = open(lexer->n_token->data, O_RDONLY);
		if (fd < 0)
			utils_exit(EXIT_FAILURE, NULL);
		lexer->c_prog->input = fd;
	}
	else if (str_cmp(lexer->c_token->data, "<<") == 0)
	{
		lexer->c_prog->input = here_document_redirect(lexer->n_token);
		if (lexer->c_prog->input == -1)
			return (-1);
	}
	else if (str_cmp(lexer->c_token->data, ">") == 0)
	{
		fd = open(lexer->n_token->data, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
			utils_exit(EXIT_FAILURE, NULL);
		lexer->c_prog->output = fd;
	}
	else if (str_cmp(lexer->c_token->data, ">>") == 0)
	{
		fd = open(lexer->n_token->data, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd < 0)
			utils_exit(EXIT_FAILURE, NULL);
		lexer->c_prog->output = fd;
	}
	return (0);
}

static char	**generate_argv(t_lexer *lexer)
{
	t_llst	*node;
	t_token	*token;
	char	**argv;
	size_t	i;

	node = lexer->c_words;
	argv = mem_calloc(sizeof(char *) * (llst_len(node) + 1));
	if (argv == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	i = 0;
	while (node)
	{
		token = (t_token *)node->data;
		argv[i] = str_dup(token->data);
		if (argv[i] == NULL)
			utils_exit(EXIT_FAILURE, NULL);
		node = node->next;
		i++;
	}
	return (argv);
}

static void	finish_prog(t_lexer *lexer, t_llst **progs)
{
	t_llst	*node;

	lexer->c_prog->argv = generate_argv(lexer);
	node = llst_new(lexer->c_prog);
	if (node == NULL)
		utils_exit(EXIT_FAILURE, NULL);
	llst_push(progs, node);
	lexer->c_prog = NULL;
	llst_destroyl(&(lexer->c_words), NULL);
	lexer->c_words = NULL;
}

int	msh_parser_lexer(t_llst **tokens, t_llst **progs)
{
	t_lexer	lexer;
	t_llst	*copy;

	lexer.c_words = NULL;
	lexer.tokens = tokens;
	lexer.c_node = *tokens;
	lexer.c_prog = init_prog();
	while (lexer.c_node)
	{
		if (lexer.c_prog == NULL)
			lexer.c_prog = init_prog();
		lexer.c_token = (t_token *)lexer.c_node->data;
		lexer.n_node = lexer.c_node->next;
		if (lexer.n_node)
			lexer.n_token = (t_token *)lexer.n_node->data;
		else
			lexer.n_token = NULL;
		if (lexer.c_token->type == TT_WORD)
		{
			copy = llst_new(lexer.c_node->data);
			if (copy == NULL)
				utils_exit(EXIT_FAILURE, NULL);
			llst_push(&(lexer.c_words), copy);
		}
		else if (lexer.c_token->type == TT_RERD)
		{
			if (parse_redirection(&lexer) != 0)
				return (-1);
			lexer.c_node = lexer.c_node->next;
		}
		else if (lexer.c_token->type == TT_PIPE)
			finish_prog(&lexer, progs);
		lexer.c_node = lexer.c_node->next;
	}
	if (llst_len(lexer.c_words) < 1)
		return (utils_printerror(NULL, "syntax error: no command after pipe"));
	finish_prog(&lexer, progs);
	apply_pipes(progs);
	return (0);
}
