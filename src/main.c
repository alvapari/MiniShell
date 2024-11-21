#include "../include/minishell.h"

int	ft_only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	history(char *input)
{
	if (input != NULL && ft_strlen(input) != 0 && ft_only_spaces(input) == 0)
		add_history(input);
}

void	init_data(t_data *data, char **env)
{
	data->env = copy_alloc_array(env);
	data->array_var = copy_alloc_array(env);
	sort_strings(data->array_var, array_len(data->array_var));
	data->input = NULL;
	data->cmd_list = NULL;
	data->exit_status = 0;
	data->token_list = NULL;
	data->here_doc_counter = 0;
	data->prs.ptrdata = data;
	ft_init_parsing_struc(&data->prs);
	//data-> pipe = NULL;
}
void    free_data(t_data *data)
{
	//Está por rellenar
	if(data->env)
		free_array(data->env);
	if(data->array_var)
		free_array(data->array_var);
	if(data->cmd_list)
		free_cmd_list(data->cmd_list);
	if(data->token_list)
		free_token_list(data->token_list);
    if (data->input)
		free(data->input);
	if (data->prs.arr_lexems)
		free_array(data->prs.arr_lexems);
	close_fds();
}
void reboot_data(t_data *data)
{
	if(data->input)
		free(data->input);
	if(data->cmd_list)
		data->cmd_list = free_cmd_list(data->cmd_list);
	if(data->token_list)
		data->token_list = free_token_list(data->token_list);
	if (data->prs.arr_lexems)
		free_array(data->prs.arr_lexems);	
	data->input = NULL;
	data->cmd_list = NULL;
	data->token_list = NULL;
	data->exit_status = 0;
	data->here_doc_counter = 0;
	ft_init_parsing_struc(&data->prs);
	close_fds();
}

void	ft_printf_proofs_split_prs(t_data data)
{
	int count;

	count = 0;
	while(count < data.prs.how_much)
	{
		printf("string número %i es: %s\n", count, data.prs.arr_lexems[count]);
		count++;
	}
}

int	main(int argc, char** argv, char **env)
{
	t_data	data;
	int exit_status;

	(void)argc; 
	(void)argv;
	init_data(&data, env);
	signals();
	while (1)
	{
		data.input = readline("MiniShell> ");
		if (data.input == NULL)
			break ;
		history(data.input);
		ft_parsing(&data);
		if(data.exit_status == 0 && data.prs.flag_space == 'g')
		{
			//prueba_ejecucion(&data);
			ft_printf_proofs_split_prs(data);
		}
		reboot_data(&data);
	}
	exit_status = data.exit_status; //esto es para que cuando hagamos ctrl+d el exit status sea el que corresponda
    free_data(&data);
	printf("exit\n");
	return (exit_status);
}
