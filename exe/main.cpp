#include "libthinkpad.h"

#include <iostream>
#include <cstring>
#include <zconf.h>

using std::cout;
using std::endl;

using ThinkPad::DisplayManagement::XServer;
using ThinkPad::DisplayManagement::ScreenResources;
using ThinkPad::PowerManagement::ACPIEventHandler;
using ThinkPad::DisplayManagement::Monitor;
using ThinkPad::DisplayManagement::point;
using ThinkPad::PowerManagement::ACPI;
using ThinkPad::PowerManagement::ACPIEvent;
using ThinkPad::Hardware::Dock;
using ThinkPad::Hardware::ThinkLight;
using ThinkPad::Configuration;
using ThinkPad::config_keypair_t;
using ThinkPad::config_section_t;


class Handler : public ACPIEventHandler {

private:

    Dock *dock;
    XServer *server;

public:
    Handler();
    ~Handler();
    void handleEvent(ACPIEvent event);
};

Handler::Handler()
{
    this->dock = new Dock();
}

Handler::~Handler()
{
    delete dock;
}

void Handler::handleEvent(ACPIEvent event) {

    switch (event) {

    case ACPIEvent::POWERBUTTON:
        printf("Power button pressed!\n");
        break;
    case ACPIEvent::DOCKED:
        printf("docking\n");
        break;
    case ACPIEvent::UNDOCKED:
        printf("undocking\n");
        break;
    case ACPIEvent::LID_CLOSED:
        printf("lid closing\n");
        break;
    case ACPIEvent::LID_OPENED:
        printf("lid opening\n");
        break;

    }

}

int main(void) {


    ThinkLight *tl = new ThinkLight();

    if (tl->probe()) {

        if (tl->isOn()) {
            printf("ThinkLight is on!\n");
        } else {
            printf("ThinkLight is off!\n");
        }

    } else{
        printf("probe failed");
    }

    delete tl;


#if 0

    ACPI *acpi = new ACPI();
    Handler *handler = new Handler();

    acpi->setEventHandler(handler);
    acpi->wait();

    delete acpi;
    delete handler;


    XServer *server = XServer::getDefaultXServer();
    ScreenResources *screenResources = new ScreenResources(server);
    vector<Monitor*> *monitors = screenResources->getMonitors();

    Monitor *vga = nullptr;
    Monitor *lvds = nullptr;

    printf("Hello, world!");

    return EXIT_SUCCESS;

    for (Monitor *monitor : *monitors) {

        if (monitor->isConnected() && monitor->getInterfaceName() == "VGA-1")
            vga = monitor;
        if (monitor->isConnected() && monitor->getInterfaceName() == "LVDS-1")
            lvds = monitor;
    }

    if (vga->isOff()) {
        vga->reconfigure();
    }

    if (lvds->isOff()) {
        lvds->reconfigure();
    }

    printf("VGA < -- > LVDS\n");

    vga->setRotation(RR_Rotate_0);
    vga->setMirror(lvds);
    vga->setPrimary(true);
    vga->applyConfiguration();

    usleep(4000000);

    printf("Only VGA\n");

    lvds->turnOff();
    lvds->setRotation(RR_Rotate_0);
    lvds->applyConfiguration();
    vga->setMirror(nullptr);
    vga->setOutputMode(vga->getPreferredOutputMode());
    vga->applyConfiguration();

    usleep(4000000);

    printf("Only LVDS\n");

    vga->turnOff();
    vga->setPrimary(false);
    vga->applyConfiguration();
    lvds->setPrimary(true);
    lvds->setOutputMode(lvds->getPreferredOutputMode());
    lvds->setRotation(RR_Rotate_0);
    lvds->applyConfiguration();

    usleep(4000000);

    printf("VGA -> LVDS\n");

    vga->setOutputMode(vga->getPreferredOutputMode());
    lvds->setOutputMode(lvds->getPreferredOutputMode());
    vga->setPrimary(true);
    vga->setRightMonitor(lvds);
    vga->applyConfiguration();

    usleep(4000000);

    printf("VGA rotated 90\n");

    lvds->turnOff();
    lvds->applyConfiguration();
    vga->setRotation(RR_Rotate_90);
    vga->setPrimary(true);
    vga->setRightMonitor(nullptr);
    vga->applyConfiguration();

    usleep(4000000);


    printf("VGA > LVDS(90)\n");

    vga->setOutputMode(vga->getPreferredOutputMode());
    lvds->setOutputMode(lvds->getPreferredOutputMode());
    lvds->setRotation(RR_Rotate_90);
    vga->setRotation(RR_Rotate_0);
    vga->setRightMonitor(lvds);
    vga->setPrimary(true);
    vga->applyConfiguration();

    usleep(4000000);

    printf("Only VGA\n");

    lvds->turnOff();
    lvds->applyConfiguration();
    vga->setPrimary(true);
    vga->setRotation(RR_Rotate_0);
    vga->setOutputMode(vga->getPreferredOutputMode());
    vga->setRightMonitor(nullptr);
    vga->setMirror(nullptr);
    vga->applyConfiguration();

    delete screenResources;
    delete server;

#endif

    return 0;

}
