/*  TITULO: Configurar módulo Bluetooth HC-05 mediante comandos AT
 
    AUTOR:
   
    MARIANO DEL CAMPO GARCÍA (@2016) --> INGENIERO TÉCNICO INDUSTRIAL ESPECIALIDAD ELECTRÓNICA
    - FACEBOOK: https://www.facebook.com/mariano.delcampogarcia
    - TWITTER: https://twitter.com/MarianoCampoGa
    - CORREO: marianodc83@gmail.com
   
   
    DESCRIPCIÓN DEL PROGRAMA
   
    Con este programa podemos configurar el módulo Bluetooth HC-05 mediante comandos AT, de la siguiente manera:
    - AT+ORGL: Restauramos los valores por defecto del módulo Bluetooth HC-05. Responde con OK.
      - Modo de trabajo: Modo Esclavo (+ROLE:0).
      - Modo de conexión: Se conecta al módulo Bluetooth especificado (+CMOD:0).
      - Velocidad de transmisión: 38400 bps; Bit de parada: 1 bit; Bit de paridad: Sin paridad (+UART:38400,0,0.)
      - Pin o contraseña: 1234 (+PSWD:1234).
      - Nombre del módulo: “H-C-2010-06-01” o "HC-05" (Se puede modificar pero no nos responde con el nombre)
    - AT: Test de comunicación. Responde con OK.
    - AT+VERSION: Preguntamos por la versión del módulo Bluetooth HC-05. Responde +VERSION:2.0-20100601.
    - AT+UART=X,Y,Z: Configura la velocidad de trasmisión del modulo según el valor de “X” (1200 bps, 2400 bps,
      4800 bps, 9600 bps, 19200 bps, 38400 bps, 57600 bps, 115200 bps, 230400 bps, 460800 bps, 921600 bps y
      1382400 bps. Con el valor de "Y" se configura el bit de parada (0 -> 1 bit y 1-> 2 bits) y con el valor de
      "Z" se configura el bit de paridad (0 -> Sín paridad, 1 -> Paridad impar y 2 -> Paridad Par).
      Con el comando AT+UART=38400,0,0 se configura el módulo Bluetooth HC-05 con una velocidad de comunicación de
      38400 bps, con un bit de parada y sin paridad. Nos responde con OK.
    - AT+UART: Preguntamos por el estado de la comunicación UART. Nos responde con +UART:38400,0,0.    
    - AT+NAME=XXXX: Configura el nombre con el que se visualizara el módulo, soporta hasta 20 caracteres. Por ejemplo
      con el comando AT+NAME=Arduino_HC-05 configura el nombre del modulo a Arduino_HC-05. Responde con OK.
    - AT+PSWD=XXXX: Configura el Pin o la contraseña de acceso al modulo Bluetooth HC-05. Con el comando AT+PSWD=1234
      se configura el pin a 1234. Responde con OK.
    - AT+PSWD: Preguntamos por el pin. Nos responde con +PSWD:1234.
    - AT+CMODE = X: Cambiamos el modo de conexión del módulo (0 -> Se conecta al dispositivo Bluetooth especificado y
      1 -> Se conecta a cualquier dispositivo Bluetooth disponible). Con el comando AT+CMODE = 1 se configura el módulo
      Bluetooth HC-05 para que pueda conectarse a cualquier dispositivo Bluetooth disponible (sin dirección requerida).
      Responde con OK.
    - AT+CMODE: Preguntamos por el modo de conexión del módulo. Responde con +CMOD:1.
    - AT+ROLE = X: Cambiamos el modo de trabajo del módulo (0 -> Modo Esclavo y 1 -> Modo Maestro). Con el comando
      AT+ROLE = 0 configuramos el módulo Bluetooth para que trabaje como Esclavo de otro dispositivo Bluetooth.
      Responde con OK.
    - AT+ROLE: Preguntamos por el modo de trabajo del módulo. Responde con +ROLE:0.  
    Aunque hay multitud de comandos AT, los anteriores son los que vamos a utilizar con una mayor frecuencia.    
   
    **NOTA:
    Para entrar en el modo de comandos AT (LED parpadea cada 2 segundos) tenemos que estar presionando el botón que trae
    el módulo al ejecutar el monitor serie del IDE de Arduino .
   
   
   
    ESQUEMA DE CONEXION
   
                                      +-----+
         +----[PWR]-------------------| USB |--+
         |                            +-----+  |
         |         GND/RST2  [ ][ ]            |
         |       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |  
         |          5V/MISO2 [ ][ ]  A4/SDA[ ] |  
         |                             AREF[ ] |
         |                              GND[ ] |
         | [ ]N/C                    SCK/13[ ] |  
         | [ ]IOREF                 MISO/12[ ] |  
         | [ ]RST                   MOSI/11[ ]~|   Pin RX del módulo Bluetooth HC-05
         | [ ]3V3    +---+               10[ ]~|   Pin TX del módulo Bluetooth HC-05
         | [ ]5v    -| A |-               9[ ]~|   Pin EN del módulo Bluetooth HC-05
         | [ ]GND   -| R |-               8[ ] |   Pin VCC del módulo Bluetooth HC-05
         | [ ]GND   -| D |-                    |
         | [ ]Vin   -| U |-               7[ ] |  
         |          -| I |-               6[ ]~|  
         | [ ]A0    -| N |-               5[ ]~|  
         | [ ]A1    -| O |-               4[ ] |  
         | [ ]A2     +---+           INT1/3[ ]~|  
         | [ ]A3                     INT0/2[ ] |  
         | [ ]A4/SDA  RST SCK MISO     TX>1[ ] |  
         | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[ ] |  
         |            [ ] [ ] [ ]              |
         |  UNO_R3    GND MOSI 5V  ____________/
          \_______________________/
 
 
  NOTAS:
 
   - Alimentación del módulo Bluetooth HC-05:
     - Pin VCC del módulo Bluetooth HC-05 --> Pin digital 8 de Arduino.
     - Pin GND del módulo Bluetooth HC-05 --> GND de Arduino.  
*/
 
  // Añadimos la librería que permite añadir pines para la comunicación serie
  #include <SoftwareSerial.h>
   
  // Definimos el objeto para la comunicación serie
  SoftwareSerial BT(10,11); // 10 RX, 11 TX.
 
  int VCC = 8; // Pin digital para alimentar el módulo Bluetooth HC-05
  int EN = 9; // Pin digital para la habilitación del módulo Bluetooth HC-05
 
 
  void setup()
  {
    pinMode(VCC, OUTPUT); // Pin digital 8 como salida
    pinMode(EN, OUTPUT); // Pin digital 9 como salida
   
    digitalWrite(EN, HIGH);  // Habilitamos el módulo Bluetooth HC-05
    delay(500); // Esperamos 500 ms
    digitalWrite (VCC, HIGH); // Encendemos el módulo Bluetooth HC-05
   
    Serial.begin(9600); // Comienzo la comunicación con el monitor serie  
    BT.begin(38400); // Comienzo de la comunicación con el módulo Bluetooth HC-05 (por defecto)
   
    Serial.println("Esperando comandos AT ... ");
  }
 
  void loop()
  {  
    // Si hay datos disponibles en el monitor serie
    if(Serial.available())
    {
       // Escribimos los valores en el módulo bluetooth HC-05
       BT.write(Serial.read());
    }
   
    // Si hay datos disponibles en el módulo bluetooth HC-05
    if(BT.available())
    {
      // Mostramos los valores en el monitor serie
      Serial.write(BT.read());
    }
  }
