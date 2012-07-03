#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Point.o \
	${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Tournee.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Lieu.o \
	${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Requete.o \
	${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Program.o \
	${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Service.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/tp4add

dist/Debug/GNU-Linux-x86/tp4add: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp4add ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Point.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/AAD/tp4/tp4ADD/Point.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Point.o /media/travail/zz2/AAD/tp4/tp4ADD/Point.cpp

${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Tournee.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/AAD/tp4/tp4ADD/Tournee.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Tournee.o /media/travail/zz2/AAD/tp4/tp4ADD/Tournee.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Lieu.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/AAD/tp4/tp4ADD/Lieu.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Lieu.o /media/travail/zz2/AAD/tp4/tp4ADD/Lieu.cpp

${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Requete.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/AAD/tp4/tp4ADD/Requete.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Requete.o /media/travail/zz2/AAD/tp4/tp4ADD/Requete.cpp

${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Program.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/AAD/tp4/tp4ADD/Program.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Program.o /media/travail/zz2/AAD/tp4/tp4ADD/Program.cpp

${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Service.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/AAD/tp4/tp4ADD/Service.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/AAD/tp4/tp4ADD/Service.o /media/travail/zz2/AAD/tp4/tp4ADD/Service.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/tp4add

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
