*This project has been created as part of the 42 curriculum by strieste, cbezenco.*

# DESCRIPTION

> The goal of this project is to create a small version of the shell. 
> This minishell has to handle single and double quotes, redirections, pipes, environment variables and signals. It also has to implement some built-in commands.

# INSTRUCTIONS

> To launch the compilation, write "make" in your terminal. 
> To execute the program, write "./minishell" in your terminal.

# RESOURCES

Man Bash :

https://www.gnu.org/software/bash/manual/bash.html

Man Readline :

https://man7.org/linux/man-pages/man3/readline.3.html

Man Fork :

https://man7.org/linux/man-pages/man2/fork.2.html

Man Signal :

https://man7.org/linux/man-pages/man7/signal.7.html


> (mic dropped).

Supress readline leaks:

{
    readline_leaks
    Memcheck:Leak
    match-leak-kinds: reachable
    ...
    fun:readline
    ...
}
{
    readline_history_leaks
    Memcheck:Leak
    match-leak-kinds: reachable
    ...
    fun:add_history
    ...
}