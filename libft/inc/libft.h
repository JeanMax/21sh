/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:13:23 by mcanal            #+#    #+#             */
/*   Updated: 2016/12/05 17:51:08 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# ifndef TRUE
#  define TRUE			1
#  define FALSE			0
# endif

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS	0
#  define EXIT_FAILURE	1
# endif

# ifndef STDIN_FILENO
#  define STDIN_FILENO	0
#  define STDOUT_FILENO	1
#  define STDERR_FILENO	2
# endif

# ifndef INT_MAX
#  define SHRT_MAX		0x7fff
#  define SHRT_MIN		(-SHRT_MAX - 1)
#  define USHRT_MAX		0xffff
#  define INT_MAX		0x7fffffff
#  define INT_MIN		(-INT_MAX - 1)
#  define UINT_MAX		0xffffffff
#  define LONG_MAX		0x7fffffffffffffff
#  define LONG_MIN		(-LONG_MAX - 1)
#  define ULONG_MAX		0xffffffffffffffff
# endif

# include <string.h>

typedef unsigned char	t_uchar;
typedef unsigned short	t_ushort;
typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;
typedef int				t_bool;
typedef int				t_cmp(const void *a, const void *b);
typedef int				t_ncmp(const void *a, const void *b, size_t n);
typedef void			*t_cpy(void *dest, const void *src, size_t n);
typedef void			t_del(void *content, size_t content_size);
typedef size_t			t_hash(const void *content, size_t content_size);

/*
** arr struct - dynamic array
*/
typedef struct s_arr	t_arr;
struct					s_arr
{
	void				*ptr;
	size_t				length;
	size_t				sizeof_element;
	size_t				alloc_len;
	t_ncmp				*cmp;
	t_cpy				*cpy;
	t_del				*del;
};

/*
** bst struct - binary search tree (avl)
*/
typedef struct s_bst	t_bst;
struct					s_bst
{
	void				*content;
	size_t				content_size;
	t_bst				*left;
	t_bst				*right;
	size_t				height;
};

/*
** hash struct - hash node
*/
typedef struct s_hnode	t_hnode;
struct					s_hnode
{
	void				*key;
	void				*value;
	size_t				hash;
	t_hnode				*next;
};

/*
** hash struct - hash table
*/
typedef struct s_htable	t_htable;
struct					s_htable
{
	size_t				length;
	t_hnode				**bucket;
	size_t				bucket_size;
	t_hash				*hash;
	t_ncmp				*key_cmp;
	t_cpy				*key_cpy;
	t_del				*key_del;
	size_t				key_size;
	t_ncmp				*value_cmp;
	t_cpy				*value_cpy;
	t_del				*value_del;
	size_t				value_size;
};

/*
** lst1 struct - simple linked list
*/
typedef struct s_list	t_list;
struct					s_list
{
	void				*content;
	size_t				content_size;
	t_list				*next;
};

/*
** lst2 struct - double linked list
*/
typedef struct s_lst	t_lst;
struct					s_lst
{
	void				*content;
	size_t				content_size;
	t_lst				*next;
	t_lst				*prev;
};

/*
** arr
*/
t_arr					*ft_arrnew(size_t length, size_t sizeof_element);
t_arr					*ft_arrdup(t_arr *arr);
void					ft_arrdel(t_arr **arr);
void					ft_arrpush(t_arr *arr, void *data, int index);
void					*ft_arrpop(t_arr *arr, int index);
void					*ft_arrget(t_arr *arr, int index);
void					ft_arrswap(t_arr *arr, int i, int j);
t_bool					ft_arrequ(t_arr *arr1, t_arr *arr2);
void					ft_arrsort(t_arr *arr);
void					*ft_arrfind(t_arr *arr, void *data);
void					ft_arrmult(t_arr *arr, size_t factor);
t_bool					ft_arrjoin(t_arr *dest, t_arr *src);
void					ft_arrslice(t_arr *arr, int start, int stop, int slide);

/*
** bst
*/
t_bst					*ft_bstnew(void *content, size_t content_size);
void					ft_bstdel(t_bst **root, t_del *del);
size_t					ft_bstlen(t_bst *root);
void					ft_bstdelone(t_bst **node, t_del *del);
t_bst					*ft_bstmax(t_bst *node);
t_bst					*ft_bstmin(t_bst *node);
void					ft_bstinorder(t_bst *root, void (*f)(t_bst *node));
void					ft_bstpreorder(t_bst *root, void (*f)(t_bst *node));
void					ft_bstpostorder(t_bst *root, void (*f)(t_bst *node));
void					*ft_bstadd(t_bst **root, void *content, \
							size_t content_size, t_cmp *cmp);
t_bst					**ft_bstfind(t_bst **root, t_bst *node, t_cmp *cmp);
t_bst					**ft_bstsearch(t_bst **root, void *content, \
							size_t content_size, t_cmp *cmp);
void					*ft_bstavladd(t_bst **root, void *content, \
							size_t content_size, t_cmp *cmp);
void					ft_bstavldelone(t_bst **root, t_bst **to_del, \
							t_cmp *cmp, t_del *del);

/*
** hash
*/
t_htable				*ft_hnew(size_t bucket_size);
void					ft_hset(t_htable *table, void *key, void *value);
void					*ft_hget(t_htable *table, void *key);
void					*ft_hfind(t_htable *table, void *value);
void					ft_hiter(t_htable *table, void (*f)(t_hnode *node));
void					ft_hdel(t_htable **table);
void					ft_hdelone(t_htable *table, void *key);

/*
** int
*/
int						ft_isalnum(int i);
int						ft_isalpha(int i);
int						ft_isascii(int i);
int						ft_isblank(int c);
int						ft_iscntrl(int c);
int						ft_isdigit(int i);
int						ft_isgraph(int c);
int						ft_islower(int c);
int						ft_isprint(int i);
int						ft_ispunct(int c);
int						ft_isspace(int c);
int						ft_isupper(int c);
int						ft_isxdigit(int c);
int						ft_tolower(int c);
int						ft_toupper(int c);
int						ft_max(int i, int j);
int						ft_min(int i, int j);
int						ft_abs(int i);
char					*ft_itoa(int n);

/*
** io
*/
void					ft_putchar(char c);
void					ft_putchar_fd(char c, int fd);
void					ft_putendl(char const *s);
void					ft_putendl_fd(char const *s, int fd);
void					*fail(char const *s);
void					*failn(char const *s);
void					ft_putdbl(double nbr);
void					ft_putdbl_fd(double nbr, int fd);
void					ft_putnbr(int nbr);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr(char const *s);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putdbl_clr(double nbr, char *clr);
void					ft_putnbr_clr(int nbr, char *clr);
void					ft_putstr_clr(char *s, char *clr);
void					ft_putendl_clr(char *s, char *clr);
void					ft_putchar_clr(char c, char *clr);
void					ft_debugstr(char *name, char *str);
void					ft_debugnbr(char *name, int nbr);
void					ft_debugdbl(char *name, double nbr);
int						get_all(int const fd, char **a);
int						get_next_line(int const fd, char **line);

/*
** lst1
*/
t_list					*ft_lstnew(void const *content, size_t content_size);
t_list					*ft_lstmap(t_list *alst, t_list *(*f)(t_list *elem));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstaddlast(t_list **alst, t_list *new);
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void					ft_lstdellink(t_list **alst, t_list *link);
void					ft_lstinser(t_list **alst, t_list *new);
void					ft_lstiter(t_list *alst, void (*f)(t_list *elem));
void					ft_lstrplc(t_list **alst, t_list *old, t_list *new);
size_t					ft_lstisn(t_list *alst, t_list *link);
size_t					ft_lstlen(t_list *alst);
t_list					*ft_lstlast(t_list *link);
t_list					*ft_lstat(t_list *alst, size_t n);
t_list					**ft_lstfind(t_list **alst, void *data, t_cmp *cmp);

/*
** lst2
*/
t_lst					*ft_lnew(void *content, size_t content_size);
t_lst					*ft_lmap(t_lst *alst, t_lst *(*f)(t_lst *elem));
void					ft_ladd(t_lst **alst, t_lst *new);
void					ft_laddlast(t_lst **alst, t_lst *new);
void					ft_ldel(t_lst **alst, void (*del)(void *, size_t));
void					ft_ldelone(t_lst **alst, void (*del)(void*, size_t));
void					ft_ldellink(t_lst *link);
void					ft_linser(t_lst **alst, t_lst *new);
void					ft_linsert_list(t_lst *dst, t_lst *src);
void					ft_liter(t_lst *alst, void (*f)(t_lst *elem));
void					ft_lrplc(t_lst *old, t_lst *new);
void					ft_lswap(t_lst *link1, t_lst *link2);
size_t					ft_lisn(t_lst *alst, t_lst *link);
size_t					ft_llen(t_lst *alst);
t_lst					*ft_lat(t_lst *alst, size_t n);
t_lst					*ft_lfirst(t_lst *link);
t_lst					*ft_llast(t_lst *link);
t_lst					**ft_lfind(t_lst **alst, void *data, t_cmp *cmp);

/*
** mem
*/
void					ft_shellsort(void *arr, size_t length, \
							size_t sizeof_element, t_ncmp *cmp);
void					ft_bzero(void *s, size_t n);
void					ft_memdel(void **ap);
void					*ft_memalloc(size_t size);
void					*ft_memccpy(void *dest, const void *src, int c, \
							size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memset(void *s, int c, size_t n);
void					*ft_realloc(void *old, size_t old_size, \
							size_t new_size);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					ft_swap(void *a, void *b, size_t n);

/*
** str
*/
int						ft_istoobig(char *s);
void					ft_strclr(char *s);
void					ft_strdel(char **as);
void					ft_striter(char *s, void (*f)(char*));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
int						ft_atoi(char *str);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strequ(char const *s1, char const *s2);
int						ft_strindex(const char *s, int c);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_strrindex(const char *s, int c);
size_t					ft_strlcat(char *dest, const char *src, size_t size);
size_t					ft_strlen(const char *str);
char					*ft_strcat(char *dest, const char *src);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strdup(char *src);
char					*ft_strchr(const char *s, int c);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s, \
							char (*f)(unsigned int, char));
char					*ft_strncat(char *dest, const char *src, size_t n);
char					*ft_strncpy(char *dest, const char *src, size_t n);
char					*ft_strndup(char *src, size_t n);
char					*ft_strnew(size_t size);
char					*ft_strnstr(const char *s1, const char *s2, size_t n);
char					*ft_strrchr(const char *s, int c);
char					*ft_strsub(char const *s, unsigned int start, \
							size_t len);
char					*ft_strstr(const char *str, const char *to_find);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char const *s, char c);

#endif
