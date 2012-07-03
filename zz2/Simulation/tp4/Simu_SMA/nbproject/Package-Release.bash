#!/bin/bash -x

#
# Generated - do not edit!
#

# Macros
TOP=`pwd`
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist
TMPDIR=build/${CND_CONF}/${CND_PLATFORM}/tmp-packaging
TMPDIRNAME=tmp-packaging
OUTPUT_PATH=${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/simu_sma
OUTPUT_BASENAME=simu_sma
PACKAGE_TOP_DIR=SimuSMAESCOURBIACSEPTIER/

# Functions
function checkReturnCode
{
    rc=$?
    if [ $rc != 0 ]
    then
        exit $rc
    fi
}
function makeDirectory
# $1 directory path
# $2 permission (optional)
{
    mkdir -p "$1"
    checkReturnCode
    if [ "$2" != "" ]
    then
      chmod $2 "$1"
      checkReturnCode
    fi
}
function copyFileToTmpDir
# $1 from-file path
# $2 to-file path
# $3 permission
{
    cp "$1" "$2"
    checkReturnCode
    if [ "$3" != "" ]
    then
        chmod $3 "$2"
        checkReturnCode
    fi
}

# Setup
cd "${TOP}"
mkdir -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package
rm -rf ${TMPDIR}
mkdir -p ${TMPDIR}

# Copy files and create directories and links
cd "${TOP}"
makeDirectory ${TMPDIR}/SimuSMAESCOURBIACSEPTIER/bin
copyFileToTmpDir "${OUTPUT_PATH}" "${TMPDIR}/${PACKAGE_TOP_DIR}bin/${OUTPUT_BASENAME}" 0755

cd "${TOP}"
makeDirectory ${TMPDIR}/SimuSMAESCOURBIACSEPTIER/ressources
copyFileToTmpDir "/media/travail/zz2/simulation/tp4/ressources/bell.mp3" "${TMPDIR}/${PACKAGE_TOP_DIR}ressources/bell.mp3" 0644

cd "${TOP}"
makeDirectory ${TMPDIR}/SimuSMAESCOURBIACSEPTIER/ressources
copyFileToTmpDir "/media/travail/zz2/simulation/tp4/ressources/humain.jpg" "${TMPDIR}/${PACKAGE_TOP_DIR}ressources/humain.jpg" 0644

cd "${TOP}"
makeDirectory ${TMPDIR}/SimuSMAESCOURBIACSEPTIER/ressources
copyFileToTmpDir "/media/travail/zz2/simulation/tp4/ressources/knife.jpg" "${TMPDIR}/${PACKAGE_TOP_DIR}ressources/knife.jpg" 0644

cd "${TOP}"
makeDirectory ${TMPDIR}/SimuSMAESCOURBIACSEPTIER/ressources
copyFileToTmpDir "/media/travail/zz2/simulation/tp4/ressources/libfmod.so" "${TMPDIR}/${PACKAGE_TOP_DIR}ressources/libfmod.so" 0755

cd "${TOP}"
makeDirectory ${TMPDIR}/SimuSMAESCOURBIACSEPTIER/ressources
copyFileToTmpDir "/media/travail/zz2/simulation/tp4/ressources/libSDL.so" "${TMPDIR}/${PACKAGE_TOP_DIR}ressources/libSDL.so" 0755

cd "${TOP}"
makeDirectory ${TMPDIR}/SimuSMAESCOURBIACSEPTIER/ressources
copyFileToTmpDir "/media/travail/zz2/simulation/tp4/ressources/libSDL_image.so" "${TMPDIR}/${PACKAGE_TOP_DIR}ressources/libSDL_image.so" 0755

cd "${TOP}"
makeDirectory ${TMPDIR}/SimuSMAESCOURBIACSEPTIER/ressources
copyFileToTmpDir "/media/travail/zz2/simulation/tp4/ressources/zombie.jpg" "${TMPDIR}/${PACKAGE_TOP_DIR}ressources/zombie.jpg" 0644


# Generate tar file
cd "${TOP}"
rm -f ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/SimuSMAESCOURBIACSEPTIER.tar
cd ${TMPDIR}
tar -vcf ../../../../${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/SimuSMAESCOURBIACSEPTIER.tar *
checkReturnCode

# Cleanup
cd "${TOP}"
rm -rf ${TMPDIR}
