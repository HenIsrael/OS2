#include <linux/kernel.h>

asmlinkage long sys_hello(void) {
    printk("Hello, World!\n");
    return 0;
}

asmlinkage long sys_set_weight(int weight) {
  // TODO: add implementation
}

asmlinkage long sys_get_weight(void) {
  // TODO: add implementation
}

asmlinkage long sys_get_ancestor_sum(void) {
  // TODO: add implementation
}

asmlinkage long sys_get_heaviest_descendant(void) {
  // TODO: add implementation
}
