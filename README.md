# M++ Profiler project

Prototype project with the aim to profile the relevant to CFD
methods of Mutation++ library. Structure and overall layout are to
very fluid. In this first iteration random data are generated in a
range relevant to atmospheric entry conditions and a few functions
are run. The current goal is to check what information the profiler
is giving us and then an in-depth discussion is necessary to set
specific goals.

One goal would be to target specific functions starting in thermodynamics.
Vectorization of loops, as well as micro-optimizations will be performed.
First goal is to document the current status of the library to fix a starting point.
The profiler named (?) will be first run, but a dedicated library profiler
could help documentation.

We are first run the code with:
- Thermodynamic database: NASA-9
- Mixture: air_5
- Chemistry: Park
- State-model: ChemNonEq1T

Functions tested (Better documentation needed):
- equilibrate
- densities
- setState (rho, T)
- getEnthalpies
- netProductionRates
- frozenThermalConductivity
- internalThermalConductivity
- viscosity