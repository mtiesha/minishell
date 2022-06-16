/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:29:39 by mtiesha           #+#    #+#             */
/*   Updated: 2022/06/16 19:01:22 by mtiesha          ###   ########.fr       */
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

/* /src/parser/cleaner */
char	*ft_cleaner(char **cmd);
/* /src/parser */
void	parser(t_src *s);
int		ft_check_wrong_pipe(t_src *s);
char	*ft_delete_pipes(t_src *s, int k);
int		ft_count_ac(const char **spl);
int		ft_isbuildin(char *str);
char	**ft_union_cmd_flg(char **av);
char	**ft_union_cmd_file(char **av);
/* MSHLVL */
char	**ft_add_mshlvl(char **envp);
void	ft_sig_handler_b(int sig);
/* /src/binary */
int		ft_gate_binary(t_src *s);
int		ft_exec_cd(t_src *s);
int		ft_exec_echo(t_src *s, int fd);
int		ft_exec_exit(t_src *s);
int		ft_exec_pwd(int fd);
/* /src/binary/export_unset */
int		ft_sort_env(char **envp);
int		ft_export_add(t_src *s);
int		ft_unset(t_src *s);
void	ft_count_include_av(char **split, char **argv, int *argc);
/* /src/executor */
int		ft_pipex(int gnr, char **argv, char **envp);
int		ft_check_arg_b(t_pipex **s, char **envp, char **argv);
char	*ft_get_env_cmd(char **envp, char *command);
int		ft_isfile(char *file);
char	*ft_get_absolute_pth(char *file);
void	ft_freesher(t_pipex **s);
void	ft_errorer(t_pipex **s, char *code);
void	ft_heredoc(t_pipex **s, char *stop);

#endif
