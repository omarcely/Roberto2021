void turn(char state, int duty[]){
  switch(state){
    case 'f':
        digitalWrite(S[0],HIGH);
        digitalWrite(S[1],LOW);
        digitalWrite(S[2],LOW);
        digitalWrite(S[3],HIGH); 
        ledcWrite(0,duty[1]);
        ledcWrite(1,duty[0]);
        delay(150);
    break;

    case 'l':
        digitalWrite(S[0],HIGH);
        digitalWrite(S[1],LOW);
        digitalWrite(S[2],LOW);
        digitalWrite(S[3],LOW);
        SerialBT.println('l');
        ledcWrite(0,duty[1]);
        ledcWrite(1,duty[0]);
        delay(750);
    break; 

    case 'r':
        digitalWrite(S[0],LOW);
        digitalWrite(S[1],LOW);
        digitalWrite(S[2],LOW);
        digitalWrite(S[3],HIGH);
        SerialBT.println('r');
        ledcWrite(0,duty[1]);
        ledcWrite(1,duty[0]);
        delay(750);   
    break;
    /*case 't':
        
    break;*/
    
    default: //Stop
        digitalWrite(S[0],LOW);
        digitalWrite(S[1],LOW);
        digitalWrite(S[2],LOW);
        digitalWrite(S[3],LOW);
        delay(500);
    break;  
    }
}

char compare(double d[]){
  if((d[1]<20) &&(d[1]!= 0)){
    //medir mina xd}
    if((d[0]<30) & (d[2]<30)){
      dutyCycle[0] = topSpeed;
      dutyCycle[1] = topSpeed;
      return 'l';
      }else if(d[0]>=30){
        dutyCycle[0] = topSpeed;
        dutyCycle[1] = topSpeed;
        return 'l';       
      }else{
        dutyCycle[0] = topSpeed;
        dutyCycle[1] = topSpeed;
        return 'r';   
        }
  }else if((d[0]<60) || (d[2]<60)){
    currentDistance = d[2];
    double diff = currentDistance - lastDistance;
    if(abs(diff)> 15 || dutyCycle[0] < 870 || dutyCycle[1] < 870){
        dutyCycle[0] = minimumSpeed;
        dutyCycle[1] = minimumSpeed;
      }else{
        dutyCycle[0] = dutyCycle[0] + diff*10;
        dutyCycle[1] = dutyCycle[1] - diff*10;
        }
    lastDistance = currentDistance;    
    return 'f';
  }else{
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
