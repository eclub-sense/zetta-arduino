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
#define SENSOR_COUNT 3


String command = "";  
byte command_termination = 0;
byte previous=0;

void setup() {
  Serial.begin(9600);
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
    if(tmp[i]){
      Serial.print("senzor ");
      Serial.println(i); 
    } 
  }
  
  Serial.println("AT+REQUEST END");
}
