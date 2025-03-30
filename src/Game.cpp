#include "Game.h"
#include <iostream>
#include <cmath>
        Game::Game(){ 
            init();
        }

        void Game::init(){ 
                d_window.create(sf::VideoMode(1000, 1000), "Checker Board");
                d_window.setFramerateLimit(59);
                
}       
    
        void Game::systemMovement(float x_Old, float y_Old, float x_New, float y_New, size_t piece_tag){
            (void)x_Old;
            (void)y_Old;
            (void)x_New;
            (void)y_New;

            bool valid = false; 
            auto cur_entity = d_Entities.getEntity(piece_tag); //Checker

            int window_x = 1000; 
            int window_y = 1000;
            float block_size = floor(std::min(window_x/9.0f, window_y/9.0f));

            //Check Piece Vs Allowed Moves
            if("white_Checker" == cur_entity->tag && turn.getTurn()==2){
                if(
                    (((x_Old + block_size) == x_New) && ((y_Old+block_size)==y_New)) ||
                    (((x_Old - block_size) == x_New) && ((y_Old+block_size)==y_New))
                ){
                    valid = true;
                }
            } else if("black_Checker" == cur_entity->tag && turn.getTurn()==1){
                if(
                    ((x_Old + block_size == x_New) && (y_Old-block_size==y_New)) ||
                    ((x_Old - block_size == x_New) && (y_Old-block_size==y_New))
                ){
                    valid = true;
                }

            } else if((("black_king" == cur_entity->tag)&&turn.getTurn()==1) || (("white_king" == cur_entity->tag)&&turn.getTurn()==2)){
                if(
                    ((x_Old + block_size == x_New) && (y_Old+block_size==y_New)) ||
                    ((x_Old - block_size == x_New) && (y_Old+block_size==y_New)) ||
                    ((x_Old + block_size == x_New) && (y_Old-block_size==y_New)) ||
                    ((x_Old - block_size == x_New) && (y_Old-block_size==y_New))
                ){
                    valid = true;
                }
            }

            //Check Tile being Moved to incase Ally piece is alreadt there
            for(auto &e: d_Entities.getEntities()){ 
                if( (x_New == e->compTransform->pos.x) && (y_New == e->compTransform->pos.y)){
                    if(cur_entity->compChecker->circle.getFillColor() == e->compChecker->circle.getFillColor()){ //Check if Block is Ally
                        valid = false;
                    } else if( ((x_New+(x_New-x_Old)) == e->compTransform->pos.x) && ((y_New+(y_New-y_Old)) == e->compTransform->pos.y)){ //Check if Next block is open
                        valid = false;
                    } else if(valid){ // Check Jump
                        bool exists = false;
                        for(auto& tile :d_BoardTiles.getEntities()){ //Check for Tile to land on
                            if(
                                ((x_New+(x_New-x_Old)) == tile->compTransform->pos.x) && 
                                ((y_New+(y_New-y_Old)  == tile->compTransform->pos.y))
                            ){
                                exists = true;
                                for(auto&e2:d_Entities.getEntities()){ //Checks For entity on tile that jump land on
                                    if(
                                        (e2->compTransform->pos.x == tile->compTransform->pos.x) &&
                                        (e2->compTransform->pos.y == tile->compTransform->pos.y)
                                    ){
                                        exists = false;
                                    }
                                }
                            }
                        }
                        if(!exists){
                            valid = false;
                        }
                    }
                }
            }


            
            if (valid)
            {
                cur_entity->compTransform->pos.x = x_New;
                cur_entity->compTransform->pos.y = y_New;

                bool Attacked = Capture();
                if(!Attacked){
                    turn.switchTurn();
                    currentTurnOutput();
                } else { 
                    cur_entity->compTransform->pos.x += (x_New-x_Old);
                    cur_entity->compTransform->pos.y += (y_New-y_Old);
                    Promote();
                    Render();

                    bool AdditionalMove = CheckActionPossible(cur_entity->compTransform->pos.x, cur_entity->compTransform->pos.y, piece_tag);

                    if(AdditionalMove){
                        bool loop = true;
                        std::cout << "Select Next Location In Jump using Middle Click" << std::endl;
                        while(loop){
                            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle)){
                                sf::Vector2i localPosition = sf::Mouse::getPosition(d_window); // window is a sf::Window
                                for(auto& tile: d_BoardTiles.getEntities()){   
                                    int window_x = 1000; 
                                    int window_y = 1000;
                                    float block_size = std::min(window_x/9.0f, window_y/9.0f);
                                    if(
                                        (tile->compTransform->pos.x-localPosition.x < 0) && (tile->compTransform->pos.x-localPosition.x > -block_size) &&
                                        (tile->compTransform->pos.y-localPosition.y < 0) && (tile->compTransform->pos.y-localPosition.y > -block_size) 
                                    ){
                                        systemMovement(cur_entity->compTransform->pos.x, cur_entity->compTransform->pos.x, tile->compTransform->pos.x, tile->compTransform->pos.y, piece_tag);
                                        loop = false;
                                    }
                                }
                            }
                        }

                    } else {
                        turn.switchTurn();
                        currentTurnOutput();
                    }

                }
                Promote();
            } else {
                currentTurnOutput();
            }
        }

        void Game::currentTurnOutput(){
            std::cout<< "---------------------------------------------------------------" << std::endl;
            std::cout <<"Current Turn: " << turn.getTurnName() << std::endl; 
            
        }
        
    
        bool Game::CheckActionPossible(float x_Old, float y_Old, size_t piece_tag){
            auto cur_entity = d_Entities.getEntity(piece_tag); //Checker
            bool valid = false; 
            bool bottom_Right = false;
            bool bottom_Left = false;
            bool top_Right = false;
            bool top_Left = false;

            int window_x = 1000; 
            int window_y = 1000;
            float block_size = floor(std::min(window_x/9.0f, window_y/9.0f));
            //White 
            if("white_Checker" == cur_entity->tag && turn.getTurn()==2){
                bottom_Right = true;
                bottom_Left = true;                    
            
            } else if("black_Checker" == cur_entity->tag && turn.getTurn()==1){
                top_Left = true;
                top_Right = true;
            } else if((("black_king" == cur_entity->tag)&&turn.getTurn()==1) || (("white_king" == cur_entity->tag)&&turn.getTurn()==2)){
                bottom_Right = true;
                bottom_Left = true; 
                top_Left = true;
                top_Right = true;
            }
            
            //Bottom Right
            if(bottom_Right){
                for(auto &e: d_Entities.getEntities()){ //Checking Right Tile
                    if(e->compTransform->pos.x == x_Old+block_size && e->compTransform->pos.y == y_Old+block_size){
                        bool exists = false;

                            for(auto& tile :d_BoardTiles.getEntities()){ //Check for Tile to land on
                                if(
                                    ((x_Old+block_size+block_size) == tile->compTransform->pos.x) && 
                                    ((y_Old+block_size+block_size  == tile->compTransform->pos.y))
                                ){
                                    exists = true;
                                    for(auto&e2:d_Entities.getEntities()){ //Checks For entity on tile that jump land on
                                        if(
                                            (e2->compTransform->pos.x == tile->compTransform->pos.x) &&
                                            (e2->compTransform->pos.y == tile->compTransform->pos.y)
                                        ){
                                            exists = false;
                                        }
                                    }
                                }
                            }
                            if(exists){
                                valid = true;
                            }
                    }
                    
                }
            }

            if(bottom_Left){
                for(auto &e: d_Entities.getEntities()){ //Checking Right Tile
                    if(e->compTransform->pos.x == x_Old-block_size && e->compTransform->pos.y == y_Old+block_size){
                        bool exists = false;
                            for(auto& tile :d_BoardTiles.getEntities()){ //Check for Tile to land on
                                if(
                                    ((x_Old-block_size-block_size) == tile->compTransform->pos.x) && 
                                    ((y_Old+block_size+block_size  == tile->compTransform->pos.y))
                                ){
                                    exists = true;
                                    for(auto&e2:d_Entities.getEntities()){ //Checks For entity on tile that jump land on
                                        if(
                                            (e2->compTransform->pos.x == tile->compTransform->pos.x) &&
                                            (e2->compTransform->pos.y == tile->compTransform->pos.y)
                                        ){
                                            exists = false;
                                        }
                                    }
                                }
                            }
                            if(exists){
                                valid = true;
                            }
                    }
                    
                }
            }

            //Bottom Right
            if(top_Right){
                for(auto &e: d_Entities.getEntities()){ //Checking Right Tile
                    if(e->compTransform->pos.x == x_Old+block_size && e->compTransform->pos.y == y_Old-block_size){
                        bool exists = false;

                            for(auto& tile :d_BoardTiles.getEntities()){ //Check for Tile to land on
                                if(
                                    ((x_Old+block_size+block_size) == tile->compTransform->pos.x) && 
                                    ((y_Old-block_size-block_size  == tile->compTransform->pos.y))
                                ){
                                    exists = true;
                                    for(auto&e2:d_Entities.getEntities()){ //Checks For entity on tile that jump land on
                                        if(
                                            (e2->compTransform->pos.x == tile->compTransform->pos.x) &&
                                            (e2->compTransform->pos.y == tile->compTransform->pos.y)
                                        ){
                                            exists = false;
                                        }
                                    }
                                }
                            }
                            if(exists){
                                valid = true;
                            }
                    }
                    
                }
            }

            if(top_Left){
                for(auto &e: d_Entities.getEntities()){ //Checking Left Tile
                    if(e->compTransform->pos.x == x_Old-block_size && e->compTransform->pos.y == y_Old-block_size){
                        bool exists = false;
                            for(auto& tile :d_BoardTiles.getEntities()){ //Check for Tile to land on
                                if(
                                    ((x_Old-block_size-block_size) == tile->compTransform->pos.x) && 
                                    ((y_Old-block_size-block_size  == tile->compTransform->pos.y))
                                ){
                                    exists = true;
                                    for(auto&e2:d_Entities.getEntities()){ //Checks For entity on tile that jump land on
                                        if(
                                            (e2->compTransform->pos.x == tile->compTransform->pos.x) &&
                                            (e2->compTransform->pos.y == tile->compTransform->pos.y)
                                        ){
                                            exists = false;
                                        }
                                    }
                                }
                            }
                            if(exists){
                                valid = true;
                            }
                    }
                    
                }
            }
            //-----------
            //Check Tile being Moved to incase Ally piece is alreadt there
            
            //std::cout << valid << std::endl;
            return valid; //Cannot Move Again
        }


        bool firstClick = true;
        float previousClick_x = -1;
        float previousClick_y = -1;
        size_t EntityId;

    
        void Game::UserInput(){
            sf::Event event;
            
            while (d_window.pollEvent(event))
                {
                if (event.type == sf::Event::Closed)
                    d_window.close(); // Close the window when the close event is triggered
                

                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    sf::Vector2i localPosition = sf::Mouse::getPosition(d_window); // window is a sf::Window
                    if(firstClick){ 
                        for(auto& tile: d_BoardTiles.getEntities()){   
                            int window_x = 1000; 
                            int window_y = 1000;
                            float block_size = std::min(window_x/9.0f, window_y/9.0f);
                            if(
                                (tile->compTransform->pos.x-localPosition.x < 0) && (tile->compTransform->pos.x-localPosition.x > -block_size) &&
                                (tile->compTransform->pos.y-localPosition.y < 0) && (tile->compTransform->pos.y-localPosition.y > -block_size) 
                            ){

                                for(auto &e: d_Entities.getEntities()){ //Check if Checker on Tile
                                    if( (tile->compTransform->pos.x == e->compTransform->pos.x) && (tile->compTransform->pos.y == e->compTransform->pos.y)){
                                        previousClick_x = tile->compTransform->pos.x;
                                        previousClick_y = tile->compTransform->pos.y;
                                        EntityId = e->m_id;
                                        firstClick= false;
                                        std::cout << "Piece Selected: " << e->tag << std::endl;

                                    }
                                }
                            }
                        }
                    } else {
                            // Handle second click or subsequent clicks if needed                            
                        for(auto& tile: d_BoardTiles.getEntities()){   
                            int window_x = 1000; 
                            int window_y = 1000;
                            float block_size = std::min(window_x/9.0f, window_y/9.0f);
                            if(
                                (tile->compTransform->pos.x-localPosition.x < 0) && (tile->compTransform->pos.x-localPosition.x > -block_size) &&
                                (tile->compTransform->pos.y-localPosition.y < 0) && (tile->compTransform->pos.y-localPosition.y > -block_size) 
                            ){
                                //std::cout << "Piece Moved" << std::endl;
                                systemMovement(previousClick_x, previousClick_y, tile->compTransform->pos.x, tile->compTransform->pos.y, EntityId);
                                firstClick = true;
                            }
                        }
                    }
                }
            }
        }
        

        bool Game::Capture(){
            std::vector<std::shared_ptr<Entity>> RemoveEnt;
            bool removed =false;
            for(auto& entity1: d_Entities.getEntities()){  
                for(auto& entity2:d_Entities.getEntities()){
                    if (entity1.get()->compTransform && entity2.get()->compTransform) {
                        if(
                            (entity1.get()->compTransform->pos.x ==  entity2.get()->compTransform->pos.x) &&
                            (entity1.get()->compTransform->pos.y ==  entity2.get()->compTransform->pos.y) &&
                            (entity1.get()->m_id != entity2->m_id)
                        ){
                            removed = true;
                            if((entity1->tag == "white_Checker" || entity1->tag == "white_king") && turn.getTurn()==2){
                                RemoveEnt.push_back(entity2);
                            } else {
                                RemoveEnt.push_back(entity1);

                            }
                            break;
                        }
                    }
                }
                if(removed){
                    break;
                }   
            }

            for (auto& entity : RemoveEnt) {
                d_Entities.RemoveEntity(entity);
            }
            return removed;
        }
    
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

                    //Draw Entity
                    d_window.draw(e->compChecker->circle);
                }

                //ScoreBoard:
                
                //Display Turn and Score
            d_window.display();
        }

        void Game::Promote(){
            int window_x = 1000; 
            int window_y = 1000;
            window_x-=window_x/9.0f;
            window_y-=window_x/9.0f;
            int margin =std::min(window_x/9.0f, window_y/9.0f)/2;
            float block_size = floor(std::min(window_x/9.0f, window_y/9.0f));

            for(auto&e: d_Entities.getEntities()){
                if((e->compTransform->pos.y >= (margin+7*(block_size))) && (e->getTag() == "white_Checker")){
                        e->tag = "white_king";

                }
                if((e->compTransform->pos.y <= (margin)) && (e->getTag()=="black_Checker")){
                    e->tag = "black_king";
                }
            }
        }

        void Game::Winner(){
            int white_count = 0;
            int black_count = 0;
            for(auto&e:d_Entities.getEntities()){
                if(e->getTag()=="white_Checker" || e->getTag()=="white_king"){
                    white_count++;
                } else {
                    black_count++;
                }
            }
            if(black_count == 0){
                std::cout << "White Has Won! "<<std::endl;
                d_running=false;
            }
            if(white_count == 0){
                std::cout << "Black Has Won!" <<std::endl;
                d_running=false;
            }
        }

        void Game::run(){
            Spawn_Board();
            Spawn_Piece(); //Create Pieces on Initialization
            
            Render(); //Load Initial Board with Pieces
            
            std::cout << "Game Loaded: " << std::endl;
            std::cout << "Black Begins" << std::endl;
            
            while(d_running){
                UserInput();
                Render();
                Winner();
            }
        }
    
   