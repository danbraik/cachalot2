#include "AnimatedLabel.hpp"
#include <iostream>

using namespace gui;

AnimatedLabel::AnimatedLabel(const sf::Font &font)
	: mFinalSprite(), 
	  mRenderTexture(), 
	  mTextSprite(), 
	  mFont(font), 
	  mHorizontalPosition(0),
	  mDoLoop(true)
{
	init();
}

AnimatedLabel::AnimatedLabel(const sf::Font &font,
							 const sf::IntRect & layout)
	: mFinalSprite(), 
	  mRenderTexture(), 
	  mTextSprite(), 
	  mFont(font), 
	  mHorizontalPosition(layout.width),
	  mDoLoop(true)
{
	init();
	setLayout(layout); // will call innerUpdate();
}

void AnimatedLabel::setLayout(const sf::IntRect & layout)
{
	mFinalSprite.setPosition(layout.left, layout.top);
	mRenderTexture.create(layout.width, layout.height);
	mFinalSprite.setTexture(mRenderTexture.getTexture());
	mHorizontalPosition = layout.width;
	innerUpdate();
}

void AnimatedLabel::setFont(const sf::Font &font)
{
	mFont = font;
	mTextSprite.setFont(mFont);
	innerUpdate();
}

void AnimatedLabel::setString(const sf::String &string)
{
	mTextSprite.setString(string);
	mTextSprite.setCharacterSize(40);
	innerUpdate();
}

void AnimatedLabel::setLoop(bool loop)
{
	mDoLoop = loop;
}

void AnimatedLabel::update(const sf::Time &elapsed)
{
	const int margin = 5;
	float textWidth = mTextSprite.getGlobalBounds().width;
	float widgetWidth = mFinalSprite.getGlobalBounds().width;
	
	if (mHorizontalPosition + textWidth < -margin)
		mHorizontalPosition += widgetWidth + textWidth + margin;
	
	float centerPosition = (widgetWidth - textWidth) / 2;
	float velocity = -80 * elapsed.asSeconds();
	
	if (mDoLoop ||
		(!mDoLoop && // even if loop is false, continue until label is centered
		 (mHorizontalPosition > centerPosition ||
		  mHorizontalPosition < (centerPosition + velocity - 5)
		 )))
		mHorizontalPosition += velocity;
	
	innerUpdate();
}

void AnimatedLabel::init()
{
	mTextSprite.setFont(mFont);
	mTextSprite.setColor(sf::Color::Black);
	
	mDegradeQuad.setPrimitiveType(sf::Quads);
	mDegradeQuad.append(sf::Vertex(sf::Vector2f(0,0), sf::Color::White));
	mDegradeQuad.append(sf::Vertex(sf::Vector2f(1,0), sf::Color(255,255,255,0)));
	mDegradeQuad.append(sf::Vertex(sf::Vector2f(1,1), sf::Color(255,255,255,0)));
	mDegradeQuad.append(sf::Vertex(sf::Vector2f(0,1), sf::Color::White));
	
	innerUpdate();
}

void AnimatedLabel::innerUpdate()
{	
	float finalSpriteHeight = mFinalSprite.getGlobalBounds().height;
	//std::cout << mTextSprite.getGlobalBounds().height << std::endl;
	float finalSpriteWidth = mFinalSprite.getGlobalBounds().width;
	float verticalPosition = (finalSpriteHeight-
							  (mTextSprite.getGlobalBounds().height+
							   mTextSprite.getCharacterSize()))/2;
			//(finalSpriteHeight + 
				//			 mTextSprite.getGlobalBounds().height /* 1.3f*/ ) / 2;
	mTextSprite.setPosition(static_cast<int>(mHorizontalPosition),
							static_cast<int>(verticalPosition));
	
	mRenderTexture.clear(sf::Color::White);
	mRenderTexture.draw(mTextSprite);
	
	// degrade
	{
		sf::RenderStates states;
		states.transform.scale(30, finalSpriteHeight);
		mRenderTexture.draw(mDegradeQuad, states);
	}
	{
		sf::RenderStates states;
		states.transform.translate(finalSpriteWidth,0);
		states.transform.scale(-30, finalSpriteHeight);
		mRenderTexture.draw(mDegradeQuad, states);
	}
	mRenderTexture.display();
}

void AnimatedLabel::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(mFinalSprite, states);
}



