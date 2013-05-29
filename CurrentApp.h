#include <Polycode.h>
#include "PolycodeView.h"
#include "Polycode3DPhysics.h"
using namespace Polycode;

class HelloPolycodeApp : public EventHandler {
public:
    HelloPolycodeApp(PolycodeView *view);
    ~HelloPolycodeApp();
    bool Update();
    
private:
	Core *core;
	void HandleEvent(Event *e);
};
