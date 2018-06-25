################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AConfigManager.cpp \
../src/AVideo.cpp \
../src/CDetectObject.cpp \
../src/CDilateErodeObjectDetection.cpp \
../src/CHoughObjectDetection.cpp \
../src/CHoughPObjectDetection.cpp \
../src/CImageWindow.cpp \
../src/CLineSepObjectDetection.cpp \
../src/CObjDetecStreamer.cpp \
../src/CObjDetectConfigManager.cpp \
../src/CRoiObjectDetection.cpp \
../src/CVideoObjDetectStreamer.cpp \
../src/CVideoReader.cpp \
../src/CVideoWriter.cpp \
../src/DetectWhiteLine.cpp 

OBJS += \
./src/AConfigManager.o \
./src/AVideo.o \
./src/CDetectObject.o \
./src/CDilateErodeObjectDetection.o \
./src/CHoughObjectDetection.o \
./src/CHoughPObjectDetection.o \
./src/CImageWindow.o \
./src/CLineSepObjectDetection.o \
./src/CObjDetecStreamer.o \
./src/CObjDetectConfigManager.o \
./src/CRoiObjectDetection.o \
./src/CVideoObjDetectStreamer.o \
./src/CVideoReader.o \
./src/CVideoWriter.o \
./src/DetectWhiteLine.o 

CPP_DEPS += \
./src/AConfigManager.d \
./src/AVideo.d \
./src/CDetectObject.d \
./src/CDilateErodeObjectDetection.d \
./src/CHoughObjectDetection.d \
./src/CHoughPObjectDetection.d \
./src/CImageWindow.d \
./src/CLineSepObjectDetection.d \
./src/CObjDetecStreamer.d \
./src/CObjDetectConfigManager.d \
./src/CRoiObjectDetection.d \
./src/CVideoObjDetectStreamer.d \
./src/CVideoReader.d \
./src/CVideoWriter.d \
./src/DetectWhiteLine.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


