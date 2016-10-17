#include "Map.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
#include <cassert>
// unrealistic examples
void access_by_key() {
    cs540::Map<int, long> m;
    m.insert({10, 10});
    m.insert({3, 3});
    m.insert({20, 20});
    m.insert({15, 15});
    
    m.at(10);
    bool thrown = false;
    try {
        m.at(10000);
    } catch (std::out_of_range) {
        thrown = true;
    }
    assert(thrown); // the .at should have thrown an exception
    
    const auto& m_ref = m;
    m_ref.at(10); // const .at
    
    auto iter = m.find(3);
    assert((*iter).second == 3);
    
    auto iter2 = m.find(100000); // not in map, should give iterator to end()
    assert(iter2 == std::end(m));
    
    m[30] = 30; // should default construct
    
    m.erase(10);
    assert(m.find(10) == std::end(m)); // 10 shouldn't be in the map anymore
}

int main() {
//    std::cout << "Enter messages to be translated (CTRL+D to exit)\n";
cs540::Map<int,int> a;
 cs540::Map<int, double> int_double_map {{1, 1.0}, {3, 5.67}, {13, 6.9}};

    // must support copy construction
    cs540::Map<int, double> copy_example{int_double_map};
	cs540::Map<int, double> assign_example;
    // must support copy assignment
    assign_example = copy_example;
    return 0;
}
