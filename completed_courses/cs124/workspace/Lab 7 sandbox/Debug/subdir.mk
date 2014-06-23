################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../lnk_msp430f2274.cmd 

C_SRCS += \
../dice.c \
../dicePics.c \
../eZ430X.c \
../lab7_a.c \
../lab7_b.c \
../lab7_c.c 

ASM_SRCS += \
../random.asm 

ASM_DEPS += \
./random.pp 

OBJS += \
./dice.obj \
./dicePics.obj \
./eZ430X.obj \
./lab7_a.obj \
./lab7_b.obj \
./lab7_c.obj \
./random.obj 

C_DEPS += \
./dice.pp \
./dicePics.pp \
./eZ430X.pp \
./lab7_a.pp \
./lab7_b.pp \
./lab7_c.pp 

OBJS_QUOTED += \
"./dice.obj" \
"./dicePics.obj" \
"./eZ430X.obj" \
"./lab7_a.obj" \
"./lab7_b.obj" \
"./lab7_c.obj" \
"./random.obj" 


# Each subdirectory must supply rules for building sources it contributes
dice.obj: ../dice.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler v3.0'
	"C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/bin/cl430" $(GEN_OPTS_QUOTED) --fp_reassoc=off --include_path="C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/include" --sat_reassoc=off --symdebug:dwarf --plain_char=unsigned --silicon_version=msp --printf_support=full --preproc_with_compile --preproc_dependency="dice.pp" $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

dicePics.obj: ../dicePics.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler v3.0'
	"C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/bin/cl430" $(GEN_OPTS_QUOTED) --fp_reassoc=off --include_path="C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/include" --sat_reassoc=off --symdebug:dwarf --plain_char=unsigned --silicon_version=msp --printf_support=full --preproc_with_compile --preproc_dependency="dicePics.pp" $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

eZ430X.obj: ../eZ430X.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler v3.0'
	"C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/bin/cl430" $(GEN_OPTS_QUOTED) --fp_reassoc=off --include_path="C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/include" --sat_reassoc=off --symdebug:dwarf --plain_char=unsigned --silicon_version=msp --printf_support=full --preproc_with_compile --preproc_dependency="eZ430X.pp" $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

lab7_a.obj: ../lab7_a.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler v3.0'
	"C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/bin/cl430" $(GEN_OPTS_QUOTED) --fp_reassoc=off --include_path="C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/include" --sat_reassoc=off --symdebug:dwarf --plain_char=unsigned --silicon_version=msp --printf_support=full --preproc_with_compile --preproc_dependency="lab7_a.pp" $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

lab7_b.obj: ../lab7_b.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler v3.0'
	"C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/bin/cl430" $(GEN_OPTS_QUOTED) --fp_reassoc=off --include_path="C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/include" --sat_reassoc=off --symdebug:dwarf --plain_char=unsigned --silicon_version=msp --printf_support=full --preproc_with_compile --preproc_dependency="lab7_b.pp" $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

lab7_c.obj: ../lab7_c.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler v3.0'
	"C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/bin/cl430" $(GEN_OPTS_QUOTED) --fp_reassoc=off --include_path="C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/include" --sat_reassoc=off --symdebug:dwarf --plain_char=unsigned --silicon_version=msp --printf_support=full --preproc_with_compile --preproc_dependency="lab7_c.pp" $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

random.obj: ../random.asm $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler v3.0'
	"C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/bin/cl430" $(GEN_OPTS_QUOTED) --fp_reassoc=off --include_path="C:/Program Files/Texas Instruments/CC Essentials v3/tools/compiler/MSP430/include" --sat_reassoc=off --symdebug:dwarf --plain_char=unsigned --silicon_version=msp --printf_support=full --preproc_with_compile --preproc_dependency="random.pp" $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


