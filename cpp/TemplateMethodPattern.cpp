// ���ø� �޼ҵ� ����(Template Method Pattern)
// �˰����� ����� �����մϴ�.
// ���ø� �޼��带 ����ϸ� �˰����� �Ϻ� �ܰ踦 ����Ŭ�������� ������ �� ������,
// �˰����� ������ �״�� �����ϸ鼭 �˰����� Ư�� �ܰ踦 ����Ŭ�������� �������� ���� �ֽ��ϴ�.

#include <iostream>

using namespace std;


class CaffeineBeverage {
public:
    virtual void prepareRecipe() final {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
        hook();
    }

    void boilWater() {
        cout << "�� ���̴� ��" << endl;
    }

    virtual void brew() = 0;

    void pourInCup() {
        cout << "�ſ� ������ ��" << endl;
    }

    virtual void addCondiments() = 0;

    virtual void hook() {
        
    }
};


class Coffee : public CaffeineBeverage {
public:
    void brew() override {
        cout << "���ͷ� Ŀ�Ǹ� ������� ��" << endl;
    }

    void addCondiments() override {
        cout << "������ ������ �߰��ϴ� ��" << endl;
    }
};

class Tea : public CaffeineBeverage {
public:
    void brew() override {
        cout << "������ ������� ��" << endl;
    }

    void addCondiments() override {
        cout << "������ �߰��ϴ� ��" << endl;
    }

    void hook() override {
        cout << "�ϼ��Ǿ����ϴ�!" << endl;
    }
};


int main() {
    Tea tea;
    tea.prepareRecipe();

    cout << endl;

    Coffee coffee;
    coffee.prepareRecipe();
}