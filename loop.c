
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "helper.h"
#include "coro.h"

/**
 * Loop routine
 */

static void
loop (void *);

/**
 * Routine stack
 */

static struct coro_stack stack;

/**
 * Routine contexts
 */

static union {
  coro_context root;
  coro_context loop;
} ctx;

int
main (void) {
  // create root context with no routine, arg, or data
  info("ctx(root)");
  coro_create(&ctx.root, NULL, NULL, NULL, 0);

  // allocate routine stack
  info("alloc(stack)");
  coro_stack_alloc(&stack, 1);

  // push loop routine to stack
  info("push(loop)");
  push(ctx.loop, stack, NULL, loop);

  // main loop
  while (1) {
    // enter loop from root
    enter(ctx.root, ctx.loop);
    info("enter(root)");
  }
  return 0;
}

static void
loop (void *data) {
  while (1) {
    info("enter(loop)");
    sleep(1);
    enter(ctx.loop, ctx.root);
  }
}
