//
//  Goods.h
//  dazuoye
//
//  Created by 袁犇 on 2016/12/18.
//  Copyright © 2016年 2. All rights reserved.
//

#ifndef Goods_h
#define Goods_h

#include <iostream>
#include <string>
#include "Date.h"
using namespace std;

class Goods {
private:
    string name;
    string type;
    int barcode;
    double price;
    string unit;
    double inprice;
    int storage;
    string note;
    double profit;
    
public:
    Goods():name("N/A"),type("N/A"),barcode(-1),price(-1),
    unit("N/A"),inprice(-1),storage(-1),note("N/A"),profit(0.0){}
    
    explicit Goods
    (string na, string ty, int ba,double pr,
     string un, double in,int st, string no, double pro)
    
    :name(na),type(ty),barcode(ba),price(pr),
    unit(un),inprice(in),storage(st),note(no),profit(pro){}
    
    string  showname()  {return name;}
    string  showtype()  {return type;}
    int     showcode()  {return barcode;}
    double  showprice() {return price;}
    string  showunit()  {return unit;}
    double  showinprice(){return inprice;}
    int     showstorage(){return storage;}
    string  shownote()  {return note;}
    double  showprofit(){return profit;}
    
    // Setting values for Goods
    void setname(string na) { name = na;}
    void settype(string ty) { type = ty;}
    void setcode(int ba)
    {
        if (barcode>99999)  barcode = ba;
        else cout<<"Bad Barcode!!"<<endl;
        //!!! if the same!!!
    }
    void setprice(double pr)
    {
        if (pr > 0 )price = pr;
        else cout<<"Bad Price!!"<<endl;
    }
    void setunit    (string un) { unit = un;}
    void setinprice (double pr) { inprice = pr;}
    void setstorge  (int st)    { storage = st;}
    void sold       (int num)  {storage -= num;}
    void setnote    (string no) { note = no; }
    void setprofit  (double pro) { profit = pro; }
    
    // Delete a goods (Wipe the information)
    void delGoods()
    {
        name = "N/A"; type  =   "N/A";  barcode =   -1; price   =   -1;
        unit = "N/A"; inprice=  -1;     storage =   -1; note    =   "N/A";
        profit = 0.0;
    }
    
    void display()
    {
        cout<<
        "Name:\t"<<name<<endl<<"Type:\t"<<type<<endl<<"Barcode:\t"<<barcode<<endl<<
        "Price:\t"<<price<<endl<<"Unit:\t"<<unit<<endl<<"Inprice:\t"<<inprice<<endl<<
        "Storage:\t"<<storage<<endl<<"Note:\t"<<note<<endl<<"Profit:\t"<<profit<<endl
        <<endl;
        
    }
};

Goods ghost;

class Purchase_action {
public:
    Goods goods;
    int count;
    Date dat;
    double profit;
    Purchase_action():goods(ghost),count(0),dat(null),profit(0){}
    explicit Purchase_action(Goods g, int c, Date d, double p):
    goods(g),count(c),dat(d),profit(p){}
};

class ProfitPerDay{
public:
    double profit;
    Date date;
    ProfitPerDay(Date d, double p):profit(p),date(d){};
    ProfitPerDay():profit(0),date(null){};
    
    void setProfitPerDay(Date d, double p)
    {
        date.setDate(d.year(), d.month(), d.day());
        profit = p;
    }
    
    void addProfit(double add)
    {
        profit += add;
    }
};


Goods& FindGoods (int code, vector<Goods>& WareHouse)
{
    vector<Goods>::iterator it;
    for (it = WareHouse.begin(); it != WareHouse.end(); it++)
    {
        if (code == it->showcode())
        {
            return *(it);
        }
    }
    cerr<<"Error: No such Goods!"<<endl;
    return ghost;
}

#endif /* Goods_h */
