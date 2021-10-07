#include "msh.h"
#include "carbon.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

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

static int	process_node(t_lexer *lexer, t_llst **progs)
{
	t_llst	*copy;

	lexer->c_token = (t_token *)lexer->c_node->data;
	lexer->n_node = lexer->c_node->next;
	if (lexer->n_node)
		lexer->n_token = (t_token *)lexer->n_node->data;
	else
		lexer->n_token = NULL;
	if (lexer->c_token->type == TT_WORD)
	{
		copy = llst_new(lexer->c_node->data);
		if (copy == NULL)
			utils_exit(EXIT_FAILURE, NULL);
		llst_push(&(lexer->c_words), copy);
	}
	else if (lexer->c_token->type == TT_RERD)
	{
		if (msh_parser_redirection(lexer) != 0)
			return (-1);
		lexer->c_node = lexer->c_node->next;
	}
	else if (lexer->c_token->type == TT_PIPE)
		finish_prog(lexer, progs);
	return (0);
}

int	msh_parser_lexer(t_llst **tokens, t_llst **progs)
{
	t_lexer	lexer;

	lexer.c_words = NULL;
	lexer.tokens = tokens;
	lexer.c_node = *tokens;
	lexer.c_prog = init_prog();
	while (lexer.c_node)
	{
		if (lexer.c_prog == NULL)
			lexer.c_prog = init_prog();
		if (process_node(&lexer, progs) == -1)
			return (-1);
		lexer.c_node = lexer.c_node->next;
	}
	if (llst_len(lexer.c_words) < 1)
		return (utils_printerror(NULL, "syntax error: no command after pipe"));
	finish_prog(&lexer, progs);
	apply_pipes(progs);
	return (0);
}
