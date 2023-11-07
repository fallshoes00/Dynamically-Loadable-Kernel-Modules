#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include <linux/string.h>

#define DRIVER_AUTHOR "ijui hung" 
#define DRIVER_DESC   "Sending parameters to Module when loading"

static char *kernelModuleName = "paramsModule"; //Change module's name when needed


static long secretValue = 987654321;
module_param(secretValue, long, 0644);
MODULE_PARM_DESC(secretValue, "Parameter for secret value.");

static char *charparameter = "Hello world! Sending parameters.";
module_param(charparameter, charp, 0644);
MODULE_PARM_DESC(charparameter,"states - Hello world");

static int modifyValues = 0;
module_param(modifyValues, int, 0644);
MODULE_PARM_DESC(modifyValues, "Indicates if we must modify the original values or not.");

static long dummySecretValue = -2;

static int initialize(void){
    
    if(modifyValues==1)
    {
        secretValue = dummySecretValue;
        charparameter = "This is a dummy message!";
    }

    printk(KERN_INFO "\n[%s - %s] =============\n",kernelModuleName,__func__);
    printk(KERN_INFO "[%s - %s] Hello!\n",kernelModuleName,__func__);

    printk(KERN_INFO "[%s - %s] String inside module = [%s]\n", kernelModuleName, __func__, charparameter);
    printk(KERN_INFO "[%s - %s] Secret value = [%ld]\n", kernelModuleName, __func__, secretValue);

    return 0;
}

static void clean_exit(void){
    printk(KERN_INFO "\n[%s - %s] =============\n",kernelModuleName,__func__);
    printk(KERN_INFO "[%s - %s] Goodbye!\n",kernelModuleName,__func__);

    printk(KERN_INFO "[%s - %s] String inside module = [%s]\n", kernelModuleName, __func__, charparameter);
    printk(KERN_INFO "[%s - %s] Secret value = [%ld]\n", kernelModuleName, __func__, secretValue);
}

module_init(initialize);
module_exit(clean_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
