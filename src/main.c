#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <math.h>

#include "./try_catch_finally.h"

#define EXCEPTION 1
#define RUNTIME_ERROR (EXCEPTION + 1)

jmp_buf point;

int main(int argc, char* *argv) {
    int i;
    srand(time(NULL));
    for (i = 0; i < 10; ++i) {
        BEGIN_TRY(outer) {
            switch (rand() % 3) {
                case 0: {
                            BEGIN_TRY(inner) {
                                if (rand() % 2 == 0)
                                    THROW(inner, EXCEPTION);
                                printf("i = %d, inner OK\n", i);
                            } CATCH(inner, EXCEPTION) {
                                printf("i = %d, inner catch\n", i);
                            } FINALLY(inner) {
                                printf("i = %d, inner finally\n", i);
                            } END_TRY(inner);
                        }
                        THROW(outer, EXCEPTION);
                case 1: THROW(outer, RUNTIME_ERROR);
            }
            printf("i = %d, OK\n", i);
        } CATCH(outer, EXCEPTION) {
            printf("i = %d, exception!\n", i);
        } CATCH(outer, RUNTIME_ERROR) {
            printf("i = %d, runtime_error!\n", i);
        } FINALLY (outer) {
            printf("i = %d, outer finally\n", i);
        } END_TRY(outer);
    }

    BEGIN_GLOBAL_TRY(point) {
        THROW(point, EXCEPTION);
    } END_TRY(point);

    return EXIT_SUCCESS;
}
