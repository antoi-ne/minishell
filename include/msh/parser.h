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
	char	*cmd;
	char	**argv;
	int		input;
	int		output;
}	t_prog;

void	msh_parser_tokenize(char *input);

void	msh_parser_expand(t_llst **tokens);

void	msh_parser_weld_tokens(t_llst **tokens);

void	msh_parser_lexer(t_llst **tokens);

#endif
