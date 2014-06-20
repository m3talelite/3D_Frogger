################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GameObject.cpp \
../src/Main.cpp \
../src/Map.cpp \
../src/ObjectLoader.cpp 

OBJS += \
./src/GameObject.o \
./src/Main.o \
./src/Map.o \
./src/ObjectLoader.o 

CPP_DEPS += \
./src/GameObject.d \
./src/Main.d \
./src/Map.d \
./src/ObjectLoader.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


