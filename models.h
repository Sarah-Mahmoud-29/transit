#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct tripRecord{
 string vehicleName;
 double distance;
 double price;

};



class Vehicle{
    protected:
    int id;
    string name;
    bool isAvailable;
    double baseFare;

public:

    Vehicle( int id, string name,double baseFare)
    :id(id) ,name(name) ,baseFare(baseFare),isAvailable(true)  {}

    int getId(){
    return id;
    }

    string getName(){
    return name;
    }

    bool getIsAvalible(){
    return isAvailable;
    }

    double getBaseFare(){
    return baseFare;
    }

    void setAvailability(bool status){
     isAvailable=status;
    }

    virtual double calculateFare(double distance)=0;

    virtual void showDetails(){
    cout<<"ID : "<<id<<endl;
    cout<<"Name : "<<name<<endl;
    cout<<"Base Fare : "<<baseFare<<endl;
    cout<<"Status : "<<(isAvailable ? "Available":"Booked")<<endl;
    }

    virtual ~Vehicle(){}

};

class Bus:public Vehicle{
public:

    Bus(int id, string name,double baseFare): Vehicle(id,name,baseFare){}

    double calculateFare(double distance){
    return baseFare+distance;
    }
};

class Car:public Vehicle{
public:

    Car(int id, string name,double baseFare): Vehicle(id,name,baseFare){}

    double calculateFare(double distance){
    return baseFare*distance;
    }

 };

class Scooter:public Vehicle{
 public:

     Scooter(int id, string name,double baseFare): Vehicle(id,name,baseFare){}

    double calculateFare(double distance){
    return baseFare+(2*distance);
    }
 };

 class Wallet{
double money;

public:

    Wallet(){
    money=0.0;
    }

    void deposit(double M){
        money+=M;
        cout<<"add money complete"<<endl;
    }

    double getBalance(){
    return money;
    }

    bool deductFare(double price){
        if(price <= money){
            money-=price;
            return true;
        }
        return false;
    }

};

 class Trip{

vector<tripRecord>allTrip;

public:

    bool getAllTrip(){
    if(allTrip.empty())
        return false;
    return true;
    }

    void displayTripHistory(){
    for(int i=0;i<allTrip.size();i++){

        cout<<"type : "<<allTrip[i].vehicleName<<"\n";
        cout<<"distance : "<<allTrip[i].distance<<"\n";
        cout<<"paid: "<<allTrip[i].price<<"\n";
        cout<<"---------------------------------------------------------------------"<<endl;
     }
    }

   double createTrip(Vehicle * vehical,double dis){
     return vehical->calculateFare(dis);
    }

    void addTrip(tripRecord trip){
        allTrip.push_back(trip);
        cout<<"complete booking"<<endl;
    }
};


class Account{


vector<pair<string,string>> userInfo;

public:

  void signUp(){
     pair<string,string> user ;

     cout<<"enter name"<<endl;
     cin>> user.first;
     cout<<"enter password"<<endl;
     cin>>user.second;

     userInfo.push_back(user);
     cout<<"complete register"<<endl;
    }

    bool login(){
     string name,password;

     cout<<"enter name"<<endl;
     cin>>name;
     cout<<"enter password"<<endl;
     cin>>password;

    for(int i=0;i<userInfo.size();i++){
        if(password==userInfo[i].second&& userInfo[i].first==name)
            return true;
    }
    return false;
    }

};

