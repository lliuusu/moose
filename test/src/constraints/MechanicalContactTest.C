//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MechanicalContactTest.h"

registerADMooseObject("MooseTestApp", MechanicalContactTest);

defineADValidParams(MechanicalContactTest,
                    ADMortarConstraint,

                    MooseEnum component("x=0 y=1 z=2");
                    params.addRequiredParam<MooseEnum>(
                        "component",
                        component,
                        "The force component constraint that this object is supplying"););

template <ComputeStage compute_stage>
MechanicalContactTest<compute_stage>::MechanicalContactTest(const InputParameters & parameters)
  : ADMortarConstraint<compute_stage>(parameters), _component(adGetParam<MooseEnum>("component"))
{
}

template <ComputeStage compute_stage>
ADReal
MechanicalContactTest<compute_stage>::computeQpResidual(Moose::MortarType type)
{
  switch (type)
  {
    case Moose::MortarType::Slave:
      // If normals is positive, then this residual is positive, indicating that we have an outflow
      // of momentum, which in turn indicates that the momentum will tend to decrease at this
      // location with time, which is what we want because the force vector is in the negative
      // direction (always opposite of the normals). Conversely, if the normals is negative, then
      // this residual is negative, indicating that we have an inflow of momentum, which in turn
      // indicates the momentum will tend to increase at this location with time, which is what we
      // want because the force vector is in the positive direction (always opposite of the
      // normals).
      return _test_slave[_i][_qp] * _lambda[_qp] * _normals[_qp](_component);

    case Moose::MortarType::Master:
      // The normal vector is signed according to the slave face, so we need to introduce a negative
      // sign here
      return -_test_master[_i][_qp] * _lambda[_qp] * _normals[_qp](_component);

    default:
      return 0;
  }
}
