/*
CCP PETMR Synergistic Image Reconstruction Framework (SIRF)
Copyright 2015 - 2017 Rutherford Appleton Laboratory STFC

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

/*!
\file
\ingroup Registration
\brief Resampling class based on nifty resample

If multiple transformations are set, they will be used in the order that they have been added.
i.e., Trans3(Trans2(Trans1(x))).

\author Richard Brown
\author CCP PETMR
*/

#ifndef _SIRFREGNIFTYRESAMPLE_H_
#define _SIRFREGNIFTYRESAMPLE_H_

#include <nifti1_io.h>
#include <string>
#include <vector>
#include <iostream>
#include "NiftiImageData3D.h"
#include "NiftiImageData3DTensor.h"
#include "SIRFRegTransformation.h"
#include "SIRFRegResample.h"

namespace sirf {

// Forward declarations
template<class dataType> class NiftiImageData3DDisplacement;
template<class dataType> class SIRFRegAffineTransformation;

/// Wrapper around NiftyReg's resample class
template<class dataType>
class SIRFRegNiftyResample : public SIRFRegResample<dataType>
{
public:

    /// Constructor
    SIRFRegNiftyResample() {}

    /// Destructor
    virtual ~SIRFRegNiftyResample() {}

    /// Process
    virtual void process();

protected:

    /// Set up the input images (convert from ImageData to NiftiImageData3D if necessary)
    void set_up_input_images();

    /// Set up the output image
    void set_up_output_image();

    /// Reference image as a NiftyImageData3D
    std::shared_ptr<const NiftiImageData3D<float> > _reference_image_nifti_sptr;
    /// Floating image as a NiftyImageData3D
    std::shared_ptr<const NiftiImageData3D<float> > _floating_image_nifti_sptr;
    /// Floating image as a NiftyImageData3D
    std::shared_ptr<NiftiImageData3D<float> >       _output_image_nifti_sptr;
};
}

#endif
