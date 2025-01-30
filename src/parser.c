/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-19 10:53:29 by jbayonne          #+#    #+#             */
/*   Updated: 2025-01-19 10:53:29 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **env)
{
	int		i;
	char	**path;
	char	*str;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
			str = ft_strnstr(env[i], "PATH=", 5);
		i++;
	}
	path = ft_split(str, ':');
	if (!path)
	{
		perror("MALLOC ERROR, parser:get_path:l28\n");
		return (NULL);
	}
	return (path);
}

char	***get_command(char **argv, int argc)
{
	char	***cmd;
	char	**args;
	int		i;
	int		j;

	cmd = malloc(sizeof(char **) * (argc - 3 + 1));
	if (!cmd)
		return (perror("MALLOC ERROR, parser:get_command:l39\n"), NULL);
	i = 0;
	j = 2;
	while (i < argc - 3)
	{
		args = ft_split(argv[j], ' ');
		if (!args)
			return (perror("MALLOC ERROR, parser:get_command:l39\n"),
				freecmd_init(cmd, i - 1), NULL);
		j++;
		cmd[i] = splitdup(args);
		if (!cmd[i])
			return (freesplit(args), freecmd_init(cmd, i), NULL);
		freesplit(args);
		i++;
	}
	cmd[argc - 3] = NULL;
	return (cmd);
}

t_ctx	*ctx_init(int argc, char **argv, char **env)
{
	t_ctx	*ctx;

	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
		return (NULL);
	ctx->cmd = get_command(argv, argc);
	if (!ctx->cmd)
		return (free(ctx), NULL);
	ctx->path = get_path(env);
	if (!ctx->path)
		return (freecmd(ctx->cmd), free(ctx), NULL);
	ctx->env = env;
	ctx->nb = 0;
	ctx->argc = argc - 3;
	ctx->argv = argv;
	return (ctx);
}
