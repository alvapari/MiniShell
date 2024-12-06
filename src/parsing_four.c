/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvapari <alvapari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:31:20 by alvapari          #+#    #+#             */
/*   Updated: 2024/12/06 19:17:38 by alvapari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// esta función nos dirá si un carácter concreto (index) de una string está o
// no está en estado de comillas. Si está FUERA de comillas devolverá 1, si
// está dentro de comillas devolverá 0

int	ft_is_spc_chr(char str)
{
	if (str == '>' || str == '<' || str == '|')
		return (1);
	return (0);
}

int	ft_tell_if_oq(char *str, int index, int i)
{
	int	flag;

	flag = 0;
	while (str[i] != '\0' && i <= index)
	{
		if (str[i] == DOUB_QUOT)
		{
			if (flag == 0)
				flag = DOUB_QUOT;
			else if (flag == DOUB_QUOT)
				flag = 0;
		}
		if (str[i] == ONE_QUOT)
		{
			if (flag == 0)
				flag = ONE_QUOT;
			else if (flag == ONE_QUOT)
				flag = 0;
		}
		if ((i == index) && flag == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_len(char *s, int k)
{
	int	i;
	int	add;

	k = 0;
	i = 0;
	add = 0;
	if (!s) 
        return (0);
	while (s[i] != '\0')
	{
		if (((i > 0 && s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i
					+ 1] == '<')) && ft_tell_if_oq(s, i, k) == 1 && s[i
			- 1] != ' ')
			add++;
		else if (i > 0 && ft_is_spc_chr(s[i]) == 1 && ft_tell_if_oq(s, i, k) == 1
			&& s[i - 1] != ' ')
			add++;
		else if (i >= 2 && s[i] != ' ' && ((s[i - 2] == '>' && s[i - 1] == '>') || (s[i
					- 2] == '<' && s[i - 1] == '<')) && s[i] != '\0'
			&& ft_tell_if_oq(s, i - 2, k) == 1)
			add++;
		else if (i >= 1 && s[i] != ' ' && ft_is_spc_chr(s[i - 1]) == 1 && s[i] != '\0'
			&& ft_tell_if_oq(s, i - 1, k) == 1)
			add++;
		if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i
				+ 1] == '<'))
			i += 2;
		else
			i++;
	}
	return (add);
}


char	*ft_new_input(char *s, int len)
{
	int		i;
	char	*new_str;
	int		cnt_ns;
	int		k;

	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
	{
		printf("String has not been created (Error)");
		exit(0);
	}
	k = 0;
	i = 0;
	cnt_ns = 0;
	while (s[i] != '\0')
	{
		if (((i > 0 && s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i
			+ 1] == '<')) && ft_tell_if_oq(s, i, k) == 1 && s[i - 1] \
			!= ' ')
			new_str[cnt_ns++] = ' ';
		else if (i > 0 && ft_is_spc_chr(s[i]) == 1 && ft_tell_if_oq(s, i, k) == 1
			&& s[i - 1] != ' ')
			new_str[cnt_ns++] = ' ';
		else if (i >= 2 && s[i] != ' ' && ((s[i - 2] == '>' && s[i - 1] == '>') 
			|| (s[i - 2] == '<' && s[i - 1] == '<')) && s[i] != '\0'
			&& ft_tell_if_oq(s, i - 2, k) == 1)
			new_str[cnt_ns++] = ' ';
		else if (i >= 1 && s[i] != ' ' && ft_is_spc_chr(s[i - 1]) == 1 && s[i] != '\0'
			&& ft_tell_if_oq(s, i - 1, k) == 1)
			new_str[cnt_ns++] = ' ';
		new_str[cnt_ns] = s[i];
		if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<' && s[i + 1] == '<'))
		{
			i++;
			cnt_ns++;
			new_str[cnt_ns] = s[i];
		}
		i++;
		cnt_ns++;
	}
	new_str[len] = '\0';
	return (new_str);
}

