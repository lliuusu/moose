[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 5
[]

[MeshModifiers]
  [./left_block]
    type = SubdomainBoundingBox
    block_id = 1
    bottom_left = '0 0 0'
    top_right = '0.5 1 0'
  [../]
  [./right_block]
    type = SubdomainBoundingBox
    block_id = 2
    bottom_left = '0.5 0 0'
    top_right = '1 1 0'
  [../]
[]

[Variables]
  [./var_1]
    block = 1
    initial_condition = 100
  [../]
  [./var_2]
    block = 2
    initial_condition = 200
  [../]
[]

[Problem]
  type = FEProblem
  kernel_coverage_check = true
  solve = false
[]

[Executioner]
  type = Steady
[]

[Postprocessors]
  [./obj]
    type = NodalMaxValue
    variable = var_1
    #block = 1 # this is what being tested, see the test spec
    execute_on = 'initial'
  [../]
[]
