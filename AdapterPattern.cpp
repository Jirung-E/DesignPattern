// ����� ����(Adapter Pattern)
// Ư�� Ŭ���� �������̽��� Ŭ���̾�Ʈ���� �䱸�ϴ� �ٸ� �������̽��� ��ȯ�մϴ�.
// �������̽��� ȣȯ���� �ʾ� ���� �� �� ������ Ŭ������ ����� �� �ְ� �����ݴϴ�. 
// ��ü ����Ϳ� Ŭ���� ����Ͱ� �ִ�. 
// Ŭ���� ����ʹ� ���� ����� �ؾ��ϹǷ� �� ���� ����� �Ұ����Ҽ��� �ִ�.
// �Ʒ��� ��ü������� ����

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
        cout << "��" << endl;
    }

    void fly() {
        cout << "�����־��!" << endl;
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
        cout << "���" << endl;
    }

    void fly() {
        cout << "ª�� �Ÿ��� ���� �־��!" << endl;
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