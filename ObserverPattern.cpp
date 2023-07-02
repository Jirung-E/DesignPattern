// ����������(Observer Pattern)
// �� ��ü�� ���°� �ٲ�� �� ��ü�� �����ϴ� �ٸ� ��ü���� ������ ���� 
// �ڵ����� ������ ���ŵǴ� ������� �ϴ��(one-to-many)�������� �����մϴ�.
// Pull ��İ� Push ����� �ְ�,
// Pull ����� ������ ��ü���� ���� ��ü�� ������ ������� ����̰�
// Push ����� ���� ��ü���� ������ ��ü�� ������ ������ ����̴�.

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
        // ���� ������Ʈ�ϴ� �ڵ�...

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