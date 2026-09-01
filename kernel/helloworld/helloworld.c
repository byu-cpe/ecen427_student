#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

// Called on module load
static int hello_init(void) {
  printk(KERN_ALERT "Hello, world\n");
  return 0;
}

// Called on module unload
static void hello_exit(void) { printk(KERN_ALERT "Goodbye, cruel world\n"); }

module_init(hello_init);
module_exit(hello_exit);