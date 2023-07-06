// 싱글턴 패턴(Singleton Pattern)
// 클래스 인스턴스를 하나만 만들고, 그 인스턴스로의 전역 접근을 제공합니다.

#include <iostream>

using namespace std;


class ChocolateBoiler {
private:
    bool empty;
    bool boiled;

    static ChocolateBoiler* singleton;

private:
    ChocolateBoiler() : empty { true }, boiled { false } {

    }

public:
    static ChocolateBoiler& getInstance() {
        if(singleton == nullptr) {
            singleton = new ChocolateBoiler;
        }
        return *singleton;
    }

    void fill() {
        if(empty) {
            empty = false;
            boiled = false;
        }
    }

    void drain() {
        if(!empty && boiled) {
            empty = true;
        }
    }

    void boil() {
        if(!empty && !boiled) {
            boiled = true;
        }
    }

    bool isEmpty() const {
        return empty;
    }

    bool isBoiled() const {
        return boiled;
    }
};


int main() {
    ChocolateBoiler& cb = ChocolateBoiler::getInstance();
}