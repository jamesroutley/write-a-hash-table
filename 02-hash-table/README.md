# Hash table structure

Our key-value pairs (items) will each be stored in a `struct`:

```c
// hash_table.h
typedef struct {
    char* key;
    char* value;
} ht_item;
```

Our hash table stores an array of pointers to items, and some details about its
size and how full it is:

```c
// hash_table.h
typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;
```

## Initialising and deleting

We need to define initialisation functions for `ht_item`s. This function
allocates a chunk of memory the size of an `ht_item`, and saves a copy of the
strings `k` and `v` in the new chunk of memory. The function is marked as
`static` because it will only ever be called by code internal to the hash table.

```c
// hash_table.c
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static ht_item* ht_new_item(const char* k, const char* v) {
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}
```

`ht_new` initialises a new hash table. `size` defines how many items we can
store. This is fixed at 53 for now. We'll expand this in the section on
[resizing](/06-resizing). We initialise the array of items with `calloc`, which
fills the allocated memory with `NULL` bytes. A `NULL` entry in the array
indicates that the bucket is empty.

```c
// hash_table.c
ht_hash_table* ht_new() {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));

    ht->size = 53;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}
```

We also need functions for deleting `ht_item`s and `ht_hash_tables`, which
`free` the memory we've allocated, so we don't cause [memory
leaks](https://en.wikipedia.org/wiki/Memory_leak).

```c
// hash_table.c
static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}


void ht_del_hash_table(ht_hash_table* ht) {
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) {
            ht_del_item(item);
        }
    }
    free(ht->items);
    free(ht);
}
```

We have written code which defines a hash table, and lets us create and destroy
one. Although it doesn't do much at this point, we can still try it out.

```c
// main.c
#include "hash_table.h"

int main() {
    ht_hash_table* ht = ht_new();
    ht_del_hash_table(ht);
}
```

Next section: [Hash functions](/03-hashing)
[Table of contents](https://github.com/jamesroutley/write-a-hash-table#contents)
