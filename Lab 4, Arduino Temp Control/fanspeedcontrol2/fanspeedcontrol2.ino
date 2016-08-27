
const int IR_Pin = 3;    // Hall Sensor Output on Pin 3
const int IR_Int = 1;    // Interrupt #1 on Pin 3
const int PWM_Pin = 5;  // PWM output to transistor to motor 
volatile int count = 0;  // count interrupts from IR Sensor

void setup()
{
  pinMode(IR_Pin, INPUT_PULLUP); // open collector IR detector
  Serial.begin(9600);
  Serial.println("\n\nInfrared Fan Motor Speed Control");
}

void loop() { 
  
  static int PWMval; 
  static float deltaold;
  int nomRPM = 1250; // nominal speed
  
  count = 0;
  attachInterrupt(IR_Int, IR_ISR, CHANGE); 
  delay(1000);               // measure for 1 second
  detachInterrupt(IR_Int);   // disable interrupt 
  
  if(count == 0 & nomRPM > 0){
    PWMval = 255; // full power start
    deltaold = 0;
  }
  else{  
    float delta = nomRPM - count*6;
    //if (delta > 0)
      PWMval = PWMval + 0.01*delta + 0.001*deltaold; //0.9*PWMval + 0.1*(PWMval + sqrt(delta));
    deltaold = deltaold + delta;
    //else
    //  PWMval = PWMval - 0.05*delta + 0.95*deltaold; //0.9*PWMval + 0.1*(PWMval - sqrt(-delta));
  }
  
  PWMval = constrain(PWMval,160,255);   
  
  analogWrite(PWM_Pin,PWMval); // set motor voltage level
  Serial.print(" Requested RPM: "); Serial.print(nomRPM);
  Serial.print(" PWM: "); Serial.print(PWMval);
  Serial.print(" Measured RPM: "); Serial.println(count*6);
}
     
void IR_ISR() {
  count++;  
}
