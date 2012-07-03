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
	${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/zombie.o \
	${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/world.o \
	${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/position.o \
	${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/agent.o \
	${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/graphic.o \
	${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/mt19937ar.o \
	${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/entite.o \
	${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/simulator.o \
	${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/main.o \
	${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/arme.o \
	${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/humain.o

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
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/simu_sma

dist/Debug/GNU-Linux-x86/simu_sma: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -lpthread -lSDLmain -lSDL -lfmod -lSDL_image -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/simu_sma ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/zombie.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/simulation/tp4/Simu_SMA/zombie.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/zombie.o /media/travail/zz2/simulation/tp4/Simu_SMA/zombie.cpp

${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/world.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/simulation/tp4/Simu_SMA/world.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/world.o /media/travail/zz2/simulation/tp4/Simu_SMA/world.cpp

${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/position.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/simulation/tp4/Simu_SMA/position.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/position.o /media/travail/zz2/simulation/tp4/Simu_SMA/position.cpp

${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/agent.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/simulation/tp4/Simu_SMA/agent.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/agent.o /media/travail/zz2/simulation/tp4/Simu_SMA/agent.cpp

${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/graphic.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/simulation/tp4/Simu_SMA/graphic.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/graphic.o /media/travail/zz2/simulation/tp4/Simu_SMA/graphic.cpp

${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/mt19937ar.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/simulation/tp4/Simu_SMA/mt19937ar.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/mt19937ar.o /media/travail/zz2/simulation/tp4/Simu_SMA/mt19937ar.cpp

${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/entite.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/simulation/tp4/Simu_SMA/entite.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/entite.o /media/travail/zz2/simulation/tp4/Simu_SMA/entite.cpp

${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/simulator.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/simulation/tp4/Simu_SMA/simulator.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/simulator.o /media/travail/zz2/simulation/tp4/Simu_SMA/simulator.cpp

${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/main.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/simulation/tp4/Simu_SMA/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/main.o /media/travail/zz2/simulation/tp4/Simu_SMA/main.cpp

${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/arme.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/simulation/tp4/Simu_SMA/arme.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/arme.o /media/travail/zz2/simulation/tp4/Simu_SMA/arme.cpp

${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/humain.o: nbproject/Makefile-${CND_CONF}.mk /media/travail/zz2/simulation/tp4/Simu_SMA/humain.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/media/travail/zz2/simulation/tp4/Simu_SMA/humain.o /media/travail/zz2/simulation/tp4/Simu_SMA/humain.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/simu_sma

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
