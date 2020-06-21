  const int trigPin = 6; 
  const int echoPin = 7;
  const int groenled = 13;
  const int roodled = 12;
  int correcteUitvoer = 0;
  long duration;

  // deze methode meet en berekent de afstand
  int distance(int trig, int echo)
    {
      digitalWrite(trig, LOW);
      delay(2);
      
      digitalWrite(trig, HIGH);
      delay(10);
      digitalWrite(trig, LOW);
      
      duration = pulseIn(echo, HIGH);
      int distance = duration*0.034/2; 
  
      return distance;
    }

   // deze methode controleert of de push-up correct(de gebruiker zakt ver genoeg door) wordt uitegevoerd 
   void pushups()
   {  
     Serial.print("Afstand : ");
     Serial.println(distance(trigPin, echoPin));
      if(distance(trigPin, echoPin) < 15)
      {
        // Correcte uitvoering
        digitalWrite(13, HIGH);
        Correcteuitvoer++;
        delay(500);
        digitalWrite(13, LOW);
      }
      else
      {
        // Foute uitvoering
       digitalWrite(12, HIGH);
       delay(500);
       digitalWrite(12, LOW);
      }
   }

   // deze methode controleert of je ver genoeg doorzakt tijdens het squaten 
   void squats()
   {
     Serial.print("Afstand : ");
     Serial.println(distance(trigPin, echoPin));
      if(distance(trigPin, echoPin) < 60)
      {
        // Correcte uitvoering
        digitalWrite(13, HIGH);
        Correcteuitvoer++;
        delay(500);
        digitalWrite(13, LOW);
      }
      else
      {
        // Foute uitvoering
       digitalWrite(12, HIGH);
       delay(500);
       digitalWrite(12, LOW);
      }
   }
  
  void setup() {
    // put your setup code here, to run once:
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    Serial.begin(115200);
  }
  
  void loop() {
    // put your main code here, to run repeatedly:
    /*
      switch (var) {
        case label1:
          pushups
          break;
        case label2:
          squats
          break;
         case label3:
         planking
         break;  
        default:
          // statements
          break;
      }
  */

     if (Correcteuitvoer == 5){
      Serial.print("Correct afgesloten ");
      Correcteuitvoer = 0;
      delay(10000);
     }

  }
