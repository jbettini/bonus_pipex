/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 00:31:00 by jbettini          #+#    #+#             */
/*   Updated: 2022/02/18 19:38:53 by jbettini         ###   ########.fr       */
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
	char	**paths;
	char	*cmd_path;
	char	**envp;
	int		redir;
	char	*outfile;
	int		fd;
}				t_env;

enum	e_err
{
	SUCCESS,
	BF_ERROR,
	OP_ERROR,
	DUP_ERROR,
	OUT_ERROR,
	CMD_ERROR,
	PATH_ERROR,
	FORK_ERROR,
	PIPE_ERROR
};

void	exec(t_list *cmd, t_env *env);
void	exec_in_child(char **args, t_env *env);
char	*make_cmd_path(char **args, char **paths);
void	exec_error(int error);
t_list	*init_cmd(char **av, int i);
void	init_env(t_env *env_set, char **env);
char	**get_paths(t_env *env);
void	ft_free_lstdpt(void *content);
int		fd_heredoc(char *stop, t_env *env);
void	pipex(char **args, t_env *env);
char    **heredoc(char *stop);
int     redir_to_stdout(char *filename, int mod);
int		fd_stdin(char *filename, t_env *env);

#endif
