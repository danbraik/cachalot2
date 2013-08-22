#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <SFML/Graphics.hpp>

namespace gui {
	
	class Slider : public sf::Drawable
	{
		public:
			Slider();
			void setLayout(const sf::IntRect & layout);
			void setMin(float min);
			void setMax(float max);
			void setValue(float value);
			void setEnable(bool enable);
			bool update(sf::Vector2f mousePosition, bool mouseButtonPressed, float & userValue);
			
		private:
			void draw(sf::RenderTarget &target, sf::RenderStates states) const;
			
					
			float mMin;
			float mMax;
			float mValue;
			float mDragValue;
			float mOldDrawingValue;
			
			sf::Sprite mFinalSprite;
			sf::RenderTexture mRenderTexture;
			
			bool mOldMouseState;
			bool mHasStartedDrag;
			
			bool mEnable;
			
			
	};

}
	
#endif // SLIDER_HPP
