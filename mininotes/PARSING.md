functions used for parsing :
-readline : EOF (-1)
- https://github.com/kibatche/parser-bison/blob/main/README.md 


get cmd ()
	 parcours de la chaine jusqua espace pipe ou Redirectiion

ORDRE DE PRIORITE :
- ~
- $
- REDIRECTION;
- CMD
- "" et ''
- arg


handle [[Redirections]]

get all the instruction in a [[chain_list]] we will send  to [[EXECUTION]]
