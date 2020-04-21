
#include "OneWire.h"
bool flag = true;
OneWire ds(12);

float readTemp()
{
  byte data[2];
  //float temp;

  if (flag)
  {
    ds.reset();     // Начинаем взаимодействие со сброса всех предыдущих команд и параметров
    ds.write(0xCC); // Даем датчику DS18b20 команду пропустить поиск по адресу. В нашем случае только одно устрйоство
    ds.write(0x44); // Даем датчику DS18b20 команду измерить температуру. Само значение температуры мы еще не получаем - датчик его положит во внутреннюю память
    //Serial.println(F("send"));
    flag = false;
  }

  else
  {
    ds.reset(); // Теперь готовимся получить значение измеренной температуры
    ds.write(0xCC);
    ds.write(0xBE);      // Просим передать нам значение регистров со значением температуры
    data[0] = ds.read(); // Читаем младший байт значения температуры
    data[1] = ds.read(); // А теперь старший}
    //Serial.println(F("read"));
    flag = true;
    return ((data[1] << 8) | data[0]) * 0.0625;
  }
}