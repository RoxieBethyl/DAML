#!/bin/csh
if( ! $?LD_LIBRARY_PATH ) then
  setenv LD_LIBRARY_PATH /home/s1967975/DAML/Week_7/GeantExample3/HEPmc/build/../install/lib
else
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/home/s1967975/DAML/Week_7/GeantExample3/HEPmc/build/../install/lib
endif
setenv PYTHIA8DATA ${PYTHIA8_HOME}/xmldoc
