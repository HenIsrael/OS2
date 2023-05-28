#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/list.h>

asmlinkage long sys_hello(void)
{
    printk("Hello, World!\n");
    return 0;
}

asmlinkage long sys_set_weight(int weight) { 
  
  if( weight < 0 )
  {
    return -EINVAL; 
  }
  struct task_struct *task = current;
  task->weight = weight;
  return 0; 
}

asmlinkage long sys_get_weight(void) { 

  struct task_struct *task = get_current();
  return task->weight;
}

asmlinkage long sys_get_ancestor_sum(void) { 

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

long findTaskWithMaxWeight(struct task_struct* task, long* maxWeight) {
    
    struct list_head* list;
    struct task_struct* child;
    long maxPID = -1; // Initalize invalid pid for father

    // Traverse the child process list
    list_for_each(list, &task->children) {
        child = list_entry(list, struct task_struct, sibling);

        // Compare weight and update maxWeight and maxPID if necessary
        if (child->weight > *maxWeight || (child->weight == *maxWeight && child->pid < maxPID && maxPID != -1)) {
            *maxWeight = child->weight;
            maxPID = child->pid;
        }

        // Recursively call the function for the current child
        long childMaxPID = findTaskWithMaxWeight(child, maxWeight);
        if (childMaxPID > maxPID) {
            maxPID = childMaxPID;
        }
    }

    return maxPID;
}

asmlinkage long sys_get_heaviest_descendant(void){
    
    struct task_struct* currentTask = current;
    long maxWeight = 0; // father is not included in heaviest descendant  

    if (list_empty(&currentTask->children)) {
        return -ECHILD;  // Return -ECHILD if the current task has no descendants
    }

    return findTaskWithMaxWeight(currentTask, &maxWeight);
}
