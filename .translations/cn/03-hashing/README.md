# 哈希函数

在这一节中，将编写用于计算索引值的哈希函数。

哈希函数应该具有以下特征：

- 输入一个字符串，返回一个 `0` - `m` 的整型数字， `m` 必须不大于哈希的长度，即上一节中 `ht_hash_table` 的 `size`

- 计算的索引值必须均匀分布，如果计算的索引值分布不均匀，会导致大多数键都落在同一索引，从而在哈希表插入过程中将会产生大量[碰撞](#Pathological data)，大大的降低性能

## 算法

我们将使用泛型字符串散列函数，下面是该算法的伪代码。

```
function hash(string, a, num_buckets):
    hash = 0
    string_len = length(string)
    for i = 0, 1, ..., string_len:
        hash += (a ** (string_len - (i+1))) * char_code(string[i])
    hash = hash % num_buckets
    return hash
```

从上面的函数可以看出，要生成一个 hash 值，我们需要做以下两步：

1. 把字符串转换为整型
2. 因转换的整型数字可能远远大于哈希表的长度，所以我们需要通过 `mod` 取余数来保证生成的哈希函数不大于哈希表长度 `m`

变量 `a` 应当是一个大于字母表大小的素数，因为我们在计算字符串的散列值，而字符串的 ASCII 大小为 128，
所以 `a` 的大小应当是大于 128 的素数

`char_code` 是将单字符转换为整数的方法

根据上面的描述，可以举个例子计算一下：

```
hash("cat", 151, 53)

hash = (151**2 * 99 + 151**1 * 97 + 151**0 * 116) % 53
hash = (2257299 + 14647 + 116) % 53
hash = (2272062) % 53
hash = 5
```

通过改变变量 `a` 的值，我们可以得到不同的计算结果

```
hash("cat", 163, 53) = 3
```

## 代码实现

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

## 病理数据

理想的散列函数无论输入什么键，其返回值都是均匀分布的。然而，对于任意的哈希函数，都不会生成每个键唯一的哈希值，
肯定会出现一些 `奇怪` 的键，这些键生成的哈希值往往会占用其它键的哈希值。

一系列的病理数据集合意味着没有完美的哈希函数可以生成唯一的哈希值。所以最好的办法就是
创建一个函数来处理这些可能会出现的数据

Pathological inputs also poses a security issue. If a hash table is fed a set of
colliding keys by some malicious user, then searches for those keys will take
much longer (`O(n)`) than normal (`O(1)`). This can be used as a denial of
service attack against systems which are underpinned by hash tables, such as DNS
and certain web services.


Next section: [处理哈希碰撞](../04-collisions)
[目录](/.translations/cn/README.md#contents)
