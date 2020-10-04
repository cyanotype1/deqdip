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
 *     km_deqdip.h
 *
 * Description:
 *     Kernel mode interface definitions for deqdip decache protocol
 *
 * Author:
 *     marcel@aexa.uk 2020 (C)
 *
 * History:
 *
 *   Date         Name             Description
 *
 *   30-SEP-2011  marcel@aexa.uk   Created.
 *
 *
 *-----------
 *
 */


#ifndef __KM_DEQDIP_H
#define __KM_DEQDIP_H

MODULE_LICENSE("GPL");


MODULE_AUTHOR("cyanotype1@github");
MODULE_DESCRIPTION("Dequeue I&D Caches on every core");
MODULE_VERSION( KM_DEQDIP_VERS );


extern void _exec_deqdip( void *info );

static long int deqdip( struct file *fp, unsigned int cmd, unsigned long argp );
static void deqdip_exit( void );
static int __init deqdip_init( void );
  
#endif
