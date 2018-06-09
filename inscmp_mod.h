#ifndef INSCMP_MOD_H
#define INSCMP_MOD_H
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/random.h>
#include <linux/radix-tree.h>
#include <linux/gfp.h>
#include <linux/hashtable.h>
#include <linux/types.h>

#define DISTRI_SIZE 100000
#define APPROX_ORDER 12 // USED FOR GETTING NORMAL DIS. FROM UNIFORM
#define HASHTBL_BITS (17) //LOG2( DISTRI_SIZE )

int test_radix_tree( int * );
int test_hashtable( int * );

typedef struct {
	unsigned key;
	char name[24];
	
	struct hlist_node node;
} inscmp_object;
#endif
