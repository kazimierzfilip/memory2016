//---------------------------------------------------------------------------

#include <vcl.h>
#include <cstdio>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int points=0;         // Punkty gracza

int jeden;          //Indeks pierwszej ods�oni�tej katy

int x;        // 0/1 - losowanie zestawu obrazk�w

int ile;      // licznik ods�onietych kart

int tura=0;    //Czyja jest tura 0/1

int zero;        //punkty gracza 1

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

struct karty           //struktura karty i tablica wszystkich kart na stole
{
    TImage *a;
    int nr;           // numer obrazka przypisywany przez losowanie
}tab[12];
//---------------------------------------------------------------------------

void enabler(bool p)
{
    for(int i=0;i<12;i++)
    {
      tab[i].a->Enabled=p;
    }
}

//---------------------------------------------------------------------------

AnsiString sciezka(int nr)          // podaje sciezke odpowiednich obrazkow rozlosowanych przy tworzeniu formy
{

    if(x==0)              //Zmiana obrazk�w �eby si� nie nudzi�o
    {
      switch(nr)
      {
       case 0: return "img/1.bmp"; break;
       case 1: return "img/2.bmp"; break;
       case 2: return "img/3.bmp"; break;    //�cie�ki obrazk�w
       case 3: return "img/4.bmp"; break;
       case 4: return "img/5.bmp"; break;
       case 5: return "img/6.bmp"; break;
     }
    }
    else
    {
      switch(nr)
      {
       case 0: return "img/7.bmp"; break;
       case 1: return "img/8.bmp"; break;
       case 2: return "img/9.bmp"; break;
       case 3: return "img/10.bmp"; break;
       case 4: return "img/11.bmp"; break;
       case 5: return "img/12.bmp"; break;
      }
    }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    tab[0].a=karta1;
    tab[1].a=karta2;                    //inicjalizacja struktury kart sto�u
    tab[2].a=karta3;
    tab[3].a=karta4;
    tab[4].a=karta5;
    tab[5].a=karta6;
    tab[6].a=karta7;
    tab[7].a=karta8;
    tab[8].a=karta9;
    tab[9].a=karta10;
    tab[10].a=karta11;
    tab[11].a=karta12;
    enabler(false);
    for(int i=0;i<12;i++)                   //�adowanie sto�u
    {
      tab[i].a->Picture->LoadFromFile("img/rewers.bmp");
      tab[i].a->Visible=true;
    }

    Button1->Visible=false;
    Label1->Caption="Zbierz je wszystkie!";
    points=0;
    tura=0;
    zero=0;
//---------------------------------------------

//---LOSOWANIE OBRAZK�W DO STO�U----
    randomize();
    int tablica[]={0,1,2,3,4,5,6,7,8,9,10,11};  //zbi�r indeks�w kt�ry zagwarantuje niepowtarzalno�� liczb
    x=random(2);   //losowa liczba 0/1 losowaniezbioru obrazk�w
    int r,r2;  //--Losowe--Liczby
    int max=0; // max-- licznik 10. liczb do losowania
    int losowe[10];    //pude�ko liczb losowych
    while(max<10)
    {
       r=random(10-max);            //Losujemy 10. liczb(indeks�w)  z zakres�w  0-10, 0-8...
       r2=random(10-max);
       if(r!=r2)
       {
         losowe[max]=r;           //Potrzebne r�ne od siebie liczby zapisujemy do tablicy
         losowe[max+1]=r2;
         max+=2;
       }
    }
    int i2; //licznik do kasownika
    int i; //licznik przypisanych kart
    for(i=0;i<10;i+=2)
    {
        tab[tablica[losowe[i]]].nr=i/2;    //przypisujemy losowej karcie cyfr� i/2
        for(i2=losowe[i];i2<11-i;i2++)
        {
          tablica[i2]=tablica[i2+1];        //kasujemy numer wylosowanej karty z puli
        }
        tablica[i2]=0;

        tab[tablica[losowe[i+1]]].nr=i/2;     //przypisujemy innej losowej karcie cyfr� i/2
        for(i2=losowe[i+1];i2<10-i;i2++)
        {
        tablica[i2]=tablica[i2+1];           //kasujemy numer wylosowanej 2. karty z puli
        }
        tablica[i2]=0;
    }
    tab[tablica[0]].nr=i/2;            //przypisujemy 2. ostatnim kartom cyfr� i/2
    tab[tablica[1]].nr=i/2;
    Button2->Caption="START";
    Button2->Visible=true;
}

//---------------------------------------------------------------------------

void gra(int kto)          //Pozwala ods�ania� karty, zlicza punkty itd.
{
    enabler(false);    //Zamro�enie sto�u
   if(ile==0)   //kiedy liczba ods�onietych kart=0
   {
     tab[kto].a->Picture->LoadFromFile("img/orewers.bmp");
     Application->ProcessMessages(); Sleep(800);                 //ods�oni�cie karty
     tab[kto].a->Picture->LoadFromFile(sciezka(tab[kto].nr));
     jeden=kto;                                              //zapis indeksu pierwszej wybranej karty
     ile++;
   }
   else if(jeden!=kto && ile==1)    //kiedy liczba ods�onietych kart=1
   {
     ile++;
     tab[kto].a->Picture->LoadFromFile("img/orewers.bmp");
     Application->ProcessMessages(); Sleep(800);
     tab[kto].a->Picture->LoadFromFile(sciezka(tab[kto].nr));
   }
   if(ile==2)    //kiedy ods�oniete 2 karty
   {
   Application->ProcessMessages(); Sleep(800);
      if(tab[jeden].nr==tab[kto].nr)
      {
         points++;
         if(tura==0)zero++;
         Form1->Label1->Caption="+1";
         tab[kto].a->Visible=false;
         tab[jeden].a->Visible=false;
      }
      else
      {
        tab[kto].a->Picture->LoadFromFile("img/rewers.bmp");
        tab[jeden].a->Picture->LoadFromFile("img/rewers.bmp");
      }
      (tura==0)?tura=1:tura=0;
      ile=0;
      if(points>=6)      //---Czy Koniec---
      {
         Form1->Button1->Visible=true;
         Form1->Label1->Caption= "Koniec.\n Gracz 1: "+IntToStr(zero)+"\n Gracz 2: "+IntToStr(points-zero);
         return;
      }
   }
   enabler(true);   //Odmro�enie sto�u
   if(tura==0)Form1->Label1->Caption="Gracz1";else Form1->Label1->Caption="Gracz2";
}

//---------------------------------------------------------------------------

void __fastcall TForm1::karta1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   gra(0);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::karta2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   gra(1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::karta3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    gra(2);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::karta4MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    gra(3);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::karta5MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   gra(4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::karta6MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   gra(5);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::karta7MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   gra(6);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::karta8MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   gra(7);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::karta9MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   gra(8);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::karta10MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    gra(9);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::karta11MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   gra(10);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::karta12MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    gra(11);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
   Label1->Caption="Gracz1";
   enabler(true);
   Button2->Visible=false;
}
//---------------------------------------------------------------------------

