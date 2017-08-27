[<img src="/.translations/flags/gb.png">](/README.md) [<img src="/.translations/flags/fr.png">](/.translations/fr/README.md)

# Write a hash table in C

[Hash tables](https://en.wikipedia.org/wiki/Hash_table) are one of the most useful data structures. Their quick and scalable
insert, search and delete make them relevant to a large number of computer
science problems.

In this tutorial, we implement an [open-addressed](https://en.wikipedia.org/wiki/Open_addressing), [double-hashed](https://en.wikipedia.org/wiki/Double_hashing) hash table in
C. By working through this tutorial, you will gain:

- Understanding of how a fundamental data structure works under the hood
- Deeper knowledge of when to use hash tables, when not to use them, and how
  they can fail
- Exposure to new C code

C is a great language to write a hash table in because:

- The language doesn't come with one included
- It is a low-level language, so you get deeper exposure to how things work at a
  machine level

This tutorial assumes some familiarity with programming and C syntax. The code
itself is relatively straightforward, and most issues should be solvable with a
web search. If you run into further problems, please open a GitHub
[Issue](https://github.com/jamesroutley/write-a-hash-table/issues).

The full implementation is around 200 lines of code, and should take around an
hour or two to work through.

## Contents

1. [Introduction](/01-introduction)
2. [Hash table structure](/02-hash-table)
3. [Hash functions](/03-hashing)
4. [Handling collisions](/04-collisions)
5. [Hash table methods](/05-methods)
6. [Resizing tables](/06-resizing)
6. [Appendix: alternative collision handling](/07-appendix)

## Credits

This tutorial was written by [James Routley](https://twitter.com/james_routley),
who blogs at [routley.io](https://routley.io).
