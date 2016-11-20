################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Arbol.cpp \
../Disco.cpp \
../Nodo.cpp \
../Terminal.cpp \
../main.cpp 

OBJS += \
./Arbol.o \
./Disco.o \
./Nodo.o \
./Terminal.o \
./main.o 

CPP_DEPS += \
./Arbol.d \
./Disco.d \
./Nodo.d \
./Terminal.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


