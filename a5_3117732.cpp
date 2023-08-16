
#include <iostream>

using namespace std;


class Date{
private:
    short unsigned int day, month, year;
public:
    Date(){};
    Date(short unsigned int d, short unsigned int m, short unsigned int y){
      day = d;
      month = m;
      year = y;
    };
    Date  operator+(int days){
        Date d ;
        if((this->day + days) <= 30){
            d.day = this->day + days;
            d.month = this->month;
            d.year = this->year;
        }else{
            days = this->day + days;
            d.month = this->month + 1;
            d.day = days - 30;
            d.year = this->year;
        }
        return d;
    }
    friend ostream& operator<<(ostream& out, Date &d){
        out << d.year << "-" << d.month << "-" << d.day;
    }
    friend istream& operator>>(istream& in, Date& d){
        char sign;
        return in>>d.year>>sign>>d.month>>sign>>d.day;
    }
};

enum  struct Services {no_meals, breakfast, half_board, all_inclusive};

ostream& operator<<(ostream& out, const Services& s){
    switch(s){
    case Services::breakfast:
        return out<<"breakfast";
        break;
    case Services::half_board:
        return out<<"half_board";
        break;
    case Services::all_inclusive:
        return out<<"all_inclusive";
        break;
    default:
        return cout<<"no_meals";
    }
}
float get_price(Services& s){
    switch(s){
    case Services::breakfast:
        return 10.00;
        break;
    case Services::half_board:
        return 20.00;
        break;
    case Services::all_inclusive:
        return 50.00;
        break;
    default:
        return 0.00;
        break;
    }
}
class Accomodation{
private:
    string location;
    Date arrival;
    int nights, singels, doubles;
    float priceNightSingle, priceNightDouble, priceOneDayParking;
    Services board;
    bool parking;
public:
    Accomodation(float pNight, float pDouble, float pParking): priceNightSingle(pNight), priceNightDouble(pDouble){
        ask_data();
    };
    ~Accomodation(){
        cout<<"destructor Accomodation "<< location<<" at "<<arrival<<" for "<<get_guests()<<" guests done"<<endl;
    }
    Date get_arrival(){
        return arrival;
    };
    Date get_checkout(){
        return arrival + nights;
    };
    int get_guests(){
        return ((1*singels) + (2*doubles));
    };
    float get_price(){
        if(parking){
            return nights*(::get_price(board) + (singels*priceNightSingle) + (doubles*priceNightDouble)+ 10);
        }else{
            return nights*(::get_price(board) + (singels*priceNightSingle) + (doubles*priceNightDouble));
        }

    }
    void ask_data (){
        char sign;
        cout<<"location of accomodation: ";
        cin>>location;
        cout<<"arrival on (yyyy-mm-dd): ";
        cin>>arrival;
        cout<<"how many nights (maximum 4 weeks): ";
        cin>>nights;
        cout<<"how many single bed rooms (80.00 EUR/night): ";
        cin>>singels;
        cout<<"how many double bed rooms (150.00 EUR/night): ";
        cin>>doubles;
        char input, input1;
        cout<<"a all inclusive (50.00 EUR/day)"<<endl<<"b breakfast     (10.00 EUR/day)"<<endl<<"h half board    (20.00 EUR/day)"<<endl<<"n no meals"<<endl;
        cin>>input;
        if(input == 'a'){
            board = Services::all_inclusive;
        }else if(input == 'b'){
            board = Services::breakfast;
        }else if(input == 'h'){
            board = Services::half_board;
        }else if(input == 'n'){
            board == Services::no_meals;
        }
        cout<<"your choice: "<<input<<endl;
        cout<<"with parking place (10.00 EUR/day; y(es) or n(o)): ";
        cin>>input1;
        if(input1 == 'y'){
            parking = true;
        }else{
            parking = false;
        }
        cout<<"price: "<<get_price()<<endl;
    };
    void print(){
        Date date1 = get_arrival();
        Date date2 = get_checkout();
        cout<<"accomodation at:    "<<location<<endl;
        cout<<"number of guests:   "<<get_guests()<<endl;
        cout<<"number of nights:   "<<nights<<endl;
        cout<<"check-in date:      "<<date1<<endl;
        cout<<"check-out date:     "<<date2<<endl;
        cout<<"single bed room(s): "<<singels<<" (80.00 EUR/night)"<<endl;
        cout<<"double bed room(s): "<<doubles<<" (150.00 EUR/night)"<<endl;
        cout<<"board:              "<<board<<" ("<<::get_price(board)<<" EUR/day and person)"<<endl;
        if(parking){
            cout<<"parking:            included (10.00 EUR/day)"<<endl;
        }else{
            cout<<"parking:            not included (0.00 EUR/day)"<<endl;
        }
        cout<<"price accomodation:  "<<get_price()<<endl;
    }

};

class Transport{
public:
    virtual ~Transport(){
        cout<<""<<endl;
    }
    virtual bool includedTransfer(){
        return false;
    }
    virtual double get_price() = 0;
    virtual void print()=0;
};
class SelfTravel:public Transport{
public:
    SelfTravel(){};
    virtual ~SelfTravel(){
        cout<<"destructor Transport done"<<endl;
    }
    virtual double get_price(){
        return 0.00;
    }
    virtual void print(){
        cout<<"self travel no transfer"<<endl;
    }
};

class PublicTransport:public Transport{
protected:
    Date departure;
    string code;
    string from;
    string to;
    double priceOneSeat;
    bool firstClass;
public:
    PublicTransport(Date departure, string code, string from, string to, double priceOneSeat, bool firstClass = false):departure(departure), code(code), from(from), to(to), priceOneSeat(priceOneSeat), firstClass(firstClass){};
    virtual ~PublicTransport(){
        cout<<"destructor PublicTransport "<<code<<" at "<<departure<<" from "<<from<<" to "<<to<<" done"<<endl;
    }
    virtual void print(){
        if(firstClass){
            cout<<departure<<" "<<code<<" from "<<from<<" to "<<to<<" first class (";
        }else{
            cout<<departure<<" "<<code<<" from "<<from<<" to "<<to<<" (";
        }
    }
};

class Flight:public PublicTransport{
protected:
    bool transfer;
public:
    Flight(Date departure, string code, string from, string to, double priceOneSeat, bool firstClass = false, bool transfer = true):PublicTransport(departure, code, from, to, priceOneSeat, firstClass), transfer(transfer){};
    ~Flight(){
        cout<<"destructor Flight done"<<endl;
    }
    virtual bool includedTransfer(){
        return transfer;
    }
    virtual double get_price(){
        if(firstClass){
            return 2*priceOneSeat;
        }else{
            return priceOneSeat;
        }
    }
    virtual void print(){
        cout<<"flight ";
        PublicTransport::print();
        if(transfer){
            cout<<get_price()<<" EUR/person) transfer included"<<endl;
        }else{
            cout<<get_price()<<" EUR/person)"<<endl;
        }
    }
};

class Train:public PublicTransport{
    public:
    Train(Date departure, string code, string from, string to, double priceOneSeat, bool firstClass = false):PublicTransport(departure, code, from, to, priceOneSeat, firstClass){};
    virtual ~Train(){
        cout<<"destructor Train done"<<endl;
    }
    virtual double get_price(){
        if(firstClass){
            return 1.5*priceOneSeat;
        }else{
            return priceOneSeat;
        }
    }
    virtual void print(){
        cout<<"train ";
        PublicTransport::print();
        cout<<get_price()<<" EUR/person)"<<endl;
    }
};
class Request {
private:
    const unsigned int no;
    static unsigned int lastNo;
    Accomodation* accomodation;
    Request* next;
    Transport* transportOutward;
    Transport* transportReturn;

public:
    Request(Accomodation* accomodation = nullptr, Request* next = nullptr, Transport* transportOutward = nullptr, Transport* transportReturn = nullptr) : no(++lastNo), accomodation(accomodation), next(next), transportOutward(transportOutward), transportReturn(transportReturn) {};
    ~Request() {
        delete accomodation;
        delete transportOutward;
        delete transportReturn;
    }
    void setTransportOutward(Transport *transportOutward){
        this->transportOutward = transportOutward;
    }
    void setTransportReturn(Transport *transportReturn){
        this->transportReturn = transportReturn;
    }

    unsigned int get_no() {
         return no;
    }
    Request* get_next() {
        return next;
    }
    void set_next(Request* next) {
        this->next = next;
    }
    double get_price() {
        return accomodation->get_price()+ (transportOutward->get_price()* accomodation->get_guests()) + (transportReturn->get_price()*accomodation->get_guests());
    }
    void print(){
        cout<<"********REQUEST NO:   "<<get_no()<<"********"<<endl;
        accomodation->print();
        cout<<"outward journey:    ";
        transportOutward->print();
        cout<<"journey back:       ";
        transportReturn->print();
        cout<<"price total:        "<<get_price()<<" EUR"<<endl;
    }
};
unsigned int Request::lastNo = 0;

class CallCenter {
private:
    Request* requests;

public:
    CallCenter() : requests(nullptr) {}

    void append(Request* request) {
        if (!requests) {
            requests = request;
            return;
        }

        Request* current = requests;
        while (current->get_next()) {
            current = current->get_next();
        }
        current->set_next(request);
    }

    void cancel(Request* request) {
        if (!requests) {
            return;
        }

        Request* current = requests;
        Request* prev = nullptr;
        while (current) {
            if (current == request) {
                if (prev) {
                    prev->set_next(current->get_next());
                } else {
                    requests = current->get_next();
                }
                delete current;
                break;
            }
            prev = current;
            current = current->get_next();
        }
    }

    Request* get_request(unsigned int no) {
        Request* current = requests;
        while (current) {
            if (current->get_no() == no) {
                return current;
            }
            current = current->get_next();
        }
        return nullptr;
    }

    void print_all() {
        Request* current = requests;
        while (current) {
            current->print();
            current = current->get_next();
        }
    };
};



int main()
{
    CallCenter callCenter;
    Accomodation *standardAccom;
    Accomodation *superiorAccom;
    Transport *transport1;
    Transport *transport2;
    int choice, choice1, choice2;
    int reqNumber;
    char input;
    string outwardCode, outwardFrom, outwardTo, returnCode, returnFrom, returnTo;
    double outwardPrice, returnPrice;
    char input1;
    while(true){
        cout<<"CALL CENTER BOOKING REQUEST"<<endl<<"0 end"<<endl<<"1 new reservation request standard"<<endl<<"2 new reservation request superior"<<endl<<"3 show reservation request"<<endl<<"4 show all reservation requests"<<endl;
        cin>>choice;
        cout<<"your choice: "<<choice<<endl;
        switch(choice){
        case(1):{
            Request* req1 = new Request(standardAccom = new Accomodation(80.00, 150.00, 10.00));
            cout<<"please choose transport outward"<<endl<<"0 self travel"<<endl<<"1 by flight"<<endl<<"2 by train"<<endl;
            cin>>choice2;
            cout<<"your choice: "<<choice2<<endl;
            switch(choice2){
            case(1):{
                cout<<"code of flight: ";
                cin>>outwardCode;
                cout<<"airport of departure: ";
                cin>>outwardFrom;
                cout<<"airport of arrival: ";
                cin>>outwardTo;
                cout<<"standard price for one passenger: ";
                cin>>outwardPrice;
                cout<<"first class ((y)es or (n)o): ";
                cin>>input1;
                if(input1 == 'y'){
                    transport1 = new Flight(standardAccom->get_arrival(), outwardCode, outwardFrom, outwardTo, outwardPrice, true);
                }else{
                transport1 = new Flight(standardAccom->get_arrival(), outwardCode, outwardFrom, outwardTo, outwardPrice);
                }
                break;
            }
            case(2):{
                cout<<"code of train: ";
                cin>>outwardCode;
                cout<<"main train station of departure: ";
                cin>>outwardFrom;
                cout<<"main train station ";
                cin>>outwardTo;
                cout<<"standard price for one passenger: ";
                cin>>outwardPrice;
                cout<<"first class ((y)es or (n)o): ";
                cin>>input1;
                if(input1 == 'y'){
                    transport1 = new Train(standardAccom->get_arrival(), outwardCode, outwardFrom, outwardTo, outwardPrice, true);

                }else{
                    transport1 = new Train(standardAccom->get_arrival(), outwardCode, outwardFrom, outwardTo, outwardPrice);
                }
                break;
            }
            case(0):{
                transport1 = new SelfTravel();
                break;
            }
            }
            cout<<"please choose transport return"<<endl<<"0 self travel"<<endl<<"1 by flight"<<endl<<"2 by train"<<endl;
            cin>>choice1;
            cout<<"your choice: "<<choice1<<endl;
            switch(choice1){
                case(1):{
                    cout<<"code of flight: ";
                    cin>>returnCode;
                    cout<<"airport of departure: ";
                    cin>>returnFrom;
                    cout<<"airport of arrival: ";
                    cin>>returnTo;
                    cout<<"standard price for one passenger: ";
                    cin>>returnPrice;
                    cout<<"first class ((y)es or (n)o): ";
                    cin>>input1;
                    if(input1 == 'y'){
                        transport2 = new Flight(standardAccom->get_checkout(), returnCode, returnFrom, returnTo, returnPrice, true);
                    }else{
                        transport2 = new Flight(standardAccom->get_checkout(), returnCode, returnFrom, returnTo, returnPrice, true);
                    }
                    break;
                }
                case(2):{
                    cout<<"code of train: ";
                    cin>>returnCode;
                    cout<<"main train station of departure: ";
                    cin>>returnFrom;
                    cout<<"main train station of arrival: ";
                    cin>>returnTo;
                    cout<<"standard price for one passenger: ";
                    cin>>returnPrice;
                    cout<<"first class ((y)es or (n)o): ";
                    cin>>input1;
                    if(input1 == 'y'){
                        transport2 = new Train(standardAccom->get_checkout(), returnCode, returnFrom, returnTo, returnPrice, true);
                    }else{
                        transport2 = new Train(standardAccom->get_checkout(), returnCode, returnFrom, returnTo, returnPrice);
                    }
                    break;
                }
               case(0):{
                transport2 = new SelfTravel();
                break;
               }
               }
            req1->setTransportOutward(transport1);
            req1->setTransportReturn(transport2);
            callCenter.append(req1);
            break;
        }
        case(2):{
            Request* req2 = new Request(superiorAccom = new Accomodation(110.00, 210.00, 10.00));
            cout<<"please choose transport outward"<<endl<<"0 self travel"<<endl<<"1 by flight"<<endl<<"2 by train"<<endl;
            cin>>choice2;
            cout<<"your choice: "<<choice2<<endl;
            switch(choice2){
            case(1):{
                cout<<"code of flight: ";
                cin>>outwardCode;
                cout<<"airport of departure: ";
                cin>>outwardFrom;
                cout<<"airport of arrival: ";
                cin>>outwardTo;
                cout<<"standard price for one passenger: ";
                cin>>outwardPrice;
                cout<<"first class ((y)es or (n)o): ";
                cin>>input1;
                if(input1 == 'y'){
                    transport1 = new Flight(superiorAccom->get_arrival(), outwardCode, outwardFrom, outwardTo, outwardPrice, true);
                }else{
                transport1 = new Flight(superiorAccom->get_arrival(), outwardCode, outwardFrom, outwardTo, outwardPrice);
                }
                break;
            }
            case(2):{
                cout<<"code of train: ";
                cin>>outwardCode;
                cout<<"main train station of departure: ";
                cin>>outwardFrom;
                cout<<"main train station of arrival";
                cin>>outwardTo;
                cout<<"standard price for one passenger: ";
                cin>>outwardPrice;
                cout<<"first class ((y)es or (n)o): ";
                cin>>input1;
                if(input1 == 'y'){
                    transport1 = new Train(superiorAccom->get_arrival(), outwardCode, outwardFrom, outwardTo, outwardPrice, true);

                }else{
                    transport1 = new Train(superiorAccom->get_arrival(), outwardCode, outwardFrom, outwardTo, outwardPrice);
                }
                break;
            }
            case(0):{
                transport1 = new SelfTravel();
                break;
            }

            }
            cout<<"please choose transport return"<<endl<<"0 self travel"<<endl<<"1 by flight"<<endl<<"2 by train"<<endl;
            cin>>choice1;
            cout<<"your choice: "<<choice1<<endl;
            switch(choice1){
                case(1):{
                    cout<<"code of flight: ";
                    cin>>returnCode;
                    cout<<"airport of departure: ";
                    cin>>returnFrom;
                    cout<<"airport of arrival: ";
                    cin>>returnTo;
                    cout<<"standard price for one passenger: ";
                    cin>>returnPrice;
                    cout<<"first class ((y)es or (n)o): ";
                    cin>>input1;
                    if(input1 == 'y'){
                        transport2 = new Flight(superiorAccom->get_checkout(), returnCode, returnFrom, returnTo, returnPrice, true);
                    }else{
                        transport2 = new Flight(superiorAccom->get_checkout(), returnCode, returnFrom, returnTo, returnPrice, true);
                    }
                    break;
                }
                case(2):{
                    cout<<"code of train: ";
                    cin>>returnCode;
                    cout<<"main train station of departure: ";
                    cin>>returnFrom;
                    cout<<"main train station of arrival: ";
                    cin>>returnTo;
                    cout<<"standard price for one passenger: ";
                    cin>>returnPrice;
                    cout<<"first class ((y)es or (n)o): ";
                    cin>>input1;
                    if(input1 == 'y'){
                        transport2 = new Train(superiorAccom->get_checkout(), returnCode, returnFrom, returnTo, returnPrice, true);
                    }else{
                        transport2 = new Train(superiorAccom->get_checkout(), returnCode, returnFrom, returnTo, returnPrice);
                    }
                    break;
                }
                case(0):{
                    transport2 = new SelfTravel();
                    break;
            }

            }
            req2->setTransportOutward(transport1);
            req2->setTransportReturn(transport2);
            callCenter.append(req2);
            break;
        }
        case(4):{
            callCenter.print_all();
            break;
        }
        case(3):{
            cout<<"number of reservation request: ";
            cin>>reqNumber;
            callCenter.get_request(reqNumber)->print();
            cout<<"(c)ancel this request or (n)ot:";
            cin>>input;
            if(input == 'c'){
                callCenter.cancel(callCenter.get_request(reqNumber));
                cout<<"destructor Request "<<reqNumber<<" done"<<endl;
            }
            break;
        }
        case(0):{
            return 0;
        }
        default:{
            continue;
        }
        }
    }
    return 0;
}
