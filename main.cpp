#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <conio.h> // for _kbhit() and _getch()

using namespace std;

vector<string> loadFrames() {
    vector<string> frames;
    for (int i = 0; i <= 9; ++i) {
        string filename = "frame" + to_string(i) + ".txt";
        ifstream file(filename);
        if (!file) continue;
        string line, content;
        while (getline(file, line)) {
            content += line + "\n";
        }
        frames.push_back(content);
    }
    return frames;
}

int main() {
    vector<string> frames = loadFrames();
    if (frames.empty()) {
        cerr << "no frames found\n";
        return 1;
    }

    const double fps = 30.0;
    const auto delay = chrono::milliseconds((int)(1000 / fps));

    size_t index = 0;
    while (true) {
        cout << frames[index];
        cout.flush();
        this_thread::sleep_for(delay);

        if (_kbhit() && _getch() == 'q')
            break;

        index = (index + 1) % frames.size();
    }

    return 0;
}
