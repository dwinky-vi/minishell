#include "head_minishell.h"
# include <term.h>
#include <string.h>
#include <fcntl.h>

char	*ft_strjoin_mod(char *s1, char *s2)
{
	char	*str;
	size_t	k;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (str == NULL)
	{
		free(s1);
		return (NULL);
	}
	k = 0;
	while ((s1)[k] != '\0')
	{
		*str++ = s1[k];
		k++;
	}
	while (*s2 != '\0' && *s2 != '\n')
	{
		*str++ = *s2++;
		k++;
	}
	free(s1);
	// free(s2);
	return (str - k);
}

int	ft_putchar(int ch)
{
	write(1, &ch, 1);
	return (0);
}

typedef struct s_envp
{
	char	*name;
	char	*value;
}				t_envp;

t_envp	*parse_envp(char *str)
{
	t_envp	*env;
	size_t	k;

	k = 0;
	env = (t_envp *)ft_calloc(1, sizeof(t_envp));
	while (str[k] != '=')
		k++;
	str[k] = '\0';
	env->name = ft_strdup(str);
	str[k] = '=';
	k++;
	env->value = ft_strdup(str + k);
	return (env);
}

t_list	*get_envp(char **envp)
{
	t_list	*lst;
	t_envp	*cur_envp;

	lst = NULL;
	while (*envp)
	{
		cur_envp = parse_envp(*envp);
		ft_lstadd_back(&lst, ft_lstnew(cur_envp));
		envp++;
	}
	return (lst);
}

char	*get_term_name(t_list *lst)
{
	while (lst)
	{
		if (ft_strncmp(((t_envp *)lst->content)->name, "TERM", 5) == 0)
			return (((t_envp *)lst->content)->value);
		lst = lst->next;
	}
	return ("xterm-256color");
}

int	init_term(struct termios *term, char *term_name)
{
	tcgetattr(0, term);
	term->c_lflag &= ~(ECHO); // отключаем этот флаг (бит) устанавливается на ноль. Отключаем, чтобы read показывал, что печатается
	term->c_lflag &= ~(ICANON); //переводим терминал в НЕ каноническое. В каноническом виде read завершается по нажатию \n
	tcsetattr(0, TCSANOW, term);
	tgetent(0, term_name); // подгружаем базу данных нашего терминала
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	struct termios	term;
	t_list			*head_envp;
	char			**history;
	char			*str;
	int				r;
	size_t			history_size;
	size_t			k;
	char			*line;
	size_t			cursor_pos = 0;

	head_envp = get_envp(envp);

	init_term(&term, get_term_name(head_envp));
	history = (char **)ft_calloc(100, sizeof(char *));
	line = (char *)ft_calloc(2000, 1);
	str = (char *)ft_calloc(2000, 1);
	history_size = 0;
	k = 0;
	int fd = open("history_file", O_CREAT | O_RDWR | O_APPEND, 0600); //права доступа выдаются, как в bash
	while (strcmp(str, "\4"))
	{
		tputs(save_cursor, 1, ft_putchar);
		write(1, "\033[1;35mbash-3.2$ \033[0m", 21);
		while (strcmp(str, "\n"))
		{
			r = read(0, str, 100);
			str[r] = '\0';
			if (!strcmp(str, "\4"))
			{
				// write(1, "exit\n", 5);
				tputs(delete_line, 1, ft_putchar);
				while (*history)
				{
					ft_putendl_fd(*history, 1);
					history++;
				}
				break ;
			}
			if (!strcmp(str, "\e[A")) // UP
			{
				tputs(delete_line, 1, ft_putchar);
				write(1, "\033[1;35mbash-3.2$ \033[0m", 21);			
				if (k > 0)
					k--;
				if (history_size != 0)
				{
					write(1, history[k], ft_strlen(history[k]));
					line = ft_strdup(history[k]);
					cursor_pos = ft_strlen(history[k]);
				}
			}
			else if (!strcmp(str, "\e[B")) // DOWN
			{
				tputs(delete_line, 1, ft_putchar);
				write(1, "\033[1;35mbash-3.2$ \033[0m", 21);
				if (k < history_size)
					k++;
				if (history_size == 0)
					k = 0;
				if (k == history_size)
				{
					tputs(delete_line, 1, ft_putchar);
					write(1, "\033[1;35mbash-3.2$ \033[0m", 21);
					cursor_pos = 0;
				}
				else if (history_size != 0)
				{
					cursor_pos = ft_strlen(history[k]);
					write(1, history[k], ft_strlen(history[k]));
					line = ft_strdup(history[k]);
				}
			}
			else if (!strcmp(str, "\177")) // delete
			{
				if (cursor_pos > 0)
				{
					cursor_pos--;
					// ??????????? //
				tputs(cursor_left, 1, ft_putchar); //перемещаемся влево на один символ
				tputs(delete_character, 1, ft_putchar); // удаляем символ на который указывает курсор
				line[cursor_pos] = '\0';
				}
			}
			else if (!strcmp(str, "\t")) // TAB
			{
			}
			else
			{
				write(1, str, r);
				cursor_pos++;
				line = ft_strjoin_mod(line, str);
				if (!strcmp(str, "\n"))
				{
					cursor_pos = 0;
					write(1, "\033[1;35mbash-3.2$ \033[0m", 21);
					if (k != history_size) // это для истории. Когда мы нажимали на стрелочки
						k = history_size;
					history[k] = ft_strdup(line);
					write(fd, history[k], ft_strlen(history[k]));
					write(fd, "\n", 1);
					ft_bzero(line, ft_strlen(line)); // ???????????????????
					history_size++;
					k = history_size;
				}
			}
			str[0] = '\0';
		}
		ft_putstr_fd("bye", 1);
		close(fd);
	}
	return (0);
}
// #define	EXIT_FAILURE	1
// #define	EXIT_SUCCESS	0

// дописать историю. Считывать файл с историей и добавлять в двумерный массив.
// Пример: 1 2 3 4 5 + подняться вверх написать что-то, потом удалить и нажать вниз, потом enter

	// term.c_cc[VMIN] = 1; // минимальное количество символов считается
	// term.c_cc[VTIME] = 0; //сколько read будет ждать