#ifndef TRY_CATCH_FINALLY_H_INCLUDED
#define TRY_CATCH_FINALLY_H_INCLUDED

#include <stdio.h>
#include <setjmp.h>
#include <limits.h>

#define BEGIN_GLOBAL_TRY(point) \
    do { \
        int point##_finally_entered; \
        point##_finally_entered = 0; \
        switch (setjmp(point)) { \
            case 0: {

#define BEGIN_LOCAL_TRY(point) \
    do { \
        jmp_buf point; \
        int point##_finally_entered; \
        point##_finally_entered = 0; \
        switch (setjmp(point)) { \
            case 0: {

#define BEGIN_TRY BEGIN_LOCAL_TRY

#define CATCH(point, x) \
                        longjmp(point, INT_MAX); \
                    } \
                    break; \
            case x: {
#define END_TRY(point) \
                        if (!point##_finally_entered) \
                            longjmp(point, INT_MAX); \
                    } \
                    break; \
        } \
    } while(0)
#define FINALLY(point) \
                        longjmp(point, INT_MAX); \
                    } \
                    break; \
            default: { \
                         point##_finally_entered = 1;

#define THROW(point, exception) longjmp(point, exception)

#endif // TRY_CATCH_FINALLY_H_INCLUDED
