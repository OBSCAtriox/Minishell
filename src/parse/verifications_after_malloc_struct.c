/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications_after_malloc_struct.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tide-pau <tide-pau@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 18:37:05 by tide-pau          #+#    #+#             */
/*   Updated: 2026/01/12 18:38:37 by tide-pau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	verifications_after_malloc_struct(t_tokens *t)
{
	ps()->tl = tok_split(t);
	add_to_struct();
	add_cmd_argv(ps()->tl);
	return (1);
}
