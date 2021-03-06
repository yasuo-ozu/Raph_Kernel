/*-
 * Copyright (c) 2000 Doug Rabson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef _FREEBSD_SYS_TASKQUEUE_H_
#define _FREEBSD_SYS_TASKQUEUE_H_

#include <sys/_task.h>
#include <sys/_callout.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

  struct taskqueue;
  extern struct taskqueue *taskqueue_fast;

  typedef void (*taskqueue_enqueue_fn)(void *context);

  void _task_init(struct task *t, int priority, task_fn_t *func, void *context);

#define TASK_INIT(task, priority, func, context) \
  _task_init(task, priority, func, context);
  
#define taskqueue_create_fast(...) (nullptr)
#define taskqueue_start_threads(...) (0)

  int taskqueue_enqueue(struct taskqueue *queue, struct task *task);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _FREEBSD_SYS_TASKQUEUE_H_ */
