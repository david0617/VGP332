#pragma once

#include "Goal.h"
#include "GoalComposite.h"
#include "Strategy.h"

namespace AI
{
    template<class AgentType>
    class DecisionModule
    {
    public:
        using GoalType = Goal<AgentType>;
        using StrategyType = Strategy<AgentType>;

        DecisionModule(AgentType& agent)
            : mAgent(agent)
        {

        }

        template<class NewStrategy>
        NewStrategy* AddStrategy()
        {
            static_assert(std::is_base_of_v<StrategyType, NewStrategy>, "DecisionModule: must be type Strategy");
            auto& newStrategy = mStrategies.emplace_back(std::make_unique<NewStrategy>());
            return static_cast<NewStrategy*>(newStrategy.get());
        }

        void Update()
        {
            // decide what is the best goal at this time
            Arbitrate();
            if (mCurrentGoal != nullptr)
            {
                mCurrentGoal->Process(mAgent);
            }
        }

    private:
        void Arbitrate()
        {
            StrategyType* bestStrategy = nullptr;
            float mostDesirable = 0.0f;

            for (auto& straregy : mStrategies)
            {
                float desirability = straregy->CalculateDesirability(mAgent);
                if (desirability > mostDesirable)
                {
                    mostDesirable = desirability;
                    bestStrategy = straregy.get();
                }
            }
            if (mCurrentStrategy != bestStrategy)
            {
                mCurrentStrategy = bestStrategy;
                if (mCurrentGoal != nullptr)
                {
                    mCurrentGoal->Terminate(mAgent);
                }
                if (mCurrentStrategy != nullptr)
                {
                    mCurrentGoal = mCurrentStrategy->CreateGoal();
                }
            }
        }

        using Strategies = std::vector<std::unique_ptr<StrategyType>>;
        Strategies mStrategies;
        StrategyType* mCurrentStrategy = nullptr;
        std::unique_ptr<GoalType> mCurrentGoal = nullptr;
        AgentType& mAgent;
    };
}