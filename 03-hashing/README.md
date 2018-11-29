# Hash function

In this section, we'll write our hash function.

The hash function we choose should:

- Take a string as its input and return a number between `0` and `m`, our
  desired bucket array length.
- Return an even distribution of bucket indexes for an average set of inputs. If
  our hash function is unevenly distributed, it will put more items in some
  buckets than others. This will lead to a higher rate of
  [collisions](#pathological-data). Collisions reduce the efficiency of our hash table.

## Algorithm

We'll make use of a generic string hashing function, expressed below in
pseudocode.

```
function hash(string, a, num_buckets):
    hash = 0
    string_len = length(string)
    for i = 0, 1, ..., string_len:
        hash += (a ** (string_len - (i+1))) * char_code(string[i])
    hash = hash % num_buckets
    return hash
```

This hash function has two steps:

1. Convert the string to a large integer
2. Reduce the size of the integer to a fixed range by taking its remainder `mod`
   `m`

The variable `a` should be a prime number larger than the size of the alphabet.
We're hashing ASCII strings, which has an alphabet size of 128, so we should
choose a prime larger than that.

`char_code` is a function which returns an integer which represents the
character. We'll use ASCII character codes for this.

Let's try the hash function out:

```
hash("cat", 151, 53)

hash = (151**2 * 99 + 151**1 * 97 + 151**0 * 116) % 53
hash = (2257299 + 14647 + 116) % 53
hash = (2272062) % 53
hash = 5
```

Changing the value of `a` give us a different hash function.

```
hash("cat", 163, 53) = 3
```

## Implementation

```c
// hash_table.c
static int ht_hash(const char* s, const int a, const int m) {
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++) {
        hash += (long)pow(a, len_s - (i+1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}
```

## Pathological data

An ideal hash function would always return an even distribution. However, for
any hash function, there is a 'pathological' set of inputs, which all hash to
the same value. To find this set of inputs, run a large set of inputs through
the function. All inputs which hash to a particular bucket form a pathological
set.

The existence of pathological input sets means there are no perfect hash
functions for all inputs. The best we can do is to create a function which
performs well for the expected data set.

Pathological inputs also poses a security issue. If a hash table is fed a set of
colliding keys by some malicious user, then searches for those keys will take
much longer (`O(n)`) than normal (`O(1)`). This can be used as a denial of
service attack against systems which are underpinned by hash tables, such as DNS
and certain web services.

Next section: [Handling collisions](/04-collisions)
[Table of contents](https://github.com/jamesroutley/write-a-hash-table#contents)
