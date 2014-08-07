
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
  coro_context pub;
  coro_context sub;
} ctx;

/**
 * Max queue size
 */

#define QUEUE_MAX 10

/**
 * `int' queue
 */

static int q[QUEUE_MAX];

/**
 * `q' size
 */

static size_t qsize = 0;

/**
 * `q' index
 */

static int qi = 0;

/**
 * `pub' routine
 */

co(pub, {
  while (1) {
    if (qsize < QUEUE_MAX) {
      info("publish");
      q[qsize++] = rand();
      enter(ctx.pub, ctx.sub);
    } else {
      enter(ctx.pub, ctx.root);
    }
  }
});

/**
 * `sub' routine
 */

co(sub, {
  int n = 0;
  while (1) {
    if (qsize > 0) {
      n = q[qi++];
      qsize--;
      printf("got %d\n", n);
    }

    enter(ctx.sub, ctx.root);
  }
});

/**
 * `main'
 */

int
main (void) {
  // create root context with no routine, arg, or data
  info("ctx(root)");
  coro_create(&ctx.root, NULL, NULL, NULL, 0);

  // allocate routine stack
  info("alloc(stack)");
  coro_stack_alloc(&stack, 1);

  // push `pub' routine to stack
  info("push(pub)");
  push(ctx.pub, stack, NULL, pub);

  // push `sub' routine to stack
  info("push(sub)");
  push(ctx.sub, stack, NULL, sub);

  info("starting loop");
  while (1) {
    enter(ctx.root, ctx.pub);
  }

  return 0;
}

