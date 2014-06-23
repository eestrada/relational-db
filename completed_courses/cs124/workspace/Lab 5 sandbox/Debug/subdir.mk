################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../lnk_msp430f2274.cmd 

ASM_SRCS += \
../lab5_0.asm \
../lab5_1.asm \
../lab5_2.asm \
../lab5_3.asm \
../morse.asm 

ASM_DEPS += \
./lab5_0.pp \
./lab5_1.pp \
./lab5_2.pp \
./lab5_3.pp \
./morse.pp 

OBJS += \
./lab5_0.obj \
./lab5_1.obj \
./lab5_2.obj \
./lab5_3.obj \
./morse.obj 

OBJS_QUOTED += \
"./lab5_0.obj" \
"./lab5_1.obj" \
"./lab5_2.obj" \
"./lab5_3.obj" \
"./morse.obj" 


# Each subdirectory must supply rules for building sources it contributes
lab5_0.obj: ../lab5_0.asm $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler v3.0'
	"C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/bin/cl430" $(GEN_OPTS_QUOTED) --fp_reassoc=off --include_path="C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/include" --sat_reassoc=off --symdebug:dwarf --plain_char=unsigned --silicon_version=msp --printf_support=full --preproc_with_compile --preproc_dependency="lab5_0.pp" $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

lab5_1.obj: ../lab5_1.asm $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler v3.0'
	"C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/bin/cl430" $(GEN_OPTS_QUOTED) --fp_reassoc=off --include_path="C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/include" --sat_reassoc=off --symdebug:dwarf --plain_char=unsigned --silicon_version=msp --printf_support=full --preproc_with_compile --preproc_dependency="lab5_1.pp" $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

lab5_2.obj: ../lab5_2.asm $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler v3.0'
	"C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/bin/cl430" $(GEN_OPTS_QUOTED) --fp_reassoc=off --include_path="C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/include" --sat_reassoc=off --symdebug:dwarf --plain_char=unsigned --silicon_version=msp --printf_support=full --preproc_with_compile --preproc_dependency="lab5_2.pp" $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

lab5_3.obj: ../lab5_3.asm $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler v3.0'
	"C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/bin/cl430" $(GEN_OPTS_QUOTED) --fp_reassoc=off --include_path="C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/include" --sat_reassoc=off --symdebug:dwarf --plain_char=unsigned --silicon_version=msp --printf_support=full --preproc_with_compile --preproc_dependency="lab5_3.pp" $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

morse.obj: ../morse.asm $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler v3.0'
	"C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/bin/cl430" $(GEN_OPTS_QUOTED) --fp_reassoc=off --include_path="C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/include" --sat_reassoc=off --symdebug:dwarf --plain_char=unsigned --silicon_version=msp --printf_support=full --preproc_with_compile --preproc_dependency="morse.pp" $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


