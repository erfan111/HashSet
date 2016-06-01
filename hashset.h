
#ifndef HASHSET_H
#define HASHSET_H 1

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

    struct hashset_st {
        size_t nbits;
        size_t mask;

        size_t capacity;
        size_t *items;
        size_t nitems;
    };

    typedef struct hashset_st *hashset_t;

    hashset_t hashset_create(void);

    void hashset_destroy(hashset_t set);

    size_t hashset_num_items(hashset_t set);

    int hashset_add(hashset_t set, void *item);

    int hashset_remove(hashset_t set, void *item);

    int hashset_is_member(hashset_t set, void *item);

    int hashset_member_address(hashset_t set, void *item);


#ifdef __cplusplus
}
#endif

#endif
