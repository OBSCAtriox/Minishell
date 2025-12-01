/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:25:53 by thde-sou          #+#    #+#             */
/*   Updated: 2025/05/04 18:26:25 by thde-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*n;
	void	*str;

	new_lst = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		str = f(lst->content);
		if (!str)
			return (ft_lstclear(&new_lst, del), NULL);
		n = ft_lstnew(str);
		if (!n)
			return (del(str), ft_lstclear(&new_lst, del), NULL);
		ft_lstadd_back(&new_lst, n);
		lst = lst->next;
	}
	return (new_lst);
}

//void    *upper_lst(void *content)
//{
//        int             a;
//        char    *str;
//
//        str = ft_strdup((char *)content);
//        if (!str)
//                return (NULL);
//        a = 0;
//        while (str[a] != '\0')
//        {
//                if (str[a] >= 'a' && str[a] <= 'z')
//                        str[a] -= 32;
//                a++;
//        }
//        return ((void *)str);
//}
//
//void    del(void *content)
//{
//        free(content);
//}

//void    *upper_lst(void *content);
//void    del(void *content);
//
//int     main(void)
//{
//        t_list  *n1;
//        t_list  *n2;
//        t_list  *n3;
//        t_list  *new;
//        t_list  *prt;
//
//        n1 = ft_lstnew(ft_strdup("No um"));
//        n2 = ft_lstnew(ft_strdup("No dois"));
//        n3 = ft_lstnew(ft_strdup("No tres"));
//        ft_lstadd_back(&n1, n2);
//        ft_lstadd_back(&n1, n3);
//        new = ft_lstmap(n1, upper_lst, del);
//        prt = new;
//        while (prt)
//        {
//                printf("%s\n", (char *)(prt->content));
//                prt = prt->next;
//        }
//        printf("Quantidade de nóis: %d\n", (int)(ft_lstsize(new)));
//        ft_lstclear(&n1, free);
//        return (0);
//}
