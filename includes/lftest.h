/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lftest.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:25:24 by bazaluga          #+#    #+#             */
/*   Updated: 2023/12/06 02:32:26 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LFTEST_H
# define LFTEST_H
# ifdef __linux__
#  define _GNU_SOURCE
#  include <bsd/string.h>
# endif
# include "CuTest.h"
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include <limits.h>
# include <dlfcn.h>
# define BUFFSIZE 30
# define BUFFBSIZE 2048
# define BUFFBBSIZE 8192
# define ANSI_COLOR_RED     "\033[31m"
# define ANSI_COLOR_GREEN   "\033[32m"
# define ANSI_COLOR_RESET	"\033[0m"
# define N_TESTS_FUN 34

/********************************** STRUCTS ***********************************/

typedef struct	s_ft
{
	char	*fun_name;
	void	*fun;
	void	*test_fun;
}				t_ft;

typedef struct	print_buff
{
	char	color;
	char	txt[BUFFBBSIZE];
}				print_buff;

typedef struct	s_malloc t_malloc;
struct	s_malloc
{
	unsigned long	addr;
	size_t			size;
	size_t			rank;
	t_malloc		*next;
};

typedef struct	s_leaks_tracer t_leaks_tracer;
struct	s_leaks_tracer
{
	t_malloc	*first_malloc;
	int			count;
	int			in_use;
};

/****************************** GLOBAL VARIABLES ******************************/

extern int				g_exit_code;
extern pid_t			g_pid;
extern int				g_malloc_fail;
extern size_t			g_last_malloc_size;
extern t_leaks_tracer	g_leaks;
extern char				*g_leaks_text;
extern t_ft				fcts[34];
extern print_buff		buff;
extern int				g_in_fun;
extern int				fds[2];
extern char				pipe_buff[BUFFSIZE];

/*********************************** MACROS ***********************************/

/* Testing mallocs */
# define FAIL_MALLOC g_malloc_fail = 1;
# define END_FAIL g_malloc_fail = 0;
# define LEAKS_TRACER_START if (g_leaks_text) {	\
		free(g_leaks_text);						\
		g_leaks_text = NULL;}					\
	leaks_tracer_reset(&g_leaks);				\
	leaks_tracer_start(&g_leaks);
# define LEAKS_TRACER_STOP leaks_tracer_stop(&g_leaks);
# define LEAKS_TRACER_RESULT LEAKS_TRACER_STOP;						\
	g_leaks_text = leaks_tracer_text(&g_leaks);						\
	/* *s = leaks_tracer_text(&g_leaks);*/							\
	/*g_leaks_text = *s;*/											\
	leaks_tracer_reset(&g_leaks);
# define LEAKS_OK g_leaks_text == NULL
/* Getting fds & protecting stdout + stderr */
# define CLOSE_OUTPUTS manage_outputs(1);
# define OPEN_OUTPUTS manage_outputs(0);
# define OPEN_PIPE manage_pipes(1, 0);
# define CLOSE_PIPE manage_pipes(0, 1);
/* Preventing tester from crashs */
# define SANDBOX(X)								\
	if ((g_pid = fork()) == -1){				\
		perror("Error during fork");			\
		exit(1);								\
	}											\
	if (!g_pid){								\
		X;										\
		exit(0);								\
	}											\
	wait(&g_exit_code);

/*********************** MALLOCS, FREE & LEAKS FUNCTIONS **********************/

void	leaks_tracer_start(t_leaks_tracer *lst);
void	leaks_tracer_stop(t_leaks_tracer *lst);
char	*leaks_tracer_text(t_leaks_tracer *lst);
void	leaks_tracer_reset(t_leaks_tracer *lst);

/****************************** UTILS FUNCTIONS *******************************/

void	*init_fcts();
void	*get_fun(char *name);
void	*get_test_fun(char *name);
void	add_txt_buff(char *txt);
void	add_color_buff(char c);
void	printbuff();
void	manage_outputs(int to_close);
void	manage_pipes(int get_read, int get_write);

/****************************** TESTS FUNCTIONS *******************************/

CuSuite	*ft_isalpha_get_suite();
CuSuite	*ft_isdigit_get_suite();
CuSuite	*ft_isalnum_get_suite();
CuSuite	*ft_isascii_get_suite();
CuSuite	*ft_isprint_get_suite();
CuSuite	*ft_strlen_get_suite();
CuSuite	*ft_memset_get_suite();
CuSuite	*ft_bzero_get_suite();
CuSuite	*ft_memcpy_get_suite();
CuSuite	*ft_memmove_get_suite();
CuSuite	*ft_strlcpy_get_suite();
CuSuite	*ft_strlcat_get_suite();
CuSuite	*ft_toupper_get_suite();
CuSuite	*ft_tolower_get_suite();
CuSuite	*ft_strchr_get_suite();
CuSuite	*ft_strrchr_get_suite();
CuSuite	*ft_strncmp_get_suite();
CuSuite	*ft_memchr_get_suite();
CuSuite	*ft_memcmp_get_suite();
CuSuite	*ft_strnstr_get_suite();
CuSuite	*ft_atoi_get_suite();
CuSuite	*ft_calloc_get_suite();
CuSuite	*ft_strdup_get_suite();
CuSuite	*ft_substr_get_suite();
CuSuite	*ft_strjoin_get_suite();
CuSuite	*ft_strtrim_get_suite();
CuSuite	*ft_split_get_suite();
CuSuite	*ft_itoa_get_suite();
CuSuite	*ft_strmapi_get_suite();
CuSuite	*ft_striteri_get_suite();
CuSuite	*ft_putchar_fd_get_suite();
CuSuite	*ft_putstr_fd_get_suite();
CuSuite	*ft_putendl_fd_get_suite();
CuSuite	*ft_putnbr_fd_get_suite();

#endif
