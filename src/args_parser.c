/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:56:11 by kguibout          #+#    #+#             */
/*   Updated: 2021/10/08 19:03:09 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

bool	check_options_alias(char *option)
{
	size_t		i;
	t_option	*options;

	i = 0;
	options = get_options_func();
	option = option + 1;
	while (options[i].func != NULL)
	{
		if (options[i].alias != NULL && ft_strequ(option, options[i].alias))
		{
			options[i].func();
			return (true);
		}
		i++;
	}
	ft_printf("%s: unrecognized option -- '%s'\n", get_env()->exec_name, option);
	return (false);
}

bool	check_options_name(char *option)
{
	size_t		i;
	t_option	*options;

	i = 0;
	options = get_options_func();
	option = option + 2;
	while (options[i].func != NULL)
	{
		if (options[i].name != NULL && ft_strequ(option, options[i].name))
		{
			options[i].func();
			return (true);
		}
		i++;
	}
	ft_printf("%s: unrecognized option '--%s'\n", get_env()->exec_name, option);
	return (false);
}

bool	parse_option(char *option)
{
	if (option[0] == '-')
	{
		if (option[1] == '-')
			return (check_options_name(option));
		return (check_options_alias(option));
	}
	return (true);
}

bool	parse_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			if (!parse_option(av[i]))
				return (false);
		}
		else
			vector_push(&get_env()->files, &av[i]);
		i++;
	}
	return (true);
}
