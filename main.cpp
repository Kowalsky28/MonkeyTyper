#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fmt/ostream.h>

auto createMovableWords(std::vector<std::string> words, const sf::Font& font, int size = 40) -> std::vector<sf::Text>;
auto isLetter(char sign) -> bool;
auto increaseScore(int& counter, sf::Text& score) -> void;
auto getNextWord(int& index, sf::Vector2f& textPos, int n) -> void;
auto resetAnswer(std::string& ans, sf::Text& answer) -> void;
auto action1(std::string& ans, sf::Text& answer,int& counter, sf::Text& score,int& index, sf::Vector2f& textPos, int n) -> void;
auto createFonts() -> std::vector<sf::Font>;
auto setGreenColor(sf::RectangleShape& f1, sf::RectangleShape& f2,sf::RectangleShape& f3) -> void;
auto buttonsColorChange(sf::RectangleShape& b1,sf::RectangleShape& b2,sf::RectangleShape& b3,sf::RectangleShape& b4 ) -> void;
auto checkShortCut(sf::Event event,sf::Keyboard::Key k1, sf::Keyboard::Key k2) -> bool;
auto readtop5() -> std::vector<std::string>;
auto formatRanking(std::vector<std::string> scores) -> std::string;
auto checkResult(int score, std::vector<std::string> top5) -> void;
auto sizeButtonsAction(bool& change, int& size, int val, sf::RectangleShape& b1, sf::RectangleShape& b2, sf::RectangleShape& b3, sf::RectangleShape& b4  ) -> void;
auto fontButtonsAction(bool& change, sf::Font& current, sf::Font& next, sf::RectangleShape& b1, sf::RectangleShape& b2, sf::RectangleShape& b3, sf::RectangleShape& b4  ) -> void;
auto buttonSetColorAndPosition(sf::RectangleShape& button, float x ,float y, sf::Color color)->void;
auto textSetColorAndPosition(sf::Text& text, float x ,float y, sf::Color color)->void;
auto main() -> int{
    auto menuWindow = sf::RenderWindow(
            sf::VideoMode{800,600},
            "Menu - MonkeyTyper",
            sf::Style::Default,
            sf::ContextSettings(0,0,8)
    );

    auto gameWindow = sf::RenderWindow(
            sf::VideoMode({1200,900}),
            "Monkey Typer",
            sf::Style::Default,
            sf::ContextSettings(0,0,8)
    );
    gameWindow.setVisible(false);
//---------------------- zmienne do gry
    auto counter = int(0);
    auto missCounter = int(5);
    auto index1 = int(0);
    auto index2 = int(0);
    auto index3 = int(0);
    auto keepPlaying = bool(true);
    auto speedChange = int(10);
    auto rankingCheck = bool(true);
//---------------------- tablice do slow
    auto words1 = std::vector<std::string>{
        "one","two","three","four","five","six","seven","eight","nine","ten"
    };

    auto words2 = std::vector<std::string>{
            "sowa","las","bieszczady","fox","mleko","pjatk","laptop","amator","drzewo","laryngolog"
    };

    auto words3 = std::vector<std::string>{
        "bit", "piwo", "praca", "walizka", "plecak", "czapka", "misiak", "ministrant", "ekosystem","wypoczynek"
    };
//---------------------- twozenie czcionek
    auto fonts = createFonts();
    auto startFont = fonts[0];

    auto mW = createMovableWords(words1, startFont);
    auto mW2 = createMovableWords(words2, startFont);
    auto mW3 = createMovableWords(words3,startFont);

    auto textPos1 = sf::Vector2f(-200.f, 150.f);
    auto textPos2 = sf::Vector2f(-200.f, 350.f);
    auto textPos3 = sf::Vector2f (-200.f,550.f);
    auto textVelo = sf::Vector2f(0.20f, 0.f);

    auto score = sf::Text(sf::String(std::to_string(counter)), startFont, 50);
    textSetColorAndPosition(score,gameWindow.getSize().x - 60,5,sf::Color::Black);

    auto livesCounter = sf::Text(sf::String(std::to_string(missCounter)), startFont, 50);
    textSetColorAndPosition(livesCounter,gameWindow.getSize().x - 260,5,sf::Color::Black);

    auto livesText = sf::Text("Lives:",startFont,50);
    textSetColorAndPosition(livesText,gameWindow.getSize().x - 410,5,sf::Color::Black);

    auto ans = std::string("");
    auto answer = sf::Text(sf::String(ans), startFont, 40);
    textSetColorAndPosition(answer,20, gameWindow.getSize().y - 80,sf::Color::Black);
    //------------------------------------------------------------ End screen

    auto restarText = sf::Text("Press \"Enter\" to restart",startFont,55);
    restarText.setFillColor(sf::Color::Black);

    auto scoreText = sf::Text("Score:",startFont,50);
    scoreText.setFillColor(sf::Color::Black);

    auto backToMenuText = sf::Text("Press \"Escape\" to restart",startFont,55);
    backToMenuText.setFillColor(sf::Color::Black);

    //------------------------------------------------------------ menu

    auto title = sf::Text("MonkeyTyper",startFont,80);
    textSetColorAndPosition(title,50,30,sf::Color::Black);
//-------------------------- przyciski w menu
    auto startButton = sf::RectangleShape(sf::Vector2f(260 ,50));
    buttonSetColorAndPosition(startButton,50,200,sf::Color::Green);

    auto startBTextSf = sf::Text(sf::String(std::string("Start")),startFont,30);
    textSetColorAndPosition(startBTextSf,80,210,sf::Color::Black);

    auto fontButton = sf::RectangleShape(sf::Vector2f(100,50));
    buttonSetColorAndPosition(fontButton,50,270,sf::Color::Green);

    auto fontBTextSf = sf::Text(sf::String(std::string("Font")),startFont,30);
    textSetColorAndPosition(fontBTextSf,80,280,sf::Color::Black);

    auto sizeButton = sf::RectangleShape(sf::Vector2f(170,50));
    buttonSetColorAndPosition(sizeButton,50,340,sf::Color::Green);

    auto sizeBTextSf = sf::Text(sf::String(std::string("Font Size")),startFont,30);
    textSetColorAndPosition(sizeBTextSf,80,350,sf::Color::Black);

    auto leadersBoardButton = sf::RectangleShape(sf::Vector2f(260,50));
    buttonSetColorAndPosition(leadersBoardButton,50,410,sf::Color::Green);

    auto leadrBTextSf = sf::Text(sf::String(std::string("TopResults")),startFont,30);
    textSetColorAndPosition(leadrBTextSf,80,420,sf::Color::Black);

    auto leaderBoardText = sf::Text();
    leaderBoardText.setFont(startFont);
    leaderBoardText.setCharacterSize(40);
    textSetColorAndPosition(leaderBoardText,80,490,sf::Color::Black);
//--------------------------- przyciski czcionek
    auto font1Button = sf::RectangleShape(sf::Vector2f(150,50));
    buttonSetColorAndPosition(font1Button,160,270,sf::Color::Red);
    auto f1BTextSf = sf::Text(sf::String(std::string("Standard")),startFont,30);
    textSetColorAndPosition(f1BTextSf,170,280,sf::Color::Black);

    auto font2Button = sf::RectangleShape(sf::Vector2f(150,50));
    buttonSetColorAndPosition(font2Button,320,270,sf::Color::Green);
    auto f2BTextSf = sf::Text(sf::String(std::string("Hotpizza")),fonts[1],30);
    textSetColorAndPosition(f2BTextSf,330,280,sf::Color::Black);

    auto font3Button = sf::RectangleShape(sf::Vector2f(150,50));
    buttonSetColorAndPosition(font3Button,480,270,sf::Color::Green);
    auto f3BTextSf = sf::Text(sf::String(std::string("Marlboro")),fonts[2],35);
    textSetColorAndPosition(f3BTextSf,490,272,sf::Color::Black);

    auto font4Button = sf::RectangleShape(sf::Vector2f(150,50));
    buttonSetColorAndPosition(font4Button,640,270,sf::Color::Green);
    auto f4BTextSf = sf::Text(sf::String(std::string("MetaLord")),fonts[3],30);
    textSetColorAndPosition(f4BTextSf,650,275,sf::Color::Black);
    //--------------------------- przyciski do rozmiaru czcionki
    auto size1Button = sf::RectangleShape(sf::Vector2f(80,50));
    buttonSetColorAndPosition(size1Button,230,340,sf::Color::Red);
    auto s1BTextSf = sf::Text(sf::String(std::string("1")),startFont,30);
    textSetColorAndPosition(s1BTextSf,240,350,sf::Color::Black);

    auto size2Button = sf::RectangleShape(sf::Vector2f(80,50));
    buttonSetColorAndPosition(size2Button,320,340,sf::Color::Green);
    auto s2BTextSf = sf::Text(sf::String(std::string("2")),startFont,30);
    textSetColorAndPosition(s2BTextSf,330,350,sf::Color::Black);

    auto size3Button = sf::RectangleShape(sf::Vector2f(80,50));
    buttonSetColorAndPosition(size3Button,410,340,sf::Color::Green);
    auto s3BTextSf = sf::Text(sf::String(std::string("3")),startFont,30);
    textSetColorAndPosition(s3BTextSf,420,350,sf::Color::Black);

    auto size4Button = sf::RectangleShape(sf::Vector2f(80,50));
    buttonSetColorAndPosition(size4Button,500,340,sf::Color::Green);
    auto s4BTextSf = sf::Text(sf::String(std::string("4")),startFont,30);
    textSetColorAndPosition(s4BTextSf,510,350,sf::Color::Black);
    //--------------------------- zmienne do menu
    auto showFonts = bool(false);
    auto fontChanged = bool(false);
    auto currentFont = startFont;
    auto showSize = bool(false);
    auto fontSize = int(40);
    auto top5 = readtop5();
    auto showLeaderboard = bool(false);



//----------------------------- petla menu
    while(menuWindow.isOpen()){
        auto event = sf::Event();
        while(menuWindow.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                menuWindow.close();
                gameWindow.close();
            }
            if(checkShortCut(event,sf::Keyboard::LShift,sf::Keyboard::Num1)){
                fontButtonsAction(fontChanged,currentFont,fonts[0],font1Button,font2Button,font3Button,font4Button);
            }
            if(checkShortCut(event,sf::Keyboard::LShift,sf::Keyboard::Num2)){
                fontButtonsAction(fontChanged,currentFont,fonts[1],font2Button,font1Button,font2Button,font3Button);
            }
            if(checkShortCut(event,sf::Keyboard::LShift,sf::Keyboard::Num3)){
                fontButtonsAction(fontChanged,currentFont,fonts[2],font3Button,font1Button,font2Button,font4Button);
            }
            if(checkShortCut(event,sf::Keyboard::LShift,sf::Keyboard::Num4)){
                fontButtonsAction(fontChanged,currentFont,fonts[3],font4Button,font1Button,font2Button,font3Button);
            }
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    auto mousePos = sf::Mouse::getPosition(menuWindow);
                    if(startButton.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        menuWindow.close();
                        gameWindow.setVisible(true);
                    }
                    if(leadersBoardButton.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        leaderBoardText.setString(sf::String(std::string(formatRanking(top5))));
                        showLeaderboard = true;
                    }
                    if(fontButton.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        showFonts = true;
                    }
                    if(font1Button.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        fontButtonsAction(fontChanged,currentFont,fonts[0],font1Button,font2Button,font3Button,font4Button);
                    }
                    if(font2Button.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        fontButtonsAction(fontChanged,currentFont,fonts[1],font2Button,font1Button,font3Button,font4Button);
                    }
                    if(font3Button.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        fontButtonsAction(fontChanged,currentFont,fonts[2],font3Button,font1Button,font2Button,font4Button);
                    }
                    if(font4Button.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        fontButtonsAction(fontChanged,currentFont,fonts[3],font4Button,font1Button,font2Button,font3Button);
                    }
                    if(sizeButton.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        showSize = true;
                    }
                    if(size1Button.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        sizeButtonsAction(fontChanged, fontSize, 40, size1Button, size2Button, size3Button, size4Button);
                    }
                    if(size2Button.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        sizeButtonsAction(fontChanged, fontSize, 48, size2Button, size1Button, size3Button, size4Button);
                    }
                    if(size3Button.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        sizeButtonsAction(fontChanged, fontSize, 55, size3Button, size1Button, size2Button, size4Button);
                    }
                    if(size4Button.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        sizeButtonsAction(fontChanged, fontSize, 62, size4Button, size1Button, size2Button, size3Button);
                    }

                }
            }
        }
        if(fontChanged) {
            mW = createMovableWords(words1, currentFont,fontSize);
            mW2 = createMovableWords(words2, currentFont,fontSize);
            mW3 = createMovableWords(words3, currentFont,fontSize);
            fontChanged = false;
        }

        menuWindow.clear(sf::Color::White);
        menuWindow.draw(title);
        menuWindow.draw(startButton);
        menuWindow.draw(startBTextSf);
        menuWindow.draw(fontButton);
        menuWindow.draw(fontBTextSf);
        menuWindow.draw(sizeButton);
        menuWindow.draw(sizeBTextSf);
        menuWindow.draw(leadersBoardButton);
        menuWindow.draw(leadrBTextSf);
        if (showFonts) {
            menuWindow.draw(font1Button);
            menuWindow.draw(f1BTextSf);
            menuWindow.draw(font2Button);
            menuWindow.draw(f2BTextSf);
            menuWindow.draw(font3Button);
            menuWindow.draw(f3BTextSf);
            menuWindow.draw(font4Button);
            menuWindow.draw(f4BTextSf);
        }
        if (showSize) {
            menuWindow.draw(size1Button);
            menuWindow.draw(s1BTextSf);
            menuWindow.draw(size2Button);
            menuWindow.draw(s2BTextSf);
            menuWindow.draw(size3Button);
            menuWindow.draw(s3BTextSf);
            menuWindow.draw(size4Button);
            menuWindow.draw(s4BTextSf);
        }
        if (showLeaderboard){
            menuWindow.draw(leaderBoardText);
        }
        menuWindow.display();

    }

    //------------------------------------------------------------

    while(gameWindow.isOpen()) {
        auto event = sf::Event();
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gameWindow.close();
            if (event.type == sf::Event::TextEntered && isLetter((char) event.text.unicode)) {
                ans += (char) event.text.unicode;
                answer.setString(ans);
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Delete){
                ans = "";
                answer.setString(ans);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
                if (!ans.empty()) {
                    ans = ans.erase(ans.size() - 1, 1);
                    answer.setString(ans);
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !keepPlaying){
                counter = 0;
                score.setString(sf::String(std::to_string(counter)));
                score.setPosition(gameWindow.getSize().x - 60, 5);
                livesCounter.setFillColor(sf::Color::Black);
                livesText.setFillColor(sf::Color::Black);
                missCounter = 5;
                livesCounter.setString(sf::String(std::to_string(missCounter)));
                index1 = 0;
                index2 = 0;
                index3 = 0;
                ans = "";
                answer.setString(ans);
                mW[index1].setPosition(textPos1);
                mW2[index2].setPosition(textPos2);
                mW3[index3].setPosition(textPos3);
                textPos1 = sf::Vector2f(-200.f, 150.f);
                textPos2 = sf::Vector2f(-200.f, 350.f);
                textPos3 = sf::Vector2f (-200.f,550.f);
                textVelo = sf::Vector2f(0.20f, 0.f);
                speedChange = 10;
                keepPlaying = true;
                rankingCheck = true;
                top5 = readtop5();
            }
            if (ans == mW[index1].getString() && index1 < mW.size()) {
                mW[index1].setFillColor(sf::Color::Black);
                action1(ans, answer, counter, score, index1, textPos1,1);
            }
            if (ans == mW2[index2].getString() && index2 < mW2.size()) {
                mW2[index2].setFillColor(sf::Color::Black);
                action1(ans, answer, counter, score, index2, textPos2,2);
            }
            if(ans == mW3[index3].getString() && index3 < mW3.size()){
                mW3[index3].setFillColor(sf::Color::Black);
                action1(ans,answer,counter,score,index3,textPos3,3);
            }

        }

        textPos1 += textVelo; //cyklicznie zwiękaszjąca się ilość słów na ekranie aż wszystkie tablice podają słowa
        if (counter > 3)
            textPos2 += textVelo;
        if(counter > 7)
            textPos3 += textVelo;

        if (textPos1.x >= 1200.f) {  //podawanie kolejnych słow gdy te nie zostaną wpisane i zwiększenia missCountera
            mW[index1].setFillColor(sf::Color::Black);
            livesCounter.setString(std::to_string(--missCounter));
            getNextWord(index1, textPos1,1);
        }
        if (textPos2.x >= 1200.f) {
            mW2[index2].setFillColor(sf::Color::Black);
            livesCounter.setString(std::to_string(--missCounter));
            getNextWord(index2, textPos2,2);
        }
        if(textPos3.x >= 1200.f){
            mW3[index3].setFillColor(sf::Color::Black);
            livesCounter.setString(std::to_string(--missCounter));
            getNextWord(index3,textPos3,3);
        }

        if (textPos1.x >= 600.f) mW[index1].setFillColor(sf::Color::Blue);  //zmiana koloru w trakcie podróży słowa
        if (textPos2.x >= 600.f) mW2[index2].setFillColor(sf::Color::Blue);
        if (textPos3.x >= 600.f) mW3[index3].setFillColor(sf::Color::Blue);

        if (textPos1.x >= 900.f) mW[index1].setFillColor(sf::Color::Red);
        if (textPos2.x >= 900.f) mW2[index2].setFillColor(sf::Color::Red);
        if (textPos3.x >= 900.f) mW3[index3].setFillColor(sf::Color::Red);

        if(index1 == mW.size())   //zapętlenie tablic ze słowami / gra trwa do puki nie przegrasz
            index1 = 0;
        if(index2 == mW2.size())
            index2 = 0;
        if(index3 == mW3.size())
            index3 = 0;

        if(counter > speedChange){  //przyśpieszanie słów cyklicznie
            textVelo.x += 0.10f;
            speedChange += 15;
        }

        if (missCounter < 0) {
            keepPlaying = false;
            /*auto currLb = readtop5(file);
            fmt::println("{}",currLb);*/
        }
        if (missCounter == 0){
            livesCounter.setFillColor(sf::Color::Red);
            livesText.setFillColor(sf::Color::Red);
        }

        mW[index1].setPosition(textPos1);
        mW2[index2].setPosition(textPos2);
        mW3[index3].setPosition(textPos3);

        if (!keepPlaying) {

            textVelo.x = 0;
            gameWindow.clear(sf::Color::Red);
            score.setCharacterSize(70);
            score.setPosition(gameWindow.getSize().x / 2 - 30, gameWindow.getSize().y / 2 - 150);
            gameWindow.draw(score);
            scoreText.setPosition(400,315 );
            gameWindow.draw(scoreText);
            gameWindow.draw(restarText);
            gameWindow.display();
        }
        if(!keepPlaying && rankingCheck){
            checkResult(counter,top5);
            rankingCheck = false;
        }

        if (keepPlaying) {
            gameWindow.clear(sf::Color::White);
            gameWindow.draw(mW[index1]);
            gameWindow.draw(mW2[index2]);
            gameWindow.draw(mW3[index3]);
            gameWindow.draw(answer);
            scoreText.setPosition(gameWindow.getSize().x - 210, 5);
            gameWindow.draw(scoreText);
            score.setCharacterSize(50);
            gameWindow.draw(score);
            gameWindow.draw(livesText);
            gameWindow.draw(livesCounter);
            gameWindow.display();
        }
    }
}



