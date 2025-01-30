/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-19 10:54:14 by jbayonne          #+#    #+#             */
/*   Updated: 2025-01-19 10:54:14 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_ctx
{
	char	***cmd;
	char	**path;
	char	**env;
	char	**argv;
	int		fd[2];
	pid_t	id;
	int		argc;
	int		in_fd;
	int		out_fd;
	int		nb;
}			t_ctx;

t_ctx	*ctx_init(int argc, char **argv, char **env);

int		nb_args(char **argv);
char	*find_path(t_ctx *ctx);
void	open_file(char **argv, t_ctx *ctx);
char	**splitdup(char	**args);

void	freecmd_init(char ***cmd, int i);
void	freecmd(char ***cmd);
void	freesplit(char **split);
void	freesplit_i(char **split, int n);
void	freectx(t_ctx *ctx);

void	exec_cmd(t_ctx *ctx);
void	open_files(t_ctx *ctx);
void	ft_error(char *msg, t_ctx *ctx);

#endif
