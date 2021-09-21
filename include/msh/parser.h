#ifndef PARSER_H
# define PARSER_H

typedef enum	e_token_type
{
	TT_UKWN, // unknown, not pased yet
	TT_SPCE, // space
	TT_DQS, // double quote string
	TT_SQS, // single quote string
	TT_WORD, // word (interpretable token)
	TT_RERD // redirection
}	t_token_type;

typedef struct	s_token
{
	char			*data;
	t_token_type	type;
}	t_token;


void	msh_parser_tokenize(char *input);

#endif
