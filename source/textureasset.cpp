#include "textureasset.hpp"

TextureAsset::TextureAsset(Vector2 pos, std::string path):raylib::Texture(path)
{
	this->pos = pos;
}

void TextureAsset::Draw()
{
	Texture::Draw(this->pos);
}