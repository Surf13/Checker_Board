#include "Game.h"
#include <iostream>
#include <cmath>
        Game::Game(){ //const std::string &configFile 
            init();
        }

        void Game::init(){ //const std::string &configFile
                d_window.create(sf::VideoMode(1000, 1000), "Checker Board");
                d_window.setFramerateLimit(59);
                
}       
                
        bool Game::systemMovement(float x_Old, float y_Old, float x_New, float y_New, std::string piece_tag){
            (void) x_Old;
            (void) y_Old;
            (void) x_New;
            (void) y_New;
            std::cout << "Piece Type:   " << piece_tag << std::endl << std::flush;
            std::cout << "Old Position: " << (int)x_Old << "," << (int)y_Old << std::endl;
            std::cout << "New Position: " << x_New << "," << y_New << std::endl;




            return false; //IF Sucessful Return False
        }
        
        bool firstClick = false;
        float previousClick_x = -1;
        float previousClick_y = -1;
        std::string EntityTag;

        void Game::UserInput(){
            sf::Event event;
            
            while (d_window.pollEvent(event))
                {
                if (event.type == sf::Event::Closed)
                    d_window.close(); // Close the window when the close event is triggered
                

                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    sf::Vector2i localPosition = sf::Mouse::getPosition(d_window); // window is a sf::Window
                    if(!firstClick){ 
                        //std::cout << "Position: (" << localPosition.x<< "," << localPosition.y << ")" << std::endl;
                        for(auto& tile: d_BoardTiles.getEntities()){   
                            int window_x = 1000; 
                            int window_y = 1000;
                            float block_size = std::min(window_x/9.0f, window_y/9.0f);
                            if(
                                (tile->compTransform->pos.x-localPosition.x < 0) && (tile->compTransform->pos.x-localPosition.x > -block_size) &&
                                (tile->compTransform->pos.y-localPosition.y < 0) && (tile->compTransform->pos.y-localPosition.y > -block_size) 
                            ){
                                //std::cout << "Tile Clicked: " << tile->tag << std::endl;

                                for(auto &e: d_Entities.getEntities()){ //Check if Checker on Tiele
                                    if( (tile->compTransform->pos.x == e->compTransform->pos.x) && (tile->compTransform->pos.y == e->compTransform->pos.y)){
                                        previousClick_x = tile->compTransform->pos.x;
                                        previousClick_y = tile->compTransform->pos.y;
                                        EntityTag = e->tag;
                                        firstClick= true;
                                    }
                                }
                            }
                        }
                    } else {
                            // Handle second click or subsequent clicks if needed
                        //std::cout << "Subsequent click at position: (" << localPosition.x << ", " << localPosition.y << ")\n";
                            
                        for(auto& tile: d_BoardTiles.getEntities()){   
                            int window_x = 1000; 
                            int window_y = 1000;
                            float block_size = std::min(window_x/9.0f, window_y/9.0f);
                            if(
                                (tile->compTransform->pos.x-localPosition.x < 0) && (tile->compTransform->pos.x-localPosition.x > -block_size) &&
                                (tile->compTransform->pos.y-localPosition.y < 0) && (tile->compTransform->pos.y-localPosition.y > -block_size) 
                            ){
                                //std::cout << "Tile Clicked: " << tile->tag << std::endl;
                                std::cout << previousClick_x << std::endl;
                                firstClick = systemMovement(previousClick_x, previousClick_y, localPosition.x, localPosition.y, EntityTag);
                            }
                            // Optionally, reset the flag if you want to handle another first click
                        //firstClick = false;
                        }
                    }
                }
            }
        }
        
        void Game::Capture(){}
    
        void Game::Spawn_Board(){
            //d_window.clear();
            int window_x = 1000; 
            int window_y = 1000;

            //Reduce for Margin Space
            window_x-=window_x/9.0f;
            window_y-=window_x/9.0f;

            int margin =std::min(window_x/9.0f, window_y/9.0f)/2;

            float block_size = std::min(window_x/8.0f, window_y/8.0f);

            for(int i=0; i< 8; i++){ //8
                for(int j=0;j<8;j++){ //8
                    auto tile = d_BoardTiles.addEntity("Tile");

                    tile->compTransform = std::make_shared<CompTransform>(Vec2{margin + j * block_size, margin + i * block_size});

                    //std::cout << "Block Position: ("<< margin + j * block_size << "," << margin + i * block_size << ")"<<std::endl;
                    if((i+j) % 2==0){
                        tile->compRect =  std::make_shared<CompRect>(block_size,block_size,sf::Color(139, 69, 19)); //Brown
                    } else {
                        tile->compRect =  std::make_shared<CompRect>(block_size,block_size,sf::Color(255, 255, 25)); //White
                    }
                }
            }
            
        }
        
        void Game::Spawn_Piece(){
            
            int window_x = 1000; 
            int window_y = 1000;

            //Reduce for Margin Space
            window_x-=window_x/9.0f;
            window_y-=window_x/9.0f;
            int margin =std::min(window_x/9.0f, window_y/9.0f)/2;
            float block_size = std::min(window_x/8.0f, window_y/8.0f);

            for(int i=0;i<3;i++){
                for(int j=0;j<8;j+=2){

                    auto white_piece = d_Entities.addEntity("white_Checker");
                    float setX = margin + j * block_size;
                    float setY = margin + i * block_size;
                    if(i % 2 == 1){
                        setX += block_size;
                    }

                    white_piece->compTransform = std::make_shared<CompTransform>(Vec2({setX,setY}));

                    white_piece->compChecker   = std::make_shared<CompChecker>(32.0f,32,32,sf::Color(255, 155, 255),sf::Color(255,155,255),4.0f);
                }
            }

            for(int i=7;i>4;i--){
                for(int j=0;j<8;j+=2){

                    auto white_piece = d_Entities.addEntity("black_Checker");
                    float setX = margin + j * block_size;
                    float setY = margin + i * block_size;
                    if(i % 2 == 1){
                        setX += block_size;
                    }
                    white_piece->compTransform = std::make_shared<CompTransform>(Vec2({setX,setY}));

                    white_piece->compChecker   = std::make_shared<CompChecker>(32.0f,32,32,sf::Color(155, 255, 255),sf::Color(155,255,255),4.0f);
                }
            }
    


        }
    
    //public:
        void Game:: Render(){
            d_window.clear();
                for(auto&e: d_BoardTiles.getEntities()){ //Render Tiles
                    //Set Position 
                    float e_X = e->compTransform->pos.x;
                    float e_Y = e->compTransform->pos.y;  

                    e->compRect->rect.setPosition(e_X,e_Y);

                    //Draw Tile
                    d_window.draw(e->compRect->rect);
                }

                for(auto& e: d_Entities.getEntities()){ // Render Checkers
                    //Adjust Circle Location on Board
                    int window_x = 1000; 
                    int window_y = 1000;
                    float block_size = std::min(window_x/9.0f, window_y/9.0f);

                    float e_X = e->compTransform->pos.x + block_size/2;
                    float e_Y = e->compTransform->pos.y + block_size/2;  
                    e->compChecker->circle.setPosition(e_X,e_Y);
                    //std::cout << "Id:" << e->m_id << std::endl;
                    //std::cout << "Position: (" << e->compTransform->pos.x<< "," << e->compTransform->pos.y << ")" << std::endl;
                    //Draw Entity
                    d_window.draw(e->compChecker->circle);
                }

            d_window.display();
        }

        void Game::run(){
            Spawn_Board();
            Spawn_Piece(); //Create Pieces on Initialization
            
            Render(); //Load Initial Board with Pieces

            while(d_running){
                UserInput();
                //Capture();
                Render();

                
                
            }
        }
    
    
/*
  while (d_window.isOpen())
            {
                // Process events (like closing the window)
                sf::Event event;
                while (d_window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    d_window.close(); // Close the window when the close event is triggered
                }
        
                // Clear the window with a black color
                //d_window.clear(sf::Color::Black);
                //Spawn_Board(); //Dosplay Board
                Render();
                // Display everything that was drawn
                d_window.display();
            }
*/

/*
    int main()
{
    // Create a window with a title "SFML Window" and a size of 800x600 pixels
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(150, 50, 250));
    
    // set a 10-pixel wide orange outline
    shape.setOutlineThickness(10.f);
    shape.setOutlineColor(sf::Color(250, 150, 100));
    // Main game loop (window stays open until user closes it)
    while (window.isOpen())
    {
        // Process events (like closing the window)
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close(); // Close the window when the close event is triggered
        }

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        // Display everything that was drawn
        window.draw(shape);
        window.display();
    }

    return 0;
}
    */