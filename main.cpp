#include <stdio.h>
#include "FLTK_HEADERS.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Goods.h"
#include "Date.h"
#include "File_Manipulate.h"

using namespace std;


// Global Variables
int when = 0;
Fl_Input *input[15];
Fl_Output *result;
Fl_Button * b[8];
Fl_Output *sName;
Fl_Output *sPric;
Fl_Output *sCatg;
Fl_Output *sCode;
Fl_Output *sStor;
Fl_Output *bName;
Fl_Output *bPric;
Fl_Output *bCatg;
Fl_Output *bCode;
Fl_Output *bStor;
Fl_Output *pleasepay;
Fl_Output *change;
Fl_Box  *uiSearch;
Fl_Box  *uiBuy;
Fl_Window *window = new Fl_Window(840,650);



int searchCode;
Date today;
Date startDate,endDate;
vector<Goods> WareHouse;
vector<Purchase_action> History;
vector<Purchase_action> Customer;
vector<ProfitPerDay> statistic;


Goods* fR;
double totalPrice=0;
double totalProfit=0;
double Received=0;


#include "FLTK_functions.h"


int main(int argc, char **argv) {
    
    // Read the list of Goods First
    vector<Goods>::iterator it;
    WareHouse = inputFromFile();
    outputFile(WareHouse);
    
    // the following two lines set the correct color scheme, so that
    // calling fl_contrast below will return good results
    Fl::args(argc, argv);
    Fl::get_system_colors();
    
    window->resizable(window);
    
    //======================== User Interface ========================
    uiSearch = new Fl_Box(FL_FRAME_BOX,10,20,350,170,"Search Section");
    uiSearch -> align(FL_ALIGN_TOP);
    
    uiBuy = new Fl_Box(FL_FRAME_BOX,400,20,420,260,"Trading Section");
    uiBuy -> align(FL_ALIGN_TOP);
    
    cu = new profitCurve(0,0,1000,1000);
    
    //======================== Input ========================
    // Search for Goods Area
    int datex=150, datey = 220;
    input[0] = new Fl_Int_Input(80,30,130,25,"Barcode:");
    input[0]->tooltip("The Barcode you would like to search for.");
    
    // Buying Section
    input[1] = new Fl_Int_Input(470,30,130,25,"Barcode:");
    input[1]->tooltip("Enter the barcode of Product to buy.");
    
    input[2] = new Fl_Int_Input(650,30,50,25,"Num:");
    input[2]->tooltip("Enter the number of Product.");
    
    input[3] = new Fl_Float_Input(530,220,100,25,"Received:");
    input[3]->tooltip("Enter the amout of money received.");
    
    input[4] = new Fl_Float_Input(datex,datey,30,25,"Today(mm/dd/yyyy):");
    input[4]->tooltip("What date would you like today? :-)");
    input[7] = new Fl_Float_Input(datex,datey+40,30,25,"Start(mm/dd/yyyy):");
    input[10] = new Fl_Float_Input(datex,datey+70,30,25,"End(mm/dd/yyyy):");
    
    datex+=32;
    
    input[5] = new Fl_Float_Input(datex,datey,30,25,"");
    input[8] = new Fl_Float_Input(datex,datey+40,30,25,"");
    input[11] = new Fl_Float_Input(datex,datey+70,30,25,"");
    
    datex+=32;
    
    input[6] = new Fl_Float_Input(datex,datey,40,25,"");
    input[9] = new Fl_Float_Input(datex,datey+40,40,25,"");
    input[12] = new Fl_Float_Input(datex,datey+70,40,25,"");
    
    datex+=45;
    
    //======================== Button ========================
    b[0] = new Fl_Button(230,30,60,25,"Search");
    b[0]->callback(ReadCode);  //Read in the Search barcode
    b[1] = new Fl_Button(720,30,50,25,"Buy");
    b[1]->callback(Buy);  //Read in the Search barcode
    b[2] = new Fl_Button(650,250,105,25,"Print Receipt");
    b[2]->callback(PrintReceipt);  //Read in the Search barcode
    b[4] = new Fl_Button(datex,220,80,25,"SetDate");
    b[4]->callback(setDate);    //Set the date of today
    b[5] = new Fl_Button(datex,275,115,25,"SetSearchDate");
    b[5]->callback(tabulation); //Read in the Search barcode
    
    //======================== Output ========================
    int x = 75, y = 60, xl = 230;
    sName = new Fl_Output(x,y,xl,20,"Name");y += 23;
    sPric = new Fl_Output(x,y,xl,20,"Price");  y += 23;
    sCatg = new Fl_Output(x,y,xl,20,"Category");  y += 23;
    sCode = new Fl_Output(x,y,xl,20,"Barcode");  y += 23;
    sStor = new Fl_Output(x,y,xl,20,"Storage");  y += 23;
    x+=390; y = 60;
    bName = new Fl_Output(x,y,xl,20,"Name");y += 23;
    bPric = new Fl_Output(x,y,xl,20,"Price");  y += 23;
    bCatg = new Fl_Output(x,y,xl,20,"Category");  y += 23;
    bCode = new Fl_Output(x,y,xl,20,"Barcode");  y += 26;
    bStor = new Fl_Output(x,y,xl,20,"Storage\n(after)");  y += 35;
    pleasepay = new Fl_Output(x,y,xl,20,"&Total:");
    change = new Fl_Output(530,250,100,25,"Change:");
    
    
    window->show(argc,argv);
    window->end();
    
    return Fl::run();
}
