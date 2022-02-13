/* Switch off mem debbugging totally */

#define mem_malloc malloc
#define mem_calloc calloc
#define mem_free free
#define mem_realloc realloc
#define mem_strdup strdup

#define mem_check()
#define mem_init()
#define mem_term()
