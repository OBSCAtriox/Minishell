/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:40:23 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/21 17:57:04 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "minishell.h"

# define ERR_ARG "\033[91mT_Shell: Error\n\033[0m"
# define SYNT_ERR_P "\033[91mT_Shell: syntax\
error near unexpected token --> ´|'\n\033[0m"
# define SYNT_ERR_R "\033[91mT_Shell: syntax\
error from --> ´redirections'\n\033[0m"
# define MALLOC_FAIL "\033[91mT_Shell:\
Malloc Failure.\n\033[0m"
# define UNCLOSED_QUOTES "\033[91mT_Shell:\
syntax error from --> ´Unclosed Quotes'\n\033[0m"

void	basic_error(char *msg);

#endif