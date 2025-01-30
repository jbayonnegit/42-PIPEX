/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-19 10:53:57 by jbayonne          #+#    #+#             */
/*   Updated: 2025-01-19 10:53:57 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	t_ctx	*ctx;

	if (!env[0])
	{
		write(2, "ENV ERROR, main:l20", 19);
		return (-1);
	}
	if (argc != 5)
	{
		write(2, "ARG ERROR, main:l25", 19);
		return (-1);
	}
	ctx = ctx_init(argc, argv, env);
	if (!ctx)
		exit(EXIT_FAILURE);
	ctx->path[0] += 5;
	exec_cmd(ctx);
	while (wait(NULL) != -1)
		;
	freectx(ctx);
	return (0);
}
