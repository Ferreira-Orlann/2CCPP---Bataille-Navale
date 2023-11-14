#include "raylib-cpp.hpp"
#include "asset.hpp"

class TextureAsset : public raylib::Texture, public Asset
{
private:
	Vector2 pos;
public:
	TextureAsset(Vector2 pos, std::string path);
	void Draw();
};