#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace gui {
	class AnimatedLabel;
	class Button;
	class Slider;
	class Label;
}

class MusicPlayer : public sf::Drawable
{
	public:
		MusicPlayer(const std::string & guiTexturePath,
					const std::string & fontPath);
		sf::Vector2u getSize() const;
		// io_offset will contain last music time
		bool play(const std::string & filepath, float & io_offset);
		// pause or resume music
		void toggle();
		void update(const sf::Vector2f & mousePosition, 
					bool leftMouseButtonPressed);
		
		~MusicPlayer();
	
	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void changeMusicOffset(float value);
		void innerChangeMusicOffset();
		std::string getReadableMusicOffset(const sf::Time & offset);
		
		sf::Texture mGuiTexture;
		
		sf::Clock mClock;	
		sf::Music * mMusic;
		bool mIsMusicValid;
		float mOffset;
		float * mOut_offset;
		sf::Font mLabelFont;
		
		sf::Thread * mThreadChangeOffset;
		float mThreadParameter;
		bool mIsChangingOffset;
		
		gui::AnimatedLabel * mAnimatedLabel;
		gui::Button * mButtonPlay;
		gui::Button * mButtonPause;
		gui::Slider * mSlider;
		gui::Label * mLabel;
		
};

#endif // MUSICPLAYER_HPP
