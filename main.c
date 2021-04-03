#include "head_minishell.h"

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
	env = (t_envp *)ft_calloc(1, sizeof(env));
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

int main(int argc, char **argv, char **envp)
{
	t_list	*head;

	head = get_envp(envp);
	while (head)
	{
		t_envp *cur = (head->content);
		printf("%s = %s\n", cur->name, cur->value);
		head = head->next;
	}
	return (0);
}