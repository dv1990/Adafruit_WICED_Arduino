/*
  AsyncHTTP Example:
  
  1.  Start the HTTP server via the python script in 'AsyncHTTP/http_server'
        $ cd http_server
        $ sudo python server.py   // port 80 - require root privileges
        or
        $ python server.py 8000   // port 8000
  2.  Make a note of your local IP address (the method to determine your IP
      address will depend on your operating system)
  3.  Add your AP details via WLAN_SSID and WLAN_PASS in this sketch
  4.  Add the URL of the HTTP server you started to the URL in this sketch,
      using the IP address of your machine, the port number of started server
      (optional, default is 80) and the filename to load.
      For example:
        "192.168.1.1/text_1KB.txt"   // Default port 80
        "192.168.1.1:8000/text.100B.txt"
  5.  Run the example and open serial monitor to see the async HTTP request
  6.  Compare the CRC of downloaded file with the CRC generated by 'crc32.py'
      $ python crc32.py <filename>

  author: huynguyen
  
  CRC code by James Bowman: http://excamera.com/sphinx/article-crc.html
 */

#include "adafruit_wifi.h"

#define WLAN_SSID            "SSID"
#define WLAN_PASS            "PASS"

#define URL                  "URL/filename"
#define CONTENT              ""
#define METHOD               GET_METHOD


int wifi_error = -1; // FAIL
unsigned long crc = ~0L;
int first_chunk = 1;

static PROGMEM prog_uint32_t crc_table[16] = {
  0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
  0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
  0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
  0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};

unsigned long crc_update(unsigned long crc, byte data)
{
  byte tbl_idx;
  tbl_idx = crc ^ (data >> (0 * 4));
  crc = pgm_read_dword_near(crc_table + (tbl_idx & 0x0f)) ^ (crc >> 4);
  tbl_idx = crc ^ (data >> (1 * 4));
  crc = pgm_read_dword_near(crc_table + (tbl_idx & 0x0f)) ^ (crc >> 4);
  return crc;
}

/**************************************************************************/
/*!
    @brief  Connect to pre-specified AP

    @return Error code
*/
/**************************************************************************/
int connectAP()
{
  // Attempt to connect to an AP
  Serial.print(F("Attempting to connect to: "));
  Serial.println(WLAN_SSID);

  int error = feather.connectAP(WLAN_SSID, WLAN_PASS);

  if (error == 0)
  {
    Serial.println(F("Connected!"));
  }
  else
  {
    Serial.print(F("Failed! Error: "));
    Serial.println(error, HEX);
  }
  Serial.println("");

  return error;
}

/**************************************************************************/
/*!
    This function is called whenever new data received
*/
/**************************************************************************/
void rxCallback(uint8_t* data, uint16_t data_length, uint16_t available)
{
  Serial.print(F("Data Received!\r\n"));
  Serial.println((char*)data);

  char* p_data = NULL;
  if (first_chunk == 1)
  {
    p_data = strstr((char*)data, "\r\n\r\n");
    p_data += 4;
    first_chunk = 0;
  }
  else
  {
    p_data = (char*)data;
  }

  while (*p_data)
    crc = crc_update(crc, *p_data++);
}

/**************************************************************************/
/*!
    @brief  The setup function runs once when reset the board
*/
/**************************************************************************/
void setup()
{
  // If you want to use LED for debug
  pinMode(BOARD_LED_PIN, OUTPUT);
  
  // wait for Serial
  while (!Serial) delay(1);

  Serial.println(F("HTTP Example\r\n"));
  
  feather.addHttpDataReceivedCallBack(rxCallback);
  wifi_error = connectAP();
}

/**************************************************************************/
/*!
    @brief  The loop function runs over and over again forever
*/
/**************************************************************************/
void loop() {
  // put your main code here, to run repeatedly
  Serial.println(F("Toggle LED"));
  togglePin(BOARD_LED_PIN);
  
  if (wifi_error == 0)
  {
    int http_error = -1;
    if ( (http_error = feather.asyncHttpRequest(URL, CONTENT, METHOD) ) != 0)
    {
      Serial.print(F("Error: "));
      Serial.println(http_error, HEX);
    }
    else
    {
      crc = ~crc;
      Serial.print(F("\r\nCRC = "));
      Serial.println(crc, HEX);
    }
  }

  first_chunk = 1;
  crc = ~0L;
  Serial.println(F("\r\n"));
  delay(10000);
}