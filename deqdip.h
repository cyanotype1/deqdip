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
 *     deqdip.h
 *
 * Description:
 *     User mode interface definitions for deqdip decache protocol
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

#ifndef __DEQDIP_IOCTL_H
#define __DEQDIP_IOCTL_H


#include <linux/ioctl.h>


#define _DEQDIP_IOCTL_SVC  0x01



#define _DEQDIP_IOCTL_ID    _IO( _DEQDIP_IOCTL_SVC, 1 )


#define KM_DEQDIP_VERS "1.01"


#endif


