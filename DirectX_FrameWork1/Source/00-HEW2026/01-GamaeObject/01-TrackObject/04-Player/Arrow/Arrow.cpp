#include "Arrow.h"
#include "../../../../../99-Lib/01-MyLib/07-Component/02-Renderer/01-SpriteRenderer/SpriteRenderer.h"

Arrow::Arrow()
{
}

Arrow::~Arrow()
{
}

void Arrow::Init()
{
    p_transform->position.z = -3.0f;

    p_transform->scale = { 100.0f, 100.0f, 1.0f };

    auto renderer = GetComponent<SpriteRenderer>();
    renderer->LoadTexture("Assets/01-Texture/02-Player/Arrow.png");

    renderer->SetIsActive(false);
}

void Arrow::Init(float _scaleRatio)
{
    scaleRatio = _scaleRatio;

    p_transform->position.z = -3.0f;

    // ”ä—¦‚ðŠ|‚¯‚é
    p_transform->scale = { 100.0f * scaleRatio, 100.0f * scaleRatio, 1.0f };

    auto renderer = GetComponent<SpriteRenderer>();
    renderer->LoadTexture("Assets/01-Texture/02-Player/Arrow.png");

    renderer->SetIsActive(false);
}

void Arrow::UpdateTransform(const hft::HFFLOAT2& _pos, float _angle, float _ratio)
{
    auto renderer = GetComponent<SpriteRenderer>();
    if (!renderer->GetIsActive()) {
        renderer->SetIsActive(true);
    }

    Transform* pTrf = GetTransformPtr();

    // ˆÊ’u‚Æ‰ñ“]‚ÌXV
    pTrf->position.x = _pos.x;
    pTrf->position.y = _pos.y;

    pTrf->rotation.z = _angle - 180.f; //‰æ‘œ‚ÉŠî‚Ã‚«¶‰E”½“] -180

    // ƒpƒ[‚É‰ž‚¶‚½Lk
    // _ratio (0.0`1.0) ‚É‰ž‚¶‚ÄA’·‚³‚ð•Ï‚¦‚é
    float scaleVal = 0.5f + _ratio; // Å¬0.5”{ ` Å‘å1.5”{

    pTrf->scale = { 100.0f * scaleVal * scaleRatio, 50.0f * scaleRatio, 1.0f };
}

void Arrow::Hide()
{
    GetComponent<SpriteRenderer>()->SetIsActive(false);
}