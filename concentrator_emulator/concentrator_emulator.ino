/*
přijetí dotazu po sériový lince

vygenerovat počet paketů 0-3 (0 o něco víckrát)
vytvořit pakety
zašifrovat?
odeslat

00000001:41:1234567890123
00000002:41:1234567890123
00000003:41:1234567890123
*/
#define SENSOR_COUNT 10


String command = "";  
byte command_termination = 0;
byte previous=0;

void setup() {
  Serial.begin(19200);
  command.reserve(200);

}

void loop() {
}

void serialEvent() {
  if(readCommand(Serial.read())){
    if(command.equals("AT+REQUEST?")){
      sendRandomPackets();
    } else {
      Serial.println("AT+UNKNOWN");
    }
    command="";  
  }  
}

boolean readCommand(byte incoming){  
  boolean finished = false;
  if(incoming==10){
    if(previous==13)finished=true;    
  } else if(incoming!=13){
    command+=(char)incoming;  
  }
  previous=incoming;
  return finished;
}

void sendRandomPackets(){
  int count=0;
  boolean tmp[SENSOR_COUNT];
  
  for(int i=0;i<SENSOR_COUNT;i++){
    if(random(3)==2){
      count++;
      tmp[i]=true;   
    } else {
      tmp[i]=false;  
    }
  }
  
  Serial.print("AT+REQUEST START,");
  Serial.println(count);
  for(int i=0;i<SENSOR_COUNT;i++){
    if(tmp[i])sendPacket(i); 
  }
  
  Serial.println("AT+REQUEST END");
}

void sendPacket(int i){
  

  byte packetBytes[32];

  //UUID (4)
  packetBytes[0]=0;
  packetBytes[1]=0;
  packetBytes[2]=0;
  packetBytes[3]=i;


  //SHOULD BE ENCRYPTED BY XOR
  //INCR (1)
  packetBytes[4]=0;

  //TYPE (1)
  packetBytes[5]=0x41;
  if(i>7){
    packetBytes[5]=0x42;
  }


  //BATTERY (1)
  packetBytes[6]=0xFF;

  //RESERVED (3)
  packetBytes[7]=0;
  packetBytes[8]=0;
  packetBytes[9]=0;

  //PAYLOAD (21)
  
  //first byte data
  packetBytes[10]=random(256);
  //second byte data
  packetBytes[11]=random(256);
  if(i>7){
    packetBytes[11]=0;
  }
  
  //rest is blank
  for(int j=0;j<20;j++){
    packetBytes[12+j]=0;
  }

  //CRC (1) - in payload temporarily
  //0-30

  
  for(int j=0;j<32;j++){
    if(packetBytes[j] < 16)Serial.print("0");
    Serial.print(packetBytes[j], HEX);
  }
  Serial.println();

  
}





