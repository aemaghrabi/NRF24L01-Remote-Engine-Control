/**
 **********************************************************************************************************
 * @file           : Reciver
 * @author         : Ahmed Elmaghrabi
 * @brief          : about NRF24L01
 ***********************************************************************************************************
 */

/*
 * IN NRF
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   IN ARDUINO
   LED 3,GND
   POT VCC, A0 ,GND
*/

/* ******************** Include Section Start *********************************************************** */
#include <SPI.h>
#include <nRF24L01.h>
#include "RF24.h"
/* ******************** Include Section End ************************************************************* */

/* ******************** Definition section Start ******************************************************** */
#define CE_PIN   9
#define CSN_PIN 10
/* ******************** Definition section End ********************************************************** */

/* ******************** Global Decleration Section Start ************************************************ */
int led = 4;
int pwm_pumb;
unsigned int l_pwm_pumb=pwm_pumb-120;
int pot;
int data = 0;
//const uint64_t pipe = 0xE8E8F0F0E1LL; 
const uint64_t pipe = 0xF0F0F0F0E1LL;
/* ******************** Global Decleration Section End ************************************************** */

/* ******************** Sup_Program Decleration Section Start ******************************************* */
RF24 radio(CE_PIN, CSN_PIN);
/* ******************** Sup_Program Decleration Section End ********************************************* */

/* ******************** Setup Section Start ************************************************************* */
void setup()
{
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  pinMode(A0, INPUT);
  radio.begin();//Intializing NRF24L01 Module
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}
/* ******************** Setup Section End *************************************************************** */

/* ******************** Main Section Start ************************************************************** */
void loop(){
  //Serial.println("ok");
  readPWM();
  
  if (radio.available()){
    Serial.println("radio available");
    radio.read(&data,4);
    Serial.println("msg read");
    Serial.println(data);
    // if(data==1){
    //   while(1){/////////////////////////////////
    //     digitalWrite(led, HIGH);
    //     if(pwm_pumb > 70){
    //       low();
    //       if (radio.available()){
    //         radio.read(&data,1);
    //         if(data==0){
    //           digitalWrite(led, LOW);
    //           radio.read(&data,1);
    //           readPWM();
    //           break;
    //         }
    //       }
    //     }
    //   }//////////////
    // }
  }

  if (data == 1111) {
    digitalWrite(led, HIGH);
    analogWrite(3, pwm_pumb/2);
  } else {
    digitalWrite(led, LOW);
    analogWrite(3, pwm_pumb);
  }
}
/* ******************** Main Section End ***************************************************************** */

/* ******************** Sup_Program Decleration Section Start ******************************************** */
void readPWM(){
  pot = analogRead(A0);
  pwm_pumb = map(pot, 0, 1023, 0, 255);
}
void low(){
  readPWM();
  analogWrite(3,l_pwm_pumb);
}

/* ******************** Sup_Program Decleration Section End ********************************************** */

/**
 **********************************************************************************************************
 User               Date                brief
 **********************************************************************************************************
 khaled osama       8Oct2023            Task 1 add a communication by nrf.
 khaled osama       9Oct2023            Task 2 add a control on pin.
 khaled osama       10Oct2023           Task 3 add a potentiometer , led com_ state.
*/
