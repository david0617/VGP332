#pragma once

#include <AI.h>

class SCV : public AI::Agent
{
public:
    SCV(AI::AIWorld& world);
    ~SCV() override = default;

    void Load();
    void Unload();

    void Update(float deltaTime);
    void Render();

    void ShowDebug(bool debug);

    void SetSeek(bool active);
    void SetFlee(bool active);
    void SetArrive(bool active);
    void SetWander(bool active);
    void SetPursuit(bool active);
    void SetEvade(bool active);
    void SetSeparation(bool active);
    void SetAlignment(bool active);
    void SetCohesion(bool active);

    void SetSeekWeight(float weight);
    void SetFleeWeight(float weight);
    void SetArriveWeight(float weight);
    void SetWanderWeight(float weight);
    void SetPursuitWeight(float weight);
    void SetEvadeWeight(float weight);
    void SetSeparationWeight(float weight);
    void SetAlignmentWeight(float weight);
    void SetCohesionWeight(float weight);

private:
    std::unique_ptr<AI::SteeringModule> mSteeringModule;
    AI::SeekBehavior* mSeekBehavior = nullptr;
    AI::FleeBehavior* mFleeBehavior = nullptr;
    AI::ArriveBehavior* mArriveBehavior = nullptr;
    AI::WanderBehavior* mWanderBehavior = nullptr;
    AI::PursuitBehavior* mPursuitBehavior = nullptr;
    AI::EvadeBehavior* mEvadeBehavior = nullptr;
    AI::SeparationBehavior* mSeparationBehavior = nullptr;
    AI::AlignmentBehavior* mAlignmentBehavior = nullptr;
    AI::CohesionBehavior* mCohesionBehavior = nullptr;

    std::array<X::TextureId, 16> mTextureIds;
};