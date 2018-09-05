# 介绍

A hash table is a data structure which offers a fast implementation of the
associative array [API](#api). As the terminology around hash tables can be
confusing, I've added a summary 
哈希表是一种数据结构，它提供了关联数组 [API](#api) 的快速实现，关于哈希表的相关知识大家可能会感觉困惑和不解，没关系，我在[下面](#摘要).添加了一些摘要

A hash table consists of an array of 'buckets', each of which stores a key-value
pair. In order to locate the bucket where a key-value pair should be stored, the
key is passed through a hashing function. This function returns an integer which
is used as the pair's index in the array of buckets. When we want to retrieve a
key-value pair, we supply the key to the same hashing function, receive its
index, and use the index to find it in the array.
哈希表是由一系列的"桶"组成，每个桶都存储一组键值对。为了确定该键值对的桶应该放置在哪个位置，
我们可以通过将键值对的键作为参数传递到哈希函数中，然后此哈希函数生成一个整型索引值作为数组索引，
当需要检索数据时，也是同样的通过此哈希函数生成相应的索引来定位此键值对存放的位置。

Array indexing has algorithmic complexity `O(1)`, making hash tables fast at
storing and retrieving data.
由于数组的复杂度为 `O(1)`，使得哈希表能够快速的存储和检索数据

Our hash table will map string keys to string values, but the principals
given here are applicable to hash tables which map arbitrary key types to
arbitrary value types. Only ASCII strings will be supported, as supporting
unicode is non-trivial and out of scope of this tutorial.
以下将要实现的哈希表仅仅是存储字符类型的键值对， 其实原则上应该是实现任意类型的键值对，
但由于支持 unicode 并不简单而且超出了本教程的范围，所以本教程只支持 ASCII 字符串。

## API

Associative arrays are a collection of unordered key-value pairs. Duplicate keys
are not permitted. The following operations are supported:
关联数组是无序键值对的集合，故重复的键是无效的，且支持以下的操作：

- `search(a, k)`: 数组 `a` 中通过键 `k` 返回值 `v`，如果该键对应的值不存在，则返回 NULL
- `insert(a, k, v)`: 在数组 `a` 中存储键值对 `k:v`
- `delete(a, k)`: 通过键 `k` 删除数组 `a` 中对应的键值对，若键不存在，则不做任何操作

## 起始

To set up C on your computer, please consult [Daniel Holden's](@orangeduck)
guide in the [Build Your Own
Lisp](http://www.buildyourownlisp.com/chapter2_installation) book.  Build Your
Own Lisp is a great book, and I recommend working through it.
由于本教程是由 C 编写的，如果你还不清楚 C，可以参考 [Daniel Holden's](@orangeduck) 编写的
《[Build Your Own Lisp](http://www.buildyourownlisp.com/chapter2_installation)》，
这是一本不错的书籍，如果可以的话，我建议你读一读

## 代码结构

Code should be laid out in the following directory structure.
代码结构由以下目录和文件组成

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
`src` 文件夹里放置我们的代码，`build` 文件夹放置编译后的二进制文件

## 摘要

There are lots of names which are used interchangeably. In this article, we'll
use the following:
很多名词都有很多种不同的叫法，在本文中，我们统一用以下命名：

- Associative array: an abstract data structure which implements the
  [API](#api) described above. Also called a map, symbol table or
  dictionary.
- 关联数组： 实现以上 [API](#api) 的一种抽象的数据结构。也称为映射，符号表，字典

- Hash table: a fast implementation of the associative array API which makes
  use of a hash function. Also called a hash map, map, hash or
  dictionary.
- 哈希表： 通过散列函数实现的快速存储与检索的关联数组。也称为哈希映射，映射，哈希或字典。

Associative arrays can be implemented with many different underlying data
structures. A (non-performant) one can be implemented by simply storing items in
an array, and iterating through the array when searching. Associative arrays and
hash tables are often confused because associative arrays are so often
implemented as hash tables.

Next section: [Hash table structure](/02-hash-table)
[Table of contents](https://github.com/jamesroutley/write-a-hash-table#contents)
