#
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# GPL Licence
#------------------------------------------------------------------------
#
# Facility:
#     deqdip 
#
# Name:
#     km_s_deqdip.S
#
# Description:
#     Kernel mode implementation of cache dequeue protocol. 
#   
# Author:
#     marcel@aexa.uk 2020 (C)
#
# History:
#
#   Date         Name             Description
#
#   30-SEP-2011  marcel@aexa.uk   Created.
#
#
#-----------
#
#

.data

v_cr0_cd_set:	.quad	1<<30
v_cr0_nw_clr:	.quad	~(1<<29)

	
.text

.global	_exec_deqdip


/*++++
 *
 * Follow Intel Architecturally defined specification to initiate
 * dequeue on ICache and DCache.
 *
 * This executes on the current core of the current thread only.
 *
 * The calling routine is responsible for arranging execution on
 * all cores to effect the cache flush in shared memory
 * configurations.
 * 
 *----
 */


_exec_deqdip:	
	mov	%cr0, %rax
	or	v_cr0_cd_set, %rax
	and	v_cr0_nw_clr, %rax
	mov	%rax, %cr0
	wbinvd

	// mttr no longer used by linux

	// pat can also be disregarded 
	

		

_rts_keck:
	ret
	
