// 전략패턴(Strategy Pattern)
// 알고리즘군을 정의하고 캡슐화해서 각각의 알고리즘군을 수정해서 쓸 수 있게 해 줍니다. 
// 클라이언트로부터 알고리즘을 분리해서 독립적으로 변경할 수 있습니다.


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