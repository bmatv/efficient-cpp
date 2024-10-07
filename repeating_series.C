#include <algorithm>
#include <iostream>
#include <vector>

struct SearchBoxParms {
    long xSearchSize, ySearchSize, zSearchSize, scaleCoeff;
    [[nodiscard]] auto getXSize() const -> long { return xSearchSize / scaleCoeff; }
    [[nodiscard]] auto getYSize() const -> long { return ySearchSize / scaleCoeff; }
    [[nodiscard]] auto getZSize() const -> long { return zSearchSize; }
    template <typename TArchive> void serialize(TArchive& ar, const unsigned int version) {
        ar & xSearchSize;
        ar & ySearchSize;
        ar & zSearchSize;
        ar & scaleCoeff;
    }
};

int main() {
    auto searchBoxParms = SearchBoxParms{10, 10, 1, 8};
    long radMin = 130;
    long radMax = 160;

    auto zdim = 2;

    std::vector<long> radiiSubSet((radMax - radMin) / searchBoxParms.scaleCoeff + 1, 0);
    std::generate(radiiSubSet.begin(), radiiSubSet.end(), [&, value = 0]() mutable {
        return radMin + searchBoxParms.scaleCoeff * value++;
    });
    // for(auto val: radiiSubSet)
    //     std::cout << val << ", ";
    // std::cout << '\n';

    // std::vector<std::vector<long>> radii(zdim,radiiSubSet); // (zdim, radiiSubSet)
    std::vector<std::vector<long>> radii(zdim);
    // radii.reserve(zdim);
    //
    // could do reserve and then insert but with no init element, could initialize with the elements,
    // rest of ways require init vector with elements, e.g. = short arr, assign
    // can't use swap as subset becomes empty', same with move. Need to create a vec first and then move
    // for the init stage - just init with default being radiiSubSet

    // the vectors for each slice won't be equal in size - the problem is that if radii selected are
    // far enough it will create n*3 new radii but
    for (auto & radsVec : radii) {
        radsVec = radiiSubSet;
        // radsVec = std::move(radiiSubSet);
    }

    for (auto& i : radii) {
        for (auto& val : i) {
            std::cout << val << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "Hello World\n";
}
