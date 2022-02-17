/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:33:19 by jbettini          #+#    #+#             */
/*   Updated: 2022/02/17 23:02:22 by jbettini         ###   ########.fr       */
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

int	redir_in(char **av, int ac, t_env *env)
{
	int	infile;
	int	i;

	i = 0;
	if (ft_strequ(av[1], "heredoc"))
	{
		infile = fd_stdin(av[2], 1);
		i++;
	}
	else
		infile = fd_stdin(av[1], 0);
	if (infile != -1 && dup2(infile, 0) == -1)
	{
		perror("dup2 error ");
		exit(EXIT_FAILURE);
	}
	env->redir = i;
	return (i);
}

int fd_stdin(char *filename, int mod)
{
    char **hd;
    int i;
    int fd;

    i = -1;
    hd = NULL;
    fd = 0;
    if (!mod)
    {
        if (access(filename, F_OK | R_OK) == -1)
        {
            perror("file not found");
            return (-1);
        }
            return (open(filename, O_RDONLY));
    }
    else
    {
        fd = open(".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0744);
        hd = heredoc(filename);
        while (hd[++i])
            ft_putstr_fd(hd[i], fd);
        close(fd);
        ft_free_split(hd);
        return(open(".heredoc_tmp", O_RDWR, 0744));
    }
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