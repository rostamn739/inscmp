obj-m += inscmp_mod.o

#inscmp_mod-objs += inscmp_radix.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
