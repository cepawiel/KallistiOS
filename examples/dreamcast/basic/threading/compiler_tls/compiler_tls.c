/* KallistiOS ##version##

   compiler_tls.c

   (c)2023 Colton Pawielski

   A simple example showing off thread local variables

   This example launches two threads that access variables
   placed in the TLS segment by the compiler. The compiler
   is then able to generate trivial lookups based on the GBR
   register which holds the address to the current threads's
   control block.

 */

#include <kos.h>
#include <stdbool.h>

#if (__GNUC__ <= 4)
/* GCC4 only supports using TLS with the __thread identifier,
   even when passed the -std=c99 flag */
#define thread_local __thread
#else
/* Newer versions of GCC use C11's _Thread_local to specify TLS */
#define thread_local _Thread_local
#endif

typedef struct {
    uint8_t inner[3];
} Align4;

typedef struct {
    uint8_t inner[3];
} Align16;

static thread_local volatile _Alignas(4)  Align4   BUF_4           = {.inner = {2, 2, 2}};
static thread_local volatile _Alignas(16) Align16  BUF_16          = {.inner = {1, 1, 1}};
static thread_local volatile              uint16_t tlsUint16[256]  = { 0 };
static thread_local volatile _Alignas(32) uint32_t tbss_test       = 0;
static thread_local volatile _Alignas(32) char     tlsCharArray_[] = { "abcdefghijklmnopqrstuvwxyz012345" };
static thread_local volatile              uint32_t tdata_test      = 0x5A;

/* Thread Function */
void *thd(void *v) {
    int i;
    int id = (int) v;

    printf("Started Thread %d\n", id);

    for (i = 0; i < 5; i++){        
        printf("Thread[%d]\tbss_test = 0x%lX\n", id, tbss_test);
        tbss_test++;
        thd_sleep(50);
    }

    for (i = 0; i < 5; i++){
        printf("Thread[%d]\ttdata_test = 0x%lX\n", id, tdata_test);
        tdata_test++;
        thd_sleep(50);
    }

    if(tlsUint16[0] != 0)
        printf("TLSUINT16 FAILED!\n");

    if(strcmp(tlsCharArray_, "abcdefghijklmnopqrstuvwxyz012345")) {
        printf("ALPHABET FAILED: %s\n", tlsCharArray_);
    }


    bool reproduced = false;

    // Check if at least one byte has been offset improperly
    printf("[");
    for (int i = 0; i < 3; i++) {
        if (BUF_4.inner[i] != 2) {
            reproduced = true;
        }
        printf("%d, ", BUF_4.inner[i]);
    }
    printf("]\n");

    printf("[");
    for (int i = 0; i < 3; i++) {
        if (BUF_16.inner[i] != 1) {
            reproduced = true;
        }
        printf("%d, ", BUF_16.inner[i]);
    }
    printf("]\n");


    if (reproduced) {
        printf("Bug has been reproduced!\n");
    }
    else {
        printf("There has been no issue!\n");
    }

    printf("Finished Thread %d\n", id);
    return NULL;
}

/* The main program */
int main(int argc, char **argv) {
    const int thread_count = 5;

    int i;
    kthread_t * threads[thread_count];   

    printf("Starting Threads\n");

    for(i = 0; i < thread_count; i++) {
        threads[i] = thd_create(0, thd, (void *) i);
    };

        for (i = 0; i < 5; i++){        
        printf("Main Thread\tbss_test = 0x%lX\n", tbss_test);
        tbss_test++;
        thd_sleep(25);
    }

    for (i = 0; i < 5; i++){
        printf("Main Thread\ttdata_test = 0x%lX\n", tdata_test);
        tdata_test++;
        thd_sleep(25);
    }

    for(i = 0; i < thread_count; i++) {
        int ret = (int) thd_join(threads[i], NULL);
        printf("Thread[%d] Returned: %d\n", i, ret);
    }
    
    printf("Threads Finished!\n");
    return 0;
}
