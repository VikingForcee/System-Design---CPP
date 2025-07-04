#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

enum class VehicleType {Car, Motorcycle, Truck};

class Vehicle{
    private:
        VehicleType type;
        string number;   // Car number for identification
        bool incoming;   // Is it incoming or outgoing
        int time;   //Time of Entry or Exit to aid the concurreny issue or wait list.
    public:
        Vehicle(string number, bool incoming, int time){
            this->number = number;
            this->incoming = incoming;
            this->time = time;
        }

        // To get the Values of Car Incoming/ Outgoing
        string getNumber(){ return number; }
        int getTime(){ return time; }
        bool getIncoming(){ return incoming; }

        // To set the Values of Car Incoming/ Outgoing
        void setNumber(string str){ number = str; }
        void setTime(int time){ this->time = time; }
        void setIncoming(bool inc){ incoming = inc; }

};


class ParkingLot{
    private:
        vector<vector<Vehicle*>> lot;   //hashtable storing the car Space
        unordered_map<string, pair<int,int>> vehicleToSpot;
    
    public:
        ParkingLot(int levels, int slotsPL){
            lot = vector<vector<Vehicle*>>(levels, vector<Vehicle*>(slotsPL, nullptr));
        }
        
        bool assignSpot(Vehicle* v, VehicleType type){
            int start, end;

            if(type == VehicleType::Car) {
                start = 0; end = 49;
            }
            else if(type == VehicleType::Motorcycle) {
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
    Vehicle* V1 = new Vehicle("CH1101", true, 0);
    Vehicle* V2 = new Vehicle("CH1102", true, 0);

    P1.assignSpot(V1, VehicleType::Car);
    P1.assignSpot(V2, VehicleType::Truck);

    P1.releaseSpot(V1);

    delete V1;
    delete V2;
    return 0;
}