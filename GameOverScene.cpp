#include "GameOverScene.h"
#include "SharedContext.h"
#include "IntroScene.h"
#include "ScoreScene.h"
#include <SFML/Window/Keyboard.hpp>
#include <windows.h>
#include <fstream>

bool ordenarPtos(Tabla a, Tabla b){
    return (a.puntos>b.puntos);
};

GameOverScene::GameOverScene(int l_score, std::string l_time, bool exito, sf::Vector2f l_centerView) 
    :BaseScene(), m_newScore( l_score), m_newTime (l_time){
		if(exito){
			m_gameOver.setString(sf::String("Juego terminado"));
			m_music.openFromFile("sounds/victory.ogg");
			m_music.setVolume(50);
			m_music.setLoop(true);
			m_music.play();

		} else {
			m_gameOver.setString(sf::String("Intentalo de nuevo"));
			m_music.openFromFile("sounds/gameover.ogg");
			m_music.setVolume(50);
			m_music.setLoop(true);
			m_music.play();
		}
   	this->m_view = new sf::View(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));
   	this->m_view->setCenter(l_centerView);
    }

GameOverScene::~GameOverScene(){ 

}

void GameOverScene::onCreate(TextureMap &l_textureMap){
        
	m_fontGameOver.loadFromFile("fonts/BowlbyOneSC-Regular.otf");
    m_font.loadFromFile("fonts/CompleteinHim.ttf");

	m_gameOver.setFont(m_fontGameOver);
	//m_gameOver.setFont(getFontB());
	m_gameOver.setCharacterSize(65);
	m_gameOver.setFillColor(sf::Color::Red);
	sf::FloatRect textRectTitle = m_gameOver.getLocalBounds();
	m_gameOver.setOrigin(textRectTitle.left + textRectTitle.width / 2.0f,
		textRectTitle.top + textRectTitle.height / 2.0f);
	m_gameOver.setPosition(this->m_view->getCenter().x,HEIGHT * 1.5/12);
    m_toPrint.push_back(m_gameOver);
	
	m_textTime.setFont(getFontC());
	m_textTime.setCharacterSize(45);
    m_textTime.setFillColor(sf::Color::Red);
	m_textTime.setPosition(this->m_view->getCenter().x- WIDTH * 1/5,HEIGHT * 3/12);
	m_textTime.setString("Tu tiempo fue: ");
    m_toPrint.push_back(m_textTime);

	m_time.setFont(getFontC());
	m_time.setCharacterSize(45);
    m_time.setFillColor(sf::Color::Red);
	m_time.setPosition(this->m_view->getCenter().x + WIDTH * 1/8,HEIGHT * 3/12);
	m_time.setString(m_newTime);
    m_toPrint.push_back(m_time);
	
    m_textScore.setFont(getFontC());
	m_textScore.setCharacterSize(45);
    m_textScore.setFillColor(sf::Color::Red);
	m_textScore.setPosition(this->m_view->getCenter().x- WIDTH * 1/5,HEIGHT * 4/12);
	m_textScore.setString("Tu puntaje es: ");
    m_toPrint.push_back(m_textScore);

	m_score.setFont(getFontC());
	m_score.setCharacterSize(45);
    m_score.setFillColor(sf::Color::Red);
	m_score.setPosition(this->m_view->getCenter().x + WIDTH * 1/8,HEIGHT * 4/12);
	m_score.setString(std::to_string(m_newScore));
    m_toPrint.push_back(m_score);

	m_textName.setFont(getFontC());
	m_textName.setCharacterSize(55);
    m_textName.setFillColor(sf::Color::Red);
	m_textName.setString("Ingresa tu nombre: ");
    sf::FloatRect textRectName = m_textName.getLocalBounds();
	m_textName.setOrigin(textRectName.left + textRectName.width / 2.0f,
		textRectName.top + textRectName.height / 2.0f);
	m_textName.setPosition(this->m_view->getCenter().x,HEIGHT * 6/12);
    m_toPrint.push_back(m_textName);
	
    m_pos0.setFont(getFontC());
	m_pos0.setCharacterSize(60);
	m_pos0.setPosition(this->m_view->getCenter().x - WIDTH * 1/10,HEIGHT * 7/12);
    m_pos0.setFillColor(sf::Color::Red);

	m_pos1.setFont(getFontC());
	m_pos1.setCharacterSize(60);
	m_pos1.setPosition(this->m_view->getCenter().x - WIDTH * 1/26,HEIGHT * 7/12);
    m_pos1.setFillColor(sf::Color::Red);
	
	m_pos2.setFont(getFontC());
	m_pos2.setCharacterSize(60);
	m_pos2.setPosition(this->m_view->getCenter().x + WIDTH * 1/26,HEIGHT * 7/12);
    m_pos2.setFillColor(sf::Color::Red);
	
	m_pos3.setFont(getFontC());
	m_pos3.setCharacterSize(60);
	m_pos3.setPosition(this->m_view->getCenter().x + WIDTH * 1/10,HEIGHT * 7/12);
    m_pos3.setFillColor(sf::Color::Red);	

	m_space.setFont(getFontC());
	m_space.setCharacterSize(35);
	m_space.setString("-- Presione Espacio para continuar --");
    m_space.setFillColor(sf::Color::Red);
     sf::FloatRect textRectSpace = m_space.getLocalBounds();
	m_space.setOrigin(textRectSpace.left + textRectSpace.width / 2.0f,
		textRectSpace.top + textRectSpace.height / 2.0f);
	m_space.setPosition(this->m_view->getCenter().x,HEIGHT * 9/12);
    m_toPrint.push_back(m_space);
}

void GameOverScene::onDestroy(){
}

void GameOverScene::activate(){}

void GameOverScene::deactivate(){}

void GameOverScene::saveScore(int l_p, std::string l_n){
    std::ifstream fileIn("varios/Puntajes.dat", std::ios::binary);
	if(!fileIn.is_open()){
        std::cerr<<"No se pudo abrir el archivo de puntajes";
    }

    fileIn.seekg(0, std::ios::end);
    int tamanio = fileIn.tellg()/sizeof(Tabla);
    fileIn.seekg(0, std::ios::beg);
    if(tamanio != 0){
        for (size_t i = 0; i < tamanio; i++) {
            Tabla import;
            fileIn.read(reinterpret_cast<char*>(&import),sizeof(Tabla));
            m_vTabla.push_back(import);
        }
    }
	fileIn.close();

    Tabla exp;
    exp.puntos = l_p;
    strcpy(exp.nombre, l_n.c_str());
    
    m_vTabla.push_back(exp);

    sort(m_vTabla.begin(), m_vTabla.end(), ordenarPtos);

    std::ofstream fileOut("varios/Puntajes.dat", std::ios::binary|std::ios::trunc);
	if(!fileOut.is_open()){
        std::cerr<<"No se pudo abrir el archivo de puntajes";
    }
    for (size_t i = 0; i< m_vTabla.size();i++) {
		fileOut.write(reinterpret_cast<char*>(&m_vTabla[i]),sizeof(Tabla));
	}

	fileOut.close();

}

void GameOverScene::update(const sf::Time &l_time, Game &g){
	*this->m_view = g.getView();
    Sleep(50);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		Sleep(100);
		if(pos0=='-'){pos0='A';}
		else if(pos1=='-'){pos1='A';}
		else if(pos2=='-'){pos2='A';}
		else if(pos3=='-'){pos3='A';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
		Sleep(100);
		if(pos0=='-'){pos0='B';}
		else if(pos1=='-'){pos1='B';}
		else if(pos2=='-'){pos2='B';}
		else if(pos3=='-'){pos3='B';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
		Sleep(100);
		if(pos0=='-'){pos0='C';}
		else if(pos1=='-'){pos1='C';}
		else if(pos2=='-'){pos2='C';}
		else if(pos3=='-'){pos3='C';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		Sleep(100);
		if(pos0=='-'){pos0='D';}
		else if(pos1=='-'){pos1='D';}
		else if(pos2=='-'){pos2='D';}
		else if(pos3=='-'){pos3='D';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
		Sleep(100);
		if(pos0=='-'){pos0='E';}
		else if(pos1=='-'){pos1='E';}
		else if(pos2=='-'){pos2='E';}
		else if(pos3=='-'){pos3='E';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
		Sleep(100);
		if(pos0=='-'){pos0='F';}
		else if(pos1=='-'){pos1='F';}
		else if(pos2=='-'){pos2='F';}
		else if(pos3=='-'){pos3='F';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
		Sleep(100);
		if(pos0=='-'){pos0='G';}
		else if(pos1=='-'){pos1='G';}
		else if(pos2=='-'){pos2='G';}
		else if(pos3=='-'){pos3='G';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)){
		Sleep(100);
		if(pos0=='-'){pos0='H';}
		else if(pos1=='-'){pos1='H';}
		else if(pos2=='-'){pos2='H';}
		else if(pos3=='-'){pos3='H';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
		Sleep(100);
		if(pos0=='-'){pos0='I';}
		else if(pos1=='-'){pos1='I';}
		else if(pos2=='-'){pos2='I';}
		else if(pos3=='-'){pos3='I';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
		Sleep(100);
		if(pos0=='-'){pos0='J';}
		else if(pos1=='-'){pos1='J';}
		else if(pos2=='-'){pos2='J';}
		else if(pos3=='-'){pos3='J';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
		Sleep(100);
		if(pos0=='-'){pos0='K';}
		else if(pos1=='-'){pos1='K';}
		else if(pos2=='-'){pos2='K';}
		else if(pos3=='-'){pos3='K';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
		Sleep(100);
		if(pos0=='-'){pos0='L';}
		else if(pos1=='-'){pos1='L';}
		else if(pos2=='-'){pos2='L';}
		else if(pos3=='-'){pos3='L';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
		Sleep(100);
		if(pos0=='-'){pos0='M';}
		else if(pos1=='-'){pos1='M';}
		else if(pos2=='-'){pos2='M';}
		else if(pos3=='-'){pos3='M';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
		Sleep(100);
		if(pos0=='-'){pos0='N';}
		else if(pos1=='-'){pos1='N';}
		else if(pos2=='-'){pos2='N';}
		else if(pos3=='-'){pos3='N';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
		Sleep(100);
		if(pos0=='-'){pos0='O';}
		else if(pos1=='-'){pos1='O';}
		else if(pos2=='-'){pos2='O';}
		else if(pos3=='-'){pos3='O';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
		Sleep(100);
		if(pos0=='-'){pos0='P';}
		else if(pos1=='-'){pos1='P';}
		else if(pos2=='-'){pos2='P';}
		else if(pos3=='-'){pos3='P';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
		Sleep(100);
		if(pos0=='-'){pos0='Q';}
		else if(pos1=='-'){pos1='Q';}
		else if(pos2=='-'){pos2='Q';}
		else if(pos3=='-'){pos3='Q';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
		Sleep(100);
		if(pos0=='-'){pos0='R';}
		else if(pos1=='-'){pos1='R';}
		else if(pos2=='-'){pos2='R';}
		else if(pos3=='-'){pos3='R';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		Sleep(100);
		if(pos0=='-'){pos0='S';}
		else if(pos1=='-'){pos1='S';}
		else if(pos2=='-'){pos2='S';}
		else if(pos3=='-'){pos3='S';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
		Sleep(100);
		if(pos0=='-'){pos0='T';}
		else if(pos1=='-'){pos1='T';}
		else if(pos2=='-'){pos2='T';}
		else if(pos3=='-'){pos3='T';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)){
		Sleep(100);
		if(pos0=='-'){pos0='U';}
		else if(pos1=='-'){pos1='U';}
		else if(pos2=='-'){pos2='U';}
		else if(pos3=='-'){pos3='U';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)){
		Sleep(100);
		if(pos0=='-'){pos0='V';}
		else if(pos1=='-'){pos1='V';}
		else if(pos2=='-'){pos2='V';}
		else if(pos3=='-'){pos3='V';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		Sleep(100);
		if(pos0=='-'){pos0='W';}
		else if(pos1=='-'){pos1='W';}
		else if(pos2=='-'){pos2='W';}
		else if(pos3=='-'){pos3='W';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
		Sleep(100);
		if(pos0=='-'){pos0='X';}
		else if(pos1=='-'){pos1='X';}
		else if(pos2=='-'){pos2='X';}
		else if(pos3=='-'){pos3='X';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)){
		Sleep(100);
		if(pos0=='-'){pos0='Y';}
		else if(pos1=='-'){pos1='Y';}
		else if(pos2=='-'){pos2='Y';}
		else if(pos3=='-'){pos3='Y';}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
		Sleep(100);
		if(pos0=='-'){pos0='Z';}
		else if(pos1=='-'){pos1='Z';}
		else if(pos2=='-'){pos2='Z';}
		else if(pos3=='-'){pos3='Z';}
	}
	m_pos0.setString(pos0);
	m_pos1.setString(pos1);
	m_pos2.setString(pos2);
	m_pos3.setString(pos3);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        std::stringstream s;
        s<<pos0<<pos1<<pos2<<pos3;
        saveScore(m_newScore, s.str());
        
		g.switchScene(new ScoreScene(g.getView().getCenter()));
	}
}

void GameOverScene::draw(sf::RenderWindow &w){
    w.clear(sf::Color(210,205,165));
    for(auto text: m_toPrint){
        w.draw(text);
    }
    w.draw(m_pos0);
    w.draw(m_pos1);
    w.draw(m_pos2);
    w.draw(m_pos3);

    w.setView(*m_view);
}




void GameOverScene::processEvent(const sf::Event &e){}
