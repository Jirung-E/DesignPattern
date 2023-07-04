// ���ڷ����� ����(Decorator Pattern)
// ��ü�� �߰� ��Ҹ� �������� ���� �� �ֽ��ϴ�. 
// ���ڷ����͸� ����ϸ� ����Ŭ������ ���� ������ �ξ� �����ϰ� ����� Ȯ���� �� �ֽ��ϴ�.

#include <iostream>

using namespace std;


class Beverage {
protected:
    string description;

public:
    Beverage() : description { "���� ����" } {

    }

public:
    virtual string getDescription() {
        return description;
    }

    virtual double cost() = 0;
};

class Espresso : public Beverage {
public:
    Espresso() {
        description = "����������";
    }

public:
    double cost() {
        return 1.99;
    }
};

class HouseBlend : public Beverage {
public:
    HouseBlend() {
        description = "�Ͽ콺����Ŀ��";
    }

public:
    double cost() {
        return .89;
    }
};


class CondimentDecorator : public Beverage {
protected:
    Beverage* beverage;

public:
    CondimentDecorator(Beverage* beverage) : beverage { beverage } {
        
    }

public:
    virtual string getDescription() = 0;
};

class Mocha : public CondimentDecorator {
public:
    Mocha(Beverage* beverage) : CondimentDecorator { beverage } {
        
    }

public:
    string getDescription() {
        return beverage->getDescription() + ", ��ī";
    }

    double cost() {
        return beverage->cost() + .20;
    }
};

class Soy : public CondimentDecorator {
public:
    Soy(Beverage* beverage) : CondimentDecorator { beverage } {
        
    }

public:
    string getDescription() {
        return beverage->getDescription() + ", ����";
    }

    double cost() {
        return beverage->cost() + .15;
    }
};

class Whip : public CondimentDecorator {
public:
    Whip(Beverage* beverage) : CondimentDecorator { beverage } {
        
    }

public:
    string getDescription() {
        return beverage->getDescription() + ", ����ũ��";
    }

    double cost() {
        return beverage->cost() + .10;
    }
};


int main() {
    Beverage* beverage = new Espresso;
    cout << beverage->getDescription() << " $" << beverage->cost() << endl;

    beverage = new Mocha { beverage };
    beverage = new Whip { beverage };
    cout << beverage->getDescription() << " $" << beverage->cost() << endl;
}