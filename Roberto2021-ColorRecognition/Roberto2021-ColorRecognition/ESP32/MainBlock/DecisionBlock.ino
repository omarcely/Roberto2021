void turn(char state, int duty[]){
  switch(state){
    case 'f':
        digitalWrite(S[0],HIGH);
        digitalWrite(S[1],LOW);
        digitalWrite(S[2],LOW);
        digitalWrite(S[3],HIGH); 
        ledcWrite(0,duty[1]);
        ledcWrite(1,duty[0]);
    break;

    case 'l':
        digitalWrite(S[0],HIGH);
        digitalWrite(S[1],LOW);
        digitalWrite(S[2],LOW);
        digitalWrite(S[3],LOW);
        SerialBT.println('l');
        ledcWrite(0,duty[1]);
        ledcWrite(1,duty[0]);
        delay(900);
    break; 

    case 'r':
        digitalWrite(S[0],LOW);
        digitalWrite(S[1],LOW);
        digitalWrite(S[2],LOW);
        digitalWrite(S[3],HIGH);
        SerialBT.println('r');
        ledcWrite(0,duty[1]);
        ledcWrite(1,duty[0]);
        delay(900);        
    break;
    
    default: //Stop
        digitalWrite(S[0],LOW);
        digitalWrite(S[1],LOW);
        digitalWrite(S[2],LOW);
        digitalWrite(S[3],LOW);
        delay(1000);
    break;  
    }
}

char compare(double d[]){
  
  if(d[1] > 15 && d[2] < 13){
    if(d[2] < 9){
        dutyCycle[1] = minimumSpeed + 10;
        dutyCycle[0] = minimumSpeed - 10;
      }else if(d[2] > 11){
        dutyCycle[1] = minimumSpeed - 10;
        dutyCycle[0] = minimumSpeed + 10;
      }
      return 'f';
    
  }else if(d[0] > 13 && d[2] < 13){
    dutyCycle[0] = topSpeed;
    dutyCycle[1] = topSpeed;
    return 'l';
    
  }else if(d[0] < 13 && d[2] > 13 && d[1] < 15){
    dutyCycle[0] = topSpeed;
    dutyCycle[1] = topSpeed;
    return 'r'; 
    
  }else{
    dutyCycle[0] = topSpeed;
    dutyCycle[1] = topSpeed;
    return 's';
  }
  
}

double readUltrasonic(int trig, int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  return pulseIn(echo, HIGH)* 0.01716;
 }
