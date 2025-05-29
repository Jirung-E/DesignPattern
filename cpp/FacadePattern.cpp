// 퍼사드 패턴(Facade Pattern)
// 서브시스템에 있는 일련의 인터페이스를 통합 인터페이스로 묶어줍니다.
// 또한 고수준 인터페이스도 정의하므로 서브시스템을 더 편리하게 사용할 수 있습니다.

#include <iostream>

using namespace std;


class Tuner {

};

class StreamingPlayer {
public:
    string now_playing = "";

public:
    void on() {
        cout << "스트리밍 플레이어가 켜졌습니다." << endl;
    }

    void off() {
        cout << "스트리밍 플레이어가 꺼졌습니다." << endl;
    }

    void play(const string& movie) {
        cout << "스트리밍 플레이어에서 " << movie << "를 재생합니다." << endl;
        now_playing = movie;
    }

    void stop() {
        cout << "스트리밍 플레이어에서 " << now_playing << " 재생을 종료합니다." << endl;
    }
};

class Amplifier {
private:
    StreamingPlayer* player = nullptr;

public:
    void on() {
        cout << "앰프가 켜졌습니다." << endl;
    }

    void off() {
        cout << "앰프가 꺼졌습니다." << endl;
    }

    void setStreamingPlayer(StreamingPlayer* player) {
        this->player = player;
        cout << "엠프를 스트리밍 플레이어와 연결합니다." << endl;
    }

    void setSurroundSound() {
        cout << "엠프를 서라운드 모드로 설정합니다." << endl;
    }

    void setVolume(int volume) {
        cout << "엠프 볼륨을 " << volume << "로 설정합니다." << endl;
    }
};

class Projector {
public:
    void on() {
        cout << "프로젝터가 켜졌습니다." << endl;
    }

    void off() {
        cout << "프로젝터가 꺼졌습니다." << endl;
    }

    void wideScreenMode() {
        cout << "프로젝터 화면 비율을 와이드 모드로 설정합니다." << endl;
    }
};

class TheaterLights {
public:
    void dim(int percentage) {
        cout << "조명 밝기를 " << percentage << "%로 설정합니다." << endl;
    }

    void on() {
        cout << "조명이 켜졌습니다." << endl;
    }
};

class Screen {
public:
    void down() {
        cout << "스크린이 내려옵니다." << endl;
    }

    void up() {
        cout << "스크린이 올라갑니다." << endl;
    }
};

class PopcornPopper {
public:
    void on() {
        cout << "팝콘 기계가 켜졌습니다." << endl;
    }

    void off() {
        cout << "팝콘 기계가 꺼졌습니다." << endl;
    }

    void pop() {
        cout << "팝콘 기계에서 팝콘을 튀기고 있습니다." << endl;
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
        cout << "영화 볼 준비 중" << endl;
        
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
        cout << "홈시어터를 끄는중" << endl;

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

    home_theater.watchMovie("인디아나 존스 : 레이더스");
    home_theater.endMovie();
}