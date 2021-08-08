#include "SettingsState.h"
#include "Utilities.h"
Shitful::SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
	, mGUIContainer()
{
	mBackgroundSprite.setTexture(context.textures->get(TextureID::TitleScreen));
	sf::Vector2f windowSize(context.window->getSize());
	// Build key binding buttons and labels
	addButtonLabel(Player::MoveLeft, 0.5f * windowSize.x - 244 - 190, 100, "Move Left", context);
	addButtonLabel(Player::MoveRight, 0.5f * windowSize.x - 244 - 190, 100 + 100 * 1, "Move Right", context);
	addButtonLabel(Player::MoveUp, 0.5f * windowSize.x - 244 - 190, 100 + 100 * 2, "Move Up", context);
	addButtonLabel(Player::MoveDown, 0.5f * windowSize.x + 244 - 190, 100, "Move Down", context);
	addButtonLabel(Player::Output, 0.5f * windowSize.x - 190, 100 + 100 * 3, "Debug", context);

	updateLabels();

	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(0.5f * windowSize.x - 190, 150 + 100 * 4);
	backButton->setText("Back");
	backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

	mGUIContainer.pack(backButton);
}

void Shitful::SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool Shitful::SettingsState::update(sf::Time dt)
{
    return true;
}

bool Shitful::SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;
	for (std::size_t action = 0; action < Player::ActionCount; ++action)
	{
		if (mBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyPressed)
			{
				getContext().player->assignKey(static_cast<Player::Action>(action), event.key.code);
				mBindingButtons[action]->deactivate();
			}
			break;
		}
	}
	if (isKeyBinding)
		updateLabels();
	else
		mGUIContainer.handleEvent(event);
	return false;
}

void Shitful::SettingsState::updateLabels()
{
	Player& player = *getContext().player;
	for (std::size_t i = 0; i < Player::ActionCount; ++i)
	{
		sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
		mBindingLabels[i]->setText(toString(key));
		mBindingLabels[i]->setOutlineColor(sf::Color::Black);
		mBindingLabels[i]->setOutlineThickness(1.f);
	}
}

void Shitful::SettingsState::addButtonLabel(Player::Action action, float x, float y, const std::string& text, Context context)
{
	mBindingButtons[action] = std::make_shared<GUI::Button>(context);
	mBindingButtons[action]->setPosition(x, y);
	mBindingButtons[action]->setText(text);
	mBindingButtons[action]->setToggle(true);

	mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.fonts);
	mBindingLabels[action]->setPosition(x + 190, y + 20);

	mGUIContainer.pack(mBindingButtons[action]);
	mGUIContainer.pack(mBindingLabels[action]);
}