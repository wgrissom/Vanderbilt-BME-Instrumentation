
const int IR_Pin = 3;    // Hall Sensor Output on Pin 3
const int IR_Int = 1;    // Interrupt #1 on Pin 3
volatile int count = 0;  // count interrupts from IR Sensor

void setup()
{
  pinMode(IR_Pin, INPUT_PULLUP); // open collector IR detector
  Serial.begin(9600);
  Serial.println("\n\nInfrared Fan Motor Speed Control");
}

void loop() { 
  
  count = 0;
  attachInterrupt(IR_Int, IR_ISR, CHANGE); 
  delay(1000);               // measure for 1 second
  detachInterrupt(IR_Int);   // disable interrupt 
  
  Serial.print(" Speed: "); Serial.println(count*6);
}
     
void IR_ISR() {
  count++;  
}
