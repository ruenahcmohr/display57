#include "font.h"

/*

ok, the wiring will be as follows:  

display -> Nano

data in  ->; D2
clock in ->; D3
Row 1    ->; D6
Row 2    ->; D7
Row 3    ->; D8
Row 4    ->; D9
Row 5    ->; D10
Row 6    ->; D11
Row 7    ->; D12
+5V      ->; 5V
GND      ->; GND
GND      ->; GND

*/


char display[4];


void NextColumn(      void ) ;
void setupColumnScan( void ) ;
void setRows(         uint8_t d );


void setup() {
 pinMode(2, OUTPUT); // data for shift reg cols
 pinMode(3, OUTPUT); // clock for shift reg cols
 
 pinMode(6, OUTPUT); // row 1 
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(9, OUTPUT);
 pinMode(10, OUTPUT);
 pinMode(11, OUTPUT);
 pinMode(12, OUTPUT); // row 7
 
 display[0] = '0'; // initial display data.
 display[1] = '1';
 display[2] = '2';
 display[3] = '3';
}



void loop() {
  int dig, col;
  // scan scan scan scan!!! 



    // turn off rows
    setRows(0);

    // load first column data
    setupColumnScan();

   // oh headache, this device scans from right to left :(
    for (dig = 3; dig >= 0; dig--) {
      for (col = 4; col >= 0; col--) {       
        setRows( Font5x7[((display[dig])-' ')*5 + col] );
        delay(1); // POV delay
        setRows(0); // turn the rows off so they do not smear.
        NextColumn();
      }
    }

  

}

void NextColumn() {
   digitalWrite(3,  HIGH); // pulse clock
   digitalWrite(3,  LOW);  // pulse clock
}

// this loads a 0 into the first shift register
// we will walk that zero thru all the columns
void setupColumnScan() {
   digitalWrite(2,  HIGH); // data low (its inverted)
   digitalWrite(3,  HIGH); // pulse clock
   digitalWrite(3,  LOW);  // pulse clock
   digitalWrite(2,  LOW);  // data high (its inverted)
}


void setRows( uint8_t d ) {
  if (d & 0x01) digitalWrite(6,  HIGH); else digitalWrite(6,  LOW);
  if (d & 0x02) digitalWrite(7,  HIGH); else digitalWrite(7,  LOW);
  if (d & 0x04) digitalWrite(8,  HIGH); else digitalWrite(8,  LOW);
  if (d & 0x08) digitalWrite(9,  HIGH); else digitalWrite(9,  LOW);
  if (d & 0x10) digitalWrite(10, HIGH); else digitalWrite(10, LOW);
  if (d & 0x20) digitalWrite(11, HIGH); else digitalWrite(11, LOW);
  if (d & 0x40) digitalWrite(12, HIGH); else digitalWrite(12, LOW);
}


