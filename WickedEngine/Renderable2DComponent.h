#pragma once
#include "RenderableComponent.h"
#include "wiGUI.h"

class wiSprite;
class wiFont;

#define DEFAULT_RENDERLAYER "default"

struct LayeredRenderEntity
{
	enum TYPE
	{
		SPRITE,
		FONT,
	} type;
	wiSprite* sprite;
	wiFont* font;
	int order;

	LayeredRenderEntity()
	{
		type = SPRITE;
		sprite = nullptr;
		font = nullptr;
		order = 0;
	}
};
struct RenderLayer
{
	std::vector<LayeredRenderEntity> entities;
	std::string name;
	int order;

	RenderLayer(const std::string& newName)
	{
		name = newName;
		order = 0;
	}
};

class Renderable2DComponent :
	public RenderableComponent
{
private:
	float m_spriteSpeed;
	static wiRenderTarget rtFinal;
	wiGUI GUI;

protected:
	virtual void ResizeBuffers();
public:
	Renderable2DComponent();
	virtual ~Renderable2DComponent();

	virtual void Initialize();
	virtual void Load();
	virtual void Unload();
	virtual void Start();
	virtual void Update(float dt);
	virtual void FixedUpdate();
	virtual void Render();
	virtual void Compose();

	void addSprite(wiSprite* sprite, const std::string& layer = DEFAULT_RENDERLAYER);
	void removeSprite(wiSprite* sprite);
	void clearSprites();
	void setSpriteSpeed(float value){ m_spriteSpeed = value; }
	float getSpriteSpeed(){ return m_spriteSpeed; }
	int getSpriteOrder(wiSprite* sprite);

	void addFont(wiFont* font, const std::string& layer = DEFAULT_RENDERLAYER);
	void removeFont(wiFont* font);
	void clearFonts();
	int getFontOrder(wiFont* font);

	std::vector<RenderLayer> layers;
	void addLayer(const std::string& name);
	void setLayerOrder(const std::string& name, int order);
	void SetSpriteOrder(wiSprite* sprite, int order);
	void SetFontOrder(wiFont* font, int order);
	void SortLayers();
	void CleanLayers();

	wiGUI& GetGUI() { return GUI; }
};

