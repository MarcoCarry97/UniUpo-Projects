################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../client.o \
../directory_server.o \
../directory_server_functions.o \
../error.o \
../list.o \
../my_io.o \
../my_signal.o \
../mysql.o \
../server.o 

C_SRCS += \
../client.c \
../client_functions.c \
../directory_server.c \
../directory_server_functions.c \
../error.c \
../list.c \
../my_io.c \
../my_signal.c \
../mysql.c \
../server.c 

OBJS += \
./client.o \
./client_functions.o \
./directory_server.o \
./directory_server_functions.o \
./error.o \
./list.o \
./my_io.o \
./my_signal.o \
./mysql.o \
./server.o 

C_DEPS += \
./client.d \
./client_functions.d \
./directory_server.d \
./directory_server_functions.d \
./error.d \
./list.d \
./my_io.d \
./my_signal.d \
./mysql.d \
./server.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


