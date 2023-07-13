// ���� ����(State Pattern)
// ��ü�� ���� ���°� �ٲ� ���� ��ü�� �ൿ�� �ٲ� �� �ֽ��ϴ�.
// ��ġ ��ü�� Ŭ������ �ٲ�� �Ͱ� ���� ����� ���� �� �ֽ��ϴ�.

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

        cout << "���� ����: " << count << "��" << endl;
        cout << (*current_state)->getByString() << endl;

        cout << endl;
    }

    void releaseBall() {
        cout << "�˸��̸� �������� �ֽ��ϴ�." << endl;
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
        cout << "�����Ǿ����ϴ�." << endl;
    }

    void ejectQuarter() override {
        cout << "������ ���� �ʾҽ��ϴ�." << endl;
    }

    void turnCrank() override {
        cout << "�����Ǿ����ϴ�." << endl;
    }

    void dispense() override {
        cout << "�����Ǿ����ϴ�." << endl;
    }

    void refill() override {
        cout << "�˸��̸� �����մϴ�." << endl;
        gumball_machine->setCurrentState(gumball_machine->getNoQuarterState());
    }

    string getByString() override {
        return "����";
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
        cout << "�˸��̸� �������� �ֽ��ϴ�." << endl;
    }

    void ejectQuarter() override {
        cout << "�̹� �˸��̸� �����̽��ϴ�." << endl;
    }

    void turnCrank() override {
        cout << "�����̴� �ѹ��� �����ּ���." << endl;
    }

    void dispense() override {
        gumball_machine->releaseBall();
        if(gumball_machine->getCount() > 0) {
            gumball_machine->setCurrentState(gumball_machine->getNoQuarterState());
        }
        else {
            cout << "�˸��̰� �����ϴ�." << endl;
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
        cout << "������ �����̽��ϴ�." << endl;
        gumball_machine->setCurrentState(gumball_machine->getHasQuarterState());
    }

    void ejectQuarter() override {
        cout << "������ �־��ּ���" << endl;
    }

    void turnCrank() override {
        cout << "������ �־��ּ���" << endl;
    }

    void dispense() override {
        cout << "������ �־��ּ���" << endl;
    }

    string getByString() override {
        return "���� ���� �����";
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
        cout << "������ �Ѱ��� �־� �ּ���." << endl;
    }

    void ejectQuarter() override {
        cout << "������ ��ȯ�˴ϴ�." << endl;
        gumball_machine->setCurrentState(gumball_machine->getNoQuarterState());
    }

    void turnCrank() override {
        cout << "�����̸� �����̽��ϴ�." << endl;
        if(uid(rd) == 0 && gumball_machine->getCount() > 1) {
            gumball_machine->setCurrentState(gumball_machine->getWinnerState());
        }
        else {
            gumball_machine->setCurrentState(gumball_machine->getSoldState());
        }
    }

    void dispense() override {
        cout << "�˸��̸� ������ �� �����ϴ�." << endl;
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
        cout << "�˸��̸� �������� �ֽ��ϴ�." << endl;
    }

    void ejectQuarter() override {
        cout << "�̹� �˸��̸� �����̽��ϴ�." << endl;
    }

    void turnCrank() override {
        cout << "�����̴� �ѹ��� �����ּ���." << endl;
    }

    void dispense() override {
        gumball_machine->releaseBall();
        if(gumball_machine->getCount() == 0) {
            gumball_machine->setCurrentState(gumball_machine->getSoldOutState());
        }
        else {
            gumball_machine->releaseBall();
            cout << "���ϵ帳�ϴ�! �˸��̸� �ϳ� �� ������ �� �ֽ��ϴ�." << endl;
            if(gumball_machine->getCount() > 0) {
                gumball_machine->setCurrentState(gumball_machine->getNoQuarterState());
            }
            else {
                cout << "�� �̻� �˸��̰� �����ϴ�." << endl;
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
    void insertQuarter() {                      // State���� �� �޼������ ȣ���ϸ� �ȵǹǷ� �������̽��� �ø��� ����
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