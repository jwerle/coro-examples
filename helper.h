
#ifndef HELPER_H
#define HELPER_H

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

#endif
