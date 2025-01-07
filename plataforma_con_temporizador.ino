int subir=7, bajar = 8, pulsador = 11, fcarriba = 10, fcabajo = 9, temporizadorbajar = 1, temporizadorsubir = 1;
long tiempoarriba = 180000, tiempoabajo = 30000, temp = 0;
bool boton,farriba,fabajo;
char bt = '0';

void setup() {
  // put your setup code here, to run once:
  pinMode(pulsador,INPUT);
  pinMode(fcarriba,INPUT);
  pinMode(fcabajo,INPUT);
  pinMode(subir, OUTPUT);
  pinMode(bajar, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  farriba = digitalRead(fcarriba);
  fabajo = digitalRead(fcabajo);
  boton = digitalRead(pulsador);
  
  if (temporizadorsubir == 1 && boton == 0 && fabajo == 1){
    Serial.begin(9600);
    digitalWrite(subir,LOW);
    digitalWrite(bajar,LOW);
    for(temp;temp <= tiempoabajo; temp ++){
      bt = Serial.read();
      boton = digitalRead(pulsador);
      fabajo = digitalRead(fcabajo);
      if(bt == '1' || boton == 1){
        temporizadorsubir = 0;
        break;
      }
      else if(fabajo == 0){
        break;
      }
      else{
        delay(10);
      }
    }
    if(fabajo == 1){
    temporizadorsubir = 0;
    temporizadorbajar = 1;
    temp = 0;
    }
    else{
      temp = 0;
    }
    }
  else if(temporizadorsubir == 0 && farriba == 0){
    Serial.end();
    digitalWrite(subir,HIGH);
    digitalWrite(bajar,LOW);
    }
  else if (temporizadorbajar == 1 && boton == 0 && farriba == 1){
    Serial.begin(9600);
    digitalWrite(subir,LOW);
    digitalWrite(bajar,LOW);
    for(temp = 0;temp <= tiempoarriba; temp ++){
      bt = Serial.read();
      boton = digitalRead(pulsador);
      farriba = digitalRead(fcarriba);
      if(bt == '1' || boton == 1){
        temporizadorbajar = 0;
        break;
      }
      else if(farriba == 0){
        break;
      }
      else{
        delay(10);
      }
    }
    if(farriba == 1){
    temporizadorsubir = 1;
    temporizadorbajar = 0;
    temp = 0;
    }
    else{
      temp = 0;
    }
  }
  else if(temporizadorbajar == 0 && fabajo == 0){
    Serial.end();
    digitalWrite(subir,LOW);
    digitalWrite(bajar,HIGH);
  }
  else{
    digitalWrite(subir,LOW);
    digitalWrite(bajar,LOW);
  }
}
