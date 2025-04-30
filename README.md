# Embedded-9

This project demonstrates building and running an embedded program on **VxWorks 7** for the **Raspberry Pi 4B**. The main source file is `modules/led.c`.

---

## 📁 Project Structure

- **Main Program**: `modules/led.c`
- **Library**: `gpioLib/gpioLib.c`
- **Toolchain**: `wrsdk-vxworks7-raspberrypi4b`

---

## ⚙️ Requirements

- [`pyftpdlib`](https://pypi.org/project/pyftpdlib/)
- `wrsdk-vxworks7-raspberrypi4b` (Wind River SDK for VxWorks 7)
- A Raspberry Pi 4B running VxWorks 7
- A Linux development host

---

# 🚀 How to Run

## 1. On the Linux Development System

### Source the SDK environment
$ source wrsdk-vxworks7-raspberrypi4b/sdkenv.sh

### Change to the project directory
cd to this folder

### Compile the code
$CC -dkm gpioLib/gpioLib.c modules/led.c -o modules/led.o

### Start an FTP server for VxWorks to access the files
sudo python -m pyftpdlib -p 21 -u target -P vxTarget -d . &

## 2. On the VxWorks Target

1. Mount the FTP server directory:

```vxworks

Replace 192.168.10.191 with the IP address of your Linux host
-> netDevCreate ("/wrs", "192.168.10.191", 1)
	-> change ip to your linux system's ip

2. Navigate to the mounted directory and load the module

[vxWorks *]# cd /wrs
[vxWorks *]# pwd/wrs
[vxWorks *]# cd /modules
[vxWorks *]# ls
led.c  led.o
[vxWorks *]# ld "led.o"
[vxWorks *]# C
[vxWorks *]# sp start
