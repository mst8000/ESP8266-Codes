#include "FS.h"

#define FILENAME  "/tmp.txt"

// https://github.com/esp8266/Arduino/blob/master/doc/filesystem.rst

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("***  SPIFFS File Manager  ***\n");
  Serial.println("Usage:");
  Serial.println(" r\t Read Text file");
  Serial.println(" w\t Write Text file");
  Serial.println(" f\t Format filesystem\n");
}

void loop() {
  Serial.println("Input: ");
  while (1) {
    if (Serial.available() > 0) {
      int readData = Serial.read();

      // Read TextFile
      if (readData == 'r') {
        FS_ReadTextFileAll(FILENAME);
        break;
      }

      // Write Text
      else if (readData == 'w') {
        //WriteTextFile(FILENAME, "");
        break;
      }

      // Format FileSystem
      else if (readData == 'f') {
        FS_FormatFileSystem();
        break;
      }
    }
  }
}



//Format Filesystem
int FS_FormatFileSystem() {
  // 確認メッセージ表示
  Serial.println("#####################");
  Serial.println("##  !! WORNING !!  ##");
  Serial.println("#####################");
  Serial.println("Are you sure you want to delete All data? (Y/n): ");
  Serial.flush();

  // Serialのバッファ内データをすべて捨てる
  while (Serial.available() > 0) Serial.read();

  // 入力待ち & 確認
  while (1) {
    if (Serial.available() > 0) {
      int readData = Serial.read();

      if (readData == 'Y') {
        // フォーマット実行
        if (!SPIFFS.begin()) {
          Serial.println("SPIFFS Begin Failed");
          return -1;
        } else {
          SPIFFS.format();
          SPIFFS.end();
          Serial.println("SPIFFS Format Complete");
          return 0;
        }
      } else {
        // フォーマット中断
        Serial.println("SPIFFS Format Canceled");
        return -2;
      }
    }
  }
}

// Write TextFile
int FS_WriteTextFile(String filePath, String writeText)
{
  // SPIFFSスタート
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS Begin Failed");
    return -1;
  }

  // ファイルオープン
  File fd = SPIFFS.open(FILENAME, "a");
  if (!fd) {
    Serial.println("SPIFFS File Open Failed");
    return -2;
  }

  // 書き込み実行
  fd.println(writeText);

  // ファイル & SPIFFSクローズ
  fd.close();
  SPIFFS.end();
  return 0;
}


// Read TextFile
int FS_ReadTextFileAll(String filePath)
{
  // SPIFFSスタート
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS Begin Failed");
    return -1;
  }

  // ファイルオープン
  File fd = SPIFFS.open(filePath, "r");
  if (!fd) {
    Serial.println("SPIFFS File Open Failed");
    return -2;
  }

  // ファイルサイズ表示
  Serial.println("File size (byte)= " + String(fd.size()));
  Serial.println();

  // ファイル終端まで読み出しながらシリアル出力
  while (fd.available() > 0) {
    String str = fd.readStringUntil('\n');
    Serial.println(str);
  }
  Serial.println("\n[End of File]");

  // ファイル & SPIFFSクローズ
  fd.close();
  SPIFFS.end();
  return 0;
}
