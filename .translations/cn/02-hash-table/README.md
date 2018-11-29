# 哈希表结构

哈希表的元素由以下结构 `ht_item` 组成，键：`key`，值：`value`，且均为字符类型：

```c
// hash_table.h
typedef struct {
    char* key;
    char* value;
} ht_item;
```

哈希表结构定义， `items` 属性是指向  `ht_item` 结构的指针数组，`size` 则存储哈希表的总长度，`count` 属性代表当前哈希表的长度使用情况，即当前已用元素的数量：

```c
// hash_table.h
typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;
```

## 哈希结构的初始化和删除方法

以下是实现哈希表的初始化方法，首先需要初始化 `ht_item` 的结构体，然后将键值对参数存储到结构体对应的属性，最后，将该方法标记为 `static` 静态方法，以防外部文件调用

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

`ht_new` 方法用于初始化哈希表结构。 `size` 属性定义了哈希表的长度，当前暂且只分配 53 的长度，在后面的章节中，我们将会通过 [调整哈希表大小](../06-resizing) 来动态调整哈希表的存储大小。

使用 `calloc` 初始化 `items` 属性，这里用 `calloc` 而不用 `malloc` 是因为 `calloc` 所分配的内存空间的每一位元素都会初始化为 `NULL`，`NULL` 代表哈希表的此位置可用

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

为了防止[内存泄漏](https://en.wikipedia.org/wiki/Memory_leak)，我们需要定义 `ht_item` 和 `ht_hash_tables` 结构的删除方法来进行内存的回收

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

在本章节中，我们定义了如何初始化或删除一个哈希表，虽然实现的功能并不多，但为了保证后面程序能正常运行，需要进行简单的测试

```c
// main.c
#include "hash_table.h"

int main() {
    ht_hash_table* ht = ht_new();
    ht_del_hash_table(ht);
}
```

下一节: [哈希函数](../03-hashing)
[目录](/.translations/cn/README.md#目录)
