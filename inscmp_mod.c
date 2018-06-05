#include "inscmp_mod.h"

unsigned normal_distri[DISTRI_SIZE];

static void fill_uniform( unsigned *uniform, int unif_size ) {
	int i;
	for (i = 0; i < unif_size; ++i) {
		unsigned rnd;
		get_random_bytes( &rnd, sizeof rnd );
		rnd %= DISTRI_SIZE;
		
		uniform[i] = rnd;
		//printk( KERN_INFO "Got random number %u", uniform[i] );
	}
}

static void approx_fill_normal( void ) {
	int i;
	for (i = 0; i < DISTRI_SIZE; ++i) {
		int j, normal_rnd;
		
		unsigned uniform[APPROX_ORDER];
		fill_uniform( uniform, APPROX_ORDER );
		
		for (j = 0, normal_rnd = 0; j < APPROX_ORDER; ++j) {
			normal_rnd += uniform[j];
		}
		//Get the integer quotient
		normal_rnd = normal_rnd / APPROX_ORDER;
		normal_distri[i] = normal_rnd;
		//printk( KERN_INFO "Got random number %u", normal_distri[i] );
	}
}

int init_module( void ) {
	int radix_success_count;
    printk( KERN_INFO "INSCMP Loading\n" );
    
    approx_fill_normal( );
    test_radix_tree( &radix_success_count );
	//fill_uniform( );
    return 0;
}

void cleanup_module( void ) {

    printk( KERN_INFO "INSCMP Unloading\n" );
}
