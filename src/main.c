/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 14:38:36 by jbettini          #+#    #+#             */
/*   Updated: 2022/02/17 18:16:24 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
char	**get_paths(t_env *env)
{
	int	i;

	i = 0;
	while (env->envp[i] && ft_strncmp(env->envp[i], "PATH=", 5))
		i++;
	return (ft_split(env->envp[i] + 5, ':'));
}

void	redir(char **av, int ac)
{
	int	infile;
	int	outfile;

	
	if (ft_strequ(av[1], "heredoc"))
	{
		infile = fd_stdin(av[2], 0);
		outfile = redir_to_stdout(av[ac - 1], 0);
	}
	else
	{
		infile = fd_stdin(av[1], 1);
		outfile = redir_to_stdout(av[ac - 1], 1);
	}
	if (dup2(infile, 0) == -1)
		perror("dup error\n");
	if (dup2(outfile, 1) == -1)
		perror("dup error\n");
}

int	main(int ac, char **av, char **env)
{	
	t_env	*env_set;

	env_set->envp = env;
	env_set->paths = get_paths(env_set);
	print()
	// printf("1 - %s\n", get_next_line());
	// if (ac >= 5)
	// {
		// redir(av, ac)

	// }
	redir(av, ac);
	system("leaks pipex");
	return (0);
}
