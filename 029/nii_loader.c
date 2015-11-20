


void nii_print(void);

static int niitm_init(void)
{
	nii_print();
	return 0;
}

static void niitm_exit(void)
{
}

module_init(niitm_init);
module_exit(niitm_exit);
