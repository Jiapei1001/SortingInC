#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "a6.h"
#include "hashtable.c"

// Create graph
Graph *CreateGraph() {
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    graph->num_nodes = 0;
    graph->total_city_num = 0;
    graph->visited_city_num = 0;
    return graph;
}

// Create node, with name, it neighbor as ListItem,
// foundBy to track the closest path,
// and visited mark to mark if the city node is visited.
Node *CreateNode(char *data) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->neighbor = NULL;
    node->foundBy = NULL;
    node->visited = 0;
    return node;
}

// Represent the all the city nodes that have
// edge direct to the front city node.
// Implemented as linked structure.
ListItem *CreateList() {
    ListItem *item = (ListItem *) malloc(sizeof(ListItem));
    item->payload = NULL;
    item->next = NULL;
    item->edgeDist = 0;
    return item;
}

void AddNode(Graph *graph, Node *node) {
    graph->nodes[graph->num_nodes++] = node;
}

void AddEdge(Node *src, Node *dest, double distance) {
    ListItem *li = CreateList();
    li->payload = dest;
    li->next = src->neighbor;
    src->neighbor = li;
    li->edgeDist = distance;
}


void PrintGraph(Graph *graph, Hashtable *ht) {
    int i;
    for (i = 0; i < graph->num_nodes; i++) {
        printf("NODE: %s: ", graph->nodes[i]->data);

        ListItem *li = graph->nodes[i]->neighbor;
        while (li != NULL) {
            printf("-> %s ", li->payload->data);
            printf("(edge: %.2lf) ", li->edgeDist);
            HashNode *tempHN = GetNode(ht, li->payload->data);
            printf("(count: %.2lf) ", tempHN->val);
            li = li->next;
        }
        printf("\n");
    }
}


int readFile(Graph *graph, Hashtable *ht) {
    char str[STRING_ARRAY_SIZE];
    char *array[3];
    char buf[STRING_ARRAY_SIZE];

    FILE *fp;
    fp = fopen("miles_edges.txt", "r");

    while (fgets(str, STRING_ARRAY_SIZE, fp)) {
        // split each line into three tokens
        // assign them to the array
        strcpy(buf, str);
        char *token;
        token = strtok(str, " \n");
        int j = 0;
        while (token != NULL) {
            array[j++] = token;
            token = strtok(NULL, " \n");
        }

        Node *source;
        Node *destination;

        char *copyString = (char *) malloc(sizeof(char) * STRING_ARRAY_SIZE);
        strcpy(copyString, array[0]);

        // Check if the first city in the hashtable
        // if it is, create node, insert into both the graph and the hashtable
        // if not, free the malloc'd string
        if (Get(ht, copyString) == -1) {
            source = CreateNode(copyString);
            InsertHashNode(ht, copyString, DIS_MAX, source);
            AddNode(graph, source);
            graph->total_city_num++;
        } else {
            free(copyString);
        }

        // Check if the second city in the hashtable
        // if it is, create node, insert into both the graph and the hashtable
        // if not, free the malloc'd string
        char *copyString2 = (char *) malloc(sizeof(char) * STRING_ARRAY_SIZE);
        strcpy(copyString2, array[1]);

        if (Get(ht, copyString2) == -1) {
            destination = CreateNode(copyString2);
            InsertHashNode(ht, copyString2, DIS_MAX, destination);
            AddNode(graph, destination);
            graph->total_city_num++;
        } else {
            free(copyString2);
        }

        double distance;
        sscanf(array[2], "%lf", &distance);

        HashNode *sourceHashNode = GetNode(ht, array[0]);
        HashNode *destinationHashNode = GetNode(ht, array[1]);

        // Add edge
        AddEdge(sourceHashNode->currNode,
                destinationHashNode->currNode, distance);
    }
    fclose(fp);
    return 0;
}

void Destroy(Hashtable *ht, Graph *graph) {
    DestroyHashtable(ht, 1);
    int i;
    for (i = 0; i < graph->num_nodes; i++) {
        ListItem *li = graph->nodes[i]->neighbor;
        while (li != NULL) {
            ListItem *nextListItem = li->next;
            free(li);
            li = nextListItem;
        }
        free(graph->nodes[i]->data);
        free(graph->nodes[i]);
    }
    free(graph);
}

// Loop through all the non-visited front city nodes in the graph
// array as adjacency list, to find the city node with the current
// minimum value.
int *FindMinNode(Graph *graph, Hashtable *ht, int *min_index) {
    int i;
    HashNode *tempHashNode;

    for (i = 0; i < graph->num_nodes; i++) {
        tempHashNode = GetNode(ht, graph->nodes[i]->data);
        if (tempHashNode->visited != 1) {
            *min_index = i;
            return min_index;
        }
    }
    return min_index;
}

// When the city node with the current minimum value is found.
// Implement Djikstra's Algorithm to swap the value
// for relaxation of the city node.
void UpdateListItemValue(Graph *graph, Hashtable *ht,
        int min_index, HashNode **parentArray, int *k) {
    Node *tempNode = graph->nodes[min_index];
    HashNode *tempHashNode = GetNode(ht, tempNode->data);

    if (tempNode->neighbor == NULL) {
        tempHashNode->visited = 1;
        graph->visited_city_num++;
        parentArray[*k] = tempHashNode;
        (*k)++;
        return;
    }

    ListItem *tempListItem = tempNode->neighbor;
    HashNode *tempHN2;
    while (tempListItem != NULL) {
        // Front Node value + current edge value
        double D_Combine = tempHashNode->val + tempListItem->edgeDist;
        // Check the current List Item Node's value
        tempHN2 = GetNode(ht, tempListItem->payload->data);
        double D_Target = tempHN2->val;
        // If the combined value is less than
        // the current List Item Node's value, swap them
        if (D_Combine < D_Target) {
            tempHN2->val = D_Combine;
            tempListItem->payload->foundBy = tempNode;
        }
        tempListItem = tempListItem->next;
    }

    tempHashNode->visited = 1;
    graph->visited_city_num++;
    printf("key: %s\n", tempHashNode->key);
    printf("value: %.2lf\n", tempHashNode->val);
    printf("k: %d\n", *k);
    parentArray[*k] = tempHashNode;
    (*k)++;
}

// Set the source city node's value as 0 for start the
// looping process.
void SetStart(Graph *graph, Hashtable *ht, char *start) {
    int i;
    Node *tempNode;
    HashNode *tempHashNode;
    for (i = 0; i < graph->num_nodes; i++) {
        if (strcmp(graph->nodes[i]->data, start) == 0) {
            tempNode = graph->nodes[i];
            tempHashNode = GetNode(ht, start);
            tempHashNode->val = 0;
        }
    }
}

// Swap the front node array in the graph.
void Swap(Node **xp, Node **yp) {
    Node *temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Sort the front node array in the graph
// to find the city node with the current
// minimum value.
void Sort(Hashtable *ht, Node *arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            HashNode *temp1 = GetNode(ht, arr[j]->data);
            HashNode *temp2 = GetNode(ht, arr[j + 1]->data);
            if (temp1->val > temp2->val) {
                Swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Running the code
void RunShortestDistance(Graph *graph, Hashtable *ht, char *start, char *end) {
    SetStart(graph, ht, start);

    // parentArray to get all the visited city nodes in sequence order
    // (distance to the source city node)
    HashNode **parentArray;
    parentArray = (HashNode **) malloc(sizeof(HashNode *) * PARENT_ARRAY_SIZE);

    // k represent the index of the current parentArray.
    int *k;
    k = (int *) malloc(sizeof(int));
    *k = 0;

    // min_index represent the minimum index of the city node with the current lowest value.
    int *min_index;
    min_index = (int *) malloc(sizeof(int));
    *min_index = 0;

    int i;
    for (i = 0; i < graph->total_city_num; i++) {
        Sort(ht, graph->nodes, graph->num_nodes);
        min_index = FindMinNode(graph, ht, min_index);
        UpdateListItemValue(graph, ht, *min_index, parentArray, k);
    }


    // Check which index is the end city node located.
    for (i = 0; i < graph->visited_city_num; i++) {
        if (strcmp(parentArray[i]->key, end) == 0) {
            break;
        }
    }

    // Print result.
    printf("\n\n");
    Node *printNode = parentArray[i]->currNode;
    while (printNode->foundBy != NULL) {
        HashNode *currPrintHashNode = GetNode(ht, printNode->data);
        printf("%s:", currPrintHashNode->key);
        printf("%.2lf<--", currPrintHashNode->val);
        printNode = printNode->foundBy;
    }
    HashNode *currPrintHashNode = GetNode(ht, printNode->data);
    printf("%s:", currPrintHashNode->key);
    printf("%.2lf\n\n\n\n\n\n", currPrintHashNode->val);

    // free memory
    free(k);
    free(min_index);
    free(parentArray);
    Destroy(ht, graph);
}


int main() {
    char *start;
    char *end;
    char *start_new;
    char *end_new;

    Graph *graph = CreateGraph();
    Hashtable *ht = CreateHashtable(HASHTABLE_SIZE);

    readFile(graph, ht);


    /* For Seattle_WA to Boston_MA
     * or Minneapolis_MN to Ann Arbor_MI
     * Please run uncomment one or comment the other one */


//    start = (char*)malloc(sizeof(char) * 20);
//    end = (char*)malloc(sizeof(char) * 20);
//    strcpy(start, "Seattle_WA");
//    strcpy(end, "Boston_MA");
//    RunShortestDistance(graph, ht, start, end);
//    printf("\n\n");
//    free(start);
//    free(end);


    start_new = (char *) malloc(sizeof(char) * 20);
    end_new = (char *) malloc(sizeof(char) * 20);
    strcpy(start_new, "Minneapolis_MN");
    strcpy(end_new, "Ann_Arbor_MI");
    RunShortestDistance(graph, ht, start_new, end_new);
    printf("\n\n");
    free(start_new);
    free(end_new);
}
