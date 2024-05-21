#include "SceneHighscore.h"
#include <iostream>
#include <fstream>
#include "FontManager.h"
#include "VideoManager.h"
#include "InputManager.h"
#include "SceneDirector.h"

using namespace std;

SceneHighscore::SceneHighscore()
{
    _pFontManager = nullptr;
    _pVideoManager = nullptr;
    _pInputManager = nullptr;
}

SceneHighscore::~SceneHighscore()
{

}

void SceneHighscore::Init()
{
    _pFontManager = FontManager::GetInstance();
    _pVideoManager = VideoManager::GetInstance();
    _pInputManager = InputManager::GetInstance();

    ReadScore();
}

void SceneHighscore::ReInit()
{
    _reInit = false;

    ReadScore();
}

void SceneHighscore::Update()
{
    if (_pInputManager->GetPause()) {
        _pInputManager->SetPause(false);
        _pInputManager->SetPlayerActions(InputManager::WAITING_SELECTION);
        SceneDirector::GetInstance()->ChangeScene(SceneEnum::MAIN, true);
    }
}

void SceneHighscore::Render()
{
    _pVideoManager->ClearScreen(0x00000000);

    _pFontManager->RenderText(0, "HIGHSCORE", { 255, 255, 255, 255 }, 160, 50);
    _pFontManager->RenderText(1, "Top 10", { 255, 255, 255, 255 }, (SCREEN_WIDTH / 2 - 50), 140);

    for (int i = 0; i < _scoreList.size() && i < 10; i++) {
        _pFontManager->RenderText(1, _scoreList[i], { 255, 255, 255, 255 }, static_cast<int>(SCREEN_WIDTH / 2.5), 200 + (i * 50));
    }

    _pVideoManager->UpdateScreen();
}

void SceneHighscore::ReadScore()
{
    fstream fileHandler;
    string allScore, score, name, points;
    vector<int> listPoints;

    _scoreList.clear();

    // Reading the points of the score list file and showing the top 10 best punctuations in screen.
    fileHandler.open("ScoreList.txt", ios::in); // Opening the file in the reading mode.

    if (fileHandler.is_open()) {
        while (!fileHandler.eof()) { // Until is the end of the file we read.
            getline(fileHandler, allScore);
        }

        fileHandler.close(); // Closing the file

        while (allScore.find(44) != string::npos) { // Until it doesn't find a , will cut the names and the points and will save them.
            score = allScore.substr(0, allScore.find(44)); // Cutting the name and the points.
            name = score.substr(0, score.find(124)); // Separating the name.
            points = score.substr(score.find(124) + 1); // Separating the points.

            listPoints.push_back(stoi(points)); // List of all the points to check the order later.
            _scoreList.push_back(points + " - " + name); // List of the visual display to the user. List of name and points.

            allScore.erase(0, allScore.find(44) + 1); // Erase of the , to get another names.
        }

        for (size_t i = 0; i < listPoints.size() - 1; i++) {
            for (size_t j = i + 1; j < listPoints.size(); j++) {
                if (listPoints[i] < listPoints[j]) { // Ordering the points with the sawp function.
                    swap(listPoints[i], listPoints[j]);
                    swap(_scoreList[i], _scoreList[j]);
                }
            }
        }
    }
}
