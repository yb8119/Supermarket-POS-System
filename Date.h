//
//  Date.h
//  dazuoye
//
//  Created by 袁犇 on 2016/12/18.
//  Copyright © 2016年 2. All rights reserved.
//

#ifndef Date_h
#define Date_h

class Date{
    int y,m,d;
public:
    Date():y(0),m(0),d(0){};
    Date(int yy, int mm, int dd):y(yy),m(mm),d(dd){};
    void setDate(int y, int m, int d);
    int month(){return m;}
    int day(){return d;}
    int year(){return y;}
};

void Date::setDate(int yy, int mm, int dd)
{
    int sche[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    if(mm>12 || mm<1)
        std::cout<< "Error: Month"<< mm<<std::endl;
    else if(dd>sche[mm-1]||dd<1)
        std::cout<<"Error: Date"<< dd<<' '<<sche[mm]<<std::endl;
    else{
        y = yy;
        m = mm;
        d = dd;
    }
}

Date null;
#endif /* Date_h */
