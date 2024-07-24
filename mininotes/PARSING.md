functions used for parsing :
-readline : EOF (-1)
- https://github.com/kibatche/parser-bison/blob/main/README.md 


get cmd ()
	 parcours de la chaine jusqua espace pipe ou Redirectiion




ifnfile et outfile

{
 if infile/outfile
	 free infile/outfile

}



ORDRE DE PRIORITE :
- ~ (entre deux espaces ou suivi d'un '/')
- $
- REDIRECTION;
- CMD
- "" et ''
- arg


handle [[Redirections]]

get all the instruction in a [[chain_list]] we will send  to [[EXECUTION]]
