# 哈希表 Api

哈希表需要实现以下函数：

```c
// hash_table.h
void ht_insert(ht_hash_table* ht, const char* key, const char* value);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);
```

## 插入

为了让一个键值对能插入到哈希表中，我们需要调用哈希值函数来生成索引值，但索引值的对应位置可能已经被使用，也就是说发生了冲突，则通过递增 `i` 的值来重新生成索引，直至找到合适的位置存储新元素。
在插入了新元素后，我们同样需要将哈希表的 `count` 属性加一，这是为了便于[调整哈希表大小](../06-resizing)

```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    ht_item* item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL) {
        index = ht_get_hash(item->key, ht->size, i);
        cur_item = ht->items[index];
        i++;
    } 
    ht->items[index] = item;
    ht->count++;
}
```

## 查找

查找过程与插入过程类似，也是通过 `key` 来生成索引值，利用索引值寻找哈希表对应位置的元素，然后通过比较元素的 `key` 与参数 `key` 来确定当前元素是否我们需要要查找的元素。
如果两个 `key` 不相等，则说明 `key` 在插入过程中可能发生了冲突，需要继续通过 `ht_get_hash` 来生成索引值，接着重复上个过程，直至找到与参数 `key` 一致的元素。
如果在查询过程中，`index` 索引返回了 `NULL`，则代表当前索引值为空，即元素不存在，结果返回 `NULL`

```c
// hash_table.c
char* ht_search(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    } 
    return NULL;
}
```

## 删除

删除元素的操作比插入或查找都更为复杂。在查找删除元素的过程中可能会出现冲突，如果直接删除查询结果的话，就会破坏了查询、插入等操作，从而无法定位到发生冲突后的元素。
所以，为了解决这个问题，我们不能删除这个元素，取而代之的是把这个元素做个标记，即软删除。
（举个例子： `hello` 的索引是 `4`, `world` 的索引也是 `4`，通过冲突处理函数，`world` 重新分配到了索引为 10 的位置。
如果直接删除索引为 `4` 的位置，在查询 `world` 的过程中就会因为 `4` 的位置返回 `NULL`，从而结果也就为 `NULL`）

我们当然需要定义一个标记值，即 `ht_item HT_DELETED_ITEM = {NULL, NULL}`，然后，把需要删除的元素的指向替换成指向 `HT_DELETED_ITEM` 元素即可

```c
// hash_table.c
static ht_item HT_DELETED_ITEM = {NULL, NULL};


void ht_delete(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                ht_del_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    } 
    ht->count--;
}
```

在删除元素后，哈希表的 `count` 属性也需要减一

以上的操作会影响到本章开头编写的插入与查找函数，我们还需要稍微修改一下这两个函数

在查找的时候，我们将查询到的元素与 `HT_DELETED_ITEM` 进行比较，以此来判断该元素是否已经被删除，如果已经删除了，则跳过该元素，继续寻找下一个。
在插入过程中，如果新增元素的索引位置恰巧命中了已删除元素的位置，则直接把新元素覆盖为旧元素


```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    // ...
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) {
        // ...
    }
    // ...
}


char* ht_search(ht_hash_table* ht, const char* key) {
    // ...
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) { 
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        // ...
    }
    // ...
}
```

## 更新

当前实现的哈希表并不支持更新操作。因为当前结构不能存在两个同样的键，假如存在同样的键，那么在插入过程中必然会产生冲突，从而导致相同的键由于冲突存储在不同的索引值位置。而在查找函数过程中，通过键生成的索引值肯定是一样的，这样就导致了无法查找到后面插入进来的键值元素，将永远只命中第一个符合键的元素

为了解决这个问题，我们可以通过修改插入函数，把新的元素覆盖旧元素

```c
// hash_table.c
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {
    // ...
    while (cur_item != NULL) {
        if (cur_item != &HT_DELETED_ITEM) {
            if (strcmp(cur_item->key, key) == 0) {
                ht_del_item(cur_item);
                ht->items[index] = item;
                return;
            }
        }
        // ...
    } 
    // ...
}
```

下一节: [调整哈希表长度](../06-resizing)
[目录](/.translations/cn/README.md#目录)
