include_directories(BEFORE sources/src/h)

add_library(rneg ${LIBTYPE}
${SNP_SRC}
sources/src/negatest/negatestcell.cpp
sources/src/negmain/negdefs.cpp
sources/src/recog/negrecog.cpp
sources/src/negmain/recnegmain.cpp
sources/src/negmain/rnegbase.cpp
sources/src/searchneg/searchneg.cpp
)
set_property(TARGET rneg PROPERTY COMPILE_DEFINITIONS __RNEG__)

target_link_libraries(rneg
cimage
cpage
rdib
rimage
rselstr
exc
rstr
)

library_hook(rneg)
