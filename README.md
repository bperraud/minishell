# 42 minishell
## commandes (cmd)
si fin de ligne -> mode = NONE, executer la commande
si | -> mode = pipe -> creer un pipe vers la prochaine commande
si && -> mode = AND -> executer la commande seulement si la precedente est ok
si || -> mode = OR -> executer la commande seulement si la precedente est ko

## pipes
(<<) si here\_doc != NULL -> lire avec here\_doc
(<) si infile != NULL -> lire dans infile a la place de stdin
(>) si outfile != NULL -> ecrire dans outfile a la place de stdout
(>>) si, en plus, append\_out == TRUE -> ecrire en mode append
