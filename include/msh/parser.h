#ifndef PARSER_H
# define PARSER_H

typedef enum e_token_type
{
	TT_UKWN,
	TT_SPCE,
	TT_DQS,
	TT_SQS,
	TT_WORD,
	TT_RERD,
	TT_PIPE
}	t_token_type;
// unknown, not pased yet
// space
// double quote string
// single quote string
// word (interpretable token)
// redirection "> >> < <<"
// pipe "|"

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	int				is_string;
}	t_token;
//is_string only used for heredoc

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

typedef union u_bytearray
{
	int		integer;
	char	byte[4];
}	t_bytearray;

int		msh_parser(char *input, t_llst **progs);

int		msh_parser_tokenize(char *input, t_llst **tokens);

void	msh_parser_expand(t_llst **tokens);

void	msh_parser_weld_tokens(t_llst **tokens);

int		msh_parser_lexer(t_llst **tokens, t_llst **progs);

int		msh_parser_redirection(t_lexer *lexer);

int		here_document_redirect(t_token *delimiter);

void	msh_parser_prog_free(t_prog *prog);

void	msh_parser_token_free(t_token *token);

void	msh_parser_set_retval(int retval);

int		msh_parser_get_retval(void);

t_prog	*init_prog(void);

char	*msh_parser_expand_dqs(char *str, size_t i, size_t start);

void	apply_pipes(t_llst **progs);

void	add_token(t_llst **tokens, char *data, t_token_type type);
int		add_dqs_token(char *input, t_llst **tokens, size_t *i);
int		add_sqs_token(char *input, t_llst **tokens, size_t *i);
int		add_redirect_token(char *input, t_llst **tokens, size_t *i);
int		add_pipe_token(char *input, t_llst **tokens, size_t *i);
void	add_word_token(char *input, t_llst **tokens, size_t *i);

#endif
