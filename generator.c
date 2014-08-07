
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helper.h"
#include "coro.h"

/**
 * Routine stack
 */

static struct coro_stack stack;

/**
 * Routine contexts
 */

static union {
  coro_context root;
  coro_context gen;
} ctx;

/**
 * `gen' Generator routine
 */

co(gen, {
  info("in routine");
});

int
main (void) {
  char ptr[1024];

  // create root context with no routine, arg, or data
  info("ctx(root)");
  coro_create(&ctx.root, NULL, NULL, NULL, 0);

  // allocate routine stack
  info("alloc(stack)");
  coro_stack_alloc(&stack, 1);

  // push `gen' routine to stack
  info("push(gen)");
  push(ctx.gen, stack, &ptr, gen);

  info("enter(gen)");
  enter(ctx.root, ctx.gen);

  return 0;
}
