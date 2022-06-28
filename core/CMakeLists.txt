SET(CORE_SOURCE
  item.cc
  book.cc
  video_cd.cc
  painting.cc
  manager.cc
)

ADD_LIBRARY(core-static STATIC ${CORE_SOURCE})
SET_TARGET_PROPERTIES(core-static PROPERTIES OUTPUT_NAME "core")
SET_TARGET_PROPERTIES(core-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
