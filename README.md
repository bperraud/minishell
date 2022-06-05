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
# TODO
- Incrementer SHLVL quand on lance le shell.
- Si SHVL=999, SHLVL devient vide (dans env, SHVL= )
- Si SHVL est vide ou plus grand que 999 ou pas un int, reset SHLVL a 1
- Dans env mettre la derniere commande executee dans la variable _
- (ls && ls) > file1 syntax error 
- ligne vide doit mettre $? à 0 
- exit numeric argument required
- protection absolute path pour ./minishell (pour l'instant utilise $PWD, si unset pas de subshell possible)
- $PWD pas update dans env (attention l'update sans changer le point précedent enleve les subshells)
- redirections dans des pipes -> garder toutes les strings de la commande (pas de here_doc possible dans un pipe par ex)
- chevauchement messages d'erreurs dans des pipes
- cmd1 | cmd2 | -> segfault
