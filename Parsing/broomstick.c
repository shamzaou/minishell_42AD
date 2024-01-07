#include "../minishell.h"

void	free_tree(t_cmd *cmd)
{
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;
	t_execcmd	*ecmd;

	if (cmd && cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		free_tree(pcmd->left);
		free_tree(pcmd->right);
		ft_free(pcmd);
	}
	else if (cmd && cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		free_tree(rcmd->subcmd);
		ft_free(rcmd);
	}
	else if (cmd && cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		ft_free(ecmd);
	}
}
