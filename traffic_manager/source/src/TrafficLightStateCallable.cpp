// Member Defination for Class TrafficLightStateCallable

#include "TrafficLightStateCallable.hpp"

namespace traffic_manager {

    TrafficLightStateCallable::TrafficLightStateCallable(
        SyncQueue<PipelineMessage>* input_queue,
        SyncQueue<PipelineMessage>* output_queue):
        PipelineCallable(input_queue, output_queue, NULL){}

    TrafficLightStateCallable::~TrafficLightStateCallable(){}

    PipelineMessage TrafficLightStateCallable::action(PipelineMessage in_message)
    {
        PipelineMessage out_message;

        float throttle = in_message.getAttribute("throttle");
        float brake = in_message.getAttribute("brake");
        float steer = in_message.getAttribute("steer");

        auto vehicle = boost::static_pointer_cast<carla::client::Vehicle>(in_message.getActor());
        auto traffic_light_state = vehicle->GetTrafficLightState();

        float traffic_hazard = -1;
        if(traffic_light_state == carla::rpc::TrafficLightState::Red
            or traffic_light_state == carla::rpc::TrafficLightState::Yellow)
        {
            traffic_hazard = 1;
        }

        out_message.setActor(in_message.getActor());
        out_message.setAttribute("traffic_light", traffic_hazard);
        out_message.setAttribute("collision", in_message.getAttribute("collision"));
        out_message.setAttribute("velocity", in_message.getAttribute("velocity"));
        out_message.setAttribute("deviation", in_message.getAttribute("deviation"));

        return out_message;
    }
}