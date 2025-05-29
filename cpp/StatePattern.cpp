// 상태 패턴(State Pattern)
// 객체의 내부 상태가 바뀜에 따라서 객체의 행동을 바꿀 수 있습니다.
// 마치 객체의 클래스가 바뀌는 것과 같은 결과를 얻을 수 있습니다.

#include <iostream>
#include <random>

using namespace std;


class State {
public:
    virtual void insertQuarter() = 0;
    virtual void ejectQuarter() = 0;
    virtual void turnCrank() = 0;
    virtual void dispense() = 0;
    virtual string getByString() = 0;
    virtual void refill() {

    }
};


class GumballMachineInterface {
protected:
    int count;
    State** current_state;
    State* sold;
    State* sold_out;
    State* no_quarter;
    State* has_quarter;
    State* winner;

protected:
    GumballMachineInterface(int count) : current_state { &sold_out }, count { count } {
        if(count > 0) {
            setCurrentState(no_quarter);
        }
    }

public:
    void setCurrentState(State*& state) {
        current_state = &state;
    }

    State*& getHasQuarterState() {
        return has_quarter;
    }

    State*& getNoQuarterState() {
        return no_quarter;
    }

    State*& getSoldState() {
        return sold;
    }

    State*& getSoldOutState() {
        return sold_out;
    }

    State*& getWinnerState() {
        return winner;
    }

    void printCurrentState() const {
        cout << endl;

        cout << "남은 개수: " << count << "개" << endl;
        cout << (*current_state)->getByString() << endl;

        cout << endl;
    }

    void releaseBall() {
        cout << "알맹이를 내보내고 있습니다." << endl;
        if(count > 0) {
            count--;
        }
    }

    int getCount() const {
        return count;
    }
};


class SoldOutState : public State {
private:
    GumballMachineInterface* gumball_machine;

public:
    SoldOutState(GumballMachineInterface* gumball_machine) : gumball_machine { gumball_machine } {

    }

public:
    void insertQuarter() override {
        cout << "매진되었습니다." << endl;
    }

    void ejectQuarter() override {
        cout << "동전을 넣지 않았습니다." << endl;
    }

    void turnCrank() override {
        cout << "매진되었습니다." << endl;
    }

    void dispense() override {
        cout << "매진되었습니다." << endl;
    }

    void refill() override {
        cout << "알맹이를 리필합니다." << endl;
        gumball_machine->setCurrentState(gumball_machine->getNoQuarterState());
    }

    string getByString() override {
        return "매진";
    }
};

class SoldState : public State {
private:
    GumballMachineInterface* gumball_machine;

public:
    SoldState(GumballMachineInterface* gumball_machine) : gumball_machine { gumball_machine } {

    }

public:
    void insertQuarter() override {
        cout << "알맹이를 내보내고 있습니다." << endl;
    }

    void ejectQuarter() override {
        cout << "이미 알맹이를 뽑으셨습니다." << endl;
    }

    void turnCrank() override {
        cout << "손잡이는 한번만 돌려주세요." << endl;
    }

    void dispense() override {
        gumball_machine->releaseBall();
        if(gumball_machine->getCount() > 0) {
            gumball_machine->setCurrentState(gumball_machine->getNoQuarterState());
        }
        else {
            cout << "알맹이가 없습니다." << endl;
            gumball_machine->setCurrentState(gumball_machine->getSoldOutState());
        }
    }

    string getByString() override {
        return "";
    }
};

class NoQuarterState : public State {
private:
    GumballMachineInterface* gumball_machine;

public:
    NoQuarterState(GumballMachineInterface* gumball_machine) : gumball_machine { gumball_machine } {

    }

public:
    void insertQuarter() override {
        cout << "동전을 넣으셨습니다." << endl;
        gumball_machine->setCurrentState(gumball_machine->getHasQuarterState());
    }

    void ejectQuarter() override {
        cout << "동전을 넣어주세요" << endl;
    }

    void turnCrank() override {
        cout << "동전을 넣어주세요" << endl;
    }

    void dispense() override {
        cout << "동전을 넣어주세요" << endl;
    }

    string getByString() override {
        return "동전 투입 대기중";
    }
};

class HasQuarterState : public State {
private:
    GumballMachineInterface* gumball_machine;
    uniform_int_distribution<> uid { 0, 9 };
    random_device rd;

public:
    HasQuarterState(GumballMachineInterface* gumball_machine) : gumball_machine { gumball_machine } {

    }

public:
    void insertQuarter() override {
        cout << "동전은 한개만 넣어 주세요." << endl;
    }

    void ejectQuarter() override {
        cout << "동전이 반환됩니다." << endl;
        gumball_machine->setCurrentState(gumball_machine->getNoQuarterState());
    }

    void turnCrank() override {
        cout << "손잡이를 돌리셨습니다." << endl;
        if(uid(rd) == 0 && gumball_machine->getCount() > 1) {
            gumball_machine->setCurrentState(gumball_machine->getWinnerState());
        }
        else {
            gumball_machine->setCurrentState(gumball_machine->getSoldState());
        }
    }

    void dispense() override {
        cout << "알맹이를 내보낼 수 없습니다." << endl;
    }

    string getByString() override {
        return "";
    }
};

class WinnerState : public State {
private:
    GumballMachineInterface* gumball_machine;

public:
    WinnerState(GumballMachineInterface* gumball_machine) : gumball_machine { gumball_machine } {

    }

public:
    void insertQuarter() override {
        cout << "알맹이를 내보내고 있습니다." << endl;
    }

    void ejectQuarter() override {
        cout << "이미 알맹이를 뽑으셨습니다." << endl;
    }

    void turnCrank() override {
        cout << "손잡이는 한번만 돌려주세요." << endl;
    }

    void dispense() override {
        gumball_machine->releaseBall();
        if(gumball_machine->getCount() == 0) {
            gumball_machine->setCurrentState(gumball_machine->getSoldOutState());
        }
        else {
            gumball_machine->releaseBall();
            cout << "축하드립니다! 알맹이를 하나 더 받으실 수 있습니다." << endl;
            if(gumball_machine->getCount() > 0) {
                gumball_machine->setCurrentState(gumball_machine->getNoQuarterState());
            }
            else {
                cout << "더 이상 알맹이가 없습니다." << endl;
            gumball_machine->setCurrentState(gumball_machine->getSoldOutState());
            }
        }
    }

    string getByString() override {
        return "";
    }
};


class GumballMachine : public GumballMachineInterface {
public:
    GumballMachine(int count) : GumballMachineInterface { count } {
        sold = new SoldState { this };
        sold_out = new SoldOutState { this };
        no_quarter = new NoQuarterState { this };
        has_quarter = new HasQuarterState { this };
        winner = new WinnerState { this };
    }

public:
    void insertQuarter() {                      // State에서 이 메서드들을 호출하면 안되므로 인터페이스로 올리지 않음
        (*current_state)->insertQuarter();
    }

    void ejectQuarter() {
        (*current_state)->ejectQuarter();
    }

    void turnCrank() {
        (*current_state)->turnCrank();
        (*current_state)->dispense();
    }

    void refill(int count) {
        if(this->count == 0) {
            this->count += count;
            (*current_state)->refill();
        }
    }
};


int main() {
    GumballMachine gumball_machine { 5 };

    gumball_machine.printCurrentState();

    gumball_machine.insertQuarter();
    gumball_machine.turnCrank();

    gumball_machine.printCurrentState();

    gumball_machine.insertQuarter();
    gumball_machine.turnCrank();
    gumball_machine.insertQuarter();
    gumball_machine.turnCrank();
    gumball_machine.insertQuarter();
    gumball_machine.turnCrank();
    gumball_machine.insertQuarter();
    gumball_machine.turnCrank();
    gumball_machine.insertQuarter();
    gumball_machine.turnCrank();
    gumball_machine.insertQuarter();
    gumball_machine.turnCrank();
    gumball_machine.insertQuarter();
    gumball_machine.turnCrank();
    gumball_machine.insertQuarter();
    gumball_machine.turnCrank();
    gumball_machine.insertQuarter();
    gumball_machine.turnCrank();
    gumball_machine.insertQuarter();
    gumball_machine.turnCrank();
    gumball_machine.insertQuarter();
    gumball_machine.turnCrank();

    gumball_machine.printCurrentState();

    gumball_machine.refill(10);
    gumball_machine.insertQuarter();
    gumball_machine.turnCrank();
    
    gumball_machine.printCurrentState();
}