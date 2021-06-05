char Compare(int d[]){
  if(d[1] > 10 && d[2] < xwidth){
    return 'f';
  }else if(d[0] > 15 && d[2] < xwidth){
    return 'l';
  }else if(d[0] < xwidth && d[2] > xwidth){
    return 'r'; 
  }else{
    return 's';
  }
}
/*if (distance[1] > 15 && distance[2] < xwidth){
      //Forward: S = [1, 0, 0, 1]
        /*if(distance[0] - distance[2] <= -2){
          //Correction too close to the left hand side
          dutyCycle[0] = maxspeed;
          dutyCycle[1] = minspeed;
        }else if(distance[0] - distance[2] >= 2){
          dutyCycle[0] = minspeed;
          dutyCycle[1] = maxspeed;
        }else{
          SerialBT.println(distance[1]); 
          Serial.println("Forward");
          dutyCycle[0] = maxspeed;
          dutyCycle[1] = maxspeed;
        //}  
          turn(1);
          delay(10);
        
    }else if(distance[0] > 15 && distance[2] < xwidth){
        turn(4);
        Serial.println("Turn Left");
        dutyCycle[0] = maxspeed;
        dutyCycle[1] = maxspeed;
        turn(2);
        delay(500);
    }else if(distance[0] < xwidth && distance[2] > 15){
        turn(4);
        Serial.println("Turn Right");
        dutyCycle[0] = maxspeed;
        dutyCycle[1] = maxspeed;
        turn(3);
        delay(500);
    
     }else{
        Serial.println("Stop");
        dutyCycle[0] = maxspeed;
        dutyCycle[1] = maxspeed;
        turn(4);    
    }*/
