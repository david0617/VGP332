#pragma once

#include <AI.h>

class VisualSensor;

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
    void SetSeparation(bool active);
    void SetAlignment(bool active);
    void SetCohesion(bool active);

    void SetSeekWeight(float weight);
    void SetSeparationWeight(float weight);
    void SetAlignmentWeight(float weight);
    void SetCohesionWeight(float weight);

private:
    std::unique_ptr<AI::PerceptionModule> mPerceptionModule;
    std::unique_ptr<AI::SteeringModule> mSteeringModule;
    AI::SeekBehavior* mSeekBehavior = nullptr;

    AI::SeparationBehavior* mSeparationBehavior = nullptr;
    AI::AlignmentBehavior* mAlignmentBehavior = nullptr;
    AI::CohesionBehavior* mCohesionBehavior = nullptr;
    VisualSensor* mVisualSensor = nullptr;

    std::array<X::TextureId, 16> mTextureIds;
};