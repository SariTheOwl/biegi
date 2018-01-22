#include <iostream>
#include <vector> // 6.wykorzystanie biblioteki STL
#include <fstream>
#include <string>
#include "Users.h"
#include "Runner.h"
#include "Races.h"
using namespace std;
vector<Users> users;
vector<Runner> runner;
vector<Races> races;
void Show_Admin_Options()
{
    cout<<"1.Zaloz konto Biegacza"<<endl;
    cout<<"2.Dodaj biegi"<<endl;
    cout<<"3.Wprowadz rezultaty biegu dla wybranego biegacza"<<endl;
}
void Show_Runner_Options()
{
    cout<<"1.Pokaz wyniki biegow "<<endl;
    cout<<"2.Oblicz sredni czas wszystkich biegow "<<endl;
}
void Load() //5. Wczytanie stanu apki
{
 fstream frunners;
 fstream fusers;
 fstream frace;
 frunners.open("Runners.txt");
 fusers.open("Users.txt");
 frace.open("Race.txt");

 while( !frunners.good() )
    {
     Runner *s1 = new Runner;
     runner.push_back(*s1);
     runner.back().Add(runner.size(),frunners);
    }
  frunners<<'\b \b';
 while( !fusers.good() )
    {
     Users *s1 = new Users;
     users.push_back(*s1);
     users.back().Add(users.size(),fusers);
    }
    fusers<<'\b \b';
    while( !frace.good() )
    {
     Races *s1 = new Races;
     races.push_back(*s1);
     races.back().Add(races.size(),frace);
    }
  frace<<'\b \b';
  frunners.close();
  frace.close();
  fusers.close();
}

void Save() //5. Zapis odczytu apki
{
 fstream frunners;
 fstream fusers;
 fstream frace;
 frunners.open("Runners.txt");
 fusers.open("Users.txt");
 frace.open("Race.txt");
 for(int i=0;i<runner.size()-1;i++)
    {

          runner[i].Save(frunners);
    }
    frunners<<'\b \b';
 for(int i=0;i<users.size()-1;i++)
    {

          users[i].Save(fusers);
         fusers<<endl;


    }
   fusers<<'\b \b';
 for(int i=0;i<races.size()-1;i++)
    {
          races[i].Save(frace);
    }
  frace<<'\b \b';
  frunners.close();
  frace.close();
  fusers.close();
}

int main()
{
    int log,pass,option=1;
    string login,password;
    Load();
    log_in:
    cout <<"login"<<endl;
    cin>>login;
    log=users[0].Log_Check(-1,login,users);
    if (log==-1)
    {
        cout<<"Login nie istnieje - podaj login ponownie"<<endl;
        goto log_in;
    }
    pass_word:
    cout<<"haslo"<<endl;
    cin>>password;
    pass=users[0].Log_Check(log,password,users);
    if (pass==-1)
    {
        cout<<"Bledne haslo - podaj haslo ponownie"<<endl;
        goto pass_word;
    }

    switch (pass)
    {
    case 0:
        {
            users[log].Welcome();
            while(option)
            {
                Show_Runner_Options();
                cin>>option;
                switch(option)
                {
                case 1:
                    {
                        runner[log].Show();
                    }
                case 2:
                    {

                    }

                }
            break;
            }
        }
    case 1:
        {
            users[log].Welcome();
            while(option)
            {
               Show_Admin_Options();
               cin>>option;
               switch(option)
               {
               case 1:
                   {
                        Users *s1 = new Users; //1. dodawanie biegaCZA
                        users.push_back(*s1);
                        users.back().Add(users.size());
                         Runner *s2 = new Runner;
                         runner.push_back(*s1);
                         runner.back().Add(runner.size(),users.back().log,users.back().pass,users.back().fname,users.back().lname);
                        break;
                   }
               case 2:
                   {
                        Races *s1 = new Races; //1. dodawanie biegaCZA
                        races.push_back(*s1);
                        races.back().Add(races.size());
                        break;
                   }
               case 3:
                   {
                       int idw,idb,czas;
                       for (int i=0;i<races.size();i++)
                       {
                           races[i].Show();
                       }
                       cout<<endl<<endl<<"Wybierz bieg."<<endl;
                       cin>>idw;
                       for (int i=0;i<runner.size();i++)
                       {
                           runner[i].Show();
                       }
                       cout<<endl<<endl<<"Wybierz biegacza."<<endl;
                       cin>>idb;
                       cout<<"Wpisz czas."<<endl;
                       cin>>czas;
                       break;
                   }


               }
             Save();
            }
            break;
        }

    }





    return 0;
}
