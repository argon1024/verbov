#include <linux/module.h>
#include "export.h"

void nii_print(void);

static int niitm_init(void)
{
	printk(KERN_INFO "Loaded loader.\n");
	nii_print();
	return 0;
}

static void niitm_exit(void)
{
}

module_init(niitm_init);
module_exit(niitm_exit);
