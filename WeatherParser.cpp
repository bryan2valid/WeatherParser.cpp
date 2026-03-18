#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

class WeatherSentinel {
private:
    // Replace "022105" with your actual Parish FIPS code (e.g., 022105 is Tangipahoa)
    std::string homeFipsCode = "022105"; 

    std::map<std::string, std::string> alertLevels = {
        {"TOR", "TORNADO WARNING - RED ALERT"},
        {"SVR", "SEVERE THUNDERSTORM - YELLOW ALERT"},
        {"FFW", "FLASH FLOOD - YELLOW ALERT"}
    };

public:
    void processSignal(std::string rawSignal) {
        // SAME Format: [Preamble]-[Originator]-[Event]-[Location]-[Duration]-[Time]-[ID]
        // Example: ZCZC-WXR-TOR-022105+0015...
        
        std::string eventCode = rawSignal.substr(9, 3);
        std::string signalFips = rawSignal.substr(13, 6);

        std::cout << "Incoming Signal for Location: " << signalFips << std::endl;

        // 1. Check if the alert is for OUR location
        if (signalFips == homeFipsCode || signalFips == "000000") { // 000000 is "All Areas"
            
            // 2. Check if it's an event we care about
            if (alertLevels.count(eventCode)) {
                std::cout << "!!! ALERT FOR YOUR AREA: " << alertLevels[eventCode] << " !!!" << std::endl;
            } else {
                std::cout << "Local event detected (" << eventCode << "), but not in priority list." << std::endl;
            }

        } else {
            std::cout << "Alert ignored. Not for home Parish (" << homeFipsCode << ")." << std::endl;
        }
    }
};

int main() {
    WeatherSentinel sentinel;

    std::cout << "--- Sentinel System Active (Louisiana Parish Filter On) ---" << std::endl;

    // Test 1: An alert for a DIFFERENT parish
    std::string otherParish = "ZCZC-WXR-TOR-022017"; 
    sentinel.processSignal(otherParish);

    // Test 2: An alert for YOUR parish
    std::string homeParish = "ZCZC-WXR-TOR-022105"; 
    sentinel.processSignal(homeParish);

    return 0;
}

