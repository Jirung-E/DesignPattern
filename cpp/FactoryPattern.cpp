// 팩토리 메소드 패턴(Factory Method Pattern)
// 객체를 생성할 때 필요한 인터페이스를 만듭니다.
// 어떤 클래스의 인스턴스를 만들지는 서브클래스에서 결정합니다. 
// 팩토리 메소드 패턴을 사용하면 클래스 인스턴스 만드는 일을 서브클래스에게 맡기게 됩니다.

// 추상 팩토리 패턴(Abstract Factory Pattern)
// 구상 클래스에 의존하지 않고도 서로 연관되거나 의존적인 객체로 이루어진 제품군을 생산하는 인터페이스를 제공합니다.
// 구상 클래스는 서브 클래스에서 만듭니다.

#include <iostream>
#include <list>

using namespace std;


class Dough {

};

class ThinCrustDough : public Dough {

};

class ThickCrustDough : public Dough {

};

class Sauce {

};

class TomatoSauce : public Sauce {

};

class MarinaraSauce : public Sauce {

};

class Cheese {

};

class MozzarellaCheese : public Cheese {

};

class ReggianoCheese : public Cheese {

};

class Veggies {

};

class Garlic : public Veggies {

};

class Onion : public Veggies {

};

class Mushroom : public Veggies {

};

class RedPepper : public Veggies {

};

class BlackOlives : public Veggies {

};

class Spinach : public Veggies {

};

class EggPlant : public Veggies {

};

class Pepperoni {

};

class SlicedPepperoni : public Pepperoni {

};


class PizzaIngredientFactory {
public:
    virtual Dough* createDough() = 0;
    virtual Sauce* createSauce() = 0;
    virtual Cheese* createCheese() = 0;
    virtual list<Veggies*> createVeggies() = 0;
    virtual Pepperoni* createPepperoni() = 0;
};


class NYPizzaIngredientFactory : public PizzaIngredientFactory {
public:
    Dough* createDough() {
        return new ThinCrustDough;
    }

    Sauce* createSauce() {
        return new MarinaraSauce;
    }

    Cheese* createCheese() {
        return new ReggianoCheese;
    }

    list<Veggies*> createVeggies() {
        return { new Garlic, new Onion, new Mushroom, new RedPepper };
    }

    Pepperoni* createPepperoni() {
        return new SlicedPepperoni;
    }
};

class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory {
public:
    Dough* createDough() {
        return new ThickCrustDough;
    }

    Sauce* createSauce() {
        return new TomatoSauce;
    }

    Cheese* createCheese() {
        return new MozzarellaCheese;
    }

    list<Veggies*> createVeggies() {
        return { new EggPlant, new BlackOlives, new Spinach };
    }

    Pepperoni* createPepperoni() {
        return new SlicedPepperoni;
    }
};


class Pizza {
protected:
    string name;

    Dough* dough;
    Sauce* sauce;
    list<Veggies*> veggies;
    Cheese* cheese;
    Pepperoni* pepperoni;

public:
    virtual void prepare() = 0;

    virtual void bake() {
        cout << "175도에서 25분간 굽기" << endl;
    }

    virtual void cut() {
        cout << "피자를 사선으로 자르기" << endl;
    }

    virtual void box() {
        cout << "상자에 피자 담기" << endl;
    }

    string getName() const {
        return name;
    }

    void setName(const string& name) {
        this->name = name;
    }

    string toString() {
        // 피자 이름을 출력하는 부분
    }
};


class CheesePizza : public Pizza {
    PizzaIngredientFactory* ingredient_factory;

public:
    CheesePizza(PizzaIngredientFactory* ingredient_factory) : ingredient_factory { ingredient_factory } {
        
    }
    
public:
    void prepare() {
        cout << "준비중: " << name << endl;
        dough = ingredient_factory->createDough();
        sauce = ingredient_factory->createSauce();
        cheese = ingredient_factory->createCheese();
    }
};

class PepperoniPizza : public Pizza {
    PizzaIngredientFactory* ingredient_factory;

public:
    PepperoniPizza(PizzaIngredientFactory* ingredient_factory) : ingredient_factory { ingredient_factory } {

    }

public:
    void prepare() {
        cout << "준비중: " << name << endl;
        dough = ingredient_factory->createDough();
        sauce = ingredient_factory->createSauce();
        cheese = ingredient_factory->createCheese();
        pepperoni = ingredient_factory->createPepperoni();
    }
};

class VeggiePizza : public Pizza {
    PizzaIngredientFactory* ingredient_factory;

public:
    VeggiePizza(PizzaIngredientFactory* ingredient_factory) : ingredient_factory { ingredient_factory } {

    }

public:
    void prepare() {
        cout << "준비중: " << name << endl;
        dough = ingredient_factory->createDough();
        sauce = ingredient_factory->createSauce();
        cheese = ingredient_factory->createCheese();
        veggies = ingredient_factory->createVeggies();
    }
};


class PizzaStore {
public:
    Pizza* orderPizza(const string& type) {
        Pizza* pizza = createPizza(type);

        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        return pizza;
    }

protected:
    virtual Pizza* createPizza(const string& type) = 0;
};

class NYStylePizzaStore : public PizzaStore {
protected:
    Pizza* createPizza(const string& type) {
        Pizza* pizza = nullptr;
        PizzaIngredientFactory* factory = new NYPizzaIngredientFactory;

        if(type == "cheese") {
            pizza = new CheesePizza { factory };
            pizza->setName("뉴욕 스타일 치즈 피자");
        }
        else if(type == "pepperoni") {
            pizza = new PepperoniPizza { factory };
            pizza->setName("뉴욕 스타일 페퍼로니 피자");
        }
        else if(type == "veggie") {
            pizza = new VeggiePizza { factory };
            pizza->setName("뉴욕 스타일 야채 피자");
        }
        return pizza;
    }
};

class ChicagoStylePizzaStore : public PizzaStore {
protected:
    Pizza* createPizza(const string& type) {
        Pizza* pizza = nullptr;
        PizzaIngredientFactory* factory = new ChicagoPizzaIngredientFactory;

        if(type == "cheese") {
            pizza = new CheesePizza { factory };
            pizza->setName("시카고 스타일 치즈 피자");
        }
        else if(type == "pepperoni") {
            pizza = new PepperoniPizza { factory };
            pizza->setName("시카고 스타일 페퍼로니 피자");
        }
        else if(type == "veggie") {
            pizza = new VeggiePizza { factory };
            pizza->setName("시카고 스타일 야채 피자");
        }
        return pizza;
    }
};


int main() {
    PizzaStore* ny_store = new NYStylePizzaStore;
    PizzaStore* chicago_store = new ChicagoStylePizzaStore;

    Pizza* pizza = ny_store->orderPizza("cheese");
    cout << pizza->getName() << endl << endl;
    pizza = chicago_store->orderPizza("cheese");
    cout << pizza->getName() << endl << endl;
}