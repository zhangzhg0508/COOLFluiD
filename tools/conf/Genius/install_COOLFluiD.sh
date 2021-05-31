# Updated procedure 2018-07-03
# The same CoolFluid_VSC.conf should be used

if [ -z "$1" ] ; then
    echo '"Please choose and run one of the following options:"'
    echo '"./install_COOLFluiD.sh DEBUG_CUDA $2 (with debugging, development version with CUDA)"'
    echo '"./install_COOLFluiD.sh OPTIM_CUDA $2 (w/o debugging, production version with CUDA)"'
    echo '"./install_COOLFluiD.sh DEBUG_NOCUDA $2 (with debugging, development version w/o CUDA)"'
    echo '"./install_COOLFluiD.sh OPTIM_NOCUDA $2 (w/o debugging, production version w/o CUDA)"'
    echo '"where $2 is either --download=0 (update) or --download=1 (update,configure) or --download=2 (download,update,configure)"' 
    exit 1 
fi

if [ -z "$2" ] ; then
    echo '"Please choose and run one of the following options:"'
    echo '"./install_COOLFluiD.sh DEBUG_CUDA $2 (with debugging, development version with CUDA)"'
    echo '"./install_COOLFluiD.sh OPTIM_CUDA $2 (w/o debugging, production version with CUDA)"'
    echo '"./install_COOLFluiD.sh DEBUG_NOCUDA $2 (with debugging, development version w/o CUDA)"'
    echo '"./install_COOLFluiD.sh OPTIM_NOCUDA $2 (w/o debugging, production version w/o CUDA)"'
    echo '"where $2 is either --download=0 (update) or --download=1 (update,configure) or --download=2 (download,update,configure)"' 
    exit 1
fi

module load CMake/3.10.2-GCCcore-6.4.0
module load paralution/1.1.0-foss-2018a
module load Boost/1.66.0-foss-2018a
module load ParMETIS/4.0.3-foss-2018a

export TOP_DIR="${VSC_DATA}"
export COOLFLUID_TOP_DIR="${TOP_DIR}/COOLFluiD_Genius"
# download COOLFluiD
if [ "$2" == "--download=2" ] ; then
svn co https://github.com/andrealani/COOLFluiD/trunk ${COOLFLUID_TOP_DIR}
elif [ "$2" == "--download=0" ] || [ "$2" == "--download=1" ] ; then
#update COOLFluiD
cd ${COOLFLUID_TOP_DIR} 
svn up .
fi

if [ "$1" == "DEBUG_CUDA" ] ; then
# with debugging
export BUILD_MODE=geniuscuda
export CONF_FILE="COOLFluid_Genius_debug.conf"
module load PETSc/3.9.0-foss-2018a-debug
elif [ "$1" == "OPTIM_CUDA" ] ; then
# w/o debugging (production mode)
export BUILD_MODE=geniuscudafast
export CONF_FILE="COOLFluid_Genius_optim.conf"
module load PETSc/3.9.0-foss-2018a-CUDA
elif [ "$1" == "DEBUG_NOCUDA" ] ; then
# w/o debugging (production mode)
export BUILD_MODE=optim
export CONF_FILE="COOLFluid_Genius_nocuda.conf"
module load PETSc/3.9.0-foss-2018a-cpu
elif [ "$1" == "OPTIM_NOCUDA" ] ; then
# w/o debugging (production mode)
export BUILD_MODE=release
export CONF_FILE="COOLFluid_Genius_nocuda.conf"
module load PETSc/3.9.0-foss-2018a-cpu
fi

export COOLFLUID_BASEBUILD_DIR="${COOLFLUID_TOP_DIR}/OPENMPI"
export COOLFLUID_CONF_FILE="${COOLFLUID_TOP_DIR}/${CONF_FILE}"
export COOLFLUID_INSTALL_DIR="${COOLFLUID_BASEBUILD_DIR}/${BUILD_MODE}/INSTALL"
export ALL_ACTIVE=1

if [ "$2" == "--download=2" ] ; then
cp ${COOLFLUID_TOP_DIR}/tools/conf/Genius/${CONF_FILE} ${COOLFLUID_TOP_DIR}
cd ${COOLFLUID_TOP_DIR}
./prepare.pl --config-file=${COOLFLUID_CONF_FILE} --build=${BUILD_MODE}
elif [ "$2" == "--download=1" ] ; then
# clean up old object files and libraries
cp ${COOLFLUID_TOP_DIR}/tools/conf/Genius/${CONF_FILE} ${COOLFLUID_TOP_DIR}
rm -fr ${COOLFLUID_BASEBUILD_DIR}/${BUILD_MODE} 
cd ${COOLFLUID_TOP_DIR}
./prepare.pl --config-file=${COOLFLUID_CONF_FILE} --build=${BUILD_MODE}
fi

cd ${COOLFLUID_BASEBUILD_DIR}/${BUILD_MODE}
make -j 4
make install
