################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DisplayImage.cpp \
../src/EdgeCanny.cpp \
../src/EdgeSobel.cpp \
../src/HistogramEqual.cpp \
../src/HoughLine.cpp \
../src/ImageMoments.cpp \
../src/LaplacianEdge.cpp \
../src/LinearFilter.cpp \
../src/MaskOperations.cpp \
../src/ScanImage.cpp \
../src/Threshold.cpp 

OBJS += \
./src/DisplayImage.o \
./src/EdgeCanny.o \
./src/EdgeSobel.o \
./src/HistogramEqual.o \
./src/HoughLine.o \
./src/ImageMoments.o \
./src/LaplacianEdge.o \
./src/LinearFilter.o \
./src/MaskOperations.o \
./src/ScanImage.o \
./src/Threshold.o 

CPP_DEPS += \
./src/DisplayImage.d \
./src/EdgeCanny.d \
./src/EdgeSobel.d \
./src/HistogramEqual.d \
./src/HoughLine.d \
./src/ImageMoments.d \
./src/LaplacianEdge.d \
./src/LinearFilter.d \
./src/MaskOperations.d \
./src/ScanImage.d \
./src/Threshold.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


