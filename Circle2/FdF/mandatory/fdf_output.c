/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function17.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ucho <ucho@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:11:17 by ucho              #+#    #+#             */
/*   Updated: 2025/08/19 11:51:34 by ucho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*get_fdf_name(const char *path)
{
	const char	*name;
	const char	*slash;
	const char	*dot;
	size_t		len;
	char		*result;

	slash = ft_strrchr(path, '/');
	if (slash)
		name = slash + 1;
	else
		name = path;
	dot = ft_strrchr(name, '.');
	if (dot == NULL || dot == name)
		len = ft_strlen(name);
	else
		len = (size_t)(dot - name);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, name, len);
	result[len] = '\0';
	return (result);
}

static char	*get_suffix(int number)
{
	char	*count;
	char	*suffix;
	char	*type;

	count = ft_itoa(number);
	if (!count)
		return (NULL);
	suffix = ft_strjoin("_screenshot_", count);
	free(count);
	if (!suffix)
		return (NULL);
	type = ft_strjoin(suffix, ".ppm");
	free(suffix);
	if (!type)
		return (NULL);
	return (type);
}

char	*get_ppm_name(t_file file)
{
	char	*fdf;
	char	*suffix;
	char	*ppm;

	fdf = get_fdf_name(file.name);
	if (!fdf)
		return (NULL);
	suffix = get_suffix(file.screenshot);
	if (!suffix)
	{
		free(fdf);
		return (NULL);
	}
	ppm = ft_strjoin(fdf, suffix);
	if (!ppm)
	{
		free(suffix);
		free(fdf);
		return (NULL);
	}
	free(suffix);
	free(fdf);
	return (ppm);
}
