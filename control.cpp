#include "thu_vien_2048.h"
// Hàm yêu cầu nhập và trả về nút - điều khiển của người chơi.
sf::Keyboard::Key control(sf::RenderWindow &window){
    clear_screen();

    sf::Event event;
    
    std::cout << "n: new game\n" 
              << "w: len\n" << "s: xuong\n" << "a: trai\n" << "d: phai\n" 
              << "u: undo\n" << "r: redo\n" 
              << "q: thoat\n" << "p: luu va thoat\n";

     do {
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }

            if (event.type == sf::Event::KeyPressed){

                if (event.key.code == sf::Keyboard::N || 
                    event.key.code == sf::Keyboard::W ||event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D || 
                    event.key.code == sf::Keyboard::U || event.key.code == sf::Keyboard::R || 
                    event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::P)
                    return event.key.code;
                
            }
        }
    } while (true);
}