#ifndef PARSER_H
# define PARSER_H

typedef enum	e_metachar
{
	MC_EOS = 0,		// end of string: (/0)
	MC_NAS = 1,		// not a string
	MC_SD = 2,		// string delimiter (" or ')
	MC_SQS = 3,		// single quote string
	MC_DQS = 4		// double quote string
}	t_metachar;

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
	TT_UKWN, // unknown, not pased yet
	TT_SPCE, // space
	TT_DQS, // double quote string
	TT_SQS, // single quote string
	TT_WORD // word (interpretable token)
}	t_token_type;

typedef struct	s_token
{
	char			*data;
	t_token_type	type;
}	t_token;


void	msh_parser_tokenize(char *input);

#endif
