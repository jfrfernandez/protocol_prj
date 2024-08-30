#include <Arduino.h>
#include "myprot.h"

myprot N0(2,4);
void loop0(void *pvParameters){    // Core 0 - Send Loop
  while(1){
  int i = 0;
  unsigned char data = '0';
  N0.setTXData(data);
  for (i= 0; i < 75; i++){  
    delay(20);
    N0.sendByte(N0.getTXData());
    data++;
    N0.setTXData(data);
    }
  }
}


myprot N1(12,14);
void loop1(void *pvParameters){    // Core 1 loop - Receive Loop
  char rec;
  while(1){
    if(N1.getRxSignal() == 0){
      //Serial.println("Se detecto Comienzo Transmision");
      N1.receiveByte();
      sprintf(&rec, "%c", N1.getRXData().data);
      Serial.print("Data Received: "); Serial.println(rec);
    }
  }
}

void setup(){
  // Debug console
  Serial.begin(115200);

  xTaskCreatePinnedToCore(loop1, "loop1", 4096, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(loop0, "loop0", 4096, NULL, 1, NULL, 0);
}

void loop(){}