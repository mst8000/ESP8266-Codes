ADC_MODE(ADC_VCC);

// DeepSleep投入(Sleep時間を秒で指定)
void GoDeepSleep(const long sleepSec)
{
  Serial.print("DEEP SLEEP Start (");
  Serial.print(sleepSec);
  Serial.println("sec)");

  long sleepusec = sleepSec * 1000000;
  if (sleepusec > micros()) sleepusec -= micros();

  Serial.print(sleepusec);
  Serial.println("[usec]");
  ESP.deepSleep(sleepusec, WAKE_RF_DEFAULT);
  delay(1000);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("ResetReason: " + ESP.getResetReason());
  Serial.println("FreeHeap: " + String(ESP.getFreeHeap()));
  Serial.println("ChipID: " + String(ESP.getChipId()));
  Serial.println("CPUFreq(MHz): " + String(ESP.getCpuFreqMHz()));
  Serial.println("FreeSketch: " + String(ESP.getFreeSketchSpace()));
  Serial.println("FlashChipSize(byte): " + String(ESP.getFlashChipSize()));
  Serial.println("FlashChipRealSize(byte): " + String(ESP.getFlashChipRealSize()));
  Serial.println("FlashChipSpeed(Hz): " + String(ESP.getFlashChipSpeed()));
  Serial.println("Vcc: " + String(ESP.getVcc()));
  
  GoDeepSleep(5);
}
