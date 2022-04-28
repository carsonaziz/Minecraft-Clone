#include "layer.h"

#include "core/log.h"
#include "core/events/key_event.h"

namespace Minecraft
{
    class GameLayer : public Layer
    {
    public:
        GameLayer() : Layer() {}

        virtual void on_event(Event& event) override
        {
            EventHandler handler(event);
            handler.handle_event<KeyPressedEvent>(std::bind(&GameLayer::test, this, std::placeholders::_1));
        }

        virtual void render() override {}
        virtual void update() override {}

        bool test(Event& event)
        {
            MC_LOG_WARN("{}, in game", event.to_string());

            return true;
        }
    };
}