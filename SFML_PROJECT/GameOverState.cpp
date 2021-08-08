#include "GameOverState.h"
#include "Utilities.h"

Shitful::GameOverState::GameOverState(StateStack& stack, Context context)
	: State(stack, context)
	, mGameOverText()
	, mElapsedTime(sf::Time::Zero)
{
	sf::Font& font = context.fonts->get(FontID::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mGameOverText.setFont(font);
	if (context.player->getChapterStatus() == Player::ChapterStatus::Failure)
		mGameOverText.setString("Mission failed!");
	else
		mGameOverText.setString("Mission successful!");

	mGameOverText.setCharacterSize(70);
	centerOrigin(mGameOverText);
	mGameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void Shitful::GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	// Create dark, semitransparent background
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mGameOverText);
}

bool Shitful::GameOverState::update(sf::Time dt)
{
	// 3秒之后返回标题画面
	mElapsedTime += dt;
	if (mElapsedTime > sf::seconds(3))
	{
		requestStateClear();
		requestStackPush(StateID::Menu);
	}
	return false;
}

bool Shitful::GameOverState::handleEvent(const sf::Event& event)
{
    return false;
}
