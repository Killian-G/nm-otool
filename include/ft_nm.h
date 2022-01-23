/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:52:40 by kguibout          #+#    #+#             */
/*   Updated: 2021/10/08 18:40:04 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <elf.h>

typedef enum e_sort_type
{
    ALPHABETICAL,
    NUMERICAL,
    NONE,
}   t_sort_type;

typedef struct	s_option
{
	char	*name;
	char	*alias;
	void	(*func)();
}	t_option;

typedef struct  s_options
{
    t_sort_type sort_type;
    bool        reverse;
}   t_options;

typedef struct	s_env
{
	char		*exec_name;
	char		*path;
	void		*elf_file;
	char		*section_sting_table;
	size_t		section_sting_table_size;
	char		*symbol_sting_table;
	size_t		symbol_sting_table_size;
	t_vector	files;
	t_options	options;
	bool		is_64bit;
	size_t		file_index;
}	t_env;

typedef struct s_file_data
{
	void	*data;
	size_t	length;
}	t_file_data;

t_env	*get_env();
void 	init_env();
void	free_env(void);
bool    parse_args(int ac, char **av);

void	numeric_sort_option(void);
void	no_sort_option(void);
void	reverse_sort_option(void);
t_option	*get_options_func(void);
void	print_section(Elf64_Shdr *section_header);
bool	merge_sort_string(char **string_array, ssize_t size, int (*comp_func)(const char *, const char *));
bool	merge_sort(void *array, ssize_t size, size_t data_size, int (*comp_func)(void *, void *));
#endif //FT_NM_H
