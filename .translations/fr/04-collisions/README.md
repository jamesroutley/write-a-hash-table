## Traitement des collisions

Les fonctions de hashage peuvent avoir un nombre infini d'entrées mais ont un nombre fini de sorties. Differentes entrées peuvent ainsi retourner le meme résultat. C'est ce que l'on appelle une collision.

Notre table de hachage traitera les collisions en utilisant une technique appelée [adressage ouvert](https://fr.wikipedia.org/wiki/Table_de_hachage#Adressage_ouvert) avec une méthode de sondage de type double hachage.

Le double hashage utilise deux fonctions de hashage pour calculer l'index ou un élément doit être stocké après `i` collisions.

Pour un aperçu des autres types de résolution de collision, voir l'[annexe] (../07-appendix).

## Double hashage

L'index que nous allons utiliser apres `i` collisions est defini comme ceci :

```
index = hash_a(string) + i * hash_b(string) % num_buckets
```

Nous voyons que si aucune collision n'a eu lieu, `i = 0`, alors l'indice est juste `hash_a` de la chaîne. Si une collision se produit, l'indice est modifié par `hash_b`.

Il est possible que `hash_b` renvoie 0, réduisant le second terme à 0. Ceci rend caduque l'utilisation de `i` car `index` aura la meme valeur quelle que soit `i`. Nous pouvons résoudre cela en ajoutant 1 au résultat de `hash_b`.

```
index = (hash_a(string) + i * (hash_b(string) + 1)) % num_buckets
```

## Implémentation

```c
// hash_table.c
static int ht_get_hash(
    const char* s, const int num_buckets, const int attempt
) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}
```

Prochaine section: [Méthodes d'une table de Hachage](../05-methods)

[Table des matières](/.translations/fr/README.md#contents)
