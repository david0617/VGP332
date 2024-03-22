#include "Precompiled.h"
#include "PerceptionModule.h"

using namespace AI;

PerceptionModule::PerceptionModule(Agent& agent, ImportanceCalculator calculator)
    : mAgent(agent)
    , mComputeImportance(calculator)
{
}

void PerceptionModule::Update(float deltaTime)
{
    // update the sensors
    for (auto& sensor : mSensors)
    {
        sensor->Update(mAgent, mMemoryRecords, deltaTime);
    }

    // remove old entries
    mMemoryRecords.erase(
        std::remove_if(
            mMemoryRecords.begin(),
            mMemoryRecords.end(),
            [span = mMemorySpan](const auto& record)
            {
                return record.lastRecordedTime + span < X::GetTime();
            }),
        mMemoryRecords.end());

    // caculate the importance of records
    for (auto& record : mMemoryRecords)
    {
        record.importance = mComputeImportance(mAgent, record);
    }

    // sort by importance
    mMemoryRecords.sort(
        [](const auto& a, const auto& b)
        {
            return a.importance > b.importance;
        });
}
