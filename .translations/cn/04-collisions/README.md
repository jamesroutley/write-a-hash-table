## 哈希冲突

上节提到的哈希值函数存在`无限的输入数据映射到有限数量的输出数据`，则哈希值函数必然会生成同样的哈希值，所以也就导致了存储位置的索引冲突，所以需要一个方案来处理冲突后的元素

在本文中我们将使用一种称为开放寻址和再哈希的技术来处理这些冲突。换句话说，在发生冲突后，再哈希会通过 `i` 变量使用两次哈希值函数来计算冲突后的哈希值。当然，处理的方案不止一种，对于其它的方案，就不在这里赘述，请查看[附录](../07-appendix)

## 再哈希

在发生冲突后，哈希值可根据 `i` 由以下公式算出：

```
index = hash_a(string) + i * hash_b(string) % num_buckets
```

通过以上公式我们可以知道，如果没有发生任何冲突，即 `i = 0`，所以哈希值仅仅只是 `hash_a` 的返回值。如果冲突发生了，即 `i != 0`，结果很明显会根据 `hash_b` 的结果进行变化

显然，如果 `hash_b` 的返回结果为 `0`，公式第二项的结果也为 0，哈希表会一遍又一遍的将元素尝试插入到同一位置，那么我们的这项处理就毫无意义了，所以，需要在 `hash_b` 的返回结果后面 `+1` 来缓解这种的情况

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

下一节: [哈希表函数的实现](../05-methods)
[目录](/.translations/cn/README.md#目录)
