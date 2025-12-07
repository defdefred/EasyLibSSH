# EasyLibSSH - LibSSH made easy for ESP32
Thanks to the wonderful [ewpa/LibSSH-ESP32](https://github.com/ewpa/LibSSH-ESP32) port.
## Use cases
- Using ssh/Putty to connect securely to your ESP32 and command your project via a CLI or TUI interface.
- Making a GUI interface with using libssh to connect securely to your ESP32 and command it.

## Hardware & Software
Any ESP32 board flashed with Arduino GUI or [CLI](https://github.com/defdefred/EasyLibSSH/blob/main/README_Arduino.md).
```
/dev/ttyACM0 serial   Serial Port (USB) LOLIN S2 Mini esp32:esp32:lolin_s2_mini esp32:esp32
```
Last tested version: LibSSH-ESP32@5.7.0

## Configuration
To print all libssh step to establish the secure connection.
```
// Display errors via serial
// #define EASYLIBSSH_DEBUG
```
You should customize SSH private host key for each microcontroller board.
```
// Set hostkey for libSSH
const char *EASYLIBSSH_HOSTKEY = "-----BEGIN OPENSSH PRIVATE KEY-----\nb3BlbnNzaC1rZXktdjEAAAAABG
↪5vbmUAAAAEbm9uZQAAAAAAAAABAAAAMwAAAAtzc2gtZWQyNTUxOQAAACDGogjt/r8zbECmh6lm1UX6Gx+lAmbfG7PsFHTNkQ
↪iYQAAAAJDQkgeZ0JIHmQAAAAtzc2gtZWQyNTUxOQAAACDGogjt/r8zbECmh6lm1UX6Gx+lAmbfG7PsFHTNkQiYQAAAAEAhjp
↪XJ4AgPfRC8PuuNIEq0itAFa2pxG0S5iMEe0iAY/saiCO3+vzNsQKaHqWbVRfobH6UCZt8bs+wUdM2RCJhAAAAAAAECAwQFBg
↪cICQoLDA0=\n-----END OPENSSH PRIVATE KEY-----";
```
Public key authorisation is the only one allowed.
```
// Set an array of authorized_key for libSSH
const uint8_t EASYLIBSSH_NBAUTHKEY = 2;
const char *EASYLIBSSH_TYPEKEY[] = { "ssh-ed25519",
                                     "ssh-ed25519" };
const char *EASYLIBSSH_AUTHKEY[] = { "AAAAC3NzaC1lZDI1NTE5AAAAIPtooFfereunifeni34345352y/qI2Iys6k
↪kMo6mUHWq",
                                     "AAAAC3NzaC1lZDI1NTE5AAAAIPtooFfcMRdCSSouYMrBpXVG2y/qI2Iys6k
↪kMo6mUHWq" };

```
You need to include the library and to customize the name of the ssh channel.
```
#include "easylibssh.h"
// choose the name of your ssh_channel
ssh_channel chan;
```
Data to connect to your confidential WiFi management network. 
```
// Set local WiFi credentials
const char *configSTASSID = "mySID";
const char *configSTAPSK = "mySECRET";
```
## Troubleshooting
If you encountered a stack error message like:
```
***ERROR*** A stack overflow in task loopTask has been detected.
Core  0 register dump:
MEPC    : 0x40381d70  RA      : 0x403864e6  SP      : 0x3fc95360  GP      : 0x3fc8da00  
TP      : 0x3fc64438  T0      : 0x4005890e  T1      : 0x0000000f  T2      : 0x00000001  
S0/FP   : 0x3fc95380  S1      : 0x3fc95380  A0      : 0x3fc95380  A1      : 0x3c0f0078  
A2      : 0x0000000b  A3      : 0x3fc953ae  A4      : 0x00000001  A5      : 0x3fc99000  
A6      : 0x3fc9de68  A7      : 0x0003e000  S2      : 0x00001881  S3      : 0x3fc98edc  
S4      : 0x3fca03a4  S5      : 0xffffffff  S6      : 0x3fc9e72c  S7      : 0x3fc9e52c  
S8      : 0x3fc9ed2c  S9      : 0x00001000  S10     : 0x3fc99000  S11     : 0x3fca040c  
T3      : 0x00000000  T4      : 0x00000000  T5      : 0x00000001  T6      : 0x00000000  
MSTATUS : 0x00001801  MTVEC   : 0x40380001  MCAUSE  : 0x00000007  MTVAL   : 0x00000000  
MHARTID : 0x00000000  
```
You need to increase the LoopTask stack size with:
```
// This sets Arduino Stack Size - comment this line to use default 8K stack size
SET_LOOP_TASK_STACK_SIZE(16 * 1024);  // 16KB

```
## Projects using EasyLibSSH
- EasyLibSSH: An example is provided, printing "It Works!" to the ssh client and resending back every strokes. "~." to quit.
- [Remotty](https://github.com/defdefred/Remotty): Remotte SSH to Serial USB access.
- More: to come...

## Usefull links
https://github.com/arduino/arduino-cli/releases

https://github.com/ewpa/LibSSH-ESP32

https://www.chiark.greenend.org.uk/~sgtatham/putty/

https://www.openssh.com/

https://www.libssh.org/

https://www.rfc-editor.org/rfc/rfc4252#section-7
