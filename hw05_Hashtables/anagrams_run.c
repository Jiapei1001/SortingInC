//
// Created by Jiapei Li on 8/7/20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chained_ht.h"

int main() {
    Hashtable *ht = CreateHashtable(BUCKETS_NUM);

    ReadFile(ht);

    Hashtable *ht_new = CreateHashtable(FINAL_BUCKETS_NUM);

    // moving results to a new hashtable
    // starting from index 0
    MoveHashtable(ht, ht_new);

    PrintHashtable(ht_new);

    DestroyHashtable(ht, 1);
    DestroyHashtable(ht_new, 1);
}
