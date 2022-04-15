# 42 minishell
## commandes (cmd)
si fin de ligne -> mode = NONE: executer la commande  
si | -> mode = pipe: creer un pipe vers la prochaine commande  
si && -> mode = AND: executer la commande seulement si la precedente est ok  
si || -> mode = OR: executer la commande seulement si la precedente est ko  

## variables d'environnement (var)
si, dans une commande, il y a un =, definir la variable d'environnement  
si il y a un dollar, il faut le remplacer par sa valeur SAUF si l'argument est dans entre dquotes "  

## pipes
(<<) si here\_doc != NULL -> lire avec here\_doc  
(<) si infile != NULL -> lire dans infile a la place de stdin  
(>) si outfile != NULL -> ecrire dans outfile a la place de stdout  
(>>) si, en plus, append\_out == TRUE -> ecrire en mode append  
