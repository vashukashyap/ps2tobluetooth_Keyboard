
// char ScancodeToASCII[2][128] = {
//   {
//     0,"f9",0,"f5","f3",27,"f2","f12", 0,"f10",
//     "f8","f6","f4",9,96,0, 0,"alt","shift",0,
//     "ctrl",113,49,0,0,0,122,115,97,119,
//     50,"win",0,99,120,100,101,52,51,0,
//     0,32,118,102,116,114,53,0,0,110,
//     98,104,103,121,54,0,0,0,109,106,
//     117,55,56,0,0,44,107,105,111,48,
//     57,0,0,46,47,108,59,112,45,0,
//     0,0,39,0,91,61,0,0,0,0,
//     10,93,0,124,0,0,0,60,0,0,
//     0,0,8,0,0,49,0,52,55,0,
//     0,0,0,46,50,53,54,56,27,0,
//     0,43,51,45,42,57,0,0
//   },
//   { 0,0,0,0,0,0,0,0,         0,0,0,0,0,0,126,0,        0,0,0,0,0,81,33,0,        0,0,90,83,65,87,64,35,       // with SHIFT
//     0,67,88,68,69,36,35,0,    0,32,86,70,84,82,37,0,     0,78,66,72,71,89,94,0,    0,0,77,74,85,38,42,0,
//     0,60,75,73,79,41,40,0,   0,62,63,76,58,80,95,0,   0,0,34,0,123,43,0,0,      0,0,0,125,0,92,0,0,
//     0,62,0,0,0,0,0,0,        0,0,0,0,0,0,0,0,          0,0,0,0,0,0,0,0,          0,0,0,0,0,0,0,0  } };

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
