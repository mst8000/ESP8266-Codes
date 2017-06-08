#include "FS.h"

#define FILENAME  "/tmp.txt"

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();

  bool res = SPIFFS.begin();
  if (!res) {
    Serial.println("SPIFFS.begin fail");
    return;
  }
}

void loop() {
  int readValue = 0;

  if (Serial.available() > 0)
  {
    readValue = Serial.read();

    // Read TextFile
    if (readValue == 'r')
    {
      ReadTextFileAll();
    }

    // Text Write
    else if (readValue == 'w')
    {
      unsigned long millisValue = millis();
      Serial.print("Wrote: ");
      Serial.println(millisValue);
      WriteTextFile(String(millisValue));
    }

    // Format FileSystem
    else if (readValue == 'f')
    {
      SPIFFS.format();
      Serial.println("formatted.");
    }
  }
}

// Write TextFile
int WriteTextFile(String writeText)
{
  File fd = SPIFFS.open(FILENAME, "a");
  if (!fd) {
    Serial.println("file open error.");
    return -1;
  }
  fd.println(writeText);
  fd.close();
  return 0;
}

// Read TextFile
int ReadTextFileAll()
{
  File fd = SPIFFS.open(FILENAME, "r");
  if (!fd) {
    Serial.println("file open error.");
    return -1;
  }
  Serial.print("filesize= ");
  Serial.println(fd.size());

  while (fd.available())
  {
    String str = fd.readStringUntil('\n');
    Serial.println(str);
  }  
  Serial.println();
  fd.close();
  return 0;
}
