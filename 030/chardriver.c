#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define OLD_METHOD

#define NIITM_NAME "niitm char driver"
const char msg_to_rd[] = "Privet chuvak!\n\r";
#define BUF_LEN	PAGE_SIZE

const char dev_name[] = "lohoped_dev\0";
struct cdev *my_cdev;
dev_t first_node;
char *databuf;



static ssize_t my_chardev_read(struct file *file_p, char __user *user_p, size_t size, loff_t *loff)
{
	int ret;
	printk(KERN_INFO "read exec\n");
	ret = size - copy_to_user(user_p, msg_to_rd, sizeof(msg_to_rd));
	loff += ret;
	return ret;
}

static ssize_t my_chardev_write (struct file *file_p, const char __user *user, size_t size, loff_t *f_pos)
{
	unsigned long retval;
	int n_bytes;
//	if (*file_p == 0) return 0;

#if 0
	memset(&databuf, 0, sizeof(BUF_LEN));
	copy_from_user(&databuf, user, size);
	databuf[size] = 0x00;
#endif
	retval = copy_from_user(databuf, user, size);
	if(retval != 0)
		printk("Error copy_from_user.\n");
	printk(KERN_INFO "writed:\"%s\" %d bytes\n", databuf, (int)size);
	n_bytes = size - retval;	
	return (size_t)n_bytes;
}

static int my_chardev_open(struct inode *inode, struct file *file_s)
{
	return 0;
}

static int my_chardev_release(struct inode *inode, struct file *file_s)
{
	return 0;
}

//long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);

enum e_ioctl_cmds {RD_CNT, CLR_CNT};

long my_unlocked_ioctl(struct file *file_s, unsigned int cmd, unsigned long arg)
{
	switch(cmd) {
		case RD_CNT:
			printk("RD_CNT\n");
		break;
		case CLR_CNT:
			printk("CLR_CNT\n");
		break;
		default:
			printk("Error cmd in ioctl: %d\n", cmd);
			return -EINVAL;
		break;
	}
	return 0;
}

static const struct file_operations my_chardev_fops = {
	.owner = THIS_MODULE,
	.read = my_chardev_read,
	.write = my_chardev_write,
	.open = my_chardev_open,
	.release = my_chardev_release,
	.unlocked_ioctl = my_unlocked_ioctl
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
MODULE_AUTHOR( "Konstantin (lab-2) <name@domain.com>" );
MODULE_DESCRIPTION("Query ioctl() Char Driver");


static int niitm_init(void)
{
	printk(KERN_INFO "Loaded %s.\n", NIITM_NAME);
#if defined OLD_METHOD
	register_chrdev(800, dev_name, &my_chardev_fops);
#else
	first_node = MKDEV(800, 0);
	register_chrdev_region(first_node, 1, dev_name);
	my_cdev = cdev_alloc();
	cdev_init(my_cdev, &my_chardev_fops);
	cdev_add(my_cdev, first_node, 1);
#endif
	databuf = kmalloc(BUF_LEN, GFP_KERNEL);
	if (!databuf){
		printk("Error kmalloc!\n");	
		return -1;
	}
	return 0;
}

static void niitm_exit(void)
{
	printk(KERN_INFO "Unloaded %s.\n", NIITM_NAME);
#if defined OLD_METHOD
	unregister_chrdev(800, dev_name);
#else
	cdev_del(my_cdev);
#endif
	kfree(databuf);
}

module_init(niitm_init);
module_exit(niitm_exit);
