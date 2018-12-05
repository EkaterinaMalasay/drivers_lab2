#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h> 
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/cdev.h>

static dev_t first;  //Global variable for the first device number
static struct cdev c_dev;  //Global variable for the character device structure


///////////////////////////////////////////////////////////////////////////////////

static int lab_open(struct inode i, struct file f)
{
	printk(KERN_INFO "Driver open");
	return 0;
}

static int lab_close(struct inode i, struct file f)
{
	printk(KERN_INFO "Driver close");
	return 0;
}

static ssize_t lab_read(struct file f, char __user buf, size_t len, loff_t off)
{
	printk(KERN_INFO "Driver read");
	return 0;
}

static ssize_t lab_write(struct file f, const char __user buf, size_t len, loff_t off)
{
	printk(KERN_INFO "Driver write");
	return len;
}

///////////////////////////////////////////////////////////////////////////////////
static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open = lab_open,
	.release = lab_close,
	.read = lab_read,
	.write = lab_write
};

static int __init lab_init(void) /* Constructor */
{
	int result;
	printk(KERN_INFO "module for lab 2 ");

	result = alloc_chrdev_region(&first, 0, 1, "lab2module");
	if ( result < 0) {
		printk(KERN_WARNING "module for lab 2: can't get major \n");
		return result;
	}

	cdev_init(&c_dev, &fops);
	if (cdev_add(&c_dev, first, 1) == -1) {
		unregister_chrdev_region(first, 1);
		return -1;
	}

	printk(KERN_INFO "<Major, Minor>: <%d, %d>\n", MAJOR(first), MINOR(first));
	return 0;
}


static void __exit lab_exit(void) /* Destructor */
{
	unregister_chrdev_region(first, 1);
	printk(KERN_INFO "module for lab 2 finishes his work");
}


module_init(lab_init);
module_exit(lab_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Character Driver for lab2");

