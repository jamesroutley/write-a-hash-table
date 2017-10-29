[<img src="/.translations/flags/gb.png">](/README.md) [<img src="/.translations/flags/fr.png">](/.translations/fr/README.md)

# Implémenter une table de hachage en C

Les [tables de hachage](https://fr.wikipedia.org/wiki/Table_de_hachage) sont l'une des structures de données les plus utiles.
Leur rapidité à insérer, rechercher, supprimer et leur extensibilité rendent leur utilisation pertinante pour résoudre un grand nombre de problèmes informatiques.

Dans ce tutoriel, nous implémenterons une table de hachage à [adressage ouvert](https://fr.wikipedia.org/wiki/Table_de_hachage#Adressage_ouvert) utilisant une méthode de sondage de type double hachage. Le language utilisé est le [language C](https://fr.wikipedia.org/wiki/C_(langage)).

En suivant ce tutoriel vous pourrez :

- Comprendre le fonctionnement interne d'une structure de données
- Savoir quand utiliser (ou non) une table de hachage et pourquoi elle peuvent ne pas etre efficaces.
- Manipuler du code C

Le language C est un bon language pour cet exercice car :

- Il n'inclut pas d'implémentation de table de hachage.
- C'est un language bas niveau. On se rapproche donc du fonctionnement de la machine pour l'implémentation.

Ce tutoriel part du postulat que vous avez une connaissance de la programmation et de la syntaxe du C. Le code est relativement simple et la plupart des problèmes peuvent etre résolus avec une recherche Internet. Si vous rencontrez d'autres problèmes, ouvrez un ticket (issue) sur [GitHub](https://github.com/jamesroutley/write-a-hash+table/issues).

L'implémentation complète fait autour de 200 lignes de code et suivre le tutoriel vous prendra une à deux heures.

## Sommaire

1. [Introduction](./01-introduction)
2. [Structure d'une table de hachage](./02-hash-table)
3. [Fonctions de hachage](./03-hashing)
4. [Gestion des collisions](./04-collisions)
5. [Méthodes de la table de Hachage](./05-methods)
6. [Redimensionnement](./06-resizing)
7. [Annexe : Gestion de collisions alternative](./07-appendix)

## Credits

Ce tutoriel a été écrit par [James Routley](https://twitter.com/james_routley),
qui blog ici : [routley.io](https://routley.io).

Traduit par [Sylvestre Antoine](https://github.com/yoshyn).
Corrigé par [Agathe Begault](https://github/begault).
