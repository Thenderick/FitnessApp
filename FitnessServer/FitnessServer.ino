#include <SPI.h>
#include <Ethernet.h>

EthernetClient client;

byte mac[] = { 0x08, 0x97, 0x98, 0x6B, 0xF3, 0x80 };
IPAddress ip(192, 168, 1, 3);

EthernetServer server(80);

int calibratedHeight;
int countArray[6];
long duration;
int distance;
int i;
int led[2] = {9,8}; //9 = rood 8 = groen
int trigPin = 6;
int echoPin = 7;
int correcteUitvoer;
char Phone_input; //voor het oplaan van het ontvangen karakter
char currentExercise;
bool down;
char response[4];

void getDistance(int trig, int echo){
  digitalWrite(trig, LOW);
  delay(2);

  digitalWrite(trig, HIGH);
  delay(998); 
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration*0.034/2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void calibrateHeight(int trig, int echo){
  delay(2000); //2 seconden om goed in positie te komen voordat hij gaat meten

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
    Serial.print(calibratedHeight);
    Serial.println(" cm");
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

void Planking(int trig, int echo){
  if(distance >= (calibratedHeight - 1) && distance <= (calibratedHeight + 1)){
    i = 1; //Als de hoogte goed is, gaat het groene lampje aan
    correcteUitvoer++;
  }else{
    i = 0;//Als de hoogte niet goed is, gaat het rode lampje aan
  }
  digitalWrite(led[i], HIGH);
  
  getDistance(trig, echo); 
  
  digitalWrite(led[i], LOW);
}

void squatsOrPushUps(int afstand, int trig, int echo){
   getDistance(trig, echo);
   Serial.print("Afstand : ");
   Serial.println(distance);
    if(down &&(distance < afstand))
    {
      // Correcte uitvoering
      digitalWrite(led[1], HIGH);
      correcteUitvoer++;
      delay(500);
      digitalWrite(led[1], LOW);
      down = false;
    }
    if(!down && (distance > afstand))
    {
      // Foute uitvoering
     digitalWrite(led[0], HIGH);
     delay(500);
     digitalWrite(led[0], LOW);
     down = true;
    }
    Serial.print("Aantal correcte uitvoer: ");
    Serial.println(correcteUitvoer);
}

void execute(char c){
  Serial.println(Phone_input);
  switch (Phone_input) {
        case 'p': //pushups
          currentExercise = 'p';           
          break;
        case 's': //squats
          currentExercise = 's';
          break;
        case 'l':
         calibrateHeight(trigPin, echoPin);
         currentExercise = 'l';
         break;  
        case 'b':
           stopExercise();
         break;
        default:
          
         break;
      }
}

void stopExercise(){
  char tempExercise = Phone_input;
  Phone_input = NULL;
  currentExercise = NULL;
  switch (tempExercise){
    case 'p':
      Serial.print("Totale aantal pushups: "); Serial.println(correcteUitvoer);
      break;
    case 's':
      Serial.print("Totale aantal squats: "); Serial.println(correcteUitvoer);
      break;
    case 'l':
      Serial.print("Totale tijd geplankt: "); Serial.println(correcteUitvoer);
      break;
    default:
      break;
  }
  itoa(correcteUitvoer, response, 10);
  correcteUitvoer = 0;
  server.write(response, 4);
  Serial.print("Response was: "); Serial.println(response);
}

//Zorgt ervoor dat de juiste oefening in de loop blijft
void exercise(){
  //Serial.println(currentExercise);
  switch (currentExercise){
    case 'p': //pushups
      squatsOrPushUps(15, trigPin, echoPin);           
      break;
    case 's': //squats
      squatsOrPushUps(60, trigPin, echoPin);
      break;
    case 'l':
      Planking(trigPin, echoPin);
      break;
    default:
      break;
      
  }
}

void setup() {
  // put your setup code here, to run once:
  correcteUitvoer = 0;
  Serial.begin(115200);
  for(i = 0; i < 2; i++){
    pinMode(led[i], OUTPUT);
  }
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

   if(Ethernet.begin(mac)==0){
    Serial.println("No DHCP");
    Ethernet.begin(mac, ip);
  }

  server.begin();
  Serial.print("Server is at "); Serial.println(Ethernet.localIP());
}

void loop() {
  client = server.available();
  if(client.connected()){
    Phone_input = client.read();
    execute(Phone_input);
  }
  exercise();
      
  }
