/*********************************************************************
 This is an example for our Feather WIFI modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

#include <adafruit_feather.h>
#include "adafruit_spiflash.h"

/* This example use SpiFlash create and write to file
 */

// the setup function runs once when you press reset or power the board
void setup() 
{
  Serial.begin(115200);

  // Wait for the USB serial to connect. Needed for native USB port only.
  while (!Serial) delay(1);
    
  Serial.println("SPI Flash Write File Example");

  // Initialize SPI Flash
  SpiFlash.begin();

  // Print root's contents
  printRootDir();

  Serial.println();
  Serial.print("Enter Filename to create or append: ");
}

// the loop function runs over and over again forever
void loop() 
{
  // Waiting until there is any user input and echo
  char* input = getUserInput();
  Serial.println(input);

  FatFile file;
  if  ( !file.open(input, FAT_FILE_WRITE | FAT_FILE_OPEN_APPEND ) )
  {
    Serial.println("Incorrect filename");  
  }else
  {
    Serial.print(input);
    Serial.println(" file created");  
    Serial.print("Enter file contents or 'exit' to close: ");

    // Get file contents
    input = getUserInput();
    
    while( strcmp("exit", input) )
    { 
      // echo   
      Serial.println();
      Serial.print(input);

      // write to file, append new line each input
      file.print(input);
      file.println();

      input = getUserInput();
    }
    
    file.close();
  }

  // Print root's contents
  printRootDir();

  Serial.println();
  Serial.print("Enter Filename to create or append: ");
}

/**************************************************************************/
/*!
    @brief  Print directory contents
*/
/**************************************************************************/
void printRootDir(void)
{
  // Open the input folder
  FatDir dir;  
  dir.open("/");

  // Print root symbol
  Serial.println("/");
  
  // File Entry Information which hold file attribute and name
  FileInfo finfo;

  // Loop through the directory  
  while( dir.read(&finfo) )
  {
    Serial.print("|_ ");
    Serial.print( finfo.name() );

    if ( finfo.isDirectory() ) 
    {
      Serial.println("/");
    }else
    {      
      // Print padding, file size starting from position 30
      for (int i=strlen(finfo.name()); i<30; i++) Serial.print(' ');

      // Print at least one extra space in case current position > 30
      Serial.print(' ');

      // Print size in KB
      Serial.print( finfo.size() / 1024 );
      Serial.println( " KB");
    }
  }

  dir.close();
}

/**************************************************************************/
/*!
    @brief  Get user input from Serial
*/
/**************************************************************************/
char* getUserInput(void)
{
  static char inputs[128+1];
  memset(inputs, 0, sizeof(inputs));

  // wait until data is available
  while( Serial.available() == 0 ) { delay(1); }

  uint8_t count=0;
  do
  {
    count += Serial.readBytes(inputs+count, 64);
  } while( (count < 64) && Serial.available() );

  return inputs;
}
