/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvapari <alvapari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:32:01 by alvapari          #+#    #+#             */
/*   Updated: 2024/11/20 23:23:32 by alvapari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*esta función devuelve 1 o 0 en caso de que el lexema esté compuesto solo
por comillas de un solo tipo: en ese caso deberemos llamar a otra función.*/
int	ft_if_lexem_only_single_quotes(char *str, t_parsing *prs)
{
	int	aux;

	aux = prs->init_index;
	while (aux <= prs->end_index)
	{
		if (str[aux] == ONE_QUOT)
			aux++;
		else
			return (2);
	}
	return (1);
}

/*esta función crea un lexema con solo un espacio y un carácter nulo*/
void	ft_create_a_space_lexem(t_parsing *prs)
{
	int	len;

	prs->cnt_new_str = 0;
	len = 2;
	prs->arr_lexems[prs->index_arr] = malloc(sizeof(char) * len);
	if (!prs->arr_lexems[prs->index_arr])
	{
		printf("String has not been created (Error)");
		exit(0);
	}
	prs->arr_lexems[prs->index_arr][0] = 32;
	prs->arr_lexems[prs->index_arr][1] = '\0';
}

/*imprime errores y realiza un exit_status = 2*/
void	ft_print_prs_err(char flag, t_parsing *prs)
{
	if (flag == 'u')
	{
		prs->ptrdata->exit_status = 2;
		ft_putstr_fd("Minishell does not work with unclosed quotes\n", 2);
	}
}

/*esta función devuelve 1 o 0 en caso de que el lexema esté compuesto solo
por comillas de un solo tipo: en ese caso deberemos llamar a otra función.*/
int	ft_if_lexem_only_doub_quotes(char *str, t_parsing *prs)
{
	int	aux;

	aux = prs->init_index;
	while (aux <= prs->end_index)
	{
		if (str[aux] == DOUB_QUOT)
			aux++;
		else
			return (2);
	}
	return (1);
}
