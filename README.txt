main program : modules/led.c

# How to run :
## requirements : 
pyftpdlib
wrsdk-vxworks7-raspberrypi4b 
## steps:
(on your linux system)
$ source wrsdk-vxworks7-raspberrypi4b/sdkenv.sh
cd to this folder
$CC -dkm gpioLib/gpioLib.c modules/led.c -o modules/led.o
sudo python -m pyftpdlib -p 21 -u target -P vxTarget -d . &

(on vxworks)
-> netDevCreate ("/wrs", "192.168.10.191", 1)
	> change ip to your linux system's ip
-> cmd
[vxWorks *]# cd /wrs
[vxWorks *]# pwd
/wrs
[vxWorks *]# cd /modules
[vxWorks *]# ls
led.c
led.o
[vxWorks *]# ld "led.o"
[vxWorks *]# C
-> sp start