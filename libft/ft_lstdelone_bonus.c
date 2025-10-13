/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:30:04 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/01 17:42:12 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/*void    del(void *content)
{
        free(content);
}*/

/*void    del(void *content);

int     main(void)
{
        t_list  *n1;
        t_list  *n2;
        t_list  *n3;
        int     len;

        n1 = ft_lstnew(ft_strdup("Nó 1"));
        n2 = ft_lstnew(ft_strdup("Nó 2"));
        n3 = ft_lstnew(ft_strdup("Nó 3"));
        ft_lstadd_back(&n1, n2);
        ft_lstadd_back(&n1, n3);
        len = ft_lstsize(n1);
        printf("Tamanho do nó: %d\n", len); //Antes de apagar.
        n1->next = n2->next; //atualiza pra onde o n1 aponta.
        ft_lstdelone(n2, del);
        len = ft_lstsize(n1);
        printf("Tamanho do nó: %d\n", len); //Depois que apagou.
        return (0);
}*/
