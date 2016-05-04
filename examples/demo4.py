import os
import pylab
import sys
import time

BUILD_PATH = os.environ.get('BUILD_PATH') + '/xGadgetron'
SRC_PATH = os.environ.get('SRC_PATH') + '/xGadgetron/pGadgetron'

sys.path.append(BUILD_PATH)
sys.path.append(SRC_PATH)

from pGadgetron import *

try:
    # acquisitions will be read from this HDF file
    input_data = MR_Acquisitions('testdata.h5')
    
    # define gadgets
    gadget1 = Gadget('RemoveROOversamplingGadget')
    gadget2 = Gadget('SimpleReconGadgetSet')
    gadget3 = Gadget('ExtractGadget')

    gadget2.set_property('trigger_dimension', 'repetition')
    gadget2.set_property('split_slices', 'true')

    # create reconstruction object
    recon = ImagesReconstructor()

    # build reconstruction chain
    recon.add_gadget('g1', gadget1)
    recon.add_gadget('g2', gadget2)

    # connect to input data
    recon.set_input(input_data)
    # perform reconstruction
    recon.process()

    # get reconstructed images
    imgs = recon.get_output()

    # build image post-processing chain
    proc = ImagesProcessor()
    proc.add_gadget('g3', gadget3)

    # post-process reconstructed images
    images = proc.process(imgs)

    # plot obtained images
    for i in range(images.number()):
        data = images.image_as_array(i)
        pylab.figure(i + 1)
        pylab.imshow(data[0,0,:,:])
        print('Close Figure %d window to continue...' % (i + 1))
        pylab.show()

except error as err:
    # display error information
    print ('Gadgetron exception occured:\n', err.value)
