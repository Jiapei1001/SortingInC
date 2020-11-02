//
// Created by Jiapei Li on 8/7/20.
//

#ifndef HW05_HASHTABLES_CHAINED_HT_H
#define HW05_HASHTABLES_CHAINED_HT_H


#define BUCKETS_NUM 436000
#define FINAL_BUCKETS_NUM 1200
#define STRING_LEN 66

typedef struct Node {
    char *val;
    char *key;
    struct Node *next;
} Node;

typedef struct {
    Node **buckets;
    int num_elements;
    int num_buckets;
} Hashtable;


Hashtable *CreateHashtable(int num_buckets);

void DestroyNode(Node *node);

void DestroyList(Node *head);

void DestroyHashtable(Hashtable *ht, int destroyNodes);

double GetLoadFactor(Hashtable *ht);

void PrintHashtable(Hashtable *ht);

int HashString(char *key, int buckets);

void Insert(Hashtable *ht, char *key, char *val);

char *Get(Hashtable *ht, char *key);

Hashtable *Resize(Hashtable *ht);

char *SortLetter(char *word);

void ReadFile(Hashtable *ht);

void MoveHashtable(Hashtable *old_ht, Hashtable *new_ht);

#endif  // HW05_HASHTABLES_CHAINED_HT_H
