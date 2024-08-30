/*
5V ___     ___        ___        ______     _______
      |SB |B0 |B1  B2|B3 |B4  B5|B6 B7 |PB |
      |___|   |______|   |______|      |___|

0V

The line is in high state when no transmiting. The first bit is a starting bit putting the line in zero for 20ms.
After the starting bit, we transmitt, the 8 bits in 2ms slots. At the end the parity bit is ensuring even parity.
This mean that(not counting the start bit) the parity bit is set in one or zero to enzure the number of bits in one 
is even.
*/

#ifndef MYPROT_H_
#define MYPROT_H_


#define DELAY 2

class myprot{ 

private:

  int TX_PIN;
  int RX_PIN;

  typedef union {
    struct {
      unsigned char bit0:1;
      unsigned char bit1:1;
      unsigned char bit2:1;
      unsigned char bit3:1;
      unsigned char bit4:1;
      unsigned char bit5:1;
      unsigned char bit6:1;
      unsigned char bit7:1;
    } u;
    unsigned char data;
  } data_str;

  data_str dTx;
  data_str dRx;

public:

  myprot(int tx_pin, int rx_pin);

  unsigned char getparity(data_str d);

  int sendByte(data_str d);
  int receiveByte();

  int getRxSignal();

  data_str getTXData();
  data_str getRXData();

  void setTXData(unsigned char d);
};
#endif