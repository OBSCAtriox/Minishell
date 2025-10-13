/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:30:23 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/04 18:48:43 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

//int     main(void)
//{       
//        t_list  *lista = NULL;
//        t_list  *n1;
//        t_list  *n2;
//        
//        n1 = ft_lstnew(ft_strdup("Nó 1"));
//        n2 = ft_lstnew(ft_strdup("Nó 2"));
//        ft_lstadd_front(&lista, n1);
//        ft_lstadd_front(&lista, n2);
//        t_list  *temp = lista;
//        ft_lstsize(temp);
//        printf("Tamanho da lista: %d\n", ft_lstsize(temp));
//        ft_lstclear(&lista, free);
//        return (0);
//}
