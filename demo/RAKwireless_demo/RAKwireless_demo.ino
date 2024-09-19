// #include <WiFi.h>
#include "RAK12029_LDC1614.h" 
#define BLINKER_WIFI
#include <Blinker.h>

#define INDUCTANCE   13.000  //13.00  ——————> 电感值
#define CAPATANCE    100.0   //100.00 ————> 焊盘对应的寄生电容值
#define GETCHANNEL   LDC1614_CHANNEL_0 
#define BLINKER_WIFI  
RAK12029_LDC1614_Inductive ldc;

char auth[] = "a6596e39abe3";
char ssid[]     = "mmlab206";
char password[] = "mmlab206";

BlinkerNumber CH1("channel1"); //数据组件名
BlinkerNumber CH2("channel2");
BlinkerNumber CH3("channel3");
BlinkerNumber CH4("channel4");

u32 channel1_read = 0, channel2_read = 0, channel3_read = 0, channel4_read = 0;
// WiFiServer server(80);

void dataStorage()
{
    Blinker.dataStorage("channel1", channel1_read); //数据组件名，数据值
    Blinker.dataStorage("channel2", channel2_read);
    Blinker.dataStorage("channel3", channel3_read); //数据组件名，数据值
    Blinker.dataStorage("channel4", channel4_read);
}

void setup()
{
    // Serial.begin(115200);
    // Serial.println();
    // Serial.println();
    // Serial.print("Connecting to ");
    // Serial.println(ssid);

    // WiFi.begin(ssid, password);

    // while (WiFi.status() != WL_CONNECTED) {
    //     delay(500);
    //     Serial.print(".");
    // }

    // Serial.println("");
    // Serial.println("WiFi connected.");
    // Serial.println("IP address: ");
    // Serial.println(WiFi.localIP());
    
    // server.begin();

  BLINKER_DEBUG.stream(Serial);
  BLINKER_DEBUG.debugAll();
  Blinker.begin(auth, ssid, password);
  Blinker.attachDataStorage(dataStorage);

  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, LOW);

  pinMode(WB_IO2, OUTPUT);
  digitalWrite(WB_IO2, HIGH);
  delay(300);

  pinMode(WB_IO5, OUTPUT);
  digitalWrite(WB_IO5, LOW);

  time_t timeout = millis();
  Serial.begin(115200);
  while (!Serial)
  {
    if ((millis() - timeout) < 5000)
    {
      delay(100);
    }
    else
    {
      break;
    }
  }

  Serial.println("RAK12029 TEST");
  // delay(1000);
  ldc.LDC1614_init();

  if (ldc.LDC1614_mutiple_channel_config(INDUCTANCE, CAPATANCE) != 0)
  {
    Serial.println("can't detect sensor!");
    while (1) delay(100);
  }
}

int value = 0;

void loop(){
//  WiFiClient client = server.available();   
  Blinker.run();
  // if (client) {                             
  //   Serial.println("New Client.");           
  //   String currentLine = "";                
  //   while (client.connected()) {            
  //     if (client.available()) {             
  u16 value = 0;
  ldc.IIC_read_16bit(LDC1614_READ_DEVICE_ID, &value);
  if (value == 0x3055)
  {
    u32 ChannelBuf[4] = {0};
    client.println("------------------------------------------------------------");
    for (uint8_t channelCount = 0; channelCount < 4; channelCount++)
    {
      // delay(100);
      if (ldc.LDC1614_get_channel_result(3 - channelCount, &ChannelBuf[channelCount]) == 0) //
      {
        if (0 != ChannelBuf[channelCount])
        {
          // client.printf("The result channel %d is:%d\r\n", channelCount + 1, ChannelBuf[channelCount]);
          // Serial.printf("The result channel %d is:%d\r\n", channelCount + 1, ChannelBuf[channelCount]);
          
          if(channelCount==0)
          {
            channel1_read = ChannelBuf[channelCount];
            CH1.print(ChannelBuf[channelCount]);
            // Blinker.log("The result channel %d is:%d\r\n", channelCount + 1, ChannelBuf[channelCount]);
            Serial.printf("The result channel %d is:%d\r\n", channelCount + 1, ChannelBuf[channelCount]);
          }
          if(channelCount==1)
          { 
            channel2_read = ChannelBuf[channelCount];
            CH2.print(ChannelBuf[channelCount]);
            // Blinker.log("The result channel %d is:%d\r\n", channelCount + 1, ChannelBuf[channelCount]);
            Serial.printf("The result channel %d is:%d\r\n", channelCount + 1, ChannelBuf[channelCount]);
          }
          if(channelCount==2)
          {
            channel3_read = ChannelBuf[channelCount];
            CH3.print(ChannelBuf[channelCount]);
            // Blinker.log("The result channel %d is:%d\r\n", channelCount + 1, ChannelBuf[channelCount]);
            Serial.printf("The result channel %d is:%d\r\n", channelCount + 1, ChannelBuf[channelCount]);
          }
          if(channelCount==3)
          { 
            channel4_read = ChannelBuf[channelCount];
            CH4.print(ChannelBuf[channelCount]);
            // Blinker.log("The result channel %d is:%d\r\n", channelCount + 1, ChannelBuf[channelCount]);
            Serial.printf("The result channel %d is:%d\r\n", channelCount + 1, ChannelBuf[channelCount]);
          }
          digitalWrite(LED_BLUE, HIGH);
        }
      }
    }
    client.println("------------------------------------------------------------");
    client.println();
    // delay(500);
    digitalWrite(LED_BLUE, LOW);
    // delay(500);
  }
  else
  {
    client.println("The IIC communication fails,please reset the sensor!");
    // delay(500);
  }
}
//     }
//   }
// }
