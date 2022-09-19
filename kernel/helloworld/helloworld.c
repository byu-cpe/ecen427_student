#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void) {
  // Called on module load
  printk(KERN_ALERT "Hello, world\n");
  return 0;
}
static void hello_exit(void) {
  // Called on module unload
  printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);