/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "add.h"

bool_t
xdr_add_in (XDR *xdrs, add_in *objp)
{
	register int32_t *buf;

	 if (!xdr_long (xdrs, &objp->arg1))
		 return FALSE;
	 if (!xdr_long (xdrs, &objp->arg2))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_add_out (XDR *xdrs, add_out *objp)
{
	register int32_t *buf;

	 if (!xdr_long (xdrs, &objp->res))
		 return FALSE;
	return TRUE;
}