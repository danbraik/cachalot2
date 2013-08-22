#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

namespace gui {

	class Button : public sf::Drawable
	{
		public:
			Button(const sf::Texture & texture,
				   const sf::IntRect & texRectNormal,
				   const sf::IntRect & texRectFocused
				   );
			Button(const sf::Texture & texture,
				   const sf::IntRect & texRectNormal,
				   const sf::IntRect & texRectFocused,
				   const sf::IntRect & texRectClicked
				   );
			void setPosition(const sf::Vector2f & position);
			void setVisible(bool visible);
			void setEnable(bool enable);
			bool update(sf::Vector2f mousePosition, bool mouseButtonPressed);
			
		private:
			void draw(sf::RenderTarget &target, sf::RenderStates states) const;
			
			const sf::IntRect mTexRectNormal;
			const sf::IntRect mTexRectFocused;
		    const sf::IntRect mTexRectClicked;
			
			sf::Sprite mSprite;
			bool mOldMouseButtonState;
			bool mIsVisible;
			bool mHasStartedClick;
			bool mEnable;
	};

}

#endif // BUTTON_HPP
