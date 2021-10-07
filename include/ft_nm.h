/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:32:55 by kguibout          #+#    #+#             */
/*   Updated: 2021/10/03 12:11:48 by kguibout         ###   ########.fr       */
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

typedef struct	s_env
{
	char	*exec_name;
	char	*path;
	void	*elf_file;
	char	*section_sting_table;
	size_t	section_sting_table_size;
	char	*sting_table;
	size_t	sting_table_size;
}	t_env;

t_env	*get_env();

#endif //FT_NM_H
