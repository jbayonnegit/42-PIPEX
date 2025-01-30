/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-19 19:02:52 by jbayonne          #+#    #+#             */
/*   Updated: 2025-01-19 19:02:52 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_file(t_ctx *ctx)
{
	if (ctx->out_fd >= 0)
		close(ctx->out_fd);
	if (dup2(ctx->in_fd, STDIN_FILENO) < 0)
		ft_error("DUP2 ERROR\n", ctx);
	close(ctx->in_fd);
	close(ctx->fd[0]);
	if (dup2(ctx->fd[1], STDOUT_FILENO) < 0)
		ft_error("DUP2 ERROR\n", ctx);
	close(ctx->fd[1]);
}

void	last_file(t_ctx *ctx)
{
	if (ctx->in_fd >= 0)
		close(ctx->in_fd);
	if (dup2(ctx->out_fd, STDOUT_FILENO) < 0)
		ft_error("DUP2 ERROR\n", ctx);
	close(ctx->out_fd);
	close(ctx->fd[1]);
	if (dup2(ctx->fd[0], STDIN_FILENO) < 0)
		ft_error("DUP2 ERROR\n", ctx);
	close(ctx->fd[0]);
}

void	child(t_ctx *ctx)
{
	if (ctx->nb == 0)
		first_file(ctx);
	else
		last_file(ctx);
	if (execve(find_path(ctx), ctx->cmd[ctx->nb], ctx->env) == -1)
	{
		write(2, ctx->cmd[ctx->nb][0], ft_strlen(ctx->cmd[ctx->nb][0]));		
		write(2, ": ", 2);
		perror(NULL);
		exit(EXIT_FAILURE);
	}
}

void	exec_cmd(t_ctx *ctx)
{
	open_files(ctx);
	if (pipe(ctx->fd) < 0)
		ft_error("PIPE ERROR\n", ctx);
	while (ctx->nb < ctx->argc)
	{
		ctx->id = fork();
		if (ctx->id == 0)
			child(ctx);
		else
			ctx->nb++;
	}
	close(ctx->fd[0]);
	close(ctx->fd[1]);
	if (ctx->in_fd >= 0)
		close(ctx->in_fd);
	if (ctx->out_fd >= 0)
		close(ctx->out_fd);
}
