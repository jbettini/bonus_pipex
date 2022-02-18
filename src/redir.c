/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:33:19 by jbettini          #+#    #+#             */
/*   Updated: 2022/02/18 19:37:27 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int redir_to_stdout(char *filename, int mod)
{
    int fd;

    if (!mod)
        fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0766);
    else if (mod)
        fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0766);
    if (fd == -1)
        return (-1);
    if (dup2(fd, 1) == -1)
        return (-1);
    return (fd);
}

void	pipex(char **args, t_env *env)
{
	pid_t	pid;
	int		fd[2];

	env->cmd_path = make_cmd_path(args, env->paths);
	if (pipe(fd) == -1)
		exec_error(PIPE_ERROR);
	pid = fork();
	if (pid == -1)
		exec_error(FORK_ERROR);
	if (!pid)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		execve(env->cmd_path, args, env->envp);
	}
	else if (pid)
	{
		waitpid(-1, NULL, 0);
		if (env->cmd_path)
			free(env->cmd_path);
		dup2(fd[0], 0);
		close(fd[1]);
	}
}

int fd_stdin(char *filename, t_env *env)
{
    int fd;

    fd = -1;
    if (access(filename, F_OK | R_OK) == -1)
    {
        perror("file not found");
        return (fd);
    }
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        exec_error(OP_ERROR);
    if (dup2(fd, 0) == -1)
        exec_error(DUP_ERROR);
    env->redir = 0;
    return (0); 
}

int fd_heredoc(char *stop, t_env *env)
{
    int     fd;
    char    **hd;
    int     i;  

    i = -1;
    fd = open(".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0744);
    hd = heredoc(stop);
    while (hd[++i])
        ft_putstr_fd(hd[i], fd);
    close(fd);
    ft_free_split(hd);
    fd = open(".heredoc_tmp", O_RDONLY);
    if (fd == -1)
        exec_error(OP_ERROR);
    if (dup2(fd, 0) == -1)
        exec_error(DUP_ERROR);
    env->redir = 1;
    return (1);
}

char **heredoc(char *stop)
{
    t_list  *hd;
    char    **ret;
    char    *line;
    int	    check;

    hd = NULL;
    ret = NULL;
    line = NULL;
    check = 1;
    stop = ft_strjoin(stop, "\n");
    while (check == 1)
    {
        ft_putstr("> ");
        line = get_next_line(0);
        if (!ft_strequ(line, stop))
			ft_lstadd_back(&hd, ft_lstnew(ft_strdup(line)));
		else
			check--; 
        free (line);
    }
    ret = ft_lst_to_dpt(hd);
    ft_lstclear(&hd, free);
    free(stop);
    return (ret);
}