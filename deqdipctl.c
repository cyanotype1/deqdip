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
 *     deqdipctl.c
 *
 * Description:
 *     Optional usermode utility to initiate dequeue on ICache & DCache
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

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

#include <linux/stat.h>
#include <sys/ioctl.h>

#include <errno.h>

#include <unistd.h>

#include "deqdip.h"



int main ( void )
{
  int fd_m, fd_p, sts;

    fd_m = open( "/sys/kernel/debug/deqdip/deqdipreq", O_RDONLY );
    
    if( fd_m == -1 )
      {
	perror( "open" );
	return -1;
      }
    
    sts = ioctl( fd_m, _DEQDIP_IOCTL_ID );
    
    if( sts == -1 )
      {
	perror( "ioctl" );
	return -1;
      }

    printf( "ioctl return sts : 0x%02X\n", sts );
    
    fd_p = open( "/proc/sys/vm/drop_caches", O_WRONLY );
    sts = write( fd_p, "3", 1);

    return 0;

}

