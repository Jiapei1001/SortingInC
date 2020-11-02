#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chained_ht.h"

// Create Node
Node *CreateNode(char *key, char *value) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->next = NULL;
    node->key = key;
    node->val = value;
    return node;
}

// Create Hashtable
Hashtable *CreateHashtable(int num_buckets) {
    Hashtable *ht = (Hashtable *) malloc(sizeof(Hashtable));
    ht->buckets = (Node **) malloc(sizeof(Node *) * num_buckets);
    int i;
    for (i = 0; i < num_buckets; i++) {
        ht->buckets[i] = NULL;
    }
    ht->num_buckets = num_buckets;
    ht->num_elements = 0;
    return ht;
}

// Destroy Node
void DestroyNode(Node *node) {
    free(node);
}

// Destroy the linked node within one hashtable bucket
void DestroyList(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        DestroyNode(head);
        head = next;
    }
}

// Loop through the hashtable and destroy the nodes
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

// Load factor
double GetLoadFactor(Hashtable *ht) {
    return ((double) ht->num_elements) / ht->num_buckets;
}

// Print hashtable
void PrintHashtable(Hashtable *ht) {
    printf("Num elems: %d; Alpha: %.2f\n", ht->num_elements, GetLoadFactor(ht));
    int i;
    for (i = 0; i < ht->num_buckets; i++) {
        printf("%d: ", i);
        Node *node = ht->buckets[i];
        while (node != NULL) {
            printf("[%s:%s] ", node->key, node->val);
            node = node->next;
        }
        printf("\n");
    }
    printf("\n");
}

// Get which bucket index in the hashtable to put the new node
// ASCII number % number of buckets
int HashString(char *key, int buckets) {
    int len = strlen(key);
    int i;
    int acc = 0;
    for (i = 0; i < len; i++) {
        acc += key[i];
    }
    return acc % buckets;
}

// Insert Node
void Insert(Hashtable *ht, char *key, char *val) {
    // bucket index
    int index = HashString(key, ht->num_buckets);

    Node *new_node = CreateNode(key, val);

    // check if the bucket is occupied
    if (ht->buckets[index] != NULL) {
        // if occupied and the key is the same
        // assign new node's next to the current linked node

        // when the key doesn't match
        // loop through the buckets
        // to find the next available bucket with NULL inside
        if (strcmp(ht->buckets[index]->key, new_node->key) == 0) {
            new_node->next = ht->buckets[index];
        } else {
            while ((ht->buckets[index] != NULL) && (index < BUCKETS_NUM - 1)) {
                index++;
            }
            while ((ht->buckets[index] != NULL) && (index > 0)) {
                index--;
            }
        }
    }

    // increase the number of elements in the hashtable
    // assign the current bucket to the linked node
    ht->num_elements++;
    ht->buckets[index] = new_node;
}

// find a specific key
char *Get(Hashtable *ht, char *key) {
    int index = HashString(key, ht->num_buckets);

    Node *node = ht->buckets[index];
    if (node == NULL)
        return NULL;
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->val;
        }
        node = node->next;
    }
    return NULL;
}

// resize hashtable
Hashtable *Resize(Hashtable *ht) {
    Hashtable *new_ht = CreateHashtable(ht->num_buckets * 2);

    int i;

    for (i = 0; i < ht->num_buckets; i++) {
        Node *node = ht->buckets[i];
        while (node != NULL) {
            Node *old_next_node = node->next;
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

// sort the word
char *SortLetter(char *word) {
    char *string = word;
    char temp;
    int i, j;
    int n = strlen(string);

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (string[i] >= string[j]) {
                temp = string[i];
                string[i] = string[j];
                string[j] = temp;
            }
        }
    }
    return string;
}

// read the words file
void ReadFile(Hashtable *ht) {
    FILE *fp = fopen("words.txt", "r");
    char line[STRING_LEN];

    if (fp == NULL)
        exit(EXIT_FAILURE);

    while (fgets(line, sizeof(line), fp)) {
        // remove new line at the end
        strtok(line, "\n");

        // malloc the new key and new val
        // copy string
        // as pointers, they will be freed when destroying the hashtable
        char *new_key = (char *) malloc(sizeof(char) * STRING_LEN);
        char *new_val = (char *) malloc(sizeof(char) * STRING_LEN);
        strcpy(new_key, line);
        strcpy(new_val, line);

        // calling to insert the new key and new val to the hashtable
        new_key = SortLetter(new_key);
        Insert(ht, new_key, new_val);
    }

    fclose(fp);
}

// move results to a new hashtable
void MoveHashtable(Hashtable *old_ht, Hashtable *new_ht) {
    // Delete all nodes
    int i;
    int j = 0;
    for (i = 0; i < old_ht->num_buckets; i++) {
        if ((old_ht->buckets[i] != NULL) && (old_ht->buckets[i]->next != NULL)) {
            new_ht->buckets[j] = old_ht->buckets[i];
            new_ht->num_elements++;
            j++;
        }
    }
}