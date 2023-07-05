// ���丮 �޼ҵ� ����(Factory Method Pattern)
// ��ü�� ������ �� �ʿ��� �������̽��� ����ϴ�.
// � Ŭ������ �ν��Ͻ��� �������� ����Ŭ�������� �����մϴ�. 
// ���丮 �޼ҵ� ������ ����ϸ� Ŭ���� �ν��Ͻ� ����� ���� ����Ŭ�������� �ñ�� �˴ϴ�.

// �߻� ���丮 ����(Abstract Factory Pattern)
// ���� Ŭ������ �������� �ʰ� ���� �����ǰų� �������� ��ü�� �̷���� ��ǰ���� �����ϴ� �������̽��� �����մϴ�.
// ���� Ŭ������ ���� Ŭ�������� ����ϴ�.

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
        cout << "175������ 25�а� ����" << endl;
    }

    virtual void cut() {
        cout << "���ڸ� �缱���� �ڸ���" << endl;
    }

    virtual void box() {
        cout << "���ڿ� ���� ���" << endl;
    }

    string getName() const {
        return name;
    }

    void setName(const string& name) {
        this->name = name;
    }

    string toString() {
        // ���� �̸��� ����ϴ� �κ�
    }
};


class CheesePizza : public Pizza {
    PizzaIngredientFactory* ingredient_factory;

public:
    CheesePizza(PizzaIngredientFactory* ingredient_factory) : ingredient_factory { ingredient_factory } {
        
    }
    
public:
    void prepare() {
        cout << "�غ���: " << name << endl;
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
        cout << "�غ���: " << name << endl;
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
        cout << "�غ���: " << name << endl;
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
            pizza->setName("���� ��Ÿ�� ġ�� ����");
        }
        else if(type == "pepperoni") {
            pizza = new PepperoniPizza { factory };
            pizza->setName("���� ��Ÿ�� ���۷δ� ����");
        }
        else if(type == "veggie") {
            pizza = new VeggiePizza { factory };
            pizza->setName("���� ��Ÿ�� ��ä ����");
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
            pizza->setName("��ī�� ��Ÿ�� ġ�� ����");
        }
        else if(type == "pepperoni") {
            pizza = new PepperoniPizza { factory };
            pizza->setName("��ī�� ��Ÿ�� ���۷δ� ����");
        }
        else if(type == "veggie") {
            pizza = new VeggiePizza { factory };
            pizza->setName("��ī�� ��Ÿ�� ��ä ����");
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