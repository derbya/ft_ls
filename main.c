/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderby <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 09:48:36 by aderby            #+#    #+#             */
/*   Updated: 2019/05/26 19:19:08 by aderby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	hidden_file(const char *name)
{
	if (*name == '.')
		return (1);
	return (0);
}

int		store_name(t_ls *new, char *name)
{
	t_name	*tmp;

	tmp = new->name_list;
	if (!new->name_list->name)
	{
		//if (!(tmp = (t_name *)malloc(sizeof(t_name))))
		//	return (0);
		new->name_list->name = ft_strdup(name);
		new->name_list->right = NULL;
		new->name_list->left = NULL;
		//initialize d - depending on if it is a dir or file somehow
		//new->name_list = tmp;
		return (1);
	}
	while (tmp->name)
		tmp = tmp->right;
	tmp = (t_name *)malloc(sizeof(t_name));
	tmp->name = ft_strdup(name);
	tmp->right = NULL;
	tmp->left = NULL;
	new->name_list = tmp;
	//initialize d - depending on if it is a dir or file somehow
	return (1);
}

//void	the_recursive_big_r(t_ls *flags)
//{
//	
//}

//int	main(int a, char **v)
//{
//	t_ls			*flags;
//
//	flags = parse_command(a, v);
//	if (flags->name_list->name == NULL)
//		flags->name_list->name = ft_strdup("./");
//	flags->ptr = opendir(flags->name_list->name);
//	lstat(flags->name_list->name, &flags->buffer);
//	flags->pwd = getpwuid(flags->buffer.st_uid);
//	ft_printf("%s\n", ctime(&flags->buffer.st_ctime));
//	ft_printf("%s\n", flags->pwd->pw_name);
//	if (flags->ptr == NULL)
//		return (1);
//	while ((flags->dirptr = readdir(flags->ptr)) != NULL)
int		initialize_ls(t_ls **new)
{
	if (!((*new) = (t_ls *)malloc(sizeof(t_ls))))
		return (0);
	(*new)->l_flag = 0;
	(*new)->a_flag = 0;
	(*new)->r_flag = 0;
	(*new)->big_r_flag = 0;
	(*new)->t_flag = 0;
	(*new)->name_list = (t_name *)malloc(sizeof(t_name));
	(*new)->name_list->name = NULL;
	(*new)->name_list->right = NULL;
	(*new)->name_list->left = NULL;
	return (1);
}

t_ls	*parse_command(int a, char **v)
{
	int		i;
	t_ls	*new;

	i = 1;
	if (!initialize_ls(&new))
		return (NULL);
	while (i < a)
	{
		if (v[i][0] == '-')
		{
			if (ft_strchr(v[i], 'a'))
				new->a_flag = 1;
			if (ft_strchr(v[i], 'r'))
				new->r_flag = 1;
			if (ft_strchr(v[i], 'l'))
				new->l_flag = 1;
			if (ft_strchr(v[i], 'R'))
				new->big_r_flag = 1;
			if (ft_strchr(v[i], 't'))
				new->t_flag = 1;
		}
		else
			if (!store_name(new, v[i]))
				return (NULL);
		i++;
	}
	return (new);
}

void	print_l_flag(t_ls *flags, char *name)
{
	if (!flags->a_flag)
		if (!hidden_file(name))
			ft_printf("%s\n", name);
	if (flags->a_flag)
		ft_printf("%s\n", name);
}

void	print_a_flag(t_ls *flags, char *name)
{
	if (!flags->a_flag)
		if (!hidden_file(name))
			ft_printf("%s\t", name);
	if (flags->a_flag)
		ft_printf("%s\t", name);
}

void	print_name(t_ls *flags, char *name)
{
	if (flags->a_flag)
		print_a_flag(flags, name);
	else
		print_l_flag(flags, name);
//	if (flags->r_flag)
//		print_r_flag(flags, name);
//	if (flags->big_r_flag)
//		print_big_r_flag(flags, name);
//	if (flags->t_flag)
//		print_t_flag(flags, name);
}

void	store_name_list(t_ls *flags)
{
	flags->ptr = opendir(flags->name_list->name);
	lstat(flags->name_list->name, &flags->buffer);
//	if (S_ISDIR(flags->buffer.st_mode))
}

void	get_permissions(t_ls *flags)
{
	PER(0) = (flags->buffer.st_mode & S_IFDIR) ? 'd' : '-';
	PER(1) = (flags->buffer.st_mode & S_IRUSR) ? 'r' : '-';
	PER(2) = (flags->buffer.st_mode & S_IWUSR) ? 'w' : '-';
	PER(3) = (flags->buffer.st_mode & S_IXUSR) ? 'x' : '-';
	PER(4) = (flags->buffer.st_mode & S_IRGRP) ? 'r' : '-';
	PER(5) = (flags->buffer.st_mode & S_IWGRP) ? 'w' : '-';
	PER(6) = (flags->buffer.st_mode & S_IXGRP) ? 'x' : '-';
	PER(7) = (flags->buffer.st_mode & S_IROTH) ? 'r' : '-';
	PER(8) = (flags->buffer.st_mode & S_IWOTH) ? 'w' : '-';
	PER(9) = (flags->buffer.st_mode & S_IXOTH) ? 'x' : '-';
	PER(10) = '\0';
}
// things may not persist form main, such as buffer
void	fill_data(t_ls *flags)
{
	get_permissions(flags);
	LINK_NUM = BUFFER.st_nlink;
	//free this shit
	PWD = getpwuid(BUFFER.st_uid);
	GID = getgrgid(BUFFER.st_gid);
	flags->name_list->time = ft_strsplit(ctime(&flags->buffer.st_ctime), ' ');
	flags->name_list->hm_time = ft_strsplit(TIME(3), ':');
	//all of it
	ft_printf("%s  %d ", PERLIST, LINK_NUM);
//	ft_printf("%d ", LINK_NUM);
	ft_printf("%s  ", flags->pwd->pw_name);
	ft_printf("%s   ", flags->gid->gr_name);
	ft_printf("%d ", flags->buffer.st_size);
	ft_printf("%s %s %s:%s ", TIME(1), TIME(2), HM_TIME(0), HM_TIME(1));
	ft_printf("%s\n", NAME);
//	ft_printf("%s\n", ctime(&flags->buffer.st_ctime));
}

void	do_a_thing(t_ls *flags)
{
	lstat(flags->dirptr->d_name, &flags->buffer);
	fill_data(flags);
}
int	main(int a, char **v)
{
	t_ls			*flags;

	flags = parse_command(a, v);
	if (flags->name_list->name == NULL)
		flags->name_list->name = ft_strdup("./");
	flags->ptr = opendir(flags->name_list->name);
	lstat(flags->name_list->name, &flags->buffer);
	flags->pwd = getpwuid(flags->buffer.st_uid);
//	fill_data(flags);
//	get_permissions(flags);
//	ft_printf("%s\n", ctime(&flags->buffer.st_ctime));
//	ft_printf("%s\n", flags->pwd->pw_name);
//	ft_printf("%s\n", PERLIST);
//	ft_printf("%d\n", flags->buffer.st_nlink);
	if (flags->ptr == NULL)
		return (1);
	while ((flags->dirptr = readdir(flags->ptr)) != NULL)
		do_a_thing(flags);
//	store_name_list(flags);
	closedir(flags->ptr);
	return (0);
}
		//print_name(flags, flags->dirptr->d_name);

