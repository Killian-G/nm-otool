/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:52:39 by kguibout          #+#    #+#             */
/*   Updated: 2021/10/08 18:34:49 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_env	*get_env(void)
{
	static t_env	env = {0};

	return (&env);
}

t_option	*get_options_func(void)
{
	static t_option	options[] = {
	{.name = "numeric-sort", .alias = "n", .func = numeric_sort_option},
	{.name = NULL, .alias = "v", .func = numeric_sort_option},
	{.name = "no-sort", .alias = "p", .func = no_sort_option},
	{.name = "reverse-sort", .alias = "r", .func = reverse_sort_option},
	{.func = NULL},
	};

	return (options);
}

void	init_env(void)
{
	t_env	*env;

	env = get_env();
	vector_init(&env->files, sizeof(char *));
}

void	free_env(void)
{
	t_env	*env;

	env = get_env();
	vector_free(&env->files);
}
