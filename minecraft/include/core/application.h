#include <memory>

namespace Minecraft
{
    class Application
    {
    public:
        Application() {}
        ~Application() {}

        static std::unique_ptr<Application> create();

        void run();
    };
}