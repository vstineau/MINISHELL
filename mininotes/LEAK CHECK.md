suppress readline leaks by adding a suppress file in the repo containing :
{
    ignore_readline_leaks
    Memcheck:Leak
    ...
    obj:*/libreadline.so*
}
then compiling with : valgrind --leak-check=full --suppressions=su
ppress ./minishell 