#!/bin/sh
if [ ! $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=/home/s1967975/DAML/Week_7/GeantExample3/HEPmc/build/../install/lib
fi
if [ $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/s1967975/DAML/Week_7/GeantExample3/HEPmc/build/../install/lib
fi
export PYTHIA8DATA=${PYTHIA8_HOME}/xmldoc
