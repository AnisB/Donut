GENERATE_PROGRAM(bezierProgram)

if(ROOF)
GENERATE_PROGRAM(roofGeneration)
endif(ROOF)

GENERATE_PROGRAM(objSerializer)

GENERATE_PROGRAM(brdfReader)
