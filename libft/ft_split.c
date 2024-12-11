/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <kfreyer@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:53:44 by kfreyer           #+#    #+#             */
/*   Updated: 2024/07/31 21:45:13 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*jump_sep(char *str, char sep)
{
	while (*str && *str == sep)
		str++;
	return (str);
}

char	*jump_non_sep(char *str, char sep)
{
	while (*str && (*str != sep))
		str++;
	return (str);
}

int	count_words(char *str, char c)
{
	int	count;

	count = 0;
	if (!*str)
		return (0);
	if (*str != c)
		count++;
	str = jump_non_sep(str, c);
	str = jump_sep(str, c);
	while (*str && (*str == c))
		str++;
	while (*str)
	{
		count++;
		str = jump_non_sep(str, c);
		str = jump_sep(str, c);
	}
	return (count);
}

char	*extract_string(char *str, char *end_word, char **strs, size_t count)
{
	size_t	idx;

	strs[count] = (char *)malloc(((end_word - str) + 1) * sizeof(char));
	if (strs[count] == NULL)
	{
		idx = 0;
		while (idx < count)
			free(strs[idx++]);
		free(strs);
		return (NULL);
	}
	idx = 0;
	while (str != end_word)
		strs[count][idx++] = *str++;
	strs[count][idx] = '\0';
	return (strs[count]);
}

char	**ft_split(char *str, char c)
{
	char	**strs;
	char	*end_word;
	int		nbr_of_words;
	size_t	count;

	nbr_of_words = count_words(str, c);
	strs = (char **)malloc((nbr_of_words + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	str = jump_sep(str, c);
	count = 0;
	while (nbr_of_words-- > 0)
	{
		end_word = jump_non_sep(str, c);
		if (extract_string(str, end_word, strs, count) == NULL)
			return (NULL);
		str = jump_non_sep(str, c);
		str = jump_sep(str, c);
		count++;
	}
	strs[count] = NULL;
	return (strs);
}
