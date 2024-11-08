

#include "Seeed_LDC1612.h"
LDC1612 sensor;


void setup()
{
    Serial.begin(115200);
    delay(100);
    Serial.println("start!");

    sensor.init();

    if(sensor.single_channel_config(CHANNEL_0))
    {
        Serial.println("can't detect sensor!");
        while(1);
    }


}


void loop()
{
    u32 result_channel0 = 0;
    // u32 result_channel1 = 0;
    // uint32_t result_channel2 = 0;

    /*shows the status of sensor.*/
    // sensor.get_sensor_status();  //在不使用的时候，注释掉

    /*Get channel 0 result and parse it.*/
    sensor.get_channel_result(CHANNEL_0,&result_channel0);
    // sensor.get_channel_result(CHANNEL_0,&result_channel1);

    /*sensor result value.you can make a lot of application according to its changes.*/
    // if(0!=result_channel1)
    if(0!=result_channel0)
    {
        Serial.print("result_channel0 is ");
        // Serial.println(result_channel1);
        Serial.println(result_channel0);

    }
    delay(100);
}



