
#ifndef HELPER_H
#define HELPER_H

#include "coro.h"

// shut up syntastic
#define coro_transfer coro_transfer

/**
 * Output formatted info
 */

#define info(s, ...) ({                                                        \
  printf("  ");                                                                \
  printf(s, ##__VA_ARGS__);                                                    \
  printf("\n");                                                                \
})

/**
 * Push routine to stack
 */

#define push(ctx, stack, data, fn) ({                                          \
  coro_create(&ctx, fn, data, stack.sptr, stack.ssze);                         \
})

/**
 * Enter context from another context
 */

#define enter(from, to) coro_transfer(&from, &to)

/**
 * Initialize a new routine in block from name
 */

#define co(name, body) static void name (void *__data) {                       \
  body                                                                         \
  enter(ctx.name, ctx.root);                                                   \
}

#endif
