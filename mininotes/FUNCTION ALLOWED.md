
## - **readline :** 
	 ## - **char *readline(const char *prompt);**
		## readline will read a line from the terminal and return it, using prompt as a prompt.
     ## - If prompt is NULL or the empty string, no prompt is issued.  The  line  returned  is allocated  with malloc(3); the caller must free it when finished.  The line returned has the final newline removed, so only the text of the line remains 
    	## - readline returns the text of the line read.  A blank line returns the empty  string.
    ## - If EOF is encountered while reading a line, and the line is empty, NULL is returned.
    ## - If an EOF is read with a non-empty line, it is treated as a newline.
## - **rl_clear_history :**
	## - **void rl_clear_history(void);**
	## - **Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.**
## - **rl_on_new_line,**
	## - **int rl_on_new_line(void);**
	## - **Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.**
## - **rl_replace_line :**
	## - **void rl_replace_line(const *char text, int clear_undo)**
	## - **Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.**
## - **rl_redisplay :**
	## - **void rl_redisplay(void);**
	## - **Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.**
## - **add_history :**
	## - **void add_history(const char line );**
	## - **add the line to the history list for a future recall**
## - **access :**
	## - **int access(const char *pathname, int mode);**
	## - **access() checks whether the calling process can access the file pathname.  If pathname is a symbolic link, it is dereferenced.**
	## - **the  mode specifies the accessibility check(s) to be performed, and is either the value F_OK, or a mask consisting of the bitwise OR of one or more of R_OK, W_OK, and X_OK.  F_OK tests for the existence of the file.  R_OK, W_OK, and X_OK test whether the file exists and grants read, write, and execute permissions, respectively.**
	## - **On success (all requested permissions granted, or mode is F_OK and the file exists), zero is returned.  On error (at least one bit in mode asked for a permission that is  denied, or mode is F_OK and the file does not exist, or some other error occurred), -1 is returned, and errno is set appropriately.**
## - **fork :**
## - **wait :**
## - **waitpid :**
## - **wait3 :**
## - **wait4 :**
## - **signal :**
## - **sigaction :**
## - **sigemptyset :**
## - **sigaddset :**
## - **kill :**
## - **exit :**
## - **getcwd :**
	char *getcwd(char *buf, size_t size);
	These functions return a null-terminated string containing an absolute pathname that is the current working directory of the calling process.  The pathname  is  returned as the function result and via the argument buf, if present. The  getcwd()  function copies an absolute pathname of the current working directory to the array pointed to by buf, which is of length size. If the length of the absolute pathname of the current working  directory,  including the terminating null byte, exceeds size bytes, NULL is returned, and errno is set to ERANGE; an application should check for this error, and allocate a larger buffer  if necessary 
	On  success, these functions return a pointer to a string containing the pathname of the current working directory.  In the case of getcwd() and getwd() this is the same value as buf. On  failure,  these  functions  return NULL, and errno is set to indicate the error.The contents of the array pointed to by buf are undefined on error.
## - **chdir :**
int chdir(const char *path)
chdir() changes the current working directory of the calling process to the directory specified in path.
On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

## - **stat :**
## - **lstat :**
## - **fstat :** 
## - **unlink :** 
unlink - call the unlink function to remove the specified file
## - **execve :**
## - **dup :**
## - **dup2 :**
## - **pipe :**
## - **opendir :**
## - **readdir :**
## - **closedir,**
## - **strerror :**
## - **perror :**
## - **isatty :** 
## - **ttyname :** 
## - **ttyslot :** 
## - **ioctl :**
## - **getenv :** 
## - **tcsetattr :** 
## - **tcgetattr :** 
## - **tgetent :** 
## - **tgetflag :**
## - **tgetnum :**
## - **tgetstr :**
## - **tgoto :**
## - **tputs :**