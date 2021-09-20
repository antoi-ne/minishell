#ifndef PARSER_H
# define PARSER_H

typedef enum	e_data_type
{
	DT_UNKWN = 0, // unknown (not parsed yet)
	DT_SPACER, // space between tokens
	DT_CMD, // command
	DT_ARG, // argument following a command
	DT_SQS, // sigle quote string
	DT_DQS // double quote string
}	t_data_type;

typedef enum	e_token_type
{
	TT_UKWN,
	TT_DQS,
	TT_SQS,
	TT_CMD,
	TT_ARG,
	TT_PIPE,
	TT_REDR,
}	t_token_type;

typedef struct	s_token
{
	char			*data;
	t_token_type	type;
}	t_token;


void	msh_parser_tokenize(char *input);

#endif
