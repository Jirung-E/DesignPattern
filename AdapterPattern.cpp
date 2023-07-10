// 어댑터 패턴(Adapter Pattern)
// 특정 클래스 인터페이스를 클라이언트에서 요구하는 다른 인터페이스로 변환합니다.
// 인터페이스가 호환되지 않아 같이 쓸 수 없었던 클래스를 사용할 수 있게 도와줍니다. 
// 객체 어댑터와 클래스 어댑터가 있다. 
// 클래스 어댑터는 다중 상속을 해야하므로 언어에 따라서 사용이 불가능할수도 있다.
// 아래는 객체어댑터의 예시

#include <iostream>

using namespace std;

class Duck {
public:
    virtual void quack() = 0;
    virtual void fly() = 0;
};

class MallardDuck : public Duck {
public:
    void quack() {
        cout << "꽥" << endl;
    }

    void fly() {
        cout << "날고있어요!" << endl;
    }
};

class Turkey {
public:
    virtual void gobble() = 0;
    virtual void fly() = 0;
};

class WildTurkey : public Turkey {
public:
    void gobble() {
        cout << "골골" << endl;
    }

    void fly() {
        cout << "짧은 거리를 날고 있어요!" << endl;
    }
};


class TurkeyAdapter : public Duck {
private:
    Turkey* turkey;

public:
    TurkeyAdapter(Turkey* turkey) : turkey { turkey } {

    }

public:
    void quack() {
        turkey->gobble();
    }

    void fly() {
        for(int i=0; i<5; ++i) {
            turkey->fly();
        }
    }
};


void testDuck(Duck* duck) {
    duck->quack();
    duck->fly();
}

int main() {
    Duck* duck = new MallardDuck;
    Turkey* turkey = new WildTurkey;
    Duck* turkey_adapter = new TurkeyAdapter { turkey };

    turkey->gobble();
    turkey->fly();

    cout << endl;

    testDuck(duck);

    cout << endl;

    testDuck(turkey_adapter);
}