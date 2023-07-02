// 옵저버패턴(Observer Pattern)
// 한 객체의 상태가 바뀌면 그 객체에 의존하는 다른 객체에게 연락이 가고 
// 자동으로 내용이 갱신되는 방식으로 일대다(one-to-many)의존성을 정의합니다.
// Pull 방식과 Push 방식이 있고,
// Pull 방식은 옵저버 객체에서 주제 객체의 정보를 끌어오는 방식이고
// Push 방식은 주제 객체에서 옵저버 객체로 정보를 보내는 방식이다.

#include <iostream>
#include <list>
#include <sstream>


using namespace std;


class Display {
public:
    virtual void update() = 0;
    virtual void display() = 0;
};


class WeatherData {
private:
    list<Display*> display;

public:
    void registerDisplay(Display* display) {
        this->display.push_back(display);
    }

    void removeDisplay(Display* display) {
        this->display.remove(display);
    }

    void updateDisplay() {
        for(auto e : display) {
            e->update();
        }
    }


    float getTemperature() {
        return 0.0f;
    }
    float getHumidity() {
        return 0.0f;
    }
    float getPressure() {
        return 0.0f;
    }

    void measurementsChanged() {
        // 대충 업데이트하는 코드...

        updateDisplay();
    }
};


// --------------------------------------------


class DataDisplay : public Display {
private:
    string temp;
    string humi;
    string pres;
    WeatherData& weather_data;

public:
    DataDisplay(WeatherData& wd) : weather_data { wd } {
        wd.registerDisplay(this);
    }

public:
    void update() {
        cout << "Data update" << endl;
        ostringstream oss;
        oss << "Temp: " << weather_data.getTemperature();
        this->temp = oss.str();
        oss.str("");
        oss << "Humi: " << weather_data.getHumidity();
        this->humi = oss.str();
        oss.str("");
        oss << "Pres: " << weather_data.getPressure();
        this->pres = oss.str();
        oss.str("");
    }

    void display() {
        cout << temp << endl;
        cout << humi << endl;
        cout << pres << endl;
    }
};

class DiscomfortIndexDisplay : public Display {
private:
    string text;
    WeatherData& weather_data;

public:
    DiscomfortIndexDisplay(WeatherData& wd) : weather_data { wd } {
        wd.registerDisplay(this);
    }

    void update() {
        cout << "DiscomfortIndex update" << endl;
        ostringstream oss;
        oss << "DiscomfortIndex: " 
            << 1.8f * weather_data.getTemperature() - 0.55f * (1-weather_data.getHumidity()) * (1.8f * weather_data.getTemperature() - 26) + 32;
        text = oss.str();
    }

    void display() {
        cout << text << endl;
    }
};


int main(char argc, char* argv[]) {
    WeatherData wd;
    DataDisplay ddis { wd };
    DiscomfortIndexDisplay didis { wd };
    wd.measurementsChanged();
    ddis.display();
    didis.display();
}