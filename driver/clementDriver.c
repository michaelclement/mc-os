/* ------------------------------------------------- */
/*             CHARACTER DEVICE DRIVER               */
/* ------------------------------------------------- */

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
// global character to store the rotated value
static char r;

/* ------------------------------------------------- */
/* ------------------------------------------------- */

static int cd_open(struct inode *i, struct file *f)
{
   printk(KERN_INFO "Driver: open()\n");
   return 0;
}

static int cd_close(struct inode *i, struct file *f)
{
   printk(KERN_INFO "Driver: close()\n");
   return 0;
}

static ssize_t cd_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
   printk(KERN_INFO "Driver: read()\n");
   if (*off == 0)
   {
      // copy one byte from c into buf, in user space.
      // Return an error if all data isn't transferred
      if (copy_to_user(buf, &r, 1) != 0)
      {
         return -EFAULT;
      }
      else
      {
         // increment off so that we don't infinitely
         // spit out the last character in the buffer
         // when we read.
         (*off)++;
         return 1;
      }
   }
   else
   {
      return 0;
   }
}

static ssize_t cd_write(struct file *f, const char __user *buf, size_t len,
                        loff_t *off)
{

   printk(KERN_INFO "*- Driver: write( %d )\n", c);

   if (copy_from_user(&c, buf + len - 1, 1) != 0)
   {
      printk(KERN_INFO "Failed here.\n");
      return -EFAULT;
   }
   else
   {
      // Check if it's a lowercase value
      if ((c <= 122) && (c >= 97))
      {
         printk(KERN_INFO "Lowercase received.");
         // Write to 'c'
         // save original char value to r
         r = c;
         // perform rotation
         if (r > 109)
         {
            // wrap around
            r = 97 + (12 - (122 - r));
         }
         else
         {
            // No wrap around
            r = r + 13;
         }
         // log the rotation:
         printk(KERN_INFO "C -> R: %d -> %d\n", c, r);
         return len;
      }
      // return without rotating
      return len;
   }
}

static struct file_operations clem_fops = {
    .owner = THIS_MODULE,
    .open = cd_open,
    .release = cd_close,
    .read = cd_read,
    .write = cd_write};

// Function to be called when the module is loaded
static int __init clem_init(void)
{
   int ret;

   struct device *dev_ret;

   // Print when we register the module
   printk(KERN_INFO "\n--------\nCLEM DRIVER REGISTERED");

   // Register character device number with name "clem"
   if ((ret = alloc_chrdev_region(&first, 0, 1, "clem")) < 0)
   {
      return ret;
   }
   if (IS_ERR(cl = class_create(THIS_MODULE, "chardrv")))
   {
      unregister_chrdev_region(first, 1);
      return PTR_ERR(cl);
   }
   if (IS_ERR(dev_ret = device_create(cl, NULL, first, NULL, "cdnull")))
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
