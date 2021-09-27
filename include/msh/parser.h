#ifndef PARSER_H
# define PARSER_H

typedef enum	e_token_type
{
	TT_UKWN, // unknown, not pased yet
	TT_SPCE, // space
	TT_DQS, // double quote string
	TT_SQS, // single quote string
	TT_WORD, // word (interpretable token)
	TT_RERD, // redirection "> >> < <<"
	TT_PIPE // pipe "|"
}	t_token_type;

typedef struct	s_token
{
	char			*data;
	t_token_type	type;
}	t_token;

typedef struct s_prog
{
	char	**argv;
	int		input;
	int		output;
}	t_prog;

typedef struct s_lexer
{
	t_llst	**tokens;
	t_llst	*c_node;
	t_token	*c_token;
	t_llst	*n_node;
	t_token	*n_token;
	t_prog	*c_prog;
	t_llst	*c_words;
}	t_lexer;

void	msh_parser(char *input, t_llst **progs);

void	msh_parser_tokenize(char *input, t_llst **tokens);

void	msh_parser_expand(t_llst **tokens);

void	msh_parser_weld_tokens(t_llst **tokens);

void	msh_parser_lexer(t_llst **tokens, t_llst **progs);

void	msh_parser_prog_free(t_prog *prog);

void	msh_parser_token_free(t_token *token);

void	print_progs(t_llst *progs);

#endif
