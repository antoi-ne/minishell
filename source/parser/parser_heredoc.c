/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:41:46 by maperrea          #+#    #+#             */
/*   Updated: 2021/10/07 15:46:56 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "carbon.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

static void	heredoc_proc(t_token *delimiter, int pipefd[2])
{
	char	*input;

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
	free(input);
	close(pipefd[1]);
	close(pipefd[0]);
	exit(EXIT_SUCCESS);
}

int	here_document_redirect(t_token *delimiter)
{
	int		pipefd[2];
	pid_t	pid;
	int		retval;

	if (pipe(pipefd) < 0)
		utils_exit(EXIT_FAILURE, NULL);
	pid = fork();
	if (pid < 0)
		utils_exit(EXIT_FAILURE, NULL);
	else if (pid == 0)
		heredoc_proc(delimiter, pipefd);
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
