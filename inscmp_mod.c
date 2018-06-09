#include "inscmp_mod.h"
#define ADD_TESTS 1


unsigned normal_distri[DISTRI_SIZE];


RADIX_TREE(inscmp_tree, GFP_KERNEL);
static char *dummy = "DUMMY VALUE"; //all entries will point to this

int test_radix_tree( int *success_count ) {
	//for key in normal distribution
	int i;
	*success_count = 0;
	for (i = 0; i < DISTRI_SIZE; ++i) {
		//radix_tree_preload( GFP_KERNEL )
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

#ifdef ADD_TESTS
static void test_radix_tree_lookup_lastval( void **lastval ) {
	*lastval = radix_tree_lookup( 
		&inscmp_tree,
		normal_distri[DISTRI_SIZE-1] );
}
#endif

DEFINE_HASHTABLE(inscmp_htbl, HASHTBL_BITS);

int test_hashtable( int *success_count ) {
	int i;
	*success_count = 0;
	//hash_init(inscmp_htbl, HASHTBL_BITS);
	hash_init(inscmp_htbl);
	printk( KERN_INFO "Hashtable had initialized\n" );
	for (i = 0; i < DISTRI_SIZE; ++i) {
		inscmp_object obje = { 
			.key = normal_distri[i],
			.name = "DUMMY NAME"
		};
		(void) hash_add( inscmp_htbl, &obje.node, obje.key );
		*success_count += 1;
	}
	return 0;
}

#ifdef ADD_TESTS
static void test_htbl_lookup( void **val_found ) {
	unsigned key = normal_distri[DISTRI_SIZE-1];
	inscmp_object *obje;
	hash_for_each_possible(inscmp_htbl, obje, node, key) {
		if ( obje->key == key) {
			*val_found = obje->name;
			return;
		}
	}
}
#endif

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
	int htbl_success_count;
#ifdef ADD_TESTS
	char *radix_lastval;
	char *htbl_lastval;
#endif
    printk( KERN_INFO "INSCMP Loading\n" );
    
    approx_fill_normal( );
    //START MEASUREING WITH RADIX TREE
    test_radix_tree( &radix_success_count );
#ifdef ADD_TESTS
	test_radix_tree_lookup_lastval( (void **) &radix_lastval );
	if (radix_lastval == NULL) {
		printk( KERN_INFO "INSCMP Radix tree LAST VALUE failed\n");
	}
	printk( KERN_INFO "INSCMP Radix tree LAST VALUE %s\n", radix_lastval );
#endif
    printk( KERN_INFO "INSCMP Radix Tree success count %d\n", 
		radix_success_count);
	//END MEASUREING WITH RADIX TREE
	
	//START MEASUREING WITH HASH TABLE
	test_hashtable( &htbl_success_count );
#ifdef ADD_TESTS
	test_htbl_lookup( (void **) &htbl_lastval );
	printk( KERN_INFO "INSCMP Hashtable LAST VALUE %s\n", htbl_lastval );
#endif
	printk( KERN_INFO "INSCMP Hashtable success count %d\n", htbl_success_count );
	//END MEASUREING WITH HASH TABLe
	
	//fill_uniform( );
    return 0;
}

void cleanup_module( void ) {

    printk( KERN_INFO "INSCMP Unloading\n" );
}
MODULE_LICENSE( "GPL" );
