
int calibratedHeight;
int countArray[6];
long duration;
int distance;
int i;
int led[2] = {12,13}; //12 = rood 13 = groen
int trigPin = 6;
int echoPin = 7;
int exerciseDuration = 30000; //Voor nu een halve minuut
int actualDuration;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(i = 0; i < 2; i++){
    pinMode(led[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Planking(trigPin, echoPin, exerciseDuration);
  delay(10000); // 10 seconden pauze en dan komt of de volgende workout of dezelfde weer
}

int getDistance(int trig, int echo){
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(500); //Per halve seconde gaat hij meten
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration*0.034/2;

  if(distance < 100 && distance > 5){
    Serial.print("Distance: ");
    return Serial.println(distance);
    Serial.print(" cm");
  }else{
    for(i = 0; i < 3; i++){ // als de meting niet goed is knippert het rode lampje 3 keer en dan na een seconde gaat hij weer overnieuw meten
      digitalWrite(led[0], HIGH);
      delay(500);
      digitalWrite(led[0], LOW);
      delay(500);
    }
    distance = NULL;
    delay(1000);
    return getDistance(trig, echo);
  }
}

int calibrateHeight(int trig, int echo){
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  delay(3000); //3 seconden om goed in positie te komen voordat hij gaat meten

  for(i = 0; i <= 5; i++){ //Hij meet 6 keer om accurate resultaten te krijgen en doet dit over een periode van 3 seconden
    getDistance(trig, echo);
    countArray[i] = distance;
  }
  
  distance = (countArray[1]+countArray[2]+countArray[3]+countArray[4]+countArray[5]) / 6; // De eerste word niet mee gerekend, want dan ben je vaak nog niet helemaal goed in positie
  
  if(distance != NULL){ 
    for(i = 0; i < 2; i++){ // Als het calibreren succesvol is afgerond knippert hij 2 keer groen
      digitalWrite(led[1], HIGH);
      delay(100);
      digitalWrite(led[1], LOW);
      delay(100);
    }
    calibratedHeight = distance;
    Serial.print("Distance: ");
    return Serial.println(calibratedHeight);
    Serial.print(" cm");
  }else{
    for(i = 0; i < 3; i++){ // als de meting niet goed is knippert het rode lampje 3 keer en dan na een seconde gaat hij weer overnieuw meten
      digitalWrite(led[0], HIGH);
      delay(500);
      digitalWrite(led[0], LOW);
      delay(500);
    }
    return calibrateHeight(trig, echo);
  }
}

int Planking(int trig, int echo, int eDuration){
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  calibrateHeight(trig, echo);

  while(actualDuration < eDuration){ //De exercise duurt op het moment een halve minuut en hij controlleert de hoogte elke seconde
    if(distance == calibratedHeight || distance >= (calibratedHeight - 1) || distance <= calibratedHeight + 1){ //Er is speling van een cm omhoog en een cenitmeter omlaag
      if(actualDuration != eDuration){
        digitalWrite(led[1], HIGH); //Zolang de hoogte goed is blijft het lampje groen
        digitalWrite(trig, LOW);
        delayMicroseconds(2);

        digitalWrite(trig, HIGH);
        delayMicroseconds(998);
        digitalWrite(trig, LOW);

        duration = pulseIn(echo, HIGH);
        distance = duration*0.034/2;

        actualDuration += 1000;

        Serial.print("Distance: ");
        return Serial.println(distance);
        Serial.print(" cm");
      }else if(actualDuration == eDuration){
        for(i = 0; i < 4; i++){ // Als de oefening voorbij is knippert hij 5 keer snel
          digitalWrite(led[1], HIGH);
          delay(10);
          digitalWrite(led[1], LOW);
          delay(10);
        }
      }
    }else{
      digitalWrite(led[0], HIGH); //Zolang de hoogte fout is blijft het lampje rood
      digitalWrite(trig, LOW);
      delayMicroseconds(2);

      digitalWrite(trig, HIGH);
      delayMicroseconds(998);
      digitalWrite(trig, LOW);

      duration = pulseIn(echo, HIGH);
      distance = duration*0.034/2;

      actualDuration += 1000;

      Serial.print("Distance: ");
      return Serial.println(distance);
      Serial.print(" cm");
    }
  }
}
