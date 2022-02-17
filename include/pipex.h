/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 00:31:00 by jbettini          #+#    #+#             */
/*   Updated: 2022/02/17 18:08:58 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_env
{
	char **paths;
	char **envp;
}				t_env;

enum	e_err
{
	SUCCESS,
	BF_ERROR,
	OP_ERROR,
	DUP_ERROR,
	OUT_ERROR,
	CMD_ERROR
};

char    **heredoc(char *stop);
int     redir_to_stdout(char *filename, int mod);
int		fd_stdin(char *filename, int mod);

#endif
