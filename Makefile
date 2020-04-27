# AUTHOR: ISABELA HUTCHINGS
# CLASS: csc 452 summer 2019
# project 2
obj-m += pi_driver.o

KDIR := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc -Wall -o pi_digits pi_digits.c
