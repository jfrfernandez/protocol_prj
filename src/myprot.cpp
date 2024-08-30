#include <Arduino.h>
#include "myprot.h"


unsigned char myprot::getparity(data_str d){
    int i = 0;
    unsigned char count = 0;

    for(i=0; i < 8; i++){
        if(d.data & (1<<i))
            count++;
    }

    if((count%2) != 0)
        return 1;
    else 
        return 0;
}

int myprot::sendByte(data_str d){

    int par = getparity(d); 

    digitalWrite(TX_PIN, LOW);              // Start bit
    delay(DELAY);
    digitalWrite(TX_PIN, d.u.bit0);
    delay(DELAY);
    digitalWrite(TX_PIN, d.u.bit1);
    delay(DELAY);
    digitalWrite(TX_PIN, d.u.bit2);
    delay(DELAY);
    digitalWrite(TX_PIN, d.u.bit3);
    delay(DELAY);
    digitalWrite(TX_PIN, d.u.bit4);
    delay(DELAY);
    digitalWrite(TX_PIN, d.u.bit5);
    delay(DELAY);
    digitalWrite(TX_PIN, d.u.bit6);
    delay(DELAY);
    digitalWrite(TX_PIN, d.u.bit7);
    delay(DELAY);
    digitalWrite(TX_PIN, par);
    delay(DELAY);
    digitalWrite(TX_PIN, HIGH);
    delay(DELAY*2.5);
    
    return 0;

}

int myprot::receiveByte(){
    
    unsigned char par_r = 0;
    unsigned char par_c = 0;
    
    delay(DELAY);
    dRx.u.bit0 = digitalRead(RX_PIN);
    delay(DELAY);
    dRx.u.bit1 = digitalRead(RX_PIN);
    delay(DELAY);
    dRx.u.bit2 = digitalRead(RX_PIN);
    delay(DELAY);
    dRx.u.bit3 = digitalRead(RX_PIN);
    delay(DELAY);
    dRx.u.bit4 = digitalRead(RX_PIN);
    delay(DELAY);
    dRx.u.bit5 = digitalRead(RX_PIN);
    delay(DELAY);
    dRx.u.bit6 = digitalRead(RX_PIN);
    delay(DELAY);
    dRx.u.bit7 = digitalRead(RX_PIN);
    delay(DELAY);
    par_r = digitalRead(RX_PIN);

    par_c = getparity(dRx);
    delay(DELAY*2.5);
   
    if(par_c == par_r)
        return 0;
    else 
        return -1;

}

myprot::myprot(int tx_pin, int rx_pin){
    
    RX_PIN = rx_pin;
    TX_PIN = tx_pin;

    pinMode(RX_PIN, INPUT_PULLUP);
    pinMode(TX_PIN, OUTPUT);
    digitalWrite(TX_PIN, HIGH);

}

int myprot::getRxSignal(){
    //Serial.println("Pin: " + String(RX_PIN));
    return digitalRead(RX_PIN);
}

myprot::data_str myprot::getTXData(){
    return dTx;
}

myprot::data_str myprot::getRXData(){
    return dRx;
}

void myprot::setTXData(unsigned char d){
    dTx.data = d;
}

