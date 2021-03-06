# InterfaceValueUserObjectAux

## Description

InterfaceValueUserObjectAux is an AuxKernel used to collect values stored in a [InterfaceQpValueUserObject](/InterfaceQpValueUserObject.md) and save them into an aux variable at each quadrature point.
It requires three inputs:

* `variable` is the name of the output AuxVariable
* `boundary` = the name of the boundary to which this AuxKernel applies
* `interface_uo_name` = the name of interface UserObject where data are stored

## Example Input File Syntax

listing test/tests/userobjects/interface_user_object/interface_value_user_object_QP.i block=AuxKernels/interface_avg_qp_aux

!syntax description /AuxKernels/InterfaceValueUserObjectAux

!syntax parameters /AuxKernels/InterfaceValueUserObjectAux

!syntax inputs /AuxKernels/InterfaceValueUserObjectAux

!syntax children /AuxKernels/InterfaceValueUserObjectAux

!bibtex bibliography
