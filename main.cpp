#include <iostream>
#include <vector>
#include "models.h"

using namespace std;

 int main(){

  Account user;
  Wallet  myWallet;
  Trip    tripManegment;

  vector<Vehicle*> fleet;

  fleet.push_back(new Car(101,"Tesla Model 3", 10.0));
  fleet.push_back(new Car(191,"Tesla Model 5", 10.0));

  fleet.push_back(new Bus(201,"Mercedes City Bus", 5.0));
  fleet.push_back(new Bus(399,"Mercedes City Bus", 5.0));
  fleet.push_back(new Bus(222,"Mercedes City Bus", 5.0));

  fleet.push_back(new Scooter(301,"Xiaomi Scooter", 2.0));

  cout<<"1-Register"<<endl<<"2-login"<<endl;
  cout<<"Choice : ";
  int choice;cin>>choice;
  cout<<endl;

  bool log=false;

  if(choice==1){
    user.signUp();
    log=true;
  }
  else if(choice==2){
    if(user.login()){
      cout << "Login successful!\n";
       log=true;
    }
    else{
        cout << "Invalid login!\n";
    }
  }


  while(log){

    cout << "\n==== MENU ====\n";
    cout<<"1-Book Vehicle\n2-My Wallet\n3-Trip History\n4-logout \n";
    int num;
    cout<<"Choice :";cin>>num;
    cout<<endl;


    if(num==1){

    cout<<"Type:\n1-Car\n2-Bus\n3-Scooter\nChoice:";
    int n;cin>>n;
    cout<<endl;

    vector<Vehicle*>sellected;
    for(Vehicle *v :fleet){
        if(n==1&&dynamic_cast<Car*>(v)&&v->getIsAvalible())
           sellected.push_back(v);
        else if(n==2&&dynamic_cast<Bus*>(v)&&v->getIsAvalible())
           sellected.push_back(v);
        else if(n==3&&dynamic_cast<Scooter*>(v)&&v->getIsAvalible())
           sellected.push_back(v);
    }

    if(sellected.empty())
        cout<<"No available vehicle\n";
    else{

        for(Vehicle *v:sellected){
            v->showDetails();
            cout<<"------------------------------------------------------\n";

        }

        double dis;
        int V_id;

        cout<<"Enter id of Vehicle : ";cin>>V_id;
        cout<<endl;
        cout<<"Enter distant : ";cin>>dis;
        cout<<endl;

        Vehicle * chosenVehicle=nullptr;
        for(Vehicle *v :sellected){
            if(v->getId()==V_id){
                chosenVehicle=v;
                break;
            }

        }

        if(chosenVehicle==nullptr)
            cout<<"No matching id"<<endl;
        else if(!chosenVehicle->getIsAvalible())
            cout<<"Sorry, this vehicle is already booked!\n";
        else{

            double totalPrice=tripManegment.createTrip(chosenVehicle,dis);
            cout<<"Total price : "<<totalPrice<<endl;
           cout<<"To continue press 1 else press anything else\n";
           int confirm;cin>>confirm;
           if(confirm==1){
             if(myWallet.deductFare(totalPrice)){
                chosenVehicle->setAvailability(false);
                tripRecord newTrip = {chosenVehicle->getName(), dis, totalPrice};
                tripManegment.addTrip(newTrip);
                cout << "Booking Complete!\n";
             }
           else{
            cout << "Transaction Failed: Insufficient Wallet Balance!\n";
           }

           }
           else
            continue;
        }

    }

    }
    else if(num==2){
        cout << "1- Add Money\n2- Check Balance\n Choice: ";
        int n;cin>>n;
        cout<<endl;

        if(n==1){
        double money;
        cout<<"Enter amount"<<endl;
        cin>>money;
        myWallet.deposit(money);

        }
        else if(n==2){

            cout << "Balance: $" <<myWallet.getBalance()<<endl;
        }
        else{
           cout<<"Invalid number"<<endl;
        }
    }
    else if(num==3){

     if(tripManegment.getAllTrip()){
        tripManegment.displayTripHistory();
     }
     else{
     cout<<"No History"<<endl;
     }

    }
    else{
        cout<<"Logout.....\n";
        break;
    }

  }

for (Vehicle* v : fleet) delete v;


 return 0;
 }
