/*
 *
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * GPL Licence
 *------------------------------------------------------------------------
 *
 * Facility:
 *     deqdip 
 *
 * Name:
 *     km_c_deqdip.c
 *
 * Description:
 *     Kernel mode implementation of cache dequeue protocol. 
 *
 * Author:
 *     marcel@aexa.uk 2020 (C)
 *
 * History:
 *
 *   Date         Name             Description
 *
 *   30-SEP-2020  marcel@aexa.uk   Created.
 *
 *
 *-----------
 *
 */


#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
//#include <linux/printk.h>

#include <linux/ioctl.h>

//#include <linux/uaccess.h>
#include <linux/debugfs.h>

#include "deqdip.h"

#include "km_deqdip.h"


static struct dentry *df;

static struct file_operations fops = {
				      
   .owner = THIS_MODULE, .unlocked_ioctl = &deqdip
   
};


/*++++
 *
 * Service requests to /sys/kernel/.../deqdipreq device file
 *
 *----
 */

static long int deqdip ( struct file *fp, unsigned int cmd, unsigned long argp )
{
  
  void __user *arg_user;

  arg_user = ( void __user * )argp;

  //printk( KERN_INFO "deqdip_cmd: 0x%02X\n", cmd );

  switch( cmd )
    {

    case _DEQDIP_IOCTL_ID:

      on_each_cpu( _exec_deqdip, NULL, 1 );
      
      return 0;
      break;
    }

  return -1;

}


static void deqdip_exit ( void )
{
  
  debugfs_remove_recursive( df );
  
  printk( KERN_INFO "module unloaded: (deqdip) dequeue all-core CPU caches v%s\n",
	    KM_DEQDIP_VERS );

}


/*++++
 *
 * Create /sys/kernel/.../deqdipreq device file
 *
 *----
 */


static int __init deqdip_init ( void )
{
  
  df = debugfs_create_dir( "deqdip", 0 );
  
  debugfs_create_file( "deqdipreq", 0, df, NULL, &fops );
  
  printk( KERN_INFO "module is loaded: (deqdip) deque all-core CPU caches v%s\n",
	  KM_DEQDIP_VERS );
  
  return 0;
}



module_init( deqdip_init );

module_exit( deqdip_exit );
