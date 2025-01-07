int secuencia[] = {3,5,6}, secuenciaa = 0,retardo;//pines PWM
bool boton;
char bt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(secuencia[0],OUTPUT);
  pinMode(secuencia[1],OUTPUT);
  pinMode(secuencia[2],OUTPUT);
  pinMode(12,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  bt = Serial.read();
  boton = digitalRead(12);
  retardo = 250;
  
  if(bt == '2' || boton == 1){
    delay(retardo);
    secuenciaa ++;
    Serial.println(secuenciaa);
    if(secuenciaa > 1){
      secuenciaa = 0;
    }
  }

  if(secuenciaa == 0){
    for(int i = 0;i <= 255; i++){
      bt = Serial.read();
      boton = digitalRead(12);
      if(bt == '2' || boton == 1){
        delay(retardo);
        secuenciaa++;
        }
      if(secuenciaa == 1){
        break;
      }
      digitalWrite(secuencia[1],LOW);
      digitalWrite(secuencia[2],LOW);
      analogWrite(secuencia[0],i);
      if(i == 255){
        for(int i = 0;i <= 200; i++){
          bt = Serial.read();
          boton = digitalRead(12);
          if(bt == '2' || boton == 1){
            delay(retardo);
            secuenciaa++;
            }
          else if(secuenciaa == 1){
            break;
          }
          else {
            delay(10);
          }
        }
      }
      delay(5);
    }
    
    for(int i = 255;i >= 0; i--){
      bt = Serial.read();
      boton = digitalRead(12);
      if(bt == '2' || boton == 1){
        delay(retardo);
        secuenciaa++;
        }
      if(secuenciaa == 1){
        break;
      }
        analogWrite(secuencia[0],i);
        delay(5);
    }
    for(int i = 0;i <= 255; i++){
      bt = Serial.read();
      boton = digitalRead(12);
      if(bt == '2' || boton == 1){
        delay(retardo);
        secuenciaa++;
        }
      if(secuenciaa == 1){
        break;
      }
        analogWrite(secuencia[1],i);
        if(i == 255){
        for(int i = 0;i <= 200; i++){
          bt = Serial.read();
          boton = digitalRead(12);
          if(bt == '2' || boton == 1){
            delay(retardo);
            secuenciaa++;
            }
          else if(secuenciaa == 1){
            break;
          }
          else {
            delay(10);
          }
        }
      }
        delay(5);
    }
    
    for(int i = 255;i >= 0; i--){
      bt = Serial.read();
      boton = digitalRead(12);
      if(bt == '2' || boton == 1){
        delay(retardo);
        secuenciaa++;
        }
      if(secuenciaa == 1){
        break;
      }
        analogWrite(secuencia[1],i);
        delay(5);
    }
  
    for(int i = 0;i <= 255; i++){
      bt = Serial.read();
      boton = digitalRead(12);
      if(bt == '2' || boton == 1){
        delay(retardo);
        secuenciaa++;
        }
      if(secuenciaa == 1){
        break;
      }
        analogWrite(secuencia[2],i);
        if(i == 255){
        for(int i = 0;i <= 200; i++){
          bt = Serial.read();
          boton = digitalRead(12);
          if(bt == '2' || boton == 1){
            delay(retardo);
            secuenciaa++;
            }
          else if(secuenciaa == 1){
            break;
          }
          else {
            delay(10);
          }
        }
      }
        delay(5);
    }
    
    for(int i = 255;i >= 0; i--){
      bt = Serial.read();
      boton = digitalRead(12);
      if(bt == '2' || boton == 1){
        delay(retardo);
        secuenciaa++;
        }
      if(secuenciaa == 1){
        break;
      }
        analogWrite(secuencia[2],i);
        delay(5);
    }
  }
    if(secuenciaa == 1){
      digitalWrite(secuencia[0],HIGH);
      digitalWrite(secuencia[1],HIGH);
      digitalWrite(secuencia[2],HIGH);
    }
}
