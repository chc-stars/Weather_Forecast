#ifndef WEATHER_DATA_H
#define WEATHER_DATA_H
#include <QString>

class Today{
public:
   Today()
   {
       date = "2022-10-20";
       city = "广州";

       ganmao = "感冒指数";

       wendu = 0;
       shidu = "0%";
       pm25 = 0;
       quality = "无数据";

       type = "多云";

       fl = "2级";
       fx = "南风";

       high = 30;
       low = 18;

   }

   QString date;
   QString city;
   QString ganmao, shidu, quality, fx, fl, type;

   int wendu, pm25, high, low;


};

class Day{
public:
    Day(){
        date = "2022-10-20";
        week = "周五";

        type = "多云";

        high = 0;
        low = 0;

        fx = "南风";
        fl = "2级";

        aqi = 0;

    }

    QString date, week, type, fx, fl;
    int aqi, high, low;

};



#endif // WEATHER_DATA_H
