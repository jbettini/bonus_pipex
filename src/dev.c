/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 23:01:48 by jbettini          #+#    #+#             */
/*   Updated: 2022/02/18 19:57:52 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_lstdpt(void *content)
{
	size_t	i;
	char	**tab;

	i = -1;
	tab = (char **)content;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	tab = 0;
}

char	**get_paths(t_env *env)
{
	int	i;

	i = 0;
	while (env->envp[i] && !ft_strnstr(env->envp[i], "PATH=", 5))
		i++;
	if (env->envp[i] == NULL)
		return (NULL);
	return (ft_split(env->envp[i] + 5, ':'));
}

void	init_env(t_env *env_set, char **env)
{
	env_set->envp = env;
	env_set->paths = get_paths(env_set);
}

t_list	*init_cmd(char **av, int i)
{
	t_list	*tmp;

	tmp = NULL;
	if (i != -1)
		while (av[++i + 1])
			ft_lstadd_back(&tmp, ft_lstnew(ft_split(av[i], ' ')));
	else
	{
		i = 1;
		while (av[++i + 1])
			ft_lstadd_back(&tmp, ft_lstnew(ft_split(av[i], ' ')));
	}
	return (tmp);
}

void	exec_error(int error)
{
	if (error == FORK_ERROR)
		perror("fork failed :");
	else if (error == PIPE_ERROR)
		perror("pipe failed :");
	else if (error == OP_ERROR)
		perror("open error : ");
	else if (error == DUP_ERROR)
		perror("dup error : ");
	exit(1);
}
