# 42 minishell
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
