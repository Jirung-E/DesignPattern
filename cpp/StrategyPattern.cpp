// ��������(Strategy Pattern)
// �˰����� �����ϰ� ĸ��ȭ�ؼ� ������ �˰����� �����ؼ� �� �� �ְ� �� �ݴϴ�. 
// Ŭ���̾�Ʈ�κ��� �˰����� �и��ؼ� ���������� ������ �� �ֽ��ϴ�.


#include <iostream>

using namespace std;


// --------------------------------------
class FlyBehavior {
public:
    virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior {
public:
    void fly() {
        cout << "Flying!" << endl;
    }
};

class FlyNoWay : public FlyBehavior {
public:
    void fly() {
        cout << "I can't fly" << endl;
    }
};
// --------------------------------------

class Duck {
protected:
    FlyBehavior* fly_behavior;

public:
    Duck() : fly_behavior { nullptr } {

    }

public:
    virtual void display() = 0;
    void fly() {
        fly_behavior->fly();
    }

    void setFlyBehavior(FlyBehavior* fly_behavior) {
        this->fly_behavior = fly_behavior;
    }
};

class DummyDuck : public Duck {
public:
    DummyDuck() { 
        fly_behavior = new FlyNoWay;
    }

public:
    void display() {
        cout << "<><>" << endl;
    }
};

class MallardDuck : public Duck {
public:
    MallardDuck() {
        fly_behavior = new FlyWithWings;
    }

public:
    void display() {
        cout << "[][]" << endl;
    }
};


int main() {
    Duck* duck = new DummyDuck;
    duck->display();
    duck->fly();
    duck->setFlyBehavior(new FlyWithWings);
    duck->display();
    duck->fly();
}