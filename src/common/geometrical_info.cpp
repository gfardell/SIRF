/*
  CCP PETMR Synergistic Image Reconstruction Framework (SIRF)
  Copyright 2018 Commonwealth Scientific and Industrial Research Organisation's
  Australian eHealth Research Organisation

  This is software developed for the Collaborative Computational
  Project in Positron Emission Tomography and Magnetic Resonance imaging
  (http://www.ccppetmr.ac.uk/).

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at
  http://www.apache.org/licenses/LICENSE-2.0
  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include <string>
#include "SIRF/common/geometrical_info.h"

template <int num_dimensions>
VoxelisedGeometricalInfo<num_dimensions>::
VoxelisedGeometricalInfo(
	const Offset& offset, const Spacing& spacing,
	const Size& size, const Direction& direction)
	:
	offset (offset),
	spacing (spacing),
	size (size),
	direction (direction)
{}

template <int num_dimensions>
const typename VoxelisedGeometricalInfo<num_dimensions>::Offset
VoxelisedGeometricalInfo<num_dimensions>::get_offset()
{
	return offset;
}

template <int num_dimensions>
const typename VoxelisedGeometricalInfo<num_dimensions>::Spacing
VoxelisedGeometricalInfo<num_dimensions>::get_spacing()
{
	return spacing;
}

template <int num_dimensions>
const typename VoxelisedGeometricalInfo<num_dimensions>::Size
VoxelisedGeometricalInfo<num_dimensions>::get_size()
{
	return size;
}

template <int num_dimensions>
const typename VoxelisedGeometricalInfo<num_dimensions>::Direction
VoxelisedGeometricalInfo<num_dimensions>::get_direction()
{
	return direction;
}
