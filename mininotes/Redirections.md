[[EXECUTION]]


◦ < should redirect input. when catching the char"<" skip isspace  then copy every char until the next isspace in t_cmd->infile (see [[chain_list]]) and define t_cmd->type on NO_HEREDOC.


◦ > should redirect output. when catching the char">" skip isspace  then copy every char until the next isspace in t_cmd->outfile (see [[chain_list]]) and define t_cmd->type on NO_APPEND so the following argument wil replace the content of the outfile.


◦ << should be given a delimiter, then read the input until a line containing the
delimiter is seen (here-document). However, it doesn’t have to update the history!


◦ >> should redirect output in append mode. when catching the chars ">>" skip isspace  then copy every char until the next isspace in t_cmd->outfile (see [[chain_list]]) and define t_cmd->type on APPEND so the following argument will be add at the end of the outfile and will not replace his content.