## Arduino configuration
I don't use arduino-ide, it is way to bloaded and slow. I prefer arduino-cli and vim :-).
You can get it from https://github.com/arduino/arduino-cli/releases. It is only a big executable binary file:
```
user@minipc1:~/Downloads$ tar ztfv arduino-cli_0.29.0_Linux_64bit.tar.gz
-rwxr-xr-x root/root  27425400 2022-11-17 10:22 arduino-cli
-rw-r--r-- runner/docker 35149 2022-11-17 10:21 LICENSE.txt
```
Increase the default network timeout
```
wize@minipc:~/Arduino$ ./arduino-cli config set network.connection_timeout 600s
```
Don't forget to install / upgrade the board ESP32:
```
user@minipc1:~/Arduino$ ./arduino-cli core update-index
Downloading index: package_index.tar.bz2 downloaded
user@minipc1:~/Arduino$ ./arduino-cli core search esp32
ID          Version   Name
esp32:esp32 1.0.5-rc4 ESP32 Arduino
user@minipc1:~/Arduino$ ./arduino-cli core upgrade esp32:esp32
Error during upgrade: Platform '' is already at the latest version
```
Don't forget to install / upgrade the library LibSSH-ESP32:
```
user@minipc1:~/Arduino$ ./arduino-cli lib search libssh
Downloading index: library_index.tar.bz2 downloaded
Name: "LibSSH-ESP32"
  Author: Ewan Parker
  Maintainer: Ewan Parker
  Sentence: SSH client and SSH server library for ESP32 based on libssh.
  Paragraph: This is an ESP32/FreeRTOS port of the libssh.org SSH Library created originally for Linux, Unix or Windows.  Several examples are included, for example an SSH client, SSH server, SCP client, key generator, and over-the-air (OTA) flashing using SCP.
  Website: https://www.ewan.cc/?q=node/157
  Category: Communication
  Architecture: esp32
  Types: Contributed
  Versions: [0.2.0, 1.0.0, 1.0.1, 1.1.0, 1.1.1, 1.1.2, 1.1.3, 1.2.0, 1.2.1, 1.2.2, 1.2.3, 1.3.0, 1.4.0, 1.4.1, 2.1.0, 2.2.0, 3.0.0, 3.0.1]
  Provides includes: libssh_esp32.h

user@minipc1:~/Arduino$ ./arduino-cli lib upgrade libSSH-ESP32
Error upgrading libraries: Library 'libSSH-ESP32' not found
user@minipc1:~/Arduino$ ./arduino-cli lib upgrade LibSSH-ESP32
Downloading LibSSH-ESP32@3.0.1...
LibSSH-ESP32@3.0.1 downloaded
Installing LibSSH-ESP32@3.0.1...
Replacing LibSSH-ESP32@3.0.0 with LibSSH-ESP32@3.0.1...
Installed LibSSH-ESP32@3.0.1
```

Compiling, flashing monitoring is easy and fast with a little shell script:
```
user@minipc1:~/Arduino$ cat ./do
./arduino-cli compile -b esp32:esp32:esp32 $1 || exit
./arduino-cli upload -p /dev/ttyUSB0 -b esp32:esp32:esp32 $1 || exit
./arduino-cli monitor -p /dev/ttyUSB0 -b esp32:esp32:esp32 -c 115200,off,8,none,off,1
```
Example:
```
user@minipc1:~/Arduino$ ./do remotty
Sketch uses 972922 bytes (74%) of program storage space. Maximum is 1310720 bytes.
Global variables use 52904 bytes (16%) of dynamic memory, leaving 274776 bytes for local variables. Maximum is 327680 bytes.

Used library Version Path
LibSSH-ESP32 3.0.0   /home/user/Arduino/libraries/LibSSH-ESP32
WiFi         1.0     /home/user/.arduino15/packages/esp32/hardware/esp32/1.0.5-rc4/libraries/WiFi

Used platform Version   Path
esp32:esp32   1.0.5-rc4 /home/user/.arduino15/packages/esp32/hardware/esp32/1.0.5-rc4

esptool.py v3.0-dev
Serial port /dev/ttyUSB0
Connecting.....
Chip is ESP32-D0WDQ6-V3 (revision 3)
Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
Crystal is 40MHz
MAC: 3c:61:05:0c:aa:7c
Uploading stub...
Running stub...
Stub running...
Changing baud rate to 921600
Changed.
Configuring flash size...
Auto-detected Flash size: 4MB
Compressed 8192 bytes to 47...
Wrote 8192 bytes (47 compressed) at 0x0000e000 in 0.0 seconds (effective 9118.2 kbit/s)...
Hash of data verified.
Compressed 18624 bytes to 12037...
Wrote 18624 bytes (12037 compressed) at 0x00001000 in 0.2 seconds (effective 874.2 kbit/s)...
Hash of data verified.
Compressed 973040 bytes to 602165...
Wrote 973040 bytes (602165 compressed) at 0x00010000 in 9.0 seconds (effective 865.8 kbit/s)...
Hash of data verified.
Compressed 3072 bytes to 128...
Wrote 3072 bytes (128 compressed) at 0x00008000 in 0.0 seconds (effective 7078.2 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...
Monitor port settings:
baudrate=115200
Monitor port settings:
rts=off
Monitor port settings:
bits=8
Monitor port settings:
parity=none
Monitor port settings:
rts=off
Monitor port settings:
stop_bits=1
Connected to /dev/ttyUSB0! Press CTRL-C to exit.
```
After last upgrade, I got stack issue with my projet, si I needed to downgrade th esp32 core.
Searching older core version:
```
wize@minipc:~/Arduino$ ./arduino-cli core search esp32 -a
ID            Version                  Name
arduino:esp32 2.0.10                   Arduino ESP32 Boards
arduino:esp32 2.0.11                   Arduino ESP32 Boards
arduino:esp32 2.0.12                   Arduino ESP32 Boards
arduino:esp32 2.0.13                   Arduino ESP32 Boards
arduino:esp32 2.0.18-20240930.arduino3 Arduino ESP32 Boards
arduino:esp32 2.0.18-arduino.5         Arduino ESP32 Boards
esp32:esp32   1.0.0                    esp32
esp32:esp32   1.0.1                    esp32
esp32:esp32   1.0.2                    esp32
esp32:esp32   1.0.3                    esp32
esp32:esp32   1.0.4                    esp32
esp32:esp32   1.0.5                    esp32
esp32:esp32   1.0.6                    esp32
esp32:esp32   2.0.0                    esp32
esp32:esp32   2.0.1                    esp32
esp32:esp32   2.0.2                    esp32
esp32:esp32   2.0.3                    esp32
esp32:esp32   2.0.4                    esp32
esp32:esp32   2.0.5                    esp32
esp32:esp32   2.0.6                    esp32
esp32:esp32   2.0.7                    esp32
esp32:esp32   2.0.8                    esp32
esp32:esp32   2.0.9                    esp32
esp32:esp32   2.0.10                   esp32
esp32:esp32   2.0.11                   esp32
esp32:esp32   2.0.12                   esp32
esp32:esp32   2.0.13                   esp32
esp32:esp32   2.0.14                   esp32
esp32:esp32   2.0.15                   esp32
esp32:esp32   2.0.16                   esp32
esp32:esp32   2.0.17                   esp32
esp32:esp32   3.0.0                    esp32
esp32:esp32   3.0.1                    esp32
esp32:esp32   3.0.2                    esp32
esp32:esp32   3.0.3                    esp32
esp32:esp32   3.0.4                    esp32
esp32:esp32   3.0.5                    esp32
esp32:esp32   3.0.6                    esp32
esp32:esp32   3.0.7                    esp32
esp32:esp32   3.1.0                    esp32
esp32:esp32   3.1.1                    esp32
esp32:esp32   3.1.2                    esp32
esp32:esp32   3.1.3                    esp32
esp32:esp32   3.2.0                    esp32
esp32:esp32   3.2.1                    esp32
esp32:esp32   3.3.0                    esp32
esp32:esp32   3.3.1                    esp32
esp32:esp32   3.3.2                    esp32
esp32:esp32   3.3.3                    esp32
esp32:esp32   3.3.4                    esp32
```
Uninstall core and install a specific version:
```
wize@minipc:~/Arduino$ ./arduino-cli core uninstall esp32:esp32
Uninstalling esp32:esp32@3.3.4...
Running pre_uninstall script....
Platform esp32:esp32@3.3.4 uninstalled
Uninstalling esp32:esp32-arduino-libs@idf-release_v5.5-8410210c-v2, tool is no more required...
Running pre_uninstall script....
Tool esp32:esp32-arduino-libs@idf-release_v5.5-8410210c-v2 uninstalled
Uninstalling esp32:esp-x32@2507, tool is no more required...
Running pre_uninstall script....
Tool esp32:esp-x32@2507 uninstalled
Uninstalling esp32:xtensa-esp-elf-gdb@16.3_20250913, tool is no more required...
Running pre_uninstall script....
Tool esp32:xtensa-esp-elf-gdb@16.3_20250913 uninstalled
Uninstalling esp32:esp-rv32@2507, tool is no more required...
Running pre_uninstall script....
Tool esp32:esp-rv32@2507 uninstalled
Uninstalling esp32:riscv32-esp-elf-gdb@16.3_20250913, tool is no more required...
Running pre_uninstall script....
Tool esp32:riscv32-esp-elf-gdb@16.3_20250913 uninstalled
Uninstalling esp32:openocd-esp32@v0.12.0-esp32-20250707, tool is no more required...
Running pre_uninstall script....
Tool esp32:openocd-esp32@v0.12.0-esp32-20250707 uninstalled
Uninstalling esp32:esptool_py@5.1.0, tool is no more required...
Running pre_uninstall script....
Tool esp32:esptool_py@5.1.0 uninstalled
Uninstalling esp32:mkspiffs@0.2.3, tool is no more required...
Running pre_uninstall script....
Tool esp32:mkspiffs@0.2.3 uninstalled
Uninstalling esp32:mklittlefs@4.0.2-db0513a, tool is no more required...
Running pre_uninstall script....
Tool esp32:mklittlefs@4.0.2-db0513a uninstalled
Uninstalling arduino:dfu-util@0.11.0-arduino5, tool is no more required...
Running pre_uninstall script....
Tool arduino:dfu-util@0.11.0-arduino5 uninstalled
```
Try version 2.0.17
```
wize@minipc:~/Arduino$ ./arduino-cli core install esp32:esp32@2.0.17
Téléchargement des paquets...
esp32:xtensa-esp32-elf-gcc@esp-2021r2-patch5-8.4.0 esp32:xtensa-esp32-elf-gcc@esp-2021r2-patch5-8.4.0 déjà téléchargé
esp32:xtensa-esp32s2-elf-gcc@esp-2021r2-patch5-8.4.0 esp32:xtensa-esp32s2-elf-gcc@esp-2021r2-patch5-8.4.0 déjà téléchargé
esp32:xtensa-esp32s3-elf-gcc@esp-2021r2-patch5-8.4.0 esp32:xtensa-esp32s3-elf-gcc@esp-2021r2-patch5-8.4.0 déjà téléchargé
esp32:xtensa-esp-elf-gdb@11.2_20220823 esp32:xtensa-esp-elf-gdb@11.2_20220823 déjà téléchargé
esp32:riscv32-esp-elf-gcc@esp-2021r2-patch5-8.4.0 esp32:riscv32-esp-elf-gcc@esp-2021r2-patch5-8.4.0 déjà téléchargé
esp32:riscv32-esp-elf-gdb@11.2_20220823 esp32:riscv32-esp-elf-gdb@11.2_20220823 déjà téléchargé
esp32:openocd-esp32@v0.12.0-esp32-20230921 esp32:openocd-esp32@v0.12.0-esp32-20230921 déjà téléchargé
esp32:esptool_py@4.5.1 esp32:esptool_py@4.5.1 déjà téléchargé
esp32:mkspiffs@0.2.3 esp32:mkspiffs@0.2.3 déjà téléchargé
esp32:mklittlefs@3.0.0-gnu12-dc7f933 esp32:mklittlefs@3.0.0-gnu12-dc7f933 déjà téléchargé
arduino:dfu-util@0.11.0-arduino5 arduino:dfu-util@0.11.0-arduino5 déjà téléchargé
esp32:esp32@2.0.17 downloaded                                                                                                                                                                                        
Installing esp32:xtensa-esp32-elf-gcc@esp-2021r2-patch5-8.4.0...
Configuring tool....
esp32:xtensa-esp32-elf-gcc@esp-2021r2-patch5-8.4.0 installed
Installing esp32:xtensa-esp32s2-elf-gcc@esp-2021r2-patch5-8.4.0...
Configuring tool....
esp32:xtensa-esp32s2-elf-gcc@esp-2021r2-patch5-8.4.0 installed
Installing esp32:xtensa-esp32s3-elf-gcc@esp-2021r2-patch5-8.4.0...
Configuring tool....
esp32:xtensa-esp32s3-elf-gcc@esp-2021r2-patch5-8.4.0 installed
Installing esp32:xtensa-esp-elf-gdb@11.2_20220823...
Configuring tool....
esp32:xtensa-esp-elf-gdb@11.2_20220823 installed
Installing esp32:riscv32-esp-elf-gcc@esp-2021r2-patch5-8.4.0...
Configuring tool....
esp32:riscv32-esp-elf-gcc@esp-2021r2-patch5-8.4.0 installed
Installing esp32:riscv32-esp-elf-gdb@11.2_20220823...
Configuring tool....
esp32:riscv32-esp-elf-gdb@11.2_20220823 installed
Installing esp32:openocd-esp32@v0.12.0-esp32-20230921...
Configuring tool....
esp32:openocd-esp32@v0.12.0-esp32-20230921 installed
Installing esp32:esptool_py@4.5.1...
Configuring tool....
esp32:esptool_py@4.5.1 installed
Installing esp32:mkspiffs@0.2.3...
Configuring tool....
esp32:mkspiffs@0.2.3 installed
Installing esp32:mklittlefs@3.0.0-gnu12-dc7f933...
Configuring tool....
esp32:mklittlefs@3.0.0-gnu12-dc7f933 installed
Installing arduino:dfu-util@0.11.0-arduino5...
Configuring tool....
arduino:dfu-util@0.11.0-arduino5 installed
Installing platform esp32:esp32@2.0.17...
Configuration de la plateforme....
Platform esp32:esp32@2.0.17 installed
```

