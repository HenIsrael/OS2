#include <linux/kernel.h>

asmlinkage long sys_hello(void) {
    printk("Hello, World!\n");
    return 0;
}

asmlinkage long sys_set_weight(int weight) { //TODO: Tali
  // TODO: add implementation
  if( weight < 0 )
  {
    return -EINVAL; 
  }
  struct task_struct *task = current;
  task->weight = weight;
  return 0; 
}

asmlinkage long sys_get_weight(void) { //TODO: Hen
  // TODO: add implementation
  struct task_struct *task = get_current();
  return task->weight;
}

asmlinkage long sys_get_ancestor_sum(void) { //TODO: Tali
  // TODO: add implementation
  int sum_weight = 0;
  struct task_struct *task = current;
  while( task->pid != 0)
  {
    sum_weight = sum_weight + task->weight ;
    task = task->parent ; 
  }
  sum_weight = sum_weight + task->weight ;
  return sum_weight;
}

asmlinkage pid_t sys_get_heaviest_descendant(void)
{ //TODO: Hen
  // TODO: add implementation
  struct task_struct* task = get_current();
  pid_t maxPID = task->pid;
  long maxWeight = task->weight;

  struct task_struct* child;
  struct list_head* list;

  // Check if the current task has children
  if (list_empty(&task->children))
    return -ECHILD;

  // Traverse the child process list
  list_for_each(list, &task->children) {

    child = list_entry(list, struct task_struct, sibling);

    // Recursively find the task with the biggest weight among descendants
    pid_t childMaxWeightPID = sys_get_heaviest_descendant();

    // Compare weights and choose the task with the biggest weight
    if (child->weight > maxWeight) {
      maxWeight = child->weight;
      maxPID = child->pid;
    }

    // If weights are the same, compare pids and choose the task with the biggest pid
    else if (child->weight == maxWeight && childMaxWeightPID > maxPID) {
       maxPID = childMaxWeightPID;
     
    }
  }
  return maxPID;
}
