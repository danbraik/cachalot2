#include <iostream>
#include <string>
#include <stdio.h>
#include "MusicPlayer.hpp"
#include "AnimatedLabel.hpp"
#include "Button.hpp"
#include "Slider.hpp"
#include "Label.hpp"

#include <libgen.h>

std::string basename(std::string path) {
	int pos = path.find_last_of('/');
	return path.substr(pos+1);
}


MusicPlayer::MusicPlayer(const std::string & guiTexturePath,
						 const std::string & fontPath)
	: mGuiTexture(),
	  mClock(),
	  mMusic(0),
	  mIsMusicValid(),
	  mOffset(0),
	  mOut_offset(&mOffset),
	  mLabelFont(),
	  mThreadChangeOffset(),
	  mThreadParameter(0),
	  mIsChangingOffset(false),
	  mAnimatedLabel(0),
	  mButtonPlay(0),
	  mButtonPause(0),
	  mSlider(0),
	  mLabel(0)

{
	// Construct GUI
	mGuiTexture.loadFromFile(guiTexturePath);	
	mLabelFont.loadFromFile(fontPath);
	
	mAnimatedLabel = new gui::AnimatedLabel(mLabelFont);
	mAnimatedLabel->setLayout(sf::IntRect(64,0,256-8,64));
	mAnimatedLabel->setString("Loading ...");
	
	mButtonPlay = new gui::Button(mGuiTexture,
						   sf::IntRect(0,0,64,64),
						   sf::IntRect(0,64,64,64),
						   sf::IntRect(0,128,64,64)
						   );
	mButtonPlay->setEnable(false);
	
	mButtonPause = new gui::Button (mGuiTexture,
							sf::IntRect(64,0,64,64),
						    sf::IntRect(64,64,64,64),
						    sf::IntRect(64,128,64,64)
							);
	
	mSlider = new gui::Slider();
	mSlider->setLayout(sf::IntRect(8,64+4,256-16-8,16));	
	mSlider->setEnable(false);
	
	mLabel = new gui::Label(mLabelFont,
							sf::IntRect(256-16+16-8,64-16+4+4,64,16));
	mLabel->setString("...?");
}

sf::Vector2u MusicPlayer::getSize() const
{
	return sf::Vector2u(256+64, 64+16+8+8);
}

bool MusicPlayer::play(const std::string &filepath, float & io_offset)
{
	// Load music
	mMusic = new sf::Music();
	
	mIsMusicValid = mMusic->openFromFile(filepath);
	
	if (!mIsMusicValid) {
		delete mMusic;
		
		mAnimatedLabel->setString(sf::String("Loading music error ! File : " + filepath));
		return false;
	}
	
	float musicDuration = mMusic->getDuration().asSeconds();
	
	// Set playing offset	
	if (io_offset < 0 || io_offset >= musicDuration)
		io_offset = 0;
	
	mOut_offset = &io_offset;
	
	//mMusic.setPlayingOffset(sf::seconds(io_offset));
	
	mSlider->setEnable(true);
	mButtonPlay->setEnable(true);
	
	// Update GUI
	mAnimatedLabel->setString(sf::String( basename(filepath) ));
	mAnimatedLabel->setLoop(true);
	
	// max should be inferior at real duration
	mSlider->setMax(musicDuration - 1);
	mClock.restart();
	
	
	// Play music
	mMusic->play();
	
	changeMusicOffset(io_offset);
	
	return true;
}

void MusicPlayer::toggle()
{
	if (mIsMusicValid && !mIsChangingOffset) {	
		if (mMusic->getStatus() == sf::Music::Playing)
			mMusic->pause();
		else
			mMusic->play();
	}
}




void MusicPlayer::changeMusicOffset(float sliderUserValue) {
	if (!mIsChangingOffset) {
		mIsChangingOffset = true;
		
		mThreadParameter = sliderUserValue;
		
		if (mThreadChangeOffset)
			delete mThreadChangeOffset; // will wait
		
		mThreadChangeOffset = new sf::Thread(&MusicPlayer::innerChangeMusicOffset, this);
		mThreadChangeOffset->launch();
		
		//mThreadChangeOffset->wait();
	}
}

void MusicPlayer::innerChangeMusicOffset() {
	//std::cout << "!!!!!" << std::endl;
	mMusic->setPlayingOffset(sf::seconds(mThreadParameter));
	mIsChangingOffset = false;
}

std::string MusicPlayer::getReadableMusicOffset(const sf::Time & offset) {
	int time_s = static_cast<int>(offset.asSeconds());
	int hours = time_s / 3600;
	time_s -= 3600 * hours;
	int minutes = time_s / 60;
	time_s -= 60 * minutes;
	int seconds = time_s;
	
	
	
	char * c_str = new char[64];
	
	if (hours > 0)
		sprintf(c_str, "%d:%02d:%02d", hours, minutes, seconds);
	else
		sprintf(c_str, "%d:%02d", minutes, seconds);
	
	return std::string(c_str);
}



void MusicPlayer::update(const sf::Vector2f & mousePosition, 
						 bool leftMouseButtonPressed) {
	
	const sf::Time elapsed = mClock.restart();
	
	/// TITLE MUSIC LABEL
	
	mAnimatedLabel->update(elapsed);
	
	/// PLAY BUTTON
	
	if (mButtonPlay->update(mousePosition, leftMouseButtonPressed)) {
		if (mMusic->getStatus() != sf::Music::Playing && !mIsChangingOffset)
			mMusic->play();
	}
	
	/// PAUSE BUTTON
	
	if (mButtonPause->update(mousePosition, leftMouseButtonPressed)) {
		mMusic->pause();
	}
	
	/// MUSIC TIME SLIDER
	
	float sliderUserValue = *mOut_offset = mMusic->getPlayingOffset().asSeconds();
	
	if (mSlider->update(mousePosition, leftMouseButtonPressed, sliderUserValue)) {
		// std::cout << sliderUserValue << std::endl;
		
		changeMusicOffset(sliderUserValue);
	}
	
	if (!mIsChangingOffset)
		mSlider->setValue(sliderUserValue);
	
	
	/// MUSIC TIME LABEL
	
	if (mIsMusicValid)
		mLabel->setString(sf::String(getReadableMusicOffset(
				mMusic->getDuration() - mMusic->getPlayingOffset())));
	
	
	/// OTHER UPDATES
	
	// Binding with music status
	mButtonPlay->setVisible(mMusic->getStatus() != sf::Music::Playing);
	mButtonPause->setVisible(mMusic->getStatus() == sf::Music::Playing);
	if (mIsMusicValid)
		mAnimatedLabel->setLoop(mMusic->getStatus() == sf::Music::Playing);
}

MusicPlayer::~MusicPlayer()
{
	delete mAnimatedLabel;
	delete mButtonPlay;
	delete mButtonPause;
	delete mSlider;
	delete mLabel;
	
	if (mThreadChangeOffset)
		delete mThreadChangeOffset; // will wait
	
	if (mMusic)
		delete mMusic;
}

void MusicPlayer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*mAnimatedLabel);
	target.draw(*mButtonPlay);
	target.draw(*mButtonPause);
	target.draw(*mSlider);	
	target.draw(*mLabel);
}

