#ifndef PARSER_H
# define PARSER_H

typedef enum	e_token_type
{
	TOK_CMD, // command
	TOK_ARG, // argument following a command
	TOK_SQS, // sigle quote string
	TOK_DQS // double quote string
}	token_type;

typedef struct	s_token
{
	char	*data;

}	t_token;

void	msh_parser_tokenize(char *input);

#endif
