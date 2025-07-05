#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Vehicle{
    private:
        string number;   // Car number for identification
        bool incoming;   // Is it incoming or outgoing
        int time;   //Time of Entry or Exit to aid the concurreny issue or wait list.
        string type;    
    public:
        Vehicle(string number, bool incoming, int time, string type){
            this->number = number;
            this->incoming = incoming;
            this->time = time;
            this->type = type;
        }

        // To get the Values of Car Incoming/ Outgoing
        string getNumber(){ return number; }
        int getTime(){ return time; }
        bool getIncoming(){ return incoming; }
        string getType(){ return type; }

        // To set the Values of Car Incoming/ Outgoing
        void setNumber(string str){ number = str; }
        void setTime(int time){ this->time = time; }
        void setIncoming(bool inc){ incoming = inc; }

};

class GenerateTicket{
    private:
        int ticketNum;
    public:
        GenerateTicket(){
            this->ticketNum = 0;
        }

        void setTicket(int i, int j){
            ticketNum++;
            cout << "Your ticket number is" << " " << ticketNum << endl; 
            cout << "Your Spot is : " << i << "th Floor & " << j << "th Number" << endl;
        }
};

class ParkingLot : GenerateTicket{
    private:
        vector<vector<Vehicle*>> lot;   //hashtable storing the car Space
        unordered_map<string, pair<int,int>> vehicleToSpot;
    
    public:
        ParkingLot(int levels, int slotsPL){
            lot = vector<vector<Vehicle*>>(levels, vector<Vehicle*>(slotsPL, nullptr));
        }
        
        bool assignSpot(Vehicle* v){
            int start, end;
            
            string type = v->getType();

            if(type == "Car") {
                start = 0; end = 49;
            }
            else if(type == "Motorcycle") {
                start = 50; end = 89;
            }
            else{
                start = 90; end = 99;
            }

            for(int level = 0; level < lot.size(); level++){
                for(int i = start; i <= end; i++){
                    if(lot[level][i] == nullptr){
                        lot[level][i] = v;
                        vehicleToSpot[v->getNumber()] = {level, i};  // Mapping for future release and lookout
                        setTicket(level, i);
                        return true;
                    }
                }
            }
            return false;
        }

        bool releaseSpot(Vehicle* v){
            string num = v->getNumber();
            if(vehicleToSpot.count(num)){
                auto [level, index] = vehicleToSpot[num];
                lot[level][index] = nullptr;
                vehicleToSpot.erase(num);
                return true;
            }
            
            return false;
        }
};




int main(){
    ParkingLot P1(10, 100);
    GenerateTicket G1;

    Vehicle* V1 = new Vehicle("CH1101", true, 0, "Car");
    Vehicle* V2 = new Vehicle("CH1102", true, 0, "Car");
    Vehicle* V3 = new Vehicle("CH1103", true, 0, "Truck");
    Vehicle* V4 = new Vehicle("CH1104", true, 0, "Truck");
    Vehicle* V5 = new Vehicle("CH1105", true, 0, "Motorcycle");
    Vehicle* V6 = new Vehicle("CH1106", true, 0, "Car");
    Vehicle* V7 = new Vehicle("CH1107", true, 0, "Motorcycle");

    P1.assignSpot(V1);
    P1.assignSpot(V2);
    P1.assignSpot(V3);
    P1.assignSpot(V4);
    P1.assignSpot(V5);
    P1.assignSpot(V6);
    P1.assignSpot(V7);

    P1.releaseSpot(V1);

    delete V1;
    delete V2;
    return 0;
}