#include <iostream>
#include <cmath>
#include "Slider.hpp"


using namespace gui;

Slider::Slider()
	: mMin(0),
	  mMax(100),
	  mValue(0),
	  mFinalSprite(),
	  mRenderTexture(),
	  mOldMouseState(false),
	  mHasStartedDrag(false),
	  mDragValue(0),
	  mEnable(true),
	  mOldDrawingValue(-1)
{
}

void Slider::setLayout(const sf::IntRect &layout)
{
	mFinalSprite.setPosition(layout.left, layout.top);
	mRenderTexture.create(layout.width, layout.height);
	mFinalSprite.setTexture(mRenderTexture.getTexture());
}

void Slider::setMin(float min)
{
	mMin = std::min(min, mMax-.1f);
	setValue(mValue);
}

void Slider::setMax(float max)
{
	mMax = std::max(mMin+.1f, max);
	setValue(mValue);
}

void Slider::setValue(float value)
{
	mValue = std::max(mMin, std::min(value, mMax));
}

void Slider::setEnable(bool enable)
{
	mEnable = enable;
}

bool Slider::update(sf::Vector2f mousePosition, bool mouseButtonPressed, float &userValue)
{
	bool hasUserValue(false);
	
	const sf::Vector2f finalPosition(mFinalSprite.getGlobalBounds().left,
									 mFinalSprite.getGlobalBounds().top);
	const sf::Vector2f finalSize(mFinalSprite.getGlobalBounds().width,
								 mFinalSprite.getGlobalBounds().height);
	
	bool hasFocus = mFinalSprite.getGlobalBounds().contains(mousePosition);
	
	// test if user has enter new value
	
	
	if (mEnable) {
		if (mouseButtonPressed && !mOldMouseState) {// user pressed
			if (hasFocus)
				mHasStartedDrag = true;
		} else if (!mouseButtonPressed && mOldMouseState) { // user released
			if (mHasStartedDrag) {
				mHasStartedDrag = false;
				hasUserValue = true;
			}
		}
		mOldMouseState = mouseButtonPressed;
	
		
		// compute user value
		if (mHasStartedDrag || hasUserValue) {
			float relativeMousePos =  mousePosition.x - finalPosition.x;
			relativeMousePos = std::max(0.f, std::min(finalSize.x, relativeMousePos));
			
			
			mDragValue = relativeMousePos / finalSize.x
						* (mMax-mMin) 
						+ mMin;
			
			// return user value
			//if (hasUserValue)
			userValue = mDragValue;
			
			//std::cout << userValue << std::endl;
		}
	}
	
	float drawingValue = (mHasStartedDrag) ? mDragValue : mValue;
	
	if (drawingValue != mOldDrawingValue)
	{
		mOldDrawingValue = drawingValue;
		
		float horizontalPos = (drawingValue - mMin) / (mMax-mMin) * 
							  mFinalSprite.getGlobalBounds().width ;
		
		mRenderTexture.clear(sf::Color(240,240,240));
		sf::RectangleShape rect(sf::Vector2f(horizontalPos, mFinalSprite.getGlobalBounds().height));
		rect.setFillColor(sf::Color::Black);
		mRenderTexture.draw(rect);
		mRenderTexture.display();
	}
	
	return hasUserValue;
}

void Slider::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(mFinalSprite);
}
