#include "ScoreScene.h"

ScoreScene::ScoreScene(sf::Vector2f l_centerView) : 
    BaseScene() {
	this->m_view = new sf::View(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));
    this->m_view->setCenter(l_centerView);
}

ScoreScene::ScoreScene() : 
    BaseScene() {}

ScoreScene::~ScoreScene(){}

void ScoreScene::onCreate(TextureMap &l_textureMap){
    readTabla();
   auto itr = l_textureMap.vm->find("Intro");
    if(itr != l_textureMap.vm->end()){
	    m_introSprite.setTexture(*itr->second);
    }		
	m_introSprite.setScale(0.65,0.65);
	m_introSprite.setOrigin(itr->second->getSize().x / 2.0f,
							itr->second->getSize().y / 2.0f);
    
	m_introSprite.setPosition(this->m_view->getCenter());
    
   m_font.loadFromFile("fonts/CompleteinHim.ttf");
    m_fontPuntaje.loadFromFile("fonts/BowlbyOneSC-Regular.otf");

    m_puntaje.setFont(getFontB());
    //m_puntaje.setFont(m_fontPuntaje);
	m_puntaje.setString(sf::String("Puntajes"));
	m_puntaje.setCharacterSize(65);
	m_puntaje.setFillColor(sf::Color::Red);
	sf::FloatRect textRectTitle = m_puntaje.getLocalBounds();
	m_puntaje.setOrigin(textRectTitle.left + textRectTitle.width / 2.0f,
		textRectTitle.top + textRectTitle.height / 2.0f);
	  
	m_puntaje.setPosition(this->m_view->getCenter().x,HEIGHT * 1.5/12);
    m_textos.push_back(m_puntaje);

    float posXName = this->m_view->getCenter().x- WIDTH * 1/7;
    float posXScore = this->m_view->getCenter().x* 1.005;
	std::stringstream s0;
        s0<<m_vTabla[0].nombre[0]<<m_vTabla[0].nombre[1]
            <<m_vTabla[0].nombre[2]<<m_vTabla[0].nombre[3];
	m_namePos0.setFont(getFontC());
	m_namePos0.setCharacterSize(45);
    m_namePos0.setFillColor(sf::Color::Red);
	m_namePos0.setPosition(posXName,HEIGHT * 3/12);
	m_namePos0.setString(s0.str());
    m_textos.push_back(m_namePos0);

	m_pos0.setFont(getFontC());
	m_pos0.setCharacterSize(45);
    m_pos0.setFillColor(sf::Color::Red);
	m_pos0.setPosition(posXScore,HEIGHT * 3/12);
	m_pos0.setString(std::to_string(m_vTabla[0].puntos));
    m_textos.push_back(m_pos0);
 
    std::stringstream s1;
        s1<<m_vTabla[1].nombre[0]<<m_vTabla[1].nombre[1]
            <<m_vTabla[1].nombre[2]<<m_vTabla[1].nombre[3];
	m_namePos1.setFont(m_font);
	m_namePos1.setCharacterSize(45);
    m_namePos1.setFillColor(sf::Color::Red);
	m_namePos1.setPosition(posXName,HEIGHT * 4/12);
	m_namePos1.setString(s1.str());
    m_textos.push_back(m_namePos1);

	m_pos1.setFont(m_font);
	m_pos1.setCharacterSize(45);
    m_pos1.setFillColor(sf::Color::Red);
	m_pos1.setPosition(posXScore,HEIGHT * 4/12);
	m_pos1.setString(std::to_string(m_vTabla[1].puntos));
    m_textos.push_back(m_pos1);

	std::stringstream s2;
        s2<<m_vTabla[2].nombre[0]<<m_vTabla[2].nombre[1]
            <<m_vTabla[2].nombre[2]<<m_vTabla[2].nombre[3];
    m_namePos2.setFont(m_font);
	m_namePos2.setCharacterSize(45);
    m_namePos2.setFillColor(sf::Color::Red);
	m_namePos2.setPosition(posXName,HEIGHT * 5/12);
	m_namePos2.setString(s2.str());
    m_textos.push_back(m_namePos2);

	m_pos2.setFont(m_font);
	m_pos2.setCharacterSize(45);
    m_pos2.setFillColor(sf::Color::Red);
	m_pos2.setPosition(posXScore,HEIGHT * 5/12);
	m_pos2.setString(std::to_string(m_vTabla[2].puntos));
    m_textos.push_back(m_pos2);

    std::stringstream s3;
        s3<<m_vTabla[3].nombre[0]<<m_vTabla[3].nombre[1]
            <<m_vTabla[3].nombre[2]<<m_vTabla[3].nombre[3];
	m_namePos3.setFont(m_font);
	m_namePos3.setCharacterSize(45);
    m_namePos3.setFillColor(sf::Color::Red);
	m_namePos3.setPosition(posXName,HEIGHT * 6/12);
	m_namePos3.setString(s3.str());
    m_textos.push_back(m_namePos3);

	m_pos3.setFont(m_font);
	m_pos3.setCharacterSize(45);
    m_pos3.setFillColor(sf::Color::Red);
	m_pos3.setPosition(posXScore,HEIGHT * 6/12);
	m_pos3.setString(std::to_string(m_vTabla[3].puntos));
    m_textos.push_back(m_pos3);

    std::stringstream s4;
        s4<<m_vTabla[4].nombre[0]<<m_vTabla[4].nombre[1]
            <<m_vTabla[4].nombre[2]<<m_vTabla[4].nombre[3];
	m_namePos4.setFont(m_font);
	m_namePos4.setCharacterSize(45);
    m_namePos4.setFillColor(sf::Color::Red);
	m_namePos4.setPosition(posXName,HEIGHT * 7/12);
	m_namePos4.setString(s4.str());
    m_textos.push_back(m_namePos4);

	m_pos4.setFont(m_font);
	m_pos4.setCharacterSize(45);
    m_pos4.setFillColor(sf::Color::Red);
	m_pos4.setPosition(posXScore,HEIGHT * 7/12);
	m_pos4.setString(std::to_string(m_vTabla[4].puntos));
    m_textos.push_back(m_pos4);

    m_escape.setFont(m_font);
	m_escape.setCharacterSize(35);
	m_escape.setString("-- Presione Escape para volver al inicio --");
    m_escape.setFillColor(sf::Color::Red);
     sf::FloatRect textRectSpace = m_escape.getLocalBounds();
	m_escape.setOrigin(textRectSpace.left + textRectSpace.width / 2.0f,
		textRectSpace.top + textRectSpace.height / 2.0f);
	m_escape.setPosition(this->m_view->getCenter().x,HEIGHT * 9/12);
    m_textos.push_back(m_escape); 

}

void ScoreScene::onDestroy(){}

void ScoreScene::activate(){}

void ScoreScene::deactivate(){}

void ScoreScene::readTabla(){
   Tabla import;
    std::ifstream fileIn("varios/Puntajes.dat", std::ios::binary);
	if(!fileIn.is_open()){
        std::cerr<<"No se pudo abrir el archivo de puntajes";
    }
    fileIn.seekg(0, std::ios::end);
    int tamanio = fileIn.tellg()/sizeof(Tabla);
    fileIn.seekg(0, std::ios::beg);
    if(tamanio != 0){
        for (size_t i = 0; i < tamanio; i++) {
		fileIn.read(reinterpret_cast<char*>(&import),sizeof(Tabla));
		m_vTabla.push_back(import);
        }
	}

	fileIn.close();
}

void ScoreScene::update(const sf::Time &l_time, Game &g){
    *this->m_view = g.getView();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){        
		g.switchScene(new IntroScene(g.getView().getCenter()));
	}
}

void ScoreScene::draw(sf::RenderWindow &w){
    w.clear(sf::Color(210,205,165));
    w.draw(m_introSprite);
    for(auto text: m_textos){
        w.draw(text);
    }
    
    w.setView(*m_view);
}

void ScoreScene::processEvent(const sf::Event &e){}