// 템플릿 메소드 패턴(Template Method Pattern)
// 알고리즘의 골격을 정의합니다.
// 템플릿 메서드를 사용하면 알고리즘의 일부 단계를 서브클래스에서 구현할 수 있으며,
// 알고리즘의 구조는 그대로 유지하면서 알고리즘의 특정 단계를 서브클래스에서 재정의할 수도 있습니다.

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
        cout << "물 끓이는 중" << endl;
    }

    virtual void brew() = 0;

    void pourInCup() {
        cout << "컵에 따르는 중" << endl;
    }

    virtual void addCondiments() = 0;

    virtual void hook() {
        
    }
};


class Coffee : public CaffeineBeverage {
public:
    void brew() override {
        cout << "필터로 커피를 우려내는 중" << endl;
    }

    void addCondiments() override {
        cout << "설탕과 우유를 추가하는 중" << endl;
    }
};

class Tea : public CaffeineBeverage {
public:
    void brew() override {
        cout << "찻잎을 우려내는 중" << endl;
    }

    void addCondiments() override {
        cout << "레몬을 추가하는 중" << endl;
    }

    void hook() override {
        cout << "완성되었습니다!" << endl;
    }
};


int main() {
    Tea tea;
    tea.prepareRecipe();

    cout << endl;

    Coffee coffee;
    coffee.prepareRecipe();
}