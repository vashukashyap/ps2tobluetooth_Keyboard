

void setup() {

  noInterrupts();
  PCICR = 0b00000010;
  PCMSK1 = 0b00010000;

  interrupts();
  Serial.begin(9600);

}

void loop() 
{}

ISR(PCINT1_vect)
{
  int val = 0;
  for(int i=0; i<11; i++)
  {
    while(bitRead(PINC, 4) == true);
    val |= bitRead(PINC, 3)<<i;
    while(bitRead(PINC, 4) == false);
  }
  val = (val>>1) & 255;
  // Serial.println(val);

  static bool shiftIsActive = false;
  static bool nextIsReleased = false;
  static bool specialButtonIsReleased = false;

  switch (val)
  {
    // case 18: 
    // case 89: 
    //   shiftIsActive = !nextIsReleased;
    //   nextIsReleased = false;
    //   break;
    case 240:
      nextIsReleased = true;
      break;
    case 224:
      specialButtonIsReleased = true;
      break;
    default:
      if(!nextIsReleased)
      {
        Serial.println(val);
      }
      nextIsReleased = false;
      break;
  }

  PCIFR = 0x02;
}
