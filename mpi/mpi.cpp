#include <iostream>
#include <string>

#include <boost/mpi/collectives/all_reduce.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/inplace.hpp>
#include <mpi.h>


struct TwoIntStruct {
    int a;
    int b;
    // error: no match for ‘operator+’ (operand types are ‘const TwoIntStruct’ and ‘const
    // TwoIntStruct’) thus needs const const
    TwoIntStruct operator+(const TwoIntStruct other) const { return {a + other.a, b + other.b}; };
    template <typename TArchive> void serialize(TArchive& ar, const unsigned int version) {
        ar & a;
        ar & b;
    }
};

namespace boost::mpi {
template <> struct is_mpi_datatype<TwoIntStruct> : public mpl::true_ {};
}  // namespace boost::mpi

int main() {
    boost::mpi::environment env;
    boost::mpi::communicator world;
    std::vector<TwoIntStruct> testStructVec(3, {1, 2});

    std::cout << "I am process " << world.rank() << " of " << world.size() << "." << std::endl;

    boost::mpi::all_reduce(world, boost::mpi::inplace_t<TwoIntStruct*>(testStructVec.data()),
                           static_cast<int>(testStructVec.size()), std::plus<TwoIntStruct>());

    if (world.rank() == 0) {
        std::string msg = "";
        for (auto val : testStructVec) {
            msg += std::to_string(val.a) + ":" + std::to_string(val.b) + "|";
        }
        std::cout << msg << '\n';
    }

    return 0;
}
