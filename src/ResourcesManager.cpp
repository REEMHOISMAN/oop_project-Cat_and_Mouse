#include "ResourcesManager.h"
#include <iostream> //for "cerr" in case loading one of the resources faild

/*================== instance =================*/
/**----------------------------------------------
 * this class is a 'singletone' class -> this function is the way
   other classes can reach to this class 'getters'
 *---------------------------------------------**/
ResourcesManager& ResourcesManager::instance()
{
    static ResourcesManager instance;
    return instance;
}

/*================== ResourcesManager constructor =================*/
ResourcesManager::ResourcesManager()
{
    initTextures();
    initSounds();

    if (!m_font.loadFromFile("ghostclan.ttf")) failedLoad("ghostclan.ttf");
   
    m_font.setSmooth(true);
}

/*================== getTexture =================*/
//enum Textures documentation in "const.h" file
sf::Texture& ResourcesManager::getTexture(const Textures type)
{
    int i = (int)type;
    return m_textures[i];
}

/*================== getFont =================*/
sf::Font& ResourcesManager::getFont()
{
    return m_font;
}

/*================== getSound =================*/
//enum Sounds documentation in "const.h" file
sf::SoundBuffer& ResourcesManager::getSound(const Sounds sound)
{
    int i = (int)sound;
    return m_sounds[i];
}

/*================== initTextures =================*/
void ResourcesManager::initTextures()
{
    std::string textureNames[TEXTURES] = 
    { "menu","newGame","help", "help1", "help2", "gameOver","exit", "InfoBoard",
        "timer", "life", "background" , "wall", "mouse",
        "cheese", "key" , "door", "cat", "popCat", "freeze"};

    for (int i = 0; i < TEXTURES; ++i)
    {
        sf::Texture texture;
        
        if (!texture.loadFromFile(textureNames[i] + ".png")) failedLoad(textureNames[i] + ".png");
   
        m_textures[i] = texture;
        m_textures[i].setSmooth(true);
    }
}

/*================== initSounds =================*/
void ResourcesManager::initSounds()
{
    std::string soundsNames[SOUNDS] = { "levelPassed", "lifeSound", "door",
        "freeze", "key", "lostLife", "eatCheese", "popCat", "time", "button"};

    for (int i = 0; i < SOUNDS; ++i)
    {
        sf::SoundBuffer sound;

        if (!sound.loadFromFile(soundsNames[i] + ".ogg")) failedLoad(soundsNames[i] + ".ogg");

        m_sounds[i] = sound;
    }
}

/*================== failedLoad =================*/
void ResourcesManager::failedLoad(const std::string msg) const
{
    std::cerr << "failed load " << msg << " in ResourceManager\n";
    exit(1);
}