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

asmlinkage long sys_get_heaviest_descendant(void) { //TODO: Hen
  // TODO: add implementation
}
