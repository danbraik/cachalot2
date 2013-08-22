#ifndef ANIMATEDLABEL_HPP
#define ANIMATEDLABEL_HPP

#include <SFML/Graphics.hpp>

namespace gui {

	class AnimatedLabel : public sf::Drawable
	{
		public:
			AnimatedLabel(const sf::Font & font);
			AnimatedLabel(const sf::Font & font,
						  const sf::IntRect & layout);
			void setLayout(const sf::IntRect & layout);
			void setFont(const sf::Font & font);
			void setString(const sf::String & string);
			void setLoop(bool loop);
			void update(const sf::Time & elapsed);
		private:
			void init();
			void innerUpdate();
			void draw(sf::RenderTarget &target, sf::RenderStates states) const;
			
			sf::Sprite mFinalSprite;
			sf::RenderTexture mRenderTexture;
			sf::Text mTextSprite;
			sf::Font mFont;
			float mHorizontalPosition;
			
			// degrade stuff
			sf::VertexArray mDegradeQuad;
			sf::RenderStates mDegradeLeft;
			sf::RenderStates mDegradeRight;
			
			bool mDoLoop;
	};


}

#endif // ANIMATEDLABEL_HPP
