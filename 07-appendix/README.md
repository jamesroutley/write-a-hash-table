# Appendix: alternative collision handling

There are two common methods for handling collisions in hash tables:

- Separate chaining
- Open addressing

### Separate chaining

Under separate chaining, each bucket contains a linked list. When items collide,
they are added to the list. Methods:

- Insert: hash the key to get the bucket index. If there is nothing in that
  bucket, store the item there. If there is already an item there, append the
  item to the linked list.
- Search: hash the key to get the bucket index. Traverse the linked list,
  comparing each item's key to the search key. If the key is found, return the
  value, else return `NULL`.
- Delete: hash the key to get the bucket index. Traverse the linked list,
  comparing each item's key to the delete key. If the key is found, remove the
  item from the linked list. If there is only one item in the linked list,
  place the `NULL` pointer in the bucket, to indicate that it is empty.


This has the advantage of being simple to implement, but is space inefficient.
Each item has to also store a pointer to the next item in the linked list, or
the `NULL` pointer if no items come after it. This is space wasted on
bookkeeping, which could be spent on storing more items.

### Open addressing

Open addressing aims to solve the space inefficiency of separate chaining. When
collisions happen, the collided item is placed in some other bucket in the
table. The bucket that the item is placed into is chosen according some
predetermined rule, which can be repeated when searching for the item. There are
three common methods for choosing the bucket to insert a collided item into.

#### Linear probing. 

When a collision occurs, the index is incremented and the item is put in the
next available bucket in the array. Methods:

- Insert: hash the key to find the bucket index. If the bucket is empty, insert
  the item there. If it is not empty, repeatedly increment the index until an
  empty bucket is found, and insert it there.
- Search: hash the key to find the bucket index. Repeatedly increment the index,
  comparing each item's key to the search key, until an empty bucket is found.
  If an item with a matching key is found, return the value, else return `NULL`.
- Delete: hash the key to find the bucket index. Repeatedly increment the index,
  comparing each item's key to the delete key, until an empty bucket is found.
  If an item with a matching key is found, delete it. Deleting this item breaks
  the chain, so we have no choice but to reinsert all items in the chain after
  the deleted item.


Linear probing offers good [cache
performance](https://en.wikipedia.org/wiki/Locality_of_reference), but suffers
from clustering issues. Putting collided items in the next available bucket can
lead to long contiguous stretches of filled buckets, which need to be iterated
over when inserting, searching or deleting.

#### Quadratic probing. 

Similar to linear probing, but instead of putting the collided item in the next
available bucket, we try to put it in the buckets whose indexes follow the
sequence: `i, i + 1, i + 4, i + 9, i + 16, ...`, where `i` is the original hash
of the key. Methods:

- Insert: hash the key to find the bucket index. Follow the probing sequence
  until an empty or deleted bucket is found, and insert the item there.
- Search: hash the key to find the bucket index. Follow the probing sequence,
  comparing each item's key to the search key until an empty bucket is found. If
  a matching key is found, return the value, else return `NULL`.
- Delete: we can't tell if the item we're deleting is part of a collision chain,
  so we can't delete the item outright. Instead, we just mark it as deleted.

Quadratic probing reduces, but does not remove, clustering, and still offers
decent cache performance.

#### Double hashing. 

Double hashing aims to solve the clustering problem. To do so, we use a second
hash function to choose a new index for the item. Using a hash function gives us
a new bucket, the index of which should be evenly distributed across all
buckets. This removes clustering, but also removes any boosted cache performance
from locality of reference. Double hashing is a common method of collision
management in production hash tables, and is the method we implement in this
tutorial.


