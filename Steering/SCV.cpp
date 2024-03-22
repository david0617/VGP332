#include "SCV.h"

#include "TypeId.h"

extern float wanderJitter;
extern float wanderRadius;
extern float wanderDistance;

SCV::SCV(AI::AIWorld& world)
    : Agent(world, static_cast<uint32_t>(AgentType::SCV))
{
}

void SCV::Load()
{
    mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
    mSeekBehavior = mSteeringModule->AddBehavior<AI::SeekBehavior>();
    mFleeBehavior = mSteeringModule->AddBehavior<AI::FleeBehavior>();
    mArriveBehavior = mSteeringModule->AddBehavior<AI::ArriveBehavior>();
    mWanderBehavior = mSteeringModule->AddBehavior<AI::WanderBehavior>();
    mPursuitBehavior = mSteeringModule->AddBehavior<AI::PursuitBehavior>();
    mEvadeBehavior = mSteeringModule->AddBehavior<AI::EvadeBehavior>();
    mSeparationBehavior = mSteeringModule->AddBehavior<AI::SeparationBehavior>();
    mAlignmentBehavior= mSteeringModule->AddBehavior<AI::AlignmentBehavior>();
    mCohesionBehavior= mSteeringModule->AddBehavior<AI::CohesionBehavior>();

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
    if (mWanderBehavior != nullptr)
    {
        mWanderBehavior->Setup(wanderRadius, wanderDistance, wanderJitter);
    }

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
    mSeekBehavior->ShowDebug(debug);
    mFleeBehavior->ShowDebug(debug);
    mArriveBehavior->ShowDebug(debug);
    mWanderBehavior->ShowDebug(debug);
    mPursuitBehavior->ShowDebug(debug);
    mEvadeBehavior->ShowDebug(debug);
    mSeparationBehavior->ShowDebug(debug);
    mAlignmentBehavior->ShowDebug(debug);
    mCohesionBehavior->ShowDebug(debug);
}

void SCV::SetSeek(bool active)
{
    mSeekBehavior->SetActive(active);
}

void SCV::SetFlee(bool active)
{
    mFleeBehavior->SetActive(active);
}

void SCV::SetArrive(bool active)
{
    mArriveBehavior->SetActive(active);
}

void SCV::SetWander(bool active)
{
    mWanderBehavior->SetActive(active);
}

void SCV::SetPursuit(bool active)
{
    mPursuitBehavior->SetActive(active);
}

void SCV::SetEvade(bool active)
{
    mEvadeBehavior->SetActive(active);
}

void SCV::SetSeparation(bool active)
{
    mSeparationBehavior->SetActive(active);
}

void SCV::SetAlignment(bool active)
{
    mAlignmentBehavior->SetActive(active);
}
void SCV::SetCohesion(bool active)
{
    mCohesionBehavior->SetActive(active);
}

void SCV::SetSeekWeight(float weight)
{
    mSeekBehavior->SetWeight(weight);
}

void SCV::SetFleeWeight(float weight)
{
    mFleeBehavior->SetWeight(weight);
}

void SCV::SetArriveWeight(float weight)
{
    mArriveBehavior->SetWeight(weight);
}

void SCV::SetWanderWeight(float weight)
{
    mWanderBehavior->SetWeight(weight);
}

void SCV::SetPursuitWeight(float weight)
{
    mPursuitBehavior->SetWeight(weight);
}

void SCV::SetEvadeWeight(float weight)
{
    mEvadeBehavior->SetWeight(weight);
}

void SCV::SetSeparationWeight(float weight)
{
    mSeparationBehavior->SetWeight(weight);
}

void SCV::SetAlignmentWeight(float weight)
{
    mAlignmentBehavior->SetWeight(weight);
}

void SCV::SetCohesionWeight(float weight)
{
    mCohesionBehavior->SetWeight(weight);
}
