/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-19 10:54:18 by jbayonne          #+#    #+#             */
/*   Updated: 2025-01-19 10:54:18 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	nb_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

char	**splitdup(char	**args)
{
	char	**dup;
	int		i;

	i = 0;
	dup = malloc(sizeof(char *) * (nb_args(args) + 1));
	if (!dup)
	{
		perror("MALLOC ERROR, utils:splitdup:l35\n");
		return (NULL);
	}
	while (args[i])
	{
		dup[i] = ft_strdup(args[i]);
		if (!dup[i])
		{
			perror("MALLOC ERROR, utilis:splitdup:l43\n");
			freesplit_i(dup, i);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	open_files(t_ctx *ctx)
{
	int	last_arg;

	last_arg = nb_args(ctx->argv) - 1;
	ctx->in_fd = open(ctx->argv[1], O_RDONLY);
	if (ctx->in_fd < 0)
	{
		ft_printf("%s :", ctx->argv[1]);
		perror(NULL);
		ctx->nb++;
	}
	ctx->out_fd = open(ctx->argv[last_arg], O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (ctx->out_fd < 0)
	{
		if (!(ctx->in_fd < 0))
			close(ctx->in_fd);
		ft_printf("%s :", ctx->argv[last_arg]);
		perror(NULL);
		ctx->argc--;
	}
}

char	*find_path(t_ctx *ctx)
{
	int		i;
	char	*str;
	char	*file_name;

	if (ft_strchr(ctx->cmd[ctx->nb][0], '/'))
		return (ctx->cmd[ctx->nb][0]);
	file_name = ft_strjoin("/", ctx->cmd[ctx->nb][0]);
	if (!file_name)
		return (perror("MALLOC ERROR, find_path:l73\n"), freectx(ctx), NULL);
	i = 0;
	while (ctx->path[i])
	{
		str = ft_strjoin(ctx->path[i], file_name);
		if (!str)
			return (perror("MALLOC ERROR, find_path:l78\n"), free(file_name),
				freectx(ctx), NULL);
		if (access(str, F_OK | X_OK | R_OK) == 0)
			return (free(file_name), str);
		else
			free(str);
		i++;
	}
	return (free(file_name), NULL);
}

void	ft_error(char *msg, t_ctx *ctx)
{
	perror(msg);
	freectx(ctx);
	exit(EXIT_FAILURE);
}
