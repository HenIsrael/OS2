#include <linux/kernel.h>

asmlinkage long sys_hello(void) {
    printk("Hello, World!\n");
    return 0;
}

asmlinkage long sys_set_weight(int weight) { //TODO: Tali
  // TODO: add implementation
}

asmlinkage long sys_get_weight(void) { //TODO: Hen
  // TODO: add implementation
}

asmlinkage long sys_get_ancestor_sum(void) { //TODO: Tali
  // TODO: add implementation
}

asmlinkage long sys_get_heaviest_descendant(void) { //TODO: Hen
  // TODO: add implementation
}
