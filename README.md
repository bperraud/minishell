# 42 minishell
## Installation
This minishell uses GNU readline. It was tested with version 8.1 and might not work on earlier versions.
To install it on schools' Mac, install homebrew, and then readline.
```
rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
brew install readline
```
Then, export header and lib files to compilation and linking flags.
```
export CFLAGS="-I/Users/$USER/.brew/opt/readline/include"
export LFLAGS="-L/Users/$USER/.brew/opt/readline/lib"
```
Compile and run
```
make
./minishell
```
## TODO
- rajouter gestion error appels systèmes (pipe, fork etc)
- 'export a=3 && echo $a'
- 'export $a' -> Segmentation fault
- Error (ls && ls) et espace avant parenthese -> parsing error
- Wildcards
- Finish
	- Norme
	- Tests (with error codes)

## commandes (cmd)
si fin de ligne -> mode = NONE: executer la commande
si | -> mode = PIPE: creer un pipe vers la prochaine commande
si && -> mode = AND: executer la commande seulement si la precedente est ok
si || -> mode = OR: executer la commande seulement si la precedente est ko

## redirections
(<<) si here\_doc != NULL -> lire avec here\_doc, qui est le delimiteur
(<) si fd_in != 0 -> lire dans fd_in a la place de stdin
(>) si fd_out != 1 -> ecrire dans fd_out a la place de stdout
(>>) si, en plus, append\_out == TRUE -> ecrire en mode append
