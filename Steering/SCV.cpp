#include "SCV.h"

#include "TypeId.h"
SCV::SCV(AI::AIWorld& world)
    : Agent(world, static_cast<uint32_t>(AgentType::SCV))
{
}

void SCV::Load()
{
    mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
    AI::SeekBehavior* seek = mSteeringModule->AddBehavior<AI::SeekBehavior>();
    seek->SetActive(true);
    seek->ShowDebug(true);

    const float screenWidth = static_cast<float>(X::GetScreenWidth());
    const float screenHeight = static_cast<float>(X::GetScreenHeight());
    destination = { screenWidth * 0.5f, screenHeight * 0.5f };

    for (int i = 0; i < mTextureIds.size(); ++i)
    {
        char name[128];
        sprintf_s(name, "scv_%02i.png", i + 1);
        mTextureIds[i] = X::LoadTexture(name);
    }
}

void SCV::Unload()
{

}

void SCV::Update(float deltaTime)
{

    const X::Math::Vector2 force = mSteeringModule->Calculate();
    const X::Math::Vector2 acceleration = force / mass;
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;

    if (X::Math::MagnitudeSqr(velocity) > 1.0f)
    {
        heading = X::Math::Normalize(velocity);
    }

    const float screenWidth = static_cast<float>(X::GetScreenWidth());
    const float screenHeight = static_cast<float>(X::GetScreenHeight());
    if (position.x < 0.0f)
    {
        position.x += screenWidth;
    }
    if (position.x >= screenWidth)
    {
        position.x -= screenWidth;
    }
    if (position.y < 0.0f)
    {
        position.y += screenHeight;
    }
    if (position.y >= screenHeight)
    {
        position.y -= screenHeight;
    }
}

void SCV::Render()
{
    const float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
    const float percent = angle / X::Math::kTwoPi;
    const int frame = static_cast<int>(percent * mTextureIds.size()) % mTextureIds.size();
    X::DrawSprite(mTextureIds[frame], position);
}

void SCV::ShowDebug(bool debug)
{
}
