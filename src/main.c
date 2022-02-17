/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 14:38:36 by jbettini          #+#    #+#             */
/*   Updated: 2022/02/17 23:02:12 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*make_cmd_path(char **args, char **paths)
{
	int		i;
	char	*cmd;
	char	*cmd_path;

	i = -1;
	cmd_path = NULL;
	cmd = ft_strjoin("/", args[0]);
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!access(cmd_path, F_OK | X_OK))
		{
			free(cmd);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free(cmd);
	perror("command not found : ");
	return (NULL);
}

void	exec_in_child(char **args, t_env *env)
{
	pid_t	pid;

	env->cmd_path = make_cmd_path(args, env->paths);
	if (!env->cmd_path)
		return ;
	pid = fork();
	if (pid == -1)
		exec_error(FORK_ERROR);
	else if (!pid)
		execve(env->cmd_path, args, env->envp);
	else if (pid)
	{
		waitpid(-1, NULL, 0);
		if (env->cmd_path)
			free(env->cmd_path);
	}
}

void	exec(t_list *cmd, t_env *env)
{
	while (cmd)
	{
		if (cmd->next)
			pipex(cmd->content, env);
		else
		{
			env->fd = redir_to_stdout(env->outfile, env->redir);
			if (env->fd == -1)
				exit(EXIT_FAILURE);
			exec_in_child(cmd->content, env);
		}
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **env)
{	
	t_env	env_set;
	t_list	*cmd;
	int		check;

	if (ac >= 5)
	{
		init_env(&env_set, env);
		env_set.outfile = av[ac - 1];
		cmd = init_cmd(&av[1], redir_in(av, ac, &env_set));
		exec(cmd, &env_set);
		ft_lstclear(&cmd, ft_free_lstdpt);
		if (!access(".heredoc_tmp", F_OK))
			unlink(".heredoc_tmp");
	}
	else
		perror("Invalid arguments\n");
	return (0);
}
