#define ledPin1 7
#define ledPin2 2
#define ledPin3 3
#define ledPin4 4
#define ledPin5 5
#define ledPin6 6

#define switchingButton 10
#define choosingButton 11

long randNum;
int chances;
long currentSuspect;
boolean isFound;

int suspects[6] = {1,2,3,4,5,6};

void setup() {

  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);

  pinMode(switchingButton, INPUT_PULLUP);
  pinMode(choosingButton, INPUT_PULLUP);


 

}

void loop() {
    Serial.println("");
    Serial.println("Witaj detektywie! \nSystem wychwycił 6-ciu potencjalnych sprawców morderstwa sprzed kilku miesięcy. \nNiestety tylko 3-ech z nich jest w stanie dokładniej sprawdzić. \nDecyzja, których należy już do ciebie! \nPowodzenia!");
    Serial.println("");
    
    for (int i = 0;i<3;i++){
    
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    digitalWrite(ledPin5, HIGH);
    digitalWrite(ledPin6, HIGH);
    delay(200);

    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, LOW);
    digitalWrite(ledPin6, LOW);
    delay(200);
    
  }

  
   randNum = random(1,7);
   chances = 3;
   currentSuspect = 1;
   isFound = false;
   suspects[0]=1;
   suspects[1]=2;
   suspects[2]=3;
   suspects[3]=4;
   suspects[4]=5;
   suspects[5]=6;
   
   digitalWrite(ledPin1, HIGH);
   digitalWrite(ledPin2, HIGH);
   digitalWrite(ledPin3, HIGH);
   digitalWrite(ledPin4, HIGH);
   digitalWrite(ledPin5, HIGH);
   digitalWrite(ledPin6, HIGH);

   
   while(!isFound && chances>0){

     Serial.println("Podejrzany nr "+String(currentSuspect)+". (Szanse: "+String(chances)+"):");
     
     while(digitalRead(switchingButton)==HIGH && !isFound && chances>0){
        digitalWrite(currentSuspect+1,LOW);
        if(digitalRead(choosingButton)==LOW){
          checkWhetherFound();
          break;
        }
        delay(200);
        digitalWrite(currentSuspect+1,HIGH);
        if(digitalRead(choosingButton)==LOW){
          checkWhetherFound();
          break;
        }
        delay(200);
     }
     if(!isFound && chances>0){
       Serial.println("");
       Serial.println("Przełączam podejrzanego...");
       delay(1000);
       if(suspects[currentSuspect-1]!=0){
        digitalWrite(currentSuspect+1,HIGH);
       }
       do{
          currentSuspect+=1;
          if(currentSuspect == 7){currentSuspect = 1;}
       }while(suspects[currentSuspect-1]==0);
     }
   }

   if(chances<=0){
     digitalWrite(ledPin1, LOW);
     digitalWrite(ledPin2, LOW);
     digitalWrite(ledPin3, LOW);
     digitalWrite(ledPin4, LOW);
     digitalWrite(ledPin5, LOW);
     digitalWrite(ledPin6, LOW);
     Serial.println("");
     Serial.println("Skończyły nam się szanse detektywie!");
     delay(3000);
     digitalWrite(randNum+1,HIGH);
     Serial.println("Mordercą był podejrzany nr "+String(randNum)+".");
     delay(5000);
   }
}

void checkWhetherFound(){
   digitalWrite(currentSuspect+1,HIGH);
   Serial.println("Sprawdzam podejrzanego...");
   delay(1000);
   if(currentSuspect!=randNum){
      digitalWrite(currentSuspect+1,LOW);
      Serial.println("");
      Serial.println("Niestety, to nie jest morderca!");
      suspects[currentSuspect-1] = 0;
      chances=chances - 1;
     
    } else {
            for(int i=1;i<7;i++){
              if(i!=randNum){
                digitalWrite(i+1,LOW);
              }
            }
            digitalWrite(randNum+1,HIGH);
            Serial.println("");
            Serial.println("Tak jest! Znalazłeś mordercę!");
            delay(5000);
            isFound=true;
                  
    }
}
