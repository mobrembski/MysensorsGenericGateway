#ifndef BouncerAdaptor_h

#include "Bounce2.h"
#include "Bounce2mcp.h"
class BouncerAdaptor {
    public:
        BouncerAdaptor( int pin ) : normalBouncer( new Bounce() ),
                                    mcpBouncer( NULL )
        {
            normalBouncer->attach( pin );
        }
        BouncerAdaptor( Adafruit_MCP23017 &mcpX, int pin ) : normalBouncer( NULL ),
                                                             mcpBouncer( new BounceMcp() )
        {
            mcpBouncer->attach( mcpX, pin, 10 );
        }
        // Updates the pin
        // Returns 1 if the state changed
        // Returns 0 if the state did not change
        bool update()
        {
            return mcpBouncer != nullptr ? mcpBouncer->update() : normalBouncer->update();
        }

        // Returns the updated pin state
        bool read()
        {
            return mcpBouncer != nullptr ? mcpBouncer->read() : normalBouncer->read();
        }

        // Returns the falling pin state
        bool fell()
        {
            return mcpBouncer != nullptr ? mcpBouncer->fell() : normalBouncer->fell();
        }

        // Returns the rising pin state
        bool rose()
        {
            return mcpBouncer != nullptr ? mcpBouncer->rose() : normalBouncer->rose();
        }

        // Sets the debounce interval
        void interval(uint16_t interval_millis)
        {
            return mcpBouncer != nullptr ? mcpBouncer->interval( interval_millis ) : normalBouncer->interval( interval_millis );
        }
        
    private:
        BouncerAdaptor();
        Bounce* normalBouncer;
        BounceMcp* mcpBouncer;
};
#define BouncerAdaptor_h

#endif /* BouncerAdaptor_h */