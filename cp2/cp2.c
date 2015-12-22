#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/netdevice.h>

#define OLD_METHOD

#define NIITM_NAME "cp2 virtual net driver."
const char msg_to_rd[] = "Privet chuvak!\n\r";
#define BUF_LEN	PAGE_SIZE

const char char_dev_name[] = "lohoped_dev\0";
const char net_dev_name[] = "lab0\0";
struct cdev *my_cdev;
dev_t first_node;
char *databuf;
struct net_device *dev;

struct My_net_dev {
	struct net_device *dev;
	char last_buf[1];
//data
};


//int		my_ndo_init(struct net_device *dev);
//void		my_ndo_uninit(struct net_device *dev);
int		my_ndo_open(struct net_device *dev)
{
	printk("iface lab2 is up.\n");
	return 0;
}
int		my_ndo_stop(struct net_device *dev)
{
	printk("iface lab2 is down.\n");
	return 0;
}
netdev_tx_t	my_ndo_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	printk("to iface lab2 sended pkt.\n");
	return NETDEV_TX_OK;
}



static const struct net_device_ops mynet_netdev_ops = {
	.ndo_open = my_ndo_open,
	.ndo_stop = my_ndo_stop,
	.ndo_start_xmit = my_ndo_start_xmit
};


static void mynet_netdev_init(struct net_device *dev)
{
	struct My_net_dev *priv = netdev_priv(dev);
	priv->dev = dev;
	ether_setup(dev);
	dev->flags |= IFF_NOARP;
	dev->netdev_ops = &mynet_netdev_ops;
	dev->watchdog_timeo = 1;
}

static struct net_device *mynet_netdev_create(const char *name)
{
	struct net_device *dev;
	dev = alloc_netdev(sizeof(struct My_net_dev), name, NET_NAME_UNKNOWN, mynet_netdev_init);
//	printk(KERN_ERR "Dev = %p\n",dev);
	return dev;
}

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
	int ret;
	printk(KERN_INFO "Loaded %s.\n", NIITM_NAME);
#if defined OLD_METHOD
	register_chrdev(800, char_dev_name, &my_chardev_fops);
#else
	first_node = MKDEV(800, 0);
	register_chrdev_region(first_node, 1, char_dev_name);
	my_cdev = cdev_alloc();
	cdev_init(my_cdev, &my_chardev_fops);
	cdev_add(my_cdev, first_node, 1);
#endif
	databuf = kmalloc(BUF_LEN, GFP_KERNEL);
	if (!databuf) {
		printk("Error kmalloc!\n");	
		return -1;
	}
	if((dev=mynet_netdev_create(net_dev_name)) == NULL)
	{
		printk("Error mynet_netdev_create!\n");
		goto error;
	}
	ret = register_netdev(dev);
	if(ret != 0) { // no success
		printk("Error register_netdev!\n");
		unregister_netdev(dev);
error:
		free_netdev(dev);

#if defined OLD_METHOD
		unregister_chrdev(800, char_dev_name);
#else
		cdev_del(my_cdev);
#endif
		kfree(databuf);
		return -1;
	}
	printk("lab0 net init success!\n");

	return 0;
}

static void niitm_exit(void)
{
	unregister_netdev(dev);
	free_netdev(dev);

	printk(KERN_INFO "Unloaded %s.\n", NIITM_NAME);
#if defined OLD_METHOD
	unregister_chrdev(800, char_dev_name);
#else
	cdev_del(my_cdev);
#endif
	kfree(databuf);
}

module_init(niitm_init);
module_exit(niitm_exit);
