/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:33:19 by jbettini          #+#    #+#             */
/*   Updated: 2022/02/17 18:10:02 by jbettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int redir_to_stdout(char *filename, int mod)
{
    int fd;

    if (mod)
        fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0766);
    else if (!mod)
        fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0766);
    if (fd == -1)
        return (OP_ERROR);
    if (dup2(fd, 1) == -1)
        return (DUP_ERROR);
    return (fd);
}

// int ft(char **av, int nb_cmd, char **env)
// {
//     pid_t pid;
//     int fd[2];
//     int i;

//     i = 0;
//     while (i < nb_cmd)
//     {
//         if (pipe(fd) == -1)
//         {
//             perror("pipe");
//             return (0);
//         }
//         pid = fork();
//         if (pid == -1)
//         {
//             perror("fork");
//             return (0);
//         }
//         if (pid == 0)
//         {
//             close(fd[0]);
//             dup2(fd[1], 1);
//             path = get_cmd_path(av[i], env);
//             execve(path, )
//             exit(1);
//         }
//         close(fd[1]);
//         dup2(fd[0], 0);
//         i++;        
//     }
// }

int fd_stdin(char *filename, int mod)
{
    char **hd;
    int i;
    int fd;

    i = -1;
    hd = NULL;
    fd = 0;
    if (mod)
    {
        if (access(filename, F_OK | R_OK) == -1)
        {
            perror("file not found");
            return (0);
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
// int redir_to_stdin