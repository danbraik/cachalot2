#include "Button.hpp"

using namespace gui;


Button::Button(const sf::Texture &texture, 
			   const sf::IntRect &texRectNormal, 
			   const sf::IntRect &texRectFocused)
	: mTexRectNormal(texRectNormal), 
	  mTexRectFocused(texRectFocused), 
	  mTexRectClicked(texRectFocused),
	  mSprite(texture),
	  mOldMouseButtonState(false),
	  mIsVisible(true),
	  mHasStartedClick(false),
	  mEnable(true)
{
}

Button::Button(const sf::Texture &texture, 
			   const sf::IntRect &texRectNormal, 
			   const sf::IntRect &texRectFocused,
			   const sf::IntRect &texRectClicked)
	: mTexRectNormal(texRectNormal), 
	  mTexRectFocused(texRectFocused),
	  mTexRectClicked(texRectClicked),
	  mSprite(texture),
	  mOldMouseButtonState(false),
	  mIsVisible(true),
	  mHasStartedClick(false),
	  mEnable(true)
{
}


void Button::setPosition(const sf::Vector2f &position)
{
	mSprite.setPosition(position);
}

void Button::setVisible(bool visible)
{
	mIsVisible = visible;
}

void Button::setEnable(bool enable)
{
	mEnable = enable;
	mSprite.setTextureRect(mTexRectNormal);
	
	if (mEnable)
		mSprite.setColor(sf::Color::White);
	else
		mSprite.setColor(sf::Color(255,255,255,172));
}

bool Button::update(sf::Vector2f mousePosition, bool mouseButtonPressed)
{
	if (!mIsVisible || !mEnable)
		return mHasStartedClick = false;	
	
	bool isFocusing = mSprite.getGlobalBounds().contains(mousePosition);
	
	// compute new display
	if (isFocusing) {
		if (mouseButtonPressed && mHasStartedClick)
			mSprite.setTextureRect(mTexRectClicked);
		else
			mSprite.setTextureRect(mTexRectFocused);
	} else
		mSprite.setTextureRect(mTexRectNormal);
	
	
	// test if user clicked
	bool hasClicked(false);
	
	if (isFocusing) {
		if (mouseButtonPressed && !mOldMouseButtonState)
			mHasStartedClick = true;
		else if (!mouseButtonPressed && mOldMouseButtonState && mHasStartedClick) {
			hasClicked = true;
			mHasStartedClick = false;
		}
	} else {
		if (mouseButtonPressed != mOldMouseButtonState)
			mHasStartedClick = false;
	}
	
	mOldMouseButtonState = mouseButtonPressed;
		
	return 	hasClicked;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (mIsVisible)
		target.draw(mSprite);
}


