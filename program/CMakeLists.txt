GENERATE_PROGRAM(bezierProgram)

if(ROOF)
GENERATE_PROGRAM(roofGeneration)
endif(ROOF)

GENERATE_PROGRAM(wavefrontConverter)

GENERATE_PROGRAM(brdfReader)
