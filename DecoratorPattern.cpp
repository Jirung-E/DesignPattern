// 데코레이터 패턴(Decorator Pattern)
// 객체에 추가 요소를 동적으로 더할 수 있습니다. 
// 데코레이터를 사용하면 서브클래스를 만들 때보다 훨씬 유연하게 기능을 확장할 수 있습니다.

#include <iostream>

using namespace std;


class Beverage {
protected:
    string description;

public:
    Beverage() : description { "제목 없음" } {

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
        description = "에스프레소";
    }

public:
    double cost() {
        return 1.99;
    }
};

class HouseBlend : public Beverage {
public:
    HouseBlend() {
        description = "하우스블렌드커피";
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
        return beverage->getDescription() + ", 모카";
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
        return beverage->getDescription() + ", 두유";
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
        return beverage->getDescription() + ", 휘핑크림";
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