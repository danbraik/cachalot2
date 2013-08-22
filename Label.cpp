#include "Label.hpp"

using namespace gui;

Label::Label(const sf::Font &font, const sf::IntRect &layout)
	: mFont(font), mTextSprite()
{
	mTextSprite.setFont(mFont);
	mTextSprite.setColor(sf::Color::Black);
	setLayout(layout);
}

void Label::setLayout(const sf::IntRect &layout)
{
	sf::Vector2f center(static_cast<int>(layout.width / 2 + layout.left),
						static_cast<int>(layout.height / 2 + layout.top));
	
	mTextSprite.setPosition(center);
}

void Label::setFont(const sf::Font &font)
{
	mFont = font;
	mTextSprite.setFont(mFont);
}

void Label::setString(const sf::String &string)
{
	mTextSprite.setString(string);
	sf::Vector2f center(static_cast<int>(mTextSprite.getGlobalBounds().width / 2),
						static_cast<int>(mTextSprite.getGlobalBounds().height / 2));
	mTextSprite.setOrigin(center);
}

void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(mTextSprite);
}
