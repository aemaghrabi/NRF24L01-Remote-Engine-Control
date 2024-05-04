/**
 *****************************************************************************
 * @file           : Transmater
 * @author         : Ahmed Elmaghrabi
 * @brief          : about NRF24L01
 *****************************************************************************
 */
 
 /*
  nrf
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
  key pad
    rows 8,7,6,5
    cols 4,3,2
*/

/* ******************** Include Section Start ***************************** */
#include <SPI.h>
#include <nRF24L01.h>
#include "RF24.h"
#include <Keypad.h>
/* ******************** Include Section End ******************************* */

/* ******************** Definition section Start ************************** */
#define CE_PIN   9
#define CSN_PIN 10
/* ******************** Definition section End **************************** */

/* ******************** Global Decleration Section Start ****************** */
const uint64_t pipe = 0xF0F0F0F0E1LL; 
int data;
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2}; //connect to the column pinouts of the keypad
const String password_on = "1111";
const String password_off = "5555";
String password_entered;
/* ******************** Global Decleration Section End ******************** */

/* ******************** Sup_Program Decleration Section Start ************* */
RF24 radio(CE_PIN, CSN_PIN);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
/* ******************** Sup_Program Decleration Section End *************** */

/* ******************** Setup Section Start ******************************** */
void setup()
{
  Serial.begin(9600);
  radio.begin();//Intializing NRF24L01 Module
  radio.openWritingPipe(pipe);// For Transmitting Operation, Must OpenWritingPipe
}
/* ******************** Setup Section End ********************************** */

/* ******************** Main Section Start ******************************** */
void loop(){
  Serial.println("ok");
  password_entered = "";
  //radio.write(&data,4);
  pass();
  Serial.println(password_entered);

  if (password_entered == password_on){
    data=1111; //on
    Serial.println("YES");
    Serial.println(data);
  } else {
    data = 0;
    Serial.println("NO");
  }
  // if (password_entered == password_off){
  //   data=0; //off
  //   Serial.println("NO");
  // }
  
  radio.write(&data,4);
  Serial.println("msg send");
}
/* ******************** Main Section End ********************************** */

/* ******************** Sup_Program Decleration Section Start ******************************************** */
void pass(){
  while(password_entered.length() <4){
    char key = keypad.getKey ();
    if(key != NO_KEY){
      password_entered += key;
    }
  }
}
/* ******************** Sup_Program Decleration Section End ********************************************** */
