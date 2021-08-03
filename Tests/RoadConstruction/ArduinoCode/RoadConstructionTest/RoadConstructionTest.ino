int distance = 30; //distance[0] = uts_1 (Left); distance[1] = uts_2 (Front); distance[2] = uts_3 (Right);  
char state = 'b';
boolean done = false;

void setup() { 
  Serial.begin(9600);
}

void loop() {

  if(distance > 2){
      Serial.println(distance);
      distance -= 1;
  }else{
      switch(state){
        
        case 'b':
           Serial.println('b');
           delay(10);
           done = false;
           
           while(done == false){
            if(Serial.available()){
               if(Serial.read() == 'd'){
                  done = true; 
               }
            }
           }
            delay(500);
            Serial.println('l');
            delay(750);
            distance = 30;
            state = 'g';
        break;

        case 'g':
           Serial.println('g');
           delay(10);
           done = false;
           while(done == false){
            if(Serial.available()){
               if(Serial.read() == 'd'){
                  done = true; 
               }
            }
           }
            Serial.println('r');
            delay(750);
            distance = 30;
            state = 'x';
        break;  

        case 'x':
           Serial.println('x');
           delay(10);
           done = false;
           while(done == false){
            if(Serial.available()){
               if(Serial.read() == 'd'){
                  done = true; 
               }
            }
           }
            Serial.println('r');
            delay(750);
            distance = 30;
            state = 'n';
        break;

        case 'n':
           Serial.println('n');
           delay(10);
           done = false;
           while(done == false){
            if(Serial.available()){
               if(Serial.read() == 'd'){
                  done = true; 
               }
            }
           }
            Serial.println('l');
            delay(750);
            distance = 30;
            state = 'a';
        break;

        default:
           delay(5000);
           state = 'b';
        break;

      }
  }

}