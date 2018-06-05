#ifndef INSCMP_MOD_H
#define INSCMP_MOD_H
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/random.h>

#define DISTRI_SIZE 100
#define APPROX_ORDER 12

extern unsigned normal_distri[DISTRI_SIZE];
int test_radix_tree( int * );
#endif
