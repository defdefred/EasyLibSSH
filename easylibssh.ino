// Display errors via serial
// #define DEBUG
// #define EASYLIBSSH_DEBUG

// Set hostkey for libSSH
const char *EASYLIBSSH_HOSTKEY = "-----BEGIN OPENSSH PRIVATE KEY-----\nb3BlbnNzaC1rZXktdjEAAAAABG5vbmUAAAAEbm9uZQAAAAAAAAABAAAAMwAAAAtzc2gtZWQyNTUxOQAAACDGogjt/r8zbECmh6lm1UX6Gx+lAmbfG7PsFHTNkQiYQAAAAJDQkgeZ0JIHmQAAAAtzc2gtZWQyNTUxOQAAACDGogjt/r8zbECmh6lm1UX6Gx+lAmbfG7PsFHTNkQiYQAAAAEAhjpXJ4AgPfRC8PuuNIEq0itAFa2pxG0S5iMEe0iAY/saiCO3+vzNsQKaHqWbVRfobH6UCZt8bs+wUdM2RCJhAAAAAAAECAwQFBgcICQoLDA0=\n-----END OPENSSH PRIVATE KEY-----";

// Set an array of authorized_key for libSSH
const uint8_t EASYLIBSSH_NBAUTHKEY = 2;
const char *EASYLIBSSH_TYPEKEY[] = { "ssh-ed25519",
                                     "ssh-ed25519" };
const char *EASYLIBSSH_AUTHKEY[] = { "AAAAC3NzaC1lZDI1NTE5AAAAIPtooFfereunifeni34345352y/qI2Iys6kkMo6mUHWq",
                                     "AAAAC3NzaC1lZDI1NTE5AAAAIPtooFfcMRdCSSouYMrBpXVG2y/qI2Iys6kkMo6mUHWq" };

#include "easylibssh.h"
// choose the name of your ssh_channel
ssh_channel chan;

// Set local WiFi credentials
const char *configSTASSID = "mySID";
const char *configSTAPSK = "mySECRET";
#include "WiFi.h"

#define MAX 2048
char buffer[MAX];

void setup()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.setHostname("EasyLibSSH");  
  WiFi.begin(configSTASSID, configSTAPSK);
  while (WiFi.status() != WL_CONNECTED) delay(1000);

#ifdef DEBUG | EASYLIBSSH_DEBUG
  Serial.begin(115200);
  Serial.println(WiFi.localIP());
#endif

  easylibssh_begin();
}

void loop()
{
  int i;
  chan =  easylibssh_loop_start();

  if ( chan == NULL ) return;

  i=sprintf(buffer, "It Works!\r\n");
  if (i > 0) ssh_channel_write( chan, buffer, i);

  do {
    i=ssh_channel_read_nonblocking(chan, buffer, MAX, 0);
    if (i > 0) ssh_channel_write( chan, buffer, i);
    if (i > 0 && buffer[0] == '\r') ssh_channel_write( chan, "\n", 1);
  } while (ssh_channel_is_open(chan) && !ssh_channel_is_eof(chan));

  easylibssh_loop_end(chan);
}
