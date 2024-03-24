#pragma once

namespace AI
{
    template<class AgentType>
    class Goal
    {
    public:
        enum class Status
        {
            Inactive,
            Active,
            Completed,
            Failed
        };

        Goal() = default;
        virtual ~Goal() = default;

        virtual void Activate(AgentType& agent) = 0;
        virtual Status Process(AgentType& agent) = 0;
        virtual void Terminate(AgentType& agent) = 0;

        Status GetStatus() const { return mStatus; }

    protected:
        void ActivateIfInactive(AgentType& agentType)
        {
            if (mStatus == Status::Inactive)
            {
                Activate(agentType);
            }
        }

        void ReactiveIfFailed(AgentType& agent)
        {
            if (mStatus == Status::Failed)
            {
                Activate(agent);
            }
        }

        Status mStatus = Status::Inactive;

    };
}