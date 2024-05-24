/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycontre <ycontre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:16:25 by rgramati          #+#    #+#             */
/*   Updated: 2024/05/24 16:32:23 by ycontre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* INCLUDES ***************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

/* STRUCTS ****************************************************************** */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* CHAR ********************************************************************* */

/**
 * @brief		Is a char between a-z and A-Z.
 * 
 * @param c		char to test
 * 
 * @return		1 if true, 0 otherwise;
*/
int		ft_isalpha(int c);

/**
 * @brief		Is a char between 0-9.
 * 
 * @param c		char to test
 * 
 * @return		1 if true, 0 otherwise;
*/
int		ft_isdigit(int c);

/**
 * @brief		Is a char a digit or an alphabetic character.
 * 
 * @param c		char to test
 * 
 * @return		1 if true, 0 otherwise;
*/
int		ft_isalnum(int c);

/**
 * @brief		Is a char between 0 and 127 (ASCII table range).
 * 
 * @param c		char to test
 * 
 * @return		1 if true, 0 otherwise;
*/
int		ft_isascii(int c);

/**
 * @brief		Is a char between 32 and 126 (printable range).
 * 
 * @param c		char to test
 * 
 * @return		1 if true, 0 otherwise;
*/
int		ft_isprint(int c);

/**
 * @brief		Is a char between 9 and 13 (whitespaces range).
 * 
 * @param c		char to test
 * 
 * @return		1 if true, 0 otherwise;
*/
int		ft_isspace(int c);

/**
 * @brief		Is a char uppercase.
 * 
 * @param c		char to test
 * 
 * @return		1 if true, 0 otherwise;
*/
int		ft_isupper(int c);

/**
 * @brief		Is a char lowercase.
 * 
 * @param c		char to test
 * 
 * @return		1 if true, 0 otherwise;
*/
int		ft_islower(int c);

/**
 * @brief		Change a lowercase letter to uppercase.
 * 
 * @param c		char to convert
 * 
 * @return		Uppercase letter if c was a lowercase letter, c otherwise;
*/
int		ft_toupper(int c);

/**
 * @brief		Change an uppercase letter to lowercase.
 * 
 * @param c		char to convert
 * 
 * @return		Lowercase letter if c was an uppercase letter, c otherwise;
*/
int		ft_tolower(int c);

/**
 * @brief		Max between 2 values.
 * 
 * @param a		First value.
 * @param b		Second value.
 * 
 * @return		Max between a and b.
*/
int		ft_max(int a, int b);
int		ft_min(int a, int b);
int		ft_sign(float a);

/* ************************************************************************** */

/* STRING ******************************************************************* */
size_t	ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strcat(char *dest, char *src);
size_t	ft_strlcat(char *dst, char *src, size_t size, int null_term);
size_t	ft_strlcpy(char *dst, char *src, size_t size);
char	*ft_strchr(char *s, int c);
char	*ft_strrchr(char *s, int c);
int		ft_atoi(char *nptr);
int		ft_atoi_base(char *nptr, int base);
float	ft_atof(char *nptr);
char	*ft_strdup(char *s);
char	*ft_strndup(char *str, int n);
char	*ft_strnstr(char *big, char *little, size_t len);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2, char *c, int tofree);
char	*ft_strsjoin(char **strs, char *sep, int tofree);
char	*ft_strmapi(char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	**ft_split(char *s, char c);
char	*ft_strtrim(char *s1, char *set);
char	*ft_itoa(int n);
int		ft_strcspn(char *s, char *rejects);
char	*ft_strtok(char *str, char *token);
int		ft_wc(char *str, char delim);
int		ft_tab_len(char **tab);
char	**ft_strtab(char *str);
void	ft_strapp(char ***tab, char *str);
void	ft_strtabjoin(char ***tab, char **next);

/**
 * @brief		Returns a lowercase copy of a string.
 * 
 * @param str	String to lower.
 * 
 * @return		Lowercase string.
*/
char	*ft_strlow(char *str);

/**
 * @brief		Returns an uppercase copy of a string.
 * 
 * @param str	String to upper.
 * 
 * @return		Uppercase string.
*/
char	*ft_strupp(char *str);

void	ft_swap_strs(char **a, char **b);

void	ft_swap(float *a, float *b, int condition);

void	ft_sort_strs_tab(char **tab, int size);

void	ft_sort_lowstrs_tab(char **tab, int size);

/* ************************************************************************** */

/* MEMORY ******************************************************************* */
void	*ft_memset(void *s, int c, size_t n);
void	*ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, void *src, size_t n);
void	*ft_memmove(void *dest, void *src, size_t n);
void	*ft_memchr(void *s, int c, size_t n);
int		ft_memcmp(void *s1, void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_free_tab(void **tab);
/* ************************************************************************** */

/* PUT_FD ******************************************************************* */
size_t	ft_putchar_fd(int fd, char c);
size_t	ft_putstr_fd(int fd, char *str);
size_t	ft_putnbr_hex_fd(int fd, unsigned long nb, int flags, int depth);
size_t	ft_putnbr_fd(int fd, long nb);
size_t	ft_putunbr_fd(int fd, unsigned long nb);
void	ft_putendl_fd(char *s, int fd);

int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
/* ************************************************************************** */

/* T_LIST ******************************************************************* */
t_list	*ft_lstnew(void *content);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstget_index(t_list *lst, int index);
/* ************************************************************************** */

/* GNL TLST ***************************************************************** */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_slist
{
	struct s_slist	*next;
	char			*str;
}	t_slist;

char	*get_next_line(int fd);
char	*offset(t_slist *lst);
char	*line_from_list(t_slist **lst);

t_slist	*ft_slstnew(char *str);
void	ft_slstclear(t_slist **lst);
void	ft_slstadd_back(t_slist **lst, t_slist *new);
int		ft_slstcsize(t_slist *lst);
/* ************************************************************************** */

#endif