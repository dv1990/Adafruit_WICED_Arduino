# 0.6.0

- Increase Arduino code size from 128KB to 256KB
- Increase Arduino SRAM from 16KB to 20KB
- rename menu Featherlib (Beta) --> Featherlib (Debug)
- print warning message when Featherlib & Arduino library version are not matched
- fix get TCP peer information when SOCKET is CLOSED
- Move memory allocation for UDP from featherlib to arduino code
- change sdep parameter length from uint16_t to uint32_t
- Debug Feather
	- Retrieve Arduino Heap usage: dbgHeapTotal(), dbgHeapUsed(), dbgHeapFree()
	- Retrieve Featherlib Heap usage: dbgFeatherlibHeapTotal(), dbgFeatherlibHeapFree(), dbgFeatherlibHeapUsed()
	- add printThreadlist() and dbgThreadInfo()
- add AdafruitBase64
- add AdafruitUrlencode
- move AdafruitCrc32 to AdafruitCrypto
- AdafruitTCP : automatically free up resource when disconnected even user does not register disconnect callback
- AdafruitHTTP
	- add get() with keyvalues data support
	- move base64Decode to its own class in AdafruitCrypto
	- move urlencode to its own class
	- add response processing function
		- respParseHeader
		- respStatus
		- respContentLength
- AdafruitTwitter
	- add checkDirectMessage()
	- add setDirectMessageRecvCallback()
- SoftAP support with FeatherAP
	- add setJoinCallback(), setLeaveCallback()
	- add clientNum() clientMAC()
	- add interface properties to AdafruitTCP & AdafruitTCPServer, change constructors accordingly.
	- add interface() to return current bound interface (STATION or SoftAP)
	- add started()
	- enhance AdafruitTCP/AdafruitTCPServer to support both STA & SoftAP interface
	- enhance AdafruitUDP to support both STA & SoftAP interface
	- add APChatServer, APClientRSSI, APTcpServer examples
- AdafruitHTTPServer support
	- Static, Dynamic Page support (SimpleHTTPServer example)
	- Page resource generation with advance page design (D3Graphic example)
	- add tools/pyresource to generate C header for HTTP Server
	- support resource files in SPI Flash
- Enable SPI Flash support with AdafruitFatfs, FatFile, FatDir, FileInfo 

# 0.5.5

- rename HardWire to TwoWire to stay compatible with Arduino
- fix #43 : Implement UDP as buffered stream (enabled by default), can be changed using usePacketBuffering()
- Add .config() to manual set static IP
- Add TLS Mutual Verification support (Client Identity verification) with .tlsSetIdentity()
- "VeriSign Class 3 Public Primary Certification Authority - G5" replace "Starfield Services Root Certificate Authority - G2" for AWS IOT 
- Add AdafruitTwitter to send Tweet, and send Direct Message
- Add AdafruitSHA1 to perform SHA1, and HMAC-SHA1 computation
- AdafruitHTTP
	- Change post() API: will perform URLEncode for Post Values
	- add postWithoutURLencoded(): skip URLEncode for values
	- add postRaw(): post data as binary, useful for binary data.
	- add urlEncode(), urlEncodeLength(), base64Encode() as static method

## Known Issues

- When connecting with TLS Mutual Verification (client verification) such as AWS IOT, if Identity is not set, it will cause an hardfault due to Broadcom SSL library ssl_write_certificate() when handshaking.

# 0.5.2

- Add Servo library suport
- Fix issue where 0xff is misinterpreted as EOF with USBSerial
- Fix EXT GPIO interrupt conflict between Featherlib & Arduino
- Fix #32 PWM only work after 3-5 minutes
- Fix compiling issues with existing library

# 0.5.1

- `Baltimore CyberTrust Root` replace `VeriSign Class 3 Public Primary Certification Authority - G5` in default root certificate list
- Fix #38 `Disconnect callback for MQTT and TCP don't imply that connected() method returns false` 
- Fix #36, #37 : Rework I2C with repeated START for MPL3115A2 sensor and alike.
- Use pre-compiled feather_dfu for Windows
- Fix Linux's rules for USB VID/PID
- Update signed driver for Windows

# Version 0.5.0

- First Release
