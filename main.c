#include "head_minishell.h"

void	ft_putline(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 1);
	ft_putstr_fd(s2, 1);
	ft_putstr_fd(s3, 1);
}

void	ft_putline_nbr(char *s1, int nbr)
{
	ft_putstr_fd(s1, 1);
	ft_putnbr_fd(nbr, 1);
	ft_putstr_fd("\n", 1);
}

int	ft_putchar(int ch)
{
	write(1, &ch, 1);
	return (0);
}

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

int	parser(char *line, t_list *list_env, char **envp)
{
	t_command	command;
	size_t		k;
	size_t		count;

	if (line == NULL)
		return (-1);
	while (*line == ' ')
		line++;
	k = 0;
	while (line[k] != ' ' && line[k])
		k++;
	command.name = ft_substr(line, 0, k);
	line += k;
	k = 0;
	command.args = (char **)ft_calloc(20, sizeof(char *)); // кол-во аргументов
	count = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		k = 0;
		while (line[k] != ' ' && line[k])
			k++;
		command.args[count++] = ft_substr(line, 0, k);
		line += k;
	}

	processing(&command, list_env, envp);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	struct termios	term;
	t_list			*head_env;
	char			**history;
	char			*str;
	int				r;
	size_t			history_size;
	size_t			k;
	char			*line;
	size_t			cursor_pos = 0;
	int				fd;

	head_env = get_envp(envp);
	init_term(&term, get_term_name(head_env));
	history = (char **)ft_calloc(200, sizeof(char *));
	str = (char *)ft_calloc(2000, 1);
	history_size = 0;
	fd = open("history_file", O_CREAT | O_RDWR | O_APPEND, 0600); //права доступа выдаются, как в bash
	k = 0;
	while ((r = get_next_line(fd, &line)) >= 0)
	{
		if (*line != '\0')
			history[k++] = line;
		if (r == 0)
			break ;
	}
	history_size = k;
	line = (char *)ft_calloc(2000, 1);
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
				write(1, "exit\n", 5);
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
					ft_bzero(line, ft_strlen(line));
				}
				else if (history_size != 0)
				{
					cursor_pos = ft_strlen(history[k]);
					write(1, history[k], ft_strlen(history[k]));
					line = ft_strdup(history[k]);
				}
			}
			else if (!strcmp(str, "\e[D")) // LEFT // Влево –– ^[[D
			{
			}
			else if (!strcmp(str, "\e[C")) // RIGHT // вправо –– ^[[C
			{
			}
			else if (!strcmp(str, "\e[3~")) // del // (удалить справа) –– ^[[3~
			{
			}
			else if (!strcmp(str, "\177")) // delete
			{
				if (cursor_pos > 0)
				{
					cursor_pos--;
					tputs(cursor_left, 1, ft_putchar); //перемещаемся влево на один символ
					tputs(delete_character, 1, ft_putchar); // удаляем символ на который указывает курсор
					line[cursor_pos] = '\0';
				}
			}
			else if (!strcmp(str, "\t") || !strcmp(str, "\e[H")  || !strcmp(str, "\e[F")) // TAB /** в начало строки –– [H **/ /** в конец строки ––[F **/
			{
			}
			else
			{
				write(1, str, r);
				if (!strcmp(str, "\n"))
				{
					parser(line, head_env, envp);
					cursor_pos = 0;
					write(1, "\033[1;35mbash-3.2$ \033[0m", 21);
					if (k != history_size) // это для истории. Когда мы нажимали на стрелочки
						k = history_size;
					if (strcmp(line, ""))
					{
						history[k] = ft_strdup(line);
						write(fd, history[k], ft_strlen(history[k]));
						write(fd, "\n", 1);
						history_size++;
						k = history_size;
					}
					ft_bzero(line, ft_strlen(line)); // чтобы после enter строка очищалась
				}
				else
				{
					cursor_pos++;
					line = ft_strjoin_free(line, str, 1);
				}
			}
			str[0] = '\0';
		}
	}
	close(fd);
	return (0);
}
