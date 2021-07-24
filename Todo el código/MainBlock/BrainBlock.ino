void brain(){
    r = SerialBT.read();
    if(r == 'r'){
      sendToPhy = true;
      distance[0] = readUltrasonic(trigger,uts_1);
      delay(5);
      distance[1] = readUltrasonic(trigger,uts_2);
      delay(5); 
      distance[2] = readUltrasonic(trigger,uts_3);
      delay(5);
      currentState = compare(distance);
    }else if(r == 's'){
      sendToPhy = false;
      turn('s',dutyCycle);
    }else{
      sendToPhy = sendToPhy;
    }
    
    if(sendToPhy == true){
        switch(currentState){
          case 'l':
            turn(currentState, dutyCycle);
            currentState = 's';
          break;
            
          case 'f':
            turn(currentState, dutyCycle); 
            distance[0] = readUltrasonic(trigger,uts_1);
            delay(5); 
            distance[1] = readUltrasonic(trigger,uts_2);
            delay(5);
            distance[2] = readUltrasonic(trigger,uts_3);
            delay(5);   
            SerialBT.println(distance[1]);
                     
            nextState = compare(distance);
            if(nextState != currentState){
                currentState = 's';
                dutyCycle[0] = topSpeed;
                dutyCycle[1] = topSpeed;
            }else{
                currentState = nextState;
                if (dutyCycle[0] > minimumSpeed){
                  dutyCycle[0] = dutyCycle[0] - 20;
                  dutyCycle[1] = dutyCycle[1] - 20;
                } 
            }
          break;
          
          case 'r':
            turn(currentState, dutyCycle);
            currentState = 's';
          break;
          
          default: 
            turn(currentState, dutyCycle);
            distance[0] = readUltrasonic(trigger,uts_1);
            delay(5);
            distance[1] = readUltrasonic(trigger,uts_2);
            delay(5); 
            distance[2] = readUltrasonic(trigger,uts_3);
            delay(5);
            currentState = compare(distance);
          break; 
       }
       }
}
