#
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# GPL Licence
#------------------------------------------------------------------------
#
# Facility:
#     deqdip 
#
# Name:
#     Makefile
#
# Description:
#     Build deqdip decache protocol
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

EXTRA_CFLAGS =-Wno-unused-function

# use rule to make the .ko module file
obj-m += km_deqdip.o 

km_deqdip-objs := km_c_deqdip.o km_s_deqdip.o

ERLRTS := $(shell ls -d /usr/lib64/erlang/erts*)
ERLH := $(ERLRTS)/include

all:    nif 
	make CFLAGS="-Wno-unused-function" -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
# also do the following

nif:
# make erlang NIF and optional deqdipctl utility only
	gcc -I $(ERLH)  -fPIC -shared -o nif_deqdip.so nif_deqdip.c
	sudo chmod +g nif_deqdip.so
#
	gcc -fPIC -shared  -o deqdipctl deqdipctl.c
	sudo chmod +g deqdipctl

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f km_deqdip.der km_deqdip.priv
	rm -f *.o
	rm -f deqdipctl km_deqdip.ko km_deqdipctl.so nif_deqdip.so

sign:
# sign the module to avoid complaints
	openssl req -new -x509 -newkey rsa:2048 -keyout km_deqdip.priv -outform DER -out km_deqdip.der -nodes -days 36500 -subj "/CN=Descr"
	sudo /usr/src/kernels/$(shell uname -r)/scripts/sign-file sha256 ./km_deqdip.priv ./km_deqdip.der km_deqdip.ko

install:
# 	run in a shell so that any mod command errors dont halt Makefile
	$(shell sudo rmmod km_deqdip.ko >/dev/null 2>&1)
	$(shell sudo insmod km_deqdip.ko)
	@echo -e "\n**\n**Advisory (km_deqdip) : new kernel module 'km_deqdip' loaded.\n**\n"
	sudo cp deqdipctl /usr/bin
	sudo chmod +s /usr/bin/deqdipctl
	@echo -e "\n**\n**Advisory (deqdip) : /usr/bin/deqdipctl optional utility now has suid permission.\n**\n"

