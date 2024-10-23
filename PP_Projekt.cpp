#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Vehicle{
protected:
    int vehicleID;
    string make;
    string model;
    float rentalRate;
    bool isAvailable;
public:
    Vehicle(int id,string mk,string mdl,float rate)
        : vehicleID(id),make(mk),model(mdl),rentalRate(rate),isAvailable(true){}

    virtual float calculateRent(int days){
        return days*rentalRate;
    }

    void rentVehicle(){
        if(isAvailable){
            isAvailable=false;
            cout<<"Vehicle rented successfully!"<<endl;
        }else{
            cout<<"Vehicle is already rented!"<<endl;
        }
    }

    void returnVehicle(){
        isAvailable=true;
        cout<<"Vehicle returned successfully!"<<endl;
    }

    bool getAvailability()const{
        return isAvailable;
    }

    int getVehicleID()const{
        return vehicleID;
    }

    virtual void displayInfo()const{
        cout<<"Vehicle ID: "<<vehicleID<<", Make: "<<make
             <<", Model: "<<model<<", Rental Rate: $"<<rentalRate<<"/day"<<endl;
    }

    virtual ~Vehicle(){}
};

class Car:public Vehicle{
private:
    int seats;
    string transmissionType;
public:
    Car(int id,string mk,string mdl,float rate,int st,string tt)
        : Vehicle(id,mk,mdl,rate),seats(st),transmissionType(tt){}

    float calculateRent(int days)override{
        float rent=days*rentalRate;
        if(days>7){
            rent*=0.9;
        }
        return rent;
    }

    void displayInfo()const override{
        Vehicle::displayInfo();
        cout<<"Seats: "<<seats<<", Transmission: "<<transmissionType<<endl;
    }
};

class Bike:public Vehicle{
private:
    int cc;
    string gearType;
public:
    Bike(int id,string mk,string mdl,float rate,int c,string gt)
        : Vehicle(id,mk,mdl,rate),cc(c),gearType(gt){}

    float calculateRent(int days)override{
        return days*rentalRate;
    }

    void displayInfo()const override{
        Vehicle::displayInfo();
        cout<<"Engine Capacity: "<<cc<<"cc, Gear Type: "<<gearType<<endl;
    }
};

class Bus:public Vehicle{
private:
    int passengerCapacity;
    string busType;
public:
    Bus(int id,string mk,string mdl,float rate,int capacity,string type)
        : Vehicle(id,mk,mdl,rate),passengerCapacity(capacity),busType(type){}

    float calculateRent(int days)override{
        float rent=days*rentalRate;
        if(busType=="AC"){
            rent*=1.15;
        }
        return rent;
    }

    void displayInfo()const override{
        Vehicle::displayInfo();
        cout<<"Passenger Capacity: "<<passengerCapacity<<", Bus Type: "<<busType<<endl;
    }
};

class RentalSystem{
private:
    vector<Vehicle*> vehicles;
public:
    void addVehicle(Vehicle* v){
        vehicles.push_back(v);
    }

    void displayAvailableVehicles(){
        for(auto v:vehicles){
            if(v->getAvailability()){
                v->displayInfo();
                cout<<"------------------------"<<endl;
            }
        }
    }

    void rentVehicle(int vehicleID,int days){
        for(auto v:vehicles){
            if(v->getAvailability()&&vehicleID==v->getVehicleID()){
                v->rentVehicle();
                cout<<"Rent for "<<days<<" days: $"<<v->calculateRent(days)<<endl;
                return;
            }
        }
        cout<<"Vehicle not available for rent!"<<endl;
    }

    void returnVehicle(int vehicleID){
        for(auto v:vehicles){
            if(!v->getAvailability()&&vehicleID==v->getVehicleID()){
                v->returnVehicle();
                return;
            }
        }
        cout<<"Vehicle not found!"<<endl;
    }

    ~RentalSystem(){
        for(auto v:vehicles){
            delete v;
        }
    }
};

void addVehicleDynamically(RentalSystem& system){
    int vehicleType;
    int vehicleID;
    string make,model;
    float rentalRate;
    cout<<"\nEnter Vehicle ID: ";
    cin>>vehicleID;
    cout<<"Enter Make: ";
    cin>>make;
    cout<<"Enter Model: ";
    cin>>model;
    cout<<"Enter Rental Rate (per day): ";
    cin>>rentalRate;
    cout<<"Choose vehicle type:\n1. Car\n2. Bike\n3. Bus\nEnter your choice: ";
    cin>>vehicleType;

    if(vehicleType==1){
        int seats;
        string transmissionType;
        cout<<"Enter number of seats: ";
        cin>>seats;
        cout<<"Enter transmission type (Automatic/Manual): ";
        cin>>transmissionType;
        system.addVehicle(new Car(vehicleID,make,model,rentalRate,seats,transmissionType));
        cout<<"Car added successfully!\n";
    }else if(vehicleType==2){
        int cc;
        string gearType;
        cout<<"Enter engine capacity (cc): ";
        cin>>cc;
        cout<<"Enter gear type (Manual/Automatic): ";
        cin>>gearType;
        system.addVehicle(new Bike(vehicleID,make,model,rentalRate,cc,gearType));
        cout<<"Bike added successfully!\n";
    }else if(vehicleType==3){
        int passengerCapacity;
        string busType;
        cout<<"Enter passenger capacity: ";
        cin>>passengerCapacity;
        cout<<"Enter bus type (AC/Non-AC): ";
        cin>>busType;
        system.addVehicle(new Bus(vehicleID,make,model,rentalRate,passengerCapacity,busType));
        cout<<"Bus added successfully!\n";
    }else{
        cout<<"Invalid vehicle type!\n";
    }
}

int main(){
    RentalSystem system;
    int choice,vehicleID,days;
    while(true){
        cout<<"\n1. Add a vehicle\n2. Display available vehicles\n3. Rent a vehicle\n4. Return a vehicle\n5. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                addVehicleDynamically(system);
                break;
            case 2:
                system.displayAvailableVehicles();
                break;
            case 3:
                cout<<"Enter vehicle ID to rent: ";
                cin>>vehicleID;
                cout<<"Enter number of days: ";
                cin>>days;
                system.rentVehicle(vehicleID,days);
                break;
            case 4:
                cout<<"Enter vehicle ID to return: ";
                cin>>vehicleID;
                system.returnVehicle(vehicleID);
                break;
            case 5:
                return 0;
            default:
                cout<<"Invalid choice! Try again."<<endl;
        }
    }
}

