#include "Talkie.h"
#include "Vocab_US_Large.h"
#include "Vocab_Special.h"

const int pin_Tachometer = 10;
const int pin_Led_On = 8;
const int pin_Led_Off = 6;
const int pin_Buzzer = 3;
const int pin_Reset = 7;
const int pin_Talk = 5;

int tac_value = 0;
int tac_flag = 1;
int counter = 0;

Talkie voice;

void setup() {
  Serial.begin(9600);
  pinMode(pin_Tachometer, INPUT);
  pinMode(pin_Led_On, OUTPUT);
  pinMode(pin_Led_Off, OUTPUT);
  pinMode(pin_Reset, INPUT);
  pinMode(pin_Talk, INPUT);
}

void loop(){
  tac_value = digitalRead(pin_Tachometer);
  counterReset(&counter, pin_Reset, pin_buzzer);
  
 if(digitalRead(pin_Talk) == LOW) {
  if (tac_value == HIGH && tac_flag == 0) {
      Serial.print("A   ");
      digitalWrite(pin_Led_On, HIGH);
      digitalWrite(pin_Led_Off, LOW);
      Serial.print("Counter: ");
      Serial.println(counter);
      tac_flag = 1;
      counterReset(&counter, pin_Reset, pin_buzzer);
      
   } else if (tac_value == LOW && tac_flag == 1) {
      Serial.print("B   ");
      digitalWrite(pin_Led_Off, HIGH);
      digitalWrite(pin_Led_On, LOW);
      counter += 1;
      Serial.print("Counter: ");
      Serial.println(counter);
      tac_flag = 0;
      tone(pin_buzzer, 300, 30);
      counterReset(&counter, pin_Reset, pin_buzzer);
  }
  delay(5);
 } else if (digitalRead(pin_Talk) == HIGH) {
  sayNumber(counter);
  delay(5);
 } 
}

void counterReset(int *counter, int pin_Reset, int pin_buzzer) {
  int cValue = digitalRead(pin_Reset); 
  if (cValue == HIGH) {
      *counter = 0;
      tone(pin_buzzer, 300, 50);
      delay(100);
      tone(pin_buzzer, 300, 50);
      Serial.println("**** RESET ****");
    }
}

void sayNumber(long n) {
  if (n<0) {
    voice.say(sp2_MINUS);
    sayNumber(-n);
  } else if (n==0) {
    voice.say(sp2_ZERO);
  } else {
    if (n>=1000) {
      int thousands = n / 1000;
      sayNumber(thousands);
      voice.say(sp2_THOUSAND);
      n %= 1000;
      if ((n > 0) && (n<100)) voice.say(sp2_AND);
    }
    if (n>=100) {
      int hundreds = n / 100;
      sayNumber(hundreds);
      voice.say(sp2_HUNDRED);
      n %= 100;
      if (n > 0) voice.say(sp2_AND);
    }
    if (n>19) {
      int tens = n / 10;
      switch (tens) {
        case 2: voice.say(sp2_TWENTY); break;
        case 3: voice.say(sp2_THIR_); voice.say(sp2_T); break;
        case 4: voice.say(sp2_FOUR); voice.say(sp2_T);  break;
        case 5: voice.say(sp2_FIF_);  voice.say(sp2_T); break;
        case 6: voice.say(sp2_SIX);  voice.say(sp2_T); break;
        case 7: voice.say(sp2_SEVEN);  voice.say(sp2_T); break;
        case 8: voice.say(sp2_EIGHT);  voice.say(sp2_T); break;
        case 9: voice.say(sp2_NINE);  voice.say(sp2_T); break;
      }
      n %= 10;
    }
    switch(n) {
      case 1: voice.say(sp2_ONE); break;
      case 2: voice.say(sp2_TWO); break;
      case 3: voice.say(sp2_THREE); break;
      case 4: voice.say(sp2_FOUR); break;
      case 5: voice.say(sp2_FIVE); break;
      case 6: voice.say(sp2_SIX); break;
      case 7: voice.say(sp2_SEVEN); break;
      case 8: voice.say(sp2_EIGHT); break;
      case 9: voice.say(sp2_NINE); break;
      case 10: voice.say(sp2_TEN); break;
      case 11: voice.say(sp2_ELEVEN); break;
      case 12: voice.say(sp2_TWELVE); break;
      case 13: voice.say(sp2_THIR_); voice.say(sp2__TEEN); break;
      case 14: voice.say(sp2_FOUR); voice.say(sp2__TEEN);break;
      case 15: voice.say(sp2_FIF_); voice.say(sp2__TEEN); break;
      case 16: voice.say(sp2_SIX); voice.say(sp2__TEEN); break;
      case 17: voice.say(sp2_SEVEN); voice.say(sp2__TEEN); break;
      case 18: voice.say(sp2_EIGHT); voice.say(sp2__TEEN); break;
      case 19: voice.say(sp2_NINE); voice.say(sp2__TEEN); break;
    }
  }
}
