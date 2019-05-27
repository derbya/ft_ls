/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 10:29:31 by aderby            #+#    #+#             */
/*   Updated: 2019/05/26 19:22:51 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <dirent.h>
# include <libft.h>

# define PWD flags->pwd
# define GID flags->gid
# define GIDNAME flags->name_list->group_name
# define PER(X) flags->name_list->permission[(X)]
# define TIME(X) flags->name_list->time[(X)]
# define HM_TIME(X) flags->name_list->hm_time[(X)]
# define PERLIST flags->name_list->permission
# define LINK_NUM flags->name_list->link_num
# define BUFFER flags->buffer
# define NAME flags->dirptr->d_name

typedef	struct		s_name
{
	char 			*name;
	char			*u_name;
	char			*group_name;
	char			**time;
	char			**hm_time;
	char			permission[11];
	int				link_num;
	struct s_name	*left;
	struct s_name	*right;
}					t_name;

typedef	struct		s_ls
{
	int				l_flag;
	int				a_flag;
	int				r_flag;
	int				big_r_flag;
	int				t_flag;
	struct	dirent	*dirptr;
	struct	stat	buffer;
	struct	passwd	*pwd;
	struct	group	*gid;
	DIR				*ptr;
	t_name			*name_list;
}					t_ls;

int					hidden_file(const char *name);
int					store_name(t_ls *new, char *name);

#endif
