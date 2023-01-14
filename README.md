# EasyLibSSH - LibSSH made easy for ESP32
## Use cases
Using ssh/Putty to connect securely to your ESP32 and command your project via a CLI or TUI interface.

## Hardware & Software
Any ESP32 board with usb port and flashed with Arduino (https://github.com/defdefred/Remotty/blob/main/README_Arduino.md)

## Configuration
### Debuging
To print all libssh step to establish the secure connection.
```
// Display errors via serial
// #define EASYLIBSSH_DEBUG
```
You should customize SSH private host key for each microcontroller board.
```
// Set remotty hostkey
const char *configHOSTKEY = "-----BEGIN OPENSSH PRIVATE KEY-----\nb3BlbnNzaC1rZXktdjEAAAAABG5vbmUAA
↪AAEbm9uZQAAAAAAAAABAAAAMwAAAAtzc2gtZWQyNTUxOQAAACDGogjt/r8zbECmh6lm1UX6Gx+lAmbfG7PsFHTNkQiYQAAAAJD
↪QkgeZ0JIHmQAAAAtzc2gtZWQyNTUxOQAAACDGogjt/r8zbECmh6lm1UX6Gx+lAmbfG7PsFHTNkQiYQAAAAEAhjpXJ4AgPfRC8P
↪uuNIEq0itAFa2pxG0S5iMEe0iAY/saiCO3+vzNsQKaHqWbVRfobH6UCZt8bs+wUdM2RCJhAAAAAAAECAwQFBgcICQoLDA0=\n-
↪----END OPENSSH PRIVATE KEY-----";
```
Public key authorisation is the only one allowed.
```
// Set an array of authorized_key for libSSH
const uint8_t EASYLIBSSH_NBAUTHKEY = 2;
const char *EASYLIBSSH_TYPEKEY[] = { "ssh-ed25519",
                                     "ssh-ed25519" };
const char *EASYLIBSSH_AUTHKEY[] = { "AAAAC3NzaC1lZDI1NTE5AAAAIPtooFfereunifeni34345352y/qI2Iys6kkMo6mUHWq",
                                     "AAAAC3NzaC1lZDI1NTE5AAAAIPtooFfcMRdCSSouYMrBpXVG2y/qI2Iys6kkMo6mUHWq" };

```
You need include the library and to customize the name of the ssh channel.
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

## Projects using EasyLibSSH
- EasyLibSSH: An example is provided, printing "It Works!" to the ssh client and resending back every strokes. "~." to quit.
- ![Remotty](https://github.com/defdefred/Remotty): Remotte SSH to Serial USB access.
- More: to come...

## Usefull links
https://github.com/arduino/arduino-cli/releases

https://github.com/ewpa/LibSSH-ESP32

https://www.chiark.greenend.org.uk/~sgtatham/putty/

https://www.openssh.com/

https://www.libssh.org/

https://www.rfc-editor.org/rfc/rfc4252#section-7
