//
//  FLTK_functions.h
//  dazuoye
//
//  Created by 袁犇 on 2016/12/18.
//  Copyright © 2016年 2. All rights reserved.
//

#ifndef FLTK_functions_h
#define FLTK_functions_h


class profitCurve: public Fl_Widget {
public:
    profitCurve(int x,int y,int w,int h,const char *l=0)
    : Fl_Widget(x,y,w,h,l) {}
    void draw()
    {
        int i = 1;
        char temp[50][30];
        double max_x = 1, max_y = 1e-4;
        int x_start = 50, y_start = 380, x_end, y_end, wid = 300,hei=150;
        double x_step, y_step = 0;
        y_end = y_start + hei;
        x_end = x_start + wid;
        
        // Here I assume that the date of purchasing records
        //  (in vector<ProfitPerDay> statistic) only progresses
        vector<ProfitPerDay>::iterator ista;
        cout<<"===Drawing==="<<endl;
        fl_line(x_start, y_start, x_start, y_end);
        fl_line(x_start, y_end, x_end, y_end);
        
        for (ista = statistic.begin(); ista != statistic.end(); ista++)
        {
            if (max_y < ista->profit ) max_y = ista->profit;
        }
        if (statistic.size() > max_x) max_x = statistic.size();
        
        y_step = hei / max_y;
        x_step = wid / max_x;
        
        fl_color(FL_RED);
        fl_begin_line();
        for (ista = statistic.begin(); ista != statistic.end(); ista++)
        {
            fl_vertex( 10 + i * x_step, y_end - ista->profit *y_step);
            cout<<"x: "<<10 + i * x_step<<" y: "<<ista->profit *y_step;
            ++i;
        }
        fl_end_line();
        
        fl_color(FL_BLACK);
        
        i = 1;
        
        for (ista = statistic.begin(); ista != statistic.end(); ista++)
        {
            sprintf(temp[0], "%2d-%2d",
                    ista->date.month(),ista->date.day());
            sprintf(temp[1], "%5d",ista->date.year());
            fl_draw(temp[0], 10 + i * x_step , y_end+25);
            fl_draw(temp[1], 10 + i * x_step , y_end+40);
            sprintf(temp[1], "%6.2f",ista->profit);
            fl_draw(temp[1], 10 + i * x_step , y_end - ista->profit *y_step-10);
            ++i;
        }
        sprintf(temp[2], "Total Profit: %6.2f" ,totalProfit);
        fl_draw(temp[2], x_start+100 , y_end+70);
        
        // Now for the percentage of each products
        vector<Goods>::iterator iwh;
        int iiwh, x_start_table = 400;
        double sumProfit = -1;
        
        fl_draw("Profit Contribution", x_start_table+80 , y_start-35);
        for(iwh = WareHouse.begin(); iwh!= WareHouse.end(); iwh++)
        {
            sumProfit += iwh->showprofit();
        }
        
        
        for(iwh = WareHouse.begin(); iwh!= WareHouse.end(); iwh++)
        {
            iiwh = int (distance(WareHouse.begin(), iwh));
            sprintf(temp[3], "%s: %6.2f %% ",
                    iwh->showname().c_str(), 100. * iwh->showprofit()/sumProfit );
            fl_draw(temp[3], x_start_table , y_start + iiwh * 25);
        }
        
    }
}*cu;

void ReadCode(Fl_Widget *,void *)
{
    char temp[3][20];
    searchCode = atoi(input[0]->value());
    fR = &FindGoods(searchCode,WareHouse);
    fR->display();
    sprintf(temp[0], "%f",fR->showprice());
    sprintf(temp[1], "%d",fR->showcode());
    sprintf(temp[2], "%d",fR->showstorage());
    
    sName->value(fR->showname().c_str());
    sPric->value(temp[0]);
    sCatg->value(fR->showtype().c_str());
    sCode->value(temp[1]);
    sStor->value(temp[2]);
}

void Buy(Fl_Widget *,void *)
{
    char temp[4][20];
    int num;
    double prof;
    num = atoi(input[2]->value());
    searchCode = atoi(input[1]->value());
    
    fR = &FindGoods(searchCode,WareHouse);
    //fR.display();
    
    if (fR->showstorage() >= num)
    {
        prof = num * (fR->showprice()-fR->showinprice());
        Purchase_action act(*fR,num,today,prof);
        History.push_back(act);
        Customer.push_back(act);
        totalPrice += fR->showprice()*num;
    }
    sprintf(temp[0], "%f",fR->showprice());
    sprintf(temp[1], "%d",fR->showcode());
    if (fR->showstorage() >= num)
    {
        fR->sold(num);
        sprintf(temp[2], "%d",fR->showstorage());
    }
    else   sprintf(temp[2], "This product is sold out!");
    
    bName->value(fR->showname().c_str());
    bPric->value(temp[0]);
    bCatg->value(fR->showtype().c_str());
    bCode->value(temp[1]);
    bStor->value(temp[2]);
    
    sprintf(temp[3], "%8.2f",totalPrice);
    pleasepay->value(temp[3]);
}

void PrintReceipt(Fl_Widget *,void *)
{
    char temp[100];
    Received = atof(input[3]->value());
    sprintf(temp, "%8.2f",Received - totalPrice);
    change->value(temp);
    ofstream output ("./Receipt.txt");
    output<<"Welcome to the Supermarket!"<<endl;
    output<<"==============================="<<endl;
    output<<"Date:(mm/dd/yyyy) "<<today.month()<<'/'<<today.day()<<'/'<<today.year()<<endl;
    output<<"==============================="<<endl;
    sprintf(temp, "Name      Price     Count");
    output<<temp<<endl;
    vector<Purchase_action>::iterator it;
    for ( it = Customer.begin(); it != Customer.end(); it++ )
    {
        sprintf(temp, "%-10s%-10.2f%-10d",
                it->goods.showname().c_str(),
                it->goods.showprice(),
                it->count);
        output<<temp<<endl;
    }
    output<<"==============================="<<endl;
    output<<"Total: "<<totalPrice<<endl;
    output<<"Recieved:"<<Received<<endl;
    output<<"Change:"<<Received - totalPrice<<endl;
    Customer.clear();
    Received = 0;
    totalPrice = 0;
}

void setDate(Fl_Widget *,void *)
{
    int tyear;
    int tmonth;
    int tday;
    tmonth  =   atoi(input[4]->value());
    tday    =   atoi(input[5]->value());
    tyear   =   atoi(input[6]->value());
    cout<< tyear<< tmonth<< tday<<endl;
    today.setDate(tyear, tmonth, tday);
}

void tabulation(Fl_Widget *,void *)
{
    int tyear1, tyear2;
    int tmonth1, tmonth2;
    int tday1, tday2;
    int rp, itr = 0;
    double tempDayProfit=0;
    double* resProfit= new double[WareHouse.size()];
    window->redraw();
    
    for (rp = 0; rp<WareHouse.size(); rp++) {
        resProfit[rp] = 0;
    }
    tmonth1  =   atoi(input[7]->value());
    tday1    =   atoi(input[8]->value());
    tyear1   =   atoi(input[9]->value());
    
    tmonth2  =   atoi(input[10]->value());
    tday2    =   atoi(input[11]->value());
    tyear2   =   atoi(input[12]->value());
    
    startDate.setDate(tyear1, tmonth1, tday1);
    endDate.setDate(tyear2, tmonth2, tday2);
    vector<Purchase_action>::iterator ith;
    vector<ProfitPerDay>::iterator ipd;
    vector<Goods>::iterator ig;
    ProfitPerDay temp;
    
    cout<<"Generating the Table!"<<endl;
    for (ith = History.begin(); ith != History.end(); ith++)
    {
        //cout<<"Year";
        if (ith->dat.year() >= tyear1 && ith->dat.year() <= tyear2)
        {
            //cout<<"Month";
            if (ith->dat.month() >= tmonth1 && ith->dat.month() <= tmonth2)
            {
                //cout<<"Day";
                if (ith->dat.day() >= tday1 && ith->dat.day() <= tday2)
                {
                    tempDayProfit = 0;
                    totalProfit += ith->profit;
                    tempDayProfit += ith->profit;
                    for(ig = WareHouse.begin(); ig!= WareHouse.end(); ig++)
                    {
                        if(ig->showcode() == ith->goods.showcode())
                        {
                            rp = int(distance(WareHouse.begin(), ig));
                            resProfit[rp] += ith->profit;
                            //cout<<ig->showname()<<"  ->  "<<resProfit[rp]<<endl;
                        }
                    }
                    if(itr == 0)
                    {
                        temp.setProfitPerDay(ith->dat,tempDayProfit);
                    }
                    else
                    {
                        if (ith -> dat.day() == temp.date.day() &&
                            ith -> dat.month() == temp.date.month() &&
                            ith -> dat.year() == temp.date.year())
                        {
                            temp.addProfit(tempDayProfit);
                        }
                        else
                        {
                            statistic.push_back(temp);
                            temp.setProfitPerDay(ith->dat,tempDayProfit);
                            cout<<"Pushed"<<endl;
                        }
                    }
                    itr++;
                }
            }
        }
    }
    statistic.push_back(temp);
    
    for(ig = WareHouse.begin(); ig!= WareHouse.end(); ig++)
    {
        rp = int(distance(WareHouse.begin(), ig));
        ig->setprofit(resProfit[rp]);
    }
    
    cu->redraw();
    // Create Multiple Output
}



#endif /* FLTK_functions_h */
