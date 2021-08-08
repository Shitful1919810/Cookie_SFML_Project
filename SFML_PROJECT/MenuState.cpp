#include "MenuState.h"
#include "Utilities.h"
#include "Button.h"
Shitful::MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context)
    , mGUIContainer()
    //, mOptions()
    //, mOptionIndex(0)
{
    sf::Texture& texture = context.textures->get(TextureID::TitleScreen);
    mBackgroundSprite.setTexture(texture);
    sf::Vector2f windowSize(context.window->getSize());
    //sf::Font& font = context.fonts->get(FontID::Main);
    /*
    sf::Text playOption;
    playOption.setFont(font);
    playOption.setString("Play");
    centerOrigin(playOption);
    playOption.setPosition(context.window->getView().getSize() / 2.f);
    mOptions.push_back(playOption);


    sf::Text exitOption;
    exitOption.setFont(font);
    exitOption.setString("Exit");
    centerOrigin(exitOption);
    exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
    mOptions.push_back(exitOption);

    updateOptionText();*/
    auto playButton = std::make_shared<GUI::Button>(context);
    playButton->setPosition(0.5f * windowSize.x - 190, 360 - 49);
    playButton->setText("Start");
    playButton->setCallback([this]()
        {
            requestStackPop();
            requestStackPush(StateID::Game);
        });

    auto settingsButton = std::make_shared<GUI::Button>(context);
    settingsButton->setPosition(0.5f * windowSize.x - 190, 360 - 49 + 100);
    settingsButton->setText("Settings");
    settingsButton->setCallback([this]()
        {
            requestStackPush(StateID::Settings);
        });
        
    auto exitButton = std::make_shared<GUI::Button>(context);
    exitButton->setPosition(0.5f * windowSize.x - 190, 360 - 49 + 100 * 2);
    exitButton->setText("Exit");
    exitButton->setCallback([this]()
        {
            requestStackPop();
        });


    mGUIContainer.pack(playButton);
    mGUIContainer.pack(settingsButton);
    mGUIContainer.pack(exitButton);

    try
    {
        context.music->play(MusicID::MenuTheme);
    }
    catch (std::exception& e)
    {
        printf("%s\n", e.what());
        printf("%s\n", "为回避版权诉讼，已移除音乐文件，请用户自己将合适的文件(.ogg)重命名后放入Music文件夹");
    }
}

void Shitful::MenuState::draw()
{
    /*sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(mBackgroundSprite);

    for(const sf::Text& text : mOptions)
        window.draw(text);*/
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(mBackgroundSprite);
    window.draw(mGUIContainer);
}

bool Shitful::MenuState::update(sf::Time dt)
{
    return true;
}

bool Shitful::MenuState::handleEvent(const sf::Event& event)
{
    /*
    if (event.type != sf::Event::KeyPressed)
        return false;
    if (event.key.code == sf::Keyboard::Up)
    {
        if (mOptionIndex > 0)
            mOptionIndex--;
        else
            mOptionIndex = mOptions.size() - 1;
        updateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Down)
    {
        if (mOptionIndex < mOptions.size() - 1)
            mOptionIndex++;
        else
            mOptionIndex = 0;
        updateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Return)
    {
        if (mOptionIndex == Play)
        {
            requestStackPop();
            requestStackPush(StateID::Loading);
        }
        else if (mOptionIndex == Exit)
        {
            requestStackPop();
        }
    }
    return true;*/
    mGUIContainer.handleEvent(event);
    return false;
}