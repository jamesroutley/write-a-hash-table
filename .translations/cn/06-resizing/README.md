# 调整哈希表长度

到目前为止，我们的哈希表长度都是固定为 `53` ,但随着越来越多的元素被添加进来，哈希表在有限的空间内将会被塞满，这可能会导致两个问题：

1. 哈希表的性能会随着高冲突率而下降
2. 哈希表只能存储固定长度的元素，无法添加更多的元素

如何解决以上问题？很简单，当哈希表即将要满的时候，增加哈希表的长度就可以了。
但需要制定策略：什么时候应该扩大？什么时候应该减小？
在上一节的 `count` 属性的统计就发挥了重要的作用，我们可以通过该属性与 `size` 属性来计算当前哈希表的存储容量百分比，并保存在 `load` 变量中，当满足以下条件时进行调整：

- 当 load > 0.7，增加哈希表的长度
- 当 load < 0.1，减小哈希表的长度

我们可以通过创建一个新的哈希表，其长度为当前哈希表的一半或两倍，并将当前哈希表未被删除的数据迁移到新的哈希表

新的哈希表长度为旧哈希表长度的一半或者两倍的素数，但找到新的长度并不是一件简单的事情，为此，需要设置一个初始值，当需要增加哈希表长度的时候，只需在初始值的基础上找到下一个素数即可。而当需要减小长度的时候，将旧哈希表的长度减半，然后基于这个数值找到下一个素数

哈希表的初始长度设置为 50

我们将用比较粗暴的方法去查找下一个素数，但事实上，此方法并不会耗费过多的时间与性能，因为我们需要检查的数量其实是非常少的，所需的时间当然比遍历哈希表每个元素都要少

首先，我们把素数的相关方法保存在文件 `prime.h` 和 `prime.c`

```c
// prime.h
int is_prime(const int x);
int next_prime(int x);
```

```c
// prime.c

#include <math.h>

#include "prime.h"


/*
 * 判断 x 是否素数
 *
 * 返回值:
 *   1  - 素数
 *   0  - 不是素数
 *   -1 - 无效的输入 (i.e. x < 2)
 */
int is_prime(const int x) {
    if (x < 2) { return -1; }
    if (x < 4) { return 1; }
    if ((x % 2) == 0) { return 0; }
    for (int i = 3; i <= floor(sqrt((double) x)); i += 2) {
        if ((x % i) == 0) {
            return 0;
        }
    }
    return 1;
}


/*
 * 返回 x 基础上的下一个素数
 */
int next_prime(int x) {
    while (is_prime(x) != 1) {
        x++;
    }
    return x;
}
```

下一步，需要更新 `ht_new` 函数以便可以根据传入的参数来生成指定长度的哈希表，
所以，需要新增一个函数 `ht_new_sized`，然后把我们之前的 `ht_new` 函数重命名为 `ht_new_sized` 并加上参数

```c
// hash_table.c
static ht_hash_table* ht_new_sized(const int base_size) {
    ht_hash_table* ht = xmalloc(sizeof(ht_hash_table));
    ht->base_size = base_size;

    ht->size = next_prime(ht->base_size);

    ht->count = 0;
    ht->items = xcalloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}


ht_hash_table* ht_new() {
    return ht_new_sized(HT_INITIAL_BASE_SIZE);
}
```

到目前为止，我们已经完成了可以根据不同的参数创建不同长度的哈希表的函数。

下面，我们在这个函数的基础上编写调整哈希表长度的函数。

首先，需要保证哈希表长度不能低于预设的最小值，然后根据这个值，创建一个新的哈希表。

接着，遍历旧的哈希表，把所有结果不为 `NULL` 以及没有被删除的元素都迁移到新的哈希表上，
当一切工作已经完成后，要记得释放旧的哈希表的内存，以防内存泄漏

```c
// hash_table.c
static void ht_resize(ht_hash_table* ht, const int base_size) {
    if (base_size < HT_INITIAL_BASE_SIZE) {
        return;
    }
    ht_hash_table* new_ht = ht_new_sized(base_size);
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    // To delete new_ht, we give it ht's size and items 
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_del_hash_table(new_ht);
}
```

为了便于调整与调用，下面简单的定义了增大哈希表以及减小哈希表的两个方法

```c
// hash_table.c
static void ht_resize_up(ht_hash_table* ht) {
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}


static void ht_resize_down(ht_hash_table* ht) {
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}
```

在插入以及删除的时候需要触发哈希表长度的检查，通过当前存储的容量百分比，我们可以很轻易的判断出，当容量超过 70% 的时候，需要增加哈希表长度，
当使用容量小于 10% 的时候，需要减小哈希表长度

```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    const int load = ht->count * 100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }
    // ...
}


void ht_delete(ht_hash_table* ht, const char* key) {
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }
    // ...
}
```

下一节: [附录](../07-appendix)
[目录](/.translations/cn/README.md#目录)
