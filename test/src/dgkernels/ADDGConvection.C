//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADDGConvection.h"

registerADMooseObject("MooseTestApp", ADDGConvection);

defineADValidParams(ADDGConvection,
                    ADDGKernel,
                    params.addRequiredParam<RealVectorValue>("velocity", "Velocity vector");
                    params.addClassDescription("DG upwinding for the convection"););

template <ComputeStage compute_stage>
ADDGConvection<compute_stage>::ADDGConvection(const InputParameters & parameters)
  : ADDGKernel<compute_stage>(parameters), _velocity(adGetParam<RealVectorValue>("velocity"))
{
}

template <ComputeStage compute_stage>
ADReal
ADDGConvection<compute_stage>::computeQpResidual(Moose::DGResidualType type)
{
  ADReal r = 0;

  Real vdotn = _velocity * _normals[_qp];

  switch (type)
  {
    case Moose::Element:
      if (vdotn >= 0)
        r += vdotn * _u[_qp] * _test[_i][_qp];
      else
        r += vdotn * _u_neighbor[_qp] * _test[_i][_qp];
      break;

    case Moose::Neighbor:
      if (vdotn >= 0)
        r -= vdotn * _u[_qp] * _test_neighbor[_i][_qp];
      else
        r -= vdotn * _u_neighbor[_qp] * _test_neighbor[_i][_qp];
      break;
  }

  return r;
}
