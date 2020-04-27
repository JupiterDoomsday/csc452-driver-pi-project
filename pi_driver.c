/*
 * AUTHOR: ISABELA HUTCHINGS
 * CLASS: csc 452
 * PROJECT 2: pi_driver.c
 *
 */

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include "pi.h"
/*
 * pi_driver_read is the function called when a process calls read() on
 * /dev/hello.  It writes N numbers of pi to the buffer passed in the
 * read() call.
 */

static ssize_t pi_driver_read(struct file* file,char * buf, size_t count, loff_t *ppos){

	pi(buf,count);

	int len = strlen(buf); // Don't include the null byte
	 // We only support reading the whole string at once.
	if (count < len)
		return -EINVAL;
	/*
	 * If file position is non-zero, then assume the string has
	 * been read and indicate there is no more data to be read.
	 */
	if (*ppos != 0) return 0;
	// Tell the user how much data we wrote
	*ppos = len;
	return len;
}

/*
 * The only file operation we care about is read.
 */

static const struct file_operations pi_driver_fops = {
	.owner		= THIS_MODULE,
	.read		= pi_driver_read,
};

static struct miscdevice pi_driver_dev = {
	/*
	 * We don't care what minor number we end up with, so tell the
	 * kernel to just pick one.
	 */
	MISC_DYNAMIC_MINOR,
	/*
	 * Name ourselves /dev/pi.
	 */
	"pi_driver",
	/*
	 * What functions to call when a program performs file
	 * operations on the device.
	 */
	&pi_driver_fops
};

static int __init
pi_driver_init(void)
{
	int ret;

	/*
	 * Create the "pi_driver" device in the /sys/class/misc directory.
	 * Udev will automatically create the /dev/hello device using
	 * the default rules.
	 */
	ret = misc_register(&pi_driver_dev);
	if (ret)
		printk(KERN_ERR
		       "Unable to register \"pi!\" misc device\n");

	return ret;
}

module_init(pi_driver_init);

static void __exit
pi_driver_exit(void)
{
	misc_deregister(&pi_driver_dev);
}

module_exit(pi_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ISABEL HUTCHINGS <cssetton@email.arizona.edu>");
MODULE_DESCRIPTION("\"pi\" this reas n number of digits");
MODULE_VERSION("dev");
