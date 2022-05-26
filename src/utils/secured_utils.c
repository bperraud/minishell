/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secured_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboumal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:33:01 by jboumal           #+#    #+#             */
/*   Updated: 2022/05/26 16:33:10 by jboumal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_sstrdup(char *src)
{
	char	*dst;
	int		len;

	len = ft_strlen(src);
	dst = smalloc ((len + 1) * sizeof(char));
	ft_strlcpy(dst, src, len + 1);
	return (dst);
}

char	*ft_strndup(char *src, int n)
{
	char	*dst;

	dst = smalloc ((n + 1) * sizeof(char));
	ft_strlcpy(dst, src, n + 1);
	return (dst);
}

void	*smalloc(size_t n_bytes)
{
	void	*data;

	data = malloc (n_bytes);
	if (!data)
	{
		perror("minishell");
		exit(ENOMEM);
	}
	return (data);
}
