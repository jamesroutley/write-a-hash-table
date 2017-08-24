# Resizing

Currently, our hash table has a fixed number of buckets. As more items are
inserted, the table starts to fill up. This is problematic for two reasons:

1. The hash table's performance diminishes with high rates of collisions
2. Our hash table can only store a fixed number of items. If we try to store
   more than that, the insert function will fail.

To mitigate this, we can increase the size of the item array when it gets too
full. We store the number of items stored in the hash table in the table's
`count` attribute. On each insert and delete, we calculate the table's 'load',
or ratio of filled buckets to total buckets. If it gets higher or lower than
certain values, we resize the bucket up or down.

We will resize:

- up, if load > 0.7
- down, if load < 0.1

To resize, we create a new hash table roughly half or twice as big as the
current, and insert all non-deleted items into it.

Our new array size should be a prime number roughly double or half the current
size.  Finding the new array size isn't trivial. To do so, we store a base
size, which we want the array to be, and then define the actual size as the
first prime larger than the base size. To resize up, we double the base size,
and find the first larger prime, and to resize down, we halve the size and
find the next larger prime.

Our base sizes start at 50. Instead of storing

We use a brute-force method to find the next prime, by checking if each
successive number is prime. While brute-forcing anything sounds alarming, the
number of values we actually have to check is low, and the time it takes is
outweighed by the time spent re-hashing every item in the table.

First, let's define a function for finding the next prime. We'll do this in two
new files, `prime.h` and `prime.c`.

```c
// prime.h
int is_prime(const int x);
int next_prime(int x);
```

```c
// prime.c

#include <math.h>

#include "prime.h"


/*
 * Return whether x is prime or not
 *
 * Returns:
 *   1  - prime
 *   0  - not prime
 *   -1 - undefined (i.e. x < 2)
 */
int is_prime(const int x) {
    if (x < 2) { return -1; }
    if (x < 4) { return 1; }
    if ((x % 2) == 0) { return 0; }
    for (int i = 3; i <= floor(sqrt((double) x)); i += 2) {
        if ((x % i) == 0) {
            return 0;
        }
    }
    return 1;
}


/*
 * Return the next prime after x, or x if x is prime
 */
int next_prime(int x) {
    while (is_prime(x) != 1) {
        x++;
    }
    return x;
}
```

Next, we need to update our `ht_new` function to support creating hash tables
of a certain size. To do this, we'll create a new function, `ht_new_sized`. We
change `ht_new` to call `ht_new_sized` with the default starting size.

```c
// hash_table.c
static ht_hash_table* ht_new_sized(const int base_size) {
    ht_hash_table* ht = xmalloc(sizeof(ht_hash_table));
    ht->base_size = base_size;

    ht->size = next_prime(ht->base_size);

    ht->count = 0;
    ht->items = xcalloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}


ht_hash_table* ht_new() {
    return ht_new_sized(HT_INITIAL_BASE_SIZE);
}
```

Now we have all the parts we need to write our resize function.

In our resize function, we check to make sure we're not attempting to reduce the
size of the hash table below its minimum. We then initialise a new hash table
with the desired size. All non `NULL` or deleted items are inserted into the new
hash table. We then swap the attributes of the new and old hash tables before
deleting the old.

```c
// hash_table.c
static void ht_resize(ht_hash_table* ht, const int base_size) {
    if (base_size < HT_INITIAL_BASE_SIZE) {
        return;
    }
    ht_hash_table* new_ht = ht_new_sized(base_size);
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    // To delete new_ht, we give it ht's size and items 
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_del_hash_table(new_ht);
}
```

To simplify resizing, we define two small functions for resizing up and down.

```c
// hash_table.c
static void ht_resize_up(ht_hash_table* ht) {
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}


static void ht_resize_down(ht_hash_table* ht) {
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}
```

To perform the resize, we check the load on the hash table on insert and
deletes. If it is above or below predefined limits of 0.7 and 0.1, we resize up
or down respectively.

To avoid doing floating point maths, we multiply the count by 100, and check if
it is above or below 70 or 10.

```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    const int load = ht->count * 100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }
    // ...
}


void ht_delete(ht_hash_table* ht, const char* key) {
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }
    // ...
}
```

Next section: [Appendix](/07-appendix)
[Table of contents](https://github.com/jamesroutley/write-a-hash-table#contents)
