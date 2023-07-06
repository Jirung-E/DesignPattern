// 커맨드 패턴(Command Pattern)
// 요청 내역을 객체로 캡슐화해서 객체를 서로 다른 요청 내역에 따라 매개변수화 할 수 있습니다.
// 이러면 요청을 큐에 저장하거나 로그로 기록하거나 작업 취소 기능을 사용할 수 있습니다.

#include <iostream>
#include <sstream>

using namespace std;


class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;

    //virtual string getName() {
        //return typeid(*this).name();
    string getName() {
    //void getName() {
        //cout << typeid(*this).name() << endl;
        return typeid(this).name();
    }
};

class NoCommand : public Command {  // 널 객체(NULL Object)
public:
    void execute() {

    }

    void undo() {

    }
};


class Light {
private:
    string name;

public:
    Light(const string& name) : name { name } {

    }

public:
    void on() {
        cout << name << " 불이 켜졌습니다" << endl;
    }

    void off() {
        cout << name << " 불이 꺼졌습니다" << endl;
    }
};

class LightOnCommand : public Command {
private:
    Light& light;

public:
    LightOnCommand(Light& light) : light { light } {
        
    }

public:
    void execute() {
        light.on();
    }

    void undo() {
        light.off();
    }
};

class LightOffCommand : public Command {
private:
    Light& light;

public:
    LightOffCommand(Light& light) : light { light } {

    }

public:
    void execute() {
        light.off();
    }

    void undo() {
        light.on();
    }
};


class CeilingFan {
public:
    enum Speed {
        OFF, LOW, MEDIUM, HIGH
    };

private:
    Speed speed;
    string location;

public:
    CeilingFan(const string& location) : speed { OFF }, location { location } {

    }

public:
    void high() {
        speed = HIGH;
        cout << "선풍기가 빠르게 돕니다!" << endl;
    }

    void medium() {
        speed = MEDIUM;
        cout << "선풍기가 적당한 속도로 돕니다" << endl;
    }

    void low() {
        speed = LOW;
        cout << "선풍기가 느리게 돕니다.." << endl;
    }

    void off() {
        speed = OFF;
        cout << "선풍기가 멈췄습니다" << endl;
    }

    Speed getSpeed() const {
        return speed;
    }
};

class CeilingFanOnCommand : public Command {
private:
    CeilingFan& fan;
    int prev_speed;

public:
    CeilingFanOnCommand(CeilingFan& fan) : fan { fan }, prev_speed { CeilingFan::OFF } {

    }

public:
    void execute() {
        prev_speed = fan.getSpeed();
        switch(prev_speed) {
        case CeilingFan::OFF:
            fan.low();
            break;
        case CeilingFan::LOW:
            fan.medium();
            break;
        case CeilingFan::MEDIUM:
            fan.high();
            break;
        case CeilingFan::HIGH:
            fan.low();
            break;
        }
    }

    void undo() {
        switch(prev_speed) {
        case CeilingFan::OFF:
            fan.off();
            break;
        case CeilingFan::LOW:
            fan.low();
            break;
        case CeilingFan::MEDIUM:
            fan.medium();
            break;
        case CeilingFan::HIGH:
            fan.high();
            break;
        }
    }
};

class CeilingFanOffCommand : public Command {
private:
    CeilingFan& fan;
    int prev_speed;

public:
    CeilingFanOffCommand(CeilingFan& fan) : fan { fan }, prev_speed { CeilingFan::OFF } {

    }

public:
    void execute() {
        prev_speed = fan.getSpeed();
        fan.off();
    }

    void undo() {
        switch(prev_speed) {
        case CeilingFan::OFF:
            fan.off();
            break;
        case CeilingFan::LOW:
            fan.low();
            break;
        case CeilingFan::MEDIUM:
            fan.medium();
            break;
        case CeilingFan::HIGH:
            fan.high();
            break;
        }
    }
};


class SimpleRemoteControl {
private:
    Command* slot;

public:
    SimpleRemoteControl() : slot { nullptr } {

    }

public:
    void setCommand(Command* command) {
        slot = command;
    }

    void buttonWasPressed() {
        slot->execute();
    }
};


class RemoteControl {
private:
    const int num_of_commands;
    Command** on_commands;
    Command** off_commands;
    Command* undo_command;

public:
    RemoteControl() : num_of_commands { 7 }, 
        on_commands { new Command*[num_of_commands] }, 
        off_commands { new Command*[num_of_commands] } {

        Command* no_com = new NoCommand;
        for(int i=0; i<num_of_commands; ++i) {
            on_commands[i] = no_com;
            off_commands[i] = no_com;
        }
        undo_command = no_com;
    }

public:
    void setCommand(int slot, Command* on_command, Command* off_command) {
        on_commands[slot] = on_command;
        off_commands[slot] = off_command;
    }

    void onButtonWasPushed(int slot) {
        on_commands[slot]->execute();
        undo_command = on_commands[slot];
    }

    void offButtonWasPushed(int slot) {
        off_commands[slot]->execute();
        undo_command = off_commands[slot];
    }

    void undoButtonWasPushed() {
        undo_command->undo();
    }

    //string toString() const {
    //    ostringstream oss;
    //    oss << "------ 리모컨 ------" << endl;
    //    for(int i=0; i<num_of_commands; ++i) {
    //        oss << "[slot " << i << "] " << on_commands[i]->getName() << "\t\t" << off_commands[i]->getName() << endl;  // 자바처럼은 안된다.
    //        //oss << "[slot " << i << "] ";
    //        //on_commands[i]->getName();
    //        //off_commands[i]->getName();
    //    }
    //    return oss.str();
    //}
};


int main() {
    //SimpleRemoteControl remote;
    //Light light;
    ////LightOnCommand light_on { light };
    //remote.setCommand(new LightOnCommand { light });
    //remote.buttonWasPressed();


    RemoteControl remote_control;
    Light living_room_light { "거실" };
    Light kitchen_light { "주방" };
    CeilingFan ceiling_fan { "선풍기" };

    remote_control.setCommand(0, new LightOnCommand { living_room_light }, new LightOffCommand { living_room_light });
    remote_control.setCommand(1, new LightOnCommand { kitchen_light }, new LightOffCommand { kitchen_light });
    remote_control.setCommand(2, new CeilingFanOnCommand { ceiling_fan }, new CeilingFanOffCommand { ceiling_fan });

    //cout << remote_control.toString() << endl;

    //remote_control.onButtonWasPushed(0);
    //remote_control.offButtonWasPushed(0);
    //remote_control.onButtonWasPushed(1);
    //remote_control.offButtonWasPushed(1);

    for(int i=0; i<7; ++i) {
        remote_control.onButtonWasPushed(i);
        remote_control.offButtonWasPushed(i);
    }

    remote_control.onButtonWasPushed(2);
    remote_control.onButtonWasPushed(2);
    remote_control.onButtonWasPushed(2);
    remote_control.undoButtonWasPushed();
    remote_control.onButtonWasPushed(2);
    remote_control.onButtonWasPushed(2);
    remote_control.onButtonWasPushed(2);
    remote_control.offButtonWasPushed(2);
}