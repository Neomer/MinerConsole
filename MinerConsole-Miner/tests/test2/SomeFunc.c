__kernel void vec_op( __global float *a )
{
	int gid = get_global_id(0);
 
	if ( gid % 2 ) {
		a[gid] += a[gid];
	} else {
		a[gid] *= a[gid];
	}
}