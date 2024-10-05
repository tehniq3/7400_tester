/*
 * XOR (74LS86/ 7486) tester by Nicu FLORICA (niq_ro)
 * based on OR (74HC32 / 74LS32) tester by Nicu FLORICA (niq_ro)
 * v.0 - intial version
 * v.1 - addde serial info
 * v.2 - stable version
 */

/*
#define gate11 2   // input
#define gate12 3   // input
#define gate13 4   // output
#define gate21 5   // input
#define gate22 6   // input
#define gate23 7   // output
#define gate31 A2  // input
#define gate22 A1 // input
#define gate33 A0  // output
#define gate41 A5  // input
#define gate42 A4  // input
#define gate43 A3  // output
*/
#define lednok    11  //
#define ledok     12  //

//byte icpin[] = { 2, 3, 4, 5, 6, 7, 16, 15, 14, 19, 18, 17 };
byte inpin1[] = { 2, 5, 16, 19};
byte inpin2[] = { 3, 6, 15, 18};
byte outpin[] = { 4, 7, 14, 17}; 
byte test[] = {  // https://www.build-electronic-circuits.com/7400-series-integrated-circuits/74hc32-74ls32/
0, 0, 0,
1, 0, 1,
0, 1, 1,
1, 1, 1
};

byte nok = 0;
byte valoare = 0;
int pauzamica = 100;
int pauzamare = 500;

void setup() {
  Serial.begin(9600);
  Serial.println("-");
  Serial.println("NAND gates teter (74LS86 / 7486 tester"); 
  Serial.println("------------------------------------"); 
  for (int i = 0; i < 4; i++) 
  {
    pinMode(inpin1[i], OUTPUT);
    pinMode(inpin2[i], OUTPUT);
    digitalWrite(inpin1[i], 0);
    digitalWrite(inpin2[i], 0);
    pinMode(outpin[i], INPUT);
  }
  
pinMode(lednok, OUTPUT);
pinMode(ledok, OUTPUT);
  for (int i = 0; i < 5; i++) 
  {
digitalWrite(lednok, 1);
digitalWrite(ledok, 0);
delay(pauzamica);
digitalWrite(lednok, 0);
digitalWrite(ledok, 1);   
delay(pauzamica);
  }
digitalWrite(lednok, 0);
digitalWrite(ledok,0);
}

void loop() {
  nok = 0;
  for (int i = 0; i < 4; i++) 
  {
    Serial.print("Gate no. ");
    Serial.println(i+1);
    Serial.print(": ");
    digitalWrite(inpin1[i], test[3*i]);
   // delay(pauzamare);
    Serial.print(test[3*i]);
    Serial.print(" with ");
    digitalWrite(inpin2[i], test[3*i+1]);
   // delay(pauzamare);
    Serial.print(test[3*i+1]);
    Serial.print(" is ");
    valoare = digitalRead(outpin[i]);
  //  delay(pauzamare);
    Serial.print(valoare);
    Serial.print(" ? ");
    Serial.print(test[3*i+2]); 
    Serial.print(" => ");
    if (valoare != test[3*i+2])
     {
     nok = 1;
     Serial.println(" NOK !");
     }
     else
     Serial.println(" OK !");
     delay(pauzamica);
  }
  if (nok == 1)
   {
    for (int i = 0; i < 5; i++) 
    {
    digitalWrite(lednok,1);
    delay(pauzamica);
    digitalWrite(lednok,0);
    delay(pauzamare);
    }
   }
   else
    {
    for (int i = 0; i < 5; i++) 
    {
    digitalWrite(ledok,1);
    delay(pauzamare);
    digitalWrite(ledok,0);
    delay(pauzamare);
    }
   }
  digitalWrite(lednok, 0);
  digitalWrite(ledok,0);   
  Serial.println("------------------------------------"); 
}  // end main loop
