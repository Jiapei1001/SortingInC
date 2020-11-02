//
// Created by Jiapei Li on 8/7/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chained_ht.h"


#define assert(EXPRESSION) (                            \
    (EXPRESSION) ?                                      \
    _assert_pass(#EXPRESSION, __FILE__, __LINE__) :     \
    _assert_fail(#EXPRESSION, __FILE__, __LINE__))

void _assert_fail(const char *expression,
                  const char *file,
                  int line) {
    fprintf(stderr,
            "\n**** Assertion '%s' FAILED, file '%s' line '%d' *******.\n",
            expression,
            file,
            line);
}

void _assert_pass(const char *expression,
                  const char *file,
                  int line) {
    fprintf(stdout,
            "Assertion '%s' passed, file '%s' line '%d'.\n",
            expression,
            file,
            line);
}

void StartTest(const char *test) {
    static int count = 1;
    printf("Test #%d: %s\n\n", count++, test);
}

void EndTest() {
    printf("\n--------------------------------\n\n");
}


void TestCreateHashtable() {
    StartTest("create_hashtable");

    Hashtable *ht = CreateHashtable(BUCKETS_NUM);

    // hashtable's number is buckets_num
    assert(ht->num_buckets == BUCKETS_NUM);
    assert(ht->num_elements == 0);

    // destroy hashtable
    DestroyHashtable(ht, 1);

    EndTest();
}

void TestGetLoadFactor() {
    StartTest("test get load factor");
    Hashtable *ht = CreateHashtable(5);
    Insert(ht, "jason", "lee");

    assert(ht->num_elements == 1);
    assert(GetLoadFactor(ht) == (double) 0.2);

    // destroy hashtable
    DestroyHashtable(ht, 1);
    EndTest();
}

void TestInsert() {
    StartTest("test insert element to the hashtable");
    Hashtable *ht = CreateHashtable(5);
    assert(ht->buckets[0] == NULL);
    assert(ht->buckets[1] == NULL);
    assert(ht->buckets[2] == NULL);
    assert(ht->buckets[3] == NULL);
    assert(ht->buckets[4] == NULL);

    Insert(ht, "jason", "lee");
    assert(ht->num_elements == 1);
    assert(ht->num_buckets == 5);

    Insert(ht, "jack", "ma");
    assert(ht->num_elements == 2);
    assert(ht->num_buckets == 5);

    DestroyHashtable(ht, 1);
    EndTest();
}

void TestGetKey() {
    StartTest("test get key");
    Hashtable *ht = CreateHashtable(5);

    Insert(ht, "jason", "lee");
    Insert(ht, "jack", "ma");

    assert(ht->num_buckets == 5);
    assert(ht->num_elements == 2);

    assert("lee" == Get(ht, "jason"));
    assert("ma" == Get(ht, "jack"));

    DestroyHashtable(ht, 1);
    EndTest();
}

void TestSortLetter() {
    StartTest("test sort letter");

    char *new_key = (char *) malloc(sizeof(char) * STRING_LEN);
    char *new_val = (char *) malloc(sizeof(char) * STRING_LEN);
    strcpy(new_key, "baacsdfdsa");
    strcpy(new_val, "aaabcddfss");

    printf("%s\n", new_key);
    printf("%s\n", SortLetter(new_key));

    char *after_one = SortLetter(new_key);

    assert(*new_val == after_one[0]);
    assert(new_val[1] == after_one[1]);
    assert(new_val[2] == after_one[2]);
    assert(new_val[3] == after_one[3]);
    assert(new_val[4] == after_one[4]);
    assert(new_val[5] == after_one[5]);
    assert(new_val[6] == after_one[6]);
    assert(new_val[7] == after_one[7]);
    assert(new_val[8] == after_one[8]);
    assert(new_val[9] == after_one[9]);

    free(new_key);
    free(new_val);

    EndTest();
}


int main(void) {
    srand(21774);

    TestCreateHashtable();

    TestGetLoadFactor();

    TestInsert();

    TestGetKey();

    TestSortLetter();

    return EXIT_SUCCESS;
}
