#include "application/Application.h"

namespace stinky {
    class StinkyApplication : public Application
    {
    public:
        StinkyApplication();
    };

    Application* CreateApplication();
}
