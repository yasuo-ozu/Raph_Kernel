/*
 *
 * Copyright (c) 2016 Raphine Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Author: Liva
 * 
 */

#include <raph.h>
#include <task.h>
#include <cpu.h>
#include "taskqueue.h"

extern "C" {

  struct taskqueue *taskqueue_fast = nullptr;
  
  static void __taskqueue_handle(void *arg) {
    struct task *task = reinterpret_cast<struct task *>(arg);
    task->ta_func(task->ta_context, task->ta_pending);
    task->ta_pending++;
  }


  void _task_init(struct task *t, int priority, task_fn_t *func, void *context) {
    t->ta_task = new Task;
    Function f;
    f.Init(__taskqueue_handle, reinterpret_cast<void *>(t));
    t->ta_task->SetFunc(f);
    t->ta_pending = 0;
    t->ta_func = (func);
    t->ta_context = (context);
  }

  int taskqueue_enqueue(struct taskqueue *queue, struct task *task) {
    task_ctrl->Register(cpu_ctrl->RetainCpuIdForPurpose(CpuPurpose::kLowPriority), task->ta_task);
    return 0;
  }

}
