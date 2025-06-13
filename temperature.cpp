#include <iostream>
using namespace std;

float tempcin;
float tempfin;

int ctof( float tempc)
{
    float tempConvertedF = (9.0*tempc)/5 + 32;
    cout<<"\n Temperature in Celcius : "<<tempc<<endl;
    cout<<"\n Temperature in Fahrenheit : "<<tempConvertedF<<endl;
    return 0;
}

int ftoc( float tempf)
{
    float tempConvertedC = (5.0*(tempf - 32))/9;
    cout<<"\n Temperature in Fahrenheit : "<<tempf<<endl;
    cout<<"\n Temperature in Celcius : "<<tempConvertedC<<endl;
    return 0;
}

int main()
{
    int choice;
    cout <<"\n 1 - Convert Celcius to Fahrenheit"<<endl;
    cout <<"\n 2 - Convert Fahrenheit to Celcius"<<endl;
    cout <<"\n Choose one of the options :"<<endl;
    cin>>choice;

    switch (choice)
    {
    case 1:
        cout<<"Enter the temperature to be converted : "<<endl;
        cin>>tempcin;
        ctof(tempcin);
        break;
    case 2:
        cout<<"Enter the temperature to be converted : "<<endl;
        cin>>tempfin;
        ftoc(tempfin);
        break;
    
    default:
        cout <<"Invalid selection!"<<endl;
        break;
    }

    return 0;
}