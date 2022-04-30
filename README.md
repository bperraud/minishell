# 42 minishell
## Installation
This minishell uses GNU readline. To avoid line wrapping bugs, you should install latest build of readline.  
On schools' Mac, you night need to install homebrew, and then readline  
```rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
brew install readline
```
You also need to export compilation and linking flags if readine is installed in your home directory
```
export CFLAGS="-I/Users/$USER/.brew/opt/readline/include"
export LFLAGS="-L/Users/$USER/.brew/opt/readline/lib"
```
Then, just compile and run
```
make
./minishell
```
## commandes (cmd)
si fin de ligne -> mode = NONE: executer la commande  
si | -> mode = PIPE: creer un pipe vers la prochaine commande  
si && -> mode = AND: executer la commande seulement si la precedente est ok  
si || -> mode = OR: executer la commande seulement si la precedente est ko  

## variables d'environnement (var)
si, dans une commande, il y a un =, definir la variable d'environnement  
si il y a un dollar, il faut le remplacer par sa valeur SAUF si l'argument est dans entre squotes '  

## redirections
(<<) si here\_doc != NULL -> lire avec here\_doc, qui est le delimiteur    
(<) si fd_in != 0 -> lire dans fd_in a la place de stdin  
(>) si fd_out != 1 -> ecrire dans fd_out a la place de stdout  
(>>) si, en plus, append\_out == TRUE -> ecrire en mode append  
