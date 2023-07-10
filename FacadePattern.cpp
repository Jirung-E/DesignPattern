// �ۻ�� ����(Facade Pattern)
// ����ý��ۿ� �ִ� �Ϸ��� �������̽��� ���� �������̽��� �����ݴϴ�.
// ���� ����� �������̽��� �����ϹǷ� ����ý����� �� ���ϰ� ����� �� �ֽ��ϴ�.

#include <iostream>

using namespace std;


class Tuner {

};

class StreamingPlayer {
public:
    string now_playing = "";

public:
    void on() {
        cout << "��Ʈ���� �÷��̾ �������ϴ�." << endl;
    }

    void off() {
        cout << "��Ʈ���� �÷��̾ �������ϴ�." << endl;
    }

    void play(const string& movie) {
        cout << "��Ʈ���� �÷��̾�� " << movie << "�� ����մϴ�." << endl;
        now_playing = movie;
    }

    void stop() {
        cout << "��Ʈ���� �÷��̾�� " << now_playing << " ����� �����մϴ�." << endl;
    }
};

class Amplifier {
private:
    StreamingPlayer* player = nullptr;

public:
    void on() {
        cout << "������ �������ϴ�." << endl;
    }

    void off() {
        cout << "������ �������ϴ�." << endl;
    }

    void setStreamingPlayer(StreamingPlayer* player) {
        this->player = player;
        cout << "������ ��Ʈ���� �÷��̾�� �����մϴ�." << endl;
    }

    void setSurroundSound() {
        cout << "������ ������ ���� �����մϴ�." << endl;
    }

    void setVolume(int volume) {
        cout << "���� ������ " << volume << "�� �����մϴ�." << endl;
    }
};

class Projector {
public:
    void on() {
        cout << "�������Ͱ� �������ϴ�." << endl;
    }

    void off() {
        cout << "�������Ͱ� �������ϴ�." << endl;
    }

    void wideScreenMode() {
        cout << "�������� ȭ�� ������ ���̵� ���� �����մϴ�." << endl;
    }
};

class TheaterLights {
public:
    void dim(int percentage) {
        cout << "���� ��⸦ " << percentage << "%�� �����մϴ�." << endl;
    }

    void on() {
        cout << "������ �������ϴ�." << endl;
    }
};

class Screen {
public:
    void down() {
        cout << "��ũ���� �����ɴϴ�." << endl;
    }

    void up() {
        cout << "��ũ���� �ö󰩴ϴ�." << endl;
    }
};

class PopcornPopper {
public:
    void on() {
        cout << "���� ��谡 �������ϴ�." << endl;
    }

    void off() {
        cout << "���� ��谡 �������ϴ�." << endl;
    }

    void pop() {
        cout << "���� ��迡�� ������ Ƣ��� �ֽ��ϴ�." << endl;
    }
};


class HomeTheaterFacade {
    Amplifier& amp;
    Tuner& tuner;
    StreamingPlayer& player;
    Projector& projector;
    TheaterLights& lights;
    Screen& screen;
    PopcornPopper& popper;

public:
    HomeTheaterFacade(Amplifier& amp,
        Tuner& tuner,
        StreamingPlayer& player,
        Projector& projector,
        TheaterLights& lights,
        Screen& screen,
        PopcornPopper& popper) : 
        amp { amp },
        tuner { tuner },
        player { player },
        projector { projector },
        lights { lights },
        screen { screen },
        popper { popper } {
        
    }

public:
    void watchMovie(const string& movie) {
        cout << "��ȭ �� �غ� ��" << endl;
        
        popper.on();
        popper.pop();

        lights.dim(10);

        screen.down();

        projector.on();
        projector.wideScreenMode();

        amp.on();
        amp.setStreamingPlayer(&player);
        amp.setSurroundSound();
        amp.setVolume(5);

        player.on();
        player.play(movie);
    }

    void endMovie() {
        cout << "Ȩ�þ��͸� ������" << endl;

        popper.off();

        lights.on();

        screen.up();

        projector.off();

        amp.off();

        player.stop();
        player.off();
    }
};


int main() {
    Amplifier amp;
    Tuner tuner;
    StreamingPlayer player;
    Projector projector;
    Screen screen;
    TheaterLights lights;
    PopcornPopper popper;

    HomeTheaterFacade home_theater { amp, tuner, player, projector, lights, screen, popper };

    home_theater.watchMovie("�ε�Ƴ� ���� : ���̴���");
    home_theater.endMovie();
}