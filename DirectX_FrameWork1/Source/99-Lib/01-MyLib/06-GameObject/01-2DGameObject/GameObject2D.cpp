#include "GameObject2D.h"


#include "../../07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

void GameObject2D::Init()
{
}

void GameObject2D::Update()
{
}

void GameObject2D::Draw()
{
	if (auto comp = GetComponent<SpriteRenderer>())
		comp->Draw();
}
