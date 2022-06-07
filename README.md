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
ENV :
- update $PWD (attention l'update sans changer le premier point dans 'AUTRES' enleve les subshells) ! abs path
- cat | ls
- signals error code is reset
- tmp file pipex not deleted
- ls > out | ls
- enter on empty line reset error code
