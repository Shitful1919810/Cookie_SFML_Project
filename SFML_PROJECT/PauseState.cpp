#include "PauseState.h"
#include "Utilities.h"
#include "Button.h"

Shitful::PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, mBackgroundSprite()
	, mPausedText()
	, mGUIContainer()
{
	sf::Font& font = context.fonts->get(FontID::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mPausedText.setFont(font);
	mPausedText.setString("Game Paused");
	mPausedText.setCharacterSize(70);
	centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	auto returnButton = std::make_shared<GUI::Button>(context);
	returnButton->setPosition(0.5f * windowSize.x - 190, 0.4f * windowSize.y + 75);
	returnButton->setText("Return");
	returnButton->setCallback([this]()
		{
			requestStackPop();
		});

	auto backToMenuButton = std::make_shared<GUI::Button>(context);
	backToMenuButton->setPosition(0.5f * windowSize.x - 190, 0.4f * windowSize.y + 75 + 100);
	backToMenuButton->setText("Back to menu");
	backToMenuButton->setCallback([this]()
		{
			requestStateClear();
			requestStackPush(Shitful::StateID::Menu);
		});

	mGUIContainer.pack(returnButton);
	mGUIContainer.pack(backToMenuButton);

	getContext().music->setPaused(true);
}

Shitful::PauseState::~PauseState()
{
	getContext().music->setPaused(false);
}

void Shitful::PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mGUIContainer);
}

bool Shitful::PauseState::update(sf::Time dt)
{
	return false;
}

bool Shitful::PauseState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}
