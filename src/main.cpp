#include "mutation++.h"

// @Todo: Stronger typing for Eigen::ArrayXd with "using"

int main() {
    // Initialize M++
    Mutation::MixtureOptions opts { "air11" };
    opts.setThermodynamicDatabase("NASA-9");
    opts.setStateModel("ChemNonEq1T");
    Mutation::Mixture mix(opts);
    const int set_state_with_rho_T = 1;

    const int ns = mix.nSpecies();

    // Testing data
    const int n = 10000;
    // T [250, 40250] K and P [1.01325, 101325] approx
    Eigen::ArrayXd T = 20000.*(1.+Eigen::ArrayXd::Random(n)) + 250.;
    const Eigen::ArrayXd P = 0.5*101325.*(1.+Eigen::ArrayXd::Random(n)) + 1.01325;

    // Equilibrium
    Eigen::ArrayXXd rhos = Eigen::ArrayXXd::Zero(ns, n);
    for (int i = 0; i < n; i++) {
        mix.equilibrate(T(i), P(i));
        mix.densities(rhos.col(i).data());
    }

    // Shuffling T so that our compositions are now out of equilibrium
    std::random_shuffle(T.begin(), T.end());

    // Thermodynamic & kinetic properties
    for (int i = 0; i < n; i++) {
        // Setting the state
        mix.setState(rhos.col(i).data(), &T(i), set_state_with_rho_T);

        //
        Eigen::ArrayXd h = Eigen::ArrayXd::Zero(ns*mix.nEnergyEqns());
        mix.getEnthalpiesMass(h.data());

        // Kinetic Properties
        Eigen::ArrayXd wdot = Eigen::ArrayXd::Zero(ns);
        mix.netProductionRates(wdot.data());

        // Transport properties without Stefan-Maxwell
        const double lambda = mix.frozenThermalConductivity(); // Note: There is a more consistent function
        const double lambda_eucken = mix.internalThermalConductivity(T(i)); // Not sure
        const double viscosity = mix.viscosity();

        (void) lambda;
        (void) lambda_eucken;
        (void) viscosity;
    }

    // Computing random species gradients for Stefan-Maxwell
    const double LENGTH = 1.e-2; // Characteristic length scale of our cells
    const Eigen::ArrayXd dx = LENGTH*(1.+Eigen::ArrayXd::Random(n-1));
    // Unnecessary but for mole fractions
    // const Eigen::ArrayXd dTdx = (T.tail(n-1)-T.head(n-1)) / dx;

    for (int i = 0; i < n-1; i++) {

    }

    return 0;
}