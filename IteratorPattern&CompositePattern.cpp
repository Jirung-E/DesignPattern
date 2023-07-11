// 반복자 패턴(Iterator Pattern)
// 컬랙션의 구현 방법을 노출하지 않으면서 집합체 내의 모든 항목에 접근하는 방법을 제공합니다.

// 컴포지트 패턴(Composite Pattern)
// 객체를 트리구조로 구성해서 부분-전체 계층구조를 구현합니다.
// 컴포지트 패턴을 사용하면 클라이언트에서 개별 객체와 복합 객체를 똑같은 방법으로 다룰 수 있습니다.

// C++로 바꾸는게 좀 어려워서 스킵
// 1. 예제로 나온 자바의 Iterator와 C++의 iterator의 작동 방식이 다름. 
//    아니면 그냥 내가 C++의 iterator를 못찾고있는걸지도...
// 2. 클래스에 begin, end 함수 추가로 해보려고 했지만 클래스가 가지고있는 배열의 형태가 list인 경우는 
//    메모리상에서 연결되어있지 않기 때문에 에러가 발생한다. 
// 3. hasNext로 while문 돌리는거 하고싶지 않음


#include <iostream>
#include <list>

using namespace std;


template <typename T>
class Iterator {
protected:
    int position;

public:
    virtual bool hasNext() = 0;
    virtual T& next() = 0;
};


class MenuItem {
    string name;
    string description;
    bool vegetarian;
    double price;

public:
    MenuItem(const string& name, const string& description, bool vegetarian, double price) :
        name { name }, description { description }, vegetarian { vegetarian }, price { price } {

    }

public:
    string getName() const {
        return name;
    }

    string getDescription() const {
        return description;
    }

    bool isVegetarian() const {
        return vegetarian;
    }

    double getPrice() const {
        return price;
    }
};


class PancakeHouseMenu : public Iterator<MenuItem*> {
    list<MenuItem*> menu_items;
    
public:
    PancakeHouseMenu() {
        addItem("K&B 팬케이크 세트", "스크램블 에그와 토스트가 곁들여진 팬케이크", false, 2.99);
        addItem("레귤러 팬케이크 세트", "달걀 프라이와 소시지가 곁들여진 팬케이크", false, 2.99);
        addItem("블루베리 팬케이크", "신선한 블루베리와 블루베리 시럽으로 만든 팬케이크", true, 3.49);
        addItem("와플", "취향에 따라 블루베리나 딸기를 얹을 수 있는 와플", true, 3.59);
    }

public:
    void addItem(const string& name, const string& description, bool vegetarian, double price) {
        menu_items.push_back(new MenuItem { name, description, vegetarian, price });
    }

    bool hasNext() override {
        
    }
};


class DinerMenu {
    static const int MAX_ITEMS = 6;
    int number_of_items = 0;
    MenuItem** menu_items;

public:
    DinerMenu() : menu_items { new MenuItem*[MAX_ITEMS] } {
        addItem("채식주의자용 BLT", "통밀 위에 콩고기 베이컨, 상추, 토마토를 얹은 메뉴", true, 2.99);
        addItem("BLT", "통밀 위에 베이컨, 상추, 토마토를 얹은 메뉴", false, 2.99);
        addItem("오늘의 스프", "감자 샐러드를 곁들인 오늘의 스프", false, 3.29);
        addItem("핫도그", "사워크라우트, 갖은 양념, 양파, 치즈가 곁들여진 핫도그", false, 3.05);
    }

public:
    void addItem(const string& name, const string& description, bool vegetarian, double price) {
        MenuItem item { name, description, vegetarian, price };
        if(number_of_items >= MAX_ITEMS) {
            cout << "죄송합니다. 메뉴가 꽉 찼습니다. 더 이상 추가할 수 없습니다." << endl;
        }
        else {
            menu_items[number_of_items++] = new MenuItem { name, description, vegetarian, price };
        }
    }

    MenuItem** getMenuItems() {
        return menu_items;
    }

    MenuItem** begin() {
        return &menu_items[0];
    }

    MenuItem** end() {
        if(number_of_items == 0) {
            return &menu_items[0];
        }
        return &menu_items[number_of_items-1] + 1;
    }
};


int main() {
    PancakeHouseMenu pancake_menu;
    DinerMenu diner_menu;

    for(auto e : pancake_menu) {
        cout << e->getName() << endl;
    }
    for(auto e : diner_menu) {
        cout << e->getName() << endl;
    }
}