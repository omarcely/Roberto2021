#define cntrl 7
void setup() {
  Serial.begin(9600);
  pinMode(cntrl, OUTPUT);
  digitalWrite(cntrl,1);
}
byte puta[36] = {255,240,0,255,240,0,255,240,0,255,240,0,0,0,255,0,0,255,0,0,255,0,0,255,255,0,0,255,0,0,255,0,0,255,0,0};
int i = 0;
void loop() {
  if(i==0){
    delay(500);
    digitalWrite(cntrl,0);
    delay(500);
    }
  Serial.write(puta[i]);
  i++;
  if(i==36){
    i=0;
    delay(500);
    digitalWrite(cntrl,1);
    delay(500);
    }
  delay(50);
}
