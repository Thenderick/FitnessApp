
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
int correcteUitvoer = 0;

void getDistance(int trig, int echo){
  digitalWrite(trig, LOW);
  delay(2);

  digitalWrite(trig, HIGH);
  delay(998); 
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration*0.034/2;

  //if(distance < 100 && distance > 5){
    Serial.print("Distance: ");
    Serial.println(distance);
    Serial.print(" cm");
  //}else{
    //for(i = 0; i < 3; i++){ // als de meting niet goed is knippert het rode lampje 3 keer en dan na een seconde gaat hij weer overnieuw meten
      //digitalWrite(led[0], HIGH);
      //delay(500);
      //digitalWrite(led[0], LOW);
      //delay(500);
    //}
    //distance = 0;
    //delay(1000);
    //getDistance(trig, echo);
  //}
}

void calibrateHeight(int trig, int echo){
  delay(3000); //3 seconden om goed in positie te komen voordat hij gaat meten

  for(i = 0; i <= 5; i++){ //Hij meet 6 keer om accurate resultaten te krijgen en doet dit over een periode van 6 seconden
    getDistance(trig, echo);
    countArray[i] = distance;
  }
  
  distance = (countArray[0]+countArray[1]+countArray[2]+countArray[3]+countArray[4]+countArray[5]) / 6; // De eerste word niet mee gerekend, want dan ben je vaak nog niet helemaal goed in positie
  
  if(distance != 0){ 
    for(i = 0; i < 2; i++){ // Als het calibreren succesvol is afgerond knippert hij 2 keer groen
      digitalWrite(led[1], HIGH);
      delay(100);
      digitalWrite(led[1], LOW);
      delay(100);
    }
    calibratedHeight = distance;
    Serial.print("Distance: ");
    Serial.println(calibratedHeight);
    Serial.print(" cm");
  }else{
    for(i = 0; i < 3; i++){ // als de meting niet goed is knippert het rode lampje 3 keer en dan na een seconde gaat hij weer overnieuw meten
      digitalWrite(led[0], HIGH);
      delay(500);
      digitalWrite(led[0], LOW);
      delay(500);
    }
    distance = 0;
    calibrateHeight(trig, echo);
  }
}

void goodOrWrong(int trig, int echo){
  if(distance >= (calibratedHeight - 1) && distance <= (calibratedHeight + 1)){
    i = 1; //Als de hoogte goed is, gaat het groene lampje aan
  }else{
    i = 0;//Als de hoogte niet goed is, gaat het rode lampje aan
  }
  digitalWrite(led[i], HIGH);
  
  getDistance(trig, echo);

  actualDuration + 1000;
  
  digitalWrite(led[i], LOW);
}

void Planking(int trig, int echo, int eDuration){
  calibrateHeight(trig, echo);
  
  digitalWrite(led[0], HIGH);//Om te laten weten dat de oefening begint gaan beide lampjes 1 keer aan en uit
  digitalWrite(led[1], HIGH);
  delay(10);
  digitalWrite(led[0], LOW);
  digitalWrite(led[1], LOW);
  delay(10);
  
  while(actualDuration < eDuration){ //De exercise duurt op het moment een halve minuut en hij controlleert de hoogte elke seconde
      goodOrWrong(trig, echo);
  }
  if(actualDuration >= eDuration){
      for(i = 0; i < 4; i++){ // Als de oefening voorbij is knippert hij 5 keer snel
        digitalWrite(led[1], HIGH);
        delay(10);
        digitalWrite(led[1], LOW);
        delay(10);
      }
    }
}

void squatsOrPushUps(int afstand, int trig, int echo){
     getDistance(trig, echo);
     Serial.print("Afstand : ");
     Serial.println(distance);
      if(distance < afstand)
      {
        // Correcte uitvoering
        digitalWrite(led[1], HIGH);
        correcteUitvoer++;
        delay(500);
        digitalWrite(led[1], LOW);
      }
      else
      {
        // Foute uitvoering
       digitalWrite(led[0], HIGH);
       delay(500);
       digitalWrite(led[0], LOW);
      }
   }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  for(i = 0; i < 2; i++){
    pinMode(led[i], OUTPUT);
  }
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Planking(trigPin, echoPin, exerciseDuration);
   /*
      switch (var) {
        case label1: //pushups
           squatsOrPushUps(15, trigPin, echoPin);           
          break;
        case label2: //squats
          squatsOrPushUps(60, trigPin, echoPin)
          break;
         case label3:
         Planking(trigPin, echoPin, exerciseDuration);
         break;  
        default:
          // statements
          break;
      }
  */
}
