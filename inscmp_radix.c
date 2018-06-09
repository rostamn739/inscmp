
#include "inscmp_mod.h"

extern unsigned normal_distri[DISTRI_SIZE];

RADIX_TREE(inscmp_tree, GFP_KERNEL);
static char *dummy = "DUMMY VALUE"; //all entries will point to this

int test_radix_tree( int *success_count ) {
	//for key in normal distribution
	int i;
	*success_count = 0;
	for (i = 0; i < DISTRI_SIZE; ++i) {
		//radix_tree_preload( GFP_TEMPORARY )
		int retval = radix_tree_insert( 
			&inscmp_tree,
			(unsigned long) normal_distri[i],
			 dummy);
		if (retval == 0 ||
			retval == -EEXIST) {
			*success_count += 1;
		} else {
			return retval;
		}
		//radix_tree_proload_end( )
	}
	return 0;
}
