## 哈希碰撞

上节提到的散列函数若通过输入无限的数据映射到有限数量的输出，必然会产生同样的索引值，所以也就导致了
存储桶的索引碰撞，所以我们需要有好的方案去处理这些冲突。

显然，已经有很多人遇到了这个问题，所以也有很多方案可以处理这些情况，对于其它处理碰撞的方法，就不在这里赘述，请查看[附录](../07-appendix)

在本文中我们将使用一种称为开放寻址和再哈希的技术来处理冲突。也就是说，在发生碰撞后，再哈希会使用两个哈希函数来计算 `i` 出现碰撞后的索引值

## 再哈希

在 `i` 发生碰撞后的索引值可由以下公式算出：

```
index = hash_a(string) + i * hash_b(string) % num_buckets
```

通过以上式子我们可以发现，如果没有发生任何碰撞，即 `i = 0`，所以哈希的索引值仅仅只是 `hash_a` 的结果。
如果碰撞发生了，即 i != 0，结果很明显会根据 `hash_b` 的返回结果进行变化

很显然，如果 `hash_b` 的返回结果为 0 将导致第二项的结果也为 0，哈希表会一遍又一遍的尝试插入到同一个位置，
那么我们的这项处理就毫无意义了，所以，我们可以通过在 `hash_b` 的结果后面加 1 来避免这样的情况。

```
index = (hash_a(string) + i * (hash_b(string) + 1)) % num_buckets
```

## 代码实现

```c
// hash_table.c
static int ht_get_hash(
    const char* s, const int num_buckets, const int attempt
) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}
```

下一节: [哈希表的函数](../05-methods)
[目录](/.translations/cn/README.md#contents)
