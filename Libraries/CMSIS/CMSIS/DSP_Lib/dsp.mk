DSPBASE = /home/kalyansreenivas/Projects/chibios_practice_programs/Libraries/CMSIS/CMSIS/

# Required include directories
DSPINC += $(DSPBASE)/Include

include $(DSPBASE)/DSP_Lib/Source/BasicMathFunctions/BasicMathFunctions.mk
include $(DSPBASE)/DSP_Lib/Source/CommonTables/CommonTables.mk
include $(DSPBASE)/DSP_Lib/Source/ComplexMathFunctions/ComplexMathFunctions.mk
include $(DSPBASE)/DSP_Lib/Source/ControllerFunctions/ControllerFunctions.mk
include $(DSPBASE)/DSP_Lib/Source/FastMathFunctions/FastMathFunctions.mk
include $(DSPBASE)/DSP_Lib/Source/FilteringFunctions/FilteringFunctions.mk
include $(DSPBASE)/DSP_Lib/Source/MatrixFunctions/MatrixFunctions.mk
include $(DSPBASE)/DSP_Lib/Source/StatisticsFunctions/StatisticsFunctions.mk
include $(DSPBASE)/DSP_Lib/Source/SupportFunctions/SupportFunctions.mk
include $(DSPBASE)/DSP_Lib/Source/TransformFunctions/TransformFunctions.mk