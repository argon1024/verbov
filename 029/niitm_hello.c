#include <linux/module.h>
#inclide "export.h"

#define NIITM_NAME "niitm hello"

EXPORT_SYMBOL(nii_print());

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Name Lastname <name@domain.com>" );


void nii_print(void)
{
	printk(KERN_INFO "Exported function executed.");
}

static int niitm_init(void)
{
	printk(KERN_INFO "Loaded %s.\n", NIITM_NAME);
	return 0;
}

static void niitm_exit(void)
{
	printk(KERN_INFO "Unloaded %s.\n", NIITM_NAME);
}

module_init(niitm_init);
module_exit(niitm_exit);
