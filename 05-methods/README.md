# Methods

Our hash function will implement the following API:

```c
// hash_table.h
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);
```

## Insert

To insert a new key-value pair, we iterate through indexes until we find an
empty bucket. We then insert the item into that bucket and increment the hash
table's `count` attribute, to indicate a new item has been added. A hash table's
`count` attribute will become useful when we look at [resizing](/06-resizing) in
the next section.

```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    ht_item* item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL) {
        index = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    } 
    ht->items[index] = item;
    ht->count++;
}
```

## Search

Searching is similar to inserting, but at each iteration of the `while` loop,
we check whether the item's key matches the key we're searching for. If it does,
we return the item's value. If the while loop hits a `NULL` bucket, we return
`NULL`, to indicate that no value was found.

```c
// hash_table.c
char* ht_search(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    } 
    return NULL;
}
```

## Delete

Deleting from an open addressed hash table is more complicated than inserting or
searching. The item we wish to delete may be part of a collision chain. Removing
it from the table will break that chain, and will make finding items in the tail
of the chain impossible. To solve this, instead of deleting the item, we
simply mark it as deleted.

We mark an item as deleted by replacing it with a pointer to a global sentinel
item which represents that a bucket contains a deleted item.

```c
// hash_table.c
static ht_item HT_DELETED_ITEM = {NULL, NULL};


void ht_delete(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                ht_del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    } 
    ht->count--;
}
```
After deleting, we decrement the hash table's `count` attribute.

We also need to modify `ht_insert` and `ht_search` functions to take account of
deleted nodes.

When searching, we ignore and 'jump over' deleted nodes. When inserting, if we
hit a deleted node, we can insert the new node into the deleted slot.

```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    // ...
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
        // ...
    }
    // ...
}


char* ht_search(ht_hash_table* ht, const char* key) {
    // ...
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) { 
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        // ...
    }
    // ...
}
```

## Update

Our hash table doesn't currently support updating a key's value. If we insert
two items with the same key, the keys will collide, and the second item will be
inserted into the next available bucket. When searching for the key, the
original key will always be found, and we are unable to access the second item.

We can fix this my modifying `ht_insert` to delete the previous item and insert
the new item at its location.

```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    // ...
    while (cur_item != NULL) {
        if (cur_item != &HT_DELETED_ITEM) {
            if (strcmp(cur_item->key, key) == 0) {
                ht_del_item(cur_item);
                ht->items[index] = item;
                return;
            }
        }
        // ...
    } 
    // ...
}
```

Next section: [Resizing tables](/06-resizing)
[Table of contents](https://github.com/jamesroutley/write-a-hash-table#contents)
