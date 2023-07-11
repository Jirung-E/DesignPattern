// �ݺ��� ����(Iterator Pattern)
// �÷����� ���� ����� �������� �����鼭 ����ü ���� ��� �׸� �����ϴ� ����� �����մϴ�.

// ������Ʈ ����(Composite Pattern)
// ��ü�� Ʈ�������� �����ؼ� �κ�-��ü ���������� �����մϴ�.
// ������Ʈ ������ ����ϸ� Ŭ���̾�Ʈ���� ���� ��ü�� ���� ��ü�� �Ȱ��� ������� �ٷ� �� �ֽ��ϴ�.

// C++�� �ٲٴ°� �� ������� ��ŵ
// 1. ������ ���� �ڹ��� Iterator�� C++�� iterator�� �۵� ����� �ٸ�. 
//    �ƴϸ� �׳� ���� C++�� iterator�� ��ã���ִ°�����...
// 2. Ŭ������ begin, end �Լ� �߰��� �غ����� ������ Ŭ������ �������ִ� �迭�� ���°� list�� ���� 
//    �޸𸮻󿡼� ����Ǿ����� �ʱ� ������ ������ �߻��Ѵ�. 
// 3. hasNext�� while�� �����°� �ϰ���� ����


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
        addItem("K&B ������ũ ��Ʈ", "��ũ���� ���׿� �佺Ʈ�� ��鿩�� ������ũ", false, 2.99);
        addItem("���ַ� ������ũ ��Ʈ", "�ް� �����̿� �ҽ����� ��鿩�� ������ũ", false, 2.99);
        addItem("��纣�� ������ũ", "�ż��� ��纣���� ��纣�� �÷����� ���� ������ũ", true, 3.49);
        addItem("����", "���⿡ ���� ��纣���� ���⸦ ���� �� �ִ� ����", true, 3.59);
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
        addItem("ä�������ڿ� BLT", "��� ���� ���� ������, ����, �丶�並 ���� �޴�", true, 2.99);
        addItem("BLT", "��� ���� ������, ����, �丶�並 ���� �޴�", false, 2.99);
        addItem("������ ����", "���� �����带 ����� ������ ����", false, 3.29);
        addItem("�ֵ���", "���ũ���Ʈ, ���� ���, ����, ġ� ��鿩�� �ֵ���", false, 3.05);
    }

public:
    void addItem(const string& name, const string& description, bool vegetarian, double price) {
        MenuItem item { name, description, vegetarian, price };
        if(number_of_items >= MAX_ITEMS) {
            cout << "�˼��մϴ�. �޴��� �� á���ϴ�. �� �̻� �߰��� �� �����ϴ�." << endl;
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