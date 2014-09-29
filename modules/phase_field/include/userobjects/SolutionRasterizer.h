#ifndef SOLUTIONRASTERIZER_H
#define SOLUTIONRASTERIZER_H

#include "SolutionUserObject.h"

//Forward Declarations
class SolutionRasterizer;

template<>
InputParameters validParams<SolutionRasterizer>();

/**
  * This Userobject is the base class of Userobjects that generate one
  * random number per timestep and quadrature point in a way that the integral
  * over all random numbers is zero. This can be used for a concentration fluctuation
  * kernel such as ConservedLangevinNoise, that keeps the total concenration constant.
  *
  * \see ConservedUniformNoise
  */
class SolutionRasterizer : public SolutionUserObject
{
public:
  SolutionRasterizer(const std::string & name, InputParameters parameters);

  virtual ~SolutionRasterizer() {}

  /// Initialize the System and Mesh objects for the solution being read
  virtual void initialSetup();

protected:
};

#endif //SOLUTIONRASTERIZER_H
