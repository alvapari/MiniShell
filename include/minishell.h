
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

#include "global.h"

typedef struct s_data	t_data;
typedef struct s_cmd	t_cmd;
typedef struct s_pipe	t_pipe;
typedef struct s_redir	t_redir;

typedef enum e_quote_status
{
	DOUB_QUOT = 34,
	ONE_QUOT = 39
}   t_quote_status;

typedef enum e_token_type
{
	CMD,
	PIPE,
	REDIR
}	t_token_type;

typedef enum e_redir_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HERE_DOC
}	t_redir_type;

typedef struct s_cmd
{
	int					index;
	char				**array_cmd;
	int					fd_in;
	int					fd_out;
	t_redir				*redir_list;
	t_data				*data;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_redir
{
	t_redir_type		type;
	int					index;
	char				*in_name;
	char				*out_name;
	char				*delim;
	t_redir				*next;
	t_data				*data;
}						t_redir;

typedef struct s_token
{
	int					index;
	t_token_type		token_type;
	struct s_token		*next;
}						t_token;

typedef struct s_parsing
{
	int 				count;
    int 				how_much; 
    int 				reject;
    char 				flag;
	char				**arr_lexems;
	char				**arr_tokens;
	int					index_arr;
	int					init_index;
	int					end_index;
	int					cnt_new_str;
	int					len;
	char				flag_space;
	t_data				*ptrdata;
}						t_parsing;

typedef struct s_data
{
	char				**env;
	char				*input;
	char				*in_ax;
	char				**array_var;
	int					exit_status;
	t_token				*token_list;
	t_cmd				*cmd_list;
	int					pipe[2];
	int					here_doc_counter;
	int					parsing_error;
	t_parsing			prs;
}						t_data;

//----------------------BUILTINS----------------------

////// BUILTINS_UTILS
char					*ft_var_name(char *name_value);
char					*ft_var_value(char *name_value);
char					*ft_getenv(char *var_name, char **env);
char					**insert_var(char **array, \
							char *var_name, char *var_value);
////// BUILTINS_EXECUTION
int						is_a_builtin(t_cmd *cmd);
void					exec_builtin(t_cmd *cmd);
void					builtin_end(t_data *data, int error);
////// FT_ECHO
int						has_variable(char *input);
char					*get_exp_var(char *s, int i);
void					print_expanded(char *input, char **env);
void					ft_echo(t_cmd *cmd);
////// FT_PWD
void					ft_pwd(t_cmd *cmd);
////// FT_CD
void					ft_cd_home(t_data *data, char *oldpwd, char *pwd);
void					ft_cd(t_cmd *cmd);
void					safe_init_cd(t_cmd *cmd, char **oldpwd, char **pwd);
void					update_env(t_data *data, char *oldpwd, char *pwd);
void					free_dirs(char *oldpwd, char *pwd);
////// FT_ENV
void					ft_env(t_cmd *cmd);
////// FT_EXPORT
void					print_export(char **array_var);
void					ft_export(t_cmd *cmd);
////// FT_UNSET
void					ft_unset(t_cmd *cmd);
void					delete_var(char **array, char *var_name);
////// FT_EXIT
void					ft_exit(t_cmd *cmd);

//----------------------DATA----------------------
void					init_data(t_data *data, char **env);
void					free_data(t_data *data);
void					reboot_data(t_data *data);
void					empty_env(t_data *data);

//----------------------EXECUTION----------------------

////// EXECUTION UTILS
void					close_fds(void);
void					exit_process(t_data *data, int exit_status);
////// EXECUTION
void					basic_parsing(t_data *data);//borrar
void					execution(t_data *data);
////// MULTIPLE CMD
void					multiple_cmd_case(t_data *data);
void					child(t_cmd *cmd, int *fd_in, int *fd_out, t_data *data);
////// ONE CMD
void					one_cmd_case(t_data *data);
void					one_builtin_case(t_cmd *cmd);
////// PATH
char					*get_path_line(char **env);
char					*get_path(char *command, char **env);

//----------------------LISTS----------------------

//////CMD LIST UTILS (1)
t_cmd					*new_cmd(char **array_cmds, t_data *data);
t_cmd					*add_cmd(t_cmd *cmd_list, t_cmd *new_cmd);
void					free_cmd(t_cmd *cmd);
t_cmd					*free_cmd_list(t_cmd *cmd_list);
int						cmd_list_len(t_cmd *cmd_list);
//////CMD LIST UTILS (2)
t_cmd					*get_last_cmd(t_cmd *cmd_list);
t_cmd					*get_cmd_by_index(t_cmd *cmd_list, int index);
int						is_first_cmd(t_cmd *cmd);
int						is_last_cmd(t_cmd *cmd);
//////PRINT LISTS
void					print_token_list(t_token *token_list);
char					*token_type_to_string(t_token_type token_type);
void					print_cmd(t_cmd *cmd);
void					print_cmd_list(t_cmd *cmd_list);
void					print_redir(t_redir *redir);
void					print_redir_list(t_redir *redir_list);
char					*redir_type_to_string(t_redir_type type);
void					instrucciones_ejemplo_listas(t_data *data);//BORRAR
//////REDIR LIST UTILS
t_redir					*new_redir(t_redir_type type, char *input, t_data *data);
void					update_index_redir_list(t_redir *redir_list);
void					add_redir(t_cmd *cmd, t_redir *redir);
t_redir					*free_redir_list(t_redir *redir_list);
////TOKEN LIST UTILS
t_token					*add_token(t_token *token_list, \
							t_token_type token_type);
int						token_list_len(t_token *token_list);
t_token					*free_token_list(t_token *token_list);

//----------------------REDIRS----------------------

//////REDIRS EXECUTION
void					update_fds_redirs(t_cmd *cmd_list);
void					dup_fds_redirs(t_cmd *cmd);
void					apply_last_out_redir(t_cmd *cmd);
void					apply_last_in_redir(t_cmd *cmd);
void					apply_redir_list(t_cmd *cmd);
//////HERE DOC REDIR
void					delete_temp_file(t_cmd *cmd, char *temp_file);
void					prompt_loop(int here_doc_fd, t_redir *redir);
char					*temp_file_name(t_cmd *cmd);
void					apply_HERE_DOC_redir(t_cmd *cmd, t_redir *redir);
//////HERE DOC UTILS
char					*append_char(char *str, char c);
char					*hd_var_name(char *line, int i);
char					*append_var_value(char *expand_line, char *line, int *i, char **env);
char					*expand_vars_hd(char *line, char **env);

//////INPUT REDIR
void					apply_INPUT_redir(t_cmd *cmd, t_redir *redir);
//////OUTPUT REDIR
void					apply_OUTPUT_redir(t_cmd *cmd, t_redir *redir);
//////APPEND REDIR
void					apply_APPEND_redir(t_cmd *cmd, t_redir *redir);
//////REDIR UTILS
t_redir					*get_last_in_redir(t_cmd *cmd);
t_redir					*get_last_out_redir(t_cmd *cmd);

// SIGNALS
void					signals_handler(void);
void					handle_ctrl_c(int signal);

//----------------------UTILS----------------------

////// UTILS (1)
void					history(char *input);
int						ft_only_spaces(char *input);
int						array_len(char **array);
void					swap(char **a, char **b);
int						ft_strcmp(const char *s1, const char *s2);

////// UTILS (2)
void					print_array(char **array);
void					free_array(char **array);
char					**copy_alloc_array(char **array);
void					sort_strings(char **array, int size);
char					**realloc_elonged_array(char **src_array);

//----------------------PARSING----------------------

// PARSING-SPLIT
void    				ft_start_parsing(char *str, t_parsing *prs, int top);
void					ft_init_parsing_struc(t_parsing *prs);
void				    ft_if_single_quote(t_parsing *prs);
void 					ft_if_doub_quote(t_parsing *prs);
void    				ft_create_arr_lexem(char *str, t_parsing *prs);
void				    ft_string_by_string(char *str, t_parsing *prs);
void				    ft_split_strings(char *str, t_parsing *prs);
void				    ft_if_doub_quote_split_strings(t_parsing *prs, char *str);
void    				ft_if_single_quote_split_strings(t_parsing *prs, char *str);
void    				ft_create_a_space_lexem(t_parsing *prs);
int    					ft_if_lexem_only_single_quotes(char *str, t_parsing *prs);
int					    ft_if_lexem_only_doub_quotes(char *str, t_parsing *prs);
void    				ft_print_prs_err(char flag, t_parsing *prs);
void					ft_move_counts(t_parsing	*prs);
void					ft_string_by_string_aux(char *str, t_parsing *prs);
void					ft_printf_proofs_split_prs(t_data data); /*Que NO se nos olvide quitar esto LOL*/
void					ft_parsing(t_data *data);
char					*new_input(char *s, int len);
int						ft_len(char *s, int k, int i, int add);
int						ft_tell_if_oq(char *str, int index, int i, int flag);
int						ft_is_spc_chr(char str);
char					*ft_new_input(char *s, int len);
void    				ft_init_cnt_sc(t_parsing *prs);
void    				ft_check_if_csp(char *str, t_parsing *prs);
void   					ft_check_if_csp_aux(char *str, t_parsing *prs);
void    				ft_realloc_prs_o(t_parsing *prs);
void    				ft_realloc_prs_t(t_parsing *prs);
char					*ft_new_input_aux(char *s, char *new_str, int i, int cnt_ns);
void					ft_create_tk_arr(t_parsing *prs);

#endif