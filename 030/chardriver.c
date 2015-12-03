#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define NIITM_NAME "niitm char driver"
#define BUF_LEN	PAGE_SIZE

const char dev_name[] = "lohoped_dev\0";
struct cdev *my_cdev;
dev_t first_node;
char *databuf;



static ssize_t my_chardev_read(struct file *file_p, char __user *user_p, size_t size, loff_t *loff)
{
	printk(KERN_INFO "read exec\n");
	return 0;
}

static ssize_t my_chardev_write (struct file *file_p, const char __user *user, size_t size, loff_t *f_pos)
{
//	if (*file_p == 0) return 0;
	memset(&databuf, 0, sizeof(BUF_LEN));
	copy_from_user(&databuf, user, size);
	databuf[size] = 0x00;
	printk(KERN_INFO "writed:\"%s\" %d bytes\n", databuf, size);

	return -EINVAL;
}

static int my_chardev_open(struct inode *inode, struct file *file_s)
{
	return 0;
}

static int my_chardev_release(struct inode *inode, struct file *file_s)
{
	return 0;
}

static const struct file_operations my_chardev_fops = {
	.owner = THIS_MODULE,
	.read = my_chardev_read,
	.write = my_chardev_write,
	.open = my_chardev_open,
	.release = my_chardev_release
};

/*
struct file {
	struct path	f_path;
	struct inode	*f_inode;
	const struct	file_operations	*f_ops;
	struct	mutex	f_pos_lock;
	loff_t		f_pos;
}
*/
/*
struct cdev {
	struct kobject kobj;
	struct module *owner;
	const struct file_operations *ops;
	struct list_head list;
	dev_t dev;
	unsigned int count;
};
*/

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Name Lastname <name@domain.com>" );


static int niitm_init(void)
{
	printk(KERN_INFO "Loaded %s.\n", NIITM_NAME);
	register_chrdev(800, dev_name, &my_chardev_fops);
	first_node = MKDEV(800, 0);
	register_chrdev_region(first_node, 1, dev_name);
	my_cdev = cdev_alloc();
	cdev_init(my_cdev, &my_chardev_fops);
	cdev_add(my_cdev, first_node, 1);
	databuf = kmalloc(BUF_LEN, GFP_KERNEL);	
	return 0;
}

static void niitm_exit(void)
{
	printk(KERN_INFO "Unloaded %s.\n", NIITM_NAME);
	unregister_chrdev(800, dev_name);
	kfree(&databuf);
}

module_init(niitm_init);
module_exit(niitm_exit);
