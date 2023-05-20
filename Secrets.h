#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "home_automation"                         //change this
 
const char WIFI_SSID[] = "PIYUSH";               //change this
const char WIFI_PASSWORD[] = "12345678";           //change this
const char AWS_IOT_ENDPOINT[] = "a2l04cena95ya1-ats.iot.ap-south-1.amazonaws.com";       //change this
 
// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIURbEjB5SoJj69IqI+IymSwRBxWcgwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIzMDQyOTA5Mjcy
OFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAOLNVPBtVoqpo1sop3Qn
wd0z5fo0Czbq74961rFIRICOwbyKZWTIPk73xtnSlvLUBDifcZo97TH6dGMSsbvT
ndE3Ipl/qKK/V6gNCem4rHcDdmauyxPb0106jJlACYvjdwbfOeXBGQfvl/S3Pz9L
gWY2e9Rc46PGY74An0rSTmDxFCeBzmlpBclM/uv715gY5I/Kwsklfwvbj8Hy36E3
QlLXkvIN0QnEbG3CzAjHVr2QaCyIlS0aVFSzOjsi/Xz8IONa0rnx2dfSiHV9rySO
lUWpo418NRVKLM77bWoOJ5Eymfz30b5EuDbTaI7eYgl0ZBsJM2RiL1HBXzUvPoTo
DGsCAwEAAaNgMF4wHwYDVR0jBBgwFoAUY6q4C1Z6Ly3NIz6IXX38coY9EpEwHQYD
VR0OBBYEFJyQyOKpJzWx4/LYg4kQKy4giLPmMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQDCGuQPHTde3HSy/DP2TOGcHSu5
MUqQH+FiiW18/kXkDZwbVylJn9/+8CBOSe1TSDo3qUjdhpDY/ZzsvWyMhjrwxwON
xMiaYDWRkBPVPL00Ev5CotAw2s2zwfUSV7NBtaB8kvYabKN7by3aTNWV2xh0lZzz
6OdGGfrp6q18xjWV3tPg9x0ozS6ZaCpCFzelFq5C9WPfP0gocBDoTIywW0kZgA86
tbuG7y8tcyA/r/kcWMAwBpQnKk/ClHnzbq7Phw2w3iYGQqBLxaXohBpMWLvxPUwg
aqUqinF+GTWkoq9rxNNS77s2upF+mQus2yEc854e77GS13439aFKhC2eEUBt
-----END CERTIFICATE-----

 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpgIBAAKCAQEA4s1U8G1WiqmjWyindCfB3TPl+jQLNurvj3rWsUhEgI7BvIpl
ZMg+TvfG2dKW8tQEOJ9xmj3tMfp0YxKxu9Od0TcimX+oor9XqA0J6bisdwN2Zq7L
E9vTXTqMmUAJi+N3Bt855cEZB++X9Lc/P0uBZjZ71Fzjo8ZjvgCfStJOYPEUJ4HO
aWkFyUz+6/vXmBjkj8rCySV/C9uPwfLfoTdCUteS8g3RCcRsbcLMCMdWvZBoLIiV
LRpUVLM6OyL9fPwg41rSufHZ19KIdX2vJI6VRamjjXw1FUoszvttag4nkTKZ/PfR
vkS4NtNojt5iCXRkGwkzZGIvUcFfNS8+hOgMawIDAQABAoIBAQDMLRuVYmkxZaw5
Ka0uhYgiUlFsYKPj6baGjYhviuaYcWv6BwFmrFpjju5GNC5OJw4xx2BnAe7iOl3C
vxagR87ghOkyFNnEwcrw7+QHs4gXkFdr81nA4/oxCL+AS0UM2VbTKeyeaKrXGRvM
Y5edrKSuVsg9ku4gBz7N0xOUMSX8X/ljP7Nq0k0mbdqYyJP7QqzoxIgv10pJteFm
pa81trQkaMyUoM7xvwm9snivZR57lbJftsgQP7+FmTUJ825jNfwttumLmwF+4UnS
ZP4QDKC1dveKiwTH5FSDleVbeecJAFGQc/6GrJe5Xu+W2AKGt6D3r6y/ctZ64jaW
nUOytwrBAoGBAP2ExVii2UGsKR67bRffxzGLWo/Bv7qyCDVguYgr4tKV+BeoiHaI
fWsNdE7V5PXiI4mST37sTEcvx3SquslF45mQZCjLQySy9Cf72CBafTSvTzVcgUMs
7vDAaqh+zqnx37ykLdhIQmFEhI737UHt2jZlsEOvVoEfVPqu4QlGt5gLAoGBAOUF
nlk0e+/L2Q/F+gLrb0ldHRkRE22yEXmO1fXjeQqYCN4YJkGcAqeJhJ38Od4F2PJq
yI3xCVdZaWbqYk9f+ys6mW3qp0Y74BIEimx1YkRcgaAHC5EEU1GCcmi5sv6ClsOa
rNRAK2uLTxfWs6TLAyVifGo5aijNdHPdK3JKCTkhAoGBAJU8ejtyKbg6Ez6vEEo0
hfrJULc9U5MgSCq71JuvUeerNo8eu64jLMk+80+RJCYGR+stALTzfveMzboE4s2m
4ZM9Z2iINu88lPOQkiqBeiDwbg04djNIGSQJ8P9dHmT2KEHQ19fwuXqureXHVpgv
3vuUos1FQwPhoNGs7nXadir/AoGBAIbxG48mHIx7SOdBWIFV5ZmNkrKNXCw7So6c
ObeLE2vJjxgFlKz91paOsaRA1HvcaCrV/lucFUvxc+he3BQ20pBzE6ovI+Z/KxSS
tlkXhRIQi5QV8pu8t7cELJNGL5BEs76HKaRaNvtD9xNtvyWvNKhXckVIlSN7g00t
mQbbVrnhAoGBAKg5rWsz1BxLNkvgt82wb22iGY+JlKJMysn2uz3uqRcFsGulagCX
f59cheHYG+kW0iFT32DhfKPKmoGZhna+ZM+F6wMNtZxQkHnxG1zNZdCPX1To/II0
2zdN1kZaaNJCDNHHmn7kW4ZpZTNjsu4g6vIszZ8z3YFUpEw/+2iBjirc
-----END RSA PRIVATE KEY-----

 
 
)KEY";