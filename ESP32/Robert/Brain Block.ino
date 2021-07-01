void brain(){
    r = SerialBT.read();
    if(r == 'r'){
      sendToPhy = true;
      distance[0] = ultra1.read();
      delay(100);
      distance[1] = ultra2.read();
      delay(100); 
      distance[2] = ultra3.read();
      delay(100);
      state = compare(distance);
    }else if(r == 's'){
      sendToPhy = false;
    }else{
      sendToPhy = sendToPhy;
    }
    
    if(sendToPhy == true){
        switch(state){
          case 'l':
            distance[0] = ultra1.read();
            delay(200);
          break;
            
          case 'f':
            distance[1] = ultra2.read();
            delay(200);
            SerialBT.println(distance[1]);
          break;
          
          case 'r':
            distance[2] = ultra3.read();
            delay(200);
          break;
          
          default: 
            turn(state, dutyCycle);
            distance[0] = ultra1.read();
            delay(100);
            distance[1] = ultra2.read();
            delay(100); 
            distance[2] = ultra3.read();
            delay(100);
            state = compare(distance);
          break; 
       }
       state = compare(distance);
       Serial.println(state);
       turn(state, dutyCycle);  
    }
}
