 {cmd} {file} {|} {infile} {cmd} 
 cat fichier | < /dev/stdin cat | ls > /dev/stdout
 cmd  arg[0]  | infile cmd arg[o] outifile 
pipe quand meme meme quand c'est builtin


je recois la commande
%% 	je check si c'est un builtin
		-> je l'execute avec les arguments qu'il faut
	sinon
		-> exec normal avec fork
 %%




