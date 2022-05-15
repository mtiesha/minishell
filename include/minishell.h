/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:16:49 by marvin            #+#    #+#             */
/*   Updated: 2022/05/15 11:34:45 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MES_ERR_SYNT_P "minishell: syntax error near unexpected token `|'\n"
# define MES_ERR_SYNT_S "-bash; syntax error near unexpected token `;'\n"

typedef struct s_data{
	int		argc;
	char	**argv;
	char	**envp;
	char	**export;
	int		ret;
	char	*str;
	char	**cmds;
	int		child;
}	t_data;

/* /src/parser */
int		ft_check_wrong_pipe(t_data *src);

/* /src/binary */
void	ft_binary_cd(t_data *param);

void	free_matrix(char **matrix);
void	set_args(char **argv, char *str, int argc);
void	child_sig_handler(int sig);
void	child_sig_handler_bash(int sig);
void	bash_command(t_data *param);
void	pwd_command(int fd);
void	exit_command(t_data *param);
void	parser(t_data *param);
void	export_value(t_data *param, int *i);
void	sort_envp(char **envp, int fd, char c);
void	rm_char(char **str, int j);
void	rm_token(char **arg);
void	command_or_pipe(t_data *param, int j);
char	*get_env(char **envp, char *env);
char	**copy_env(char **envp, int add);
char	**export_command(t_data *param, int i);
char	**unset_command(t_data *param, int i);
char	**copy_args(t_data *param);
char	**check_command(char *str, t_data *param);
int		check_builtins(int fd, t_data *param);
int		check_bin(int fd, t_data *param);
int		count_args(char *str);
int		ft_strlen_token(char *str);
int		ft_strlen_env(char *str);
int		ft_strlen_pipe(char *str);
int		ft_strlen_char(char *str, char c);
int		ft_strlen_arg_token(char *str, char c);
int		check_export_error(char **argv, int *i);
int		is_token(char c);

#endif
