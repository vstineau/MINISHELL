if arg with '='
	-> check if $
		-> replace $
	-> if before '=' exist
			->replace with after '='
	-> if before '=' didn't exist
			->  create it
if arg with no '=' 
	-> do NOTHING
if no arg
	-> print each line sort in ASCII order
	-> print "declare -x " before each line