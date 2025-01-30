/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-19 10:53:34 by jbayonne          #+#    #+#             */
/*   Updated: 2025-01-19 10:53:34 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	free(split);
}

void	freesplit_i(char **split, int n)
{
	int	i;

	i = 0;
	if (split[i])
	{
		while (i < n)
		{
			free(split[i]);
			i++;
		}
	}
	free(split);
}

void	freecmd(char ***cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		freesplit(cmd[i]);
		i++;
	}
	free(cmd);
}

void	freecmd_init(char ***cmd, int i)
{
	if (cmd[i])
	{
		while (i >= 0)
		{
			freesplit(cmd[i]);
			i--;
		}
	}
	free(cmd);
}

void	freectx(t_ctx *ctx)
{
	ctx->path[0] -= 5;
	freesplit(ctx->path);
	freecmd(ctx->cmd);
	free(ctx);
}
