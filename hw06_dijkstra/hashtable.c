#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "a6.h"


HashNode *CreateHashNode(char *key, double value) {
    HashNode *hashNode = (HashNode *) malloc(sizeof(HashNode));
    hashNode->next = NULL;
    hashNode->key = key;
    hashNode->val = value;
    hashNode->visited = 0;
    hashNode->currNode = NULL;
    return hashNode;
}

void DestroyHashNode(HashNode *hashNode) {
    free(hashNode->key);
    free(hashNode->currNode);
    free(hashNode);
}

void DestroyList(HashNode *head) {
    while (head != NULL) {
        HashNode *next = head->next;
        DestroyHashNode(head);
        head = next;
    }
}

Hashtable *CreateHashtable(int num_buckets) {
    Hashtable *ht = (Hashtable *) malloc(sizeof(Hashtable));
    ht->buckets = (HashNode **) malloc(sizeof(HashNode *) * num_buckets);
    int i;
    for (i = 0; i < num_buckets; i++) {
        ht->buckets[i] = NULL;
    }
    ht->num_buckets = num_buckets;
    ht->num_elements = 0;
    return ht;
}

void DestroyHashtable(Hashtable *ht, int destroyNodes) {
    // Delete all nodes
    int i;
    if (destroyNodes == 1) {
        for (i = 0; i < ht->num_buckets; i++) {
            DestroyList(ht->buckets[i]);
        }
    }
    free(ht->buckets);
    free(ht);
}


int HashString(char *key, int buckets) {
    int len = strlen(key);
    int i;
    int acc = 0;
    for (i = 0; i < len; i++) {
        acc += key[i];
    }
    int hashIndex = acc % buckets;
    return hashIndex;
}

void InsertHashNode(Hashtable *ht, char *key, double val, Node *curr) {
    int index = HashString(key, ht->num_buckets);

    HashNode *new_node = CreateHashNode(key, val);
    new_node->currNode = curr;

    if (ht->buckets[index] != NULL) {
        new_node->next = ht->buckets[index];
    }
    ht->buckets[index] = new_node;

    ht->num_elements++;
}

double Get(Hashtable *ht, char *key) {
    int index = HashString(key, ht->num_buckets);

    HashNode *hashNode = ht->buckets[index];
    if (hashNode == NULL)
        return -1;
    while (hashNode != NULL) {
        if (strcmp(hashNode->key, key) == 0) {
            return hashNode->val;
        }
        hashNode = hashNode->next;
    }
    return -1;
}

HashNode *GetNode(Hashtable *ht, char *copy_key) {
    int index = HashString(copy_key, ht->num_buckets);

    HashNode *hashNode = ht->buckets[index];

    char *key = (char *) malloc(sizeof(char) * GET_NODE_CHAR_SIZE);
    strcpy(key, copy_key);

    if (hashNode == NULL) {
        free(key);
        return NULL;
    }

    while (hashNode != NULL) {
        if (strcmp(hashNode->key, key) == 0) {
            free(key);
            return hashNode;
        }
        hashNode = hashNode->next;
    }

    free(key);
    return NULL;
}


Hashtable *Resize(Hashtable *ht) {
    Hashtable *new_ht = CreateHashtable(ht->num_buckets * 2);

    int i;

    for (i = 0; i < ht->num_buckets; i++) {
        HashNode *node = ht->buckets[i];
        while (node != NULL) {
            HashNode *old_next_node = node->next;
            int new_bucket = HashString(node->key, new_ht->num_buckets);
            node->next = new_ht->buckets[new_bucket];
            new_ht->buckets[new_bucket] = node;
            new_ht->num_elements++;
            node = old_next_node;
        }
    }

    DestroyHashtable(ht, 0);

    return new_ht;
}


void PrintHashtable(Hashtable *ht) {
    int i;
    for (i = 0; i < ht->num_buckets; i++) {
        printf("%d: ", i);
        HashNode *node = ht->buckets[i];
        while (node != NULL) {
            printf("[%s:%.2f] ", node->key, node->val);
            node = node->next;
        }
        printf("\n");
    }
    printf("\n");
}


