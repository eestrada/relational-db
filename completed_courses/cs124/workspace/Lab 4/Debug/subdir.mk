################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../lnk_msp430f2013.cmd 

ASM_SRCS += \
../lab4Complete.asm 

ASM_DEPS += \
./lab4Complete.pp 

OBJS += \
./lab4Complete.obj 

OBJS_QUOTED += \
"./lab4Complete.obj" 


# Each subdirectory must supply rules for building sources it contributes
lab4Complete.obj: ../lab4Complete.asm $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler v3.0'
	"C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/bin/cl430" $(GEN_OPTS_QUOTED) --fp_reassoc=off --include_path="C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/include" --sat_reassoc=off --symdebug:dwarf --plain_char=unsigned --silicon_version=msp --printf_support=minimal --preproc_with_compile --preproc_dependency="lab4Complete.pp" $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


