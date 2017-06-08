#include "FS.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);
  Serial.println("");

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
    if (readValue == 'r')
    {
      ReadTextFileAll();
    }
    else if (readValue == 'w')
    {
      unsigned long millisValue = millis();
      Serial.print("Wrote: ");
      Serial.println(millisValue);
      WriteTextFile(String(millisValue));
    }
    else if (readValue == 'f')
    {
      SPIFFS.format();
      Serial.println("formatted.");
    }
  }
}


int WriteTextFile(String writeText)
{
  File fd = SPIFFS.open("/tmp.txt", "a");
  if (!fd) {
    Serial.println("file open error.");
    return -1;
  }
  fd.println(writeText);
  fd.close();
  return 0;
}

int ReadTextFileAll()
{
  File fd = SPIFFS.open("/tmp.txt", "r");
  if (!fd) {
    Serial.println("file open error.");
    return -1;
  }
  Serial.print("filesize= ");
  Serial.println(fd.size());

  String str = fd.readStringUntil('\0');
  Serial.println(str);
  Serial.println("");
  
  fd.close();
  return 0;
}