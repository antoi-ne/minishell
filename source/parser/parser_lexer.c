#include "msh.h"
#include "carbon.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>

static t_prog	*init_prog(void)
{
	t_prog	*prog;

	prog = mem_calloc(sizeof(t_prog));
	if (prog == NULL)
		utils_exit(EXIT_FAILURE, "memory allocation error");
	prog->argv = NULL;
	prog->input = STDIN_FILENO;
	prog->output = STDOUT_FILENO;
	return (prog);
}

static int	here_document_redirect(char *delimiter)
{
	char	*input;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		utils_exit(EXIT_FAILURE, "pipe() error");
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			utils_exit(EXIT_FAILURE, "here-document readline returned NULL");
		if (str_cmp(input, delimiter) == 0)
			break ;
		write(pipefd[1], input, str_len(input));
		write(pipefd[1], "\n", 1);
		free(input);
	}
	free(input);
	close(pipefd[1]);
	return (pipefd[0]);
}

static void	parse_redirection(t_lexer *lexer)
{
	int 	fd;

	if (lexer->n_node == NULL || lexer->n_token->type != TT_WORD)
		utils_exit(EXIT_FAILURE, "parsing error: no token after redirection");
	if (str_cmp(lexer->c_token->data, "<") == 0)
	{
		fd = open(lexer->n_token->data, O_RDONLY);
		if (fd < 0)
			utils_exit(EXIT_FAILURE, "cannot open file");
		lexer->c_prog->input = fd;
	}
	else if (str_cmp(lexer->c_token->data, "<<") == 0)
	{
		lexer->c_prog->input = here_document_redirect(lexer->n_token->data);
	}
	else if (str_cmp(lexer->c_token->data, ">") == 0)
	{
		fd = open(lexer->n_token->data, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
			utils_exit(EXIT_FAILURE, "cannot open file 1");
		lexer->c_prog->output = fd;
	}
	else if (str_cmp(lexer->c_token->data, ">>") == 0)
	{
		fd = open(lexer->n_token->data, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd < 0)
			utils_exit(EXIT_FAILURE, "cannot open file 2");
		lexer->c_prog->output = fd;
	}
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
		utils_exit(EXIT_FAILURE, "memory allocation error");
	i = 0;
	while (node)
	{
		token = (t_token *)node->data;
		argv[i] = str_dup(token->data);
		if (argv[i] == NULL)
			utils_exit(EXIT_FAILURE, "memory allocation error");
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
			utils_exit(EXIT_FAILURE, "memory allocation error");
	llst_push(progs, node);
	lexer->c_prog = NULL;
	llst_destroyl(&(lexer->c_words), NULL);
	lexer->c_words = NULL;
}

void	print_progs(t_llst *progs)
{
	t_llst	*node;
	t_prog	*prog;
	size_t	i;

	node = progs;
	while (node)
	{
		prog = (t_prog *)node->data;
		printf("prog %p {\n    argv:", prog);
		i = 0;
		while (prog->argv[i])
		{
			printf(" %s", prog->argv[i]);
			i++;
		}
		printf("\n    input: %d\n    output: %d\n}\n", prog->input, prog->output);
		node = node->next;
	}
}

void	apply_pipes(t_llst **progs)
{
	t_llst	*node;
	t_prog	*prog;
	t_prog	*next_prog;
	int		pipefd[2];

	node = *progs;
	while (node && node->next)
	{
		prog = (t_prog *)node->data;
		next_prog = (t_prog *)node->next->data;
		if (pipe(pipefd) < 0)
			utils_exit(EXIT_FAILURE, "could not create pipe");
		prog->output = pipefd[1];
		next_prog->input = pipefd[0];
		node = node->next;
	}
}

void	msh_parser_lexer(t_llst **tokens, t_llst **progs)
{
	t_lexer	lexer;
	t_llst	*copy;

	lexer.c_words = NULL;
	lexer.tokens = tokens;
	lexer.c_node = *tokens;
	while (lexer.c_node)
	{
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
				utils_exit(EXIT_FAILURE, "memory allocation error");
			llst_push(&(lexer.c_words), copy);
		}
		else if (lexer.c_token->type == TT_RERD)
		{
			parse_redirection(&lexer);
			lexer.c_node = lexer.c_node->next;
		}
		else if (lexer.c_token->type == TT_PIPE)
			finish_prog(&lexer, progs);
		lexer.c_node = lexer.c_node->next;
	}
	if (llst_len(lexer.c_words) < 1)
		utils_exit(EXIT_FAILURE, "nothing after pipe");
	finish_prog(&lexer, progs);
	apply_pipes(progs);
		// print_progs(*progs);
}
