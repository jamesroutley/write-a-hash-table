// main.c
#include "hash_table.h"
#include "stdio.h"
#include "string.h"

int perm(const char *, int, char *, char *, int);

// rm -rf ./build/waht && gcc src/hash_table.c src/main.c -o build/waht -Wall && chmod +x ./build/waht && ./build/waht
int main() {
    // ht_hash_table* ht = ht_new();
    // ht_del_hash_table(ht);

    // char * chaine = "cat";
    // int bucket_size = 53;
    // int prime_number_alphabet = 163;
    // int hash_result = ht_hash(chaine, prime_number_alphabet, bucket_size);
    // printf("ht_hash(%s, %i, %i) = %i\n", chaine, prime_number_alphabet, bucket_size, hash_result);

    long length = 1047834;
    char* array[length];
    // for(int i = 0; i < length; i++)
    // {
    //   array[i] = "test";
    //   printf("array[%i]=%s\n", i, array[i]);
    // }

    const char* alphabet = "abc"; //defghijklmnopqrstuvwxyz";

    for( char* ptr = alphabet; *ptr!='\0'; ++ptr) {
        int len = strlen(ptr);
        char dest[len], destbits[len];

        memset(destbits, 0, sizeof destbits);
        int total = perm(ptr, len, dest, destbits, 0);

        printf("src(%s)\n", ptr);
    }


    // const char *src = "abc";
    // int len = strlen(src);
    // char dest[len], destbits[len];

    // memset(destbits, 0, sizeof destbits);
    // int total = perm(src, len, dest, destbits, 0);

    // printf("%d combinations\n", total);

    return 0;
}

int perm(const char *src, int len, char *dest, char *destbits, int n) {
    if (n == len) {
        printf("%.*s\n", len, dest);
        return 1;
    } else {
        int count = 0;
        for (int i = 0; i < len; i++) {
            if (destbits[i] == 0) {
                destbits[i] = 1;
                dest[n] = src[i];
                count += perm(src, len, dest, destbits, n + 1);
                destbits[i] = 0;
            }
        }
        return count;
    }
}
