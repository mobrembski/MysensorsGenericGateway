/*
   BouncerAdaptor.h

   Copyright(c) 2021 Michał Obrembski <michal.o@szerszen.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; If not, see <http://www.gnu.org/licenses/>.
*/

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