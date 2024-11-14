/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadjemia <nadjemia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:15:06 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/14 15:57:10 by nadjemia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

size_t	strlen_to_space(char *str)
{
	size_t	len;

	if (!str || !str[0])
		return (0);
	len = 0;
	while (str[len])
	{
		if (str[len] == ' ' || !str[len] || str[len] == ',')
			return (len);
		len++;
	}
	return (len);
}

static long	modified_atoi(const char *nptr, int *decimal)
{
	int	i;
	long	result;
	int	sign;

	sign = 1;
	i = 0;
	result = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' && ++i)
		sign *= -1;
	else if (nptr[i] == '+')
		i++;
	i--;
	while ((nptr[++i] >= '0' && nptr[i] <= '9') || nptr[i] == '.')
	{
		if (nptr[i] == '.')
			*decimal = strlen_to_space((char *)nptr + i + 1);
		else
			result = result * 10 + (nptr[i] - '0');
	}
	return (result * sign);
}

double	atod(char *nptr)
{
	int	decimal;
	double	result;
	
	decimal = 0;
	result = (double)modified_atoi(nptr, &decimal);
	if (decimal == 0)
		return (result);
	return (result / pow(10, decimal)); 
}

char	**tabdup(char **tab)
{
	int		i;
	int		tmp;
	char	**arr;
	
	i = 0;
	while (tab[i])
		i++;
	arr = (char **)malloc(sizeof(char *) * (i + 1));
	if (!arr)
		return (NULL);
	arr[i] = NULL;
	i = 0;
	tmp = 0;
	while (tab[i])
	{
		arr[i] = ft_strdup(tab[i]);
		if (arr[i] == NULL)
		{
			while (tmp < i)
				free(arr[tmp]);
			return (free(arr), NULL);
		}
		i++;
	}
	return (arr);
}

int	is_not_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			return (1);
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (0);
}
