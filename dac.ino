
#include <EEPROM.h>
#include <TM1637Display.h>

#include <IRremote.h>
// *************************************************************************************

const uint8_t SEG_DD[] = { //dolby
  SEG_D | SEG_B | SEG_C | SEG_E | SEG_G, //d
   SEG_C | SEG_E | SEG_D | SEG_G, //0
   SEG_E | SEG_F, //l
   SEG_D | SEG_F | SEG_C | SEG_E | SEG_G,//b
};
const uint8_t SEG_DTS[] = { //dts
  SEG_D | SEG_B | SEG_C | SEG_E | SEG_G, //d
  SEG_D | SEG_E | SEG_F | SEG_G, //t
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G, //S
  false,  
};
const uint8_t SEG_PCM[] = { //pcm
  SEG_A | SEG_B | SEG_E | SEG_F | SEG_G, //P
  SEG_D | SEG_E | SEG_G, //C
  SEG_C | SEG_E |  SEG_G, //n
  SEG_C |  SEG_G,//n   
};
const uint8_t SEG_ARC[] = { //arc
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, //A
  SEG_E | SEG_G, //R
  SEG_D | SEG_E | SEG_G, //C
  false,
};

const uint8_t SEG_coa[] = { //coaxial
  SEG_A | SEG_D | SEG_E | SEG_F, //C
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, //O
  SEG_G,
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, //A
  
};

const uint8_t SEG_OPT[] = { //optical
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, //O
  SEG_A | SEG_B | SEG_E | SEG_F | SEG_G, //P
  SEG_D | SEG_E | SEG_F | SEG_G, //T
  SEG_E | SEG_F , //I
};

const uint8_t SEG_USB[] = { //usb mdule
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_F, //U
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G, //S
  SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, //b
  false,
};

// BOOT Animation..............
const uint8_t ANIMATION0[]= {
 SEG_A,false,false,false,
};
const uint8_t ANIMATION1[]= {
 SEG_A,SEG_A,false,false,
};
const uint8_t ANIMATION2[]= {
 SEG_A,SEG_A,SEG_A,false,
};
const uint8_t ANIMATION3[]= {
 SEG_A,SEG_A,SEG_A,SEG_A,
};
const uint8_t ANIMATION4[]= {
 SEG_A,SEG_A,SEG_A,
 SEG_A | SEG_B,
};
const uint8_t ANIMATION5[]= {
 SEG_A,SEG_A,SEG_A,
 SEG_A | SEG_B | SEG_C,
};
const uint8_t ANIMATION6[]= {
 SEG_A,SEG_A,SEG_A,
 SEG_A | SEG_B | SEG_C | SEG_D,
};
const uint8_t ANIMATION7[]= {
 SEG_A,
 SEG_A,
 SEG_A| SEG_D,
 SEG_A | SEG_B | SEG_C | SEG_D,
};
const uint8_t ANIMATION8[]= {
  SEG_A,
 SEG_A| SEG_D,
 SEG_A| SEG_D,
 SEG_A | SEG_B | SEG_C | SEG_D,
};
const uint8_t ANIMATION9[]= {
 SEG_A| SEG_D,
 SEG_A| SEG_D,
 SEG_A| SEG_D,
 SEG_A | SEG_B | SEG_C | SEG_D,
};
const uint8_t ANIMATION10[]= {
 SEG_A| SEG_D | SEG_E,
 SEG_A| SEG_D,
 SEG_A| SEG_D,
 SEG_A | SEG_B | SEG_C | SEG_D,
};
const uint8_t ANIMATION11[]= {
 SEG_A| SEG_D | SEG_E | SEG_F,
 SEG_A| SEG_D |SEG_G,
 SEG_A| SEG_D,
 SEG_A | SEG_B | SEG_C | SEG_D,
};
const uint8_t ANIMATION12[]= {
 SEG_A| SEG_D | SEG_E | SEG_F,
 SEG_A| SEG_D |SEG_G,
 SEG_A| SEG_D | SEG_G,
 SEG_A | SEG_B | SEG_C | SEG_D,
};
const uint8_t ANIMATION13[]= {
 SEG_A| SEG_D | SEG_E | SEG_F,
 SEG_A| SEG_D |SEG_G,
 SEG_A| SEG_D | SEG_G,
 SEG_A | SEG_B | SEG_C | SEG_D,
};


// *******************************************************************//
//                      Code Start Here
//                      Developed By Gadget_Vishwa
// *******************************************************************//
int dd=12,dts=11,pcm=13;
const int buttonPin = 2;  
const int fta=8;
const int ftb=9;
const int usbp= 10; 
const int ftp=7;
const int CLK = 6;        // Clock pin for TM1637
const int DIO = 5;        // Data pin for TM1637
TM1637Display display(CLK, DIO);

const int IRpin = 3;      // Pin connected to the TSOP sensor module
IRrecv irrecv(IRpin);
decode_results results;


int currentState = 0;
int lastButtonState = HIGH;
int buttonState;
int buttonPresses = 0;


  void setup() {
    Serial.begin(115200);
    Serial.println("Developed by Gadget_Vishwa.");
    pinMode(ftp, OUTPUT);
    digitalWrite(ftp, HIGH);
    display.setBrightness(0x0f);
    // NEED FOR LOOP
    display.setSegments(ANIMATION0);
    delay(200);
    display.setSegments(ANIMATION1);
    delay(200);
    display.setSegments(ANIMATION2);
    delay(200);
    display.setSegments(ANIMATION3);
    delay(200);
    display.setSegments(ANIMATION4);
    delay(200);
    display.setSegments(ANIMATION5);
    delay(200);
    display.setSegments(ANIMATION6);
    delay(200);
    display.setSegments(ANIMATION7);
    delay(200);
    display.setSegments(ANIMATION8);
    delay(200);
    display.setSegments(ANIMATION9);
    delay(200);
    display.setSegments(ANIMATION10);
    delay(200);
    display.setSegments(ANIMATION11);
    delay(200);
    display.setSegments(ANIMATION12);
    delay(200);
    display.setSegments(ANIMATION13);
    delay(200);
    display.setSegments(ANIMATION13);
    delay(200);

    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(fta, OUTPUT);
    pinMode(ftb, OUTPUT);
    pinMode(usbp, OUTPUT);
    pinMode(dd,INPUT);
    pinMode(dts,INPUT);
    pinMode(pcm,INPUT);

    if (EEPROM.read(0) == 255) {  // Check if EEPROM is uninitialized
        EEPROM.write(0, 0);       // Set a default value
    }
    digitalWrite(ftp, LOW);
    currentState = EEPROM.read(0);  // Read last saved state from EEPROM
    buttonPresses = currentState;   // Set buttonPresses to match currentState
    updateMode(); 
    updateDisplay();                  // Apply last state to display, GPIO, and serial

    irrecv.enableIRIn();            // Start the IR receiver
}


void loop()
{   //for IR 
    if (irrecv.decode(&results)) {
        if (results.value == 0xFD0) {  // Replace with your remote control key value
            buttonPresses++;
            currentState = buttonPresses % 4;
            updateMode();
            updateDisplay();
            EEPROM.update(0, currentState); 
            delay(400);
        }
        irrecv.resume();  // Receive the next value
    }

    //for button press
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && lastButtonState == HIGH) {
        buttonPresses++;
        currentState = buttonPresses % 4;
        updateMode();
        updateDisplay();
        EEPROM.update(0, currentState); 
    }
    lastButtonState = buttonState;
    // delay(500);
    if(digitalRead(dd)==HIGH && digitalRead(dts)==LOW && digitalRead(pcm)==LOW){
       display.setSegments(SEG_DD); 
       Serial.println("Dolby\n");
    }
    else if(digitalRead(dd)==LOW && digitalRead(dts)==HIGH && digitalRead(pcm)==LOW){
        display.setSegments(SEG_DTS);
        Serial.println("DTS\n");
    }
    else if(digitalRead(dd)==LOW && digitalRead(dts)==LOW && digitalRead(pcm)==HIGH){
        display.setSegments(SEG_PCM); 
        Serial.println("Stero to 5.1 Channel...");       
    }
    else{
        updateDisplay();
        Serial.println("NO Format from DAC....!");
    }

}

void updateDisplay() {
  switch (currentState) {
    case 0:
      display.setSegments(SEG_USB);
      break;
    case 1:
      display.setSegments(SEG_ARC);
      break;
    case 2:
       display.setSegments(SEG_OPT); 
      break;
    case 3:
      display.setSegments(SEG_coa); 
      break;
  }
}

void updateMode() {
  switch (currentState) {
    case 0:
      usb();
      break;
    case 1:
      arc();
      break;
    case 2:
      optical();
      break;
    case 3:
      coaxial();
      break;
  }
}


void arc(){
    digitalWrite(fta, LOW);
    digitalWrite(ftb, LOW);
    digitalWrite(usbp, LOW);
    Serial.println("arc");
    Serial.println("");
    delay(500);    
}
void coaxial(){
    digitalWrite(fta, HIGH);
    digitalWrite(ftb, LOW);
    digitalWrite(usbp, LOW);
    Serial.println("coaxial");
    Serial.println(" ");
    delay(500); 
}
void optical(){
    digitalWrite(fta, LOW);
    digitalWrite(ftb, HIGH);
    digitalWrite(usbp, LOW);
    Serial.println("optical");
    Serial.println(" ");
    delay(500);   
}
void usb() {
    digitalWrite(fta, HIGH);    // Set fta HIGH
    digitalWrite(ftb, HIGH);    // Set ftb HIGH
    digitalWrite(usbp, HIGH);   // Set usbp HIGH
    Serial.println("usb");         // Print "usb" to Serial
    Serial.println(" ");
    delay(500);   
}


