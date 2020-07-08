#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
// For accessing userspace
#include <asm/uaccess.h>
#include <linux/uaccess.h>

/* ------------------------------------------------- */
/*                       GLOBALS                     */
/* ------------------------------------------------- */

// first device number
static dev_t first;
// character device structure
static struct cdev c_dev;
// device class
static struct class *cl;
// global character to be read/written 
static char c;

/* ------------------------------------------------- */
/* ------------------------------------------------- */

static int my_open(struct inode *i, struct file *f)
{
   printk(KERN_INFO "Driver: open()\n");
   return 0;
}

static int my_close(struct inode *i, struct file *f)
{
   printk(KERN_INFO "Driver: close()\n");
   return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
   printk(KERN_INFO "Driver: read()\n");
   if (*off == 0) {
      // copy one byte from c into buf, in user space.
      // Return an error if all data isn't transferred
      if (copy_to_user(buf, &c, 1) != 0) {
         return -EFAULT;
      } else {
         // increment off so that we don't infinitely
         // spit out the last character in the buffer
         // when we read.
         (*off)++;
         return 1;
      }
   } else {
      return 0;
   }
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len,
                        loff_t *off)
{
   printk(KERN_INFO "Driver: write()\n");
   // Write to 'c'
   if (copy_from_user(&c, buf + len -1, 1) != 0) {
      return -EFAULT;
   } else {
      return len;
   }
}

static struct file_operations clem_fops = {
   .owner = THIS_MODULE,
   .open = my_open,
   .release = my_close,
   .read = my_read,
   .write = my_write
};

// Function to be called when the module is loaded
static int __init clem_init(void)
{
   int ret;

   struct device *dev_ret;

   // Print when we register the module
   printk(KERN_INFO "\n--------\nCLEM DRIVER REGISTERED");

   // Register major number with name "clem"
   if ((ret = alloc_chrdev_region(&first, 0, 1, "clem")) < 0)
   {
      return ret;
   }
   if (IS_ERR(cl = class_create(THIS_MODULE, "chardrv")))
   {
      unregister_chrdev_region(first, 1);
      return PTR_ERR(cl);
   }
   if (IS_ERR(dev_ret = device_create(cl, NULL, first, NULL, "mynull")))
   {
      class_destroy(cl);
      unregister_chrdev_region(first, 1);
      return PTR_ERR(dev_ret);
   }

   cdev_init(&c_dev, &clem_fops);

   if ((ret = cdev_add(&c_dev, first, 1)) < 0)
   {
      device_destroy(cl, first);
      class_destroy(cl);
      unregister_chrdev_region(first, 1);
      return ret;
   }

   return 0;
};

static void __exit clem_exit(void) /* Destructor */
{
   cdev_del(&c_dev);
   device_destroy(cl, first);
   class_destroy(cl);
   unregister_chrdev_region(first, 1);
   printk(KERN_INFO "\n--------\nCLEM DRIVER UNREGISTERED");
};

/* ------------------------------------------------- */
/* ------------------------------------------------- */

// Call the load/unload functions
module_init(clem_init);
module_exit(clem_exit);

/* ------------------------------------------------- */
/* ------------------------------------------------- */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Michael Clement");
MODULE_DESCRIPTION("Character driver based on the examples from https://sysplay.in/");
