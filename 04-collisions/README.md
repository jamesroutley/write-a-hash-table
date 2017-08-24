## Handling collisions

Hash functions map an infinitely large number of inputs to a finite number of
outputs. Different input keys will map to the same array index, causing
bucket collisions. Hash tables must implement some method of dealing with
collisions. 

Our hash table will handle collisions using a technique called open addressing
with double hashing. Double hashing makes use of two hash functions to
calculate the index an item should be stored at after `i` collisions.

For an overview of other types of collision resolution, see the
[appendix](/07-appendix).

## Double hashing

The index that should be used after `i` collisions is given by:

```
index = hash_a(string) + i * hash_b(string) % num_buckets
```

We see that if no collisions have occurred, `i = 0`, so the index is just 
`hash_a` of the string. If a collision happens, the index is modified by the
`hash_b`.

It is possible that `hash_b` will return 0, reducing the second term to 0. This
will cause the hash table to try to insert the item into the same bucket over
and over. We can mitigate this by adding 1 to the result of the second hash,
making sure it's never 0.

```
index = (hash_a(string) + i * (hash_b(string) + 1)) % num_buckets
```

## Implementation

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

Next section: [Hash table methods](/05-methods)
[Table of contents](https://github.com/jamesroutley/write-a-hash-table#contents)
