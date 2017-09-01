# Introduction

A hash table is a data structure which offers a fast implementation of the
associative array [API](#api). As the terminology around hash tables can be
confusing, I've added a summary [below](#terminology).

A hash table consists of an array of 'buckets', each of which stores a key-value
pair. In order to locate the bucket where a key-value pair should be stored, the
key is passed through a hashing function. This function returns an integer which
is used as the pair's index in the array of buckets. When we want to retrieve a
key-value pair, we supply the key to the same hashing function, receive its
index, and use the index to find it in the array.

Array indexing has algorithmic complexity `O(1)`, making hash tables fast at
storing and retrieving data.

Our hash table will map string keys to string values, but the principals
given here are applicable to hash tables which map arbitrary key types to
arbitrary value types. Only ASCII strings will be supported, as supporting
unicode is non-trivial and out of scope of this tutorial.

## API

Associative arrays are a collection of unordered key-value pairs. Duplicate keys
are not permitted. The following operations are supported:

- `search(a, k)`: return the value `v` associated with key `k` from the
  associative array `a`, or `NULL` if the key does not exist.
- `insert(a, k, v)`: store the pair `k:v` in the associative array `a`.
- `delete(a, k)`: delete the `k:v` pair associated with `k`, or do nothing if
  `k` does not exist.

## Setup

To set up C on your computer, please consult [Daniel Holden's](/orangeduck)
guide in the [Build Your Own
Lisp](http://www.buildyourownlisp.com/chapter2_installation) book.  Build Your
Own Lisp is a great book, and I recommend working through it.

## Code structure

Code should be laid out in the following directory structure.

```
.
├── build
└── src
    ├── hash_table.c
    ├── hash_table.h
    ├── prime.c
    └── prime.h
```

`src` will contain our code, `build` will contain our compiled binaries.

## Terminology

There are lots of names which are used interchangeably. In this article, we'll
use the following:

- Associative array: an abstract data structure which implements the
  [API](#api) described above. Also called a map, symbol table or
  dictionary.

- Hash table: a fast implementation of the associative array API which makes
  use of a hash function. Also called a hash map, map, hash or
  dictionary.

Associative arrays can be implemented with many different underlying data
structures. A (non-performant) one can be implemented by simply storing items in
an array, and iterating through the array when searching. Associative arrays and
hash tables are often confused because associative arrays are so often
implemented as hash tables.

Next section: [Hash table structure](/02-hash-table)
[Table of contents](https://github.com/jamesroutley/write-a-hash-table#contents)
