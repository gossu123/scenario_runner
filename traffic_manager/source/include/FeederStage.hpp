//Declaration of FeederStage class members 
#include "PipelineStage.hpp"
#include "FeederCallable.hpp"

namespace traffic_manager
{
    class FeederStage: public PipelineStage
    {
    private:
        RegisteredActorMessage* reg_actor;
    public:
        FeederStage();
        ~FeederStage();
        void createPipelineCallables();
    };
}

