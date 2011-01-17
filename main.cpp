#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cstdlib>
#include <map>
#include <utility>
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std;
ofstream plik;

class Element{

public:
    Element():zdeptane(false), wartosc(0), id(0){
   near[0]=near[1]=near[2]=near[3]=-1;
    }
    Element( const Element& ele){
                near[0]=ele.near[0];
                near[1]=ele.near[1];
                near[2]=ele.near[2];
                near[3]=ele.near[3];
                zdeptane=ele.zdeptane;
                wartosc=ele.wartosc;
                id=ele.id;
    }

    Element(int id, int wartosc):
    id(id), wartosc(wartosc), zdeptane(false){
                near[0]=-1;
                near[1]=-1;
                near[2]=-1;
                near[3]=-1;
    }

    int near[4];
    bool zdeptane;
    int wartosc;
    int id;


    ~Element(){};
};

class Macierz{
    
    int m,n;
  public:
   Macierz(vector<Element> *elem, int m_, int n_):m(m_),n(n_){
       elementy=elem;
       int k=0;

           
       for(int i=0; i<m; i++)
           for(int j=0; j<n; j++)
           {       
               elementy->push_back( Element(k, rand()%1000) );
               elementy_wsk[ make_pair(i, j) ] = k;
               k++;
           }

       for(unsigned int i=1; i<m-1; i++)
           for(unsigned int j=1; j<n-1; j++)
           {
          elementy->at( elementy_wsk[  make_pair( i, j ) ] ).near[0]=elementy_wsk[ make_pair(i-1, j) ];//gora
          elementy->at( elementy_wsk[  make_pair( i, j ) ] ).near[1]=elementy_wsk[ make_pair(i, j+1) ];//prawo
          elementy->at( elementy_wsk[  make_pair( i, j ) ] ).near[2]=elementy_wsk[ make_pair(i+1, j) ];//dol
          elementy->at( elementy_wsk[  make_pair( i, j ) ] ).near[3]=elementy_wsk[ make_pair(i, j-1) ];//lewo
           }
           
       for(unsigned int i=1; i<n-1; i++)
       {
         //gorny brzeg bez naroznikow
          elementy->at( elementy_wsk[  make_pair( 0, i ) ] ).near[2]=elementy_wsk[ make_pair(1, i) ];//dol
          elementy->at( elementy_wsk[  make_pair( 0, i ) ] ).near[1]=elementy_wsk[ make_pair(0, i+1) ];//prawo
          elementy->at( elementy_wsk[  make_pair( 0, i ) ] ).near[3]=elementy_wsk[ make_pair(0, i-1) ];//lewo
         //dolny brzeg bez naroznikow
          elementy->at( elementy_wsk[  make_pair( m-1, i ) ] ).near[0]=elementy_wsk[ make_pair(m-2, i) ];//gora
          elementy->at( elementy_wsk[  make_pair( m-1, i ) ] ).near[1]=elementy_wsk[ make_pair(m-1, i+1) ];//prawo
          elementy->at( elementy_wsk[  make_pair( m-1, i ) ] ).near[3]=elementy_wsk[ make_pair(m-1, i-1) ];//lewo
       }

       for(unsigned int i=1; i<m-1; i++)
       {
         //lewy brzeg bez naroznikow
           elementy->at( elementy_wsk[  make_pair( i, 0 ) ] ).near[1]=elementy_wsk[ make_pair(i, 1) ];//prawo
           elementy->at( elementy_wsk[  make_pair( i, 0 ) ] ).near[0]=elementy_wsk[ make_pair(i-1, 0) ];//gora
           elementy->at( elementy_wsk[  make_pair( i, 0 ) ] ).near[2]=elementy_wsk[ make_pair(i+1, 0) ];//dol
         //prawy brzeg bez naroznikow
           elementy->at( elementy_wsk[  make_pair( i, n-1 ) ] ).near[3]=elementy_wsk[ make_pair(i,   n-2) ];//lewo
           elementy->at( elementy_wsk[  make_pair( i, n-1 ) ] ).near[2]=elementy_wsk[ make_pair(i+1, n-1) ];//dol
           elementy->at( elementy_wsk[  make_pair( i, n-1 ) ] ).near[0]=elementy_wsk[ make_pair(i-1, n-1) ];//gora
       }

       //lewy gorny naroznik
           elementy->at( elementy_wsk[  make_pair( 0, 0 ) ] ).near[1]=elementy_wsk[ make_pair(0, 1) ];//prawo
           elementy->at( elementy_wsk[  make_pair( 0, 0 ) ] ).near[2]=elementy_wsk[ make_pair(1, 0) ];//dol
       //lewy dolny naroznik
           elementy->at( elementy_wsk[  make_pair( m-1, 0 ) ] ).near[1]=elementy_wsk[ make_pair(m-1, 1) ];//prawo
           elementy->at( elementy_wsk[  make_pair( m-1, 0 ) ] ).near[0]=elementy_wsk[ make_pair(m-2, 0) ];//gora
       //prawy gorny naroznik
           elementy->at( elementy_wsk[  make_pair( 0, n-1 ) ] ).near[3]=elementy_wsk[ make_pair(0, n-2) ];//lewo
           elementy->at( elementy_wsk[  make_pair( 0, n-1 ) ] ).near[2]=elementy_wsk[ make_pair(1, n-1) ];//dol
       //prawy dolny naroznik
           elementy->at( elementy_wsk[  make_pair( m-1, n-1 ) ] ).near[3]=elementy_wsk[ make_pair(m-1, n-2) ];//lewo
           elementy->at( elementy_wsk[  make_pair( m-1, n-1 ) ] ).near[0]=elementy_wsk[ make_pair(m-2, n-1) ];//gora
           
           
        for(int i=0; i<m; i++){
           for(int j=0; j<n; j++)
           {
               if(
                  elementy->at( elementy_wsk[  make_pair( i, j ) ] ).near[0]!=-1 &&//gora
                  elementy->at( elementy_wsk[  make_pair( i, j ) ] ).near[1]!=-1&&//prawo
                  elementy->at( elementy_wsk[  make_pair( i, j ) ] ).near[2]!=-1&&//dol
                  elementy->at( elementy_wsk[  make_pair( i, j ) ] ).near[3]!=-1)//lewo
               {
                   cout.width(1);
                cout<<"C";//Center
                plik.width(1);
                plik<<"C";
               }else{
                   cout.width(1);
                   cout<<"B";//Border
                plik.width(1);
                plik<<"B";
               }
           }
           plik<<endl;
           
           cout<<endl;

        }

   }

    map< pair<unsigned int, unsigned int>, unsigned int> elementy_wsk;
    vector<Element> *elementy;


    void rysuj_wartosci(){
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                cout.width(5);
                cout<< elementy->at( elementy_wsk[  make_pair( i, j ) ] ).wartosc<<" ";
                plik.width(5);
                plik<< elementy->at( elementy_wsk[  make_pair( i, j ) ] ).wartosc<<" ";
            }
            cout<<endl;
            plik<<endl;
        }
    }

    void rysuj_ids(){
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                cout.width(5);
                cout<< elementy->at( elementy_wsk[  make_pair( i, j ) ] ).id<<" ";
                plik.width(5);
                plik<< elementy->at( elementy_wsk[  make_pair( i, j ) ] ).wartosc<<" ";
            }
            cout<<endl;
            plik<<endl;
        }
    }

    void rysuj_zdeptanie(){
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                cout<< elementy->at( elementy_wsk[  make_pair( i, j ) ] ).zdeptane<<" ";
                plik<< elementy->at( elementy_wsk[  make_pair( i, j ) ] ).zdeptane<<" ";
            }
            cout<<endl;
            plik<<endl;
            
        }
    }
    
  ~Macierz(){
      
  }

};



int id_akt_element;

class IW{
public:
    IW():id(-1),wartosc(-1){}
    IW( int id, int wartosc ):id(id), wartosc(wartosc){}

    int wartosc;
    int id;
};

bool porownanie(const IW& a, const IW& b)
{
  return a.wartosc<b.wartosc;
}; 



int znajdz_max_sasiada( vector<Element> *elementy ){

    vector<IW> lista_aktywnych_sasiadow;

    for(int i=0;i<4; i++){
        int id_tmp_sasiada=(*elementy)[ id_akt_element ].near[i];
        if( id_tmp_sasiada!=-1 )
        {
            if( !((*elementy)[ id_tmp_sasiada ].zdeptane ))
             lista_aktywnych_sasiadow.push_back( IW(id_tmp_sasiada, (*elementy)[ id_tmp_sasiada ].wartosc ) );
        }
    }

    if(lista_aktywnych_sasiadow.size()<1 )return -1;
    
    sort(lista_aktywnych_sasiadow.begin(), lista_aktywnych_sasiadow.end(), porownanie  );
    for(int i=0; i<lista_aktywnych_sasiadow.size(); i++){
         cout<<endl<<"Wartosc sasiada "<<(*elementy)[ lista_aktywnych_sasiadow[i].id ].wartosc;
         plik<<endl<<"Wartosc sasiada "<<(*elementy)[ lista_aktywnych_sasiadow[i].id ].wartosc;
    }
    int id_max=lista_aktywnych_sasiadow.back().id;

   return id_max;
}

bool wykonaj_krok( vector<Element> *elementy )
{

//==========max sasiad
    (*elementy)[ id_akt_element ].zdeptane=true;
    
   int _id_max=znajdz_max_sasiada( elementy );
        if(_id_max==-1)
            return false; //koniec algorytmu
 //cout<<endl<<"Akt max w wykonajkrok="<<(*elementy)[_id_max].wartosc;
 //cout<<endl<<"Akt id_akt_element="<<id_akt_element<<endl;

    if ( !((*elementy)[ _id_max ].zdeptane) ){

        (*elementy)[ _id_max ].zdeptane=true;
        id_akt_element=_id_max;
       // cout<<endl<<"Wykonalem w ifie id_akt_element="<<id_akt_element;
        return true;
    }
    
    return true;
}


int main(int argc, char** argv) {

           srand( time(NULL));
    unsigned int i_0=1;
    unsigned int j_0=1;
    unsigned int m,n;

    plik.open("wyniki.txt");
    
    cout<<endl<<"Podaj rozmiar macierzy (m, n):"<<endl<<"Podaj m= ";
    cin>>m;
    cout<<endl<<"Podaj n= ";
    cin>>n;
    cout<<endl<<"Podaj polozenie poczatkowe (i_0, j_0) w macierzy : "<<endl;
    cout<<endl<<"Podaj i_0= ";
    cin>>i_0;
    cout<<endl<<"Podaj j_0= ";
    cin>>j_0;
    
    vector<Element> *elementy = new vector<Element>() ;
    Macierz macierz_elementow( elementy , m, n );
    
    elementy->at( macierz_elementow.elementy_wsk[  make_pair( i_0, j_0 ) ] ).zdeptane=true;
    id_akt_element=elementy->at( macierz_elementow.elementy_wsk[  make_pair( i_0, j_0 ) ] ).id;
            
    macierz_elementow.rysuj_wartosci();
    macierz_elementow.rysuj_ids();
cout<<endl<<"Jestem na : "<<(*elementy)[ id_akt_element ].wartosc<<endl;
plik<<endl<<"Jestem na : "<<(*elementy)[ id_akt_element ].wartosc<<endl;
    macierz_elementow.rysuj_zdeptanie();

    
    while( true ){
         system("PAUSE");
         cout<<endl<<"============================================"<<endl;
         plik<<endl<<"============================================"<<endl;
        if( wykonaj_krok( elementy ) )
        {
        cout<<endl;
        plik<<endl;
        macierz_elementow.rysuj_zdeptanie();
        cout<<endl<<"Jestem na : "<<(*elementy)[ id_akt_element ].wartosc<<endl;
        plik<<endl<<"Jestem na : "<<(*elementy)[ id_akt_element ].wartosc<<endl;
         
        }else
            break;
         cout<<endl<<"============================================"<<endl;
         plik<<endl<<"============================================"<<endl;
    }

    cout<<endl<<"Koniec..."<<endl;
    plik.close();
    system("PAUSE");

    return 0;
}

