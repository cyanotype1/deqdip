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
 *     nif_deqdip.c
 *
 * Description:
 *     NIF Dynamic Library loaded with ErlangVM to steer
 *     deqdip Elixir API calls to the deqdip Kernel Loadable Module
 *     which clears the ICache & DCache. Additionally clears the
 *     fsPageCache.
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


#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <linux/stat.h>
#include <sys/ioctl.h>

#include <unistd.h>

#include <errno.h>

#include <erl_nif.h>


#include "deqdip.h"




static ERL_NIF_TERM deqdipctl( ErlNifEnv *env, int argc,
 			       const ERL_NIF_TERM argv[] )			   
{
    
  int fd_m, fd_p, sts;

  
  fd_m = open( "/sys/kernel/debug/deqdip/deqdipreq", O_RDONLY );
  
  sts = ioctl( fd_m, _DEQDIP_IOCTL_ID );
  
  if( sts == -1 )
    return enif_make_int( env, -1 );
  else
    return enif_make_int( env, 0 );

  /* std linux flush fs pagecache */
  
  fd_p = open( "/proc/sys/vm/drop_caches", O_WRONLY );
  sts = write( fd_p, "3", 1);

}



static ErlNifFunc nif_funcs[] =
{
	{ "deqdipctl", 0, deqdipctl }

};



/*
 * Nb. the pseudovariable in position 1 is not valid C
 * outside of this custom MACRODEF.
*/

ERL_NIF_INIT( Elixir.Deqdipctl, nif_funcs, NULL, NULL, NULL, NULL )
  







