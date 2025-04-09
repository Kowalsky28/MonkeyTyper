#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <fmt/core.h>
#include <algorithm>
#include <fmt/ostream.h>



auto createMovableWords(std::vector<std::string> words, const sf::Font& font, int size = 40) -> std::vector<sf::Text>{
    auto mW = std::vector<sf::Text>();
    for(int i = 0;i<words.size();i++) {
        auto text = sf::Text(words[i], font, size);
        text.setFillColor(sf::Color::Black);
        mW.push_back(text);
    }
    return mW;
}

auto isLetter(char sign) -> bool{
    return (sign >= 'a' && sign <= 'z')
           || (sign >= 'A' && sign <= 'Z');
}
auto increaseScore(int& counter, sf::Text& score) -> void{
    score.setString(std::to_string(++counter));
}
auto getNextWord(int& index, sf::Vector2f& textPos, int n) -> void{
    index++;
    auto temp = int(0);
    switch (n) {
        case 1: temp = 50;
            break;
        case 2: temp = 250;
            break;
        case 3: temp = 450;
            break;
    }
    std::srand(time(nullptr));
    auto random = (std::rand()%200);
    textPos = sf::Vector2f(-100.f, random +temp);
    //std::cout << random << "\n";
}
auto resetAnswer(std::string& ans, sf::Text& answer) -> void{
    ans = "";
    answer.setString(ans);
}
auto action1(std::string& ans, sf::Text& answer,int& counter, sf::Text& score,int& index, sf::Vector2f& textPos, int n) -> void{
    resetAnswer(ans,answer);
    increaseScore(counter,score);
    getNextWord(index, textPos,n);
}
auto setGreenColor(sf::RectangleShape& f1, sf::RectangleShape& f2,sf::RectangleShape& f3) -> void {
    f1.setFillColor(sf::Color::Green);
    f2.setFillColor(sf::Color::Green);
    f3.setFillColor(sf::Color::Green);
}
auto createFonts() -> std::vector<sf::Font> {
    auto vec = std::vector<sf::Font>();
    auto font1 = sf::Font();
    if(!font1.loadFromFile("../font1.ttf"))
        std::cout << "Error ladowania czcionki nr1";
    vec.push_back(font1);

    auto font2 = sf::Font();
    if(!font2.loadFromFile("../hotpizza.ttf"))
        std::cout << "Error ladowania czcionki nr2";
    vec.push_back(font2);

    auto font3 = sf::Font();
    if(!font3.loadFromFile("../Marlboro.ttf"))
        std::cout << "Error ladowania czcionki nr3";
    vec.push_back(font3);

    auto font4 = sf::Font();
    if(!font4.loadFromFile("../METALORD.TTF"))
        std::cout << "Error ladowania czcionki nr4";
    vec.push_back(font4);

    return vec;
}

auto buttonsColorChange(sf::RectangleShape& b1,sf::RectangleShape& b2,sf::RectangleShape& b3,sf::RectangleShape& b4 ) -> void{
    b1.setFillColor(sf::Color::Red);
    setGreenColor(b2,b3,b4);
}

auto checkShortCut(sf::Event event,sf::Keyboard::Key k1, sf::Keyboard::Key k2) -> bool {
    return event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(k1)
           &&sf::Keyboard::isKeyPressed(k2);
}
auto readtop5() -> std::vector<std::string>{
    auto file = std::fstream("../top5.txt");
    auto scores = std::vector<std::string>();
    auto num = std::string();
    for(auto i = 0;i<5;i++) {
        file >> num;
        fmt::println("{}", num);
        scores.push_back(num);
    }
    return scores;

}
auto formatRanking(std::vector<std::string> scores) -> std::string {
    auto rankingString = std::string("");
    for(int i = 0;i<5;i++){
        rankingString += std::to_string(i+1)+". "+scores[i]+"  ";
    }
    return rankingString;

}
auto writeTop5(std::vector<int> vec){
    auto file = std::fstream("../top5.txt",std::ios::out | std::ios::trunc);
    auto stringToSave = std::string("");
    for(auto i = 0;i<5;i++){
        stringToSave += std::to_string(vec[i])+" ";
    }
    fmt::print(file,"{}",stringToSave);

}
auto checkResult(int score, std::vector<std::string> top5) -> void{
    auto tmpVec = std::vector<int>();
    auto tmpInt = int();
    for(auto i = 0;i<5;i++){
        tmpInt = 0;
        for(auto j = 0;j<top5[i].size();j++){
            tmpInt += top5[i][j]-48;
            tmpInt *= 10;
        }
        tmpInt /= 10;
        tmpVec.push_back(tmpInt);
    }
    tmpVec.push_back(score);
    std::ranges::sort(tmpVec,std::greater());
    auto newVec = std::vector<int>(tmpVec.begin(),tmpVec.end()-1);

    writeTop5(newVec);
}
auto sizeButtonsAction(bool& change, int& size, int val, sf::RectangleShape& b1, sf::RectangleShape& b2, sf::RectangleShape& b3, sf::RectangleShape& b4  ) -> void{
    size = val;
    change = true;
    buttonsColorChange(b1,b2,b3,b4);
}
auto fontButtonsAction(bool& change, sf::Font& current, sf::Font& next, sf::RectangleShape& b1, sf::RectangleShape& b2, sf::RectangleShape& b3, sf::RectangleShape& b4  ) -> void{
    current = next;
    change = true;
    buttonsColorChange(b1,b2,b3,b4);
}
auto buttonSetColorAndPosition(sf::RectangleShape& button, float x ,float y, sf::Color color)->void{
    button.setPosition({x,y});
    button.setFillColor(color);
}
auto textSetColorAndPosition(sf::Text& text, float x ,float y, sf::Color color)->void{
    text.setPosition({x,y});
    text.setFillColor(color);
}



