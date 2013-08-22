#ifndef LABEL_HPP
#define LABEL_HPP

#include <SFML/Graphics.hpp>

namespace gui {
	
	class Label : public sf::Drawable
	{
		public:
			Label(const sf::Font & font,
				  const sf::IntRect & layout);
			void setLayout(const sf::IntRect & layout);
			void setFont(const sf::Font & font);
			void setString(const sf::String & string);
					
		private:
			void draw(sf::RenderTarget &target, sf::RenderStates states) const;
			
			sf::Font mFont;
			sf::Text mTextSprite;
			sf::IntRect mLayout;
	};
}

#endif // LABEL_HPP
