/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:15/37 by kfreyer           #+#    #+#             */
/*   Updated: 2024/07/31 21:57:50 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# ifdef __cplusplus

extern "C"
{
# endif

/* helper */
char *ft_get_empty_str(size_t n);
int					ft_abs(int x);
void				ft_rev_char_tab(char *tab, int size);

/* mandatory */
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isalpha(char c);
int					ft_isalnum(int c);
int					ft_isdigit(char c);
const char			*ft_jump_digits(const char *p);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_atoi(const char *nptr);
long				ft_atoi_long(const char *nptr);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				**ft_split(char *str, char c);
size_t				ft_putchar_fd(char c, int fd);
size_t				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
int					ft_ptr_to_hex(void *p, char *hex_str);
int					ft_unsigned_to_hex(unsigned int d, char *hex_str,
						bool up_case);
int					ft_unsigned_long_to_hex(unsigned long d, char *hex_str,
						bool up_case);
int					ft_num_of_digits(int d);
int					ft_num_of_digits_unsigned(unsigned int d);
void				ft_putnbr_fd(int nb, int fd);
void				ft_put_unsigned_int_fd(unsigned int nb, int fd);
char				*ft_strdup(const char *s);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_itoa(int n);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/* bonus */
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new_node);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new_node);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

	/* get_next_line */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# define MAX_FD 1024
/* type definitions */
typedef enum _OP
{
	GET_STASH = 0,
	SET_STASH,
	UPDATE_STASH,
	DELETE_STASH
}		t_op;


char *get_next_line(int fd);

#  ifdef __cplusplus

}
#  endif

# endif
