//
//  File_Manipulate.cpp
//  dazuoye
//
//  Created by 袁犇 on 2016/12/18.
//  Copyright © 2016年 2. All rights reserved.
//

#include <stdio.h>
#include "Goods.h"
#include <vector>
#include <fstream>
#include <string>

using namespace std;

vector<Goods> inputFromFile ()
{
    ifstream input("./List.txt");
    int entry;
    vector<Goods>   WareHouse;
    vector<Goods>:: iterator it;
    string name;
    string type;
    int barcode;
    double price;
    string unit;
    double inprice;
    int storage;
    string note;
    entry = 0;
    while (input)
    {
        
        input >> name>> type>> barcode>> price>> unit>> inprice >>storage >> note;
        if(input.fail()) {
            break;
        }
        if (barcode <9999999)
        {
            cout<< "Wrong Barcode in file"<<barcode<<endl;
            barcode = -1;
        }
        for (it = WareHouse.begin(); it != WareHouse.end(); it++)
        {
            if (it->showcode() == barcode)
            {
                cout<< "Barcode Duplicated in the input file!"<<endl;
                break;
            }
        }
        Goods temp(name, type, barcode, price, unit, inprice, storage, note,0);
        WareHouse.push_back(temp);
        entry++;
    }
    return WareHouse;
}

void outputFile (vector<Goods> list)
{
    ofstream output ("./WareHouse.txt");
    vector<Goods>:: iterator it;
    for (it = list.begin(); it != list.end(); it++)
    {
        output<<it->showname()<<"\t\t"<<it->showtype()<<"\t\t"<<it->showcode()<<"\t\t"<<
        it->showprice()<<"\t\t"<<it->showunit()<<"\t\t"<<it->showinprice()<<"\t\t"<<
        it->showstorage()<<"\t\t"<<it->shownote()<<endl;
    }
}

