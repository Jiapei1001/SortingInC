//
// Created by Jiapei Li on 8/13/20.
//

#ifndef HW06_DIJKSTRA_DEFINITION_H
#define HW06_DIJKSTRA_DEFINITION_H


#define MAX_NUM_NODES 1500
#define STRING_ARRAY_SIZE 160
#define DIS_MAX 10000
#define HASHTABLE_SIZE 1000
#define PARENT_ARRAY_SIZE 1000
#define GET_NODE_CHAR_SIZE 30


typedef struct listItem ListItem;
typedef struct node Node;

struct listItem {
    Node *payload;
    ListItem *next;
    double edgeDist;
};

struct node {
    char *data;
    ListItem *neighbor;
    Node* foundBy;
    int visited;
};

typedef struct graph {
    Node *nodes[MAX_NUM_NODES];
    int num_nodes;
    int total_city_num;
    int visited_city_num;
} Graph;


typedef struct HashNode {
    double val;
    char *key;
    int visited;
    Node* currNode;
    struct HashNode *next;
} HashNode;


typedef struct {
    HashNode **buckets;
    int num_elements;
    int num_buckets;
} Hashtable;




#endif  // HW06_DIJKSTRA_DEFINITION_H
