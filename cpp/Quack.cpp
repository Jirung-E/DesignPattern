#include <iostream>
#include <list>

using namespace std;


class Quackable {
public:
    virtual void quack() = 0;
};


class MallardDuck : public Quackable {
public:
    void quack() override {
        cout << "²Ð²Ð" << endl;
    }
};

class RedheadDuck : public Quackable {
public:
    void quack() override {
        cout << "²Ð²Ð" << endl;
    }
};


class DuckCall : public Quackable {
public:
    void quack() override {
        cout << "²Ë²Ë" << endl;
    }
};

class RubberDuck : public Quackable {
public:
    void quack() override {
        cout << "»à»à" << endl;
    }
};


class Goose {
public:
    void honk() {
        cout << "³£³£" << endl;
    }
};

class GooseAdapter : public Quackable {
private:
    Goose* goose;

public:
    GooseAdapter(Goose* goose) : goose { goose } {

    }

public:
    void quack() {
        goose->honk();
    }
};


class AbstractDuckFactory {
public:
    virtual Quackable* createMallardDuck() = 0;
    virtual Quackable* createRedheadDuck() = 0;
    virtual Quackable* createDuckCall() = 0;
    virtual Quackable* createRubberDuck() = 0;
};


class DuckFactory : public AbstractDuckFactory {
public:
    Quackable* createMallardDuck() override {
        return new MallardDuck;
    }

    Quackable* createRedheadDuck() override {
        return new RedheadDuck;
    }

    Quackable* createDuckCall() override {
        return new DuckCall;
    }

    Quackable* createRubberDuck() override {
        return new RubberDuck;
    }
};


class QuackCounter : public  Quackable {
private:
    Quackable* duck;
    static int number_of_quacks;

public:
    QuackCounter(Quackable* duck) : duck { duck } {

    }

public:
    void quack() {
        duck->quack();
        number_of_quacks++;
    }

    static int getQuacks() {
        return number_of_quacks;
    }
};
int QuackCounter::number_of_quacks = 0;


class CountingDuckFactory : public AbstractDuckFactory {
public:
    Quackable* createMallardDuck() override {
        return new QuackCounter { new MallardDuck };
    }

    Quackable* createRedheadDuck() override {
        return new QuackCounter { new RedheadDuck };
    }

    Quackable* createDuckCall() override {
        return new QuackCounter { new DuckCall };
    }

    Quackable* createRubberDuck() override {
        return new QuackCounter { new RubberDuck };
    }
};


class Flock : public Quackable {
private:
    list<Quackable*> quackers;

public:
    void add(Quackable* quacker) {
        quackers.push_back(quacker);
    }

    void quack() {
        for(auto& e : quackers) {
            e->quack();
        }
    }
};


void simulate(Quackable* duck) {
    duck->quack();
}

void simulate(AbstractDuckFactory* duck_factory) {
    Quackable* redhead_duck = duck_factory->createRedheadDuck();
    Quackable* duck_call = duck_factory->createDuckCall();
    Quackable* rubber_duck = duck_factory->createRubberDuck();
    Quackable* goose_duck = new GooseAdapter { new Goose };

    cout << "¿À¸® ½Ã¹Ä·¹ÀÌ¼Ç °ÔÀÓ" << endl;

    Flock* flock_of_ducks = new Flock;

    flock_of_ducks->add(redhead_duck);
    flock_of_ducks->add(duck_call);
    flock_of_ducks->add(rubber_duck);
    flock_of_ducks->add(goose_duck);

    Quackable* mallard_duck1 = duck_factory->createMallardDuck();
    Quackable* mallard_duck2 = duck_factory->createMallardDuck();
    Quackable* mallard_duck3 = duck_factory->createMallardDuck();
    Quackable* mallard_duck4 = duck_factory->createMallardDuck();

    Flock* flock_of_mallards = new Flock;

    flock_of_mallards->add(mallard_duck1);
    flock_of_mallards->add(mallard_duck2);
    flock_of_mallards->add(mallard_duck3);
    flock_of_mallards->add(mallard_duck4);

    simulate(flock_of_ducks);
    simulate(flock_of_mallards);

    cout << "Quacks: " << QuackCounter::getQuacks() << endl;
}

int main() {
    AbstractDuckFactory* duck_factory = new CountingDuckFactory;
    simulate(duck_factory);
}