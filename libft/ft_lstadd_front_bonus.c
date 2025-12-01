/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:57:56 by thde-sou          #+#    #+#             */
/*   Updated: 2025/04/26 20:25:09 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

/*int     main(void)
{       
        t_list  *lista = NULL;
        t_list  *n1;
        t_list  *n2;
        
        n1 = ft_lstnew("Nó 1"); //cria um nó
        n2 = ft_lstnew("Nó 2");
        ft_lstadd_front(&lista, n1); //n1 aponta para lista, lista se torna n1
        ft_lstadd_front(&lista, n2); //lista é n1 e n2 aponta p/ n1, lista = n2
        t_list  *temp = lista;
        while (temp != NULL)
        {       
                printf("Conteúdo do nó: %s\n", (char *)(temp->content));
                temp = temp->next; //aponta para o próximo nó até chegar a NULL
        }       
        return (0);
}*/
