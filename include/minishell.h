/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:29:39 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/12 15:59:26 by mtiesha          ###   ########.fr       */
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

typedef struct s_src{
	int		argc;
	char	**argv;
	char	**envp;
	char	**export;
	int		ret;
	char	*str;
	char	**cmds;
	int		child;
}	t_src;

typedef struct s_pipex {
	char	**path;
	char	***cmd;
	int		fd0;
	int		fd1;
	int		gnr;
}	t_pipex;

/* /src/parser */
int		ft_check_wrong_pipe(t_src *s);
char	*ft_delete_pipes(t_src *s, int k);
int		ft_count_ac(const char **spl);
int		ft_isbuildin(char *str);
char	**ft_union_cmd_flg(char ***av);
char	**ft_union_cmd_file(char ***av);
/* MSHLVL */
char	**ft_add_mshlvl(char **envp);
/* /src/binary */
int		ft_gate_binary(t_src *s);
void	ft_exec_cd(t_src *s);
void	ft_exec_echo(t_src *s, int fd);
void	ft_exec_exit(t_src *s);
void	ft_exec_pwd(int fd);
/* /src/binary/export_unset */
void	ft_sort_env(char **envp);
void	ft_export_add(t_src *s);
void	ft_unset(t_src *s);
void	ft_count_include_av(char **split, char **argv, int *argc);
/* /src/executor */
int		ft_pipex(int gnr, char **argv, char **envp);
int		ft_check_arg_b(t_pipex **s, char **envp, char **argv);
char	*ft_get_env_cmd(char **envp, char *command);
char	*ft_get_absolute_pth(char *file);
void	ft_freesher(t_pipex **s);
void	ft_errorer(t_pipex **s);
void	ft_heredoc(t_pipex **s, char *stop);

void	set_args(char **argv, char *str, int argc);
void	child_sig_handler(int sig);
void	child_sig_handler_bash(int sig);
void	bash_command(t_src *s);
void	parser(t_src *s);
void	export_value(t_src *s, int *i);
void	rm_char(char **str, int j);
void	rm_token(char **arg);
void	command_or_pipe(t_src *s, int j);
char	*get_env(char **envp, char *env);
char	**copy_args(t_src *s);
char	**check_command(char *str, t_src *s);
int		count_args(char *str);
int		ft_strlen_token(char *str);
int		ft_strlen_env(char *str);
int		ft_strlen_pipe(char *str);
int		ft_strlen_char(char *str, char c);
int		ft_strlen_arg_token(char *str, char c);
int		is_token(char c);

#endif
