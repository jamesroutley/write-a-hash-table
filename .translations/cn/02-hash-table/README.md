# 哈希表结构

哈希的元素存储在以下的 `ht_item` 结构， `key` 代表元素的键， `value` 代表元素的值，且均为字符类型：

```c
// hash_table.h
typedef struct {
    char* key;
    char* value;
} ht_item;
```

下面是哈希表的结构， `items` 是指向  `ht_item` 结构的指针数组，`size` 则存储哈希表的大小，即哈希的长度
`count` 表示当前哈希表当前已存储了多少个键值对：

```c
// hash_table.h
typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;
```

## 哈希的初始化和删除

首先，我们需要定义一个初始化 `ht_item` 结构的方法，并分配一块大小为 `ht_item` 的内存，
并存储字符串 `k` 和 `v` 的副本，该方法的开头需要标记为 `static` 静态方法，是为了该方法
只供在本文件内调用

```c
// hash_table.c
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static ht_item* ht_new_item(const char* k, const char* v) {
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}
```

`ht_new` 方法用于初始化一个哈希表结构。 `size` 定义了该结构能存储多少元素，当前暂且
只分配 53 的存储大小，在后面的章节中，我们会提到 [resizing](../06-resizing) 来动态调整哈希表的
存储大小。然后我们使用 `calloc` 方法来初始化元素数组，这里用 `calloc` 而不用 `malloc` 是因为
`calloc` 所分配的内存空间的每一位都会初始化为 `NULL`，而 `NULL` 则表示该位置未存储元素

```c
// hash_table.c
ht_hash_table* ht_new() {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));

    ht->size = 53;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}
```

当然，为了防止[内存泄漏](https://en.wikipedia.org/wiki/Memory_leak)，我们需要定义 `ht_item`
和 `ht_hash_tables` 的删除方法来进行内存的回收

```c
// hash_table.c
static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}


void ht_del_hash_table(ht_hash_table* ht) {
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL) {
            ht_del_item(item);
        }
    }
    free(ht->items);
    free(ht);
}
```

在本章节中，我们定义了如何初始化或删除一个哈希表，虽然实现的功能并不多，但为了保证后面程序的正常运行，
需要保证编写的方法不会报错，故可以照着以下的示例代码进行调试

```c
// main.c
#include "hash_table.h"

int main() {
    ht_hash_table* ht = ht_new();
    ht_del_hash_table(ht);
}
```

下一节: [哈希函数](../03-hashing)
[目录](/.translations/cn/README.md#contents)
