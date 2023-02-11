#include <Nextion.h>

NexText t3 = NexText(0, 1, "t3");
NexText t4 = NexText(0, 2, "t4");
NexText t5 = NexText(0, 3, "t5");

String data = "";
String toplam_gerilim = "";
String sicaklik = "";
String soc = "";
String buff = "";

void setup()  {
  Serial.begin(115200);
  Serial2.begin(9600);
  dbSerialPrintln("setup begin");
  nexInit();
  dbSerialPrintln("setup done");
}

void loop() {     
  if(Serial2.available()>0){ 
    char temp = (char)Serial2.read();
  //  Serial.println(temp);
    if(temp == '*'){
      int i = 0;
      int sect = 0;
    
      while(data[i]!='\0'){    
        if(data[i]==','){
          if(sect == 0){
            toplam_gerilim = buff;
            buff = "";
            sect++;
          }
          else if(sect == 1){
            sicaklik = buff;
            buff = "";
            sect++;
          }
          else if(sect == 2){
            soc = buff;
            buff = "";
            sect = 0;
            break;
          }
        }
        else{
          buff += data[i];    
        }
        i++;
      }
      Serial.println(toplam_gerilim);
      Serial.println(sicaklik);
      Serial.println(soc);
    
      toplam_gerilim = toplam_gerilim.substring(0, toplam_gerilim.indexOf('.')+3);
      sicaklik = sicaklik.substring(0, sicaklik.indexOf('.')+3);
      soc = soc.substring(0, soc.indexOf('.')+3);

      t3.setText(toplam_gerilim.c_str());
      t4.setText(sicaklik.c_str());
      t5.setText(soc.c_str());
      Serial.println(data);
      data="";
 
    }
    else{
      data+= temp;  
      
    }
    
  }
  //Serial.println(data);
  
}
