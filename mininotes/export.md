if arg with '='
	-> check if $
		-> replace $
	-> if before '=' exist
			->replace with after '='
	-> if before '=' didn't exist
			->  create it
if arg with no '=' 
	-> l'envoyer dans le env mais pas l'imprimer avec env 
if no arg
	-> print each line sort in ASCII order
	-> print "declare -x " before each line
gerer plusieurs arg aussi