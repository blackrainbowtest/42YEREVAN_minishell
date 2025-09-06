/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramarak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:57:21 by aramarak          #+#    #+#             */
/*   Updated: 2025/02/03 20:48:37 by aramarak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (needle[++j] == '\0')
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main()
{
	const char *s1 = "some word here";
	const char *s2 = "word";

	printf("%s\n", ft_strnstr(s1, s2, 12));
	printf("%s\n", ft_strnstr(((void *)0), "fake", 3));
	return (0);
}*/
