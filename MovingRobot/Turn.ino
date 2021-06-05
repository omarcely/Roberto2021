void Turn(char state, int duty[]){
  switch(state){
    case 'f':
        digitalWrite(S[0],HIGH);
        digitalWrite(S[1],LOW);
        digitalWrite(S[2],LOW);
        digitalWrite(S[3],HIGH);
    break;

    case 'l':
        digitalWrite(S[0],HIGH);
        digitalWrite(S[1],LOW);
        digitalWrite(S[2],HIGH);
        digitalWrite(S[3],LOW);
        SerialBT.println('l');
    break; 

    case 'r':
        digitalWrite(S[0],LOW);
        digitalWrite(S[1],HIGH);
        digitalWrite(S[2],LOW);
        digitalWrite(S[3],HIGH);
        SerialBT.println('r');
    break;

    default: //Stop
        digitalWrite(S[0],LOW);
        digitalWrite(S[1],LOW);
        digitalWrite(S[2],LOW);
        digitalWrite(S[3],LOW);
    break;  
    }

   ledcWrite(0,duty[0]);
   ledcWrite(1,duty[1]);
}
