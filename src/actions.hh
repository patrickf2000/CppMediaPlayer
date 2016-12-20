//actions.hh
//The header for the global actions.
#pragma once

class Actions {
public:
    static void open();
    static void setWindowFullscreen();
private:
	static bool maximized;
};
