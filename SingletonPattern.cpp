// �̱��� ����(Singleton Pattern)
// Ŭ���� �ν��Ͻ��� �ϳ��� �����, �� �ν��Ͻ����� ���� ������ �����մϴ�.

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