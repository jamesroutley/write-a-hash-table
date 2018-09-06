[<img src="/.translations/flags/gb.png">](/README.md) [<img src="/.translations/flags/fr.png">](/.translations/fr/README.md) [<img src="/.translations/flags/cn.png">](/.translations/zh-cn/README.md)

# 哈希表的实现（C）

[哈希表](https://en.wikipedia.org/wiki/Hash_table) 是一种最常用的数据结构。 由于哈希表的快速存储以及插入，搜索，删除的可扩展，使得其在计算机领域有着广泛的应用

在本篇教程中，我们将用 C 实现基于[开放寻址](https://en.wikipedia.org/wiki/Open_addressing)以及[再哈希](https://en.wikipedia.org/wiki/Double_hashing)的哈希表。
通过这篇教程，你可以知道：

- 基础数据结构是如何在底层工作的
- 深入了解到什么时候使用哈希表，而什么时候应避免使用哈希表以及为什么不能用
- 对 C 或许会有新的认知

C 非常适合用于编写哈希表，主要是因为：

- C 不需要引入任何东西就可以直接运行
- 属于底层语言，所以可以深入的了解到在机器层面上的程序是如何运作的

本教程是假设你已熟悉 C 的语法。由于代码本身相对简单，大多数问题都可以通过搜索引擎来解决。
如果你遇到其它问题，请打开 Github 的 [Issue](https://github.com/yigger/write-a-hash-table/issues) 进行提问

整个过程大概需要编写 200 行左右的代码，这大概会耗费你 1 ~ 2 个小时

## 目录

1. [介绍](./01-introduction)
2. [哈希表数据结构](./02-hash-table)
3. [哈希函数](./03-hashing)
4. [冲突处理](./04-collisions)
5. [哈希表的方法](./05-methods)
6. [调整哈希表大小](./06-resizing)
7. [附录： 处理哈希碰撞的方法与描述](./07-appendix)

## Credits

本教程是由 [James Routley](https://twitter.com/james_routley) 编写,博客地址：[routley.io](https://routley.io)。
