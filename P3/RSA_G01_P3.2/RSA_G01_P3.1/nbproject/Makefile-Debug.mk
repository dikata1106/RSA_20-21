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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Libs/iRobot_framework/IRobotConnection.o \
	${OBJECTDIR}/src/Libs/iRobot_framework/IRobotInstructionSet.o \
	${OBJECTDIR}/src/Libs/iRobot_framework/Instruction.o \
	${OBJECTDIR}/src/Libs/iRobot_framework/Serial.o \
	${OBJECTDIR}/src/TestSensors.o


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
LDLIBSOPTIONS=-lwiringPi

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test_irobot_framework

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test_irobot_framework: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/test_irobot_framework ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/Libs/iRobot_framework/IRobotConnection.o: src/Libs/iRobot_framework/IRobotConnection.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Libs/iRobot_framework
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Libs/iRobot_framework/IRobotConnection.o src/Libs/iRobot_framework/IRobotConnection.cpp

${OBJECTDIR}/src/Libs/iRobot_framework/IRobotInstructionSet.o: src/Libs/iRobot_framework/IRobotInstructionSet.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Libs/iRobot_framework
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Libs/iRobot_framework/IRobotInstructionSet.o src/Libs/iRobot_framework/IRobotInstructionSet.cpp

${OBJECTDIR}/src/Libs/iRobot_framework/Instruction.o: src/Libs/iRobot_framework/Instruction.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Libs/iRobot_framework
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Libs/iRobot_framework/Instruction.o src/Libs/iRobot_framework/Instruction.cpp

${OBJECTDIR}/src/Libs/iRobot_framework/Serial.o: src/Libs/iRobot_framework/Serial.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Libs/iRobot_framework
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Libs/iRobot_framework/Serial.o src/Libs/iRobot_framework/Serial.cpp

${OBJECTDIR}/src/TestSensors.o: src/TestSensors.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TestSensors.o src/TestSensors.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
