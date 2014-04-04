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
CCC=/usr/local/cuda-5.0/bin/nvcc
CXX=/usr/local/cuda-5.0/bin/nvcc
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU_4.7-Linux-x86
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
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/increment_gpu.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/increment

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/increment: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/increment ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/ -I/usr/local/cuda-5.0/include -I/usr/local/cuda-5.0/samples/common/inc -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/increment_gpu.o: nbproject/Makefile-${CND_CONF}.mk increment_gpu.cu 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -I/ -I/usr/local/cuda-5.0/include -I/usr/local/cuda-5.0/samples/common/inc -o ${OBJECTDIR}/increment_gpu.o increment_gpu.cu

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/increment

# Subprojects
.clean-subprojects:
